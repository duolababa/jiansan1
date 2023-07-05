#pragma once

#include "luaFunc.h"
//#include <string>
//#include "pch.h"
#include <tuple>
#include <string>
#include <vector>
#include <type_traits>
#include <functional>
using namespace std;



// 将C++的std::string转换为Lua的字符串
lua_State* C_L;
//void 置全局LUA状态机(lua_State* L)
//{
//	C_L = L;
//}
//template <typename FuncPtr, typename... Args>
//void register_function(lua_State* L, const char* name, FuncPtr func)
//{
//	lua_pushlightuserdata(L, (void*)func);
//}
//template <typename FuncPtr, typename... Args>
//int c_to_lua(lua_State* L) {
//	FuncPtr func = lua_touserdata(L, lua_upvalueindex(1)); // 取出函数指针
//	int x = luaL_checkinteger(L, 1); // 取出第一个参数
//	int y = luaL_checkinteger(L, 2); // 取出第二个参数
//	int ret = func(x, y); // 调用 C 函数
//	lua_pushinteger(L, ret); // 将返回值压入栈中
//	return 1; // 返回返回值的数量
//}
//void CToLua(FuncPtr func,int 返回值类型, Args... args)
//{
//
//	int count = sizeof...(args);
//	va_list vargs;
//	va_start(vargs, count);
//	//for(size_t i=0;i<)
//	//L = __LUA_指针;
//	
//}
int panic(lua_State* L)
{
	const char* message = lua_tostring(L, -1);
	DebugPrintf("%s\n", message);
	string error_message = message;
	SendMessageToMoConter(111, error_message.c_str());
	// 处理错误信息
	return 0;
}
lua_State* initLua()
{
	static lua_State* L = NULL;
	if (L == NULL)
	{
		L = luaL_newstate();
		luaL_openlibs(L);
		//lua_atpanic(L, panic);
	}
	return L;
}
void RegLuaScript(lua_State* L)
{


	lua_register(L, "取出主线任务", 中转_取出主线任务);
	lua_register(L, "日志输出", 中转_日志输出);
	lua_register(L, "延时", LUA_延时);
	//lua_close(L);
}

bool 执行lua(lua_State* L,const char * lua名称)
{
	
	//const char* 名称 = lua名称.c_str();
	//MyTrace(L"加载LUA");
	//lua_atpanic(L, [](lua_State* L) -> int {
	//	// 捕获 panic，输出错误信息
	//	const char* error_message = lua_tostring(L, -1);
	//	DebugPrintf("Lua script error: %s\n", error_message);
	//	return 0;
	//	});
	//if (luaL_loadfile(L, 名称) != 0) {
	//	// 加载失败，输出错误信息
	//	MyTrace(L"加载失败");
	//	const char* error_message = lua_tostring(L, -1);
	//	string errormssage = error_message;

	//	DebugPrintf("Failed to load Lua script: %s\n", error_message);
	//	lua_pop(L, 1); // 从堆栈中弹出错误信息
	//	SendMessageToMoConter(111, errormssage.c_str());
	//	Lua开关 = false; lua_close(L); return false;
	//}
	//else {
	//	// 加载成功，执行代码
	//	lua_pcall(L, 0, 0, 0);
	//}
	/*__try
	{
		
		if (luaL_loadstring(L, "if print(1);\nprint(a);\nprint(2);") != LUA_OK) {
			const char* error = lua_tostring(L, -1);
			
			lua_pop(L, 1);
		}
	}
	__except (SEHHandler(GetExceptionInformation()), EXCEPTION_EXECUTE_HANDLER)
	{

	}*/
	bool a = luaL_dofile(L, lua名称);
	MyTrace(L"结果 %d",a);
	if (a)
	{
		MyTrace(L"结果");
		string errormssage = lua_tostring(L, -1);
		
		DebugPrintf("%s\n", lua_tostring(L, -1));
		Lua开关 = false;
		lua_close(L);
		return false;
	}
	return true;
}
void 置全局LUA状态机(lua_State* L)
{
	C_L = L;
}



