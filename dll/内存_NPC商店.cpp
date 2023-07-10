#include "内存_NPC商店.h"
void NPC商店::Fun_ShopBuyAddItem(int dItemIndex, int dum)//索引从1开始 先调用添加
{
	INT64 addr_1 = R_QW(游戏模块 + gb_ShopBase);
	int dTotal = R_DW(addr_1 + go_ShopBuyItemListStart + 8);
	if (dTotal <= 10)//最多添加10个
	{
		MainUniversalCALL4(addr_1, dItemIndex, dum, 0, 游戏模块 + gc_ShopBuyAddItem);

	}

}

void NPC商店::Fub_ShopBuyItemClick()//点击购买按钮
{

	INT64 addr_1 = R_QW(游戏模块 + gb_ShopBase);
	if (R_DW(addr_1 + go_ShopBuyItemState) == 0)//状态
	{
		if (R_DW(addr_1 + go_ShopBuyItemListStart + 8))//判断添加物品
		{
			UCHAR dInfoAddr[0x1000] = { 0 };
			MainUniversalCALL2((ULONG_PTR)dInfoAddr, 0, 游戏模块 + gc_ShopBuyItem);
		}

	}
}

BOOL bCheckItemJob(DWORD dJobId, DWORD dItemResId)
{
	return (BOOL)MainUniversalCALL2_Ret(dItemResId, dJobId, 游戏模块 + gc_ItemJobCheck);
}

int  getMoneyType(int cl) {
	if (cl <= 1) {
		return 1;
	}
	else {
		if (cl == 6) {
			return 10;
		}
		else {
			if (cl == 7) {
				return 2;
			}
			else {
				if (cl != 9) {
					return 0;
				}
				else {
					return 8;
				}
			}
		}
	}
}

void NPC商店::get_ShopItemList(vector<Inventoryinfo_>& vsk)
{
	vsk.clear();
	Inventoryinfo_ temp;
	__int64 addr_1 = R_QW(游戏模块 + gb_ShopBase);
	DWORD dOffest = go_ShopListStart + 4;
	long dtotal = R_DW(addr_1 + dOffest + 0x10 + 0x18);
	__int64 dKeyAddr = R_QW(addr_1 + dOffest + 0x20);
	if (!dKeyAddr)
	{
		dKeyAddr = addr_1 + dOffest + 0x10;
	}
	long dKeyValue = R_DW(addr_1 + dOffest + 0x10);
	__int64 objStartAddr = R_QW(addr_1 + dOffest);
	for (size_t i = 0; i < dtotal; i++)
	{
		long dKeyValue = R_DW(dKeyAddr + (i / 0x20) * 4);
		DWORD dNum = i % 0x20;
		DWORD dCheck = (dKeyValue >> dNum) & 1;
		if (dCheck)
		{
			DWORD dIndex = R_BYTE(objStartAddr + i * go_ShopListSize);
			DWORD dResId = R_DW(objStartAddr + i * go_ShopListSize + 0xC);
			DWORD dPriceType = R_DW(objStartAddr + i * go_ShopListSize + 0x1C);
			DWORD dPrice = R_DW(objStartAddr + i * go_ShopListSize + 0x24);
			INT64 dResAddr = getItemResAddrById(dResId);
			INT64 dNameAddr = R_QW(dResAddr + 0x10);
			DWORD dSlotIndex = R_DW(dResAddr + 0x114);
			DWORD dpinzhi = R_DW(dResAddr + 0x118);//更新-0227
			CString csName = L"空";
			if (dNameAddr)
			{
				csName = R_CString(dNameAddr);
			}
			temp.dindex = dIndex;
			temp.ItemResId = dResId;
			temp.dPrice = dPrice;
			temp.dItemResAddr = dResAddr;
			temp.颜色 = dpinzhi;
			vsk.push_back(temp);
			MyTrace(L"索引%d 资源ID %X %s 类型%X 品质 %d 价格%d", dIndex, dResId, csName, dSlotIndex, dpinzhi, dPrice);
		}
	}
}

bool 判断存在需修理的装备()
{
	vector<Equipinfo_>vsk;
	背包::get_EquipList(vsk);
	for (size_t i = 0; i < vsk.size(); i++)
	{

		double 耐久百分比 = ((double)vsk[i].耐久度.当前耐久度 / (double)vsk[i].耐久度.最大耐久度) * 100;
		//MyTrace(L"装备名称 %s 当前耐久:%d/%d", vsk[i].ItemName, vsk[i].耐久度.当前耐久度, vsk[i].耐久度.最大耐久度);
		if (耐久百分比 <= 60)
		{

			return true;
		}
	}
	return false;
}
bool NPC商店::修理装备()
{
	if (判断存在需修理的装备())
	{
		objInfo_ 修理工 = 环境::取指定类型NPC(L"tip.name.npcfunction_repair");
		if (修理工.dResId != 0)
		{
			功能::到指定地点找NPC修理装备(地图::取当前大陆ID(), 地图::取地图ID(), 修理工.坐标.x, 修理工.坐标.y, 修理工.坐标.z, 50, 修理工.dResId);
			return true;
		}

	}
	return false;
}

bool NPC商店::补充药水()
{
	DWORD 等级 = 本人::取角色信息().等级;
	if (等级 >= 40)
	{
		if (背包::返回指定物品数量(0x2E63E) < 100)
		{
			objInfo_ 药品商人 = 环境::取指定类型NPC(L"tip.name.npcfunction_shop_potion");
			if (药品商人.dResId != 0)
			{
				if (背包::取银币数() > 12000)
				{
					功能::到指定地点找NPC买物品(地图::取当前大陆ID(), 地图::取地图ID(), 药品商人.坐标.x, 药品商人.坐标.y, 药品商人.坐标.z, 药品商人.dResId, 200, 0x2E63E, 200);
					return true;
				}

			}
		}
		return false;
	}
	if (等级 >= 28 && 等级 <= 40)
	{
		if (背包::返回指定物品数量(0x2E63D) < 50)
		{
			objInfo_ 药品商人 = 环境::取指定类型NPC(L"tip.name.npcfunction_shop_potion");
			if (药品商人.dResId != 0)
			{
				if (背包::取银币数() > 3500)
				{
					功能::到指定地点找NPC买物品(地图::取当前大陆ID(), 地图::取地图ID(), 药品商人.坐标.x, 药品商人.坐标.y, 药品商人.坐标.z, 药品商人.dResId, 200, 0x2E63D, 100);
					return true;
				}

			}
		}
	}
	return false;
}
//bool NPC商店::物品存仓()
//{
//	objInfo_ 库管 = 环境::取指定类型NPC(L"tip.name.npcfunction_stash");
//	if (库管.dResId != 0)
//	{
//
//	}
//
//}

void NPC商店::Fun_BarterShopExchange(DWORD dItemIndex, DWORD dNum)//交换物品
{

	INT64 addr_1 = R_QW(游戏模块 + gb_ShopBase);

	//UCHAR dInfoAddr[0x1000] = { 0 };
	if (!IsBadReadPtr((void*)addr_1, sizeof(addr_1)))
	{
		MainUniversalCALL4(addr_1, dItemIndex, dNum, 0, 游戏模块 + gc_BarterShopExchange);
	}


}