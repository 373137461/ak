

#include <stdint.h>
#include <stdio.h>                      //�������롢��������ĵ���,printf, gets
#include <winsock2.h>                   //socketͷ�ļ�
#include <Windows.h>                    //Ϊ�˷�����ԣ����Լ����˵ȴ�2��Ž�������server�������õ���sleep����
#include "Comm.h"
#include "mbmsg.h"
#include "mbphy.h"
#pragma comment (lib, "ws2_32")         //socket���ļ�

static char _IP[32] = "192.168.100.100";
static int  _Port;
static int _DevID = 0;
static HANDLE _hComm;
static char  _strComm[32] = "";
static uint32_t _Baud = 19200;
static uint8_t _RxBuff[512];
static uint16_t _RxSize;
static uint8_t _TxBuff[512];
static uint16_t _TxSize;


static pfcbSTK_t _cbOut = 0;
static pfcbSTK_t _cbIn = 0;


int8_t MB_STK_Out(uint8_t * pBuff, uint16_t Size);
/*
	ѡ�������豸
*/
void MB_PHY_SelPHY(int ID)
{
	_DevID = ID;
}

/*
	����IP��ַ�Ͷ˿�
*/
void MB_PHY_SetIP(const char * IP, int Port)
{
	strcpy(_IP, IP);
	_Port = Port;
	MB_STK_SetOutCallback(MB_STK_Out);
}

/*
���ô��ںźͲ�����
*/
void MB_PHY_SetBaud(const char * CommName, int Baud)
{
	strcpy(_strComm, CommName);
	_Baud = Baud;
	MB_STK_SetOutCallback(MB_STK_Out);
}

/*������������ص�*/
void MB_PHY_SetCallback(pfcbSTK_t cbOut, pfcbSTK_t cbIn)
{
	_cbOut = cbOut;
	_cbIn = cbIn;
}


#if 0
void Connect(void)
{
	WSADATA wsd;
	SOCKET cClient;
	int ret;
	struct sockaddr_in server;
	hostent *host = NULL;

	if (WSAStartup(MAKEWORD(2, 0), &wsd)){ return 0; }
	cClient = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (cClient == INVALID_SOCKET){ return 0; }
	//set Recv and Send time out
	int TimeOut = 6000; //���÷��ͳ�ʱ6��
	if (setsockopt(cClient, SOL_SOCKET, SO_SNDTIMEO, (char *)&TimeOut, sizeof(TimeOut)) == SOCKET_ERROR){
		return 0;
	}
	TimeOut = 6000;//���ý��ճ�ʱ6��
	if (setsockopt(cClient, SOL_SOCKET, SO_RCVTIMEO, (char *)&TimeOut, sizeof(TimeOut)) == SOCKET_ERROR){
		return 0;
	}
	//���÷�������ʽ����
	unsigned long ul = 1;
	ret = ioctlsocket(cClient, FIONBIO, (unsigned long*)&ul);
	if (ret == SOCKET_ERROR)return 0;

	//����
	server.sin_family = AF_INET;
	server.sin_port = htons(25);
	server.sin_addr.s_addr = inet_addr((LPCSTR)pSmtp);
	if (server.sin_addr.s_addr == INADDR_NONE){ return 0; }

	connect(cClient, (const struct sockaddr *)&server, sizeof(server));

	//select ģ�ͣ������ó�ʱ
	struct timeval timeout;
	fd_set r;

	FD_ZERO(&r);
	FD_SET(cClient, &r);
	timeout.tv_sec = 15; //���ӳ�ʱ15��
	timeout.tv_usec = 0;
	ret = select(0, 0, &r, 0, &timeout);
	if (ret <= 0)
	{
		closesocket(cClient);
		return 0;
	}
	//һ�������ģʽ�׽ӱȽ��ѿ��ƣ����Ը���ʵ��������� ���������ģʽ
	unsigned long ul1 = 0;
	ret = ioctlsocket(cClient, FIONBIO, (unsigned long*)&ul1);
	if (ret == SOCKET_ERROR){
		closesocket(cClient);
		return 0;
	}
}
#endif

