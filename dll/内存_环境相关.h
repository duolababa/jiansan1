#pragma once
#include "pch.h"
class ����
{
public:
	static objInfo_ getActorInfo(INT64 dObjAddr);
	static int CALL_�����Ƿ�ɽ���(INT64 ��������ָ��);
	static int CALL_�����Ƿ�ɽ���2(INT64 ��������ָ��);
	static int CALL_�����Ƿ�������(INT64 ��������ָ��);
	static void ����ȫ����������(vector<objInfo_>& vsk);
	static void ����ָ��ȫ����������(DWORD dtype, vector<objInfo_>& vsk);
	static bool �жϹ���(INT64 ����);
	static bool �ж�NPC(INT64 ����);
	static bool �жϵ�����Ʒ(INT64 ����);
	static bool �жϲɼ���(INT64 ����);
	static bool �жϻ������(INT64 ����);
	static bool ��������Ƿ�����(INT64 ����);
	static void ��������(vector<objInfo_>& ����);
	static void ����NPC(vector<objInfo_>& ����);
	static objInfo_ ȡָ������NPC(CString temp);
	static void �����ɼ���(vector<objInfo_>& ����);
	static void �����������(vector<objInfo_>& ����);
	static void ����������Ʒ(vector<objInfo_>& ����);
	static void ��������(vector<objInfo_>& ����);
	static void ����������(vector<objInfo_>& ����);
	static objInfo_ ȡָ��������Ϣ(DWORD ResId);
	static objInfo_ ȡ���������Ϣ();
	static objInfo_ ȡָ���ɼ�������Ϣ(DWORD ResId);
	static objInfo_ ȡָ��������ʾ������Ϣ(DWORD ResId, DWORD ResShow = 1);
	static objInfo_ ȡָ����Χ������ʾ������Ϣ(float x, float y, float z, float ����, DWORD ResId);
	static ����_ ȡ��������(INT64 ����);
	static bool CALL_��NPC(INT64 ����);
	static bool CALL_�˳�NPC();
	static bool CALL_NPC�Ի���֧(int �Ի����);
	static int ��ȡ��ǰ�Ի�NPC();
	static bool �Ƿ��ں�NPC�Ի�();
	static bool �Ƿ��ڼ���ҳ��();
	static bool �Ƿ��ڼ���ҳ��2();
	static bool �Ƿ��ڶ���();
	static bool ʰ��(INT64 ����);
	static bool CALL_���ָ��NPC(CString ��������);
	static bool CALL_���ָ��NPC_ByResId(DWORD ResId);
	static float ��ȡ����Ƕ�ֵ(INT64 obj);
	static int ��ȡ�����ͷż�����(INT64 obj);
	static DWORD ��ȡ��ǰ����ID();
	static void �������Ȳɼ�ID(CString ID�ı�);
};

class NPC
{
public:

	static bool CALL_ShopBuyAddItem(int dItemIndex);

	static bool ShopBuyItemClick();

	static void get_ShopItemList(vector<Inventoryinfo_>& �̵깺����);

};
