#include "�ڴ�_�������.h"
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
void ����::get_InventoryItemList(vector<Inventoryinfo_>& vsk)
{
	vsk.clear();
	Inventoryinfo_ temp;
	INT64 addr_1 = R_QW(��Ϸģ�� + gb_ShortKey);
	INT64 addr_2 = R_QW(addr_1 + go_AttrList_off1/*0x94*/);
	DWORD dSize = go_bag_dSize;//0x1E0;
	//DWORD dSize = 1744;//0x1E0;
	INT64 dStart = addr_2 + ƫ��_����_��Ʒ��������ͷ;//0x17DD8;//0x690;
	//INT64 dStart = addr_2 + 0x55A2C ;//0x17DD8;//0x690;
	for (size_t i = 0; i < 100; i++)
	{
		INT64 dItemId = R_QW(dStart + i * dSize + ƫ��_����_��Ʒid);
		if (dItemId)
		{
			DWORD dItmeResId = R_DW(dStart + i * dSize + ƫ��_����_��Ʒresid);
			DWORD dItemDur = R_DW(dStart + i * dSize + 0x14);
			INT64 dItemResAddr = getItemResAddrById(dItmeResId);
			//MyTrace(L"dItemResAddr");
			INT64 dNameAddr = R_QW(dItemResAddr + 0x10);
			DWORD dSlotIndex = R_DW(dItemResAddr + 0x8C);//����-2023��7��14�� 00:23:58
			DWORD dpinzhi = R_DW(dItemResAddr + 0x90);//����-2023��7��14�� 00:24:01
			DWORD ��Ʒ�ȼ� = R_W(dItemResAddr + ƫ��_����_��Ʒ�ȼ�);
			DWORD ǿ���ȼ� = R_W(dStart + i * dSize + go_ItemGradeLev) - 100;
			int dBoxType = 0;
			if (dSlotIndex == 0x791A)
			{
				//dBoxType = getItemBoxType(dItmeResId);//��Դδ�������׿�����ע��
			}
			CString csName = L"��";
			if (dNameAddr)
			{
				//string sName = UnicodeToAnsi(R_CString(dNameAddr));
				//csName = GetName(dNameAddr);
				//DbgPrintf_Mine("sName %s",sName);
				//csName = CString(sName.c_str());
				csName = R_CString(dNameAddr);
			}
			DWORD dNum = R_DW(dStart + i * dSize + ƫ��_����_��Ʒ����);
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
			temp.��ɫ = dpinzhi;
			temp.dLev = ��Ʒ�ȼ�;
			temp.dUpgradeLev = ǿ���ȼ�;
			�;ö�_ ��ʱ�;ö�;
			if (temp.WearId != 30)
			{
				��ʱ�;ö�.��ǰ�;ö� = double(R_DW(dStart + i * dSize + ƫ��_����_��ǰ�;ö�) + 99) / 100;
				��ʱ�;ö�.����;ö� = double(R_DW(dItemResAddr + ƫ��_����_����;ö�) + 99) / 100;
			}
			temp.�;ö� = ��ʱ�;ö�;
			vsk.push_back(temp);
			wchar_t buf[MAX_PATH];
			//swprintf(buf, L"λ��%X ��ַ0x%I64X ��ƷID 0x%I64X ��ԴID %X ��ַ0x%I64X ����%d %s ��λ%X ��������%d ��������%d �;�%d/%d\r\n", i, dStart + i * dSize, dItemId, dItmeResId, dItemResAddr, dNum, csName, dSlotIndex, getEquipWearArg(dSlotIndex), dBoxType, temp.�;ö�.��ǰ�;ö�, temp.�;ö�.����;ö�);
			//MyTrace(buf);
			//g_String.Insert(g_String.GetLength(), buf);
		}
	}
}

void ����::get_EquipList(vector<Equipinfo_>& vsk)
{
	vsk.clear();
	Equipinfo_ temp;
	INT64 addr_1 = R_QW(��Ϸģ�� + gb_ShortKey);
	INT64 addr_2 = R_QW(addr_1 + go_AttrList_off1/*0x94*/);
	DWORD dSize = go_bag_dSize;//0x1E0;
	//DWORD dSize = 1744;//0x1E0;
	INT64 dStart = addr_2 + ƫ��_����_װ����������ͷ;//0x17DD8;//0x690;
	//INT64 dStart = addr_2 + 0x55A2C ;//0x17DD8;//0x690;
	for (DWORD i = 0; i < 15; i++)
	{
		INT64 dItemId = R_QW(dStart + i * dSize + ƫ��_����_��Ʒid);
		if (dItemId)
		{
			DWORD dItmeResId = R_DW(dStart + i * dSize + ƫ��_����_��Ʒresid);
			INT64 dItemResAddr = getItemResAddrById(dItmeResId);
			INT64 dNameAddr = R_QW(dItemResAddr + 0x10);
			DWORD dSlotIndex = R_DW(dItemResAddr + 0x8C);//����-2023��7��14�� 00:23:58
			DWORD dpinzhi = R_DW(dItemResAddr + 0x90);//����-2023��7��14�� 00:24:01
			DWORD ��Ʒ�ȼ� = R_W(dItemResAddr + ƫ��_����_��Ʒ�ȼ�);
			DWORD ǿ���ȼ� = R_W(dStart + i * dSize + go_ItemGradeLev) - 100;
			CString csName = L"��";
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
			temp.��ɫ = dpinzhi;
			temp.dLev = ��Ʒ�ȼ�;
			temp.dUpgradeLev = ǿ���ȼ�;
			�;ö�_ ��ʱ�;ö�;
			��ʱ�;ö�.��ǰ�;ö� = double(R_DW(dStart + i * dSize + ƫ��_����_��ǰ�;ö�) + 99) / 100;
			��ʱ�;ö�.����;ö� = double(R_DW(dItemResAddr + ƫ��_����_����;ö�) + 99) / 100;
			temp.�;ö� = ��ʱ�;ö�;
			vsk.push_back(temp);
			wchar_t buf[MAX_PATH];
			//swprintf(buf, L"Ʒ�� %d wearid %d λ��%X ��ַ0x%I64X ��ƷID 0x%I64X ��ԴID %X ��ַ0x%I64X %s �;�%d/%d\r\n", dpinzhi, temp.WearId ,i, dStart + i * dSize, dItemId, dItmeResId, dItemResAddr, csName, temp.�;ö�.��ǰ�;ö�, temp.�;ö�.����;ö�);
			//MyTrace(buf);
			//g_String.Insert(g_String.GetLength(), buf);
		}
	}
}

