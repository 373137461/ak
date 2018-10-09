CC = $(CROSS_PREFIX)g++
CC_FLAG = -Wall -O2

OBJ = 000_ICE_IPCSDK_GetParkingSpaceNum.tst \
	001_ICE_IPCSDK_GetEnableParkingSpace.tst 002_ICE_IPCSDK_SetEnableParkingSpace.tst \
	003_ICE_IPCSDK_GetParkingSpaceType.tst 004_ICE_IPCSDK_SetParkingSpaceType.tst \
	005_ICE_IPCSDK_GetRemoteDevState.tst 006_ICE_IPCSDK_SetRemoteDevState.tst \
	007_ICE_IPCSDK_GetControlDevState.tst 008_ICE_IPCSDK_SetControlDevState.tst \
	009_ICE_IPCSDK_GetAllParkingSpaceLoops.tst 010_ICE_IPCSDK_SetAllParkingSpaceLoops.tst \
	011_ICE_IPCSDK_GetUARTCfg.tst 012_ICE_IPCSDK_SetUARTCfg.tst \
	013_ICE_IPCSDK_GetSingleParkingSpaceStatus.tst \
	014_ICE_IPCSDK_GetAllParkingSpaceStatus.tst \
	015_ICE_IPCSDK_TransSerialPort.tst 016_ICE_IPCSDK_TransSerialPort_RS232.tst\
	017_ICE_IPCSDK_SearchDev.tst 018_ICE_IPCSDK_SyncTime_GetDevTime.tst\
	019_ICE_IPCSDK_Get_Set_LightCtlParam.tst 020_ICE_IPCSDK_Get_Set_CGIParam.tst\
	021_ICE_IPCSDK_ModifyDevIP.tst

all : $(OBJ)

%.tst : %.cpp
	$(CC) $(CC_FLAG) -I../ $< -o $@ ../lib/libice_ipgsdk.a -lpthread


install :
	cp *.tst bin

clean :
	rm -f *.tst
