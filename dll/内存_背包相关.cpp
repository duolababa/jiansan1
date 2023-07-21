#include "内存_背包相关.h"
int getEquipWearArg(int dSlotIndex)
{
	INT dTemp = 0;
	INT64 dRet = 30;
	dTemp = 0x64 * (dSlotIndex / 0x64);
	if (dTemp == 0x2774)
	{
		return 0;
	}
	else if (dTemp == 0x16058)
	{
		return 12;
	}
	else if (dSlotIndex > 0x2969)
	{
		if (dSlotIndex <= 0x15FF5)
		{
			if (dSlotIndex == 0x15FF5)
			{
				return 13;
			}
			else
			{
				if (dSlotIndex - 0x296A == 0)
				{
					return 28;
				}
				else if (dSlotIndex - 0x296A == 1)
				{
					return 29;
				}
			}
		}
		else
		{
			if (dSlotIndex - 0x15FF6 > 5)
			{
				return 30;
			}
			switch (dSlotIndex)
			{
			case 0x15FF6:
			case 0x15FFB:
				return 14;
				break;
			case 0x15FF7:
				return 15;
				break;
			case 0x15FF8:
				return 17;
				break;
			case 0x15FF9:
				return 18;
				break;
			case 0x15FFA:
				return 16;
				break;
			}
			return 30;

		}
	}
	else
	{
		if (dSlotIndex == 0x2969)
		{
			return 27;
		}
		else
		{
			if (dSlotIndex > 0x28A1)
			{
				dTemp = dSlotIndex - 0x28A2;
				if (dTemp == 0)
				{
					return 7;
				}
				dTemp = dTemp - 1;
				if (dTemp == 0)
				{
					return 9;
				}
				dTemp = dTemp - 1;
				if (dTemp == 0)
				{
					return 26;
				}
				if (dTemp == 0x60)
				{
					return 11;
				}
			}
			else
			{
				if (dSlotIndex == 0x28A1)
				{
					return 6;
				}
				dTemp = dSlotIndex - 0x27D9;
				switch (dTemp)
				{
				case 0:
					return 1;
					break;
				case 1:
					return 2;
					break;
				case 2:
					return 3;
					break;
				case 3:
					return 4;
					break;
				case 4:
					return 5;
					break;
				}
			}

		}
	}
	return 30;
}
void 背包::get_InventoryItemList(vector<Inventoryinfo_>& vsk)
{
	vsk.clear();
	Inventoryinfo_ temp;
	INT64 addr_1 = R_QW(游戏模块 + gb_ShortKey);
	INT64 addr_2 = R_QW(addr_1 + go_AttrList_off1/*0x94*/);
	DWORD dSize = go_bag_dSize;//0x1E0;
	//DWORD dSize = 1744;//0x1E0;
	INT64 dStart = addr_2 + 偏移_背包_物品遍历数组头;//0x17DD8;//0x690;
	//INT64 dStart = addr_2 + 0x55A2C ;//0x17DD8;//0x690;
	for (size_t i = 0; i < 100; i++)
	{
		INT64 dItemId = R_QW(dStart + i * dSize + 偏移_背包_物品id);
		if (dItemId)
		{
			DWORD dItmeResId = R_DW(dStart + i * dSize + 偏移_背包_物品resid);
			DWORD dItemDur = R_DW(dStart + i * dSize + 0x14);
			INT64 dItemResAddr = getItemResAddrById(dItmeResId);
			//MyTrace(L"dItemResAddr");
			INT64 dNameAddr = R_QW(dItemResAddr + 0x10);
			DWORD dSlotIndex = R_DW(dItemResAddr + 0x8C);//更新-2023年7月14日 00:23:58
			DWORD dpinzhi = R_DW(dItemResAddr + 0x90);//更新-2023年7月14日 00:24:01
			DWORD 物品等级 = R_W(dItemResAddr + 偏移_背包_物品等级);
			DWORD 强化等级 = R_W(dStart + i * dSize + go_ItemGradeLev) - 100;
			int dBoxType = 0;
			if (dSlotIndex == 0x791A)
			{
				//dBoxType = getItemBoxType(dItmeResId);//资源未加载容易卡，先注释
			}
			CString csName = L"空";
			if (dNameAddr)
			{
				//string sName = UnicodeToAnsi(R_CString(dNameAddr));
				//csName = GetName(dNameAddr);
				//DbgPrintf_Mine("sName %s",sName);
				//csName = CString(sName.c_str());
				csName = R_CString(dNameAddr);
			}
			DWORD dNum = R_DW(dStart + i * dSize + 偏移_背包_物品数量);
			temp.BoxType = dBoxType;
			temp.dindex = i;
			temp.dNum = dNum;
			temp.ItemId = dItemId;
			temp.ItemResId = dItmeResId;
			temp.ItemName = csName;
			temp.ItemObj = dStart + i * dSize;
			temp.WearId = getEquipWearArg(dSlotIndex);
			temp.dItemResAddr = dItemResAddr;
			temp.dSlotIndex = dSlotIndex;
			temp.颜色 = dpinzhi;
			temp.dLev = 物品等级;
			temp.dUpgradeLev = 强化等级;
			耐久度_ 临时耐久度;
			if (temp.WearId != 30)
			{
				临时耐久度.当前耐久度 = double(R_DW(dStart + i * dSize + 偏移_背包_当前耐久度) + 99) / 100;
				临时耐久度.最大耐久度 = double(R_DW(dItemResAddr + 偏移_背包_最大耐久度) + 99) / 100;
			}
			temp.耐久度 = 临时耐久度;
			vsk.push_back(temp);
			wchar_t buf[MAX_PATH];
			//swprintf(buf, L"位置%X 地址0x%I64X 物品ID 0x%I64X 资源ID %X 地址0x%I64X 数量%d %s 槽位%X 穿戴参数%d 箱子类型%d 耐久%d/%d\r\n", i, dStart + i * dSize, dItemId, dItmeResId, dItemResAddr, dNum, csName, dSlotIndex, getEquipWearArg(dSlotIndex), dBoxType, temp.耐久度.当前耐久度, temp.耐久度.最大耐久度);
			//MyTrace(buf);
			//g_String.Insert(g_String.GetLength(), buf);
		}
	}
}

