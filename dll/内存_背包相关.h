#pragma once
#include "pch.h"
class ����
{
public:
    static void get_InventoryItemList(vector<Inventoryinfo_>& vsk);
    static void get_EquipList(vector<Equipinfo_>& vsk);
    static void get_UpEquipList(vector<Equipinfo_>& vsk);
    static void get_LifeToolList(vector<Equipinfo_>& vsk);
    static void get_feicangkuList(vector<Inventoryinfo_>& vsk);
    static void get_cangkuList(vector<Inventoryinfo_>& vsk);

    static Inventoryinfo_ ȡ�����ֿ�(CString name);
    static Inventoryinfo_ ȡ�����ֿ�(CString name);

    static bool ȡ��call(DWORD ��λ, DWORD �Ƿ񹫹��ֿ�);
    static bool ָ��λ��������Ƿ���װ��(DWORD ��λ);
    static Equipinfo_ get_EquipInfobyIndex(DWORD type);
    static DWORD ȡ�����();
    static DWORD ȡ������();
    static DWORD ȡ�������();
    static INT64 getMoneyNumByType(int dMoneyType);
    static void ά��װ��(DWORD ��_��������);
    static void ʹ����Ʒ(DWORD ������);
    static void ʹ��������Ʒ(DWORD ������);
    static void �Ҽ���Ʒ(DWORD ������);
    static void ������Ʒcall(INT64 ItemId);
    static DWORD �������();
    

    static void ʹ����Ʒ2(DWORD ������);
    static void get_RecommendEquipList(vector<Inventoryinfo_>& vsk);
    static int get_PosbyItemID(DWORD itemId);
    static Inventoryinfo_ get_ItemInfobyItemID(DWORD itemId);
    static void ʹ�ñ���ָ����Ʒ(CString ��Ʒ����);
    static void ʹ�ñ���ָ����Ʒ_ByResId(DWORD ResId);
    static void װ������ָ����Ʒ_ByResId(DWORD ResId);
    static DWORD ����ָ����Ʒ����(DWORD ResId);
    static bool �ж��Ƿ�Ϊ�Ƽ�װ��(INT64 ItemId);
    static void �Զ�װ���Ƽ�װ��();
    static void CALL_����װ��(DWORD bagpos, DWORD SendArg);
    static void Fun_UnWearEquip(int dEquipSlot);
    static bool ������Ʒ����();
    static void  ����ֽ���ɫcall();
    static void  �Զ����call();
    static void SetHpItemSlot(DWORD dItemId, DWORD dTargetIndex);
    static void SetBufItemSlot(DWORD dItemId, DWORD dTargetIndex);
    static void ҩƷ��קcall(DWORD λ��, DWORD dItemId, DWORD dTargetIndex, DWORD ��Ʒ����);
    static DWORD ����ĥװ�����(DWORD lv);
    static DWORD �ɼ�����(DWORD ID);
    static DWORD ָ��������Ʒ����(DWORD ID);
};

int getEquipWearArg(int dSlotIndex);