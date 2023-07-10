#pragma once

#include "luaFunc.h"
//#include <string>
//#include "pch.h"
//#include <tuple>
//#include <string>
//#include <vector>
//#include <type_traits>
//#include <functional>
using namespace std;



// 将C++的std::string转换为Lua的字符串
//lua_State* C_L;
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
	const char* message = lua_tostring(L, 1);
	//DebugPrintf("%s\n", message);
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
	//MyTrace(L"结果 %d", a);
	if (a)
	{
		//MyTrace(L"结果");
		string errormssage = lua_tostring(L, -1);

		DebugPrintf("%s\n", lua_tostring(L, -1));
		Lua开关 = false;
		lua_close(L);
		return false;
	}
	return true;
}
//void 置全局LUA状态机(lua_State* L)
//{
//	C_L = L;
//}



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

	return 0;
}

//int DPrint(CString 文本)
//{
//	MyTrace(L"%s",文本);
//	return 0;
//}

static int 最优战船(__LUA_指针)
{
	航海::自动选择最优战船();

	return 0;
}

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

static int 设置船员(__LUA_指针)
{

	航海::设置所有船员();
	return 0;

}


static int 选船(__LUA_指针)
{
	DWORD id = lua_tointeger(L, 1);
	航海::luaVoyageShipSelectShip(id);
	return 0;



}

static int 关闭多余窗口(__LUA_指针)
{
	MyTrace(L"进入");
	if (环境::是否在和NPC对话())
	{
		环境::CALL_退出NPC();
		Sleep(2000);
	}
	DWORD size = 0;
	MyTrace(L"ces");

	size = UI功能::窗口数量();

	if (size >= 1)
	{
		for (size_t i = 0; i < size; i++)
		{
			size = UI功能::窗口数量();
			if (size >= 1)
			{
				MyTrace(L"开始执行按键call");
				UI功能::内存按键(VK_ESCAPE);
				Sleep(1500);

			}


		}


	}

	return 0;
}




static int 对话完成(__LUA_指针)
{
	DWORD id = lua_tointeger(L, 1);

	任务::Fun_阶段任务完成CALL(id);
	return 0;

}


static int 检测窗口(__LUA_指针)
{
	DWORD aa=0;
		
	aa=	UI功能::窗口数量();
	lua_pushinteger(L, aa);
	return 1;


}

static int 选择体验(__LUA_指针)
{

	const char* tmpStr = lua_tostring(L, 1);
	DWORD x;
	//sscanf(tmpStr, "%x", x);

	x = 常用功能::十六进制转十进制(tmpStr);
	新手::CALL_选择体验(x);
	Sleep(2000);
	新手::CALL_退出体验();
	return 0;

}

static int 快速设置技能(__LUA_指针)
{
	DWORD 技能ID = lua_tointeger(L, 1);
	DWORD 位置 = lua_tointeger(L, 2);
	技能::CALL_快捷键技能摆放(技能ID, 位置);

	return 0;



}

static int 打孔能力石(__LUA_指针)
{
	诞生石::诞生石强化();
	return 0;

}



static int 距离判断(__LUA_指针)
{
	float x,y,z;
	ActorInfo_ 角色信息 = 本人::取角色信息();
	x = lua_tonumber(L, 1);
	y = lua_tonumber(L, 2);
	z = lua_tonumber(L, 3);


	double dx = abs(x - 角色信息.坐标.x);
	double dy = abs(y - 角色信息.坐标.y);
	double dz = abs(z - 角色信息.坐标.z);

	double xyz = sqrt(pow(dx, 2) + pow(dy, 2) + pow(dz, 2))/100;
	lua_pushnumber(L,xyz);

	return 1;

}

static int 选择角色开始游戏(__LUA_指针)
{
	DWORD 序号 = lua_tointeger(L, 1);
	登陆::CALL_进入游戏(序号);

	return 0;
}


static int 读取职业(__LUA_指针)
{
	DWORD 职业 = 0;

	ActorInfo_ 角色信息 = 本人::取角色信息();
	职业 = 角色信息.职业;

	lua_pushinteger(L, 职业);
	//角色信息.对象指针
	return 1;
}