void 背包::get_EquipList(vector<Equipinfo_>& vsk)
{
	vsk.clear();
	Equipinfo_ temp;
	INT64 addr_1 = R_QW(游戏模块 + gb_ShortKey);
	INT64 addr_2 = R_QW(addr_1 + go_AttrList_off1/*0x94*/);
	DWORD dSize = go_bag_dSize;//0x1E0;
	//DWORD dSize = 1744;//0x1E0;
	INT64 dStart = addr_2 + 偏移_背包_装备遍历数组头;//0x17DD8;//0x690;
	//INT64 dStart = addr_2 + 0x55A2C ;//0x17DD8;//0x690;
	for (DWORD i = 0; i < 15; i++)
	{
		INT64 dItemId = R_QW(dStart + i * dSize + 偏移_背包_物品id);
		if (dItemId)
		{
			DWORD dItmeResId = R_DW(dStart + i * dSize + 偏移_背包_物品resid);
			INT64 dItemResAddr = getItemResAddrById(dItmeResId);
			INT64 dNameAddr = R_QW(dItemResAddr + 0x10);
			DWORD dSlotIndex = R_DW(dItemResAddr + 0x8C);//更新-2023年7月14日 00:23:58
			DWORD dpinzhi = R_DW(dItemResAddr + 0x90);//更新-2023年7月14日 00:24:01
			DWORD 物品等级 = R_W(dItemResAddr + 偏移_背包_物品等级);
			DWORD 强化等级 = R_W(dStart + i * dSize + go_ItemGradeLev) - 100;
			CString csName = L"空";
			if (dNameAddr)
			{
				string sName = UnicodeToAnsi(R_CString(dNameAddr));
				csName = CString(sName.c_str());
			}
			temp.ItemId = dItemId;
			temp.ItemName = csName;
			temp.ItemObj = dStart + i * dSize;
			temp.Type = i;
			temp.WearId = getEquipWearArg(dSlotIndex);
			temp.dItemResAddr = dItemResAddr;
			temp.颜色 = dpinzhi;
			temp.dLev = 物品等级;
			temp.dUpgradeLev = 强化等级;
			耐久度_ 临时耐久度;
			临时耐久度.当前耐久度 = double(R_DW(dStart + i * dSize + 偏移_背包_当前耐久度) + 99) / 100;
			临时耐久度.最大耐久度 = double(R_DW(dItemResAddr + 偏移_背包_最大耐久度) + 99) / 100;
			temp.耐久度 = 临时耐久度;
			vsk.push_back(temp);
			wchar_t buf[MAX_PATH];
			//swprintf(buf, L"品质 %d wearid %d 位置%X 地址0x%I64X 物品ID 0x%I64X 资源ID %X 地址0x%I64X %s 耐久%d/%d\r\n", dpinzhi, temp.WearId ,i, dStart + i * dSize, dItemId, dItmeResId, dItemResAddr, csName, temp.耐久度.当前耐久度, temp.耐久度.最大耐久度);
			//MyTrace(buf);
			//g_String.Insert(g_String.GetLength(), buf);
		}
	}
}

void 背包::get_UpEquipList(vector<Equipinfo_>& vsk)
{
	vsk.clear();
	Equipinfo_ temp;
	INT64 addr_1 = R_QW(游戏模块 + gb_ShortKey);
	INT64 addr_2 = R_QW(addr_1 + go_AttrList_off1/*0x94*/);
	DWORD dSize = go_bag_dSize;//0x1E0;
	//DWORD dSize = 1744;//0x1E0;
	INT64 dStart = addr_2 + 偏移_背包_装备遍历数组头;//0x17DD8;//0x690;
	//INT64 dStart = addr_2 + 0x55A2C ;//0x17DD8;//0x690;
	for (DWORD i = 0; i < 6; i++)
	{
		INT64 dItemId = R_QW(dStart + i * dSize + 偏移_背包_物品id);
		if (dItemId)
		{
			DWORD dItmeResId = R_DW(dStart + i * dSize + 偏移_背包_物品resid);
			INT64 dItemResAddr = getItemResAddrById(dItmeResId);
			INT64 dNameAddr = R_QW(dItemResAddr + 0x10);
			DWORD dSlotIndex = R_DW(dItemResAddr + 0x8C);//更新-2023年7月14日 00:23:58
			DWORD dpinzhi = R_DW(dItemResAddr + 0x90);//更新-2023年7月14日 00:24:01
			DWORD 物品等级 = R_W(dItemResAddr + 偏移_背包_物品等级);
			DWORD 强化等级 = R_W(dStart + i * dSize + go_ItemGradeLev) - 100;
			CString csName = L"空";
			if (dNameAddr)
			{
				string sName = UnicodeToAnsi(R_CString(dNameAddr));
				csName = CString(sName.c_str());
			}
			temp.ItemId = dItemId;
			temp.ItemName = csName;
			temp.ItemObj = dStart + i * dSize;
			temp.Type = i;
			temp.WearId = getEquipWearArg(dSlotIndex);
			temp.dItemResAddr = dItemResAddr;
			temp.颜色 = dpinzhi;
			temp.dLev = 物品等级;
			temp.dUpgradeLev = 强化等级;
			耐久度_ 临时耐久度;
			临时耐久度.当前耐久度 = double(R_DW(dStart + i * dSize + 偏移_背包_当前耐久度) + 99) / 100;
			临时耐久度.最大耐久度 = double(R_DW(dItemResAddr + 偏移_背包_最大耐久度) + 99) / 100;
			temp.耐久度 = 临时耐久度;
			vsk.push_back(temp);
			wchar_t buf[MAX_PATH];
			//swprintf(buf, L"品质 %d wearid %d 位置%X 地址0x%I64X 物品ID 0x%I64X 资源ID %X 地址0x%I64X %s 耐久%d/%d\r\n", dpinzhi, temp.WearId ,i, dStart + i * dSize, dItemId, dItmeResId, dItemResAddr, csName, temp.耐久度.当前耐久度, temp.耐久度.最大耐久度);
			//MyTrace(buf);
			//g_String.Insert(g_String.GetLength(), buf);
		}
	}
}
void 背包::get_LifeToolList(vector<Equipinfo_>& vsk)  //生活装备
{
	vsk.clear();
	Equipinfo_ temp;
	INT64 addr_1 = R_QW(游戏模块 + gb_ShortKey);
	INT64 addr_2 = R_QW(addr_1 + go_AttrList_off1/*0x94*/);
	DWORD dSize = go_bag_dSize;//0x1E0;
	//DWORD dSize = 1744;//0x1E0;
	INT64 dStart = addr_2 + 偏移_背包_生活装备遍历数组头;//0x17DD8;//0x690;
	//INT64 dStart = addr_2 + 0x55A2C ;//0x17DD8;//0x690;
	for (DWORD i = 0; i < 6; i++)
	{
		INT64 dItemId = R_QW(dStart + i * dSize + 偏移_背包_物品id);
		if (dItemId)
		{
			DWORD dItmeResId = R_DW(dStart + i * dSize + 偏移_背包_物品resid);
			INT64 dItemResAddr = getItemResAddrById(dItmeResId);
			INT64 dNameAddr = R_QW(dItemResAddr + 0x10);
			DWORD dSlotIndex = R_DW(dItemResAddr + 0x8C);//更新-2023年7月14日 00:23:58
			DWORD dpinzhi = R_DW(dItemResAddr + 0x90);//更新-2023年7月14日 00:24:01
			CString csName = L"空";
			if (dNameAddr)
			{
				string sName = UnicodeToAnsi(R_CString(dNameAddr));
				csName = CString(sName.c_str());
			}
			temp.ItemId = dItemId;
			temp.ItemName = csName;
			temp.ItemObj = dStart + i * dSize;
			temp.Type = i;
			temp.WearId = getEquipWearArg(dSlotIndex);
			temp.dItemResAddr = dItemResAddr;
			temp.颜色 = dpinzhi;
			耐久度_ 临时耐久度;
			临时耐久度.当前耐久度 = double(R_DW(dStart + i * dSize + 偏移_背包_当前耐久度) + 99) / 100;
			临时耐久度.最大耐久度 = double(R_DW(dItemResAddr + 偏移_背包_最大耐久度) + 99) / 100;
			temp.耐久度 = 临时耐久度;
			vsk.push_back(temp);
			//wchar_t buf[MAX_PATH];
			//swprintf(buf, L"品质 %d wearid %d 位置%X 地址0x%I64X 物品ID 0x%I64X 资源ID %X 地址0x%I64X %s 耐久%d/%d\r\n", dpinzhi, temp.WearId ,i, dStart + i * dSize, dItemId, dItmeResId, dItemResAddr, csName, temp.耐久度.当前耐久度, temp.耐久度.最大耐久度);
			//MyTrace(buf);
			//g_String.Insert(g_String.GetLength(), buf);
		}
	}
}

