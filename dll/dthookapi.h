#pragma once
#include<Windows.h>
#include"detours.h"

BOOL hookapi(PVOID *oldApi/*ҪHOOK�ĵ�ַ ����*/, PVOID newApi/*�µĺ�����ַ*/);//��װHOOK
BOOL unhookapi(PVOID *oldApi, PVOID newApi);//ж��HOOK