

#ifndef _MB_PHY_
#define _MB_PHY_

#if defined(__cplusplus)
extern "C" {     /* Make sure we have C-declarations in C++ programs */
#endif

typedef void(*pfcbSTK_t)(uint8_t * pBuff, uint16_t Size);

void MB_PHY_SetCallback(pfcbSTK_t cbOut, pfcbSTK_t cbIn);
void MB_PHY_SelPHY(int ID);
void MB_PHY_SetIP(const char * IP, int Port);
void MB_PHY_SetBaud(const char * CommName, int Baud);
int8_t MB_STK_Out(uint8_t * pBuff, uint16_t Size);
int8_t MB_STK_OutEx(uint8_t * pBuff, uint16_t Size, uint8_t * pRBuff, uint16_t *pRSize);

#if defined(__cplusplus)
}
#endif

#endif