void 背包::get_cangkuList(vector<Inventoryinfo_>& vsk)
{
	vsk.clear();
	Inventoryinfo_ temp;
	INT64 addr_1 = R_QW(游戏模块 + gb_ShortKey);
	INT64 addr_2 = R_QW(addr_1 + go_AttrList_off1/*0x94*/);
	DWORD dSize = go_bag_dSize;//0x1E0;
							   //DWORD dSize = 1744;//0x1E0;
	INT64 dStart = addr_2 + g_公共仓库索引;//0x17DD8;//0x690;
											//INT64 dStart = addr_2 + 0x55A2C ;//0x17DD8;//0x690;
	for (DWORD i = 0; i < 24; i++)
	{
		INT64 dItemId = R_QW(dStart + i * dSize + 偏移_背包_物品id);
		if (dItemId)
		{
			DWORD dItmeResId = R_DW(dStart + i * dSize + 偏移_背包_物品resid);
			INT64 dItemResAddr = getItemResAddrById(dItmeResId);
			INT64 dNameAddr = R_QW(dItemResAddr + 0x10);
			DWORD dSlotIndex = R_DW(dItemResAddr + 0x8C);//更新-2023年7月14日 00:23:58
			DWORD dpinzhi = R_DW(dItemResAddr + 0x90);//更新-2023年7月14日 00:24:01
			CString csName = L"空";
			if (dNameAddr)
			{
				string sName = UnicodeToAnsi(R_CString(dNameAddr));
				csName = CString(sName.c_str());
			}
			temp.ItemId = dItemId;
			temp.ItemName = csName;
			temp.ItemObj = dStart + i * dSize;
			temp.dindex = i;
			temp.WearId = dSlotIndex;
			temp.dItemResAddr = dItemResAddr;
			temp.颜色 = dpinzhi;
			耐久度_ 临时耐久度;
			临时耐久度.当前耐久度 = double(R_DW(dStart + i * dSize + 偏移_背包_当前耐久度) + 99) / 100;
			临时耐久度.最大耐久度 = double(R_DW(dItemResAddr + 偏移_背包_最大耐久度) + 99) / 100;
			temp.耐久度 = 临时耐久度;
			vsk.push_back(temp);
		/*	wchar_t buf[MAX_PATH];
			swprintf(buf, L"品质 %d wearid %d 位置%X 地址0x%I64X 物品ID 0x%I64X 资源ID %X 地址0x%I64X %s 耐久%d/%d\r\n", dpinzhi, temp.WearId ,i, dStart + i * dSize, dItemId, dItmeResId, dItemResAddr, csName, temp.耐久度.当前耐久度, temp.耐久度.最大耐久度);
			MyTrace(buf);*/
			//g_String.Insert(g_String.GetLength(), buf);
		}
	}


}




Inventoryinfo_ 背包::取单独仓库(CString name)
{


	Inventoryinfo_ temp;
	vector<Inventoryinfo_>vsk;
	背包::get_feicangkuList(vsk);
	name.MakeUpper();

	for (size_t i = 0; i < vsk.size(); i++)
	{
		MyTrace(L"ItemName %s / %s    ItemResId %s/%s ", vsk[i].ItemName, name, CString(常用功能::十进制转十六进制(vsk[i].ItemResId).c_str()), name);
		if (vsk[i].ItemName == name || CString(常用功能::十进制转十六进制(vsk[i].ItemResId).c_str()) == name || vsk[i].WearId == _ttoi(name))
		{
			if (vsk[i].ItemId != 0)
			{

				背包::取仓call(vsk[i].dindex, 0);
				Sleep(1000);
			}
			/*temp = vsk[i];
			break;*/
		}
	}
	return temp;

}


bool 背包::取仓call(DWORD 槽位, DWORD 是否公共仓库)
{
	INT64 rcx = 0;

	bool 是否打开 = UI功能::寻找打开窗口("root1.arkui.windowCanvas.windowGo", rcx);

	if (rcx != 0)
	{
		if (是否公共仓库 != 1)
		{

			DWORD	rdx = 1;
			DWORD	r8 = 3473408 + 槽位;
			DWORD	r9 = 0;

			MainUniversalCALL4(rcx, rdx, r8, r9, 游戏模块 + gc_UnWearEquip);
			return 1;
		}
		else
		{
			DWORD	rdx = 1;
			DWORD	r8 = 3538944 + 槽位;
			DWORD	r9 = 0;
			MainUniversalCALL4(rcx, rdx, r8, r9, 游戏模块 + gc_UnWearEquip);
			return 1;
		}




	}
	return 0;

}


