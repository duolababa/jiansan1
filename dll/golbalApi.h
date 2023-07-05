#pragma once
#include <string>
#include <tchar.h>
#include <Shlwapi.h>
#include<stdio.h>



#define 标题   NULL // "Naraka"
#define 类名   "EFLaunchUnrealUWindowsClient" //UnityWndClass

//获取当前句柄
HWND  GetCurrentHwnd(const char* 游戏窗口类名);//游戏进程里用
HWND  GetCurrentHwnd();
HWND  GetGameImeHwnd(HWND hGame);//获取窗口相关联的 窗口
DWORD GetGameThreadId();
DWORD  GetGameProcesssID();
BOOL IsGameProcess();
//获取当前进程名字
const TCHAR* GetCurrentProcessPathName(IN OUT TCHAR* szCurExeFilePathName);
//获取当前进程名字
const TCHAR* GetCurrentProcessName(IN OUT TCHAR* 当前进程名);
BOOL 挂接主线程();
BOOL 卸载主线程();