// 将C++函数注册为全局函数
//typedef int (*CFunc)(lua_State*, void**);
//void register_cpp_function(lua_State* L, const char* name, CFunc func) {
//	lua_pushlightuserdata(L, (void*)func);
//	lua_pushcclosure(L, cpp_function_wrapper, 1);
//	lua_setglobal(L, name);
//}
//
//// 转发函数调用到C++函数
//int cpp_function_wrapper(lua_State* L) {
//	// 获取C++函数指针
//	CFunc func = (CFunc)lua_touserdata(L, lua_upvalueindex(1));
//
//	// 获取参数个数
//	int argc = lua_gettop(L);
//
//	// 创建参数数组
//	void** args = (void**)malloc(argc * sizeof(void*));
//
//	// 解析参数
//	int i;
//	for (i = 1; i <= argc; i++) {
//		switch (lua_type(L, i)) {
//		case LUA_TBOOLEAN:
//			args[i - 1] = (void*)(intptr_t)lua_toboolean(L, i);
//			break;
//		case LUA_TNUMBER:
//			args[i - 1] = (void*)(intptr_t)lua_tonumber(L, i);
//			break;
//		case LUA_TSTRING:
//			args[i - 1] = (void*)lua_tostring(L, i);
//			break;
//		default:
//			args[i - 1] = lua_touserdata(L, i);
//			break;
//		}
//	}
//
//	// 调用C++函数
//	//auto ptr = &func;
//	//MyCallFun::call_function(ptr, args);
//	int ret = (*func)(L, args);
//
//	// 释放参数数组
//	free(args);
//
//	// 返回结果
//	return ret;
//}

static int LUA_延时(__LUA_指针)
{
	DWORD ndArgNum = lua_gettop(L);
	if (ndArgNum <= 0)
	{
		Sleep(100);
		lua_pushboolean(L, FALSE);
		return 1;
	}
	Sleep(lua_tointeger(L, 1));//等待相应的毫秒数
	lua_pushboolean(L, TRUE);
	return 1;//返回一个参数
}

int newadd(int a, int b)
{
	return a + b;
}
//void MyL_加法()
//{
//	CToLua(&newadd, MyType::整数型, MyType::整数型, MyType::整数型);
//}

static int MovePoint(__LUA_指针)
{
	float x = lua_tonumber(L, 1);
	float y = lua_tonumber(L, 2);
	float z = lua_tonumber(L, 3);
	地图::本地图寻路(x, y, z, 0);
	return 0;
}

//int DPrint(CString 文本)
//{
//	MyTrace(L"%s",文本);
//	return 0;
//}