void 背包::get_feicangkuList(vector<Inventoryinfo_>& vsk)
{
	CString temp1;
	vsk.clear();
	Inventoryinfo_ temp;
	INT64 addr_1 = R_QW(游戏模块 + gb_ShortKey);
	INT64 addr_2 = R_QW(addr_1 + go_AttrList_off1/*0x94*/);
	DWORD dSize = go_bag_dSize;//0x1E0;
							   //DWORD dSize = 1744;//0x1E0;
	INT64 dStart = addr_2 + g_背包仓库头;//0x17DD8;//0x690;
									 //INT64 dStart = addr_2 + 0x55A2C ;//0x17DD8;//0x690;
	MyTrace(L"输出:dStart 0x%I64X", dStart);
	for (DWORD i = 0; i < 100; i++)
	{

		INT64 dItemId = R_QW(dStart + i * dSize + 偏移_背包_物品id);
		MyTrace(L"输出:i %d 地址0x%I64X ID %X", i, dStart + i * dSize + 偏移_背包_物品id, dItemId);
		/*	INT64 ace = dStart + i * dSize + 偏移_背包_物品id;
			wchar_t buf[MAX_PATH];

			swprintf(buf, L"品质 %d 地址0x%I64X \r\n", i, ace);*/

			/*
				temp1.Format(L"%d", i);
				DebugPrintf("%s\n", temp1);*/
		if (dItemId)
		{

			DWORD dItmeResId = R_DW(dStart + i * dSize + 偏移_背包_物品resid);
			INT64 dItemResAddr = getItemResAddrById(dItmeResId);
			INT64 dNameAddr = R_QW(dItemResAddr + 0x10);
			DWORD dSlotIndex = R_DW(dItemResAddr + 0x8C);//更新-2023年7月14日 00:23:58
			DWORD dpinzhi = R_DW(dItemResAddr + 0x90);//更新-2023年7月14日 00:24:01
			CString csName = L"空";
			if (dNameAddr)
			{
				string sName = UnicodeToAnsi(R_CString(dNameAddr));
				csName = CString(sName.c_str());
			}
			temp.ItemId = dItemId;
			temp.ItemName = csName;
			temp.ItemObj = dStart + i * dSize;
			//temp. = i;
			temp.ItemResId = dItmeResId;
			temp.WearId = dSlotIndex;
			temp.dItemResAddr = dItemResAddr;
			temp.dindex = i;
			temp.颜色 = dpinzhi;
			耐久度_ 临时耐久度;
			临时耐久度.当前耐久度 = double(R_DW(dStart + i * dSize + 偏移_背包_当前耐久度) + 99) / 100;
			临时耐久度.最大耐久度 = double(R_DW(dItemResAddr + 偏移_背包_最大耐久度) + 99) / 100;
			temp.耐久度 = 临时耐久度;
			vsk.push_back(temp);
			wchar_t buf[MAX_PATH];
			swprintf(buf, L"品质 %d wearid %d 位置%X 地址0x%I64X 物品ID 0x%I64X 资源ID %X 地址0x%I64X %s 耐久%d/%d\r\n", dpinzhi, temp.WearId, i, dStart + i * dSize, dItemId, dItmeResId, dItemResAddr, csName, temp.耐久度.当前耐久度, temp.耐久度.最大耐久度);
			MyTrace(buf);
			//g_String.Insert(g_String.GetLength(), buf);
		}
	}



}



Inventoryinfo_ 背包::取公共仓库(CString name)



//INT64 ItemObj;
//INT64 ItemId = 0;
//CString ItemName;
//DWORD Type;
//INT64 dItemResAddr;
//耐久度_ 耐久度;
//DWORD 物品等级 = 0;
//DWORD WearId = 0;
//DWORD 颜色 = 0;
//DWORD dLev = 0;
//DWORD dUpgradeLev = 0;   std::string str((LPCTSTR)cstr);

{
	Inventoryinfo_ temp;
	vector<Inventoryinfo_>vsk;
	背包::get_cangkuList(vsk);
	name.MakeUpper();

	for (size_t i = 0; i < vsk.size(); i++) {

		if (vsk[i].ItemName == name || CString(常用功能::十进制转十六进制(vsk[i].ItemId).c_str()) == name || vsk[i].WearId == _ttoi(name))
		{
			if (vsk[i].ItemId != 0)
			{

				背包::取仓call(vsk[i].dindex, 1);
				Sleep(1000);
			}
			/*temp = vsk[i];
			break;*/
		}
	}
	return temp;

}










bool 背包::指定位置生活工具是否已装备(DWORD 槽位)//0 采集工具 1 伐木工具 2 采矿工具 3 狩猎工具 4 钓鱼工具 5 考古工具
{
	vector<Equipinfo_>vsk;
	背包::get_LifeToolList(vsk);
	for (size_t i = 0; i < vsk.size(); i++)
	{
		if (vsk[i].Type == 槽位)
		{
			return true;
		}
	}
	return false;
}
Equipinfo_ 背包::get_EquipInfobyIndex(DWORD type)
{
	Equipinfo_ temp;
	vector<Equipinfo_>vsk;
	背包::get_EquipList(vsk);
	for (size_t i = 0; i < vsk.size(); i++)
	{
		if (vsk[i].Type == type)
		{
			temp = vsk[i];
			break;
		}
	}
	return temp;

}
DWORD 背包::取金币数()
{

	INT64 局_rcx = R_QW(游戏模块 + 基址_背包_遍历) + 288;
	DWORD 局_数量 = R_DW(局_rcx + 32);
	return 局_数量;
}
DWORD 背包::取银币数()
{

	INT64 局_rcx = R_QW(游戏模块 + 基址_背包_遍历) + 288;
	DWORD 局_数量 = R_DW(局_rcx + 2);
	return 局_数量;
}
DWORD 背包::取复活币数()
{

	INT64 局_rcx = R_QW(游戏模块 + 基址_背包_遍历) + 288;
	DWORD 局_数量 = R_DW(局_rcx + 0x43);
	//MyTrace(L"局_取复活币数 %d", 局_数量);
	return 局_数量;
}
INT64 背包::getMoneyNumByType(int dMoneyType)//A 海盗币
{
	INT64 dstart = R_QW(游戏模块 + gb_AttrList) + go_RoleMoneyListStart;
	return MainUniversalCALL4_Ret(dstart, dMoneyType, 1, 0, 游戏模块 + gc_GetMoneyValue);

}
void 背包::维修装备(DWORD 参_修理类型)
{
	INT64 局_rcx = R_QW(游戏模块 + 基址_背包_修理rcx);
	INT64 局_call = 游戏模块 + 基址_背包_修理call;
	if (局_rcx)
	{
		MainUniversalCALL4(局_rcx, 参_修理类型, 0x19, 0, 局_call);
	}
}

void 背包::使用任务物品(DWORD 格子数)
{

	INT64 局_使用物品call = 游戏模块 + 基址_背包_使用物品call;
	//INT64 局_使用物品call_rcx = 游戏模块 + 基址_背包_使用物品call_rcx;
	//INT64 局_Rcx = R_QW(游戏模块 + 基址_个人_遍历);
	DWORD 局_R8 = 327680 | 格子数;
	INT64 返回rax = UI功能::getUiObjById(0x1A);
	if (返回rax)
	{
		MainUniversalCALL4(返回rax, 1, 局_R8, 0, 局_使用物品call);
	}
}

void 背包::使用物品(DWORD 格子数)
{
	INT64 局_使用物品call = 游戏模块 + 基址_背包_使用物品call;
	//INT64 局_使用物品call_rcx = 游戏模块 + 基址_背包_使用物品call_rcx;
	//INT64 局_Rcx = R_QW(游戏模块 + 基址_个人_遍历);
	DWORD 局_R8 = 262144 | 格子数;
	INT64 返回rax = UI功能::getUiObjById(0x1A);
	if (返回rax)
	{
		MainUniversalCALL4(返回rax, 1, 局_R8, 0, 局_使用物品call);
	}

}