#if 0
/*
	�շ�����
*/
int8_t MB_PHY_TCP_SendReceve(uint8_t * pBuff, uint16_t Size, uint8_t * pRBuff, uint16_t *pRSize)
{
	WSADATA         wd;
	int ret = 0;
	static SOCKET c = 0;
	SOCKADDR_IN saddr;
	uint8_t recvBuf[1000];

	/*1.��ʼ������*/
	ret = WSAStartup(MAKEWORD(2, 2), &wd);
	if (ret != 0) {
		return -1;
	}
	if (HIBYTE(wd.wVersion) != 2 || LOBYTE(wd.wVersion) != 2) {
		WSACleanup();
		return -1;
	}
	if (c == 0) {
		/*2.�����ͻ���socket*/
		c = socket(AF_INET, SOCK_STREAM, 0);
		int nNetTimeout = 2000;
		if (SOCKET_ERROR == setsockopt(c, SOL_SOCKET, SO_RCVTIMEO, (char *)&nNetTimeout, sizeof(int)))
		{
			closesocket(c);
			WSACleanup();
			return -1;
		}
		if (SOCKET_ERROR == setsockopt(c, SOL_SOCKET, SO_SNDTIMEO, (char *)&nNetTimeout, sizeof(int)))
		{
			closesocket(c);
			WSACleanup();
			return -1;
		}

		/*3.����Ҫ���ӵķ������Ϣ*/
		saddr.sin_addr.S_un.S_addr = inet_addr(_IP);
		saddr.sin_family = AF_INET;
		saddr.sin_port = htons(_Port);

		/*4.���ӷ����*/
		ret = connect(c, (SOCKADDR*)&saddr, sizeof(SOCKADDR));
		if (ret != 0)
		{
			closesocket(c);
			WSACleanup();
			return -1;
		}
	}

	/*5���������ݵ�������*/
	ret = send(c, pBuff, Size, 0);
	if (ret == SOCKET_ERROR) {
		//closesocket(c);
		WSACleanup();
		return -1;
	}
	/*6.���ܷ������ķ���*/
	ret = recv(c, recvBuf, sizeof(recvBuf), 0);
	if (ret != SOCKET_ERROR) {
		if (pRBuff) {
			memcpy(pRBuff, recvBuf, ret);
			if (pRSize) {
				*pRSize = ret;
			}
		}
		memcpy(_RxBuff, recvBuf, ret);
		_RxSize = ret;
		if (_cbIn) {
			_cbIn(_RxBuff, _RxSize);
		}
		MB_STK_In(recvBuf, ret);
	}
	//closesocket(c);
	//WSACleanup();

	return 0;
}

#else
/*
�շ�����
*/
int8_t MB_PHY_TCP_SendReceve(uint8_t * pBuff, uint16_t Size, uint8_t * pRBuff, uint16_t *pRSize)
{
	WSADATA         wd;
	int ret = 0;
	SOCKET c = 0;
	SOCKADDR_IN saddr;
	uint8_t recvBuf[1000];

	/*1.��ʼ������*/
	ret = WSAStartup(MAKEWORD(2, 2), &wd);
	if (ret != 0) {
		return -1;
	}
	if (HIBYTE(wd.wVersion) != 2 || LOBYTE(wd.wVersion) != 2) {
		WSACleanup();
		return -1;
	}
	/*2.�����ͻ���socket*/
	c = socket(AF_INET, SOCK_STREAM, 0);
	int nNetTimeout = 2000;
	if (SOCKET_ERROR == setsockopt(c, SOL_SOCKET, SO_RCVTIMEO, (char *)&nNetTimeout, sizeof(int)))
	{
		closesocket(c);
		WSACleanup();
		return -1;
	}
	if (SOCKET_ERROR == setsockopt(c, SOL_SOCKET, SO_SNDTIMEO, (char *)&nNetTimeout, sizeof(int)))
	{
		closesocket(c);
		WSACleanup();
		return -1;
	}

	/*3.����Ҫ���ӵķ������Ϣ*/
	saddr.sin_addr.S_un.S_addr = inet_addr(_IP);
	saddr.sin_family = AF_INET;
	saddr.sin_port = htons(_Port);

	/*4.���ӷ����*/
	ret = connect(c, (SOCKADDR*)&saddr, sizeof(SOCKADDR));
	if (ret != 0)
	{
		closesocket(c);
		WSACleanup();
		return -1;
	}

	/*5���������ݵ�������*/
	ret = send(c, pBuff, Size, 0);
	if (ret == SOCKET_ERROR) {
		closesocket(c);
		WSACleanup();
		return -1;
	}
	/*6.���ܷ������ķ���*/
	ret = recv(c, recvBuf, sizeof(recvBuf), 0);
	if (ret != SOCKET_ERROR) {
		if (pRBuff) {
			memcpy(pRBuff, recvBuf, ret);
			if (pRSize) {
				*pRSize = ret;
			}
		}
		memcpy(_RxBuff, recvBuf, ret);
		_RxSize = ret;
		if (_cbIn) {
			_cbIn(_RxBuff, _RxSize);
		}
		MB_STK_In(recvBuf, ret);
	}

	closesocket(c);
	WSACleanup();

	return 0;
}
#endif

