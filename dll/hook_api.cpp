#include "pch.h"
#include "hook_api.h"
#include "tlhelp32.h";
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
	if (pExceptionInfo->ExceptionRecord->ExceptionCode == EXCEPTION_SINGLE_STEP)
	{
		int xxx =1;
		if ((DWORD64)pExceptionInfo->ExceptionRecord->ExceptionAddress == g_dwBreakpoint && xxx==1)
		{
			INT64 rdi = pExceptionInfo->ContextRecord->Rdi;

			INT64 ���ݵ�ַ = rdi;
				/*CStringA a = (char*)���ݵ�ַ;
				CString b = CStringW(a);*/
			char tmp[MAX_PATH];
			strcpy_s(tmp, (char*)���ݵ�ַ);
			_strlwr_s(tmp);
			DWORD rax1 = 0;
		//	DbgPrintf_Mine("  %s ", (char*)���ݵ�ַ);
				
			if (strstr(tmp, "data\\source\\other") == tmp || strstr(tmp, "data/source/other") == tmp)
			{
				if (strstr(tmp, ".dds"))
				{
					rax1 = 1;
				}
			}

			if (strstr(tmp, "ui\\image\\") == tmp || strstr(tmp, "ui/image/") == tmp) //�Ż���ʾ�����ͷ
			{
				if (strstr(tmp, "uicommon\\commonpanel4"))
				{
					rax1 = 1;
				}
				//dbgPrint("myOpenFile=%s", tmp);
			}
			if (strstr(tmp, "data\\source\\maps_source") == tmp || strstr(tmp, "data/source/maps_source") == tmp)
			{
				if (/*strstr(tmp, ".anitexture") == NULL &&*/ strstr(tmp, "ˮ����") == NULL && (strstr(tmp, "����") || strstr(tmp, "��ľ") || strstr(tmp, "Զ��") || strstr(tmp, "foliage") || strstr(tmp, "С���") || strstr(tmp, "ˮ�����")))
				{
					rax1 = 1;
				}
				if (/*strstr(tmp, ".anitexture") == NULL &&*/ strstr(tmp, "ˮ����") == NULL && strstr(tmp, ".dds"))
				{
					rax1 = 1;
				}
			}
			if (strstr(tmp, "data\\source\\maps\\") == tmp || strstr(tmp, "data/source/maps/") == tmp)  //ɾ����ͼ�� ȫ��dds��Դ
			{
				if (strstr(tmp, ".dds") && strstr(tmp, "minimap") == NULL) //��ͼ����С��ͼ��Ϣ
				{
					rax1 = 1;
				}
			}
			
			if (strstr(tmp, "data\\source\\npc_source") == tmp || strstr(tmp, "data/source/npc_source") == tmp) //ȥ��NPC����
			{
				if (strstr(tmp, "����") || strstr(tmp, "belt") || strstr(tmp, "hand") || strstr(tmp, "head"))
				{
			
					rax1 = 1;
				}
				
			}



			if (
				strstr(tmp, "minimap") == NULL &&																															// ����С��ͼ
				strstr(tmp, "ui\\image\\icon\\") == NULL &&																													// ����ͼ�꣨BUFF�����ܡ���Ʒ�ȵȣ�
				(

					//(strstr(tmp, "data\\source\\maps_source") == tmp && strstr(tmp, ".anitexture") == NULL && strstr(tmp, "ˮ����") == NULL && strstr(tmp, ".dds")) ||	// ȥ����ͼ��Դ���������ֻ����𴴽�����ʧ�ܵ��ļ���
					//(strstr(tmp, "data/source/maps_source") == tmp && strstr(tmp, ".anitexture") == NULL && strstr(tmp, "ˮ����") == NULL && strstr(tmp, ".dds")) ||		// ע�͵�����ȥ��Ϊ����Ż���ע������Ϊ�ض��Ż�
					strstr(tmp, "data\\source\\item") == tmp ||																												// ȥ����Ʒ
					strstr(tmp, "data/source/item") == tmp ||
					strstr(tmp, "data\\sound") == tmp ||																													// ȥ������
					strstr(tmp, "data/sound") == tmp ||
					strstr(tmp, "data\\movie") == tmp ||																													// ȥ����Ƶ
					strstr(tmp, "data/movie") == tmp ||
					(strstr(tmp, ".tga") && strstr(tmp, "data\\material\\texture\\rgbmask.tga") == NULL) ||																	// ȥ��TGAͼƬ������һ��������DirectX����ʧ�ܵ��ļ���
					strstr(tmp, ".png") // ȥ��PNGͼƬ

					)
				)
			{
				rax1 = 1;
			}
			else
			{
			
					if (strstr(tmp, "ui\\image\\") == tmp ||																													// ȥ��UI
						strstr(tmp, "ui/image/") == tmp)
					{
						rax1 = 1;
					}
					if (strstr(tmp, "data\\source\\doodad") == tmp ||																											// ȥ��������Ʒ
						strstr(tmp, "data/source/doodad") == tmp)
					{
						rax1 = 1;
					}
			




			
			}





			if (rax1 == 1)
			{
			//	DbgPrintf_Mine("  �Ż��� %s ", (char*)���ݵ�ַ);
				pExceptionInfo->ContextRecord->Rax = 0x0;
			}
			else
			{
				pExceptionInfo->ContextRecord->Rax = *(QWORD*)(pExceptionInfo->ContextRecord->Rbp + 0x20);
			}


			//pExceptionInfo->ContextRecord->Rax = *(QWORD*)(pExceptionInfo->ContextRecord->Rbp - 0x30);

			pExceptionInfo->ContextRecord->Rip += 0x4;

			return EXCEPTION_CONTINUE_EXECUTION;

		}
		else
		{
		if ((DWORD64)pExceptionInfo->ExceptionRecord->ExceptionAddress == g_dwBreakpoint)
		{
			INT64 R8��ַ = pExceptionInfo->ContextRecord->R8;
			INT64 r9��ַ = pExceptionInfo->ContextRecord->R9;
			INT64 rdx��ַ = pExceptionInfo->ContextRecord->Rdx;
			INT64 rsp��ַ = pExceptionInfo->ContextRecord->Rsp;

			INT ���� = R_DW(r9��ַ + 0x8);
			INT64 ���ݵ�ַ = R_QW(r9��ַ);
			CStringA a = (char*)���ݵ�ַ;
			CString b = CStringW(a);
			if (���� > 1)
			{
					if (b.Find(L"g_tTableFile") == -1 && b.Find(L"\"[����]\"") == -1 && b.Find(L"\"[�Ŷ���ļ") == -1 && b.Find(L"this.szName=\"[��Ӫ") == -1)
					{
						CLog::WriteMsg((LPCTSTR)b);


						if (���� < 8000)
						{

							MyTrace(L" ���� %d  %s ", ����, b);
						}


					}

				//CLog::WriteMsg((LPCTSTR)b);


			/*	if (���� < 8000)
				{

					MyTrace(L" ���� %d  %s ", ����, b);
				}*/
			}
			//}
			//$ ==>             | 4C:894424 38 | mov     qword ptr ss : [rsp + 38] , r8 |

		/*	*(QWORD*)(pExceptionInfo->ContextRecord->Rsp + 0x38) = pExceptionInfo->ContextRecord->R8;
			pExceptionInfo->ContextRecord->Rip += 0x5;

			return EXCEPTION_CONTINUE_EXECUTION;*/

			//00007FF91BDA8283  | 49 89 5B 08         | mov qword ptr ds:[r11+8],rbx              |
			*(QWORD*)(pExceptionInfo->ContextRecord->R11 + 0x8) = pExceptionInfo->ContextRecord->Rbx;
			pExceptionInfo->ContextRecord->Rip += 0x4;

			//00007FFC226351D0  | 48 89 5C 24 08     | mov qword ptr ss:[rsp+8],rbx             |
	/*		*(QWORD*)(pExceptionInfo->ContextRecord->Rsp+0x8) =pExceptionInfo->ContextRecord->Rbx;
			pExceptionInfo->ContextRecord->Rip += 0x5;*/

			return EXCEPTION_CONTINUE_EXECUTION;
		}

	}



		}


 

	


	//if (pExceptionInfo->ExceptionRecord->ExceptionCode == STATUS_BREAKPOINT)
	//{
	//	if ((DWORD64)pExceptionInfo->ExceptionRecord->ExceptionAddress == g_dwBreakpoint)
	//	{
	//		pExceptionInfo->ContextRecord->Rip += 0x6;
	//		return EXCEPTION_CONTINUE_EXECUTION;
	//	}
	//}
	
	return EXCEPTION_CONTINUE_SEARCH;
}

// ����Ӳ���ϵ�WIN10�汾���������߳�->����Ӳ���ϵ�->�ָ����߳�
DWORD WINAPI SetHardwareBreakPointWIN10Version(DWORD TreadId)
{
	//MyTrace(L"%d TreadId", TreadId);
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
	//MyTrace(L"%d hMainThread %d", DWORD64(hMainThread), status);
	ResumeThread(hMainThread);
	return 0;
}
DWORD WINAPI SetHardwareBreakPointoffWIN10Version(DWORD TreadId)
{
	//MyTrace(L"%d TreadId", TreadId);
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
	//MyTrace(L"%d hMainThread %d", DWORD64(hMainThread), status);
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