DWORD 背包::坐骑遍历()
{
	vector<DWORD>vsk;
	vsk.clear();
	INT64 b = R_QW(R_QW(游戏模块 + gb_AttrList)+0xE4);
	DWORD dtotal= R_DW(b + g_坐骑); 
	DWORD C = g_坐骑 - 8;
	INT64 跟 = R_QW(b + C);
	DWORD ID = 0;
	跟 = 跟 + g_坐骑_index单;
	//MyTrace(L"推荐装备槽位0x%I64X \r\n", 跟);
	if (dtotal >= 1)
	{
		for (DWORD i = 0; i < dtotal; i++)
		{
			ID = R_DW(跟 + i*g_坐骑_叠加单);
			if (ID > 1)
			{
				//MyTrace(L"ID 0x%I64X \r\n", ID);
				DWORD rax = 0;
				rax =本人::是否可以骑马call(ID);
				if (rax == 1)
				{
					vsk.push_back(ID);
				}

			
			}

		}
	}
	if (vsk.size() >= 1)
	{
		int randomNumber = rand() % vsk.size() + 1;
	//	MyTrace(L"随机数 0x%I64X \r\n", vsk[randomNumber - 1]);
		return vsk[randomNumber-1];
	}
	return 0;



}

void 背包::丢弃物品call(INT64 ItemId)
{

	INT64 rcx = 游戏模块 + 采集物品数量;

	MainUniversalCALL4(rcx, ItemId, 0, 0, 游戏模块 + 丢弃写入基址);

}


void 背包::右键物品(DWORD 格子数)
{
	INT64 局_使用物品call = 游戏模块 + 基址_背包_使用物品call2;
	//INT64 局_使用物品call_rcx = 游戏模块 + 基址_背包_使用物品call_rcx;
	//INT64 局_Rcx = R_QW(游戏模块 + 基址_个人_遍历);
	DWORD 局_R8 = 262144 + 格子数;
	INT64 返回rax = UI功能::getUiObjById(0x1A);
	if (返回rax)
	{
		MainUniversalCALL4(返回rax, 1, 局_R8, 0, 局_使用物品call);
	}

}
void 背包::使用物品2(DWORD 格子数)
{
	INT64 局_使用物品call = 游戏模块 + gc_UseItem;
	//INT64 局_使用物品call_rcx = 游戏模块 + 基址_背包_使用物品call_rcx;
	INT64 局_Rcx = R_QW(游戏模块 + gb_ShortKey);
	//DWORD 局_R8 = 262144 | 格子数;
	//INT64 返回rax = UI功能::getUiObjById(0x1A);
	//if (返回rax)
	//{
	MainUniversalCALL6(局_Rcx, 0, 格子数, 0, 0, 0, 局_使用物品call);
	//}

}

//耐久度_ 背包::取耐久度(INT64 物品对象)
//{
//	耐久度_ 局_耐久度;
//
//	局_耐久度.当前耐久度 = (R_DW(物品对象 + 偏移_背包_当前耐久度) + 99) / 100;
//	局_耐久度.最大耐久度 = (R_DW(局_名字对象 + #偏移_背包_最大耐久度) + 99) / 100;
//	return 局_耐久度;
//}

void 背包::get_RecommendEquipList(vector<Inventoryinfo_>& vsk)//推荐装备
{
	Inventoryinfo_ 临时;
	vsk.clear();
	INT64 inventoryWndAddr = UI功能::getUiObjById(0x1A);//背包UI地址D 1A root1.arkui.windowCanvas.inventoryWnd 

	long dtotal = R_DW(inventoryWndAddr + go_RecomEquip + 0x28);
	INT64 objStartAddr = R_QW(inventoryWndAddr + go_RecomEquip);
	for (DWORD i = 0; i < dtotal; i++)
	{
		DWORD dSlotIndex = R_DW(objStartAddr + i * 0x5 * 4);
		if (dSlotIndex && dSlotIndex != 0xFFFFFFFF)
		{
			INT64 dItmeId = R_QW(objStartAddr + i * 0x5 * 4 + 4);
			临时.ItemId = dItmeId;
			vsk.push_back(临时);
			MyTrace(L"推荐装备槽位%X 物品ID 0x%X\r\n", dSlotIndex, dItmeId);
		}
	}
}

int 背包::get_PosbyItemID(DWORD itemId)
{
	vector<Inventoryinfo_> vsk;
	背包::get_InventoryItemList(vsk);
	for (size_t i = 0; i < vsk.size(); i++)
	{
		if (vsk[i].ItemId == itemId)
		{
			return vsk[i].dindex;
		}
	}
	return -1;
}

Inventoryinfo_ 背包::get_ItemInfobyItemID(INT64 itemId)
{
	Inventoryinfo_ info;
	vector<Inventoryinfo_> vsk;
	背包::get_InventoryItemList(vsk);
	for (size_t i = 0; i < vsk.size(); i++)
	{
		if (vsk[i].ItemId == itemId)
		{
			return vsk[i];
		}
	}
	return info;
}


