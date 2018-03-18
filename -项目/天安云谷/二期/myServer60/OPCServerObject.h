
#pragma once

#ifdef _USRDLL
	#define ExportClass   __declspec( dllexport )
#else
	#define ExportClass   __declspec( dllimport )
#endif

//#include "opcDataReceiver.h"
#include "opcda.h"


/// Call back virtual class - receiver data from OPC connections 
class COPCReceiveData
{

public:
	/*! Push new data item to client 

		@param name - param name, maybe NULL if clientID is not INVALID_CLIENT_ID 
		@param clientID - client param ID, maybe INVALID_CLIENT_ID if name is not NULL
		@param time - time stamp
		@param value - param value 
		@param Quality - OPC quality flag 
	*/
	virtual void newData(LPCTSTR name, DWORD clientID, FILETIME &time, VARIANT &value, WORD Quality) = 0;
	
	/// after calls newData, called newItemIsReceived
	virtual void newItemIsReceived( DWORD count ) { count; };
	virtual void StatusChanged( int , const char * ) { };
};

/*!
	������������ ����?��� ������ ?OPC �������� 
	��?������?���������� 0 ���� ��?������
*/
class COPCServerObject
{
public:
	/// ���������� ��� ������?������?
	virtual void setServerProgID(LPCTSTR progID) = 0;

	/// ���������� CLSID ������?
	virtual void setServerCLSID(REFCLSID progID) = 0;

	/// ���������������� ������ ?������?
	virtual int RegisterServer(void) = 0;

	/// ����������������?������ ?������?
	virtual int UnregisterServer(void) = 0;

    /// ��������?������
	virtual int StartServer(OPCSERVERSTATE state = OPC_STATUS_NOCONFIG) = 0;
	
    /// ����������?������?������?
	virtual int StopServer(void) = 0;

	/// 
	virtual void SetServerState(OPCSERVERSTATE state) = 0;

	/// ������?������?����������??������ ����������
	virtual void SetDelimeter( const char *ch ) = 0;

	/// �������� ��??���� ������?
	///		��?���� ����������� ��?���� ?����������?������?������ ?���� ��������
	///     ������������ �������� - ���������� ����?��?-1 ?������, ���� ����?��?��?����������
	virtual int AddTag( LPCTSTR name, VARTYPE type, bool readOnly = true) = 0;

	/// �������� �������� ��������?
	virtual bool WriteValue( LPCTSTR name, FILETIME ft, WORD quality, const VARIANT &value ) = 0;
	virtual bool WriteValue( LPCTSTR name, FILETIME ft, WORD quality, int value ) = 0;
	virtual bool WriteValue( LPCTSTR name, FILETIME ft, WORD quality, float value ) = 0;
	virtual bool WriteValue( LPCTSTR name, FILETIME ft, WORD quality, double value ) = 0;
	virtual bool WriteValue( LPCTSTR name, FILETIME ft, WORD quality, int* value , unsigned count ) = 0;
	virtual bool WriteValue( LPCTSTR name, FILETIME ft, WORD quality, float* value, unsigned count ) = 0;
	virtual bool WriteValue( LPCTSTR name, FILETIME ft, WORD quality, double* value, unsigned count ) = 0;

	/// �������� �������� ��������?
	virtual bool WriteValue( int hdl, FILETIME ft, WORD quality, const VARIANT &value ) = 0;
	virtual bool WriteValue( int hdl, FILETIME ft, WORD quality, int value ) = 0;
	virtual bool WriteValue( int hdl, FILETIME ft, WORD quality, float value ) = 0;
	virtual bool WriteValue( int hdl, FILETIME ft, WORD quality, double value ) = 0;
	virtual bool WriteValue( int hdl, FILETIME ft, WORD quality, int* value , unsigned count ) = 0;
	virtual bool WriteValue( int hdl, FILETIME ft, WORD quality, float* value, unsigned count ) = 0;
	virtual bool WriteValue( int hdl, FILETIME ft, WORD quality, double* value, unsigned count ) = 0;

	/// ������?������?��������?�� �������� �������� �� ��������?���������� ����
	virtual void setDataReceiver( COPCReceiveData *receiver) = 0;

public:
	// ��������?
	virtual WORD QualityGood(void) = 0;
	virtual WORD QualityBad(void) = 0;
	virtual FILETIME FILETIME_NULL(void) = 0;
};

extern "C" 
{
	/*! ������?������?��� ������?OPCServer */
	ExportClass COPCServerObject* WINAPI CreateNewOPCServerObject(void);
}