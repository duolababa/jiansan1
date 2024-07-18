#include "pch.h"
#include "DbgPrint.h"
///////////////////////////////////////////////////////////////////////////////////////////////////////////
#pragma warning(push)
#pragma warning(disable:4996)//使用sprintf strcat等不安全的函数并忽略警告
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
	char szbuffFormat_Game[0x1008] = "输出:";
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

VOID __cdecl MyOutputDebugStringA(LPCSTR format, ...)//自定义调试输出 ansi版
{
	va_list vlArgs;
	//这里注意这个函数：GlobalAlloc，第一个参数GPTR的意思在堆上是分配固定内存并清零
	char    *strBuffer = (char*)GlobalAlloc(GPTR, 4096);
	char    *strText = (char*)GlobalAlloc(GPTR, 4096);

	//折腾可变参数
	va_start(vlArgs, format);
	_vsnprintf(strBuffer, 4096 - 1, format, vlArgs);
	va_end(vlArgs);
	strcat(strBuffer, "\r\n");
	wsprintfA(strText, "输出： %s", strBuffer);
	//输出调试字符串
	OutputDebugStringA(strText);
	//记得释放掉资源
	GlobalFree(strBuffer);
	GlobalFree(strText);
	return;
}

VOID __cdecl MyOutputDebugStringW(LPCWSTR format, ...)//自定义调试输出 unicode版
{
	va_list vlArgs;
	//这里注意这个函数：GlobalAlloc，第一个参数GPTR的意思在堆上是分配固定内存并清零
	WCHAR* wcsBuffer = (WCHAR *)GlobalAlloc(GPTR, 4096);
	WCHAR* wcsText = (WCHAR *)GlobalAlloc(GPTR, 4096);

	//折腾可变参数
	va_start(vlArgs, format);
	_vsnwprintf(wcsBuffer, 4096 - 1, format, vlArgs);
	va_end(vlArgs);
	wcscat(wcsBuffer, L"\r\n");
	wsprintfW(wcsText, L"输出： %s", wcsBuffer);
	//输出调试字符串
	OutputDebugStringW(wcsText);
	//记得释放掉资源
	GlobalFree(wcsBuffer);
	GlobalFree(wcsText);
	return;
}
#pragma warning(pop)