void 背包::使用背包指定物品(CString 物品名称)
{
	vector<Inventoryinfo_> vsk;
	背包::get_InventoryItemList(vsk);
	for (size_t i = 0; i < vsk.size(); i++)
	{
		if (vsk[i].ItemName.Find(物品名称) != -1)
		{
			背包::使用物品2(vsk[i].dindex);
			break;
		}
	}
}
void 背包::使用背包指定物品_ByResId(DWORD ResId)
{
	vector<Inventoryinfo_> vsk;
	背包::get_InventoryItemList(vsk);
	for (size_t i = 0; i < vsk.size(); i++)
	{
		if (vsk[i].ItemResId == ResId)
		{
			MyTrace(L"使用物品 %s", vsk[i].ItemName);
			背包::使用物品2(vsk[i].dindex);
			break;
		}
	}
}
void 背包::装备背包指定物品_ByResId(DWORD ResId)
{
	vector<Inventoryinfo_> vsk;
	背包::get_InventoryItemList(vsk);
	for (size_t i = 0; i < vsk.size(); i++)
	{
		if (vsk[i].ItemResId == ResId)
		{
			MyTrace(L"使用物品 %s", vsk[i].ItemName);
			背包::使用物品(vsk[i].dindex);
			break;
		}
	}
}
DWORD 背包::返回指定物品数量(DWORD ResId)
{
	vector<Inventoryinfo_> vsk;
	背包::get_InventoryItemList(vsk);
	for (size_t i = 0; i < vsk.size(); i++)
	{
		if (vsk[i].ItemResId == ResId)
		{
			return vsk[i].dNum;
		}
	}
	return 0;
}
bool 背包::判断是否为推荐装备(INT64 ItemId)
{
	vector<Inventoryinfo_>vsk;
	背包::get_RecommendEquipList(vsk);
	if (vsk.size() > 0)
	{
		for (size_t i = 0; i < vsk.size(); i++)
		{
			if (vsk[i].ItemId == ItemId)
			{
				return true;
			}
		}
	}

	return false;

}
void 背包::自定装备推荐装备()
{
	Equipinfo_ temp;
	Equipinfo_ temp2;
	vector<Inventoryinfo_>vsk;
	背包::get_RecommendEquipList(vsk);
	int 计次 = 0;
	int 计次2 = 0;

	for (size_t i = 0; i < vsk.size(); i++)
	{
		Inventoryinfo_ item = 背包::get_ItemInfobyItemID(vsk[i].ItemId);
		if (item.dindex == -1)
		{
			return;
		}
		MyTrace(L"穿戴 %s 格子%d", item.ItemName, item.dindex);
		if (item.WearId == 7)//耳环
		{
			if (计次 >= 2)
			{
				continue;

			}

			temp = get_EquipInfobyIndex(7);//左耳环
			//if (temp.颜色 < item.颜色)
			//{
			//	背包::CALL_穿戴装备(item.dindex, 7);
			//	break;
			//}
			temp2 = get_EquipInfobyIndex(8);//左耳环
			if (temp.ItemId != 0 && temp2.ItemId != 0)
			{
				MyTrace(L"脱下耳环");
				背包::Fun_UnWearEquip(7);
				Sleep(500);
				背包::Fun_UnWearEquip(8);
			}
			背包::使用物品(item.dindex);
			Sleep(300);
			计次 = 计次 + 1;
			Sleep(300);
			//if (temp.颜色 < item.颜色)
			//{
			//	背包::CALL_穿戴装备(item.dindex, 8);
			//	break;
			//}
			continue;
		}
		if (item.WearId == 9)//耳环
		{
			if (计次2 >= 2)
			{
				continue;

			}

			//背包::使用物品(item.dindex);
			temp = get_EquipInfobyIndex(0xA);//左耳环
			//if (temp.颜色 <= item.颜色)
			//{
			//	背包::CALL_穿戴装备(item.dindex, 0xA);
			//	break;
			//}
			temp2 = get_EquipInfobyIndex(9);//左耳环
			if (temp.ItemId != 0 && temp2.ItemId != 0)
			{
				MyTrace(L"脱下戒指");
				背包::Fun_UnWearEquip(9);
				Sleep(500);
				背包::Fun_UnWearEquip(0xA);

			}
			背包::使用物品(item.dindex);
			Sleep(300);
			计次2 = 计次2 + 1;
			Sleep(300);
			//if (temp.颜色 < item.颜色)
			//{
			//	背包::CALL_穿戴装备(item.dindex, 9);
			//	break;
			//}
			continue;
		}
		if (item.dindex != -1)
		{
			背包::使用物品(item.dindex);
			Sleep(300);
			continue;
		}
	}
}

void 背包::CALL_穿戴装备(DWORD bagpos, DWORD SendArg)
{
	INT64 dRcx = R_QW(游戏模块 + gb_ShortKey);
	INT64 dCall = 游戏模块 + gc_WearEquip;
	if (dRcx)
	{
		MainUniversalCALL4(dRcx, 0, bagpos, SendArg, dCall);
	}
}
void 背包::Fun_UnWearEquip(int dEquipSlot)
{
	INT64 dUiObj = UI功能::getUiObjById(0x34);//root1.arkui.windowCanvas.characterInfoWnd
	MainUniversalCALL4(dUiObj, 1, dEquipSlot, 0, 游戏模块 + gc_UnWearEquip);
}

void Fun_CheckBSItem_Wnd(int dNum)//普通
{
	INT64 dUiObj = UI功能::getUiObjByName(L"root1.arkui.windowCanvas.BS_Item_Wnd");//BS_Item_Wnd 
	if (dUiObj)
	{
		DWORD dShow = R_DW(dUiObj + 0x27C);

		if (dShow)
		{
			INT64 dRCX = dUiObj + go_BSItem_WndInfo;
			INT64 dCall = R_QW(R_QW(dRCX) + 0x28);
			MainUniversalCALL2(dRCX, dNum, dCall);
			Sleep(5000);
			INT64 dCloseUiCall = R_QW(R_QW(dUiObj) + 0xB8);
			MainUniversalCALL2(dUiObj, 0, dCloseUiCall);

		}
	}
}
void Fun_CheckBSSelectItem_Wnd(int dItemResId, int dNum)//选择箱子 打开全部
{
	INT64 dUiObj = UI功能::getUiObjById(0x9C);//BS_SelectItem_Wnd  需要选择的
	if (dUiObj)
	{
		DWORD dShow = R_DW(dUiObj + 0x27C);
		if (dShow)
		{
			INT64 dRCX = dUiObj + go_BSItem_WndInfo;
			INT64  dCall = R_QW(R_QW(dRCX) + 0x28);
			W_DW(dRCX + 0x34, dItemResId);

			MainUniversalCALL2(dRCX, dNum, dCall);
			Sleep(5000);
			INT64 dCloseUiCall = R_QW(R_QW(dUiObj) + 0xB8);
			MainUniversalCALL2(dUiObj, 0, dCloseUiCall);
		}
	}
}
//void Fun_CheckBSSelectItem_WndOne(int dItemResId)//选择箱子 打开单个
//{
//	INT64 dUiObj = UI功能::getUiObjById(0x9C);//BS_SelectItem_Wnd  需要选择的
//	if (dUiObj)
//	{
//		DWORD dShow = R_DW(dUiObj + 0x27C);
//		if (dShow)
//		{
//
//			INT64 dRCX = dUiObj + go_BSItem_WndInfo;
//			W_DW( dRCX + 0x34, dItemResId);
//			INT64 dCall = R_QW(R_QW(dRCX) + 0x28);
//			INT64 dCloseUiCall = R_QW(R_QW(dUiObj) + 0xB8);
//			int dBagItemResId = R_DW(dUiObj + go_BSItem_ItemInfo);
//			INT64 dBagItemSrvId = R_QW(dUiObj + go_BSItem_ItemInfo + 8);
//			UCHAR dInfoAddr[0x100] = { 0 };
//			//INT64 dInfoAddr = dm.VirtualAllocEx( 0, 0x100, 0);
//			W_DW( (INT64)&dInfoAddr[0x4], dBagItemResId);
//			W_QW((INT64)&dInfoAddr[0xC], dBagItemSrvId);
//			W_DW((INT64)&dInfoAddr[0x18], dItemResId);
//			MainUniversalCALL2(dRCX, (ULONG_PTR)dInfoAddr, dCall);
//			MainUniversalCALL2(dUiObj, 0, dCloseUiCall);
//
//		}
//	}
//}
void get_BsItem_Select()
{
	INT64 dUiObj = UI功能::getUiObjById(0x9C);//BS_SelectItem_Wnd  需要选择的
	INT64 dRCX = dUiObj + go_BSItem_WndInfo;
	DWORD dItemResId = R_DW(dRCX + 0x34);//85 ?? 0F ?? ?? ?? ?? ?? ?? 8D ?? ?? ?? 8B ?? FF ?? ?? ?? 8B ?? E8 ?? ?? ?? ?? ?? 85 ?? 0F +8+3
	INT64 dItemResAddr = getItemResAddrById(dItemResId);
	INT64 dNameAddr = R_QW(dItemResAddr + 0x10);

	CString csName = L"空";
	if (dNameAddr)
	{
		csName = R_CString(dNameAddr);
	}
	MyTrace(L"箱子选中物品ResId %X %s", dItemResId, csName);
}
void Fun_BS_RandomItemOpenAll(DWORD dNum)//随机卡片箱全部打开
{
	//INT64 go_BS_RandomItemOpenAll = 0x34;
	//85 ?? 0F ?? ?? ?? ?? ?? ?? 8D ?? ?? ?? 8B ?? FF ?? ?? ?? 8B ?? E8 ?? ?? ?? ?? ?? 85 ?? 0F +8+3 读字节 go_BS_RandomItemOpenAll
	INT64 dUiObj = UI功能::getUiObjById(0x9B);//BS_RandomItem_Wnd 
	if (dUiObj)
	{

		DWORD dShow = R_DW(dUiObj + 0x27C);
		if (dShow)
		{
			INT64 dRcx = dUiObj - go_BS_RandomItemOpenAll;
			INT64 dCall = R_QW(R_QW(dRcx) + 0x8);
			MainUniversalCALL2(dRcx, dNum, dCall);
			Sleep(5000);
			INT64 dCloseUiCall = R_QW(R_QW(dUiObj) + 0xB8);
			MainUniversalCALL2(dUiObj, 0, dCloseUiCall);
		}
	}
}

