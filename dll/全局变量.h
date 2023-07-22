#pragma once
#include "pch.h"
extern bool 循环跳出;
extern DWORD64 g_dwBreakpoint;
extern DWORD64 g_dwBreakpoint2;
extern DWORD GameIndex;
extern UINT64 游戏模块;
extern UINT64 游戏模块_EFEngine;
extern  UINT 注册消息值;
extern bool 屏蔽鼠标开关;
extern bool 调试开关;
extern POINT hook鼠标坐标;
extern vector<DWORD>暂时不打ID;
extern CString 辅助位置;
extern CString 脚本任务;
extern CString 配置服务器;
extern CString LUA脚本名称;
extern bool Lua开关;
extern int 角色数量;
extern int 角色序号;
extern vector<登陆角色信息_> 全_角色列表;