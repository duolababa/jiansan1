#pragma once

#ifndef CoreAPI
#ifndef _DLL_IMPORTS_
#define CoreAPI __declspec(dllexport)
#else
#define CoreAPI __declspec(dllimport)
#endif

#endif

void DbgPrintf_Mine(char*pszFormat, ...);
void My_DbgString(LPCTSTR lpszFormat, ...);
VOID __cdecl MyOutputDebugStringA(LPCSTR format, ...);
VOID __cdecl MyOutputDebugStringW(LPCWSTR format, ...);
void __cdecl MyTrace(TCHAR* lpszFormat, ...);
//�궨�� 
//����ע�⣬ʹ��Ԥ�����������������������Ϣ
#ifdef UNICODE
#define MyDbgPrint		MyOutputDebugStringW
#else
#define MyDbgPrint		MyOutputDebugStringA

#endif // UNICODE
