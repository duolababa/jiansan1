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
	static void shoppingmall(vector<�̳���Ϣ_>& vsk);
	static void openshop(vector<�̳���Ϣ_>& vsk);
	static void funshop(DWORD ID, DWORD ����);
	static DWORD ��ѯ��ʯ����();

	static void ��ȡ����(DWORD ID);
	//static void get_ShopItemList();
};

class ����
{
public:


	static DWORD ��ѯ���call();
	static void �Զ�����(DWORD ID, DWORD ����, DWORD �۸�, INT64 ��ƷID1);
	static 	bool ����::�������Ƿ��();
	static DWORD �г�����(DWORD ID);
	static INT64 ����_��ȡ��������(DWORD ID);

};

void �����ʼ�����(CString name);
void �����ʼ���Ʒ(DWORD ID, DWORD ����, DWORD ��Ʒλ��);
DWORD �ʼ������Ʒ����();
void ��ʼ�ʼ�();
DWORD �ʼ�ѡ�();
bool �Ƿ�����();