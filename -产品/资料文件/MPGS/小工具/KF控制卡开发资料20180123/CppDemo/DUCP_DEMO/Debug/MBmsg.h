
#ifndef _MBMSG_H_
#define _MBMSG_H_

#include <stdint.h>

// ���� ifdef ���Ǵ���ʹ�� DLL �������򵥵�
// ��ı�׼�������� DLL �е������ļ��������������϶���� DUCP_EXPORTS
// ���ű���ġ���ʹ�ô� DLL ��
// �κ�������Ŀ�ϲ�Ӧ����˷��š�������Դ�ļ��а������ļ����κ�������Ŀ���Ὣ
// DUCP_API ������Ϊ�Ǵ� DLL ����ģ����� DLL ���ô˺궨���
// ������Ϊ�Ǳ������ġ�
#ifdef DUCP_EXPORTS
#define DUCP_API __declspec(dllexport)
#else
#define DUCP_API __declspec(dllimport)
#endif

#if defined(__cplusplus)
extern "C" {     /* Make sure we have C-declarations in C++ programs */
#endif

#define MB_STK_ADDR_DEF		(0x00)	/*Ĭ�ϵĵ�ַ*/
#define MB_STK_FC_DEF		(100)	/*Ĭ�ϵĹ�����*/


#define MB_MSG_SIZE_MAX		(255)

/*
	��Ϣ�ṹ
*/
typedef struct {
	uint8_t 	PN[2];
	uint8_t  	MsgId;
	uint8_t 	DLen;
	uint8_t  	Data[MB_MSG_SIZE_MAX];
} MB_MSG_T;

/*
	��Ϣ������ɻص���������
*/
typedef int8_t (*cbMsgRdy_t)(MB_MSG_T *);

typedef int8_t (*cbSTKOut_t)(uint8_t * p,uint32_t size);

/*
    CRC16У�麯��
*/
EXTERN_C DUCP_API uint16_t MB_CRC16(uint8_t *pFrame, uint16_t count);

/*
	����Э����������ص�����
*/
EXTERN_C DUCP_API void MB_STK_SetOutCallback(cbSTKOut_t cb);

/*
	Э��ջ��������
*/
EXTERN_C DUCP_API int8_t MB_STK_In(uint8_t * pBuff, uint16_t Size);
/*
	���õ�ַ
*/
EXTERN_C DUCP_API uint8_t MB_STK_SetAddr(uint8_t NewAddr);

/*
	������Ϣ�����ص�����
*/
EXTERN_C DUCP_API void MB_MSG_SetMsgRdyCallback(cbMsgRdy_t cb);


/*
	������Ϣ
	PN + MSGID + DLEN + DATA
*/
EXTERN_C DUCP_API int8_t MB_MSG_Send(MB_MSG_T * pMsg, uint32_t Ovtime);

/*
	����Ϣ
	PN + MSGID + DLEN + DATA
*/
EXTERN_C DUCP_API int8_t MB_MSG_Read(MB_MSG_T * pMsg, uint32_t Ovtime);

/*
	����Ϣ
	PN + MSGID + DLEN + DATA
*/
EXTERN_C DUCP_API MB_MSG_T * MB_MSG_ReadEx(uint32_t Ovtime);

#if defined(__cplusplus)
}
#endif

#endif

