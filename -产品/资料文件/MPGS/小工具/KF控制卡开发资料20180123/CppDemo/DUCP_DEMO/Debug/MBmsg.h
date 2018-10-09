
#ifndef _MBMSG_H_
#define _MBMSG_H_

#include <stdint.h>

// 下列 ifdef 块是创建使从 DLL 导出更简单的
// 宏的标准方法。此 DLL 中的所有文件都是用命令行上定义的 DUCP_EXPORTS
// 符号编译的。在使用此 DLL 的
// 任何其他项目上不应定义此符号。这样，源文件中包含此文件的任何其他项目都会将
// DUCP_API 函数视为是从 DLL 导入的，而此 DLL 则将用此宏定义的
// 符号视为是被导出的。
#ifdef DUCP_EXPORTS
#define DUCP_API __declspec(dllexport)
#else
#define DUCP_API __declspec(dllimport)
#endif

#if defined(__cplusplus)
extern "C" {     /* Make sure we have C-declarations in C++ programs */
#endif

#define MB_STK_ADDR_DEF		(0x00)	/*默认的地址*/
#define MB_STK_FC_DEF		(100)	/*默认的功能码*/


#define MB_MSG_SIZE_MAX		(255)

/*
	消息结构
*/
typedef struct {
	uint8_t 	PN[2];
	uint8_t  	MsgId;
	uint8_t 	DLen;
	uint8_t  	Data[MB_MSG_SIZE_MAX];
} MB_MSG_T;

/*
	消息接收完成回调函数类型
*/
typedef int8_t (*cbMsgRdy_t)(MB_MSG_T *);

typedef int8_t (*cbSTKOut_t)(uint8_t * p,uint32_t size);

/*
    CRC16校验函数
*/
EXTERN_C DUCP_API uint16_t MB_CRC16(uint8_t *pFrame, uint16_t count);

/*
	设置协议数据输出回调函数
*/
EXTERN_C DUCP_API void MB_STK_SetOutCallback(cbSTKOut_t cb);

/*
	协议栈数据输入
*/
EXTERN_C DUCP_API int8_t MB_STK_In(uint8_t * pBuff, uint16_t Size);
/*
	设置地址
*/
EXTERN_C DUCP_API uint8_t MB_STK_SetAddr(uint8_t NewAddr);

/*
	设置消息就绪回调函数
*/
EXTERN_C DUCP_API void MB_MSG_SetMsgRdyCallback(cbMsgRdy_t cb);


/*
	发送消息
	PN + MSGID + DLEN + DATA
*/
EXTERN_C DUCP_API int8_t MB_MSG_Send(MB_MSG_T * pMsg, uint32_t Ovtime);

/*
	读消息
	PN + MSGID + DLEN + DATA
*/
EXTERN_C DUCP_API int8_t MB_MSG_Read(MB_MSG_T * pMsg, uint32_t Ovtime);

/*
	读消息
	PN + MSGID + DLEN + DATA
*/
EXTERN_C DUCP_API MB_MSG_T * MB_MSG_ReadEx(uint32_t Ovtime);

#if defined(__cplusplus)
}
#endif

#endif