static int 游戏小退(__LUA_指针)
{
	环境::小退call();

	return 0;
}


static int 任务判断(__LUA_指针)
{
	const char* 任务ID = lua_tostring(L, 1);
	DWORD x;
	//sscanf(任务ID, "%x", x);

	x = 常用功能::十六进制转十进制(任务ID);


	vector<DWORD>vsk;
	任务::get_FinishQuestList(vsk);

	if (任务::任务是否已完成(x, vsk))
	{
		lua_pushinteger(L, 1);
	}
	else
	{
		lua_pushinteger(L, 0);
	}

	return 1;
}


static int 设置技能按键1(__LUA_指针)
{
	DWORD 技能ID = lua_tointeger(L, 1);
	DWORD 技能等级 = lua_tointeger(L, 2);
	DWORD c = lua_tointeger(L, 3);
	DWORD d = lua_tointeger(L, 4);
	DWORD e = lua_tointeger(L, 5);
	DWORD f = lua_tointeger(L, 6);
技能::CALL_升级技能天赋(技能ID, 技能等级,c,d,e);

技能::CALL_快捷键技能摆放(技能ID, f);
return 0;

}
//技能::CALL_升级技能天赋



static int 穿戴装备(__LUA_指针)
{

	背包::自定装备推荐装备();
		return 0;
}

//void 背包::自定装备推荐装备()
static int 自动任务(__LUA_指针)
{
	DWORD 任务阶段 = lua_tointeger(L, 1);
	const char* 任务ID = lua_tostring(L, 2);
	//int x;
	//sscanf(任务ID, "%x", x);
	//MyTrace(L"描述x %d \r\n", x);
	DWORD id1;

	id1 = 常用功能::十六进制转十进制(任务ID);

	DWORD id = 环境::读取当前对话npc();
	//MyTrace(L"类型 %d 任务名称 %s 
	MyTrace(L"id1 %X  id %X \r\n", id1, id);
	if (id>=1)
	{

		任务::getNpcTaklEndSendArg1(id, id1, 任务阶段);

		MyTrace(L"任务结束\r\n");

	}


	return 0;

}






static int 跳过序幕(__LUA_指针)
{

	新手::CALL_跳过序幕();

		return 0;
}



static int 确认职业(__LUA_指针)
{
	const char* tmpStr = lua_tostring(L, 1);
	DWORD id = lua_tointeger(L, 2);
	DWORD x;
	
	x = 常用功能::十六进制转十进制(tmpStr);

	新手::CALL_选择职业(x);

	return 0;
}

static int 是否在航海准备界面(__LUA_指针)
{
	int 局_UI对象;
	局_UI对象=	UI功能::是否在航海准备界面();
	if (局_UI对象==1)
	{
		lua_pushinteger(L, 1);
	}
	else
	{
		lua_pushinteger(L, 0);
	}
	return 1;

}

static int 仓库取物品功能(__LUA_指针)
{
	const char* tmpStr = lua_tostring(L, 1);
	


	背包::取单独仓库(CStringW(tmpStr));


	return 0;

}

static int 仓库取大东西(__LUA_指针)
{
	const char* tmpStr = lua_tostring(L, 1);
	背包::取公共仓库(CStringW(tmpStr));


	return 0;
}




