#pragma once
#include "pch.h"
DWORD getResIndexByName(CString cName);
INT64 getResAddrById(DWORD dResTypeIndex);
INT64 getResAddrByTypeId(DWORD dResTypeIndex, DWORD dResId, DWORD dStartOffest, DWORD dNextOffest, DWORD dArraySize);
INT64 getItemResAddrById(DWORD dResId);
INT64 getSquareResAddrById(DWORD dResId);
INT64 getMapResAddrById(DWORD dResId);
INT64 getVehicleResAddrById(DWORD dResId);
INT64 getNpcResAddrById(DWORD dResId);
INT64 getShipResAddrById(DWORD dResId);
INT64 getCrewResAddrById(DWORD dResId);
BYTE getItemBoxType(int dItemResId);
CString GetName(INT64 dNameAddr);
INT64 getAttrAddr(DWORD dId);
DWORD getEncryValue(INT64 dAttrAddr, DWORD dIndex);
float  GetDis(float X1, float Y1, float Z1);
float  GetDis1(float X1, float Y1, float Z1);
//char* UnicodeToAnsi(const wchar_t* szStr);
INT64 getStringAddr(DWORD dStrIndex, INT64 dStrAddr, DWORD dStrLen);
int 距离计算(int x1, int y1, int z1, int x2, int y2, int z2);
DWORD 取相对角度(float fx, float fy);
float 距离计算3(float x1, float y1, float z1, float x2, float y2, float z2);