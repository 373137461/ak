#include "sm.h"
#include "socket.h"
#include "thread.h"
#include "sc.h"
#include "list.h"
#include "Log.h"
#include <stdlib.h>

typedef struct
{
	list_head node;
	int len;

} sc_data_t;

typedef struct
{
	pthread_t thread;	//解析与回调线程
	int exit;
	
	char ip[32];
	uint16_t port;

	sm_callback_t callback;
	void *param;

	list_head node;			//会话链表节点，链接所有会话

	sc_handle_t handle;				//socket连接句柄
	pthread_mutex_t connect_mutex;	//连接句柄锁
	int connect_status;				//连接状态

	int connect_interval;	//重连间隔
	int timer_count;		//定时器计数

	list_head list;			//数据接收队列
	pthread_mutex_t mutex;	//数据队列锁
	int packet_count;		//数据队列长度

} sm_param_t;

//会话链表
static struct list_head g_session_list = LIST_HEAD_INIT(g_session_list);
static pthread_mutex_t g_session_mutex/* = NULL*/;

//定时器
//UINT_PTR g_timer_ptr = 0;
static pthread_t g_timer_thread = NULL;
static int g_exit = 0;

static void sc_callback(const char *ip, unsigned short port, const void *data, int len, void *param)
{
	sm_param_t *rp = (sm_param_t*)param;

	//限制队列长度
	MUTEX_LOCK(rp->mutex);
	if (rp->packet_count > 1024)
	{
		MUTEX_UNLOCK(rp->mutex);
		CLog::GetInstance()->Logf(LEVEL_WARN, "%s:%d 数据队列满，丢弃", rp->ip, rp->port);
		return;
	}
	MUTEX_UNLOCK(rp->mutex);

	//分配内存
	size_t size = sizeof(sc_data_t);
	if (len > 0)
		size += len;
	
	sc_data_t *sd = (sc_data_t*)malloc(size);
	if (NULL == sd)
	{
		CLog::GetInstance()->Logf(LEVEL_WARN, "%d 字节内存分配失败，内存耗尽", size);
		return;
	}

	//初始化节点
	INIT_LIST_HEAD(&sd->node);

	//复制数据
	sd->len = len;
	if (len > 0)
		memcpy(sd + 1, data, len);

	//加入队列尾
	MUTEX_LOCK(rp->mutex);
	list_add_tail(&sd->node, &rp->list);
	rp->packet_count++;
	MUTEX_UNLOCK(rp->mutex);
}

void close_session(sm_param_t *param)
{
	param->connect_interval = 1;
	param->timer_count = 0;

	//关闭连接
	MUTEX_LOCK(param->connect_mutex);
	if (NULL != param->handle)
	{
		sc_close(param->handle);
		param->handle = NULL;
	}
	MUTEX_UNLOCK(param->connect_mutex);

	//释放所有内存
	struct list_head *node, *tmp;
	sc_data_t *sd;

	MUTEX_LOCK(param->mutex);
	list_for_each_safe(node, tmp, &param->list)
	{
		sd = list_entry(node, sc_data_t, node);
		list_del(node);
		
		free(sd);
	}
	param->packet_count = 0;
	MUTEX_UNLOCK(param->mutex);

	//触发离线回调
	if (NULL != param->callback)
		(*param->callback)(NULL, 0, param->param);
}

