#pragma once
#include "pch.h"
class NPC商店
{
public:
	static void Fun_ShopBuyAddItem(int dItemIndex, int dum);
	static void Fub_ShopBuyItemClick();
	static void get_ShopItemList(vector<Inventoryinfo_>& vsk);
	static bool 修理装备();
	static bool 补充药水();
	static bool 物品存仓();
	static void Fun_BarterShopExchange(DWORD dItemIndex, DWORD dNum);
	static void shoppingmall(vector<商城信息_>& vsk);
	static void openshop(vector<商城信息_>& vsk);
	static void funshop(DWORD ID, DWORD 次数);
	static DWORD 查询钻石数量();

	static void 领取箱子(DWORD ID);
	//static void get_ShopItemList();
};

class 拍卖
{
public:

	static void 登记拍卖(DWORD ID, DWORD ID1);
	static DWORD 查询金额call();
	static void 自动拍卖(DWORD ID, DWORD 总量, DWORD 价格, INT64 物品ID1);
	static 	bool 拍卖::拍卖行是否打开();

};

void 输入邮寄名称(CString name);
void 输入邮寄物品(DWORD ID, DWORD 数量, DWORD 物品位置);
void 开始邮寄();
DWORD 邮寄选项卡();
bool 是否输入();