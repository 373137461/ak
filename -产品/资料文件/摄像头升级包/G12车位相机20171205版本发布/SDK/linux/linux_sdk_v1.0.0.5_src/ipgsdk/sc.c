#include "sc.h"

#include "thread.h"
#include "list.h"

#include <stdlib.h>

#ifdef _WIN32
#include <WinSock2.h>
#else
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#endif

#ifdef _WIN32
#define socklen_t int
#define close closesocket
#define MSG_DONTWAIT 0
#define MSG_NOSIGNAL 0
#define EWOULDBLOCK WSAEWOULDBLOCK
#define SOCKET_ERRNO WSAGetLastError()
#else
#define SOCKET_ERRNO errno
#endif

typedef struct
{
	char ip[32];
	unsigned short port;

	sc_callback_t callback;
	void *param;

	int sockfd;
	struct hlist_node node;

	int dead;

} _sc_handle_t;

#define HASH_SIZE 127
static struct hlist_head g_handle_hlist[HASH_SIZE];
static pthread_mutex_t g_handle_mutex/* = NULL*/;

static int g_exit = 0;
static pthread_t g_hThread = NULL;

#define MAX_SOCKFD 4096
static int g_sockfd_count = 0;

#define BUF_SIZE (64 * 1024)

static THREAD_TYPE recv_proc(void *param)
{
	char *buf = (char*)malloc(BUF_SIZE);
	if (NULL == buf)
		return 0;

	while (!g_exit)
	{
		int i, len, max_fd = -1;

		fd_set fds;
		struct timeval tv;
		
		FD_ZERO(&fds);

		MUTEX_LOCK(g_handle_mutex);
		for (i = 0; i < HASH_SIZE; i++)
		{
			struct hlist_node *node;

			if (hlist_empty(g_handle_hlist + i))
				continue;

			hlist_for_each(node, g_handle_hlist + i)
			{
				_sc_handle_t *handle = hlist_entry(node, _sc_handle_t, node);
				if (handle->dead)
					continue;

				FD_SET(handle->sockfd, &fds);
				if (handle->sockfd > max_fd)
					max_fd = handle->sockfd;
			}
		}
		MUTEX_UNLOCK(g_handle_mutex);

		if (-1 == max_fd)
		{
			usleep(40000);
			continue;
		}

		tv.tv_sec = 0;
		tv.tv_usec = 40000;
  
		if (select(max_fd + 1, &fds, NULL, NULL, &tv) <= 0)
			continue;
		
		MUTEX_LOCK(g_handle_mutex);
		for (i = 0; i < HASH_SIZE; i++)
		{
			struct hlist_node *node;

			if (hlist_empty(g_handle_hlist + i))
				continue;

			hlist_for_each(node, g_handle_hlist + i)
			{
				_sc_handle_t *handle = hlist_entry(node, _sc_handle_t, node);
				if (handle->dead)
					continue;

				if (!FD_ISSET(handle->sockfd, &fds))
					continue;

				len = recv(handle->sockfd, buf, BUF_SIZE, 0);
				if (len <= 0)
					handle->dead = 1;

				if (NULL != handle->callback)
					(*handle->callback)(handle->ip, handle->port, buf, len, handle->param);
			}
		}
		MUTEX_UNLOCK(g_handle_mutex);
	}

	free(buf);
	return 0;
}

int sc_init()
{
	int i = 0;

	if (NULL != g_hThread)
		return 1;

	for (; i < HASH_SIZE; i++)
		INIT_HLIST_HEAD(g_handle_hlist + i);

	//if (NULL == g_handle_mutex)
	{
		CREATE_MUTEX(g_handle_mutex);
		//if (NULL == g_handle_mutex)
			//return 0;
	}

	if (NULL == g_hThread)
	{
		g_exit = 0;

		CREATE_THREAD(g_hThread, recv_proc, NULL);
		if (NULL == g_hThread)
		{
			DESTROY_MUTEX(g_handle_mutex);
			return 0;
		}
	}

	return 1;
}

void sc_fini()
{
	if (NULL == g_hThread)
		return;

	if (NULL != g_hThread)
	{
		g_exit = 1;

		DESTROY_THREAD(g_hThread);
		g_hThread = NULL;
	}

	//if (NULL != g_handle_mutex)
	{
		DESTROY_MUTEX(g_handle_mutex);
		//g_handle_mutex = NULL;
	}
}

