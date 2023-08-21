// pch.h: 这是预编译标头文件。
// 下方列出的文件仅编译一次，提高了将来生成的生成性能。
// 这还将影响 IntelliSense 性能，包括代码完成和许多代码浏览功能。
// 但是，如果此处列出的文件中的任何一个在生成之间有更新，它们全部都将被重新编译。
// 请勿在此处添加要频繁更新的文件，这将使得性能优势无效。

#ifndef PCH_H
#define PCH_H
//#define WIN32_LEAN_AND_MEAN  
//#define _AFXDLL
// 添加要在此处预编译的标头
//#include <Windows.h>
//#include <tchar.h>
//#include <winnls.h>

#include<stdio.h>
#include<malloc.h>
//#include<windows.h>
#include <SDKDDKVer.h>
#include <afx.h>
//#include "framework.h"
//#include <WinDNS.h>

#include <afxcontrolbars.h>
#include <d3d11.h>
#include <D3Dcompiler.h>
//#include <libop.h>
//#include <atlstr.h>
#include <iostream>
#include "自定义数据类型.h"
#include "全局变量.h"
#include "常量.h"
// ImGui头文件载入
#include "ImGui/imconfig.h"
#include "ImGui/imgui.h"
#include "ImGui/imgui_impl_dx11.h"
#include "ImGui/imgui_impl_win32.h"
#include "ImGui/imgui_internal.h"
#include "ImGui/imstb_rectpack.h"
#include "ImGui/imstb_textedit.h"
#include "ImGui/imstb_truetype.h"

// 自创字体文件
#include "Detours/include/detours.h"
#include "SDK/Helpers.h"
#include "ImGuiWin.h"
#include <vector>
#include <string>
#include "DbgPrint.h"

#include "FlowerDream.h"
#include "通用功能.h"
#include "golbalApi.h"

#include "Thread.h"
#include "内存_通用数据.h"
#include "内存_UI相关.h"
#include "内存_本人相关.h"
#include "内存_背包相关.h"
#include "内存_地图相关.h"
#include "内存_登陆相关.h"
#include "内存_环境相关.h"
#include "内存_技能相关.h"
#include "内存_任务相关.h"
#include "内存_新手相关.h"
#include "内存_签到邮件.h"
#include "内存_NPC商店.h"
#include "游戏_主线.h"
#include "配置读取.h"
#include "内存_航海相关.h"
#include "内存_钓鱼相关.h"
#include "内存_能力刻印相关.h"
#pragma comment(lib, "detours.lib" ) 
#include "dthookapi.h"
#include "hook_api.h"
#include<algorithm>  
using namespace std;
#pragma comment(lib, "lua.lib" ) 
#include "luaFunc.h"
#include "XhideDll.h"
#include "WMcopyData.h"
#include "MyCallFunction.h"
#include "常用功能.h"
#include "配置读取.h"
#include "内存_混沌副本相关.h"
#include "内存_周常任务.h"
#include "内存_登陆相关.h"
#include "通信程序集.h"
#include "luac.h"
////#include "协议解析1088.h"
//#include "LuaFunc.h"
//#include<Windows.h>
const CString 莱温哈特大教堂 = L"莱温哈特大教堂";
const CString 涅利亚酒吧 = L"涅利亚酒吧";
const CString 艾尔拉拉的装备商店 = L"艾尔拉拉的装备商店";

#endif //PCH_H

//  部分函数指针类型声明
typedef HRESULT(__stdcall* tD3D11Present)(IDXGISwapChain* pSwapChain, UINT SyscInterval, UINT Flags);
typedef LRESULT(__stdcall* WndProc_t)(const HWND, UINT, WPARAM, LPARAM);
typedef HRESULT(__stdcall* ResizeBuffers)(IDXGISwapChain* This, UINT BufferCount, UINT Width, UINT Height, DXGI_FORMAT NewFormat, UINT SwapChainFlags);
LRESULT __stdcall hkWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);




