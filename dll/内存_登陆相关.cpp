#include "�ڴ�_��½���.h"

int ��½::����������(vector<CString>& vsk)
{
	vsk.clear();
	INT64 ��_rcx = R_QW(��Ϸģ�� + ��ַ_��¼_ѡ�������rcx);
	if (��_rcx == 0)
	{
		return 0;
	}
	INT64 ��_����ͷ = R_QW(��_rcx + 156);
	DWORD ��_��Ա�� = R_DW(��_rcx + 164);
	for (size_t i = 0; i < ��_��Ա��; i++)
	{
		if (i > 500)
		{
			break;
		}
		INT64 ��_���������� = ��_����ͷ + i * 51;
		string temp = UnicodeToAnsi(R_CString(��_���������� + 0));
		CString ��_���������� = CString(temp.c_str());
		if (��_���������� != L"")
		{
			vsk.push_back(��_����������);
		}

	}
	return ��_��Ա��;
}

int ��½::��ѯ���������(CString ����������)
{
	vector<CString>vsk;
	��½::����������(vsk);
	for (size_t i = 0; i < vsk.size(); i++)
	{

		if (vsk[i] == ����������)
		{
			return i;
		}
	}
	return -1;
}
bool ��½::�Ƿ��ڷ���������()
{
	INT64 ��_rcx = R_QW(��Ϸģ�� + ��ַ_��¼_ѡ�������rcx);
	int ��_��Ա�� = R_DW(��_rcx + 164);
	if (��_��Ա�� > 0)
	{
		return true;
	}
	return false;
}
bool ��½::CALL_ѡ�������(CString ����������)
{
	int ��_��������� = ��½::��ѯ���������(����������);
	if (��_��������� == -1)
	{
		return false;
	}
	INT64 ��_rcx = R_QW(��Ϸģ�� + ��ַ_��¼_ѡ�������rcx);
	INT64 ��_Call = ��Ϸģ�� + ��ַ_��¼_ѡ�������call;
	MainUniversalCALL2(��_rcx, ��_���������, ��_Call);
	return true;
}

bool ��½::�Ƿ����ȷ��Э��()
{
	INT64 ��_UI���� = UI����::getUiObjById(4);
	if (��_UI���� == 0)
	{
		return false;
	}
	if (R_DW(��_UI���� + 184) == 1)
	{
		return true;
	}
	return false;
}
bool ��½::CALL_ȷ��Э��()
{
	INT64 ��_UI���� = UI����::getUiObjById(4);
	if (��_UI���� == 0)
	{
		return false;
	}
	INT64 ��_call = ��Ϸģ�� + ��ַ_��¼_ȷ��Э��call;
	MainUniversalCALL2(��_UI����, 0, ��_call);
	return true;
}
bool ��½::CALL_ѡ��ְҵ(CString ְҵ��)
{
	int ��_ְҵID = 0;
	if (ְҵ�� == L"սʿ")
	{
		��_ְҵID = 101;
	}
	else if (ְҵ�� == L"ħ��ʦ")
	{
		��_ְҵID = 201;
	}
	else if (ְҵ�� == L"�񶷼�(Ů)")
	{
		��_ְҵID = 301;
	}
	else if (ְҵ�� == L"�񶷼�(��)")
	{
		��_ְҵID = 311;
	}
	else if (ְҵ�� == L"����(Ů)")
	{
		��_ְҵID = 501;
	}
	else if (ְҵ�� == L"����(��)")
	{
		��_ְҵID = 511;
	}
	else if (ְҵ�� == L"����")
	{
		��_ְҵID = 401;
	}
	else
	{
		return false;
	}
	INT64 ��_rcx = ��Ϸģ�� + ��ַ_��¼_ѡ��ְҵrcx;
	if (��_rcx == 0)
	{
		return false;
	}
	INT64 ��_call = ��Ϸģ�� + ��ַ_��¼_ѡ��ְҵcall;
	INT64 ������ַ = ��_call + 106;
	W_Word(��_rcx + 0x9C, ��_ְҵID);
	MainUniversalCALL2(��_rcx, 0, ��_call);
	return true;
}
bool ��½::�Ƿ���׼������()
{
	INT64 ��_UI���� = UI����::getUiObjById(9);
	if (��_UI���� == 0)
	{
		return false;
	}

	return true;
}
bool ��½::�Ƿ��ڴ�����ɫ����()
{
	INT64 ��_UI���� = UI����::getUiObjById(19);
	if (��_UI���� == 0)
	{
		return false;
	}
	return true;
}