static int 读取人物信息(__LUA_指针)
{
	CString aa = "0";
	ActorInfo_ 角色信息 = 本人::取角色信息();
	vector<CString>arr;
	CString temp;


	arr.push_back(角色信息.名称);
	temp.Format(L"%f", 角色信息.坐标.x);//1
	arr.push_back(temp);
	temp.Format(L"%f", 角色信息.坐标.y);//2
	arr.push_back(temp);
	temp.Format(L"%f", 角色信息.坐标.z);//3
	arr.push_back(temp);
	double 血量 = (double(角色信息.当前血) / double(角色信息.最大血)) * 100;

	temp.Format(L"%f", 血量);
	arr.push_back(temp);//4

	double 蓝量 = (double(角色信息.当前蓝) / double(角色信息.最大蓝)) * 100;
	temp.Format(L"%f", 蓝量);
	arr.push_back(temp);//5
	arr.push_back(角色信息.名称);//6
	temp.Format(L"%d", 角色信息.等级);
	arr.push_back(temp);//7

	temp.Format(L"%d", 角色信息.当前动作);
	arr.push_back(temp);//8
	temp.Format(L"%d", 角色信息.举起状态);
	arr.push_back(temp);//9
	temp.Format(L"%d", 角色信息.骑行状态);
	arr.push_back(temp);//10
	//temp.Format(L"%d", 角色信息.骑行状态);
	arr.push_back(aa);//11
	temp.Format(L"%d", 角色信息.行走状态);
	arr.push_back(temp);//12
	


	double 船舶 = (double(角色信息.航海当前耐久) / double(角色信息.航海最大耐久)) * 100;
	temp.Format(L"%f", 船舶);
	arr.push_back(temp);//13
	temp.Format(L"%d", 角色信息.装备评分);
	arr.push_back(temp);//14
	temp.Format(L"%d", 角色信息.当前血);
	arr.push_back(temp);//15
	temp.Format(L"%I64X", 角色信息.对象指针);
	arr.push_back(temp);//16
	lua_newtable(L);
	//lua_pushnumber(L, 角色信息.当前血)
	lua_pushnumber(L, -1);
	lua_rawseti(L,-2,0);
	for (size_t i = 0; i < arr.size(); i++)
	{
		lua_pushstring(L, CStringA(arr[i]));
		lua_rawseti(L, -2, i);
	}
	/*lua_newtable(L);
	lua_pushstring(L, "名称");
	lua_pushstring(L, CStringA(角色信息.名称));
	lua_settable(L, -3);
	lua_pushstring(L, "等级");
	lua_pushinteger(L, 角色信息.等级);
	lua_settable(L, -3);*/


//	DebugPrintf("%s\n", CStringA(角色信息.名称));
////	角色信息.当前血
//	//string str = to_string(角色信息.当前血);
//	//const char* char_str = str.c_str();
//	lua_pushnumber(L, 角色信息.当前血);
	return 1;
}
// ActorInfo_ 本人::取角色信息()

static int 准备出航(__LUA_指针)
{
	UI功能::准备出航();
	return 0;


}


static int 调试判断(__LUA_指针)
{
	if (调试开关==1)
	{
		luaL_error(L,"停止工作");


	}
	return 0;


}

static int 死亡复活(__LUA_指针)
{
	DWORD 复活触发 = lua_tointeger(L, 1);
	CString 复活方式;
	if (复活触发 == 1)
	{
		复活方式 = "root";
		UI功能::复活(复活方式);
	}
	else

	{
		复活方式 = "root";
		UI功能::复活(复活方式);
	}

	return 0;


}

static int 采集数量(__LUA_指针)
{
	const char* 控件对象 = lua_tostring(L, 1);
	DWORD addr=背包::采集数量(常用功能::十六进制转十进制(控件对象));
	lua_pushinteger(L, addr);
	return 1;

}

static int 对象查询(__LUA_指针)
{
	const char* 控件对象 = lua_tostring(L, 1);

	//MyTrace(L"控件对象 %s", CStringW(控件对象));
	INT64 x;

	x=常用功能::hex_to_decimal(控件对象);

	//MyTrace(L"控件对象 %I64d", x);
	//a = 控件对象;
	//stoi(a,0,16);
	//MyTrace(L"控件对象 %s", a);
	//x=temp.Format(L"%I64X", 控件对象);




	CString	name = UI功能::UI名称1(x);
	MyTrace(L"控件对象 %s", name);
	lua_pushstring(L, CStringA(name));

	return 1;
}


static int 坐标点击1(__LUA_指针)
{
	const char* 控件对象 = lua_tostring(L,1);
	const char* 控件名称 = lua_tostring(L, 2);
	INT64 x;
	x = 常用功能::hex_to_decimal(控件对象);
	CString	name = UI功能::UI名称1(x);

	MyTrace(L"控件对象 %s", name);
	if (name.Find(CStringW(控件名称))!=-1 && name.GetLength()!=0)
	{ 
		MyTrace(L"开始点击");
		UI功能::控件点击call(x);
	}

	return 0;
}


