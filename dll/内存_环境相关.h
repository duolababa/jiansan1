#pragma once
#include "pch.h"
class 环境
{
public:
	static objInfo_ getActorInfo(INT64 dObjAddr);
	static int CALL_对象是否可交互(INT64 环境对象指针);
	static int CALL_对象是否可交互2(INT64 环境对象指针);
	static int CALL_怪物是否已死亡(INT64 环境对象指针);
	static void 遍历全部环境对象(vector<objInfo_>& vsk);
	static void 遍历指定全部环境对象(DWORD dtype, vector<objInfo_>& vsk);
	static bool 判断怪物(INT64 对象);
	static bool 判断NPC(INT64 对象);
	static bool 判断地面物品(INT64 对象);
	static bool 判断采集物(INT64 对象);
	static bool 判断击打道具(INT64 对象);
	static bool 击打道具是否死亡(INT64 对象);
	static void 遍历怪物(vector<objInfo_>& 数组);
	static void 遍历NPC(vector<objInfo_>& 数组);
	static objInfo_ 取指定类型NPC(CString temp);
	static void 遍历采集物(vector<objInfo_>& 数组);
	static void 遍历击打道具(vector<objInfo_>& 数组);
	static void 遍历地面物品(vector<objInfo_>& 数组);
	static void 遍历电梯(vector<objInfo_>& 数组);
	static void 遍历传送门(vector<objInfo_>& 数组);
	static objInfo_ 取指定对象信息(DWORD ResId);
	static objInfo_ 取随机怪物信息();
	static objInfo_ 取指定采集对象信息(DWORD ResId);
	static objInfo_ 取指定任务显示对象信息(DWORD ResId, DWORD ResShow = 1);
	static objInfo_ 取指定范围任务显示对象信息(float x, float y, float z, float 距离, DWORD ResId);
	static 坐标_ 取对象坐标(INT64 对象);
	static bool CALL_打开NPC(INT64 对象);
	static bool CALL_退出NPC();
	static bool CALL_NPC对话分支(int 对话序号);
	static int 读取当前对话NPC();
	static bool 是否在和NPC对话();
	static bool 是否在加载页面();
	static bool 是否在加载页面2();
	static bool 是否在动画();
	static bool 拾物(INT64 对象);
	static bool CALL_点击指定NPC(CString 对象名称);
	static bool CALL_点击指定NPC_ByResId(DWORD ResId);
	static float 获取对象角度值(INT64 obj);
	static int 获取对象释放技能组(INT64 obj);
	static DWORD 获取当前电梯ID();
	static void 加入优先采集ID(CString ID文本);
};

class NPC
{
public:

	static bool CALL_ShopBuyAddItem(int dItemIndex);

	static bool ShopBuyItemClick();

	static void get_ShopItemList(vector<Inventoryinfo_>& 商店购买组);

};
