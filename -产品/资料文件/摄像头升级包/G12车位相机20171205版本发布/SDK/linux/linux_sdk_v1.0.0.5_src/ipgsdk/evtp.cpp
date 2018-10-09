#include "evtp.h"
#include "socket.h"
#include "thread.h"
#include "Md5.h"
#include "sc.h"
#include "sm.h"
#include "list.h"

#include "ice_com_type.h"

#define BUF_SIZE (1024 * 1024)

typedef struct
{
	CLog *clog;
	
	char ip[32];
	uint16_t port;

	evtp_callback_t callback;
	void *param;

	uint8_t encrypt;
	char passwd[128];

	sm_handle_t handle;

	int heart_beat_loss;	//������ʧ����

	char trunc_buf[1500];	//����ضϻ���
	int trunc_len;			//�ѽضϳ���

	int sequence;			//�����
	int dropped;			//�Ƿ񶪰�
	char buf[BUF_SIZE];		//���ݽ�������
	int result_len;			//���ݽ����ܳ���

} evtp_param_t;

static void close_session(evtp_param_t *rp, int status)
{
	//��ռ���
	rp->heart_beat_loss = rp->trunc_len = 0;
	rp->sequence = rp->dropped = 0;

	//�رջỰ
	sm_close_session(rp->handle, status);
}

void handle_packet(evtp_param_t *param, const char *data, int len, int mark)
{
	ICE_OPER_DATA_S *header = (ICE_OPER_DATA_S*)data;

	if (mark)
	{
		//У����󣬱�ʾ�������쳣
		if ((0x5A != data[len - 2]) || (0x7E != data[len - 1]))
		{
			param->clog->Logf("%s:%d ����У����󣬶���", param->ip, param->port);
			return;
		}

		if (0 == param->sequence)
			param->sequence = header->u32Id;	//��ʼ������
		else if (!param->dropped && ((param->sequence + 1) != header->u32Id))
		{
			if (NULL != param->callback)
				(*param->callback)(param->param, header->u32Type, param->buf, param->result_len);

			param->dropped = 1;		//���Ų������������ж���
			param->clog->Logf("%s:%d ֡�Ų�������������ڶ��� : %d - %d", 
				param->ip, param->port, param->sequence + 1, header->u32Id);
		}
		
		param->sequence = header->u32Id;
		
		int first = header->u32Status & 0x80;	//�ϱ����ݵ�һ����
		if (param->dropped)
		{
			if (0 == first)
				return;	//��������ֱ����һ���ϱ�����
			
			param->dropped = 0;
		}
		
		int last = header->u32Status & 0x40;	//�ϱ��������һ����
		
		if (0x80 == first)
			param->result_len = 0;
		
		//����С������������
		memcpy(param->buf + param->result_len, header + 1, header->u32Size - 32);
		param->result_len += header->u32Size - 32;
		
		if (0x40 == last)
		{
			if (NULL != param->callback)
				(*param->callback)(param->param, header->u32Type, param->buf, param->result_len);

			param->clog->Logf("%s:%d ���ݳ��� : %d, �������� : %d", 
				param->ip, param->port, param->result_len, header->u32Type);
		}
	}
	else
	{
		//����Ӧ��
		if ((ICE_CONTROL_TYPE_VDR_REQUEST_ALARM_DATA_RSP == header->u32Type) || 
			(ICE_CONTROL_TYPE_VDR_REQUEST_ALARM_DATA_PASSWD_RSP == header->u32Type))
		{
			if (ICE_ERR_NO_LISENCE == header->u32Status)
			{
				close_session(param, ICE_ERR_NO_LISENCE);
				param->clog->Logf("%s:%d ����У�����", param->ip, param->port);
				return;
			}

			param->heart_beat_loss = 0;
		}
	}
}

static int find_next_mark(const char *data, int offset, int length)
{
	int index = offset;
	for (; index < length; index++)
	{
		if (0x7E == data[index])
			break;
	}
	
	return index;
}

static int parse_header(const char *data, int offset, int length)
{
	//��ͷ���ض�
	if (offset + 6 > length)
		return length - offset;

	//��Ч�ı�־
	if (0x5A != data[offset + 1])
		return 1;

	//��Ч�İ�����
	int len = *(int*)(data + offset + 2);
	if (len > 1500)
		return 2;

	return 4 + len;	//2 + len + 2
}

