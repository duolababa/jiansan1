#pragma once
#include "pch.h"
class ������ӡ
{
public:
	static void getAbilityEngraveAll();
	static int getEngraveDragLevById(int dEngraveId);
	static void Fun_EngraveDrag(int dEngraveId, int dPos);
};
class ����ʯ
{
public:

	static void getmarbleWndItemList();
	static bool ����ʯǿ��();

};

class ��ĥ
{
public:
	static INT64 getItemBuildUpItemList();//��ĥ������Ʒ���� ok
	static BOOL bCheckitemBuildUpRenderTargetGroupShow();//�ж����ճɹ�����
	static BOOL bCheckitemBuildUpSuccess_mc();//�ж����ճɹ�����
	static BOOL bCheckitemBuildUpFail_mc();//�ж����ճɹ�����
	static int ��ĥ::Fun_ReadItemBuildUpListSelect();
	//static BOOL bCheckItemBuildUpLevelWndContentChildWindowShow(DWORD dChildIndex);
	//static void Fun_ItemBuildUpListSelect(int dIndex);	//ѡ����Ҫǿ����Ʒ ������0��ʼ ok
	//static void Fun_ItemBuildUpLevelUp();//������ ������ť��� ok
	//static void Fun_ItemBuildUpLevelUpGrade();// ������װ����ĥ��ť���   ok

	//static void Fun_ItemBuildUpChildMaxClick();//�ӽ���1 max��ť���   ok
	//static void Fun_ItemBuildUpChildLevelUpBtnClick();//�ӽ���1 �ɳ����  ok	

	//static void Fun_ItemBuildUpChildLevelUpGradeBtnClick();	//�ӽ���2 װ����ĥ��� ok

	//static void Fun_ItemBuildLevUpResult();//�鿴�����ť ���   ok
	static void Fun_ItemBuildLevUpSucess();//���ȷ�� ���  ok ����Fun_ItemBuildLevUpResult ����� �м�ӵ��ӳ�5000
	//static bool ��ĥ::ѡ��װ���Ƿ������();
	static BOOL bCheckItemBuildUpLevelWndContentChildWindowShow(DWORD dChildIndex);

	static bool ǿ��װ��();
	static bool ǿ��װ��(int lv);
};