bool ��½::�Ƿ���ѡ��ְҵ����()
{
	INT64 ��_UI���� = R_QW(��Ϸģ�� + ��ַ_��¼_ѡ��ְҵrcx);
	if (��_UI���� == 0)
	{
		return false;
	}
	if (R_BYTE(��_UI���� + 92) == 0)
	{
		return false;
	}
	return true;
}
wchar_t* β[12] = { L"jan",L"feb",L"mar",L"apr",L"may",L"jun",L"jul",L"aug",L"sept",L"oct",L"nov",L"dec" };
wchar_t* β2[7] = { L"mon",L"tues",L"wed",L"thur",L"fri",L"sat",L"sun" };
wchar_t* β3[4] = { L"spr",L"sum",L"aut",L"win" };
wchar_t* β4[4] = { L"east",L"west",L"nort",L"sort" };
bool ��½::CALL_������ɫ(int  ��������)
{
	bool mode = true;
	INT64 ��_call = ��Ϸģ�� + ��ַ_��¼_������ɫ;
	if (!��������)
	{
		�������� = 3;
	}
	INT64 cStringClassPtr = 0;
	for (size_t i = 0; i < ��������; i++)
	{
		srand(time(NULL));
		CString ����;
		//CString ���� = �������Ӣ������(1);
		switch ((rand() % 4))
		{
		case 1:
			���� = randstr(Random(6, 12)) + β[Random(0, 11)];
			break;
		case 2:
			���� = randstr(Random(6, 12)) + β2[Random(0, 6)];
			break;
		case 3:
			���� = randstr(Random(6, 12)) + β3[Random(0, 3)];
			break;
		default:
			���� = randstr(Random(6, 12)) + β4[Random(0, 3)];
			break;
		}

		MyTrace(L"�������� %s", ����);
		if (mode)
		{
			cStringClassPtr = (DWORD64)�����ڴ�2((HANDLE)-1, 0x100);
			W_QW(cStringClassPtr, UINT64(����.GetBuffer()));
			W_QW(cStringClassPtr + 8, ����.GetLength() + 1);
			MainUniversalCALL4(0x3ED, 0x5A, cStringClassPtr, 0, ��_call);
		}
		else
		{
			temp����ָ�� cStringClassPtr2;
			cStringClassPtr2.����obj = INT64(����.GetBuffer());
			cStringClassPtr2.���� = ����.GetLength() + 1;
			MainUniversalCALL4(0x3ED, 0x5A, (UINT64)&cStringClassPtr2, 0, ��_call);
		}
		Sleep(1000);
		UI����::�ڴ水��(VK_RETURN);
		Sleep(2000);
		if (mode)
		{
			�ͷ��ڴ�2((HANDLE)-1, LPVOID(cStringClassPtr), 0x100);
		}
		return true;

	}
	/*if (mode)
	{
		�ͷ��ڴ�2((HANDLE)-1, LPVOID(cStringClassPtr), 0x100);
	}*/
	return false;
}
bool ��½::CALL_�򿪴�����ɫ(int ���)
{
	INT64 ��_call = ��Ϸģ�� + ��ַ_��¼_�򿪴�����ɫcall;
	INT64 ��_rcx = UI����::getUiObjById(12);
	if (��_rcx == 0)
	{
		return false;
	}
	MainUniversalCALL2(��_rcx, ���, ��_call);
	return true;
}
int ��½::CALL_��ɫ����(vector<��½��ɫ��Ϣ_>& vsk)
{
	vsk.clear();
	��½��ɫ��Ϣ_ temp;
	INT64 ��_call = ��Ϸģ�� + ��ַ_��¼_������ɫ;
	INT64 ��_R9 = (DWORD64)�����ڴ�2((HANDLE)-1, 0x100);
	MainUniversalCALL4(0x3EB, 0x19, 0, ��_R9, ��_call);
	INT64 ��_����ͷ = R_QW(��_R9);
	DWORD ���� = R_DW(��_R9 + 8);
	for (size_t i = 0; i < ����; i++)
	{
		temp.����ָ�� = R_QW(��_����ͷ + i * 8);
		if (temp.����ָ�� != 0)
		{
			temp.dIndex = i;
			string stemp = UnicodeToAnsi(R_CString(temp.����ָ�� + 416));
			temp.���� = CString(stemp.c_str());
			temp.�ȼ� = R_DW(temp.����ָ�� + 0x278);
			vsk.push_back(temp);
		}
	}
	return ����;
}
void ��½::get_CharacterList(vector<��½��ɫ��Ϣ_>& vsk)
{
	vsk.clear();
	��½��ɫ��Ϣ_ temp;
	INT64 addr_1 = R_QW(��Ϸģ�� + gb_CharacterList);
	DWORD dtotal = R_DW(addr_1 + go_CharacterListStart + 8);
	INT64 objStartAddr = R_QW(addr_1 + go_CharacterListStart);
	DWORD dSize = go_CharacterListSize;
	for (DWORD i = 0; i < dtotal; i++)
	{
		INT64  dCharacterInfo = objStartAddr + i * dSize;
		INT64 dNameAddr = dCharacterInfo + go_CharacterName;
		INT64 dSrvId = R_QW(dCharacterInfo + go_CharacterSrvId);
		DWORD dIndex = R_W(dCharacterInfo + go_CharacterIndex);
		DWORD dJobId = R_W(dCharacterInfo + go_CharacterJob);
		DWORD dLev = R_W(dCharacterInfo + go_CharacterLev);
		CString cName = L"";
		if (dNameAddr)
		{
			cName = R_CString(dNameAddr);
			/*wchar_t buf[100];
			swprintf(buf, L"��ַ0x%I64X %s id %I64X ְҵID %X �ȼ�%d\r\n", dCharacterInfo, cName, dSrvId, dJobId, dLev);
			MyTrace(buf);*/
		}
		temp.dIndex = dIndex;
		temp.dJob = dJobId;
		temp.�ȼ� = dLev;
		temp.���� = cName;
		temp.����ָ�� = dCharacterInfo;
		temp.SrvId = dSrvId;
		vsk.push_back(temp);
	}

}
��½��ɫ��Ϣ_ ��½::getCharacterInfoByIndex(int ���)
{
	��½��ɫ��Ϣ_ temp;
	vector<��½��ɫ��Ϣ_>vsk;
	��½::get_CharacterList(vsk);
	for (size_t i = 0; i < vsk.size(); i++)
	{
		if (vsk[i].dIndex == ���)
		{
			return vsk[i];
		}
	}
	return temp;
}
bool ��½::CALL_������Ϸ(int ��ɫ���)
{
	INT64 ��_rcx = R_QW(��Ϸģ�� + ��ַ_��¼_������Ϸrcx);
	if (��_rcx == 0)
	{
		return false;
	}
	MainUniversalCALL2(��_rcx, ��ɫ���, ��Ϸģ�� + ��ַ_��¼_������Ϸcall);
	return true;
}