void ����::get_UpEquipList(vector<Equipinfo_>& vsk)
{
	vsk.clear();
	Equipinfo_ temp;
	INT64 addr_1 = R_QW(��Ϸģ�� + gb_ShortKey);
	INT64 addr_2 = R_QW(addr_1 + go_AttrList_off1/*0x94*/);
	DWORD dSize = go_bag_dSize;//0x1E0;
	//DWORD dSize = 1744;//0x1E0;
	INT64 dStart = addr_2 + ƫ��_����_װ����������ͷ;//0x17DD8;//0x690;
	//INT64 dStart = addr_2 + 0x55A2C ;//0x17DD8;//0x690;
	for (DWORD i = 0; i < 6; i++)
	{
		INT64 dItemId = R_QW(dStart + i * dSize + ƫ��_����_��Ʒid);
		if (dItemId)
		{
			DWORD dItmeResId = R_DW(dStart + i * dSize + ƫ��_����_��Ʒresid);
			INT64 dItemResAddr = getItemResAddrById(dItmeResId);
			INT64 dNameAddr = R_QW(dItemResAddr + 0x10);
			DWORD dSlotIndex = R_DW(dItemResAddr + 0x8C);//����-2023��7��14�� 00:23:58
			DWORD dpinzhi = R_DW(dItemResAddr + 0x90);//����-2023��7��14�� 00:24:01
			DWORD ��Ʒ�ȼ� = R_W(dItemResAddr + ƫ��_����_��Ʒ�ȼ�);
			DWORD ǿ���ȼ� = R_W(dStart + i * dSize + go_ItemGradeLev) - 100;
			CString csName = L"��";
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
			temp.��ɫ = dpinzhi;
			temp.dLev = ��Ʒ�ȼ�;
			temp.dUpgradeLev = ǿ���ȼ�;
			�;ö�_ ��ʱ�;ö�;
			��ʱ�;ö�.��ǰ�;ö� = double(R_DW(dStart + i * dSize + ƫ��_����_��ǰ�;ö�) + 99) / 100;
			��ʱ�;ö�.����;ö� = double(R_DW(dItemResAddr + ƫ��_����_����;ö�) + 99) / 100;
			temp.�;ö� = ��ʱ�;ö�;
			vsk.push_back(temp);
			wchar_t buf[MAX_PATH];
			//swprintf(buf, L"Ʒ�� %d wearid %d λ��%X ��ַ0x%I64X ��ƷID 0x%I64X ��ԴID %X ��ַ0x%I64X %s �;�%d/%d\r\n", dpinzhi, temp.WearId ,i, dStart + i * dSize, dItemId, dItmeResId, dItemResAddr, csName, temp.�;ö�.��ǰ�;ö�, temp.�;ö�.����;ö�);
			//MyTrace(buf);
			//g_String.Insert(g_String.GetLength(), buf);
		}
	}
}
void ����::get_LifeToolList(vector<Equipinfo_>& vsk)  //����װ��
{
	vsk.clear();
	Equipinfo_ temp;
	INT64 addr_1 = R_QW(��Ϸģ�� + gb_ShortKey);
	INT64 addr_2 = R_QW(addr_1 + go_AttrList_off1/*0x94*/);
	DWORD dSize = go_bag_dSize;//0x1E0;
	//DWORD dSize = 1744;//0x1E0;
	INT64 dStart = addr_2 + ƫ��_����_����װ����������ͷ;//0x17DD8;//0x690;
	//INT64 dStart = addr_2 + 0x55A2C ;//0x17DD8;//0x690;
	for (DWORD i = 0; i < 6; i++)
	{
		INT64 dItemId = R_QW(dStart + i * dSize + ƫ��_����_��Ʒid);
		if (dItemId)
		{
			DWORD dItmeResId = R_DW(dStart + i * dSize + ƫ��_����_��Ʒresid);
			INT64 dItemResAddr = getItemResAddrById(dItmeResId);
			INT64 dNameAddr = R_QW(dItemResAddr + 0x10);
			DWORD dSlotIndex = R_DW(dItemResAddr + 0x8C);//����-2023��7��14�� 00:23:58
			DWORD dpinzhi = R_DW(dItemResAddr + 0x90);//����-2023��7��14�� 00:24:01
			CString csName = L"��";
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
			temp.��ɫ = dpinzhi;
			�;ö�_ ��ʱ�;ö�;
			��ʱ�;ö�.��ǰ�;ö� = double(R_DW(dStart + i * dSize + ƫ��_����_��ǰ�;ö�) + 99) / 100;
			��ʱ�;ö�.����;ö� = double(R_DW(dItemResAddr + ƫ��_����_����;ö�) + 99) / 100;
			temp.�;ö� = ��ʱ�;ö�;
			vsk.push_back(temp);
			//wchar_t buf[MAX_PATH];
			//swprintf(buf, L"Ʒ�� %d wearid %d λ��%X ��ַ0x%I64X ��ƷID 0x%I64X ��ԴID %X ��ַ0x%I64X %s �;�%d/%d\r\n", dpinzhi, temp.WearId ,i, dStart + i * dSize, dItemId, dItmeResId, dItemResAddr, csName, temp.�;ö�.��ǰ�;ö�, temp.�;ö�.����;ö�);
			//MyTrace(buf);
			//g_String.Insert(g_String.GetLength(), buf);
		}
	}
}