int parse_packet(evtp_param_t *param, const char *data, int offset, int length)
{
	//����ض�
	if (param->trunc_len > 0)
	{
		//��ͷ������
		if (param->trunc_len < 6)
		{
			//������Ҫ���ֽ���
			int len = 6 - param->trunc_len;
			if (len > length - offset)
				len = length - offset;

			//�����ͷ
			memcpy(param->trunc_buf + param->trunc_len, data + offset, len);
			param->trunc_len += len;

			return len;
		}

		//������ͷ
		int len = parse_header(param->trunc_buf, 0, param->trunc_len);
		if (len < 6)
		{
			param->clog->Logf("%s:%d �ضϺ�İ�ͷ��������", param->ip, param->port);

			param->trunc_len = 0;
			return parse_packet(param, data, offset, length);
		}
		len -= param->trunc_len;

		//ʣ���ֽ���ƥ��
		if ((length - offset) == len)
		{
			memcpy(param->trunc_buf + param->trunc_len, data + offset, len);
			param->trunc_len += len;

			handle_packet(param, param->trunc_buf + 2, param->trunc_len - 2, 1);
			param->trunc_len = 0;

			return len;
		}
		else if (len > (length - offset))
		{
			//��Ҫ����ض�
			len = length - offset;

			memcpy(param->trunc_buf + param->trunc_len, data + offset, len);
			param->trunc_len += len;

			return len;
		}
		else
		{
			//����ʣ���ֽ�
			int next = find_next_mark(data, offset + len, length);

			//У������
			if (next > offset + len)
				handle_packet(param, data + offset + len, next - (offset + len), 0);

			//��������
			memcpy(param->trunc_buf + param->trunc_len, data + offset, len);
			param->trunc_len += len;

			handle_packet(param, param->trunc_buf + 2, param->trunc_len - 2, 1);
			param->trunc_len = 0;

			return next - offset;
		}
	}

	//������ʼλ��
	int index = find_next_mark(data, offset, length);
	if (index > offset)
		handle_packet(param, data + offset, index - offset, 0);

	if (length == index)
		return 0;

	//������ͷ
	int len = parse_header(data, index, length);
	if (len < 6)
	{
		if (length == index + len)
		{
			//��Ҫ����ض�
			param->trunc_len = length - index;
			memcpy(param->trunc_buf, data + index, param->trunc_len);

			return length - offset;
		}

		param->clog->Logf("%s:%d ��ͷ��������", param->ip, param->port);
		return index + len - offset;
	}

	if (length == (index + len))
	{
		handle_packet(param, data + index + 2, len - 2, 1);
		return length - offset;
	}
	else if (index + len > length)
	{
		//��Ҫ����ض�
		param->trunc_len = length - index;
		memcpy(param->trunc_buf, data + index, param->trunc_len);

		return length - offset;
	}
	else
	{
		//��������λ��
		int next = find_next_mark(data, index + len, length);

		//У������
		if (next > index + len)
			handle_packet(param, data + index + len, next - (index + len), 0);

		//��������
		handle_packet(param, data + index + 2, len - 2, 1);
		return next - offset;
	}
}

void sm_callback(const void *data, int len, void *param)
{
	evtp_param_t *rp = (evtp_param_t*)param;

	if (NULL == data)
	{
		if (len >= 0)
		{
			//�����¼�
			if (NULL != rp->callback)
				(*rp->callback)(rp->param, 0, NULL, len);
		}
		else
		{
			//��ʱ���¼�
			if (NULL == rp->handle)
				return;

			//������ʧ����������ֵ���Ͽ�����
			rp->heart_beat_loss++;
			if (rp->heart_beat_loss >= 3)
			{
				close_session(rp, 0);
				rp->clog->Logf("%s:%d �������ʧ�ܣ��Ͽ�����", rp->ip, rp->port);
				return;
			}

			//��������
			ICE_OPER_DATA_S header = {0};
			header.u32Size = 32;
			header.u32Channel = 1;
			header.u32Type = ICE_CONTROL_TYPE_VDR_REQUEST_ALARM_DATA;

			//�����������
			if (rp->encrypt)
			{
				MD5_CTX ctx;
				MD5Init(&ctx);

				MD5Update(&ctx, (unsigned char*)rp->passwd, (unsigned int)strlen(rp->passwd));
				MD5Final(&ctx);

				memcpy(&header.u32Time, ctx.digest, 16);
				header.u32Type = ICE_CONTROL_TYPE_VDR_REQUEST_ALARM_DATA_PASSWD;
			}

			//��������
			sm_send(rp->handle, &header, 32, 40);
		}

		return;
	}

	//��������
	int offset = 0;
	while (offset < len)
	{
		rp->clog->Logf(LEVEL_DEBUG, "%s:%d �������� [ %d / %d ]", rp->ip, rp->port, offset, len);

		int result = parse_packet(rp, (char*)data, offset, len);
		if (result <= 0)
			break;
		
		offset += result;
	}
}

evtp_handle_t evtp_start(const char *ip, uint16_t port, 
	evtp_callback_t callback, void *param)
{
	return evtp_start_passwd(ip, port, NULL, callback, param);
}

evtp_handle_t evtp_start_passwd(const char *ip, uint16_t port, 
	const char *passwd, evtp_callback_t callback, void *param)
{
	CLog *log = CLog::GetInstance();
	return evtp_start_passwd_withLog(ip, port, log, passwd, callback, param);
}

evtp_handle_t evtp_start_withLog(const char *ip, uint16_t port, 
	CLog *log, evtp_callback_t callback, void *param)
{
	return evtp_start_passwd_withLog(ip, port, log, NULL, callback, param);
}

evtp_handle_t evtp_start_passwd_withLog(const char *ip, uint16_t port, 
	CLog *log, const char *passwd, evtp_callback_t callback, void *param)
{
	evtp_param_t *rp = (evtp_param_t*)malloc(sizeof(evtp_param_t));
	if (NULL == rp)
		return NULL;

	memset(rp, 0, sizeof(evtp_param_t));

	//�������
	strncpy(rp->ip, ip, 32);
	rp->port = port;
	rp->callback = callback;
	rp->param = param;
	rp->clog = log;

	if (NULL != passwd)
	{
		rp->encrypt = 1;
		strcpy(rp->passwd, passwd);
	}

	//�����豸
	rp->handle = sm_connect(ip, port, sm_callback, rp);
	if (NULL != rp->handle)
		sm_callback(NULL, -1, rp);

	return rp;
}

void evtp_stop(evtp_handle_t handle)
{
	evtp_param_t *param;

	if (NULL == handle)
		return;

	param = (evtp_param_t*)handle;

	//�Ͽ��豸
	if (NULL != param->handle)
		sm_close(param->handle);

	free(param);
}

int evtp_get_status(evtp_handle_t handle)
{
	evtp_param_t *param;

	if (NULL == handle)
		return 0;

	param = (evtp_param_t*)handle;
	if (NULL == param->handle)
		return 0;

	return sm_get_status(param->handle);
}
