#pragma once
#include <string>
#include <tchar.h>
#include <Shlwapi.h>
#include<stdio.h>



#define ����   NULL // "Naraka"
#define ����   "EFLaunchUnrealUWindowsClient" //UnityWndClass

//��ȡ��ǰ���
HWND  GetCurrentHwnd(const char* ��Ϸ��������);//��Ϸ��������
HWND  GetCurrentHwnd();
HWND  GetGameImeHwnd(HWND hGame);//��ȡ����������� ����
DWORD GetGameThreadId();
DWORD  GetGameProcesssID();
BOOL IsGameProcess();
//��ȡ��ǰ��������
const TCHAR* GetCurrentProcessPathName(IN OUT TCHAR* szCurExeFilePathName);
//��ȡ��ǰ��������
const TCHAR* GetCurrentProcessName(IN OUT TCHAR* ��ǰ������);
BOOL �ҽ����߳�();
BOOL ж�����߳�();