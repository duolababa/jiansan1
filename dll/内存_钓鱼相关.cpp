#include "�ڴ�_�������.h"
void ����::Fun_FishThrow_��Ļ(int dPx, int dPy)
{
	INT64 ��_��ʵ���� = ����::ȡ��ʵ����();
	INT64 ��_RCX = ��_��ʵ���� + ƫ��_��ͼ_Ѱ·rcx;
	����_ ��_��ǰ���� = ����::ȡ����();
	INT64 ��_dCALL = ��Ϸģ�� + ��ַ_��ͼ_Ѱ·call;
	INT64 dMuoseInfo = R_QW(��Ϸģ�� + gb_MouseInfo);
	W_DW(dMuoseInfo + go_MousePoint, dPx);
	W_DW(dMuoseInfo + go_MousePoint+4, dPy);
	UCHAR pBuff[0x140] = { 0 };
	W_QW((ULONG64)&pBuff[0x0], 0xA00004040);
	W_DW((ULONG64)&pBuff[0xDC], 0x11300);
	W_DW((ULONG64)&pBuff[0xE0], 1);
	MainUniversalCALL4(��_RCX, (ULONG_PTR)pBuff, 0, 0, ��_dCALL);
}
void ����::Fun_FishThrow_��������(float fx, float fy,float fz)
{
	INT64 ��_��ʵ���� = ����::ȡ��ʵ����();
	INT64 ��_RCX = ��_��ʵ���� + ƫ��_��ͼ_Ѱ·rcx;
	����_ ��_��ǰ���� = ����::ȡ����();
	INT64 ��_dCALL = ��Ϸģ�� + ��ַ_��ͼ_Ѱ·call;
	����::д�������굽���2(fx, fy, fz);
	UCHAR pBuff[0x140] = { 0 };
	W_QW((ULONG64)&pBuff[0x0], 0xA00004040);
	W_DW((ULONG64)&pBuff[0xDC], 0x11300);
	W_DW((ULONG64)&pBuff[0xE0], 1);
	MainUniversalCALL4(��_RCX, (ULONG_PTR)pBuff, 0, 0, ��_dCALL);
}


//����״̬
int ����::getFishObjState()//5Ϊ��ʼ�� 1Ϊ��ͨ 3Ϊ���� 2Ϊ���ָ�̾
{

	INT64 addr_3 = ����::ȡ��ʵ����();
	INT64 dTemp = R_QW(addr_3 + 0x94);//����-0218
	INT64 dFishObj = R_QW(dTemp + go_Role_FishObj);
	if (dFishObj)
	{
		return R_BYTE(dFishObj + go_Role_FishObj_State);
	}
	return -1;
}




//��ǰ��ݼ�ҳ������
int ����::getquickSlotFrameType()//1��ͨ 3 ���� 5����
{
	INT64 dUiObj = UI����::getUiObjById( 0x2D);//quickSlotFrame
	if (dUiObj)
	{
		return R_DW(dUiObj + go_QuickSlotType);
	}
	return 0;
}


void ����::����()
{
	for (size_t i = 0; i < 3000; i++)
	{
		DWORD X = ����::getquickSlotFrameType();
		if (X == 2)
		{
			UI����::�ڴ水��(DWORD('E'));
			return;
		}

		Sleep(100);
	}


}