static int 中转_取地图ID(__LUA_指针)
{
	lua_pushinteger(L, 地图::取地图ID());
	return 1;
}
static int 中转_自定装备推荐装备(__LUA_指针)
{
	背包::自定装备推荐装备();
	return 0;
}
static int 中转_日志输出(__LUA_指针)
{
	const char* tmpStr = lua_tostring(L, 1);
	//DebugPrintf("日志:%s", tmpStr);
	string tempStr = tmpStr;
	CString tmp = tempStr.c_str();
	SendMessageToMoConter(112, tmp);
	return 0;
}
static int 中转_指定UI是否显示(__LUA_指针)
{
	USES_CONVERSION;
	const char* tmpStr = lua_tostring(L, 1);
	CString tmp = A2W(tmpStr);
	if (tmp != L"")
	{
		lua_pushboolean(L, UI功能::指定UI是否显示(tmp));
	}
	
	return 0;
}
 int 中转_取出主线任务(__LUA_指针)
{
	//USES_CONVERSION;
	QuestInfo_ 主线任务 = 任务::取出主线任务();
	MyTrace(L"主线任务名称%s 子任务数量 %d", 主线任务.QuestName, 主线任务.子任务进度.size());
	// 创建"子任务进度"表
	
	MyTrace(L"2");
	lua_newtable(L);	
	lua_pushstring(L, "objBase");
	lua_pushinteger(L, 主线任务.objBase);
	lua_settable(L, -3);
	lua_pushstring(L, "dResAddr");
	lua_pushinteger(L, 主线任务.dResAddr);
	lua_settable(L, -3);
	lua_pushstring(L, "dQuestId");
	lua_pushnumber(L, 主线任务.dQuestId);
	lua_settable(L, -3);
	lua_pushstring(L, "dStep");
	lua_pushnumber(L, 主线任务.dStep);
	lua_settable(L, -3);
	lua_pushstring(L, "dState");
	lua_pushnumber(L, 主线任务.dState);
	lua_settable(L, -3);
	lua_pushstring(L, "dType");
	lua_pushnumber(L, 主线任务.dType);
	lua_settable(L, -3);
	lua_pushstring(L, "IsFinish");
	lua_pushnumber(L, 主线任务.IsFinish);
	lua_settable(L, -3);
	lua_pushstring(L, "QuestName");
	lua_pushstring(L, CStringA(主线任务.QuestName));
	lua_settable(L, -3);
	lua_pushstring(L, "CurNum");
	lua_pushnumber(L, 主线任务.CurNum);
	lua_settable(L, -3);
	lua_pushstring(L, "NeedNum");
	lua_pushnumber(L, 主线任务.NeedNum);
	lua_settable(L, -3);
	lua_pushstring(L, "TargetId");
	lua_pushnumber(L, 主线任务.TargetId);
	lua_settable(L, -3);
	lua_pushstring(L, "QuestOption");
	lua_pushstring(L, CStringA(主线任务.QuestOption));
	lua_settable(L, -3);
	lua_pushstring(L, "子任务进度数量");
	lua_pushnumber(L, 主线任务.子任务进度.size());
	lua_settable(L, -3);
	lua_pushstring(L, "子任务进度");
	lua_newtable(L);
	for (size_t i = 0; i < 主线任务.子任务进度.size(); i++)
	{
		char buffer[10];
		sprintf(buffer, "%d", i + 1);
		lua_pushstring(L, buffer);
		MyTrace(L"1");
		lua_newtable(L);
		lua_pushstring(L, "任务描述");
		lua_pushstring(L, CStringA(主线任务.子任务进度[i].任务描述));
		lua_settable(L, -3);
		lua_pushstring(L, "TargetId");
		lua_pushnumber(L, 主线任务.子任务进度[i].TargetID);
		lua_settable(L, -3);
		lua_pushstring(L, "dCur");
		lua_pushnumber(L, 主线任务.子任务进度[i].dCur);
		lua_settable(L, -3);
		lua_pushstring(L, "dNeed");
		lua_pushnumber(L, 主线任务.子任务进度[i].dNeed);
		lua_settable(L, -3);
		// 将任务1添加到子任务进度table中
		lua_settable(L, -3);
		
	}
	lua_settable(L, -3);

	
	MyTrace(L"3");
	return 1;
}
/*
#define __LUA_指针 lua_State* L

static int MovePoint(__LUA_指针)
{
	float x = lua_tonumber(L, 1);
	float y = lua_tonumber(L, 2);
	float z = lua_tonumber(L, 3);
	游戏功能群782282356::f瞬移(x, y, z);
	//DebugPrintf("调用了lua[瞬移] -- 坐标内容 => [%.1f,%.1f,%.1f]\n",x,y,z);
	return 0;
}
static int DbgPrint(__LUA_指针)
{
	const char* tmpStr = lua_tostring(L, 1);
	DebugPrintf("%s\n", tmpStr);
	return 0;
}
static int GetMapId(__LUA_指针)
{
	lua_pushinteger(L, 游戏功能群782282356::f获取地图ID());
	return 1;
}
static int FindWayTo(__LUA_指针)
{
	DWORD MAPID = lua_tonumber(L, 1);
	float x = lua_tonumber(L, 2);
	float y = lua_tonumber(L, 3);
	float z = lua_tonumber(L, 4);
	游戏功能群782282356::CALL寻路(MAPID, x, y, z);
	return 0;
}
static int GameKeyB(__LUA_指针)
{
	DWORD KeyVal = lua_tointeger(L, 1);
	//游戏功能群782282356::CALL按键((UINT64)KeyVal);
	return 0;
}

static int GetFindWayNextPos(__LUA_指针)
{
	结构_坐标 tmpPos = 游戏功能群782282356::f取寻路下个目的坐标();
	lua_pushnumber(L, tmpPos.x);
	lua_pushnumber(L, tmpPos.y);
	lua_pushnumber(L, tmpPos.z);
	return 3;
}
static int GetRolePos(__LUA_指针)
{
	结构_坐标 tmpPos = 游戏功能群782282356::f取角色坐标();
	lua_pushnumber(L, tmpPos.x);
	lua_pushnumber(L, tmpPos.y);
	lua_pushnumber(L, tmpPos.z);
	return 3;
}
static int GetRoleSateL(__LUA_指针)
{
	lua_pushinteger(L, 游戏功能群782282356::f获取角色状态());
	return 1;
}
static int IsLoadingL(__LUA_指针)
{
	lua_pushboolean(L, 游戏功能群782282356::f是否进入游戏中());
	return 1;
}
static int IsStoryMissionIngL(__LUA_指针)
{
	lua_pushboolean(L, 游戏功能群782282356::f是否在剧情中());
	return 1;
}
static int SeckillMonsterL(__LUA_指针)
{
	游戏功能群782282356::f秒杀怪物();
	return 0;
}
static int FindWayMoveTo(__LUA_指针)
{
	DWORD MAPID = lua_tonumber(L, 1);
	float x = lua_tonumber(L, 2);
	float y = lua_tonumber(L, 3);
	float z = lua_tonumber(L, 4);
	游戏功能群782282356::f寻路瞬移(MAPID, x, y, z);
	return 0;
}
static int IsFindWayIngL(__LUA_指针)
{
	lua_pushboolean(L, 游戏功能群782282356::f是否寻路中());
	return 1;
}
static int GetMainTaskListL(__LUA_指针)
{
	游戏功能群782282356::f取已接任务列表();
	lua_pushinteger(L, 游戏功能群782282356::已接任务列表.size());
	return 1;
}
static int 获取控件对象列表(__LUA_指针)
{

	//控件功能开源群782282356::f取控件对象结构列表();
	return 0;
}

static int 自动开始游戏(__LUA_指针)
{
	控件功能开源群782282356::点击开始游戏();
	return 0;
}
static int 跳过左上角引导(__LUA_指针)
{
	控件功能开源群782282356::跳过引导对话_左上角();
	return 0;
}
static int 跳过右上角引导(__LUA_指针)
{
	控件功能开源群782282356::跳过引导对话_右上角();
	return 0;
}
static int 法师攻击随机目标(__LUA_指针)
{
	游戏功能群782282356::攻击随机对象();
	return 0;
}
static int 控件_进入游戏(__LUA_指针)
{
	控件功能开源群782282356::点击进入游戏();
	return 0;
}
static int  交接任务(__LUA_指针)
{
	DWORD 标志 = lua_tointeger(L, 1);
	DWORD 任务id = lua_tointeger(L, 2);
	游戏功能群782282356::CALL交接任务(标志, 任务id);
	return 0;
}
static int 控件call(__LUA_指针)
{
	char* tmpstr = (char*)lua_tostring(L, 1);
	DWORD 偏移 = lua_tointeger(L, 2);

	//DebugPrintf("%s\n", tmpstr);	
	控件功能开源群782282356::CALL控件开源群782282356(tmpstr, 偏移);
	return 0;
}

void RegLuaScript()
{

	lua_State* L = luaL_newstate();
	luaL_openlibs(L);

	lua_register(L, "瞬移", MovePoint);
	lua_register(L, "取地图ID", GetMapId);
	lua_register(L, "调试输出", DbgPrint);
	lua_register(L, "寻路到", FindWayTo);
	lua_register(L, "寻路瞬移", FindWayMoveTo);
	lua_register(L, "获取下一个点", GetFindWayNextPos);
	lua_register(L, "获取角色坐标", GetRolePos);
	lua_register(L, "获取角色状态", GetRoleSateL);
	lua_register(L, "是否在游戏中", IsLoadingL);
	lua_register(L, "是否在剧情中", IsStoryMissionIngL);
	lua_register(L, "是否寻路中", IsFindWayIngL);
	lua_register(L, "获取已接任务", GetMainTaskListL);
	lua_register(L, "取控件对象列表", 获取控件对象列表);
	lua_register(L, "自动开始游戏", 自动开始游戏);
	lua_register(L, "自动跳过左上角引导", 跳过左上角引导);
	lua_register(L, "自动跳过右上角引导", 跳过右上角引导);
	lua_register(L, "攻击一下", 法师攻击随机目标);
	lua_register(L, "交接任务", 交接任务);
	lua_register(L, "控件CALL", 控件call);
	lua_register(L, "点击进入游戏", 控件_进入游戏);


	bool a= luaL_dofile(L, "Mir4.lua");

	if (a) DebugPrintf("%s\n", lua_tostring(L, -1));

	lua_close(L);
}

*/