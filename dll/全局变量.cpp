#include "全局变量.h"
bool 循环跳出=false;
DWORD GameIndex = 0;
UINT64 游戏模块;
UINT64 游戏模块_EFEngine;
 UINT 注册消息值 = RegisterWindowMessageA("ARKMsg");
bool 屏蔽鼠标开关 = false;
POINT hook鼠标坐标;
DWORD64 g_dwBreakpoint;
DWORD64 g_dwBreakpoint2;
vector<DWORD>暂时不打ID;
CString 辅助位置;
CString 脚本任务;
CString 配置服务器;
CString 角色序号=L"";
CString LUA脚本名称 = L"";
bool Lua开关 = false;