void ����::get_cangkuList(vector<Inventoryinfo_>& vsk)
{
	vsk.clear();
	Inventoryinfo_ temp;
	INT64 addr_1 = R_QW(��Ϸģ�� + gb_ShortKey);
	INT64 addr_2 = R_QW(addr_1 + go_AttrList_off1/*0x94*/);
	DWORD dSize = go_bag_dSize;//0x1E0;
							   //DWORD dSize = 1744;//0x1E0;
	INT64 dStart = addr_2 + g_�����ֿ�����;//0x17DD8;//0x690;
											//INT64 dStart = addr_2 + 0x55A2C ;//0x17DD8;//0x690;
	for (DWORD i = 0; i < 24; i++)
	{
		INT64 dItemId = R_QW(dStart + i * dSize + ƫ��_����_��Ʒid);
		if (dItemId)
		{
			DWORD dItmeResId = R_DW(dStart + i * dSize + ƫ��_����_��Ʒresid);
			INT64 dItemResAddr = getItemResAddrById(dItmeResId);
			INT64 dNameAddr = R_QW(dItemResAddr + 0x10);
			DWORD dSlotIndex = R_DW(dItemResAddr + 0x8C);//����-2023��7��14�� 00:23:58
			DWORD dpinzhi = R_DW(dItemResAddr + 0x90);//����-2023��7��14�� 00:24:01
			CString csName = L"��";
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
			temp.��ɫ = dpinzhi;
			�;ö�_ ��ʱ�;ö�;
			��ʱ�;ö�.��ǰ�;ö� = double(R_DW(dStart + i * dSize + ƫ��_����_��ǰ�;ö�) + 99) / 100;
			��ʱ�;ö�.����;ö� = double(R_DW(dItemResAddr + ƫ��_����_����;ö�) + 99) / 100;
			temp.�;ö� = ��ʱ�;ö�;
			vsk.push_back(temp);
		/*	wchar_t buf[MAX_PATH];
			swprintf(buf, L"Ʒ�� %d wearid %d λ��%X ��ַ0x%I64X ��ƷID 0x%I64X ��ԴID %X ��ַ0x%I64X %s �;�%d/%d\r\n", dpinzhi, temp.WearId ,i, dStart + i * dSize, dItemId, dItmeResId, dItemResAddr, csName, temp.�;ö�.��ǰ�;ö�, temp.�;ö�.����;ö�);
			MyTrace(buf);*/
			//g_String.Insert(g_String.GetLength(), buf);
		}
	}


}




Inventoryinfo_ ����::ȡ�����ֿ�(CString name)
{


	Inventoryinfo_ temp;
	vector<Inventoryinfo_>vsk;
	����::get_feicangkuList(vsk);
	name.MakeUpper();

	for (size_t i = 0; i < vsk.size(); i++)
	{
		MyTrace(L"ItemName %s / %s    ItemResId %s/%s ", vsk[i].ItemName, name, CString(���ù���::ʮ����תʮ������(vsk[i].ItemResId).c_str()), name);
		if (vsk[i].ItemName == name || CString(���ù���::ʮ����תʮ������(vsk[i].ItemResId).c_str()) == name || vsk[i].WearId == _ttoi(name))
		{
			if (vsk[i].ItemId != 0)
			{

				����::ȡ��call(vsk[i].dindex, 0);
				Sleep(1000);
			}
			/*temp = vsk[i];
			break;*/
		}
	}
	return temp;

}


bool ����::ȡ��call(DWORD ��λ, DWORD �Ƿ񹫹��ֿ�)
{
	INT64 rcx = 0;

	bool �Ƿ�� = UI����::Ѱ�Ҵ򿪴���("root1.arkui.windowCanvas.windowGo", rcx);

	if (rcx != 0)
	{
		if (�Ƿ񹫹��ֿ� != 1)
		{

			DWORD	rdx = 1;
			DWORD	r8 = 3473408 + ��λ;
			DWORD	r9 = 0;

			MainUniversalCALL4(rcx, rdx, r8, r9, ��Ϸģ�� + gc_UnWearEquip);
			return 1;
		}
		else
		{
			DWORD	rdx = 1;
			DWORD	r8 = 3538944 + ��λ;
			DWORD	r9 = 0;
			MainUniversalCALL4(rcx, rdx, r8, r9, ��Ϸģ�� + gc_UnWearEquip);
			return 1;
		}




	}
	return 0;

}