static int 获取坐标对象(__LUA_指针)
{
	float x = lua_tonumber(L, 1);
	float y = lua_tonumber(L, 2);

	INT64 addr = 环境::鼠标获取对象call(x, y);
	//CString(常用功能::十进制转十六进制(addr).c_str())
	MyTrace(L"addr,0x%I64X", addr);
		lua_pushstring(L, 常用功能::十进制转十六进制(addr).c_str());

	return 1;

}



static int 传送是否开起(__LUA_指针)
{
	DWORD 传送点ID = lua_tointeger(L, 1);


	bool id = 地图::传送点是否激活(传送点ID);
	if (id==1)
	{
		lua_pushinteger(L, 1);
	}
	else
	{
		lua_pushinteger(L, 0);
	}

	return 1;

}


static int 坐船功能(__LUA_指针)
{
	const char* tmpStr = lua_tostring(L, 1);
	DWORD x;
	x = 常用功能::十六进制转十进制(tmpStr);
	航海::坐船call功能(x);
	return 0;
}
static int 检测ESC(__LUA_指针)
{
	INT64 rcx = 0;
	bool 是否打开 = UI功能::寻找打开窗口("root1.arkui.windowCanvas.exitMenuWindow", rcx);
	if (rcx >= 1)
	{
		DWORD dResId = R_DW(rcx + 0xB8);
		if (dResId == 1)
		{
			lua_pushinteger(L, 1);
		}
		else

		{
			lua_pushinteger(L, 0);
		}
	}
	else
	{
		lua_pushinteger(L, 0);
	}
	return 1;


}
static int 重置数据(__LUA_指针)
{
	游戏模块 = (UINT64)GetModuleHandleA("LOSTARK.exe");
	游戏模块_EFEngine = (UINT64)GetModuleHandleA("EFEngine.dll");
	return 0;

}

static int 寻路地图(__LUA_指针)
{
	DWORD ID=环境::获取当前电梯ID();
	lua_pushinteger(L, ID);
	return 1;

}


static int 寻路_lua(__LUA_指针) 
{
	float x = lua_tonumber(L, 1);
	float y = lua_tonumber(L, 2);
	float z = lua_tonumber(L, 3);


	地图::本地图寻路(x,y,z,0);
	
	return 0;

}

static int 拖拽药物(__LUA_指针)
{
	DWORD x1 = lua_tointeger(L, 1);
	DWORD x2 = lua_tointeger(L, 2);
	DWORD x3 = lua_tointeger(L, 3);
	DWORD x4 = lua_tointeger(L, 4);
	背包::药品拖拽call(x1, x2, x3, x4);

	return 0;
}


static int 是否选择角色界面(__LUA_指针)
{
	//characterselect.fla_desc
	if(登陆::是否在准备界面()==1)
	{
		lua_pushinteger(L, 1);
	}
	else
	{
		lua_pushinteger(L, 0);
	}
	return 1;

}

static int 获取港口ID(__LUA_指针)
{
	DWORD 大陆ID = 地图::取当前大陆ID();
	lua_pushinteger(L, 大陆ID);

	return 1;

}

static int 还原技能(__LUA_指针)
{
	CString 弹窗文本 = UI功能::窗口反馈文本();
	CString 弹窗文本1 = "";

	if (弹窗文本.Find(L"Combat Skills") == -1)
	{
		UI功能::内存按键(DWORD('K'));
	}

	INT64 addr =环境::鼠标获取对象call(3460, 11640);
	if (addr>1)
	{
		弹窗文本1=UI功能::UI名称(addr);
		if (弹窗文本1.Find(L"init_btn") != -1)
		{


		}
		
	}
		


	return 0;


}
static int 是否航海界面(__LUA_指针)
{
	bool data = 航海::Yesornonauticalpicture();

	lua_pushinteger(L, data);

	return 1;
}
static int 金币数量(__LUA_指针)
{
	INT64 x = 背包::getMoneyNumByType(2);

	lua_pushinteger(L, x);

	return 1;
}