static THREAD_TYPE timer_thread_proc(void *param)
{
	int count = 0;

	while (!g_exit)
	{
		if (count++ < 25)
		{
			usleep(40000);
			continue;
		}

		count = 0;
		struct list_head *node;
	
		//遍历会话
		MUTEX_LOCK(g_session_mutex);
		list_for_each(node, &g_session_list)
		{
			sm_param_t *param = list_entry(node, sm_param_t, node);
			if (0 != param->connect_status)
				continue;

			//处理重连
			MUTEX_LOCK(param->connect_mutex);
			if (NULL == param->handle)
			{
				//重连间隔指数级递增，最大32秒
				param->timer_count++;
				if (0 != (param->timer_count % param->connect_interval))
				{
					MUTEX_UNLOCK(param->connect_mutex);
					continue;
				}

				param->handle = sc_connect(param->ip, param->port, sc_callback, param);
				if (NULL == param->handle)
				{
					//连接失败
					MUTEX_UNLOCK(param->connect_mutex);

					param->timer_count = 0;
					if (param->connect_interval < 30)
						param->connect_interval <<= 1;

					CLog::GetInstance()->Logf(LEVEL_INFO, "%s:%d 重连失败，%d 秒后尝试重连", 
						param->ip, param->port, param->connect_interval);
					continue;
				}

				//触发在线回调
				if (NULL != param->callback)
					(*param->callback)(NULL, 1, param->param);

				CLog::GetInstance()->Logf(LEVEL_INFO, "%s:%d 重连成功", param->ip, param->port);
			}
			MUTEX_UNLOCK(param->connect_mutex);

			//触发定时器回调
			if (NULL != param->callback)
				(*param->callback)(NULL, -1, param->param);
		}
		MUTEX_UNLOCK(g_session_mutex);
	}

	return 0;
}

int sm_init()
{
	if (NULL != g_timer_thread)
		return 1;

	//初始化会话锁
	//if (NULL == g_session_mutex)
	{
		CREATE_MUTEX(g_session_mutex);
		//if (NULL == g_session_mutex)
			//return 0;
	}

	//开启定时器
	if (NULL == g_timer_thread)
	{
		CREATE_THREAD(g_timer_thread, timer_thread_proc, NULL);
		if (NULL == g_timer_thread)
		{
			DESTROY_MUTEX(g_session_mutex);
			return 0;
		}
	}
	/*if (0 == g_timer_ptr)
	{
		g_timer_ptr = SetTimer(NULL, 0, 1000, timer_proc);
		if (0 == g_timer_ptr)
		{
			DESTROY_MUTEX(g_session_mutex);
			return 0;
		}
	}*/

	return 1;
}

void sm_fini()
{
	if (NULL == g_timer_thread)
		return;

	//停止定时器
	/*if (0 != g_timer_ptr)
	{
		KillTimer(NULL, g_timer_ptr);
		g_timer_ptr = 0;
	}*/
	if (NULL != g_timer_thread)
	{
		g_exit = 1;
		DESTROY_THREAD(g_timer_thread);
		g_timer_thread = NULL;
	}

	//销毁会话锁
	//if (NULL != g_session_mutex)
	{
		DESTROY_MUTEX(g_session_mutex);
		//g_session_mutex = NULL;
	}
}

static THREAD_TYPE callback_proc(void *param)
{
	sm_param_t *rp = (sm_param_t*)param;

	sc_data_t *sd;
	struct list_head *node, *tmp;

	while (!rp->exit)
	{
		MUTEX_LOCK(rp->mutex);
		if (&rp->list == rp->list.next)
		{
			//队列空
			MUTEX_UNLOCK(rp->mutex);
			usleep(30000);
			continue;
		}

		//从队头获取数据
		sd = list_first_entry(&rp->list, sc_data_t, node);
		list_del(&sd->node);
		rp->packet_count--;
		MUTEX_UNLOCK(rp->mutex);

		if (sd->len > 0)
		{
			if (NULL != rp->callback)
				(*rp->callback)((char*)(sd + 1), sd->len, rp->param);

			CLog::GetInstance()->Logf(LEVEL_DEBUG, "%s:%d 收到 %d 字节数据", rp->ip, rp->port, sd->len);
		}
		else
		{
			//连接已断开
			close_session(rp);
			CLog::GetInstance()->Logf(LEVEL_INFO, "%s:%d 连接已断开", rp->ip, rp->port);
		}

		//释放内存
		free(sd);
	}

	//退出前释放所有内存
	list_for_each_safe(node, tmp, &rp->list)
	{
		sd = list_entry(node, sc_data_t, node);
		list_del(node);
		
		free(sd);
	}

	return 0;
}

