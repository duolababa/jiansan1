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

void NPC商店::领取箱子(DWORD ID)
{
	INT64 addr_1 = R_QW(游戏模块 + 商城箱子rcx);


	MainUniversalCALL4(addr_1, ID, 0, 0, 游戏模块 + 打开箱子写入基址);
}



DWORD NPC商店::查询钻石数量()
{
	INT64 rcx = 游戏模块 + 钻石rcx;

	DWORD num = R_DW(rcx + g_钻石);
	INT64 addr = rcx + g_钻石 + 2;
	if (num > 6)
	{
		num = 5;

	}
	//MyTrace(L"子数%d", num);
		for (size_t i = 0; i < num; i++)
		{
			double c=R_double(addr+i*0x11);
			int b = static_cast<int>(c);
			//MyTrace(L"子数量%d", b);
			if (b!= 0)
			{
				MyTrace(L"子数量%d", b);
				return c;
			}

		}
		return 0;

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


void NPC商店::funshop(DWORD ID,DWORD 次数)
{
	//	vector<Inventoryinfo_>vsk;
	vector<商城信息_> vsk;
	DWORD W=0;
		NPC商店::shoppingmall(vsk);
		for (size_t i = 0; i < vsk.size(); i++)
		{

			if (ID == vsk[i].WearId)
			{
				

				if (UI功能::窗口反馈文本().Find(L"Do you want to purchase") != -1)
				{
					W = W + 1;
					UI功能::内存按键1(g_ENTER);
					Sleep(2222);
				}

				INT64 rcx = R_QW(游戏模块 + 基址_个人_遍历);
				INT64 rdx = 游戏模块 + 打开商品rdx;

				MainUniversalCALL6(rcx, rdx, ID, 0, vsk[i].ItemId, 0, 游戏模块 + 打开商品call);
				Sleep(2222);


				INT64 rcx1;
				bool 是否打开 = UI功能::寻找打开窗口("root1.arkui.windowCanvas.cashShopBuyWnd", rcx1);
				if (rcx != 0)
				{
					DWORD dResId = R_DW(rcx1 + 偏移_UI_显示);
					if (dResId == 1)
					{
						MainUniversalCALL4(rcx1, 0, 0, 0, 游戏模块 + 购买商品箱子写入基址);
						Sleep(4000);
					}


					if (UI功能::窗口反馈文本().Find(L"Do you want to purchase") != -1)
					{
						W = W + 1;
						UI功能::内存按键1(g_ENTER);
						Sleep(5000);
					}



				}





			}
			
			if (W >= 次数)
			{
				break;
			}


		}



}
void NPC商店::openshop(vector<商城信息_>& vsk)
{
	vsk.clear();

	INT64 addr_1 = R_QW(游戏模块 + 商城箱子rcx);
	INT64 addr = R_QW(addr_1 + g_商城遍历);
	DWORD dtotal = R_DW(addr_1 + g_商城遍历 + 8);
	for (size_t i = 0; i < dtotal; i++)
	{
		DWORD ID = R_DW(addr + i * g_商城循环);
		商城信息_ temp;
		temp.WearId = ID;

		INT64 dNameAddr = addr + i * g_商城循环 + 0x78;
		CString csName = L"空";
		if (dNameAddr)
		{
			csName = R_CString(dNameAddr);
			temp.CName = csName;
		}
		vsk.push_back(temp);

	}



}


void NPC商店::shoppingmall(vector<商城信息_>& vsk)
{
	vsk.clear();

	INT64 addr_1 = R_QW(游戏模块 + 商城箱子rcx);
	INT64 addr = R_QW(addr_1 + g_商城遍历x);
	DWORD dtotal = R_DW(addr_1 + g_商城遍历x+8);


	if (dtotal < 1)
	{
		UI功能::Fun_UiShowCtrl(190);
		Sleep(9000);
		 addr_1 = R_QW(游戏模块 + 商城箱子rcx);
		 addr = R_QW(addr_1 + g_商城遍历x);
		 dtotal = R_DW(addr_1 + g_商城遍历x + 8);
	}
	//MyTrace(L"数量%d", dtotal);
	if (dtotal > 1 && dtotal < 100)
	{

		for (size_t i = 0; i < dtotal; i++)
		{
			INT64 ItemId = addr + i * 0x28;
			DWORD dNum = R_DW(addr + i * 0x28 + 0x18);
			if (dNum != 0)
			{
				INT64 addr_shop = R_QW(addr + i * 0x28 + 0x10);
				
				for (size_t b = 0; b < dNum; b++)
				{
					商城信息_ temp;
					temp.ItemId = ItemId;
					temp.WearId = R_DW(addr_shop + b * 0x10);
					//MyTrace(L"ID%d", temp.ItemId);
				/*	INT64 dItemResAddr = getItemResAddrById(temp.WearId);
					MyTrace(L"dItemResAddr0x%I64x", dItemResAddr);
					INT64 dNameAddr = R_QW(dItemResAddr + 0x10);
					CString csName = L"空";
					if (dNameAddr)
					{
						csName = R_CString(dNameAddr);
						temp.CName = csName;
					}*/



					vsk.push_back(temp);
			//	MyTrace(L" 资源ID%d 批次0x%I64x", temp.WearId, temp.ItemId);
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
	//MyTrace(L"商店OBJ 0x%I64X", objStartAddr);
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
			//MyTrace(L"索引%d 资源ID %X %s 类型%X 品质 %d 价格%d", dIndex, dResId, csName, dSlotIndex, dpinzhi, dPrice);
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
		////MyTrace(L"装备名称 %s 当前耐久:%d/%d", vsk[i].ItemName, vsk[i].耐久度.当前耐久度, vsk[i].耐久度.最大耐久度);
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
	if (addr_1 > 1)
	{
		MainUniversalCALL4(addr_1, dItemIndex, dNum, 1, 游戏模块 + gc_BarterShopExchange);
	}

	


}

DWORD 拍卖::查询金额call()
{
	INT64 rcx = R_QW(游戏模块 + 基址_拍卖_获取遍历对象rcx);

	INT64 ret = MainUniversalCALL4_Ret(rcx, 0xD8, 0, 0, 游戏模块 + 交易金额call);

	INT64 rcx1 = R_QW(ret + 0x10);

	//MyTrace(L"rcx1 0x%I64X", rcx1);


	DWORD x = R_DW(rcx1 +g_市场最近价格+4);
		return x;

}

void 开始邮寄()
{
	INT64 rcx = 0;
	bool 是否打开 = UI功能::寻找打开窗口("root1.arkui.windowCanvas.mailWnd", rcx);
	if (rcx > 1)
	{
	MainUniversalCALL4(rcx, 0, 0, 0, 游戏模块 + send邮寄call);
	}
	
	
}
DWORD 邮寄选项卡()
{
	INT64 rcx = R_QW(游戏模块 + gb_ExpressMailList);
	DWORD rcx1 = R_DW(rcx + 邮寄选项);//E8 ?? ?? ?? ?? 85 FF 0F 88 ?? ?? ?? ?? 83 FF ?? 7E ?? 83 FF ?? 0F 85 ?? ?? ?? ?? 8D 57 ?? 48 8B CB +0 进CALL


	return rcx1;

	//INT64 call = 游戏模块 + 邮寄选项卡call;
	//MainUniversalCALL4(rcx, ID, 0, 0, call);
}

bool 是否输入()
{
	DWORD rcx = R_BYTE(游戏模块 + 光标是否激活);
		if (rcx != 0)
		{
			return 1;
		}
		return 0;
}




void 输入邮寄名称(CString name)
{
		INT64 call = 游戏模块 + 邮寄输入昵称call;
		INT64 rcx = R_QW(游戏模块 + gb_ExpressMailList);
		temp名称指针 cStringClassPtr2;
		cStringClassPtr2.名称obj = INT64(name.GetBuffer());
		cStringClassPtr2.长度 = name.GetLength() + 1;
	//	INT64 rcx1 = 0;
	//	bool 是否打开 = UI功能::寻找打开窗口("root1.arkui.windowCanvas.mailWnd", rcx1);

		//if (rcx1 > 1)
		//{
		//	W_QW(rcx1+0x578, (UINT64)&cStringClassPtr2);
		//}

		MainUniversalCALL4(rcx, (UINT64)&cStringClassPtr2, 0, 0, call);

}
void 输入邮寄物品(DWORD ID, DWORD 数量,DWORD 物品位置)
{
	INT64 call = 游戏模块 + 邮寄添加物品call;
	//INT64 call1 = 游戏模块 + 邮寄添加物品call1;//资源物品
	INT64 rcx = R_QW(游戏模块 + gb_ExpressMailList);

	if (物品位置 != 0)
	{

		MainUniversalCALL6(rcx,0xFFFFFFFF,ID, 数量,1,0, call);
	}
	else
	{

		vector<Inventoryinfo_> vsk2;
		背包::get_InventoryItemList(vsk2);
		DWORD a = 0;

		for (size_t i = 0; i < vsk2.size(); i++)
		{
			if (vsk2[i].ItemResId == ID && vsk2[i].dNum >= 数量)
			{
				MainUniversalCALL6(rcx, vsk2[i].dindex, ID, 数量, 1, 0, call);

			}

	//MyTrace(L"位置%d  物品ID 0x%I64X 资源ID  0x%I64X 数量%d  箱子类型%d 耐久%d  名称 %s 物品等级%d 物品对象0x%I64X \r\n", vsk2[i].dindex, vsk2[i].ItemId, vsk2[i].ItemResId, vsk2[i].dNum, vsk2[i].dSlotIndex, vsk2[i].耐久度.当前耐久度, vsk2[i].ItemName, vsk2[i].dLev, vsk2[i].dItemResAddr);
		
		}



	}




}





void  拍卖::自动拍卖(DWORD ID, DWORD 总量, DWORD 价格, INT64 物品ID1)
{
	INT64 rcx = R_QW(游戏模块 + 登记rcx);
	INT64 rdx = rcx+ g_市场拍卖rdx;
	INT64 call = 游戏模块 + 拍卖写入基址;
	W_QW(rdx, ID);
	if (物品ID1 > 1)
	{
		W_QW(rdx+8, 物品ID1);
	}

	W_DW(rdx +  0x10, 总量);
	W_DW(rdx + 0x14, 价格);
	if (物品ID1 == 0)
	{
		W_DW(rdx + 0x1C, 0);
		W_DW(rdx+0x1D ,1);
	}



MainUniversalCALL2(rcx, rdx, call);
}

bool 拍卖::拍卖行是否打开()
{
	INT64 rcx = 0;
	bool 是否打开 = UI功能::寻找打开窗口("root1.arkui.windowCanvas.exchangeShopWnd", rcx);
	if (rcx >= 1)
	{
		DWORD dResId = R_DW(rcx + 偏移_UI_显示);
		if (dResId == 1)
		{
			return 1;
		}


	}

	return 0;
}







void 拍卖::登记拍卖(DWORD ID, DWORD ID1)
{

	INT64 call = 游戏模块 + 登记call;
	INT64 rcx = 0;

	if (ID1 == 1)
	{

	}
	else
	{
		bool 是否打开 = UI功能::寻找打开窗口("root1.arkui.windowCanvas.exchangeShopWnd", rcx);
		if (rcx >= 1)
		{
			MainUniversalCALL2(R_QW(rcx + g_登记物品), ID, call);

		}
	}

	

	//if (ID1 == 1)
	//{
	//	MainUniversalCALL4(addr_1, ID, 1, 0, call);
	//}
	//else
	//{
	//	MainUniversalCALL4(addr_1, ID, 0, 0, call);

	//}


}