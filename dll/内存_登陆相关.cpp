#include "�ڴ�_��½���.h"
#include <random>
int ��½::����������(vector<CString>& vsk)
{
	vsk.clear();
	INT64 ��_rcx = R_QW(��Ϸģ�� + ��ַ_��¼_ѡ�������rcx);
	if (��_rcx == 0)
	{
		return 0;//[[0x50B7888+lostark.0]+9c]+0*33+3
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
		string temp = UnicodeToAnsi(R_CString(��_���������� +3));
		CString ��_���������� = CString(temp.c_str());
		if (��_���������� != L"")
		{
			MyTrace(L"%s", ��_����������);
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
	else if (ְҵ�� == L"��Ů")
	{
		��_ְҵID = 301;
	}
	else if (ְҵ�� == L"����")
	{
		��_ְҵID = 311;
	}
	else if (ְҵ�� == L"��ǹ")
	{
		��_ְҵID = 501;
	}
	else if (ְҵ�� == L"Ůǹ")
	{
		��_ְҵID = 511;
	}
	else if (ְҵ�� == L"�̿�")
	{
		��_ְҵID = 401;
	}
	else if (ְҵ�� == L"ר��")
	{
		��_ְҵID = 601;
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

std::string generateRandomString(int minLength, int maxLength) {
	// ���������ͷֲ�
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<int> dist(0, 25); // ���� 0 �� 25 ֮�������

	// �����ַ�������
	std::random_device rdLength;
	std::mt19937 genLength(rdLength());
	std::uniform_int_distribution<int> distLength(minLength, maxLength);
	int length = distLength(genLength);

	// ���ɵ�һ����ĸ����д��ĸ��
	char firstLetter = 'A' + dist(gen);

	// ����ʣ����ĸ
	std::string randomString;
	randomString += firstLetter;

	for (int i = 1; i < length; i++) {
		char letter = 'a' + dist(gen);
		randomString += letter;
	}

	return randomString;
}


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

		CString ����;
		���� = CStringA(generateRandomString(12, 15).c_str());

			temp����ָ�� cStringClassPtr2;
			cStringClassPtr2.����obj = INT64(����.GetBuffer());
			cStringClassPtr2.���� = ����.GetLength() + 1;
			MainUniversalCALL4(0x3ED, 0x5D, (UINT64)&cStringClassPtr2, 0, ��_call);
		//}45 33 C9 4C 8D 44 24 ?? 8D 57 ?? B9 ?? ?? ?? ??      RCX  +B     RDX  B
		Sleep(1000);

		UI����::�ڴ水��1(g_ENTER);
		Sleep(2000);
		return true;

	}

	return false;
}

bool ��½::��¼�����ɫ(int ���)
{
	INT64 ��_call = ��Ϸģ�� + �л���ɫcall;
	INT64 ��_UI���� = R_QW(��Ϸģ�� + ��ַ_��¼_������Ϸrcx);
	if (��_UI���� == 0)
	{
		return false;
	}
	MainUniversalCALL4(��_UI����, ���, 1, 0, ��_call);
	return true;
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
//int ��½::CALL_��ɫ����(vector<��½��ɫ��Ϣ_>& vsk)
//{
//	vsk.clear();
//	��½��ɫ��Ϣ_ temp;
//	INT64 ��_call = ��Ϸģ�� + ��ַ_��¼_������ɫ;
//	INT64 ��_R9 = (DWORD64)�����ڴ�2((HANDLE)-1, 0x100);
//	MainUniversalCALL4(0x3EB, 0x19, 0, ��_R9, ��_call);
//	INT64 ��_����ͷ = R_QW(��_R9);
//	DWORD ���� = R_DW(��_R9 + 8);
//	for (size_t i = 0; i < ����; i++)
//	{
//		temp.����ָ�� = R_QW(��_����ͷ + i * 8);
//		if (temp.����ָ�� != 0)
//		{
//			temp.dIndex = i;
//			string stemp = UnicodeToAnsi(R_CString(temp.����ָ�� + 416));
//			temp.���� = CString(stemp.c_str());
//			temp.�ȼ� = R_DW(temp.����ָ�� + 0x278);
//			vsk.push_back(temp);
//		}
//	}
//	return ����;
//}
DWORD getCharacterGetJumpState(__int64 dCharacterInfo)
{
	if (!dCharacterInfo) return 0;
	INT64 ret = MainUniversalCALL2_Ret(dCharacterInfo, 0, ��Ϸģ�� + gc_CharacterGetJumpState);
	/*wchar_t buf[100];
	dm.AsmClear();
	dm.AsmAdd(L"sub rsp,040");
	wsprintf(buf, L"MOV RCX, 0%I64X", dCharacterInfo);
	dm.AsmAdd(buf);
	wsprintf(buf, L"MOV RDI, 0%I64X", gc_CharacterGetJumpState);
	dm.AsmAdd(buf);
	dm.AsmAdd(L"call rdi");
	dm.AsmAdd(L"add rsp,040");*/
	return (DWORD)ret;
}
void ��½::get_CharacterList(vector<��½��ɫ��Ϣ_>& vsk)
{
	vsk.clear();
	��ɫ��Ϣ ="";
	CString ��ʱְҵ=L" ";
	CString ��ʱװ��=L" ";
	��½��ɫ��Ϣ_ temp;
	INT64 addr_1 = R_QW(��Ϸģ�� + gb_CharacterList);
	DWORD dtotal = R_DW(addr_1 + go_CharacterListStart + 8);
	INT64 objStartAddr = R_QW(addr_1 + go_CharacterListStart);
	DWORD dSize = go_CharacterListSize;
	for (DWORD i = 0; i < dtotal; i++)
	{//[[0x50B52C8+LOSTARK.0]+A4]+0*0x1AE4
		INT64  dCharacterInfo = objStartAddr + i * dSize;
		DWORD dJumpState = getCharacterGetJumpState(dCharacterInfo);//Ϊ1ֱ���� Ϊ3 ��ֱ��
		INT64 dNameAddr = dCharacterInfo + go_CharacterName;
		INT64 dSrvId = R_QW(dCharacterInfo + go_CharacterSrvId);
		DWORD dIndex = R_W(dCharacterInfo + go_CharacterIndex);
		DWORD dJobId = R_W(dCharacterInfo + go_CharacterJob);
		DWORD dLev = R_W(dCharacterInfo + go_CharacterLev);
		float װ��=R_Float(dCharacterInfo + go_Characterװ������);

		CString cName = L"";
		if (dNameAddr)
		{
			cName = R_CString(dNameAddr);
			wchar_t buf[100];
			swprintf(buf, L"��ַ0x%I64X %s id %I64X ְҵID %X �ȼ�%d װ�� %0.3f\r\n", dCharacterInfo, cName, dSrvId, dJobId, dLev, װ��);
			MyTrace(buf);
		}
		temp.dIndex = dIndex;
		temp.dJob = dJobId;
		temp.�ȼ� = dLev;
		temp.װ�� = װ��;

		temp.ֱ��״̬ = dJumpState;
		temp.���� = cName;
		temp.����ָ�� = dCharacterInfo;
		temp.SrvId = dSrvId;
		��ʱְҵ = ��ʱְҵ + ConvertDWORDToString(dJobId)+L"|";
		��ʱװ�� = ��ʱװ�� + ConvertDWORDToString((int)temp.װ��) + L"|";

		//temp.Format(L"%f", ��ɫ��Ϣ.����.z);//3
		//arr.push_back(temp);
		
		//	���͸�����̨1(ConvertDWORDToString(GameIndex), "��¼", "��ʼ���ɹ�");
		vsk.push_back(temp);
	}
	��ɫ��Ϣ = ��ʱװ��+ ��ʱְҵ;
	���͸�����̨1(ConvertDWORDToString(GameIndex), L"װ��ְҵ", ��ɫ��Ϣ);
}
//��½��ɫ��Ϣ_ ��½::getCharacterInfoByIndex(int ���)
//{
//	��½��ɫ��Ϣ_ temp;
//	vector<��½��ɫ��Ϣ_>vsk;
//	��½::get_CharacterList(vsk);
//	for (size_t i = 0; i < vsk.size(); i++)
//	{
//		if (vsk[i].dIndex == ���)
//		{
//			return vsk[i];
//		}
//	}
//	return temp;
//}
bool ��½::CALL_������Ϸ(int ��ɫ���)
{
	INT64 ��_rcx = R_QW(��Ϸģ�� + ��ַ_��¼_������Ϸrcx);
	if (��_rcx == 0)
	{
		return false;
	}
	��ǰִ�н�ɫ = ��ɫ���;
	MainUniversalCALL2(��_rcx, ��ɫ���, ��Ϸģ�� + ��ַ_��¼_������Ϸcall);
	//Sleep(5000);
	//INT64 addr = 0;
	//CString	name = L" ";
	// addr = ����::����ȡ����call(11300,13540);
	////MyTrace(L"ִ�е�1��call");
	//if (addr > 1)
	//{
	//
	//	name = UI����::UI����1(addr);
	//	if (name.GetLength() != 0 && name.Find(L"start") != -1)
	//	{
	//		UI����::�ؼ����call(addr);
	//		Sleep(3000);
	//	}

	//}

	//addr = 0;
	//name = L" ";
	//addr = ����::����ȡ����call(10740,3340);
	////MyTrace(L"ִ�е�1��call");
	//if (addr > 1)
	//{
	//
	//	name = UI����::UI����1(addr);
	//	if (name.GetLength() != 0 && name.Find(L"tab_0") != -1)
	//	{
	//		UI����::�ؼ����call(addr);
	//		Sleep(3000);
	//	}

	//}

	//addr = 0;
	//name = L" ";
	//addr = ����::����ȡ����call(12760,13520);
	////MyTrace(L"ִ�е�1��call");
	//if (addr > 1)
	//{

	//	name = UI����::UI����1(addr);
	//	if (name.GetLength() != 0 && name.Find(L"start_btn") != -1)
	//	{
	//		UI����::�ؼ����call(addr);
	//		Sleep(3000);
	//	}

	//}

	//addr = 0;
	//name = L" ";
	//addr = ����::����ȡ����call(12820,13620);
	////MyTrace(L"ִ�е�1��call");
	//if (addr > 1)
	//{

	//	name = UI����::UI����1(addr);
	//	if (name.GetLength() != 0 && name.Find(L"gameStartBtn") != -1)
	//	{
	//		UI����::�ؼ����call(addr);
	//		Sleep(3000);
	//	}

	//}





	return true;
}
int ��½::getJumpMapCheck(int dIndex)//������1��ʼ
{
	__int64 addr_1 = R_QW(��Ϸģ�� + gb_AccountSpecInfo);
	BYTE dCurSeverIndex = R_BYTE(��Ϸģ�� + gb_CurSeverIndex);//���ֽ�
	INT64 ret = MainUniversalCALL4_Ret(addr_1, 3, dIndex, dCurSeverIndex, ��Ϸģ�� + gc_AccountSpecCheck);
	/*wchar_t buf[100];
	dm.AsmClear();
	dm.AsmAdd(L"sub rsp,040");
	wsprintf(buf, L"MOV R9D, 0%X", dCurSeverIndex);
	dm.AsmAdd(buf);
	wsprintf(buf, L"MOV R8D, 0%X", dIndex);
	dm.AsmAdd(buf);
	wsprintf(buf, L"MOV EDX, 0%X", 3);
	dm.AsmAdd(buf);
	wsprintf(buf, L"MOV RCX, 0%I64X", addr_1);
	dm.AsmAdd(buf);
	wsprintf(buf, L"MOV RDI, 0%I64X", gc_AccountSpecCheck);
	dm.AsmAdd(buf);
	dm.AsmAdd(L"call rdi");
	dm.AsmAdd(L"add rsp,040");*/
	return (DWORD)ret;
}
DWORD ��½::getJmpMapList()//��ȡֱ���׶ε�ͼ��Ϣ
{
	for (int i = 0; i < 6; i++)
	{
		if (getJumpMapCheck(i + 1))
		{
			return i + 1;
		MyTrace(L"ֱ����ͼ%d ��ȯ", i + 1);
		}
	
	}
	return 0;
}
void ��½::Fun_UseJumpByIndex(__int64 dCharacterSrvId, int dIndex)//������1��ʼ  ʹ��ֱ��
{
	__int64 addr_1 = R_QW(��Ϸģ�� + gb_CharacterList);
	BYTE dCurSeverIndex = R_BYTE(��Ϸģ�� + gb_CurSeverIndex);//���ֽ�
	MainUniversalCALL4_Ret(addr_1, dCharacterSrvId, 3, dIndex, ��Ϸģ�� + gc_UesJumpByIndex);
	//wchar_t buf[100];
	//dm.AsmClear();
	//dm.AsmAdd(L"sub rsp,040");
	//wsprintf(buf, L"MOV R9D, 0%X", dIndex);
	//dm.AsmAdd(buf);
	//wsprintf(buf, L"MOV R8D, 0%X", 3);
	//dm.AsmAdd(buf);
	//wsprintf(buf, L"MOV RDX, 0%I64X", dCharacterSrvId);
	//dm.AsmAdd(buf);
	//wsprintf(buf, L"MOV RCX, 0%I64X", addr_1);
	//dm.AsmAdd(buf);
	//wsprintf(buf, L"MOV RDI, 0%I64X", gc_UesJumpByIndex);
	//dm.AsmAdd(buf);
	//dm.AsmAdd(L"call rdi");
	//dm.AsmAdd(L"add rsp,040");
	//return (DWORD)dm.AsmCall(HwndGlobal, 6);
}
��½��ɫ��Ϣ_ ��½::getCharacterInfoByName(CString Name)
{
	��½��ɫ��Ϣ_ temp;
	vector<��½��ɫ��Ϣ_>vsk;
	��½::get_CharacterList(vsk);
	for (size_t i = 0; i < vsk.size(); i++)
	{
		if (vsk[i].���� == Name)
		{
			return vsk[i];
		}
	}
	return temp;
}




��½��ɫ��Ϣ_ ��½::getCharacterInfoByIndex(int ���)
{
	��½��ɫ��Ϣ_ temp;
	for (size_t i = 0; i < ȫ_��ɫ�б�.size(); i++)
	{
		if (ȫ_��ɫ�б�[i].dIndex == ���)
		{
			return ȫ_��ɫ�б�[i];
		}
	}
	/*��½��ɫ��Ϣ_ temp;
	vector<��½��ɫ��Ϣ_>vsk;
	��½::get_CharacterList(vsk);
	for (size_t i = 0; i < vsk.size(); i++)
	{
		if (vsk[i].dIndex == ���)
		{
			return vsk[i];
		}
	}*/
	return temp;
}
bool �Ƿ���ڴ˽�ɫ(��½��ɫ��Ϣ_ ��ɫ��Ϣ)
{
	for (size_t i = 0; i < ȫ_��ɫ�б�.size(); i++)
	{
		if (��ɫ��Ϣ.���� == ȫ_��ɫ�б�[i].����)
		{
			return true;
		}
	}
	return false;
}
void ��½::��ʼ��ȫ�ֽ�ɫ�б�(vector<��½��ɫ��Ϣ_>& vsk)
{
	//MyTrace(L"vsk.size %d,  ȫ_��ɫ�б�.size  %d,  ֱ��״̬  %d ", vsk.size(), ȫ_��ɫ�б�.size());
	if (vsk.size() != ȫ_��ɫ�б�.size())
	{
		if (ȫ_��ɫ�б�.size() == 0)
		{
			ȫ_��ɫ�б�.assign(vsk.begin(), vsk.end());
		}
		else if (vsk.size() > ȫ_��ɫ�б�.size())
		{
			for (size_t i = 0; i < vsk.size(); i++)
			{
				//MyTrace(L"������ɫ  %s  ,dIndex %d,  SrvId  %d,  dJob  %d,  ֱ��״̬  %d ",vsk[i].����, vsk[i].dIndex, vsk[i].SrvId, vsk[i].dJob, vsk[i].ֱ��״̬);
				if (�Ƿ���ڴ˽�ɫ(vsk[i]) == false)
				{
					ȫ_��ɫ�б�.push_back(vsk[i]);

				}
			}
		}
	}
}
int ��½::ȡ��������ɽ�ɫ����()
{
	int i = 0;
	for (size_t i = 0; i < ȫ_��ɫ�б�.size(); i++)
	{
		if (ȫ_��ɫ�б�[i].�����Ƿ���� == true)
		{
			i++;
		}
	}
	/*��½��ɫ��Ϣ_ temp;
	vector<��½��ɫ��Ϣ_>vsk;
	��½::get_CharacterList(vsk);
	for (size_t i = 0; i < vsk.size(); i++)
	{
		if (vsk[i].dIndex == ���)
		{
			return vsk[i];
		}
	}*/
	return i;
}
void ��½::�������������(CString ����)
{



	for (size_t i = 0; i < ȫ_��ɫ�б�.size(); i++)
	{
		//MyTrace(L"������ɫ2  %s  ,dIndex %d,  SrvId  %d,  dJob  %d,  ֱ��״̬  %d ",ȫ_��ɫ�б�[i].����, ȫ_��ɫ�б�[i].dIndex, ȫ_��ɫ�б�[i].SrvId, ȫ_��ɫ�б�[i].dJob, ȫ_��ɫ�б�[i].ֱ��״̬);
		if (���� == ȫ_��ɫ�б�[i].����)
		{
			//MyTrace(L"���ý�ɫ���1-50����");
			ȫ_��ɫ�б�[i].�����Ƿ���� = true;

			//break;
		}
	}
}
��½��ɫ��Ϣ_ ��½::ȡδ�������Ľ�ɫ()
{
	��½��ɫ��Ϣ_ temp;
	for (size_t i = 0; i < ȫ_��ɫ�б�.size(); i++)
	{
		if (ȫ_��ɫ�б�[i].�����Ƿ���� == false)
		{
			return ȫ_��ɫ�б�[i];
		}
	}

	return temp;
}