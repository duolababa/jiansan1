#include "�ڴ�_NPC�̵�.h"
void NPC�̵�::Fun_ShopBuyAddItem(int dItemIndex, int dum)//������1��ʼ �ȵ������
{
	INT64 addr_1 = R_QW(��Ϸģ�� + gb_ShopBase);
	int dTotal = R_DW(addr_1 + go_ShopBuyItemListStart + 8);
	if (dTotal <= 10)//������10��
	{
		MainUniversalCALL4(addr_1, dItemIndex, dum, 0, ��Ϸģ�� + gc_ShopBuyAddItem);

	}

}

void NPC�̵�::Fub_ShopBuyItemClick()//�������ť
{

	INT64 addr_1 = R_QW(��Ϸģ�� + gb_ShopBase);
	if (R_DW(addr_1 + go_ShopBuyItemState) == 0)//״̬
	{
		if (R_DW(addr_1 + go_ShopBuyItemListStart + 8))//�ж������Ʒ
		{
			UCHAR dInfoAddr[0x1000] = { 0 };
			MainUniversalCALL2((ULONG_PTR)dInfoAddr, 0, ��Ϸģ�� + gc_ShopBuyItem);
		}

	}
}

BOOL bCheckItemJob(DWORD dJobId, DWORD dItemResId)
{
	return (BOOL)MainUniversalCALL2_Ret(dItemResId, dJobId, ��Ϸģ�� + gc_ItemJobCheck);
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

void NPC�̵�::get_ShopItemList(vector<Inventoryinfo_>& vsk)
{
	vsk.clear();
	Inventoryinfo_ temp;
	__int64 addr_1 = R_QW(��Ϸģ�� + gb_ShopBase);
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
			DWORD dpinzhi = R_DW(dResAddr + 0x118);//����-0227
			CString csName = L"��";
			if (dNameAddr)
			{
				csName = R_CString(dNameAddr);
			}
			temp.dindex = dIndex;
			temp.ItemResId = dResId;
			temp.dPrice = dPrice;
			temp.dItemResAddr = dResAddr;
			temp.��ɫ = dpinzhi;
			vsk.push_back(temp);
			MyTrace(L"����%d ��ԴID %X %s ����%X Ʒ�� %d �۸�%d", dIndex, dResId, csName, dSlotIndex, dpinzhi, dPrice);
		}
	}
}

bool �жϴ����������װ��()
{
	vector<Equipinfo_>vsk;
	����::get_EquipList(vsk);
	for (size_t i = 0; i < vsk.size(); i++)
	{

		double �;ðٷֱ� = ((double)vsk[i].�;ö�.��ǰ�;ö� / (double)vsk[i].�;ö�.����;ö�) * 100;
		//MyTrace(L"װ������ %s ��ǰ�;�:%d/%d", vsk[i].ItemName, vsk[i].�;ö�.��ǰ�;ö�, vsk[i].�;ö�.����;ö�);
		if (�;ðٷֱ� <= 60)
		{

			return true;
		}
	}
	return false;
}
bool NPC�̵�::����װ��()
{
	if (�жϴ����������װ��())
	{
		objInfo_ ���� = ����::ȡָ������NPC(L"tip.name.npcfunction_repair");
		if (����.dResId != 0)
		{
			����::��ָ���ص���NPC����װ��(��ͼ::ȡ��ǰ��½ID(), ��ͼ::ȡ��ͼID(), ����.����.x, ����.����.y, ����.����.z, 50, ����.dResId);
			return true;
		}

	}
	return false;
}

bool NPC�̵�::����ҩˮ()
{
	DWORD �ȼ� = ����::ȡ��ɫ��Ϣ().�ȼ�;
	if (�ȼ� >= 40)
	{
		if (����::����ָ����Ʒ����(0x2E63E) < 100)
		{
			objInfo_ ҩƷ���� = ����::ȡָ������NPC(L"tip.name.npcfunction_shop_potion");
			if (ҩƷ����.dResId != 0)
			{
				if (����::ȡ������() > 12000)
				{
					����::��ָ���ص���NPC����Ʒ(��ͼ::ȡ��ǰ��½ID(), ��ͼ::ȡ��ͼID(), ҩƷ����.����.x, ҩƷ����.����.y, ҩƷ����.����.z, ҩƷ����.dResId, 200, 0x2E63E, 200);
					return true;
				}

			}
		}
		return false;
	}
	if (�ȼ� >= 28 && �ȼ� <= 40)
	{
		if (����::����ָ����Ʒ����(0x2E63D) < 50)
		{
			objInfo_ ҩƷ���� = ����::ȡָ������NPC(L"tip.name.npcfunction_shop_potion");
			if (ҩƷ����.dResId != 0)
			{
				if (����::ȡ������() > 3500)
				{
					����::��ָ���ص���NPC����Ʒ(��ͼ::ȡ��ǰ��½ID(), ��ͼ::ȡ��ͼID(), ҩƷ����.����.x, ҩƷ����.����.y, ҩƷ����.����.z, ҩƷ����.dResId, 200, 0x2E63D, 100);
					return true;
				}

			}
		}
	}
	return false;
}
//bool NPC�̵�::��Ʒ���()
//{
//	objInfo_ ��� = ����::ȡָ������NPC(L"tip.name.npcfunction_stash");
//	if (���.dResId != 0)
//	{
//
//	}
//
//}

void NPC�̵�::Fun_BarterShopExchange(DWORD dItemIndex, DWORD dNum)//������Ʒ
{

	INT64 addr_1 = R_QW(��Ϸģ�� + gb_ShopBase);

	//UCHAR dInfoAddr[0x1000] = { 0 };
	if (!IsBadReadPtr((void*)addr_1, sizeof(addr_1)))
	{
		MainUniversalCALL4(addr_1, dItemIndex, dNum, 0, ��Ϸģ�� + gc_BarterShopExchange);
	}


}