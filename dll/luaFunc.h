#pragma once
#include "pch.h"

//extern "C"
//{
//#include "lua/src/lua.h"
//#include "lua/src/lualib.h"
//#include "lua/src/lauxlib.h"
//
//
//}
#include "LuaJIT-2.1.0-beta3\src\lua.hpp"
#pragma comment(lib,"LuaJIT-2.1.0-beta3\\src\\lua51.lib")  
extern "C"
{
#include "LuaJIT-2.1.0-beta3\src\lua.h"  
#include "LuaJIT-2.1.0-beta3\src\lualib.h"  
}
#define __LUA_指针 lua_State* L
void RegLuaScript(lua_State* L);
lua_State* initLua();
bool 执行lua(lua_State* L, const char* lua名称);
 int 中转_取出主线任务(__LUA_指针);
static int 中转_日志输出(__LUA_指针);
static int LUA_延时(__LUA_指针);