int8_t MB_PHY_UDP_SendReceve(uint8_t * pBuff, uint16_t Size, uint8_t * pRBuff, uint16_t *pRSize)
{
	WSADATA         wd;
	int ret = 0;
	static SOCKET c = 0;
	SOCKADDR_IN saddr;
	uint8_t recvBuf[1000];

	/*1.��ʼ������*/
	ret = WSAStartup(MAKEWORD(2, 2), &wd);
	if (ret != 0) {
		return -1;
	}
	if (HIBYTE(wd.wVersion) != 2 || LOBYTE(wd.wVersion) != 2) {
		WSACleanup();
		return -1;
	}

	/*2.�����ͻ���socket*/
	if (c == 0) {
		c = socket(AF_INET, SOCK_DGRAM, 0);
	}
	/*5���������ݵ�������*/
	saddr.sin_addr.S_un.S_addr = inet_addr(_IP);
	saddr.sin_family = AF_INET;
	saddr.sin_port = htons(_Port);
	sendto(c, pBuff, Size, 0, (SOCKADDR*)&saddr, sizeof(SOCKADDR));

	
	/*6.���ܷ������ķ���*/
	ret = recvfrom(c, recvBuf, sizeof(recvBuf), 0, 0, 0);
	if (ret != SOCKET_ERROR) {
		if (pRBuff) {
			memcpy(pRBuff, recvBuf, ret);
			if (pRSize) {
				*pRSize = ret;
			}
		}
		memcpy(_RxBuff, recvBuf, ret);
		_RxSize = ret;
		if (_cbIn) {
			_cbIn(_RxBuff, _RxSize);
		}
		MB_STK_In(recvBuf, ret);
	}

	return 0;
}
/*
Э��ջ�������
*/
int8_t MB_STK_OutEx(uint8_t * pBuff, uint16_t Size,uint8_t * pRBuff,uint16_t *pRSize)
{
	int MsgSizeMax;
	int TimeConst;

	//memcpy(_TxBuff, pBuff, Size);
	//_TxSize = Size;

	if (_cbOut) {
		_cbOut(pBuff, Size);
	}
	switch (_DevID) {
	case 0:
		return MB_PHY_TCP_SendReceve(pBuff, Size, pRBuff, pRSize);
	case 2:
		return MB_PHY_UDP_SendReceve(pBuff, Size, pRBuff, pRSize);
	case 1:
		MsgSizeMax = sizeof(MB_MSG_T)+5;
		TimeConst = (MsgSizeMax * 1000 / _Baud) + 200;/*ͨ��ʱ�� ���� �豸�Ĵ���ʱ��(Ԥ��200MS)*/
		_hComm = COMM_OpenEx3(_strComm, _Baud, 8, NOPARITY, ONESTOPBIT, TimeConst, 0, 5, 1000, 2, 0);
		if (_hComm == 0) {
			return -1;
		}

		Sleep(5);
		//PurgeComm(_hComm, PURGE_TXCLEAR | PURGE_TXABORT);
		//PurgeComm(_hComm, PURGE_RXCLEAR | PURGE_RXABORT);
		COMM_Write(_hComm, pBuff, Size);
		uint32_t rSize = COMM_Read(_hComm, _RxBuff, MsgSizeMax);
		MB_STK_In(_RxBuff, rSize);
		if (pRBuff && rSize) {
			memcpy(pRBuff, _RxBuff, rSize);
			if (pRSize) {
				*pRSize = rSize;
			}
			_RxSize = rSize;
			if (_cbIn) {
				_cbIn(_RxBuff, _RxSize);
			}
		}
		COMM_Close(&_hComm);
		return 0;
	}
	return -1;
}

/*
	Э��ջ�������
*/
int8_t MB_STK_Out(uint8_t * pBuff, uint16_t Size)
{
	return MB_STK_OutEx(pBuff, Size, 0, 0);
}