static int 捕鱼(__LUA_指针)
{
	钓鱼::捕鱼();

	return 0;

}

static int 拾取(__LUA_指针)
{
	DWORD ID = lua_tointeger(L, 1);
	功能::拾取(ID);

	return 0;
}



static int 类型数量(__LUA_指针)
{
	DWORD ID = lua_tointeger(L, 1);
	DWORD a = 背包::指定类型物品数量(ID);
	lua_pushinteger(L, a);
	return 1;
}

static int 技能信息(__LUA_指针)
{
	DWORD ID = lua_tointeger(L, 1);

	vector<SkillInfo_>vsk;
	技能::get_SkillList(vsk);
	//MyTrace(L"自动升级技能2");
	SkillInfo_ SKILL;
	SKILL=技能::取出指定技能信息(ID, vsk);
	lua_pushinteger(L, SKILL.dSkillLev);
	lua_pushinteger(L, SKILL.天赋1);
	lua_pushinteger(L, SKILL.天赋2);
	lua_pushinteger(L, SKILL.天赋3);

	return 4;
}

static int 剩余技能点(__LUA_指针)
{
	DWORD x = 技能::getRoleCurSkillPoints();
	lua_pushinteger(L, x);
	return 1;
}


static int 当前技能(__LUA_指针)
{
	DWORD ID = lua_tointeger(L, 1);
	DWORD add = 技能::SKLLADDR(ID);
	lua_pushinteger(L, add);
	return 1;


}


static int 信息获取(__LUA_指针)
{
	DWORD ID = lua_tointeger(L, 1);
	INT64 x= 背包::getMoneyNumByType(ID);

	lua_pushinteger(L, x);
	return 1;
}


static int 兑换黄金(__LUA_指针)
{
	DWORD ID = lua_tointeger(L, 1);
	DWORD ID1 = lua_tointeger(L, 2);
	NPC商店::Fun_BarterShopExchange(ID, ID1);
	return 0;


}


static int 测试商店(__LUA_指针)
{
	vector<Inventoryinfo_>vsk;
	NPC商店::get_ShopItemList(vsk);
	return 0;
}


static int 领取邮件(__LUA_指针)
{
	签到邮件::邮件领取();

	return 0;

}
static int 怪物数量1(__LUA_指针)
{
	DWORD 距离 = lua_tointeger(L, 1);
	DWORD add = 0;

	add = 环境::范围怪物数量1(距离);
	lua_pushinteger(L, add);
	return 1;


}

static int 怪物数量(__LUA_指针)
{
	DWORD 距离 = lua_tointeger(L, 1);
	DWORD add = 0;

	add = 环境::范围怪物数量(距离);
	lua_pushinteger(L, add);
	return 1;
}


static int 最近怪(__LUA_指针)
{
	DWORD 距离 = lua_tointeger(L, 1);
	const char* 过滤 = lua_tostring(L, 2);

	
	INT64 addr = 本人::最近怪物2(距离, 过滤);
	lua_pushinteger(L, addr);
	return 1;
}

static int 最近距离怪物(__LUA_指针)
{
	DWORD 距离 = lua_tointeger(L, 1);
//	DWORD add = 0;
	INT64 addr=本人::最近怪物1(距离);

	lua_pushinteger(L,addr);
	MyTrace(L"最近距离怪物0x%I64X\n", addr);
	return 1;


}

static int 大陆ID(__LUA_指针)
{
	DWORD 大陆ID = 地图::取当前大陆ID();
	lua_pushinteger(L, 大陆ID);

	return 1;

}

static int 测试(__LUA_指针)
{
	vector<objInfo_>vsk;
	环境::遍历全部环境对象1(vsk);
	//DWORD 大陆ID = 地图::取当前大陆ID();
	return 0;

	

}


static int 自定义记录(__LUA_指针)
{
	const char* message = lua_tostring(L, 1);

	MyTrace(L"%s", CStringW(message));

	return 0;
}



