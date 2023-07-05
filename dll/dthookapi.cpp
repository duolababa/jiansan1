#include"pch.h"
#include"detours.h"

BOOL hookapi(PVOID *oldApi/*要HOOK的地址 变量*/, PVOID newApi/*新的函数地址*/)
{
	BOOL br = FALSE;
	DetourRestoreAfterWith();//恢复原来状态
	DetourTransactionBegin();//拦截开始
	DetourUpdateThread(GetCurrentThread());//刷新当前线程

	//这里可以连续多次调用DetourAttach，表明HOOK多个函数
	//DetourAttach(&(PVOID&)OldCreateMutexA,NewCreateMutexA);
	DetourAttach(oldApi, newApi);
	//br返回NO_ERROR表示成功
	br = DetourTransactionCommit();//让拦截生效
	if (br == NO_ERROR)
	{
		br = TRUE;
	}
	else
	{
		br = FALSE;
	}
	return br;
}

BOOL unhookapi(PVOID *oldApi, PVOID newApi)
{
	BOOL br = FALSE;
	DetourTransactionBegin();//HOOK开始
	DetourUpdateThread(GetCurrentThread());;//刷新当前线程
	//这里可以连续多次调用DetourDetach,表明撤销多个函数HOOK
	DetourDetach(oldApi, newApi);//卸载HOOK
	br = DetourTransactionCommit();//HOOK生效
	if (br == NO_ERROR)
	{
		br = TRUE;
	}
	else
	{
		br = FALSE;
	}
	return br;
}


