#pragma once
#include "pch.h"

extern "C"
{
#include "lua/src/lua.h"
#include "lua/src/lualib.h"
#include "lua/src/lauxlib.h"


}
//#include "LuaJIT-2.1.0-beta3\src\lua.hpp"
//#pragma comment(lib,"LuaJIT-2.1.0-beta3\\src\\lua51.lib")  
//extern "C"
//{
//#include "LuaJIT-2.1.0-beta3\src\lua.h"  
//#include "LuaJIT-2.1.0-beta3\src\lualib.h"  
//}
#define __LUA_指针 lua_State* L
void RegLuaScript(lua_State* L);
lua_State* initLua();
bool 执行lua(lua_State* L, const char* lua名称);
 int 中转_取出主线任务(__LUA_指针);
static int 中转_日志输出(__LUA_指针);
static int LUA_延时(__LUA_指针);
static int 设置船员(__LUA_指针);
static int 寻路_lua(__LUA_指针);
static int LogMsg1(__LUA_指针);
static int 测试(__LUA_指针);
static int 读取人物信息(__LUA_指针);
static int 仓库取大东西(__LUA_指针);
static int 仓库取物品功能(__LUA_指针);
static int 选船(__LUA_指针);
static int 检测窗口(__LUA_指针);
static int 对话完成(__LUA_指针);
static int 关闭多余窗口(__LUA_指针);
static int 选择体验(__LUA_指针);
static int 确认职业(__LUA_指针);
static int 跳过序幕(__LUA_指针);
static int 自动任务(__LUA_指针);

static int 穿戴装备(__LUA_指针);
static int 设置技能按键1(__LUA_指针);
static int 快速设置技能(__LUA_指针);
static int 是否在航海准备界面(__LUA_指针);
static int 任务判断(__LUA_指针);
static int 游戏小退(__LUA_指针);
static int 读取职业(__LUA_指针);
static int 选择角色开始游戏(__LUA_指针);
static int 距离判断(__LUA_指针);
static int 打孔能力石(__LUA_指针);
static int 获取港口ID(__LUA_指针);
static int 是否选择角色界面(__LUA_指针);
static int 拖拽药物(__LUA_指针);
static int 大陆ID(__LUA_指针);
static int 寻路地图(__LUA_指针);
static int 坐船功能(__LUA_指针);
static int 重置数据(__LUA_指针);
static int 检测ESC(__LUA_指针);
static int 传送是否开起(__LUA_指针);
static int 调试判断(__LUA_指针);
static int 准备出航(__LUA_指针);
static int 最近距离怪物(__LUA_指针);
static int 最近怪(__LUA_指针);
static int 自定义记录(__LUA_指针);
static int 怪物数量(__LUA_指针);
static int 获取坐标对象(__LUA_指针);
static int 坐标点击1(__LUA_指针);
static int 对象查询(__LUA_指针);
static int 采集数量(__LUA_指针);
static int 死亡复活(__LUA_指针);
static int 怪物数量1(__LUA_指针);
static int 领取邮件(__LUA_指针);
static int 兑换黄金(__LUA_指针);
static int 测试商店(__LUA_指针);
static int 信息获取(__LUA_指针);
static int 当前技能(__LUA_指针);
static int 剩余技能点(__LUA_指针);
static int 技能信息(__LUA_指针);
static int 类型数量(__LUA_指针);
static int 拾取(__LUA_指针);
static int 捕鱼(__LUA_指针);
static int 金币数量(__LUA_指针);
static int 是否航海界面(__LUA_指针);



// NPC商店::get_ShopItemList(vector<Inventoryinfo_>& vsk)



//UI功能::复活(CString 复活方式)
//	lua_register(L, "传送是否开起", 传送是否开起);
//游戏模块 = (UINT64)GetModuleHandleA("LOSTARK.exe");
//游戏模块_EFEngine = (UINT64)GetModuleHandleA("EFEngine.dll");


//	lua_register(L, "坐船功能", 坐船功能);
//技能::CALL_升级技能天赋
//void 背包::自定装备推荐装备()

//lua_register(L, "跳过序幕", 跳过序幕);
// ActorInfo_ 本人::取角色信息()