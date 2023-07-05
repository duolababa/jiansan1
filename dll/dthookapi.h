#pragma once
#include<Windows.h>
#include"detours.h"

BOOL hookapi(PVOID *oldApi/*要HOOK的地址 变量*/, PVOID newApi/*新的函数地址*/);//安装HOOK
BOOL unhookapi(PVOID *oldApi, PVOID newApi);//卸载HOOK