void ����::get_feicangkuList(vector<Inventoryinfo_>& vsk)
{
	CString temp1;
	vsk.clear();
	Inventoryinfo_ temp;
	INT64 addr_1 = R_QW(��Ϸģ�� + gb_ShortKey);
	INT64 addr_2 = R_QW(addr_1 + go_AttrList_off1/*0x94*/);
	DWORD dSize = go_bag_dSize;//0x1E0;
							   //DWORD dSize = 1744;//0x1E0;
	INT64 dStart = addr_2 + g_�����ֿ�ͷ;//0x17DD8;//0x690;
									 //INT64 dStart = addr_2 + 0x55A2C ;//0x17DD8;//0x690;
	MyTrace(L"���:dStart 0x%I64X", dStart);
	for (DWORD i = 0; i < 100; i++)
	{

		INT64 dItemId = R_QW(dStart + i * dSize + ƫ��_����_��Ʒid);
		MyTrace(L"���:i %d ��ַ0x%I64X ID %X", i, dStart + i * dSize + ƫ��_����_��Ʒid, dItemId);
		/*	INT64 ace = dStart + i * dSize + ƫ��_����_��Ʒid;
			wchar_t buf[MAX_PATH];

			swprintf(buf, L"Ʒ�� %d ��ַ0x%I64X \r\n", i, ace);*/

			/*
				temp1.Format(L"%d", i);
				DebugPrintf("%s\n", temp1);*/
		if (dItemId)
		{

			DWORD dItmeResId = R_DW(dStart + i * dSize + ƫ��_����_��Ʒresid);
			INT64 dItemResAddr = getItemResAddrById(dItmeResId);
			INT64 dNameAddr = R_QW(dItemResAddr + 0x10);
			DWORD dSlotIndex = R_DW(dItemResAddr + 0x8C);//����-2023��7��14�� 00:23:58
			DWORD dpinzhi = R_DW(dItemResAddr + 0x90);//����-2023��7��14�� 00:24:01
			CString csName = L"��";
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
			temp.��ɫ = dpinzhi;
			�;ö�_ ��ʱ�;ö�;
			��ʱ�;ö�.��ǰ�;ö� = double(R_DW(dStart + i * dSize + ƫ��_����_��ǰ�;ö�) + 99) / 100;
			��ʱ�;ö�.����;ö� = double(R_DW(dItemResAddr + ƫ��_����_����;ö�) + 99) / 100;
			temp.�;ö� = ��ʱ�;ö�;
			vsk.push_back(temp);
			wchar_t buf[MAX_PATH];
			swprintf(buf, L"Ʒ�� %d wearid %d λ��%X ��ַ0x%I64X ��ƷID 0x%I64X ��ԴID %X ��ַ0x%I64X %s �;�%d/%d\r\n", dpinzhi, temp.WearId, i, dStart + i * dSize, dItemId, dItmeResId, dItemResAddr, csName, temp.�;ö�.��ǰ�;ö�, temp.�;ö�.����;ö�);
			MyTrace(buf);
			//g_String.Insert(g_String.GetLength(), buf);
		}
	}



}



Inventoryinfo_ ����::ȡ�����ֿ�(CString name)



//INT64 ItemObj;
//INT64 ItemId = 0;
//CString ItemName;
//DWORD Type;
//INT64 dItemResAddr;
//�;ö�_ �;ö�;
//DWORD ��Ʒ�ȼ� = 0;
//DWORD WearId = 0;
//DWORD ��ɫ = 0;
//DWORD dLev = 0;
//DWORD dUpgradeLev = 0;   std::string str((LPCTSTR)cstr);

{
	Inventoryinfo_ temp;
	vector<Inventoryinfo_>vsk;
	����::get_cangkuList(vsk);
	name.MakeUpper();

	for (size_t i = 0; i < vsk.size(); i++) {

		if (vsk[i].ItemName == name || CString(���ù���::ʮ����תʮ������(vsk[i].ItemId).c_str()) == name || vsk[i].WearId == _ttoi(name))
		{
			if (vsk[i].ItemId != 0)
			{

				����::ȡ��call(vsk[i].dindex, 1);
				Sleep(1000);
			}
			/*temp = vsk[i];
			break;*/
		}
	}
	return temp;

}










