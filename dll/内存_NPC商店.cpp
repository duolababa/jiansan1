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

void NPC�̵�::��ȡ����(DWORD ID)
{
	INT64 addr_1 = R_QW(��Ϸģ�� + �̳�����rcx);


	MainUniversalCALL4(addr_1, ID, 0, 0, ��Ϸģ�� + ������д���ַ);
}



DWORD NPC�̵�::��ѯ��ʯ����()
{
	INT64 rcx = ��Ϸģ�� + ��ʯrcx;

	DWORD num = R_DW(rcx + g_��ʯ);
	INT64 addr = rcx + g_��ʯ + 2;
	if (num > 6)
	{
		num = 5;

	}
	//MyTrace(L"����%d", num);
		for (size_t i = 0; i < num; i++)
		{
			double c=R_double(addr+i*0x11);
			int b = static_cast<int>(c);
			//MyTrace(L"������%d", b);
			if (b!= 0)
			{
				MyTrace(L"������%d", b);
				return c;
			}

		}
		return 0;

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


void NPC�̵�::funshop(DWORD ID,DWORD ����)
{
	//	vector<Inventoryinfo_>vsk;
	vector<�̳���Ϣ_> vsk;
	DWORD W=0;
		NPC�̵�::shoppingmall(vsk);
		for (size_t i = 0; i < vsk.size(); i++)
		{

			if (ID == vsk[i].WearId)
			{
				

				if (UI����::���ڷ����ı�().Find(L"Do you want to purchase") != -1)
				{
					W = W + 1;
					UI����::�ڴ水��1(g_ENTER);
					Sleep(2222);
				}

				INT64 rcx = R_QW(��Ϸģ�� + ��ַ_����_����);
				INT64 rdx = ��Ϸģ�� + ����Ʒrdx;

				MainUniversalCALL6(rcx, rdx, ID, 0, vsk[i].ItemId, 0, ��Ϸģ�� + ����Ʒcall);
				Sleep(2222);


				INT64 rcx1;
				bool �Ƿ�� = UI����::Ѱ�Ҵ򿪴���("root1.arkui.windowCanvas.cashShopBuyWnd", rcx1);
				if (rcx != 0)
				{
					DWORD dResId = R_DW(rcx1 + ƫ��_UI_��ʾ);
					if (dResId == 1)
					{
						MainUniversalCALL4(rcx1, 0, 0, 0, ��Ϸģ�� + ������Ʒ����д���ַ);
						Sleep(4000);
					}


					if (UI����::���ڷ����ı�().Find(L"Do you want to purchase") != -1)
					{
						W = W + 1;
						UI����::�ڴ水��1(g_ENTER);
						Sleep(5000);
					}



				}





			}
			
			if (W >= ����)
			{
				break;
			}


		}



}
void NPC�̵�::openshop(vector<�̳���Ϣ_>& vsk)
{
	vsk.clear();

	INT64 addr_1 = R_QW(��Ϸģ�� + �̳�����rcx);
	INT64 addr = R_QW(addr_1 + g_�̳Ǳ���);
	DWORD dtotal = R_DW(addr_1 + g_�̳Ǳ��� + 8);
	for (size_t i = 0; i < dtotal; i++)
	{
		DWORD ID = R_DW(addr + i * g_�̳�ѭ��);
		�̳���Ϣ_ temp;
		temp.WearId = ID;

		INT64 dNameAddr = addr + i * g_�̳�ѭ�� + 0x78;
		CString csName = L"��";
		if (dNameAddr)
		{
			csName = R_CString(dNameAddr);
			temp.CName = csName;
		}
		vsk.push_back(temp);

	}



}


void NPC�̵�::shoppingmall(vector<�̳���Ϣ_>& vsk)
{
	vsk.clear();

	INT64 addr_1 = R_QW(��Ϸģ�� + �̳�����rcx);
	INT64 addr = R_QW(addr_1 + g_�̳Ǳ���x);
	DWORD dtotal = R_DW(addr_1 + g_�̳Ǳ���x+8);


	if (dtotal < 1)
	{
		UI����::Fun_UiShowCtrl(190);
		Sleep(9000);
		 addr_1 = R_QW(��Ϸģ�� + �̳�����rcx);
		 addr = R_QW(addr_1 + g_�̳Ǳ���x);
		 dtotal = R_DW(addr_1 + g_�̳Ǳ���x + 8);
	}
	//MyTrace(L"����%d", dtotal);
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
					�̳���Ϣ_ temp;
					temp.ItemId = ItemId;
					temp.WearId = R_DW(addr_shop + b * 0x10);
					//MyTrace(L"ID%d", temp.ItemId);
				/*	INT64 dItemResAddr = getItemResAddrById(temp.WearId);
					MyTrace(L"dItemResAddr0x%I64x", dItemResAddr);
					INT64 dNameAddr = R_QW(dItemResAddr + 0x10);
					CString csName = L"��";
					if (dNameAddr)
					{
						csName = R_CString(dNameAddr);
						temp.CName = csName;
					}*/



					vsk.push_back(temp);
			//	MyTrace(L" ��ԴID%d ����0x%I64x", temp.WearId, temp.ItemId);
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
	//MyTrace(L"�̵�OBJ 0x%I64X", objStartAddr);
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
			//MyTrace(L"����%d ��ԴID %X %s ����%X Ʒ�� %d �۸�%d", dIndex, dResId, csName, dSlotIndex, dpinzhi, dPrice);
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
		////MyTrace(L"װ������ %s ��ǰ�;�:%d/%d", vsk[i].ItemName, vsk[i].�;ö�.��ǰ�;ö�, vsk[i].�;ö�.����;ö�);
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
	if (addr_1 > 1)
	{
		MainUniversalCALL4(addr_1, dItemIndex, dNum, 1, ��Ϸģ�� + gc_BarterShopExchange);
	}

	


}

DWORD ����::��ѯ���call()
{
	INT64 rcx = R_QW(��Ϸģ�� + ��ַ_����_��ȡ��������rcx);

	INT64 ret = MainUniversalCALL4_Ret(rcx, 0xD8, 0, 0, ��Ϸģ�� + ���׽��call);

	INT64 rcx1 = R_QW(ret + 0x10);

	//MyTrace(L"rcx1 0x%I64X", rcx1);


	DWORD x = R_DW(rcx1 +g_�г�����۸�+4);
		return x;

}

void ��ʼ�ʼ�()
{
	INT64 rcx = 0;
	bool �Ƿ�� = UI����::Ѱ�Ҵ򿪴���("root1.arkui.windowCanvas.mailWnd", rcx);
	if (rcx > 1)
	{
	MainUniversalCALL4(rcx, 0, 0, 0, ��Ϸģ�� + send�ʼ�call);
	}
	
	
}
DWORD �ʼ�ѡ�()
{
	INT64 rcx = R_QW(��Ϸģ�� + gb_ExpressMailList);
	DWORD rcx1 = R_DW(rcx + �ʼ�ѡ��);//E8 ?? ?? ?? ?? 85 FF 0F 88 ?? ?? ?? ?? 83 FF ?? 7E ?? 83 FF ?? 0F 85 ?? ?? ?? ?? 8D 57 ?? 48 8B CB +0 ��CALL


	return rcx1;

	//INT64 call = ��Ϸģ�� + �ʼ�ѡ�call;
	//MainUniversalCALL4(rcx, ID, 0, 0, call);
}

bool �Ƿ�����()
{
	DWORD rcx = R_BYTE(��Ϸģ�� + ����Ƿ񼤻�);
		if (rcx != 0)
		{
			return 1;
		}
		return 0;
}




void �����ʼ�����(CString name)
{
		INT64 call = ��Ϸģ�� + �ʼ������ǳ�call;
		INT64 rcx = R_QW(��Ϸģ�� + gb_ExpressMailList);
		temp����ָ�� cStringClassPtr2;
		cStringClassPtr2.����obj = INT64(name.GetBuffer());
		cStringClassPtr2.���� = name.GetLength() + 1;
	//	INT64 rcx1 = 0;
	//	bool �Ƿ�� = UI����::Ѱ�Ҵ򿪴���("root1.arkui.windowCanvas.mailWnd", rcx1);

		//if (rcx1 > 1)
		//{
		//	W_QW(rcx1+0x578, (UINT64)&cStringClassPtr2);
		//}

		MainUniversalCALL4(rcx, (UINT64)&cStringClassPtr2, 0, 0, call);

}
void �����ʼ���Ʒ(DWORD ID, DWORD ����,DWORD ��Ʒλ��)
{
	INT64 call = ��Ϸģ�� + �ʼ������Ʒcall;
	//INT64 call1 = ��Ϸģ�� + �ʼ������Ʒcall1;//��Դ��Ʒ
	INT64 rcx = R_QW(��Ϸģ�� + gb_ExpressMailList);

	if (��Ʒλ�� != 0)
	{

		MainUniversalCALL6(rcx,0xFFFFFFFF,ID, ����,1,0, call);
	}
	else
	{

		vector<Inventoryinfo_> vsk2;
		����::get_InventoryItemList(vsk2);
		DWORD a = 0;

		for (size_t i = 0; i < vsk2.size(); i++)
		{
			if (vsk2[i].ItemResId == ID && vsk2[i].dNum >= ����)
			{
				MainUniversalCALL6(rcx, vsk2[i].dindex, ID, ����, 1, 0, call);

			}

	//MyTrace(L"λ��%d  ��ƷID 0x%I64X ��ԴID  0x%I64X ����%d  ��������%d �;�%d  ���� %s ��Ʒ�ȼ�%d ��Ʒ����0x%I64X \r\n", vsk2[i].dindex, vsk2[i].ItemId, vsk2[i].ItemResId, vsk2[i].dNum, vsk2[i].dSlotIndex, vsk2[i].�;ö�.��ǰ�;ö�, vsk2[i].ItemName, vsk2[i].dLev, vsk2[i].dItemResAddr);
		
		}



	}




}





void  ����::�Զ�����(DWORD ID, DWORD ����, DWORD �۸�, INT64 ��ƷID1)
{
	INT64 rcx = R_QW(��Ϸģ�� + �Ǽ�rcx);
	INT64 rdx = rcx+ g_�г�����rdx;
	INT64 call = ��Ϸģ�� + ����д���ַ;
	W_QW(rdx, ID);
	if (��ƷID1 > 1)
	{
		W_QW(rdx+8, ��ƷID1);
	}

	W_DW(rdx +  0x10, ����);
	W_DW(rdx + 0x14, �۸�);
	if (��ƷID1 == 0)
	{
		W_DW(rdx + 0x1C, 0);
		W_DW(rdx+0x1D ,1);
	}



MainUniversalCALL2(rcx, rdx, call);
}

bool ����::�������Ƿ��()
{
	INT64 rcx = 0;
	bool �Ƿ�� = UI����::Ѱ�Ҵ򿪴���("root1.arkui.windowCanvas.exchangeShopWnd", rcx);
	if (rcx >= 1)
	{
		DWORD dResId = R_DW(rcx + ƫ��_UI_��ʾ);
		if (dResId == 1)
		{
			return 1;
		}


	}

	return 0;
}







void ����::�Ǽ�����(DWORD ID, DWORD ID1)
{

	INT64 call = ��Ϸģ�� + �Ǽ�call;
	INT64 rcx = 0;

	if (ID1 == 1)
	{

	}
	else
	{
		bool �Ƿ�� = UI����::Ѱ�Ҵ򿪴���("root1.arkui.windowCanvas.exchangeShopWnd", rcx);
		if (rcx >= 1)
		{
			MainUniversalCALL2(R_QW(rcx + g_�Ǽ���Ʒ), ID, call);

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