static int socket_connect(unsigned ip, unsigned short port, int timeout_ms)
{
    int sockfd;
    struct sockaddr_in addr;

#ifdef _WIN32
	u_long arg = 1;
#else
	int flags;
#endif

    sockfd = (int)socket(AF_INET, SOCK_STREAM, 0);
    if (-1 == sockfd)
        return -1;

#ifdef _WIN32
	ioctlsocket(sockfd, FIONBIO, &arg);
#else
    flags = fcntl(sockfd, F_GETFL, 0);
    fcntl(sockfd, F_SETFL, flags | O_NONBLOCK);
#endif
    
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = ip;
    addr.sin_port = htons(port);
    memset(addr.sin_zero, 0, sizeof(addr.sin_zero));
    
    if (-1 == connect(sockfd, (struct sockaddr*)&addr, sizeof(struct sockaddr)))
    {
        fd_set fds;
        struct timeval tv;
        int ret, optval = 0;
		socklen_t optlen = sizeof(socklen_t);

        FD_ZERO(&fds);
        FD_SET(sockfd, &fds);
        
        tv.tv_sec = timeout_ms / 1000;
        tv.tv_usec = (timeout_ms % 1000) * 1000;

        ret = select(sockfd + 1, NULL, &fds, NULL, &tv);
        if ((ret <= 0) || !FD_ISSET(sockfd, &fds))
        {
            close(sockfd);
            return -1;
        }
        
        ret = getsockopt(sockfd, SOL_SOCKET, SO_ERROR, (char*)&optval, &optlen);
        if ((0 != ret) || (0 != optval))
        {
            close(sockfd);
            return -1;
        }
    }

#ifndef _WIN32
    fcntl(sockfd, F_SETFL, flags);
#endif

    return sockfd;
}

sc_handle_t sc_connect(const char *ip, unsigned short port, sc_callback_t callback, void *param)
{
	int sockfd;
	_sc_handle_t *handle;

	MUTEX_LOCK(g_handle_mutex);
	if (g_sockfd_count >= MAX_SOCKFD)
	{
		MUTEX_UNLOCK(g_handle_mutex);
		return NULL;
	}
	MUTEX_UNLOCK(g_handle_mutex);

	sockfd = socket_connect(inet_addr(ip), port, 40);
	if (-1 == sockfd)
		return NULL;

	handle = (_sc_handle_t*)malloc(sizeof(_sc_handle_t));
	if (NULL == handle)
	{
		close(sockfd);
		return NULL;
	}

	memset(handle, 0, sizeof(_sc_handle_t));
	strcpy(handle->ip, ip);
	handle->port = port;
	handle->callback = callback;
	handle->param = param;
	handle->sockfd = sockfd;
	INIT_HLIST_NODE(&handle->node);

	MUTEX_LOCK(g_handle_mutex);
	hlist_add_head(&handle->node, g_handle_hlist + sockfd % HASH_SIZE);
	g_sockfd_count++;
	MUTEX_UNLOCK(g_handle_mutex);

	return handle;
}

void sc_close(sc_handle_t handle)
{
	_sc_handle_t *_handle;

	if (NULL == handle)
		return;

	_handle = (_sc_handle_t*)handle;

	MUTEX_LOCK(g_handle_mutex);
	hlist_del(&_handle->node);
	g_sockfd_count--;
	MUTEX_UNLOCK(g_handle_mutex);

	close(_handle->sockfd);
	free(_handle);
}

int sc_send(sc_handle_t handle, const void *data, int len, int timeout_ms)
{
	_sc_handle_t *_handle;
	int sent = 0, ret;

	if (NULL == handle)
		return 0;

	_handle = (_sc_handle_t*)handle;

    while (sent < len)
    {
        ret = send(_handle->sockfd, (const char*)data + sent, 
			len - sent, MSG_NOSIGNAL | MSG_DONTWAIT);
		
        if (ret > 0)
        {
            sent += ret;
        }
        else
        {
            fd_set fds;
            struct timeval tv;
            
			if (EWOULDBLOCK != SOCKET_ERRNO)
                return sent;
            
            FD_ZERO(&fds);
            FD_SET(_handle->sockfd, &fds);

            tv.tv_sec = timeout_ms / 1000;
            tv.tv_usec = (timeout_ms % 1000) * 1000;
            
            ret = select(_handle->sockfd + 1, NULL, &fds, NULL, &tv);
            if ((ret <= 0) || !FD_ISSET(_handle->sockfd, &fds))
                break;
        }
    }

	return sent;
}

int sc_get_sockfd(sc_handle_t handle)
{
	_sc_handle_t *_handle;

	if (NULL == handle)
		return -1;

	_handle = (_sc_handle_t*)handle;
	return _handle->sockfd;
}
