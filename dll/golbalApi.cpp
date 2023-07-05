#include "pch.h"

#pragma comment(lib,"Shlwapi.lib")

//获取当前句柄
HWND  GetCurrentHwnd(const char* 游戏窗口类名)
{
	//指定父窗口句柄 可以用FindWindow或者FindWindowEx来获取	 
	HWND 父窗口句柄 = HWND_DESKTOP;

	//获取父窗口下 第一个子窗口句柄
	HWND hNext = FindWindowExA(父窗口句柄, NULL, 游戏窗口类名, NULL);
	while (hNext) //
	{
		DWORD pid = 0;
		GetWindowThreadProcessId(hNext, &pid);
		DWORD 当前PID = GetCurrentProcessId();
		if (pid == 当前PID)
		{
			return hNext;
		}
		//查找下一个 子窗口句柄
		hNext = FindWindowExA(父窗口句柄, hNext, 游戏窗口类名, NULL);
		//printf("hNext=%p\r\n",hNext); //打印出窗口信息
	}//while
	return NULL;
}



HWND  GetCurrentHwnd()
{
	//多开时可以用 FindWindowEx代替
	static HWND h = NULL;
	if (h == NULL)
	{
		h = GetCurrentHwnd(类名);
	}

	return h;
}

HWND  GetGameImeHwnd(HWND hGame)
{
	if (!hGame || !IsWindow(hGame)) return NULL;

	DWORD pid = 0;
	DWORD tid = GetWindowThreadProcessId(hGame, &pid);
	DWORD tid_ime = 0;// 
	const char ImeCaption[] = "Default IME";
	HWND hIme = FindWindowExA(HWND_DESKTOP, NULL, "IME", ImeCaption);
	while (hIme)
	{
		tid_ime = GetWindowThreadProcessId(hIme, &pid);
		if (tid_ime == tid)
		{
			return hIme;
		}
		hIme = FindWindowExA(HWND_DESKTOP, hIme, "IME", ImeCaption);
	}

	return NULL;
};

DWORD GetGameThreadId()
{
	HWND  h = GetCurrentHwnd();
	DWORD tid, pid;
	tid = GetWindowThreadProcessId(h, &pid);
	return tid;
}
//获取当前进程窗口相关PID
DWORD  GetGameProcesssID()
{

	DWORD pid = 0;
	HWND h = GetCurrentHwnd();
	if (!h) return NULL;

	GetWindowThreadProcessId(h, &pid);

	return pid;
}


//判断当前进程是否是游戏进程
BOOL IsGameProcess()
{
	DWORD 游戏PID = GetGameProcesssID();
	DWORD 当前PID = GetCurrentProcessId();
	if (游戏PID == 当前PID)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}
//获取当前进程名字
const TCHAR* GetCurrentProcessPathName(IN OUT TCHAR* szCurExeFilePathName)
{

	GetModuleFileName(NULL, szCurExeFilePathName, MAX_PATH);

	return szCurExeFilePathName;
}

//获取当前进程名字
const TCHAR* GetCurrentProcessName(IN OUT TCHAR* 当前进程名)
{
	GetModuleFileName(NULL, 当前进程名, MAX_PATH);
	PathStripPath(当前进程名); //只取进程名字
	return 当前进程名;
}


