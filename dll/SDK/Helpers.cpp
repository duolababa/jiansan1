#include "../pch.h"
#include "Helpers.h"

/*
==============================================================================================

开源声明： 
，本着一起提高网络安全水平研究了一下UE4游戏的安全，把现有的研究成果和大家分享一下。本人申明，本套源码仅用于开源学习，禁止将本套源码用作任何商业用途和非法用途，如果你使用本套源码，代表已经同意了此声明，所造成的任何后果和损失，由使用者自行承担。

技术交流QQ群782282356
==============================================================================================

*/
//using namespace std;
HWND m_hWnd;
// 开始HOOK函数  开源群782282356 
void Helpers::HookFunction(PVOID* oFunction, PVOID pDetour)
{
	//开源群782282356
	DetourTransactionBegin();
	DetourUpdateThread(GetCurrentThread());
	DetourAttach(oFunction, pDetour);
	DetourTransactionCommit();
	//开源群782282356
}

// 结束HOOK函数  开源群782282356
void Helpers::UnHookFunction(PVOID* oFunction, PVOID pDetour)
{
	//开源群782282356
	DetourTransactionBegin();
	DetourUpdateThread(GetCurrentThread());
	DetourDetach(oFunction, pDetour);
	DetourTransactionCommit();
	//开源群782282356
}
/*
==============================================================================================

开源声明： 
，本着一起提高网络安全水平研究了一下UE4游戏的安全，把现有的研究成果和大家分享一下。本人申明，本套源码仅用于开源学习，禁止将本套源码用作任何商业用途和非法用途，如果你使用本套源码，代表已经同意了此声明，所造成的任何后果和损失，由使用者自行承担。

==============================================================================================

*/

BOOL Helpers::EnumWindowsCallback(HWND hWnd, LPARAM lParam)
{
	DWORD wndPid;
	GetWindowThreadProcessId(hWnd, &wndPid);
	if (wndPid != (DWORD)lParam) return TRUE;

	m_hWnd = hWnd;
	return FALSE;
}
/*
==============================================================================================

开源声明： 
，本着一起提高网络安全水平研究了一下UE4游戏的安全，把现有的研究成果和大家分享一下。本人申明，本套源码仅用于开源学习，禁止将本套源码用作任何商业用途和非法用途，如果你使用本套源码，代表已经同意了此声明，所造成的任何后果和损失，由使用者自行承担。

技术交流QQ群782282356
==============================================================================================

*/
// 获取当前所在窗口的句柄
HWND Helpers::GetCurrentWindowHandle()
{
	m_hWnd = NULL;
	EnumWindows(EnumWindowsCallback, GetCurrentProcessID());
	return m_hWnd;
}
//开源群782282356
DWORD Helpers::GetCurrentProcessID(){return GetCurrentProcessId();}



