#include "pch.h"
#include "ImGuiWin.h"
#include "luaFunc.h"

//IMGUI使用变量初始化

char InputText[1024 * 20] = u8"";

// 全局变量和类初始化
//ClipboardExample 剪贴板 = ClipboardExample();//鼠标剪贴板操作类
UINT64 全局模块句柄 = (UINT64)GetModuleHandleA("LOSTARK.exe");

bool b鼠标消息影响游戏;

void MainLuaCall()
{
    ::SendMessageA(g_hWnd, 注册消息值, Msgid::CallLua, 0);
}


// 我的IMGUI窗口开始处
void 显示游戏IMGUI窗口(bool* mainBeginSate)
{
	IM_设置初始窗口坐标;
	IM_设置窗口_不固定尺寸(600, 400);
	IM_开始(u8"LOSTARK - 觉醒 - SCRIPT");
	/*------------------------------*/ 


    //if (IM_工具栏_整行(u8"控件测试")) 工具栏5();


    IM_结束;
}


