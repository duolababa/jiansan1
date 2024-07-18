#pragma once
#include "pch.h"

#include <psapi.h>
#include <iostream>
#include <vector>
#include <Windows.h>




float  GetDis(float X1, float Y1, float Z1);
float  GetDis1(float X1, float Y1, float Z1);
//char* UnicodeToAnsi(const wchar_t* szStr);
INT64 getStringAddr(DWORD dStrIndex, INT64 dStrAddr, DWORD dStrLen);
int 距离计算(int x1, int y1, int z1, int x2, int y2, int z2);
DWORD 取相对角度(float fx, float fy);
float 距离计算3(float x1, float y1, float z1, float x2, float y2, float z2);
SIZE_T getMemoryUse();
bool EnumObjInfo(LPVOID pBuffer, DWORD pid);
LPVOID GetSystemProcessHandleInfo();
void 测试多开();

DWORD64 距离计算x(DWORD64 x1, DWORD64 y1, DWORD64 x2, DWORD64 y2);