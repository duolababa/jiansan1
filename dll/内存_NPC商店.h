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
	//static void get_ShopItemList();
};