void  背包::自动入包call()
{
	INT64 dCall = 入包call + 游戏模块;
	INT64 rcx = R_QW(采集物品数量 + 游戏模块);
	MainUniversalCALL4(rcx, 0, 0, 0, dCall);


}
void  背包::点击分解颜色call()
{
	INT64 dCall = 分解颜色call + 游戏模块;
	INT64 rcx = 0;
	//root1.arkui.windowCanvas.itemDisassembleWnd
	bool 是否打开 = UI功能::寻找打开窗口("root1.arkui.windowCanvas.itemDisassembleWnd", rcx);
	//MyTrace(L"是否打开%I64X 是否打开%d", rcx, 是否打开);
	if (rcx >= 1)
	{
		INT64 dRcx =rcx;

		MainUniversalCALL4(dRcx, 1, 1, 0, dCall);

		MainUniversalCALL4(dRcx, 2, 0, 0, dCall);
	
		MainUniversalCALL4(dRcx, 3, 0, 0, dCall);

		MainUniversalCALL4(dRcx, 4, 0, 0, dCall);
	

	}

}

bool 背包::背包物品处理()
{
	vector<Inventoryinfo_> vsk;
	vector<Inventoryinfo_> 待分解物品列表;
	背包::get_InventoryItemList(vsk);
	MyTrace(L"背包物品数量%d", vsk.size());
	if (UI功能::背包界面是否显示())
	{
		UI功能::Fun_UiShowCtrl(0x1A);
		Sleep(300);
	}
	for (size_t i = 0; i < vsk.size(); i++)
	{
		if (vsk[i].dSlotIndex == 0x78B5)//社交动作
		{
			背包::使用物品(vsk[i].dindex);
			Sleep(3000);
		}
		if (vsk[i].dSlotIndex == 0x7851)//登记大陆手册
		{
			背包::使用物品(vsk[i].dindex);
			Sleep(500);
		}
		if (vsk[i].dSlotIndex == 0x7D01)//卡牌强化 和传说书
		{
			背包::使用物品(vsk[i].dindex);
			Sleep(500);
		}
		if (vsk[i].dSlotIndex == 0x7D00)//卡牌
		{
			if (!UI功能::背包界面是否显示())
			{
				UI功能::Fun_UiShowCtrl(0x1A);
				Sleep(300);
			}
			背包::使用物品(vsk[i].dindex);
			Sleep(500);
			MyTrace(L"使用卡牌物品 回车键");
			UI功能::内存按键(VK_RETURN);//使用回车键 会导致聊天窗口打开 之后 别的功能案件不好使
		}
		if (vsk[i].ItemResId == 0x3C4D034 || vsk[i].ItemResId == 0x3C4D032 || vsk[i].ItemResId == 0x3C4D031 || vsk[i].ItemResId == 0x3C4D033 || vsk[i].ItemResId == 0x3C4D036 || vsk[i].ItemResId == 0x3C4D035 || vsk[i].ItemResId == 0x3C4D037)//传说卡牌包
		{
			背包::使用物品2(vsk[i].dindex);
			Sleep(500);
			Fun_BS_RandomItemOpenAll(vsk[i].dNum);
			Sleep(2000);
		}
		if (vsk[i].dSlotIndex == 0x765F)//拍卖币
		{
			for (size_t j = 0; j < vsk[i].dNum; j++)
			{
				背包::使用物品2(vsk[i].dindex);
				Sleep(200);
			}
		}
		//if (vsk[i].dSlotIndex == 0x7EF4)//以太书
		//{
		//	/*for (size_t j = 0; j < vsk[i].dNum; j++)
		//	{*/
		//		背包::使用物品2(vsk[i].dindex);
		//		Sleep(200);
		//	//}

		//}
		if (vsk[i].dSlotIndex == 0x7E90)//坐骑
		{
			背包::使用物品2(vsk[i].dindex);
			Sleep(500);
		}
		if (vsk[i].ItemResId == 0x7A1FD)//血爪的闪亮硬币
		{
			背包::使用物品2(vsk[i].dindex);
			Sleep(500);
		}
		if (vsk[i].ItemResId == 0x7C9C)//船员申请书
		{
			背包::使用物品2(vsk[i].dindex);
			Sleep(500);
		}
		if (vsk[i].ItemResId == 205001)//海盗箱子wai'm
		{
			背包::使用物品2(vsk[i].dindex);
			Sleep(500);
		}
		if (vsk[i].ItemResId == 0x320CB)//海盗箱子wai'm
		{
			背包::使用物品2(vsk[i].dindex);
			Sleep(500);
		}
		if (vsk[i].ItemResId == 0x263E11A || vsk[i].ItemResId == 0x26B82D1)//银币箱子wai'm
		{
			背包::使用物品2(vsk[i].dindex);
			Sleep(500);
			Fun_CheckBSItem_Wnd(vsk[i].dNum);
			Sleep(500);
		}
		if (vsk[i].dSlotIndex == 0x765D)//羽毛
		{
			for (size_t j = 0; j < vsk[i].dNum; j++)
			{
				背包::使用物品2(vsk[i].dindex);
				Sleep(500);
			}
		}
		if (vsk[i].dSlotIndex == 0x765C)//羽毛
		{
			if (vsk[i].ItemResId == 0x26BBF14)
			{
				continue;
			}
			if (vsk[i].ItemResId == 0x77A11)
			{
				continue;
			}
			背包::使用物品2(vsk[i].dindex);
			Sleep(500);
		}
		if (vsk[i].WearId <= 0xA)
		{
			if (vsk[i].颜色 <= 3 && vsk[i].dLev <= 302)
			{
				if (!背包::判断是否为推荐装备(vsk[i].ItemId))
				{
					待分解物品列表.push_back(vsk[i]);
				}
			}
		}
	}
	if (待分解物品列表.size() >= 3)
	{
		if (!UI功能::bCheckItemDisassemleWnd())
		{
			UI功能::Fun_UiShowCtrl(0x25);
			Sleep(1000);
		}
		if (UI功能::bCheckItemDisassemleWnd())
		{
			for (size_t i = 0; i < 待分解物品列表.size(); i++)
			{
				背包::右键物品(待分解物品列表[i].dindex);
				Sleep(200);
			}
			本人::CALL_全部分解();
			Sleep(3000);
			UI功能::Fun_UiShowCtrl(0x25);
			return false;
		}

	}
	else
	{
		if (UI功能::bCheckItemDisassemleWnd())
		{
			UI功能::Fun_UiShowCtrl(0x25);
			Sleep(1000);
		}
	}
	return true;
}

