#pragma once
#include "pch.h"
class NPC�̵�
{
public:
	static void Fun_ShopBuyAddItem(int dItemIndex, int dum);
	static void Fub_ShopBuyItemClick();
	static void get_ShopItemList(vector<Inventoryinfo_>& vsk);
	static bool ����װ��();
	static bool ����ҩˮ();
	static bool ��Ʒ���();
	static void Fun_BarterShopExchange(DWORD dItemIndex, DWORD dNum);
	//static void get_ShopItemList();
};

