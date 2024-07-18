#pragma once
#include "pch.h"


//#include "LuaJIT-2.1.0-beta3\src\lua.hpp"
//#pragma comment(lib,"LuaJIT-2.1.0-beta3\\src\\lua51.lib")  
//extern "C"
//{
//#include "LuaJIT-2.1.0-beta3\src\lua.h"  
//#include "LuaJIT-2.1.0-beta3\src\lualib.h"  
//}
#define __LUA_÷∏’Î lua_State* L
void RegLuaScript(lua_State* L);
lua_State* initLua();
bool ÷¥––lua(lua_State* L, const char* lua√˚≥∆);

void ExecuteLuaFile(lua_State* L, const char* luaName);