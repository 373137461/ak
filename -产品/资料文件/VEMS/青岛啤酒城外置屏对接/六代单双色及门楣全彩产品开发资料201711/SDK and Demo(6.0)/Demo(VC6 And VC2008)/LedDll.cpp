#include "StdAfx.h"
#include "LedDll.h"








CLedDll::CLedDll()
{
	
}

CLedDll::~CLedDll()
{
	if(m_hDll!=NULL)
		FreeLibrary(m_hDll);

}


BOOL CLedDll::InitDll()
{
#ifdef _UNICODE
	m_hDll=LoadLibrary (_T("LV_LED_U.DLL"));
#else
	m_hDll=LoadLibrary (_T("LV_LED.DLL"));
#endif
	if(m_hDll==NULL)
	{
		AfxMessageBox(_T("Load \"LV_LED.DLL\" Failed"));
		return FALSE;
	}	

	LV_CreateProgram=(_LV_CreateProgram)GetProcAddress(m_hDll,"LV_CreateProgram");
	LV_AddProgram=(_LV_AddProgram)GetProcAddress(m_hDll,"LV_AddProgram");
	LV_SetProgramTime=(_LV_SetProgramTime)GetProcAddress(m_hDll,"LV_SetProgramTime");
	LV_AddImageTextArea=(_LV_AddImageTextArea)GetProcAddress(m_hDll,"LV_AddImageTextArea");
	LV_AddFileToImageTextArea=(_LV_AddFileToImageTextArea)GetProcAddress(m_hDll,"LV_AddFileToImageTextArea");
	LV_AddSingleLineTextToImageTextArea=(_LV_AddSingleLineTextToImageTextArea)GetProcAddress(m_hDll,"LV_AddSingleLineTextToImageTextArea");
	LV_AddMultiLineTextToImageTextArea=(_LV_AddMultiLineTextToImageTextArea)GetProcAddress(m_hDll,"LV_AddMultiLineTextToImageTextArea");
	LV_AddStaticTextToImageTextArea=(_LV_AddStaticTextToImageTextArea)GetProcAddress(m_hDll,"LV_AddStaticTextToImageTextArea");
	LV_QuickAddSingleLineTextArea=(_LV_QuickAddSingleLineTextArea)GetProcAddress(m_hDll,"LV_QuickAddSingleLineTextArea");
	LV_AddDigitalClockArea=(_LV_AddDigitalClockArea)GetProcAddress(m_hDll,"LV_AddDigitalClockArea");
	LV_AddTimeArea=(_LV_AddTimeArea)GetProcAddress(m_hDll,"LV_AddTimeArea");
	LV_AddClockArea=(_LV_AddClockArea)GetProcAddress(m_hDll,"LV_AddClockArea");
	LV_AddWaterBorder=(_LV_AddWaterBorder)GetProcAddress(m_hDll,"LV_AddWaterBorder");
	LV_DeleteProgram=(_LV_DeleteProgram)GetProcAddress(m_hDll,"LV_DeleteProgram");
	LV_Send=(_LV_Send)GetProcAddress(m_hDll,"LV_Send");
	LV_MultiSendOne=(_LV_MultiSendOne)GetProcAddress(m_hDll,"LV_MultiSendOne");
	LV_MultiSend=(_LV_MultiSend)GetProcAddress(m_hDll,"LV_MultiSend");
	LV_TestOnline=(_LV_TestOnline)GetProcAddress(m_hDll,"LV_TestOnline");
	LV_SetBasicInfo=(_LV_SetBasicInfo)GetProcAddress(m_hDll,"LV_SetBasicInfo");
	LV_SetOEDA=(_LV_SetOEDA)GetProcAddress(m_hDll,"LV_SetOEDA");
	LV_AdjustTime=(_LV_AdjustTime)GetProcAddress(m_hDll,"LV_AdjustTime");
	LV_PowerOnOff=(_LV_PowerOnOff)GetProcAddress(m_hDll,"LV_PowerOnOff");
	LV_TimePowerOnOff=(_LV_TimePowerOnOff)GetProcAddress(m_hDll,"LV_TimePowerOnOff");
	LV_SetBrightness=(_LV_SetBrightness)GetProcAddress(m_hDll,"LV_SetBrightness");
	LV_TimeBrightness=(_LV_TimeBrightness)GetProcAddress(m_hDll,"LV_TimeBrightness");
	LV_SetLanguage=(_LV_SetLanguage)GetProcAddress(m_hDll,"LV_SetLanguage");
	LV_LedTest=(_LV_LedTest)GetProcAddress(m_hDll,"LV_LedTest");
	LV_TimeLocker=(_LV_TimeLocker)GetProcAddress(m_hDll,"LV_TimeLocker");
	LV_CancelLocker=(_LV_CancelLocker)GetProcAddress(m_hDll,"LV_CancelLocker");
	LV_SetLedCommunicationParameter=(_LV_SetLedCommunicationParameter)GetProcAddress(m_hDll,"LV_SetLedCommunicationParameter");
	LV_GetError=(_LV_GetError)GetProcAddress(m_hDll,"LV_GetError");

	return TRUE;
}