static int LogMsg1(__LUA_指针)
{
	const char* message = lua_tostring(L, 1);
	//const char* message = lua_tostring(L, -1);
	//DebugPrintf("%s\n", message);
	//string error_message = message;
	MyTrace(L"开始输出");
	MyTrace(L"%s", CStringW(message));

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


void RegLuaScript(lua_State* L)//lua注册函数
{


	lua_register(L, "取出主线任务", 中转_取出主线任务);
	lua_register(L, "日志输出", 中转_日志输出);
	lua_register(L, "延时", LUA_延时);
	lua_register(L, "设置船员", 设置船员);
	lua_register(L, "寻路", 寻路_lua);
	lua_register(L, "选船功能", 最优战船);
	lua_register(L, "msg", LogMsg1);
	lua_register(L, "读取人物信息", 读取人物信息);
	lua_register(L, "测试", 测试);
	lua_register(L, "仓库取物品功能", 仓库取物品功能);
	lua_register(L, "仓库取大东西", 仓库取大东西);
	lua_register(L, "选船功能", 选船);
	lua_register(L, "对话完成", 对话完成);
	lua_register(L, "检测窗口",检测窗口);
	lua_register(L, "选择体验", 选择体验);
	lua_register(L, "确认职业", 确认职业);
	lua_register(L, "跳过序幕", 跳过序幕);
	lua_register(L, "自动任务", 自动任务);
	lua_register(L, "穿戴装备", 穿戴装备);
	lua_register(L, "设置技能按键1", 设置技能按键1);
	lua_register(L, "快速设置技能", 快速设置技能);
	lua_register(L, "是否到达航海界面", 是否在航海准备界面);
	lua_register(L, "游戏小退", 游戏小退);
	lua_register(L, "读取职业", 读取职业);
	lua_register(L, "选择角色开始游戏", 选择角色开始游戏);
	lua_register(L, "距离判断", 距离判断);
	lua_register(L, "打孔能力石", 打孔能力石);
	lua_register(L, "获取港口ID", 获取港口ID);
	lua_register(L, "是否选择角色界面", 是否选择角色界面);
	lua_register(L, "拖拽药物", 拖拽药物);
	lua_register(L, "大陆ID", 大陆ID);
	lua_register(L, "寻路地图", 寻路地图);
	lua_register(L, "坐船功能", 坐船功能);
	lua_register(L, "重置数据", 重置数据);
	lua_register(L, "检测ESC", 检测ESC);
	lua_register(L, "传送是否开起", 传送是否开起);
	lua_register(L, "调试判断", 调试判断);
	lua_register(L, "准备出航", 准备出航);
	lua_register(L, "最近距离怪物", 最近距离怪物);
	lua_register(L, "最近怪", 最近怪);
	lua_register(L, "自定义记录", 自定义记录);
	lua_register(L, "怪物数量", 怪物数量);
	lua_register(L, "获取坐标对象", 获取坐标对象);
	lua_register(L, "坐标点击1", 坐标点击1);
	lua_register(L, "对象查询", 对象查询);
	lua_register(L, "关闭多余窗口", 关闭多余窗口);
	lua_register(L, "任务判断", 任务判断);
	lua_register(L, "特殊物品数量", 采集数量);
	lua_register(L, "死亡复活", 死亡复活);
	lua_register(L, "怪物数量1", 怪物数量1);
	lua_register(L, "领取邮件", 领取邮件);
	lua_register(L, "兑换黄金", 兑换黄金);
	lua_register(L, "测试商店", 测试商店);
	lua_register(L, "信息获取", 信息获取);

	lua_register(L, "当前技能", 当前技能);
	lua_register(L, "技能点", 剩余技能点);
	lua_register(L, "技能信息", 技能信息);

	lua_register(L, "类型数量", 类型数量);
	lua_register(L, "拾取", 拾取);
	lua_register(L, "捕鱼", 捕鱼);
	lua_register(L, "是否航海界面", 是否航海界面);



	//航海::自动选择最优战船
	//lua_close(L);
}



//CStringW  	const char*转换CString
//CStringA     CString转换const char*