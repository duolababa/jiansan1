#include "�ڴ�_�������.h"
bool ����::CALL_������Ļ()
{
	//INT64 ��_��ȡ��Ļ����call = ��Ϸģ�� + ��ַ_����_��ȡ��Ļ����call;
	//INT64 ��_��ȡ��Ļ����rcx = R_QW(��Ϸģ�� + ��ַ_����_��ȡ��Ļ����rcx);
	INT64 ��_������ĻCALL = ��Ϸģ�� + ��ַ_����_������Ļcall;
	INT64 ��_��Ļ���� = UI����::getUiObjById(0x166);
	if (��_��Ļ���� == 0)
	{
		return false;
	}
	MainUniversalCALL2(��_��Ļ����, 0, ��_������ĻCALL);
	return true;
}
bool ����::CALL_�˳�����()
{
	INT64 ��_call = ��Ϸģ�� + ��ַ_����_�˳�����call;
	MainUniversalCALL2(0, 0, ��_call);
	return true;
}

bool ����::CALL_ѡ������(DWORD ְҵID)
{
	INT64 ��_call = ��Ϸģ�� + ��ַ_����_ѡ��ְҵcall;
	MainUniversalCALL2(ְҵID, 1, ��_call);
	return true;
}

bool ����::CALL_ѡ��ְҵ(DWORD ְҵID)
{
	INT64 ��_call = ��Ϸģ�� + ��ַ_����_ѡ��ְҵcall;
	MainUniversalCALL2(ְҵID, 2, ��_call);
	return true;
}
bool ֱ��::CALL_������Ļ(DWORD index) //1��ʼ 1-6
{
	//INT64 ��_��ȡ��Ļ����call = ��Ϸģ�� + ��ַ_����_��ȡ��Ļ����call;
	//INT64 ��_��ȡ��Ļ����rcx = R_QW(��Ϸģ�� + ��ַ_����_��ȡ��Ļ����rcx);
	INT64 rcx = R_QW(��Ϸģ�� + ��ַ_ֱ��_������Ļrcx);
	INT64 dCALL = ��Ϸģ�� + ��ַ_ֱ��_������Ļcall;
	if (rcx)
	{
		MainUniversalCALL4(rcx, 1, index, 0, dCALL);
		return false;
	}

	return true;
}