sm_handle_t sm_connect(const char *ip, uint16_t port, sm_callback_t callback, void *param)
{
	sm_param_t *rp = (sm_param_t*)malloc(sizeof(sm_param_t));
	if (NULL == rp)
		return NULL;

	memset(rp, 0, sizeof(sm_param_t));

	//保存参数
	strncpy(rp->ip, ip, 32);
	rp->port = port;
	rp->callback = callback;
	rp->param = param;
	rp->connect_interval = 1;

	//初始化队列
	INIT_LIST_HEAD(&rp->list);

	//创建锁与线程
	CREATE_MUTEX(rp->mutex);
	CREATE_MUTEX(rp->connect_mutex);
	CREATE_THREAD(rp->thread, callback_proc, rp);

	//添加到链表
	INIT_LIST_HEAD(&rp->node);

	MUTEX_LOCK(g_session_mutex);
	list_add_tail(&rp->node, &g_session_list);
	MUTEX_UNLOCK(g_session_mutex);

	//连接设备
	MUTEX_LOCK(rp->connect_mutex);
	if (NULL == rp->handle)
	{
		rp->handle = sc_connect(ip, port, sc_callback, rp);
		if (NULL != rp->handle)
		{
			//触发在线回调
			if (NULL != rp->callback)
				(*rp->callback)(NULL, 1, rp->param);
		}
	}
	MUTEX_UNLOCK(rp->connect_mutex);

	return rp;
}

void sm_close(sm_handle_t handle)
{
	sm_param_t *param;

	if (NULL == handle)
		return;

	param = (sm_param_t*)handle;

	//从会话链表移除
	MUTEX_LOCK(g_session_mutex);
	list_del(&param->node);
	MUTEX_UNLOCK(g_session_mutex);

	//断开设备
	MUTEX_LOCK(param->connect_mutex);
	if (NULL != param->handle)
	{
		sc_close(param->handle);
		param->handle = NULL;
	}
	MUTEX_UNLOCK(param->connect_mutex);

	//关闭线程
	param->exit = 1;
	DESTROY_THREAD(param->thread);

	//销毁锁
	DESTROY_MUTEX(param->connect_mutex);
	DESTROY_MUTEX(param->mutex);

	free(param);
}

int sm_get_status(sm_handle_t handle)
{
	sm_param_t *param;

	if (NULL == handle)
		return 0;

	param = (sm_param_t*)handle;

	//获取连接状态
	MUTEX_LOCK(param->connect_mutex);
	int status = (NULL != param->handle);
	MUTEX_UNLOCK(param->connect_mutex);

	return status;
}

void sm_close_session(sm_handle_t handle, int status)
{
	sm_param_t *param;

	if (NULL == handle)
		return;

	param = (sm_param_t*)handle;

	param->connect_status = status;
	close_session(param);

	CLog::GetInstance()->Logf(LEVEL_INFO, "主动断开与 %s:%d 的连接", param->ip, param->port);
}

int sm_send(sm_handle_t handle, const void *data, int len, int timeout_ms)
{
	sm_param_t *param;
	int result;

	if (NULL == handle)
		return 0;

	param = (sm_param_t*)handle;

	MUTEX_LOCK(param->connect_mutex);
	if (NULL == param->handle)
	{
		MUTEX_UNLOCK(param->connect_mutex);
		return 0;
	}

	result = sc_send(param->handle, data, len, timeout_ms);
	MUTEX_UNLOCK(param->connect_mutex);

	return result;
}

int sm_get_sockfd(sm_handle_t handle)
{
	sm_param_t *param;
	int sockfd;

	if (NULL == handle)
		return 0;

	param = (sm_param_t*)handle;

	MUTEX_LOCK(param->connect_mutex);
	if (NULL == param->handle)
	{
		MUTEX_UNLOCK(param->connect_mutex);
		return -1;
	}

	sockfd = sc_get_sockfd(param->handle);
	MUTEX_UNLOCK(param->connect_mutex);

	return sockfd;
}
