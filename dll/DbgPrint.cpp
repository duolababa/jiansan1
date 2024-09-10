#include "pch.h"
#include "DbgPrint.h"
///////////////////////////////////////////////////////////////////////////////////////////////////////////
#pragma warning(push)
#pragma warning(disable:4996)//ʹ��sprintf strcat�Ȳ���ȫ�ĺ��������Ծ���
///////////////////////////////////////////////////////////////////////////////////////////////////////////
void __cdecl MyTrace(TCHAR* lpszFormat, ...)
{
	int nBuf;
	TCHAR szBuffer[0x9000];
	memset(szBuffer, 0, 0x9000 * sizeof(TCHAR));
	va_list args;
	va_start(args, lpszFormat);
	nBuf = _vsntprintf(szBuffer, sizeof(szBuffer), lpszFormat, args);
	OutputDebugString(szBuffer);
	va_end(args);

}
void DbgPrintf_Mine(char*pszFormat, ...)
{
	USES_CONVERSION;
	va_list argList;
	char szbuffFormat[0x9000];
	char szbuffFormat_Game[0x1008] = "���:";
	va_start(argList, pszFormat);
	vsprintf_s(szbuffFormat, pszFormat, argList);
	strcat_s(szbuffFormat_Game, szbuffFormat);
	OutputDebugStringA(szbuffFormat_Game);
	//CLog::WriteMsg(A2W(szbuffFormat_Game));
	va_end(argList);
}

void My_DbgString(LPCTSTR lpszFormat, ...)
{
	va_list   args;
	int       nBuf;
	TCHAR     szBuffer[512];
	va_start(args, lpszFormat);
	nBuf = _vsntprintf(szBuffer, sizeof(szBuffer) * sizeof(TCHAR), lpszFormat, args);
	assert(nBuf > 0);
	OutputDebugString(szBuffer);
	va_end(args);
}

VOID __cdecl MyOutputDebugStringA(LPCSTR format, ...)//�Զ��������� ansi��
{
	va_list vlArgs;
	//����ע�����������GlobalAlloc����һ������GPTR����˼�ڶ����Ƿ���̶��ڴ沢����
	char    *strBuffer = (char*)GlobalAlloc(GPTR, 4096);
	char    *strText = (char*)GlobalAlloc(GPTR, 4096);

	//���ڿɱ����
	va_start(vlArgs, format);
	_vsnprintf(strBuffer, 4096 - 1, format, vlArgs);
	va_end(vlArgs);
	strcat(strBuffer, "\r\n");
	wsprintfA(strText, "����� %s", strBuffer);
	//��������ַ���
	OutputDebugStringA(strText);
	//�ǵ��ͷŵ���Դ
	GlobalFree(strBuffer);
	GlobalFree(strText);
	return;
}

VOID __cdecl MyOutputDebugStringW(LPCWSTR format, ...)//�Զ��������� unicode��
{
	va_list vlArgs;
	//����ע�����������GlobalAlloc����һ������GPTR����˼�ڶ����Ƿ���̶��ڴ沢����
	WCHAR* wcsBuffer = (WCHAR *)GlobalAlloc(GPTR, 4096);
	WCHAR* wcsText = (WCHAR *)GlobalAlloc(GPTR, 4096);

	//���ڿɱ����
	va_start(vlArgs, format);
	_vsnwprintf(wcsBuffer, 4096 - 1, format, vlArgs);
	va_end(vlArgs);
	wcscat(wcsBuffer, L"\r\n");
	wsprintfW(wcsText, L"����� %s", wcsBuffer);
	//��������ַ���
	OutputDebugStringW(wcsText);
	//�ǵ��ͷŵ���Դ
	GlobalFree(wcsBuffer);
	GlobalFree(wcsText);
	return;
}
#pragma warning(pop)