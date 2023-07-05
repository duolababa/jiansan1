#include "pch.h"
#include "hook_api.h"

//BOOL WINAPI GetCursorPos(_Out_ LPPOINT lpPoint);
typedef BOOL(WINAPI* GetCursorPos_)(
	_Out_ LPPOINT lpPoint);

GetCursorPos_ OGetCursorPos = (GetCursorPos_)GetProcAddress(GetModuleHandleA("user32.dll"), "GetCursorPos");
RECT R1;
BOOL WINAPI MyGetCursorPos(_Out_ LPPOINT lpPoint)
{
	if (屏蔽鼠标开关 && g_hWnd)
	{
		GetWindowRect(g_hWnd, &R1);
		lpPoint->x = hook鼠标坐标.x + R1.left;
		lpPoint->y = hook鼠标坐标.y + R1.top;
	}
	return OGetCursorPos(lpPoint);

}
void hook_api::hookNtCursorPos(BOOL isHook)
{
	if (!OGetCursorPos)
	{
		OutputDebugStringW(L"hookNtCursorPos==NULL");
		return;
	}
	//GetCursorPos();
	BOOL br = 0;
	if (isHook)
	{
		br = hookapi((PVOID*)&OGetCursorPos, MyGetCursorPos);
	}
	else
	{
		br = unhookapi((PVOID*)&OGetCursorPos, MyGetCursorPos);
	}

	OutputDebugStringW(L"hookNtCursorPos OK");

};

#include "tlhelp32.h";
 // 关键指令，希望跳过这条指令

// 设置WIN7硬件断点函数
void SetHardwareBreakPoint()
{
	CONTEXT ctx;
	ctx.ContextFlags = CONTEXT_ALL;
	GetThreadContext(GetCurrentThread(), &ctx);
	ctx.Dr7 = (DWORD)0x1; // 启用Dr0
	ctx.Dr0 = g_dwBreakpoint; // 设置硬件断点	
	SetThreadContext(GetCurrentThread(), &ctx);
}

// 异常处理函数
DWORD NTAPI ExceptionHandler(PEXCEPTION_POINTERS pExceptionInfo)
{
	//MyTrace(L"0x%I64X | 0x%I64X", DWORD64(pExceptionInfo->ExceptionRecord->ExceptionAddress), g_dwBreakpoint);
	//if (pExceptionInfo->ExceptionRecord->ExceptionCode == EXCEPTION_SINGLE_STEP)
	//{
	//	if ((DWORD64)pExceptionInfo->ExceptionRecord->ExceptionAddress == g_dwBreakpoint)
	//	{
	//		//SetWindowTextW(g_hWnd, L"Mir4G");
	//		/*if (屏蔽鼠标开关 == true)
	//		{*/
	//		/*pExceptionInfo->ContextRecord->Dr7 = (DWORD)0x1;
	//		pExceptionInfo->ContextRecord->Dr0 = g_dwBreakpoint;*/
	//		pExceptionInfo->ContextRecord->Rax = 0;
	//		pExceptionInfo->ContextRecord->Rip += 5;
	//		//}

	//		// 已经处理了异常，不需要调用下一个异常处理来处理该异常
	//		return EXCEPTION_CONTINUE_EXECUTION;
	//	}
	//	else
	//	{
	//		pExceptionInfo->ContextRecord->Dr7 = (DWORD)0x405;
	//		pExceptionInfo->ContextRecord->Dr0 = g_dwBreakpoint;
	//		return EXCEPTION_CONTINUE_EXECUTION;
	//	}
	//}
	if (pExceptionInfo->ExceptionRecord->ExceptionCode == STATUS_BREAKPOINT)
	{
		if ((DWORD64)pExceptionInfo->ExceptionRecord->ExceptionAddress == g_dwBreakpoint)
		{
			pExceptionInfo->ContextRecord->Rip += 0x6;
			return EXCEPTION_CONTINUE_EXECUTION;
		}
		/*if ((DWORD64)pExceptionInfo->ExceptionRecord->ExceptionAddress == g_dwBreakpoint2)
		{
			pExceptionInfo->ContextRecord->Rip += 0x25;
			return EXCEPTION_CONTINUE_EXECUTION;
		}*/
	}
	//if (pExceptionInfo->ExceptionRecord->ExceptionCode == EXCEPTION_ACCESS_VIOLATION)
	//{
	//	pExceptionInfo->ContextRecord->Rip += 0x6;
	//	//::MessageBox(NULL, L"出现EXCEPTION_ACCESS_VIOLATION 异常" + 整数到文本((DWORD64)pExceptionInfo->ExceptionRecord->ExceptionAddress) , L"", MB_OK);
	//	return EXCEPTION_CONTINUE_EXECUTION;
	//}
	/*else
	{
		pExceptionInfo->ContextRecord->Dr7 = (DWORD)0x405;
		pExceptionInfo->ContextRecord->Dr0 = g_dwBreakpoint;
		return EXCEPTION_CONTINUE_EXECUTION;
	}*/
	//if ((DWORD64)pExceptionInfo->ExceptionRecord->ExceptionAddress == g_dwBreakpoint2)
	//{
	//	//SetWindowTextW(g_hWnd, L"Mir4G");
	//
	//		pExceptionInfo->ContextRecord->Rip += 6;
	//	

	//	// 已经处理了异常，不需要调用下一个异常处理来处理该异常
	//	return EXCEPTION_CONTINUE_EXECUTION;
	//}
	return EXCEPTION_CONTINUE_SEARCH;
}