bool ����::ָ��λ��������Ƿ���װ��(DWORD ��λ)//0 �ɼ����� 1 ��ľ���� 2 �ɿ󹤾� 3 ���Թ��� 4 ���㹤�� 5 ���Ź���
{
	vector<Equipinfo_>vsk;
	����::get_LifeToolList(vsk);
	for (size_t i = 0; i < vsk.size(); i++)
	{
		if (vsk[i].Type == ��λ)
		{
			return true;
		}
	}
	return false;
}
Equipinfo_ ����::get_EquipInfobyIndex(DWORD type)
{
	Equipinfo_ temp;
	vector<Equipinfo_>vsk;
	����::get_EquipList(vsk);
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
DWORD ����::ȡ�����()
{

	INT64 ��_rcx = R_QW(��Ϸģ�� + ��ַ_����_����) + 288;
	DWORD ��_���� = R_DW(��_rcx + 32);
	return ��_����;
}
DWORD ����::ȡ������()
{

	INT64 ��_rcx = R_QW(��Ϸģ�� + ��ַ_����_����) + 288;
	DWORD ��_���� = R_DW(��_rcx + 2);
	return ��_����;
}
DWORD ����::ȡ�������()
{

	INT64 ��_rcx = R_QW(��Ϸģ�� + ��ַ_����_����) + 288;
	DWORD ��_���� = R_DW(��_rcx + 0x43);
	//MyTrace(L"��_ȡ������� %d", ��_����);
	return ��_����;
}
INT64 ����::getMoneyNumByType(int dMoneyType)//A ������
{
	INT64 dstart = R_QW(��Ϸģ�� + gb_AttrList) + go_RoleMoneyListStart;
	return MainUniversalCALL4_Ret(dstart, dMoneyType, 1, 0, ��Ϸģ�� + gc_GetMoneyValue);

}
void ����::ά��װ��(DWORD ��_��������)
{
	INT64 ��_rcx = R_QW(��Ϸģ�� + ��ַ_����_����rcx);
	INT64 ��_call = ��Ϸģ�� + ��ַ_����_����call;
	if (��_rcx)
	{
		MainUniversalCALL4(��_rcx, ��_��������, 0x19, 0, ��_call);
	}
}

void ����::ʹ��������Ʒ(DWORD ������)
{

	INT64 ��_ʹ����Ʒcall = ��Ϸģ�� + ��ַ_����_ʹ����Ʒcall;
	//INT64 ��_ʹ����Ʒcall_rcx = ��Ϸģ�� + ��ַ_����_ʹ����Ʒcall_rcx;
	//INT64 ��_Rcx = R_QW(��Ϸģ�� + ��ַ_����_����);
	DWORD ��_R8 = 327680 | ������;
	INT64 ����rax = UI����::getUiObjById(0x1A);
	if (����rax)
	{
		MainUniversalCALL4(����rax, 1, ��_R8, 0, ��_ʹ����Ʒcall);
	}
}

void ����::ʹ����Ʒ(DWORD ������)
{
	INT64 ��_ʹ����Ʒcall = ��Ϸģ�� + ��ַ_����_ʹ����Ʒcall;
	//INT64 ��_ʹ����Ʒcall_rcx = ��Ϸģ�� + ��ַ_����_ʹ����Ʒcall_rcx;
	//INT64 ��_Rcx = R_QW(��Ϸģ�� + ��ַ_����_����);
	DWORD ��_R8 = 262144 | ������;
	INT64 ����rax = UI����::getUiObjById(0x1A);
	if (����rax)
	{
		MainUniversalCALL4(����rax, 1, ��_R8, 0, ��_ʹ����Ʒcall);
	}

}


DWORD ����::�������()
{
	vector<DWORD>vsk;
	vsk.clear();
	INT64 b = R_QW(R_QW(��Ϸģ�� + gb_AttrList)+0xE4);
	DWORD dtotal= R_DW(b + g_����); 
	DWORD C = g_���� - 8;
	INT64 �� = R_QW(b + C);
	DWORD ID = 0;
	�� = �� + g_����_index��;
	//MyTrace(L"�Ƽ�װ����λ0x%I64X \r\n", ��);
	if (dtotal >= 1)
	{
		for (DWORD i = 0; i < dtotal; i++)
		{
			ID = R_DW(�� + i*g_����_���ӵ�);
			if (ID > 1)
			{
				//MyTrace(L"ID 0x%I64X \r\n", ID);
				DWORD rax = 0;
				rax =����::�Ƿ��������call(ID);
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
	//	MyTrace(L"����� 0x%I64X \r\n", vsk[randomNumber - 1]);
		return vsk[randomNumber-1];
	}
	return 0;



}

void ����::������Ʒcall(INT64 ItemId)
{

	INT64 rcx = ��Ϸģ�� + �ɼ���Ʒ����;

	MainUniversalCALL4(rcx, ItemId, 0, 0, ��Ϸģ�� + ����д���ַ);

}


void ����::�Ҽ���Ʒ(DWORD ������)
{
	INT64 ��_ʹ����Ʒcall = ��Ϸģ�� + ��ַ_����_ʹ����Ʒcall2;
	//INT64 ��_ʹ����Ʒcall_rcx = ��Ϸģ�� + ��ַ_����_ʹ����Ʒcall_rcx;
	//INT64 ��_Rcx = R_QW(��Ϸģ�� + ��ַ_����_����);
	DWORD ��_R8 = 262144 + ������;
	INT64 ����rax = UI����::getUiObjById(0x1A);
	if (����rax)
	{
		MainUniversalCALL4(����rax, 1, ��_R8, 0, ��_ʹ����Ʒcall);
	}

}
void ����::ʹ����Ʒ2(DWORD ������)
{
	INT64 ��_ʹ����Ʒcall = ��Ϸģ�� + gc_UseItem;
	//INT64 ��_ʹ����Ʒcall_rcx = ��Ϸģ�� + ��ַ_����_ʹ����Ʒcall_rcx;
	INT64 ��_Rcx = R_QW(��Ϸģ�� + gb_ShortKey);
	//DWORD ��_R8 = 262144 | ������;
	//INT64 ����rax = UI����::getUiObjById(0x1A);
	//if (����rax)
	//{
	MainUniversalCALL6(��_Rcx, 0, ������, 0, 0, 0, ��_ʹ����Ʒcall);
	//}

}

//�;ö�_ ����::ȡ�;ö�(INT64 ��Ʒ����)
//{
//	�;ö�_ ��_�;ö�;
//
//	��_�;ö�.��ǰ�;ö� = (R_DW(��Ʒ���� + ƫ��_����_��ǰ�;ö�) + 99) / 100;
//	��_�;ö�.����;ö� = (R_DW(��_���ֶ��� + #ƫ��_����_����;ö�) + 99) / 100;
//	return ��_�;ö�;
//}

void ����::get_RecommendEquipList(vector<Inventoryinfo_>& vsk)//�Ƽ�װ��
{
	Inventoryinfo_ ��ʱ;
	vsk.clear();
	INT64 inventoryWndAddr = UI����::getUiObjById(0x1A);//����UI��ַD 1A root1.arkui.windowCanvas.inventoryWnd 

	long dtotal = R_DW(inventoryWndAddr + go_RecomEquip + 0x28);
	INT64 objStartAddr = R_QW(inventoryWndAddr + go_RecomEquip);
	for (DWORD i = 0; i < dtotal; i++)
	{
		DWORD dSlotIndex = R_DW(objStartAddr + i * 0x5 * 4);
		if (dSlotIndex && dSlotIndex != 0xFFFFFFFF)
		{
			INT64 dItmeId = R_QW(objStartAddr + i * 0x5 * 4 + 4);
			��ʱ.ItemId = dItmeId;
			vsk.push_back(��ʱ);
			MyTrace(L"�Ƽ�װ����λ%X ��ƷID 0x%X\r\n", dSlotIndex, dItmeId);
		}
	}
}

int ����::get_PosbyItemID(DWORD itemId)
{
	vector<Inventoryinfo_> vsk;
	����::get_InventoryItemList(vsk);
	for (size_t i = 0; i < vsk.size(); i++)
	{
		if (vsk[i].ItemId == itemId)
		{
			return vsk[i].dindex;
		}
	}
	return -1;
}

Inventoryinfo_ ����::get_ItemInfobyItemID(INT64 itemId)
{
	Inventoryinfo_ info;
	vector<Inventoryinfo_> vsk;
	����::get_InventoryItemList(vsk);
	for (size_t i = 0; i < vsk.size(); i++)
	{
		if (vsk[i].ItemId == itemId)
		{
			return vsk[i];
		}
	}
	return info;
}


void ����::ʹ�ñ���ָ����Ʒ(CString ��Ʒ����)
{
	vector<Inventoryinfo_> vsk;
	����::get_InventoryItemList(vsk);
	for (size_t i = 0; i < vsk.size(); i++)
	{
		if (vsk[i].ItemName.Find(��Ʒ����) != -1)
		{
			����::ʹ����Ʒ2(vsk[i].dindex);
			break;
		}
	}
}
void ����::ʹ�ñ���ָ����Ʒ_ByResId(DWORD ResId)
{
	vector<Inventoryinfo_> vsk;
	����::get_InventoryItemList(vsk);
	for (size_t i = 0; i < vsk.size(); i++)
	{
		if (vsk[i].ItemResId == ResId)
		{
			MyTrace(L"ʹ����Ʒ %s", vsk[i].ItemName);
			����::ʹ����Ʒ2(vsk[i].dindex);
			break;
		}
	}
}
void ����::װ������ָ����Ʒ_ByResId(DWORD ResId)
{
	vector<Inventoryinfo_> vsk;
	����::get_InventoryItemList(vsk);
	for (size_t i = 0; i < vsk.size(); i++)
	{
		if (vsk[i].ItemResId == ResId)
		{
			MyTrace(L"ʹ����Ʒ %s", vsk[i].ItemName);
			����::ʹ����Ʒ(vsk[i].dindex);
			break;
		}
	}
}
DWORD ����::����ָ����Ʒ����(DWORD ResId)
{
	vector<Inventoryinfo_> vsk;
	����::get_InventoryItemList(vsk);
	for (size_t i = 0; i < vsk.size(); i++)
	{
		if (vsk[i].ItemResId == ResId)
		{
			return vsk[i].dNum;
		}
	}
	return 0;
}
bool ����::�ж��Ƿ�Ϊ�Ƽ�װ��(INT64 ItemId)
{
	vector<Inventoryinfo_>vsk;
	����::get_RecommendEquipList(vsk);
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
void ����::�Զ�װ���Ƽ�װ��()
{
	Equipinfo_ temp;
	Equipinfo_ temp2;
	vector<Inventoryinfo_>vsk;
	����::get_RecommendEquipList(vsk);
	int �ƴ� = 0;
	int �ƴ�2 = 0;

	for (size_t i = 0; i < vsk.size(); i++)
	{
		Inventoryinfo_ item = ����::get_ItemInfobyItemID(vsk[i].ItemId);
		if (item.dindex == -1)
		{
			return;
		}
		MyTrace(L"���� %s ����%d", item.ItemName, item.dindex);
		if (item.WearId == 7)//����
		{
			if (�ƴ� >= 2)
			{
				continue;

			}

			temp = get_EquipInfobyIndex(7);//�����
			//if (temp.��ɫ < item.��ɫ)
			//{
			//	����::CALL_����װ��(item.dindex, 7);
			//	break;
			//}
			temp2 = get_EquipInfobyIndex(8);//�����
			if (temp.ItemId != 0 && temp2.ItemId != 0)
			{
				MyTrace(L"���¶���");
				����::Fun_UnWearEquip(7);
				Sleep(500);
				����::Fun_UnWearEquip(8);
			}
			����::ʹ����Ʒ(item.dindex);
			Sleep(300);
			�ƴ� = �ƴ� + 1;
			Sleep(300);
			//if (temp.��ɫ < item.��ɫ)
			//{
			//	����::CALL_����װ��(item.dindex, 8);
			//	break;
			//}
			continue;
		}
		if (item.WearId == 9)//����
		{
			if (�ƴ�2 >= 2)
			{
				continue;

			}

			//����::ʹ����Ʒ(item.dindex);
			temp = get_EquipInfobyIndex(0xA);//�����
			//if (temp.��ɫ <= item.��ɫ)
			//{
			//	����::CALL_����װ��(item.dindex, 0xA);
			//	break;
			//}
			temp2 = get_EquipInfobyIndex(9);//�����
			if (temp.ItemId != 0 && temp2.ItemId != 0)
			{
				MyTrace(L"���½�ָ");
				����::Fun_UnWearEquip(9);
				Sleep(500);
				����::Fun_UnWearEquip(0xA);

			}
			����::ʹ����Ʒ(item.dindex);
			Sleep(300);
			�ƴ�2 = �ƴ�2 + 1;
			Sleep(300);
			//if (temp.��ɫ < item.��ɫ)
			//{
			//	����::CALL_����װ��(item.dindex, 9);
			//	break;
			//}
			continue;
		}
		if (item.dindex != -1)
		{
			����::ʹ����Ʒ(item.dindex);
			Sleep(300);
			continue;
		}
	}
}

void ����::CALL_����װ��(DWORD bagpos, DWORD SendArg)
{
	INT64 dRcx = R_QW(��Ϸģ�� + gb_ShortKey);
	INT64 dCall = ��Ϸģ�� + gc_WearEquip;
	if (dRcx)
	{
		MainUniversalCALL4(dRcx, 0, bagpos, SendArg, dCall);
	}
}
void ����::Fun_UnWearEquip(int dEquipSlot)
{
	INT64 dUiObj = UI����::getUiObjById(0x34);//root1.arkui.windowCanvas.characterInfoWnd
	MainUniversalCALL4(dUiObj, 1, dEquipSlot, 0, ��Ϸģ�� + gc_UnWearEquip);
}

void Fun_CheckBSItem_Wnd(int dNum)//��ͨ
{
	INT64 dUiObj = UI����::getUiObjByName(L"root1.arkui.windowCanvas.BS_Item_Wnd");//BS_Item_Wnd 
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
void Fun_CheckBSSelectItem_Wnd(int dItemResId, int dNum)//ѡ������ ��ȫ��
{
	INT64 dUiObj = UI����::getUiObjById(0x9C);//BS_SelectItem_Wnd  ��Ҫѡ���
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
//void Fun_CheckBSSelectItem_WndOne(int dItemResId)//ѡ������ �򿪵���
//{
//	INT64 dUiObj = UI����::getUiObjById(0x9C);//BS_SelectItem_Wnd  ��Ҫѡ���
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
	INT64 dUiObj = UI����::getUiObjById(0x9C);//BS_SelectItem_Wnd  ��Ҫѡ���
	INT64 dRCX = dUiObj + go_BSItem_WndInfo;
	DWORD dItemResId = R_DW(dRCX + 0x34);//85 ?? 0F ?? ?? ?? ?? ?? ?? 8D ?? ?? ?? 8B ?? FF ?? ?? ?? 8B ?? E8 ?? ?? ?? ?? ?? 85 ?? 0F +8+3
	INT64 dItemResAddr = getItemResAddrById(dItemResId);
	INT64 dNameAddr = R_QW(dItemResAddr + 0x10);

	CString csName = L"��";
	if (dNameAddr)
	{
		csName = R_CString(dNameAddr);
	}
	MyTrace(L"����ѡ����ƷResId %X %s", dItemResId, csName);
}
void Fun_BS_RandomItemOpenAll(DWORD dNum)//�����Ƭ��ȫ����
{
	//INT64 go_BS_RandomItemOpenAll = 0x34;
	//85 ?? 0F ?? ?? ?? ?? ?? ?? 8D ?? ?? ?? 8B ?? FF ?? ?? ?? 8B ?? E8 ?? ?? ?? ?? ?? 85 ?? 0F +8+3 ���ֽ� go_BS_RandomItemOpenAll
	INT64 dUiObj = UI����::getUiObjById(0x9B);//BS_RandomItem_Wnd 
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

void  ����::�Զ����call()
{
	INT64 dCall = ���call + ��Ϸģ��;
	INT64 rcx = R_QW(�ɼ���Ʒ���� + ��Ϸģ��);
	MainUniversalCALL4(rcx, 0, 0, 0, dCall);


}
void  ����::����ֽ���ɫcall()
{
	INT64 dCall = �ֽ���ɫcall + ��Ϸģ��;
	INT64 rcx = 0;
	//root1.arkui.windowCanvas.itemDisassembleWnd
	bool �Ƿ�� = UI����::Ѱ�Ҵ򿪴���("root1.arkui.windowCanvas.itemDisassembleWnd", rcx);
	//MyTrace(L"�Ƿ��%I64X �Ƿ��%d", rcx, �Ƿ��);
	if (rcx >= 1)
	{
		INT64 dRcx =rcx;

		MainUniversalCALL4(dRcx, 1, 1, 0, dCall);

		MainUniversalCALL4(dRcx, 2, 0, 0, dCall);
	
		MainUniversalCALL4(dRcx, 3, 0, 0, dCall);

		MainUniversalCALL4(dRcx, 4, 0, 0, dCall);
	

	}

}

bool ����::������Ʒ����()
{
	vector<Inventoryinfo_> vsk;
	vector<Inventoryinfo_> ���ֽ���Ʒ�б�;
	����::get_InventoryItemList(vsk);
	MyTrace(L"������Ʒ����%d", vsk.size());
	if (UI����::���������Ƿ���ʾ())
	{
		UI����::Fun_UiShowCtrl(0x1A);
		Sleep(300);
	}
	for (size_t i = 0; i < vsk.size(); i++)
	{
		if (vsk[i].dSlotIndex == 0x78B5)//�罻����
		{
			����::ʹ����Ʒ(vsk[i].dindex);
			Sleep(3000);
		}
		if (vsk[i].dSlotIndex == 0x7851)//�ǼǴ�½�ֲ�
		{
			����::ʹ����Ʒ(vsk[i].dindex);
			Sleep(500);
		}
		if (vsk[i].dSlotIndex == 0x7D01)//����ǿ�� �ʹ�˵��
		{
			����::ʹ����Ʒ(vsk[i].dindex);
			Sleep(500);
		}
		if (vsk[i].dSlotIndex == 0x7D00)//����
		{
			if (!UI����::���������Ƿ���ʾ())
			{
				UI����::Fun_UiShowCtrl(0x1A);
				Sleep(300);
			}
			����::ʹ����Ʒ(vsk[i].dindex);
			Sleep(500);
			MyTrace(L"ʹ�ÿ�����Ʒ �س���");
			UI����::�ڴ水��(VK_RETURN);//ʹ�ûس��� �ᵼ�����촰�ڴ� ֮�� ��Ĺ��ܰ�������ʹ
		}
		if (vsk[i].ItemResId == 0x3C4D034 || vsk[i].ItemResId == 0x3C4D032 || vsk[i].ItemResId == 0x3C4D031 || vsk[i].ItemResId == 0x3C4D033 || vsk[i].ItemResId == 0x3C4D036 || vsk[i].ItemResId == 0x3C4D035 || vsk[i].ItemResId == 0x3C4D037)//��˵���ư�
		{
			����::ʹ����Ʒ2(vsk[i].dindex);
			Sleep(500);
			Fun_BS_RandomItemOpenAll(vsk[i].dNum);
			Sleep(2000);
		}
		if (vsk[i].dSlotIndex == 0x765F)//������
		{
			for (size_t j = 0; j < vsk[i].dNum; j++)
			{
				����::ʹ����Ʒ2(vsk[i].dindex);
				Sleep(200);
			}
		}
		//if (vsk[i].dSlotIndex == 0x7EF4)//��̫��
		//{
		//	/*for (size_t j = 0; j < vsk[i].dNum; j++)
		//	{*/
		//		����::ʹ����Ʒ2(vsk[i].dindex);
		//		Sleep(200);
		//	//}

		//}
		if (vsk[i].dSlotIndex == 0x7E90)//����
		{
			����::ʹ����Ʒ2(vsk[i].dindex);
			Sleep(500);
		}
		if (vsk[i].ItemResId == 0x7A1FD)//Ѫצ������Ӳ��
		{
			����::ʹ����Ʒ2(vsk[i].dindex);
			Sleep(500);
		}
		if (vsk[i].ItemResId == 0x7C9C)//��Ա������
		{
			����::ʹ����Ʒ2(vsk[i].dindex);
			Sleep(500);
		}
		if (vsk[i].ItemResId == 205001)//��������wai'm
		{
			����::ʹ����Ʒ2(vsk[i].dindex);
			Sleep(500);
		}
		if (vsk[i].ItemResId == 0x320CB)//��������wai'm
		{
			����::ʹ����Ʒ2(vsk[i].dindex);
			Sleep(500);
		}
		if (vsk[i].ItemResId == 0x263E11A || vsk[i].ItemResId == 0x26B82D1)//��������wai'm
		{
			����::ʹ����Ʒ2(vsk[i].dindex);
			Sleep(500);
			Fun_CheckBSItem_Wnd(vsk[i].dNum);
			Sleep(500);
		}
		if (vsk[i].dSlotIndex == 0x765D)//��ë
		{
			for (size_t j = 0; j < vsk[i].dNum; j++)
			{
				����::ʹ����Ʒ2(vsk[i].dindex);
				Sleep(500);
			}
		}
		if (vsk[i].dSlotIndex == 0x765C)//��ë
		{
			if (vsk[i].ItemResId == 0x26BBF14)
			{
				continue;
			}
			if (vsk[i].ItemResId == 0x77A11)
			{
				continue;
			}
			����::ʹ����Ʒ2(vsk[i].dindex);
			Sleep(500);
		}
		if (vsk[i].WearId <= 0xA)
		{
			if (vsk[i].��ɫ <= 3 && vsk[i].dLev <= 302)
			{
				if (!����::�ж��Ƿ�Ϊ�Ƽ�װ��(vsk[i].ItemId))
				{
					���ֽ���Ʒ�б�.push_back(vsk[i]);
				}
			}
		}
	}
	if (���ֽ���Ʒ�б�.size() >= 3)
	{
		if (!UI����::bCheckItemDisassemleWnd())
		{
			UI����::Fun_UiShowCtrl(0x25);
			Sleep(1000);
		}
		if (UI����::bCheckItemDisassemleWnd())
		{
			for (size_t i = 0; i < ���ֽ���Ʒ�б�.size(); i++)
			{
				����::�Ҽ���Ʒ(���ֽ���Ʒ�б�[i].dindex);
				Sleep(200);
			}
			����::CALL_ȫ���ֽ�();
			Sleep(3000);
			UI����::Fun_UiShowCtrl(0x25);
			return false;
		}

	}
	else
	{
		if (UI����::bCheckItemDisassemleWnd())
		{
			UI����::Fun_UiShowCtrl(0x25);
			Sleep(1000);
		}
	}
	return true;
}

void ����::SetHpItemSlot(DWORD dItemId, DWORD dTargetIndex)// dTargetIndex  ��0��ʼ
{
	INT64 dCall = ��Ϸģ�� + gc_ItemShortKeySet;
	INT64 dRCX = R_QW(��Ϸģ�� + gb_PacketInfo);
	MainUniversalCALL6(dRCX, 3, 1, dTargetIndex, dItemId, 0, dCall);
	//DWORD dItemId = 0x2E63A;//��Ʒ��ԴID
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
void ����::SetBufItemSlot(DWORD dItemId, DWORD dTargetIndex)// dTargetIndex  ��0��ʼ
{
	INT64 dCall = ��Ϸģ�� + gc_ItemShortKeySet;
	INT64 dRCX = R_QW(��Ϸģ�� + gb_PacketInfo);
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

DWORD ����::�ɼ�����(DWORD ID)
{
	INT64 dRCX = R_QW(��Ϸģ�� + �ɼ���Ʒ����);
	INT64 dCall = ��Ϸģ�� + �ɼ�����call;
	DWORD addr=MainUniversalCALL4_Ret(dRCX,ID,0,0, dCall);
	return addr;
//
//#define �ɼ�����call 0x1329200
//#define �ɼ���Ʒ���� 4C75ED0
}

DWORD ����::ָ��������Ʒ����(DWORD ID)
{
	vector<Inventoryinfo_> vsk;
	����::get_InventoryItemList(vsk);
	DWORD a = 0;

	for (size_t i = 0; i < vsk.size(); i++)
	{
		if (vsk[i].dSlotIndex == ID && ID!=0)
		{
			a = a + 1;


		}

	/*	if (vsk[i].ItemName.Find(��Ʒ����) != -1)
		{
			����::ʹ����Ʒ2(vsk[i].dindex);
			break;
		}*/
	}
	return a;

}


void ����::ҩƷ��קcall(DWORD λ��, DWORD dItemId, DWORD dTargetIndex, DWORD ��Ʒ����)
{
	INT64 dCall = ��Ϸģ�� + gc_ItemShortKeySet;
	INT64 dRCX = R_QW(��Ϸģ�� + gb_PacketInfo);
	DWORD r9 = λ��;
	DWORD rdx = ��Ʒ����;
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
int �ȼ�����(int needuplv)
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
DWORD ����::����ĥװ�����(DWORD lv)
{
	vector<Equipinfo_>vsk;
	����::get_UpEquipList(vsk);
	for (size_t i = 0; i < vsk.size(); i++)
	{
		lv = �ȼ�����(lv);
		if (vsk[i].dUpgradeLev < lv)
		{
			return vsk[i].WearId;
		}
	}
	return -1;
}