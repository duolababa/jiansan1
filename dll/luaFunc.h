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
#define __LUA_ָ�� lua_State* L
void RegLuaScript(lua_State* L);
lua_State* initLua();
bool ִ��lua(lua_State* L, const char* lua����);
 int ��ת_ȡ����������(__LUA_ָ��);
static int ��ת_��־���(__LUA_ָ��);
static int LUA_��ʱ(__LUA_ָ��);