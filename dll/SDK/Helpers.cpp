#include "../pch.h"
#include "Helpers.h"

/*
==============================================================================================

��Դ������ 
������һ��������簲ȫˮƽ�о���һ��UE4��Ϸ�İ�ȫ�������е��о��ɹ��ʹ�ҷ���һ�¡���������������Դ������ڿ�Դѧϰ����ֹ������Դ�������κ���ҵ��;�ͷǷ���;�������ʹ�ñ���Դ�룬�����Ѿ�ͬ���˴�����������ɵ��κκ������ʧ����ʹ�������ге���

��������QQȺ782282356
==============================================================================================

*/
//using namespace std;
HWND m_hWnd;
// ��ʼHOOK����  ��ԴȺ782282356 
void Helpers::HookFunction(PVOID* oFunction, PVOID pDetour)
{
	//��ԴȺ782282356
	DetourTransactionBegin();
	DetourUpdateThread(GetCurrentThread());
	DetourAttach(oFunction, pDetour);
	DetourTransactionCommit();
	//��ԴȺ782282356
}

// ����HOOK����  ��ԴȺ782282356
void Helpers::UnHookFunction(PVOID* oFunction, PVOID pDetour)
{
	//��ԴȺ782282356
	DetourTransactionBegin();
	DetourUpdateThread(GetCurrentThread());
	DetourDetach(oFunction, pDetour);
	DetourTransactionCommit();
	//��ԴȺ782282356
}
/*
==============================================================================================

��Դ������ 
������һ��������簲ȫˮƽ�о���һ��UE4��Ϸ�İ�ȫ�������е��о��ɹ��ʹ�ҷ���һ�¡���������������Դ������ڿ�Դѧϰ����ֹ������Դ�������κ���ҵ��;�ͷǷ���;�������ʹ�ñ���Դ�룬�����Ѿ�ͬ���˴�����������ɵ��κκ������ʧ����ʹ�������ге���

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

��Դ������ 
������һ��������簲ȫˮƽ�о���һ��UE4��Ϸ�İ�ȫ�������е��о��ɹ��ʹ�ҷ���һ�¡���������������Դ������ڿ�Դѧϰ����ֹ������Դ�������κ���ҵ��;�ͷǷ���;�������ʹ�ñ���Դ�룬�����Ѿ�ͬ���˴�����������ɵ��κκ������ʧ����ʹ�������ге���

��������QQȺ782282356
==============================================================================================

*/
// ��ȡ��ǰ���ڴ��ڵľ��
HWND Helpers::GetCurrentWindowHandle()
{
	m_hWnd = NULL;
	EnumWindows(EnumWindowsCallback, GetCurrentProcessID());
	return m_hWnd;
}
//��ԴȺ782282356
DWORD Helpers::GetCurrentProcessID(){return GetCurrentProcessId();}