void 背包::SetHpItemSlot(DWORD dItemId, DWORD dTargetIndex)// dTargetIndex  从0开始
{
	INT64 dCall = 游戏模块 + gc_ItemShortKeySet;
	INT64 dRCX = R_QW(游戏模块 + gb_PacketInfo);
	MainUniversalCALL6(dRCX, 3, 1, dTargetIndex, dItemId, 0, dCall);
	//DWORD dItemId = 0x2E63A;//物品资源ID
	/*wchar_t buf[100];
	dm.AsmClear();
	dm.AsmAdd(L"sub rsp,030");
	dm.AsmAdd(L"xor edi, edi");
	dm.AsmAdd(L"mov dword ptr ds:[rsp+28],edi");
	wsprintf(buf, L"MOV EAX, 0%X", dItemId);
	dm.AsmAdd(buf);
	dm.AsmAdd(L"mov qword ptr ds:[rsp+20],rax");
	wsprintf(buf, L"MOV R9D, 0%X", dTargetIndex);
	dm.AsmAdd(buf);
	dm.AsmAdd(L"mov r8b, 1");
	dm.AsmAdd(L"mov dl, 3");
	wsprintf(buf, L"MOV RCX, 0%I64X", dRCX);
	dm.AsmAdd(buf);
	wsprintf(buf, L"mov rdi, 0%I64X", dCall);
	dm.AsmAdd(buf);
	dm.AsmAdd(L"call rdi");
	dm.AsmAdd(L"add rsp,030");
	dm.AsmCall( 6);*/
}
void 背包::SetBufItemSlot(DWORD dItemId, DWORD dTargetIndex)// dTargetIndex  从0开始
{
	INT64 dCall = 游戏模块 + gc_ItemShortKeySet;
	INT64 dRCX = R_QW(游戏模块 + gb_PacketInfo);
	MainUniversalCALL6(dRCX, 1, 0, dTargetIndex, dItemId, 0, dCall);
	/*wchar_t buf[100];
	dm.AsmClear();
	dm.AsmAdd(L"sub rsp,030");
	dm.AsmAdd(L"xor edi, edi");
	dm.AsmAdd(L"mov dword ptr ds:[rsp+28],edi");
	wsprintf(buf, L"MOV EAX, 0%X", dItemId);
	dm.AsmAdd(buf);
	dm.AsmAdd(L"mov qword ptr ds:[rsp+20],rax");
	wsprintf(buf, L"MOV R9D, 0%X", dTargetIndex);
	dm.AsmAdd(buf);
	dm.AsmAdd(L"xor r8d, r8d");
	dm.AsmAdd(L"mov dl, 1");
	wsprintf(buf, L"MOV RCX, 0%I64X", dRCX);
	dm.AsmAdd(buf);
	wsprintf(buf, L"mov rdi, 0%I64X", dCall);
	dm.AsmAdd(buf);
	dm.AsmAdd(L"call rdi");
	dm.AsmAdd(L"add rsp,030");
	dm.AsmCall( 6);*/
}

DWORD 背包::采集数量(DWORD ID)
{
	INT64 dRCX = R_QW(游戏模块 + 采集物品数量);
	INT64 dCall = 游戏模块 + 采集数量call;
	DWORD addr=MainUniversalCALL4_Ret(dRCX,ID,0,0, dCall);
	return addr;
//
//#define 采集数量call 0x1329200
//#define 采集物品数量 4C75ED0
}

DWORD 背包::指定类型物品数量(DWORD ID)
{
	vector<Inventoryinfo_> vsk;
	背包::get_InventoryItemList(vsk);
	DWORD a = 0;

	for (size_t i = 0; i < vsk.size(); i++)
	{
		if (vsk[i].dSlotIndex == ID && ID!=0)
		{
			a = a + 1;


		}

	/*	if (vsk[i].ItemName.Find(物品名称) != -1)
		{
			背包::使用物品2(vsk[i].dindex);
			break;
		}*/
	}
	return a;

}


void 背包::药品拖拽call(DWORD 位置, DWORD dItemId, DWORD dTargetIndex, DWORD 物品类型)
{
	INT64 dCall = 游戏模块 + gc_ItemShortKeySet;
	INT64 dRCX = R_QW(游戏模块 + gb_PacketInfo);
	DWORD r9 = 位置;
	DWORD rdx = 物品类型;
	DWORD r8;

	if (rdx == 3)
	{
		r8 = 1;

	}
	else
	{
		r8 = 0;
	}


	MainUniversalCALL6(dRCX, rdx, r8, dTargetIndex, dItemId, 0, dCall);


}
int 等级换算(int needuplv)
{
	if (needuplv == 420)
	{
		return 8;
	}
	if (needuplv == 600)
	{
		return 15;
	}
	if (needuplv == 960)
	{
		return 8;
	}
	if (needuplv == 1100)
	{
		return 15;
	}
	return needuplv;
}
DWORD 背包::需研磨装备序号(DWORD lv)
{
	vector<Equipinfo_>vsk;
	背包::get_UpEquipList(vsk);
	for (size_t i = 0; i < vsk.size(); i++)
	{
		lv = 等级换算(lv);
		if (vsk[i].dUpgradeLev < lv)
		{
			return vsk[i].WearId;
		}
	}
	return -1;
}