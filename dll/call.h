#pragma once
#include "pch.h"

extern "C"
{


	int Addasm(int a, int b);
}



EXTERN_C __int64 setGameModule(__int64 hWowModuleBase);

INT64 fun获取第第一个参数指针();

INT64 fun获取第第2个参数指针(DWORD xx);
void fun递归遍历对象列表(INT64 arg二叉结构指针,_stu对象列表 &arg对象列表, _stu对象 人物对象);

void fun递归遍历地面对象列表(INT64 arg二叉结构指针, _stu对象列表& arg对象列表, _stu对象 人物对象);
_stu对象列表 fun获取对象数据();

INT64 fun获取背包指针();

_stu背包 fun获取背包数据();

void HOOk初始化();
INT64 call_luatostring(char* script);
_stu对象 fun人物信息列表();
bool 是否掉线();
INT64 fun人物指针();
CString 弹窗信息();

bool 是否在过图();
void anjianCALL(DWORD r8, DWORD r9, DWORD rdx);