// 设置硬件断点WIN10版本：挂起主线程->设置硬件断点->恢复主线程
DWORD WINAPI SetHardwareBreakPointWIN10Version(DWORD TreadId)
{
	MyTrace(L"%d TreadId", TreadId);
	HANDLE hMainThread = OpenThread(THREAD_ALL_ACCESS, TRUE, TreadId);
	SuspendThread(hMainThread);
	
	CONTEXT ctx;
	ctx.ContextFlags = CONTEXT_ALL;
	GetThreadContext(hMainThread, &ctx);
	ctx.Dr7 = (DWORD)0x405; // 启用Dr0
	ctx.Dr0 = g_dwBreakpoint; // 设置硬件断点	
	ctx.Dr1 = 0; // 设置硬件断点	
	ctx.Dr2 = 0; // 设置硬件断点	
	ctx.Dr3 = 0; // 设置硬件断点	
	bool status = SetThreadContext(hMainThread, &ctx);
	MyTrace(L"%d hMainThread %d", DWORD64(hMainThread), status);
	ResumeThread(hMainThread);
	return 0;
}
DWORD WINAPI SetHardwareBreakPointoffWIN10Version(DWORD TreadId)
{
	MyTrace(L"%d TreadId", TreadId);
	HANDLE hMainThread = OpenThread(THREAD_ALL_ACCESS, TRUE, TreadId);

	SuspendThread(hMainThread);
	CONTEXT ctx;
	ctx.ContextFlags = CONTEXT_ALL;
	GetThreadContext(hMainThread, &ctx);
	ctx.Dr7 = (DWORD)0x0; // 启用Dr0
	ctx.Dr0 = 0; // 设置硬件断点	
	ctx.Dr1 = 0; // 设置硬件断点	
	ctx.Dr2 = 0; // 设置硬件断点	
	ctx.Dr3 = 0; // 设置硬件断点	
	//ctx.Dr1 = g_dwBreakpoint2; // 设置硬件断点	
	bool status = SetThreadContext(hMainThread, &ctx);
	MyTrace(L"%d hMainThread %d", DWORD64(hMainThread), status);
	ResumeThread(hMainThread);
	return 0;
}


// 入口函数
//BOOL WINAPI DllMain(HMODULE hModule, DWORD dwReason, PVOID pvReserved)
//{
//	if (dwReason == DLL_PROCESS_ATTACH)
//	{
//		DisableThreadLibraryCalls(hModule);
//		AddVectoredExceptionHandler(1, (PVECTORED_EXCEPTION_HANDLER)ExceptionHandler);
//		//SetHardwareBreakPoint(); // 关键跳，希望跳过这条指令
//		CreateThread(0, 0, SetHardwareBreakPointWIN10Version, (LPVOID)GetCurrentThreadId(), 0, 0);
//		return Load();
//	}
//	else if (dwReason == DLL_PROCESS_DETACH)
//	{
//		Free();
//	}
//
//	return TRUE;
//}

//
//LONG WINAPI ExceptionFilter(PEXCEPTION_POINTERS ExceptionInfo)
//{
//	if (ExceptionInfo->ExceptionRecord->ExceptionCode == EXCEPTION_SINGLE_STEP)
//	{
//		INT64 GetEngineShowFlagsAddressD = 游戏模块 + 基址_鼠标_鼠标写入地址;
//		if ((PVOID)GetEngineShowFlagsAddressD == ExceptionInfo->ExceptionRecord->ExceptionAddress)
//		{
//			ExceptionInfo->ContextRecord->Rip += 6;
//			////*(PDWORD)(ExceptionInfo->ContextRecord->R13 + 0x68 + 0x4) = 0xFFF87FFF;
//
//			////恢复
//			//CHAR PatchData[] = {
//			//		0x49, 0x8B, 0x4D, 0x68
//			//};
//			//写内存字节集((HANDLE)-1, (LPVOID)(GetEngineShowFlagsAddressD), LPVOID(&PatchData), sizeof(PatchData));
//			////if (!VirtualCopyMemory((PVOID)GetEngineShowFlagsAddressD, PatchData, sizeof(PatchData)))
//			////{
//			////	//_MSGBOX_(xorstr_("写数据失败, 退出"));
//			////	return EXCEPTION_CONTINUE_SEARCH;
//			////}
//
//			return EXCEPTION_CONTINUE_EXECUTION;
//		}
//		else
//		{
//			return EXCEPTION_CONTINUE_EXECUTION;
//		}
//	}
//	return EXCEPTION_CONTINUE_EXECUTION;
//}
//
