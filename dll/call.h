#pragma once
#include "pch.h"

extern "C"
{


	int Addasm(int a, int b);
}



EXTERN_C __int64 setGameModule(__int64 hWowModuleBase);

INT64 fun��ȡ�ڵ�һ������ָ��();

INT64 fun��ȡ�ڵ�2������ָ��(DWORD xx);
void fun�ݹ���������б�(INT64 arg����ṹָ��,_stu�����б� &arg�����б�, _stu���� �������);

void fun�ݹ������������б�(INT64 arg����ṹָ��, _stu�����б�& arg�����б�, _stu���� �������);
_stu�����б� fun��ȡ��������();

INT64 fun��ȡ����ָ��();

_stu���� fun��ȡ��������();

void HOOk��ʼ��();
INT64 call_luatostring(char* script);
_stu���� fun������Ϣ�б�();
bool �Ƿ����();
INT64 fun����ָ��();
CString ������Ϣ();

bool �Ƿ��ڹ�ͼ();
void anjianCALL(DWORD r8, DWORD r9, DWORD rdx);