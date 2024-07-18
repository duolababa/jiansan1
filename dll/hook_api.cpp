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
	if (pExceptionInfo->ExceptionRecord->ExceptionCode == EXCEPTION_SINGLE_STEP)
	{
		int xxx =1;
		if ((DWORD64)pExceptionInfo->ExceptionRecord->ExceptionAddress == g_dwBreakpoint && xxx==1)
		{
			INT64 rdi = pExceptionInfo->ContextRecord->Rdi;

			INT64 内容地址 = rdi;
				/*CStringA a = (char*)内容地址;
				CString b = CStringW(a);*/
			char tmp[MAX_PATH];
			strcpy_s(tmp, (char*)内容地址);
			_strlwr_s(tmp);
			DWORD rax1 = 0;
		//	DbgPrintf_Mine("  %s ", (char*)内容地址);
				
			if (strstr(tmp, "data\\source\\other") == tmp || strstr(tmp, "data/source/other") == tmp)
			{
				if (strstr(tmp, ".dds"))
				{
					rax1 = 1;
				}
			}

			if (strstr(tmp, "ui\\image\\") == tmp || strstr(tmp, "ui/image/") == tmp) //优化显示任务箭头
			{
				if (strstr(tmp, "uicommon\\commonpanel4"))
				{
					rax1 = 1;
				}
				//dbgPrint("myOpenFile=%s", tmp);
			}
			if (strstr(tmp, "data\\source\\maps_source") == tmp || strstr(tmp, "data/source/maps_source") == tmp)
			{
				if (/*strstr(tmp, ".anitexture") == NULL &&*/ strstr(tmp, "水波纹") == NULL && (strstr(tmp, "花草") || strstr(tmp, "灌木") || strstr(tmp, "远景") || strstr(tmp, "foliage") || strstr(tmp, "小物件") || strstr(tmp, "水上物件")))
				{
					rax1 = 1;
				}
				if (/*strstr(tmp, ".anitexture") == NULL &&*/ strstr(tmp, "水波纹") == NULL && strstr(tmp, ".dds"))
				{
					rax1 = 1;
				}
			}
			if (strstr(tmp, "data\\source\\maps\\") == tmp || strstr(tmp, "data/source/maps/") == tmp)  //删掉地图上 全部dds资源
			{
				if (strstr(tmp, ".dds") && strstr(tmp, "minimap") == NULL) //地图保留小地图信息
				{
					rax1 = 1;
				}
			}
			
			if (strstr(tmp, "data\\source\\npc_source") == tmp || strstr(tmp, "data/source/npc_source") == tmp) //去掉NPC动作
			{
				if (strstr(tmp, "动作") || strstr(tmp, "belt") || strstr(tmp, "hand") || strstr(tmp, "head"))
				{
			
					rax1 = 1;
				}
				
			}



			if (
				strstr(tmp, "minimap") == NULL &&																															// 保留小地图
				strstr(tmp, "ui\\image\\icon\\") == NULL &&																													// 保留图标（BUFF、技能、物品等等）
				(

					//(strstr(tmp, "data\\source\\maps_source") == tmp && strstr(tmp, ".anitexture") == NULL && strstr(tmp, "水波纹") == NULL && strstr(tmp, ".dds")) ||	// 去掉地图资源（保留两种会引起创建场景失败的文件）
					//(strstr(tmp, "data/source/maps_source") == tmp && strstr(tmp, ".anitexture") == NULL && strstr(tmp, "水波纹") == NULL && strstr(tmp, ".dds")) ||		// 注释的内容去掉为轻度优化，注释上则为重度优化
					strstr(tmp, "data\\source\\item") == tmp ||																												// 去掉物品
					strstr(tmp, "data/source/item") == tmp ||
					strstr(tmp, "data\\sound") == tmp ||																													// 去掉声音
					strstr(tmp, "data/sound") == tmp ||
					strstr(tmp, "data\\movie") == tmp ||																													// 去掉视频
					strstr(tmp, "data/movie") == tmp ||
					(strstr(tmp, ".tga") && strstr(tmp, "data\\material\\texture\\rgbmask.tga") == NULL) ||																	// 去掉TGA图片（保留一个会引起DirectX创建失败的文件）
					strstr(tmp, ".png") // 去掉PNG图片

					)
				)
			{
				rax1 = 1;
			}
			else
			{
			
					if (strstr(tmp, "ui\\image\\") == tmp ||																													// 去掉UI
						strstr(tmp, "ui/image/") == tmp)
					{
						rax1 = 1;
					}
					if (strstr(tmp, "data\\source\\doodad") == tmp ||																											// 去掉地面物品
						strstr(tmp, "data/source/doodad") == tmp)
					{
						rax1 = 1;
					}
			




			
			}





			if (rax1 == 1)
			{
			//	DbgPrintf_Mine("  优化了 %s ", (char*)内容地址);
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
			INT64 R8地址 = pExceptionInfo->ContextRecord->R8;
			INT64 r9地址 = pExceptionInfo->ContextRecord->R9;
			INT64 rdx地址 = pExceptionInfo->ContextRecord->Rdx;
			INT64 rsp地址 = pExceptionInfo->ContextRecord->Rsp;

			INT 长度 = R_DW(r9地址 + 0x8);
			INT64 内容地址 = R_QW(r9地址);
			CStringA a = (char*)内容地址;
			CString b = CStringW(a);
			if (长度 > 1)
			{
					if (b.Find(L"g_tTableFile") == -1 && b.Find(L"\"[世界]\"") == -1 && b.Find(L"\"[团队招募") == -1 && b.Find(L"this.szName=\"[阵营") == -1)
					{
						CLog::WriteMsg((LPCTSTR)b);


						if (长度 < 8000)
						{

							MyTrace(L" 长度 %d  %s ", 长度, b);
						}


					}

				//CLog::WriteMsg((LPCTSTR)b);


			/*	if (长度 < 8000)
				{

					MyTrace(L" 长度 %d  %s ", 长度, b);
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

// 设置硬件断点WIN10版本：挂起主线程->设置硬件断点->恢复主线程
DWORD WINAPI SetHardwareBreakPointWIN10Version(DWORD TreadId)
{
	//MyTrace(L"%d TreadId", TreadId);
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
	ctx.Dr7 = (DWORD)0x0; // 启用Dr0
	ctx.Dr0 = 0; // 设置硬件断点	
	ctx.Dr1 = 0; // 设置硬件断点	
	ctx.Dr2 = 0; // 设置硬件断点	
	ctx.Dr3 = 0; // 设置硬件断点	
	//ctx.Dr1 = g_dwBreakpoint2; // 设置硬件断点	
	bool status = SetThreadContext(hMainThread, &ctx);
	//MyTrace(L"%d hMainThread %d", DWORD64(hMainThread), status);
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
