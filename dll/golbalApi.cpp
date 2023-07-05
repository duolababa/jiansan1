#include "pch.h"

#pragma comment(lib,"Shlwapi.lib")

//��ȡ��ǰ���
HWND  GetCurrentHwnd(const char* ��Ϸ��������)
{
	//ָ�������ھ�� ������FindWindow����FindWindowEx����ȡ	 
	HWND �����ھ�� = HWND_DESKTOP;

	//��ȡ�������� ��һ���Ӵ��ھ��
	HWND hNext = FindWindowExA(�����ھ��, NULL, ��Ϸ��������, NULL);
	while (hNext) //
	{
		DWORD pid = 0;
		GetWindowThreadProcessId(hNext, &pid);
		DWORD ��ǰPID = GetCurrentProcessId();
		if (pid == ��ǰPID)
		{
			return hNext;
		}
		//������һ�� �Ӵ��ھ��
		hNext = FindWindowExA(�����ھ��, hNext, ��Ϸ��������, NULL);
		//printf("hNext=%p\r\n",hNext); //��ӡ��������Ϣ
	}//while
	return NULL;
}



HWND  GetCurrentHwnd()
{
	//�࿪ʱ������ FindWindowEx����
	static HWND h = NULL;
	if (h == NULL)
	{
		h = GetCurrentHwnd(����);
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
//��ȡ��ǰ���̴������PID
DWORD  GetGameProcesssID()
{

	DWORD pid = 0;
	HWND h = GetCurrentHwnd();
	if (!h) return NULL;

	GetWindowThreadProcessId(h, &pid);

	return pid;
}


//�жϵ�ǰ�����Ƿ�����Ϸ����
BOOL IsGameProcess()
{
	DWORD ��ϷPID = GetGameProcesssID();
	DWORD ��ǰPID = GetCurrentProcessId();
	if (��ϷPID == ��ǰPID)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}
//��ȡ��ǰ��������
const TCHAR* GetCurrentProcessPathName(IN OUT TCHAR* szCurExeFilePathName)
{

	GetModuleFileName(NULL, szCurExeFilePathName, MAX_PATH);

	return szCurExeFilePathName;
}

//��ȡ��ǰ��������
const TCHAR* GetCurrentProcessName(IN OUT TCHAR* ��ǰ������)
{
	GetModuleFileName(NULL, ��ǰ������, MAX_PATH);
	PathStripPath(��ǰ������); //ֻȡ��������
	return ��ǰ������;
}


