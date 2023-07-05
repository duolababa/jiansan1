#include "pch.h"
#include "hook_api.h"

//BOOL WINAPI GetCursorPos(_Out_ LPPOINT lpPoint);
typedef BOOL(WINAPI* GetCursorPos_)(
	_Out_ LPPOINT lpPoint);

GetCursorPos_ OGetCursorPos = (GetCursorPos_)GetProcAddress(GetModuleHandleA("user32.dll"), "GetCursorPos");
RECT R1;
BOOL WINAPI MyGetCursorPos(_Out_ LPPOINT lpPoint)
{
	if (������꿪�� && g_hWnd)
	{
		GetWindowRect(g_hWnd, &R1);
		lpPoint->x = hook�������.x + R1.left;
		lpPoint->y = hook�������.y + R1.top;
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
 // �ؼ�ָ�ϣ����������ָ��

// ����WIN7Ӳ���ϵ㺯��
void SetHardwareBreakPoint()
{
	CONTEXT ctx;
	ctx.ContextFlags = CONTEXT_ALL;
	GetThreadContext(GetCurrentThread(), &ctx);
	ctx.Dr7 = (DWORD)0x1; // ����Dr0
	ctx.Dr0 = g_dwBreakpoint; // ����Ӳ���ϵ�	
	SetThreadContext(GetCurrentThread(), &ctx);
}

// �쳣������
DWORD NTAPI ExceptionHandler(PEXCEPTION_POINTERS pExceptionInfo)
{
	//MyTrace(L"0x%I64X | 0x%I64X", DWORD64(pExceptionInfo->ExceptionRecord->ExceptionAddress), g_dwBreakpoint);
	//if (pExceptionInfo->ExceptionRecord->ExceptionCode == EXCEPTION_SINGLE_STEP)
	//{
	//	if ((DWORD64)pExceptionInfo->ExceptionRecord->ExceptionAddress == g_dwBreakpoint)
	//	{
	//		//SetWindowTextW(g_hWnd, L"Mir4G");
	//		/*if (������꿪�� == true)
	//		{*/
	//		/*pExceptionInfo->ContextRecord->Dr7 = (DWORD)0x1;
	//		pExceptionInfo->ContextRecord->Dr0 = g_dwBreakpoint;*/
	//		pExceptionInfo->ContextRecord->Rax = 0;
	//		pExceptionInfo->ContextRecord->Rip += 5;
	//		//}

	//		// �Ѿ��������쳣������Ҫ������һ���쳣������������쳣
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
	//	//::MessageBox(NULL, L"����EXCEPTION_ACCESS_VIOLATION �쳣" + �������ı�((DWORD64)pExceptionInfo->ExceptionRecord->ExceptionAddress) , L"", MB_OK);
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

	//	// �Ѿ��������쳣������Ҫ������һ���쳣������������쳣
	//	return EXCEPTION_CONTINUE_EXECUTION;
	//}
	return EXCEPTION_CONTINUE_SEARCH;
}

// ����Ӳ���ϵ�WIN10�汾���������߳�->����Ӳ���ϵ�->�ָ����߳�
DWORD WINAPI SetHardwareBreakPointWIN10Version(DWORD TreadId)
{
	MyTrace(L"%d TreadId", TreadId);
	HANDLE hMainThread = OpenThread(THREAD_ALL_ACCESS, TRUE, TreadId);
	SuspendThread(hMainThread);
	
	CONTEXT ctx;
	ctx.ContextFlags = CONTEXT_ALL;
	GetThreadContext(hMainThread, &ctx);
	ctx.Dr7 = (DWORD)0x405; // ����Dr0
	ctx.Dr0 = g_dwBreakpoint; // ����Ӳ���ϵ�	
	ctx.Dr1 = 0; // ����Ӳ���ϵ�	
	ctx.Dr2 = 0; // ����Ӳ���ϵ�	
	ctx.Dr3 = 0; // ����Ӳ���ϵ�	
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
	ctx.Dr7 = (DWORD)0x0; // ����Dr0
	ctx.Dr0 = 0; // ����Ӳ���ϵ�	
	ctx.Dr1 = 0; // ����Ӳ���ϵ�	
	ctx.Dr2 = 0; // ����Ӳ���ϵ�	
	ctx.Dr3 = 0; // ����Ӳ���ϵ�	
	//ctx.Dr1 = g_dwBreakpoint2; // ����Ӳ���ϵ�	
	bool status = SetThreadContext(hMainThread, &ctx);
	MyTrace(L"%d hMainThread %d", DWORD64(hMainThread), status);
	ResumeThread(hMainThread);
	return 0;
}


// ��ں���
//BOOL WINAPI DllMain(HMODULE hModule, DWORD dwReason, PVOID pvReserved)
//{
//	if (dwReason == DLL_PROCESS_ATTACH)
//	{
//		DisableThreadLibraryCalls(hModule);
//		AddVectoredExceptionHandler(1, (PVECTORED_EXCEPTION_HANDLER)ExceptionHandler);
//		//SetHardwareBreakPoint(); // �ؼ�����ϣ����������ָ��
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
//		INT64 GetEngineShowFlagsAddressD = ��Ϸģ�� + ��ַ_���_���д���ַ;
//		if ((PVOID)GetEngineShowFlagsAddressD == ExceptionInfo->ExceptionRecord->ExceptionAddress)
//		{
//			ExceptionInfo->ContextRecord->Rip += 6;
//			////*(PDWORD)(ExceptionInfo->ContextRecord->R13 + 0x68 + 0x4) = 0xFFF87FFF;
//
//			////�ָ�
//			//CHAR PatchData[] = {
//			//		0x49, 0x8B, 0x4D, 0x68
//			//};
//			//д�ڴ��ֽڼ�((HANDLE)-1, (LPVOID)(GetEngineShowFlagsAddressD), LPVOID(&PatchData), sizeof(PatchData));
//			////if (!VirtualCopyMemory((PVOID)GetEngineShowFlagsAddressD, PatchData, sizeof(PatchData)))
//			////{
//			////	//_MSGBOX_(xorstr_("д����ʧ��, �˳�"));
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
