#include "�ڴ�_UI���.h"
UIinfo_ getUiObjInfo(INT64 dObjAddr, DWORD dIndex, DWORD dId)
{
	UIinfo_ temp;
	DWORD dShow = R_DW(dObjAddr + 0x27C);//����-0218
	INT64 addr_1 = R_QW(dObjAddr + 0X18);
	INT64 addr_2 = R_QW(addr_1 + 0x50 + 0X20);//����-0218
	INT64 dNameAddr = R_QW(addr_2 + 0xF8);
	CString csName = L"��";
	if (dNameAddr)
	{
		csName = CString(R_String(R_QW(dNameAddr)));

	}
	temp.UIObj = dObjAddr;
	temp.CName = csName;
	temp.bShow = dShow;
	temp.dIndex = dIndex;
	temp.dId = dId;
	return temp;
	//if (/*csName.Find(L"quickSlotFrame") > 0*/ dShow)//��ȡ��ݼ�UI��ַ
	/*{
		MyTrace(L"����%X �����ַ0x%I64X ID %X �Ƿ���ʾ%d %s\r\n", dIndex, dObjAddr, dId, dShow, csName);
	}*/

}
void UI����::getUiList(vector<UIinfo_>& vsk)
{
	//UIinfo_ temp;
	INT64 addr_1 = R_QW(��Ϸģ�� + gb_UiList);
	INT64 addr_2 = R_QW(addr_1 + 0xA4);//����-0218
	long dtotal = R_DW(addr_2 + 0x21C);
	INT64 objStartAddr = R_QW(addr_2 + 0x1D8);//���������ַ
	INT64 indexStartAddr = R_QW(addr_2 + 0x214);//���������ַ
	//MyTrace(L"objStartAddr 0x%I64X indexStartAddr 0x%I64X dtotal %d", objStartAddr, indexStartAddr, dtotal);
	for (long i = 0; i < dtotal; i++)
	{
		long dIndex = R_DW(indexStartAddr + i * 4);
		if (dIndex != 0xFFFFFFFF)
		{
			long dOffest = dIndex * 5 * 4;
			INT64 dObjAddr = R_QW(objStartAddr + dOffest + 4);
			WORD bId = R_W(objStartAddr + dOffest);//��˫�ֽ�
			//MyTrace(L"dObjAddr 0x%I64X dIndex %D bId %d", dObjAddr, dIndex, bId);
			UIinfo_ temp = getUiObjInfo(dObjAddr, dIndex, bId);
			vsk.push_back(temp);
			DWORD dNextIndex = 0;
			while (1)
			{
				dNextIndex = R_DW(objStartAddr + dOffest + 0xC);
				if (dNextIndex == 0xFFFFFFFF)//Ϊ-1����ѭ��
				{
					break;
				}
				else
				{
					dOffest = dNextIndex * 5 * 4;
					dObjAddr = R_QW(objStartAddr + dOffest + 4);
					bId = R_BYTE(objStartAddr + dOffest);//���ֽ�
					UIinfo_ temp2 = getUiObjInfo(dObjAddr, dNextIndex, bId);
					vsk.push_back(temp2);
				}
			}
		}
	}
}
INT64 UI����::getUiObjById_Old(DWORD ID)
{
	INT64 ��_��ȡ��Ļ����call = ��Ϸģ�� + ��ַ_����_��ȡ��Ļ����call;
	INT64 ��_��ȡ��Ļ����rcx = R_QW(��Ϸģ�� + gb_UiList);
	INT64 reta;
	__try
	{
		__asm
		{
			sub rsp, 0x60
			mov rcx, ��_��ȡ��Ļ����rcx
			mov edx, ID
			mov r8, 1
			mov rdi, ��_��ȡ��Ļ����call
			call rdi
			add rsp, 0x60
			mov reta, rax
		}
	}
	__except (1)
	{
		DbgPrintf_Mine("getUiObjById error");
		return 0;
	}
	return reta;
}


bool UI����::Ѱ�Ҵ򿪴���(CString name, INT64& rcx)
{
	CString temp;
	INT64 aaa = R_QW(��Ϸģ�� + gb_UiList);
	temp.Format(L"aaa%I64X", aaa);
	//	DebugPrintf("%s\n", CStringA(temp));
	INT64 a = R_QW(aaa + 0xA4);//����-0218
	DWORD ���� = R_DW(a + 0x2D8);
	INT64 rdx = R_QW(a + 0x2F8);//���������ַ
	//INT64 indexStartAddr = R_QW(addr_2 + 0x214);//���������ַ
	for (size_t i = 0; i < ����; i++)
	{

		//INT64 rcx = 0;
		//const char* message = lua_tostring(L, -1);
		//UI����::Ѱ�Ҵ򿪴���(CStringW(message), rcx);

		//CString temp;
		//const char* message = lua_tostring(L, -1);
		////INT64 rcx = 0;
		////UI����::Ѱ�Ҵ򿪴���(CStringW(message),rcx);
		//INT64 addr=UI����::getUiObjByName(CStringW(message));

		DWORD rax = i + 1;
		INT64 ���� = rdx + rax * 5 * 4 + 4;

		INT64 addr_1 = R_QW(R_QW(����) + 0X18);
		INT64 addr_2 = R_QW(addr_1 + 0x50 + 0X20);//����-0218
		INT64 dNameAddr = R_QW(addr_2 + 0xF8);
		CString name1 = L"��";
		if (dNameAddr)
		{
			 name1 = CString(R_String(R_QW(dNameAddr)));
		//	MyTrace(L"%s", name1.GetString());

		}
	
		//CString name1 = getMsgBoxMiddleText2(R_QW(����));


		temp.Format(L"%I64X", ����);

		if (name1 == name)
		{
			rcx = R_QW(����);
			temp.Format(L"%I64X", ����);

			//MyTrace(name1);
			return 1;


		}
		//DWORD dIndex = R_DW(indexStartAddr + i * 4);


	}
	return 0;
}
INT64 UI����::getUiObjById(DWORD ID)
{
	INT64 addr_1 = R_QW(��Ϸģ�� + gb_UiList);
	INT64 addr_2 = R_QW(addr_1 + 0xA4);//����-0218
	long dtotal = R_DW(addr_2 + 0x21C);
	INT64 objStartAddr = R_QW(addr_2 + 0x1D8);//���������ַ
	INT64 indexStartAddr = R_QW(addr_2 + 0x214);//���������ַ
	//MyTrace(L"objStartAddr 0x%I64X indexStartAddr 0x%I64X dtotal %d", objStartAddr, indexStartAddr, dtotal);
	for (size_t i = 0; i < dtotal; i++)
	{
		/*if (i > 3000)
		{
			break;
		}*/
		DWORD dIndex = R_DW(indexStartAddr + i * 4);
		//if (dIndex != 0xFFFFFFFF)
		if (dIndex != -1)
		{
			long dOffest = dIndex * 5 * 4;
			INT64 dObjAddr = R_QW(objStartAddr + dOffest + 4);
			WORD bId = R_W(objStartAddr + dOffest);//��˫�ֽ�
			if (bId == ID)
			{
				return dObjAddr;
			}
			DWORD dNextIndex = 0;
			DWORD count = 0;
			while (1)
			{
				count = count + 1;
				/*if (count >= 10000)
				{
					return 0;
				}*/
				dNextIndex = R_DW(objStartAddr + dOffest + 0xC);
				if (dNextIndex == -1)//Ϊ-1����ѭ��
				{
					break;
				}
				else
				{
					dOffest = dNextIndex * 5 * 4;
					dObjAddr = R_QW(objStartAddr + dOffest + 4);
					bId = R_W(objStartAddr + dOffest);//���ֽ�
					if (bId == ID)
					{
						return dObjAddr;
					}
				}
			}
		}
	}
	return 0;
}
INT64 UI����::getUiObjByName(CString name)
{
	vector<UIinfo_>vsk;
	getUiList(vsk);
	for (size_t i = 0; i < vsk.size(); i++)
	{
		if (vsk[i].CName == name)
		{
			return vsk[i].UIObj;
		}
	}
	return 0;
}
DWORD UI����::getUiIdByName(CString name)
{
	vector<UIinfo_>vsk;
	getUiList(vsk);
	for (size_t i = 0; i < vsk.size(); i++)
	{
		if (vsk[i].CName == name)
		{
			return vsk[i].dId;
		}
	}
	return 0;
}
INT64 �ڴ�_UI_��ȡ��������()
{
	/*INT64��_����ͷ;
	long ��_��Ա��;
	long i;
	INT64��_Obj;
	INT64��_����ַ;*/
	//' ��ȡ��������;
	INT64 ��_v1 = R_QW(R_QW(��Ϸģ��_EFEngine + ��ַ_UI_��������) + ƫ��_UI_��������);
	if (��_v1 == 0) {
		return 0;
	}
	INT64 ��_����ͷ = R_QW(��_v1 + 112); // ' 0x70;
	DWORD ��_��Ա�� = R_DW(��_v1 + 112 + 8); // ' 0x78;
	for (size_t i = 0; i < ��_��Ա��; i++)
	{
		INT64 ��_Obj = R_QW(��_����ͷ + i * 8);
		INT64 ��_����ַ = R_QW(R_QW(��_Obj) + ƫ��_UI_�������);
		if (R_BYTE(��_����ַ + 174) == 116)
		{
			return ��_Obj;
		}
	}
	return 0;
}
DWORD  �ڴ�_UI_����ת��(DWORD  ��ת������)
{
	INT64 ��_rcx = 0;
	INT64 ��_v1 = R_QW(R_QW(��Ϸģ��_EFEngine + ��ַ_UI_��������) + ƫ��_UI_�������� - 24);
	INT64 ��_rdx = R_QW(��_v1 + 188);  //' 0xBC;
	INT64 ��_r8 = R_QW(��_v1 + 128); // ' 80;
	DWORD ��_eax = R_DW(��_rdx + ��ת������ * 4);
	if (��_eax == -1) {
		return 0;
	}
	do {
		��_rcx = ��_eax;
		��_rdx = ��_rcx + ��_rcx * 4;
		if (R_BYTE(��_r8 + ��_rdx * 4) == ��ת������) {
			return R_DW(��_r8 + ��_rdx * 4 + 4);
		}
		��_eax = R_DW(��_r8 + ��_rdx * 4 + 12);


	} while (��_eax != -1);
	return 0;
}

bool UI����::�ڴ水��(DWORD ���ܼ���, DWORD ����)
{
	INT64 �������� = �ڴ�_UI_��ȡ��������();
	if (�������� == 0 || ���ܼ��� == 0)
	{
		return false;
	}
	INT64 dCALL = R_QW(R_QW(��������) + ƫ��_UI_�������);
	if (dCALL)
	{
		DWORD ��_���� = ����;
		DWORD ת������� = �ڴ�_UI_����ת��(���ܼ���);
		if (��_���� == 0)
		{
			MainUniversalCALL4(��������, 0, ת�������, 0, dCALL);
		}
		if (��_���� == 1)
		{
			MainUniversalCALL4(��������, 0, ת�������, 1, dCALL);
		}
		if (��_���� == 2)
		{
			MainUniversalCALL4(��������, 0, ת�������, 0, dCALL);
			Sleep(100);
			MainUniversalCALL4(��������, 0, ת�������, 1, dCALL);
		}
		return true;
	}
	return false;

}
bool UI����::��ͼ�Ƿ��()
{
	INT64 ��_UI���� = UI����::getUiObjById(152);
	if (R_BYTE(��_UI���� + 184) == 1)
	{
		return true;
	}
	return false;
}

bool UI����::�����ɱ���Ľ����Ƿ��()
{
	INT64 ��_UI���� = UI����::getUiObjById(0x177);//ID 31 �Ƿ���ʾ0 topRightInfoNoticeFrame
	if (R_BYTE(��_UI���� + 0x27C) == 0)
	{
		return true;
	}
	return false;
}
bool UI����::�����������Ƿ���ʾ()
{
	INT64 ��_UI���� = UI����::getUiObjById(0x64);//ID 31 �Ƿ���ʾ0  root1.arkui.frameCanvas.experienceFrame
	if (R_BYTE(��_UI���� + 0x27C) == 1)
	{
		return true;
	}
	return false;
}
bool UI����::���������Ƿ���ʾ()
{
	INT64 ��_UI���� = UI����::getUiObjById(0x1A);//ID 31 �Ƿ���ʾ0  root1.arkui.windowCanvas.inventoryWnd
	if (R_BYTE(��_UI���� + 0x27C) == 1)
	{
		//MyTrace(L"������ʾ");
		return true;
	}
	return false;
}
bool UI����::���ͼ�Ƿ���ʾ()
{
	INT64 ��_UI���� = UI����::getUiObjById(0x23D);//ID 98 �Ƿ���ʾ0   root1.arkui.windowCanvas.worldMapWnd
	if (R_BYTE(��_UI���� + 0x27C) == 1)
	{
		return true;
	}
	return false;
}
bool UI����::����ְҵ�н����Ƿ���ʾ()
{
	INT64 ��_UI���� = UI����::getUiObjById(0x1DC);//I �Ƿ���ʾ0   root1.arkui.frameCanvas.sorceressSkinFrame
	if (��_UI���� == 0)
	{
		��_UI���� = UI����::getUiObjById(0xDC);
	}
	if (R_BYTE(��_UI���� + 0x27C) == 1)
	{
		return true;
	}
	return false;
}
bool UI����::���������Ƿ��()
{
	INT64 ��_UI���� = UI����::getUiObjById(168);
	INT64 ��_UI����2 = UI����::getUiObjById(198);
	INT64 ��_UI����3 = UI����::getUiObjById(0x99);

	if (��_UI����)
	{
		if (R_BYTE(��_UI���� + ƫ��_UI_��ʾ) == 1)
		{
			return true;
		}
	}
	if (��_UI����2)
	{
		if (R_BYTE(��_UI����2 + ƫ��_UI_��ʾ) == 1)
		{
			return true;
		}
	}
	if (��_UI����3)
	{
		if (R_BYTE(��_UI����3 + ƫ��_UI_��ʾ) == 1)
		{
			return true;
		}
	}

	return false;
}
bool UI����::��������()
{
	if (UI����::�Ƿ��ں���׼������() == false)
	{
		�ڴ水��('Z');
		return false;
	}
	INT64 dCALL = ��Ϸģ�� + ��ַ_UI_��������call;
	INT64 dRCX = R_QW(��Ϸģ�� + ��ַ_UI_��������rcx);
	if (dRCX != 0)
	{
		MainUniversalCALL2(dRCX, 0, dCALL);
		return true;
	}
	return false;
}
bool UI����::�������()
{
	if (UI����::�Ƿ��ں���׼������() == false)
	{
		�ڴ水��('Z');
		return false;
	}
	INT64 dCALL = ��Ϸģ�� + ��ַ_UI_�������call;
	INT64 dRCX = R_QW(��Ϸģ�� + ��ַ_UI_��������rcx);
	if (dRCX != 0)
	{
		MainUniversalCALL2(dRCX, 0, dCALL);
		return true;
	}
	return false;
}

bool UI����::���븱��()
{
	INT64 ��_UI���� = UI����::getUiObjById(168);

	if (��_UI����)
	{
		if (R_BYTE(��_UI���� + ƫ��_UI_��ʾ) == 1)
		{
			INT64 ��_rcx = ��_UI���� + ƫ��_UI_���븱����ť;
			INT64 dCALL = ��Ϸģ�� + ��ַ_����_������������call;
			MainUniversalCALL2(��_rcx, 0, dCALL);
			return true;
		}
	}
	INT64 ��_UI����2 = UI����::getUiObjById(198);
	if (��_UI����2)
	{
		if (R_BYTE(��_UI����2 + ƫ��_UI_��ʾ) == 1)
		{
			INT64 ��_rcx = ��_UI����2;
			INT64 dCALL = ��Ϸģ�� + ��ַ_����_�볡CALL;
			MainUniversalCALL2(��_rcx, 0, dCALL);
			return true;
		}
	}
	INT64 ��_UI����3 = UI����::getUiObjById(0x99);
	if (��_UI����3)
	{
		if (R_BYTE(��_UI����3 + ƫ��_UI_��ʾ) == 1)
		{
			INT64 ��_rcx = ��_UI����3 + ƫ��_UI_���븱����ť;
			INT64 dCALL = ��Ϸģ�� + ��ַ_����_������������call;
			MainUniversalCALL2(��_rcx, 0, dCALL);
			return true;
		}
	}


	return false;
}
INT64 �ڴ�_UI_ȡ�ɼ���ʶ����()
{
	string ��_�ı���ʶ;
	CString WName;
	INT64 ��_rcx = R_QW(R_QW(��Ϸģ�� + ��ַ_����_����) + 164);
	INT64 ��_����ͷ = R_QW(��_rcx + 760);
	int ��_��Ա�� = R_DW(��_rcx + 800);
	for (size_t i = 0; i < ��_��Ա��; i++)
	{
		INT64 ��_���� = R_QW(��_����ͷ + (i - 1) * 5 * 4 + 4);
		if (��_���� != 0) {

			��_�ı���ʶ = UnicodeToAnsi(R_CString(R_QW(R_QW(��_���� + 188))));
			WName = CString(��_�ı���ʶ.c_str());
		}
		if (WName.Find(L"DataArray") != -1)
		{
			return ��_����;
		}
	}
	return 0;
}


bool UI����::�Ƿ����G()
{
	INT64 ��_UI���� = �ڴ�_UI_ȡ�ɼ���ʶ����();
	if (��_UI���� == 0)
	{
		return false;
	}
	if (R_DW(��_UI���� + ƫ��_����_�ɼ���ʶ) == 0)
	{
		return false;
	}
	return true;
}
bool UI����::�Ƿ����()
{
	INT64 ��_������ʵ���� = ����::ȡ��ʵ����();
	if (��_������ʵ���� == 0)
	{
		return false;
	}
	INT64 ��_V1 = R_QW(��_������ʵ���� + ƫ��_UI_����1);
	if (��_V1 == 0)
	{
		return false;
	}
	INT64 ��_V2 = ��_V1 + ƫ��_UI_����2;
	for (size_t i = 0; i < 9; i++)
	{
		if (R_DW(��_V2 + i * 4) == 1)
		{
			return true;
		}
	}

	return false;
}
bool UI����::�Ƿ��ں���׼������()
{
	INT64 ��_UI���� = UI����::getUiObjById(178);
	if (��_UI���� == 0)
	{
		return false;
	}
	if (R_DW(��_UI���� + ƫ��_UI_��������) == 1)
	{
		return true;
	}
	return false;
}

bool UI����::�Ƿ��ڽ����������()
{
	INT64 ��_UI���� = UI����::getUiObjById(50);
	if (��_UI���� == 0)
	{
		return false;
	}
	if (R_DW(��_UI���� + ƫ��_UI_��ʾ) == 1)
	{
		return true;
	}
	return false;
}
bool UI����::׼������()
{
	if (!UI����::���ͼ�Ƿ���ʾ())
	{
		UI����::�ڴ水��('M');
		Sleep(2000);
		return false;
	}
	//INT64 ��_UI���� = UI����::getUiObjById(152);
	INT64 ��_UI���� = UI����::getUiObjById(573);
	if (��_UI���� == 0)
	{
		return false;
	}
	if (R_DW(��_UI���� + ƫ��_UI_��ʾ) != 1)
	{
		return false;
	}
	MainUniversalCALL2(��_UI����, 0, ��Ϸģ�� + ��ַ_UI_׼������call);
	return true;
}

void getMiddle_textFieldAddr(INT64 dChildAddr, INT64& dRetAddr)
{
	if (dRetAddr) return;
	INT64 dstart = R_QW(dChildAddr + 0xE0);
	DWORD dtotal = R_DW(dChildAddr + 0xE8);
	if (dtotal < 5 && dstart)//��ֹ�������������ַ�����ѭ��
	{
		for (DWORD j = 0; j < dtotal; j++)
		{
			INT64 dTempAddr = R_QW(dstart + j * 0x10);
			INT64 dStrAddr = R_QW(dTempAddr + 0x70);
			if (dStrAddr)
			{
				dStrAddr = R_QW(dStrAddr + 0x10);
				dStrAddr = R_QW(dStrAddr);
				CString cName = CString(R_String(dStrAddr));
				if (_tcscmp(cName, L"textField") == 0)
				{
					dRetAddr = dTempAddr;
				//	MyTrace(L"�ı���ַ%I64X", dTempAddr);
				}
			}
			getMiddle_textFieldAddr(dTempAddr, dRetAddr);
		}
	}
}
void getMsgBoxMiddleText(INT64 dUIObj)
{
	INT64 addr_1 = R_QW(dUIObj + 0x18);
	INT64 addr_2 = R_QW(addr_1 + 0x70);
	INT64 addr_3 = R_QW(addr_2 + 0x60);
	INT64 dstart = R_QW(addr_3 + 0xE0);
	long dtotal = R_DW(addr_3 + 0xE8);
	for (DWORD i = 0; i < dtotal; i++)
	{
		INT64 dChildAddr = R_QW(dstart + i * 0x10);
		INT64 dStrAddr = R_QW(dChildAddr + 0x70);
		if (dStrAddr)
		{
			dStrAddr = R_QW(dStrAddr + 0x10);
			dStrAddr = R_QW(dStrAddr);
			CString cName = CString(R_String(dStrAddr));
			if (_tcscmp(cName, L"middleComponent") == 0 || _tcscmp(cName, L"titleBtn") == 0)
			{

				INT64 dTextAddr = 0;
				getMiddle_textFieldAddr(dChildAddr, dTextAddr);
				if (dTextAddr)
				{
					dStrAddr = R_QW(dTextAddr + 0x108);
					CString cTxt = UTF82WCS(R_String(dStrAddr + 0xB));//��Į����UTF8��ʽ
					//MyTrace(L"��ַ%I64X %s", dTextAddr, cTxt);
					//if (cTxt.Find(L"����") != -1 || cTxt.Find(L"Enter") != -1)
					//{
					//	Fun_MsgBoxConfirm(dUIObj);
					//	return;
					//}*/
					////return cTxt;

				}

			}

		}
	}
}
void Fun_MsgBoxConfirm(INT64 dUIObj)
{
	if (dUIObj)
	{
		INT64  dCall = ��Ϸģ�� + gc_MsgBoxConfirm;
		MainUniversalCALL2(dUIObj, 0, dCall);
	}

}
bool  UI����::getMsgBoxTextList()
{
	INT64 addr_1 = R_QW(��Ϸģ�� + gb_UiList);
	DWORD dtotal = R_DW(addr_1 + 0x144);
	INT64 dstart = R_QW(addr_1 + 0x13C);//���������ַ
	for (long i = 0; i < dtotal; i++)
	{
		INT64 dUIObj = R_QW(dstart + i * 0xC);

		//DWORD dPraentId = R_DW(dUIObj + 0x12C);//������Ʒ���ֲ���ȫ�ֵ�������
		DWORD dPraentId = R_DW(dUIObj + 0x12C);//������Ʒ���ֲ���ȫ�ֵ�������
	//	MyTrace(L"dUIObj 0x%I64X 0x%I64X", dUIObj, dPraentId);
		CString �����ı� = getMsgBoxMiddleText2(dUIObj);
		MyTrace(L"�����ı� %s", �����ı�);
		if (�����ı�.Find(L"Enter the Chaos Dungeon") != -1 || �����ı�.Find(L"Do you want to go back to the character selection screen") != -1 || �����ı�.Find(L"Teleport") != -1 || �����ı�.Find(L"�ռ��ƶ�") != -1)
			//if (dPraentId == 1)
		{
			MyTrace(L"�����Ϸ��ȷ������");
			Fun_MsgBoxConfirm(dUIObj);
			return false;
		}
		if (�����ı�.Find(L"Enter the Chaos Dungeon") != -1 || �����ı�.Find(L"Do you want to go back to the character selection screen") != -1 || �����ı�.Find(L"Teleport") != -1 || �����ı�.Find(L"��Ϊ��ķ��ص���") != -1)
			//if (dPraentId == 1)
		{
			MyTrace(L"����󶨻سǳ���");
			Fun_MsgBoxConfirm(dUIObj);
			return false;
		}
		if (�����ı�.Find(L"Enter the Chaos Dungeon") != -1 || �����ı�.Find(L"Do you want to go back to the character selection screen") != -1 || �����ı�.Find(L"Teleport") != -1 || �����ı�.Find(L"��Ӷ��Ա") != -1)
			//if (dPraentId == 1)
		{
			MyTrace(L"��Ӷ��Ա");
			Fun_MsgBoxConfirm(dUIObj);
			return false;
		}
		if (�����ı�.Find(L"Enter the Chaos Dungeon") != -1 || �����ı�.Find(L"Do you want to go back to the character selection screen") != -1 || �����ı�.Find(L"Teleport") != -1 || �����ı�.Find(L"׼������") != -1)
			//if (dPraentId == 1)
		{
			MyTrace(L"׼������");
			Fun_MsgBoxConfirm(dUIObj);
			return false;
		}
		//getMsgBoxMiddleText(dUIObj);


	}
	return true;
}

CString UI����::getMsgBoxMiddleText2(INT64 dUIObj)
{
	INT64 addr_1 = R_QW(dUIObj + 0x18);
	INT64 addr_2 = R_QW(addr_1 + 0x70);
	INT64 addr_3 = R_QW(addr_2 + 0x60);
	INT64 dstart = R_QW(addr_3 + 0xE0);
	long dtotal = R_DW(addr_3 + 0xE8);
	CString �����ı� = L"";
	for (DWORD i = 0; i < dtotal; i++)
	{
		INT64 dChildAddr = R_QW(dstart + i * 0x10);
		INT64 dStrAddr = R_QW(dChildAddr + 0x70);
		if (dStrAddr)
		{
			dStrAddr = R_QW(dStrAddr + 0x10);
			dStrAddr = R_QW(dStrAddr);
			CString cName = CString(R_String(dStrAddr));
			if (_tcscmp(cName, L"middleComponent") == 0 || _tcscmp(cName, L"titleBtn") == 0)
			{

				INT64 dTextAddr = 0;
				getMiddle_textFieldAddr(dChildAddr, dTextAddr);
				if (dTextAddr)
				{
					dStrAddr = R_QW(dTextAddr + 0x108);
					CString cTxt = UTF82WCS(R_String(dStrAddr + 0xB));//��Į����UTF8��ʽ
					�����ı� = �����ı� + cTxt;
					/*MyTrace(L"��ַ%I64X %s", dTextAddr, cTxt);
					if (cTxt.Find(L"����") != -1 || cTxt.Find(L"Enter") != -1)
					{
						Fun_MsgBoxConfirm(dUIObj);
						return;
					}*/
					//return cTxt;

				}

			}

		}
	}
	return �����ı�;
}
CString  UI����::getMsgBoxText()
{
	INT64 addr_1 = R_QW(��Ϸģ�� + gb_UiList);
	DWORD dtotal = R_DW(addr_1 + 0x144);
	INT64 dstart = R_QW(addr_1 + 0x13C);//���������ַ
	for (long i = 0; i < dtotal; i++)
	{
		if (i >= 500)
		{
			return L"";
		}
		INT64 dUIObj = R_QW(dstart + i * 0xC);
		DWORD dPraentId = R_DW(dUIObj + 0x12C);//������Ʒ���ֲ���ȫ�ֵ�������
		return getMsgBoxMiddleText2(dUIObj);


	}
	return L"";
}
CString  UI����::getMsgBoxText_ȫ()
{
	INT64 addr_1 = R_QW(��Ϸģ�� + gb_UiList);
	DWORD dtotal = R_DW(addr_1 + 0x144);
	INT64 dstart = R_QW(addr_1 + 0x13C);//���������ַ
	CString �����ı� = L"";
	for (long i = 0; i < dtotal; i++)
	{
		if (i >= 500)
		{
			return L"";
		}
		INT64 dUIObj = R_QW(dstart + i * 0xC);
		DWORD dPraentId = R_DW(dUIObj + 0x12C);//������Ʒ���ֲ���ȫ�ֵ�������
		CString ���� = getMsgBoxMiddleText2(dUIObj);
		�����ı� = �����ı� + ���� + "|";

	}
	return �����ı�;
}

INT64 getChildUiAddrByStr(INT64 dParentAddr, CString cChildName)
{
	INT64 dstart = R_QW(dParentAddr + 0xE0);
	long dtotal = R_DW(dParentAddr + 0xE8);
	for (DWORD i = 0; i < dtotal; i++)
	{
		INT64 dChildAddr = R_QW(dstart + i * 0x10);
		INT64 dStrAddr = R_QW(dChildAddr + 0x70);
		if (dStrAddr)
		{
			dStrAddr = R_QW(dStrAddr + 0x10);
			dStrAddr = R_QW(dStrAddr);
			CString cName = CString(R_String(dStrAddr));
			//MyTrace(L"0x%I64X %s", dStrAddr, cName);
			if (_tcscmp(cName, cChildName) == 0)
			{
				return dChildAddr;
			}
		}
	}
	return 0;
}

INT64 getUiFirstAddr(INT64 dUiObj)
{
	//INT64 addr_1 = R_QW(dUiObj + 0x18);
	//INT64 addr_2 =R_QW(addr_1 + 0x70);
	INT64 addr_3 = R_QW(R_QW(R_QW(dUiObj + 0x18) + 0x70) + 0x60);
	return addr_3;
}

void UI����::getNpcTalkSelectList(vector<CString>& �Ի���)
{
	�Ի���.clear();
	INT64 dUiObj = UI����::getUiObjById(0x1B);;//interactionMainFrame 
	INT64 addr_first = getUiFirstAddr(dUiObj);
	INT64 addr_1 = getChildUiAddrByStr(addr_first, L"talkSelectButtonGroup");
	DWORD dShow = R_W(addr_1 + 0x6A);
	//MyTrace(L"0x%I64x / 0x%I64x / 0x%I64x %d", dUiObj, addr_first,addr_1,dShow >> 0xe);
	if (dShow >> 0xe == 1)//�ж���ʾ
	{

		INT64 dstart = R_QW(addr_1 + 0xE0);
		long dTotal = R_DW(addr_1 + 0xE8);
		for (int i = 0; i < dTotal; i++)
		{
			INT64 addr_2 = R_QW(dstart + i * 0x10);
			dShow = R_W(addr_2 + 0x6A);
			//MyTrace(L"addr_2 0x%I64x /  %d", addr_2, dShow >> 0xe);
			if (dShow >> 0xe == 1)//�ж���ʾ
			{
				INT64 dStrAddr = R_QW(addr_2 + 0x70);
				if (dStrAddr)
				{
					dStrAddr = R_QW(dStrAddr + 0x10);
					dStrAddr = R_QW(dStrAddr);
					CString cName = CString(R_String(dStrAddr));
					//MyTrace(L"cName %s",cName);
					if (_tcsstr(cName, L"talkButtonGroup_"))//�ж��Ƿ�����ַ���talkButton_
					{
						INT64 dstart2 = R_QW(addr_2 + 0xE0);
						long dTotal2 = R_DW(addr_2 + 0xE8);
						for (int j = 0; j < dTotal2; j++)
						{
							INT64 addr_4 = R_QW(dstart2 + j * 0x10);
							DWORD dShow4 = R_W(addr_4 + 0x6A);
							DWORD straddr = R_QW(addr_4 + 0x70);
							straddr = R_QW(straddr + 0x10);
							straddr = R_QW(straddr);
							CString cstrName = CString(R_String(straddr));
							//MyTrace(L"%s addr_4 0x%I64x /  %d", cstrName, addr_4, dShow4 >> 0xe);
							if (dShow4 >> 0xe == 1)//�ж���ʾ
							{
								INT64 addr_3 = getChildUiAddrByStr(addr_4, L"tf");
								if (addr_3)
								{
									dShow = R_W(addr_3 + 0x6A);
									//MyTrace(L"addr_3 0x%I64x /  %d", addr_2, dShow >> 0xe);
									if (dShow >> 0xe == 1)//�ж���ʾ
									{
										INT64 dTextAddr = R_QW(addr_3 + 0x108);
										//MyTrace(L"dTextAddr 0x%I64X", dTextAddr);
										//string sText = R_CString(dTextAddr+0xB);
										CString cText = UTF82WCS(R_String(dTextAddr + 0xB));
										�Ի���.push_back(cText);
										//MyTrace(L"�Ի�: %s", cText);
										//wchar_t buf[MAX_PATH];
										/*swprintf(buf, L"��ַ0x%I64X %s 0x%I64X %s\r\n", addr_2, cName, dTextAddr,cText);
										MyTrace(L"�Ի�: %s", buf);*/
									}
								}
							}
						}
					}
				}
			}
		}
	}
}

bool UI����::ָ��UI�Ƿ���ʾ(CString UIName)
{
	INT64 ��_UI���� = UI����::getUiObjByName(UIName);
	if (R_BYTE(��_UI���� + 0x27C) == 1)
	{
		return true;
	}
	return false;
}
bool UI����::�̵��Ƿ��()
{
	INT64 ��_UI���� = UI����::getUiObjById(0x1F);//arkui.windowCanvas.marketWnd
	if (R_BYTE(��_UI���� + 0x27C) == 1)
	{
		return true;
	}
	return false;
}
bool UI����::�˳��˵��Ƿ��()
{
	INT64 ��_UI���� = UI����::getUiObjById(0x29);//root1.arkui.windowCanvas.exitMenuWindow
	if (R_BYTE(��_UI���� + 0x27C) == 1)
	{
		return true;
	}
	return false;
}


bool UI����::��������Ƿ���ʾ()
{
	INT64 ��_UI���� = UI����::getUiObjById(0x3A);//ID 31 �Ƿ���ʾ0  root1.arkui.windowCanvas.inventoryWnd
	if (R_BYTE(��_UI���� + 0x27C) == 1)
	{
		MyTrace(L"���������ʾ");
		return true;
	}
	return false;
}

bool UI����::����(CString ���ʽ)
{
	if (UI����::get_DeadSceneListBtnState())
	{
		int ����type = UI����::get_DeadSceneList(���ʽ);
		if (����type != -1)
		{
			INT64 dCALL = ��Ϸģ�� + gc_deadSceneWndBtn;
			INT64 dRCX = UI����::getUiObjById(0x3A);
			if (dRCX != 0)
			{
				MainUniversalCALL2(dRCX, ����type, dCALL);
				return true;
			}
		}
		else
		{
			MyTrace(L"����type����");
			return false;
		}
	}
	return false;
}

int UI����::get_DeadSceneList(CString ���ʽ)
{
	INT64 dUiObj = UI����::getUiObjById(0x3A);
	if (dUiObj)
	{
		DWORD dShow = R_DW(dUiObj + 0x27C);
		if (dShow)
		{
			INT64 dtotal = R_QW(dUiObj + go_deadSceneTotal);
			INT64 dstart = dUiObj + go_deadSceneStart;
			for (DWORD i = 0; i < dtotal; i++)
			{
				DWORD dType = R_DW(dstart + i * 0x28);
				INT64 dTexAddr = R_QW(dstart + i * 0x28 + 0x4);
				CString cName = L"��";
				cName = R_CString(dTexAddr);
				if (cName == ���ʽ)
				{
					return dType;
				}
			//	MyTrace(L"UI��ַ0x%I64X ����%d ����%d %s\r\n", dUiObj, i, dType, cName);
			}

		}
	}
	return -1;
}

CString UI����::getUiName(INT64 dObjAddr)
{
	INT64 addr_1 = R_QW(dObjAddr + 0X18);
	INT64 addr_2 = R_QW(addr_1 + 0x70);
	INT64 dNameAddr = R_QW(addr_2 + 0xF8);
	CString csName = L"��";
	if (dNameAddr)
	{
		//MyTrace(L"csName ���� %d  ���� %s", sizeof(R_String(R_QW(dNameAddr))), UTF82WCS(R_String(R_QW(dNameAddr))));
		csName = UTF82WCS((R_String(R_QW(dNameAddr))));
	}
	return csName;
}

bool UI����::get_DeadSceneListBtnState()//��ȡ���ť״̬
{

	INT64 dUiObj = UI����::getUiObjById(0x3A);
	if (dUiObj)
	{
		DWORD dShow = R_DW(dUiObj + 0x27C);
		if (dShow)
		{
			long dtotal = R_DW(dUiObj + go_DeadSceneChildList + 0x10 + 0x18);//__int64 go_DeadSceneChildList = 0x17C;
			INT64 dKeyAddr = R_QW(dUiObj + go_DeadSceneChildList + +0x20);//���������ַ
			if (!dKeyAddr)
			{
				dKeyAddr = dUiObj + go_DeadSceneChildList + 0x10;
			}
			long dKeyValue = R_DW(dKeyAddr);
			INT64 objStartAddr = R_QW(dUiObj + go_DeadSceneChildList);
			for (DWORD i = 0; i < dtotal; i++)
			{
				long dKeyValue = R_DW(dKeyAddr + (i / 0x20) * 4);
				DWORD dNum = i % 0x20;
				DWORD dCheck = (dKeyValue >> dNum) & 1;
				if (dCheck)
				{
					INT64 dObj = R_QW(objStartAddr + i * 0x18 + 0x8);
					if (dObj)
					{
						if (R_QW(dObj + 8) == 0) continue;
						CString cWidgetName = getUiName(dObj);
						INT64 addr_3 = getUiFirstAddr(dObj);
						INT64 dataAddr = R_QW(addr_3 + 0x150);
						dataAddr = R_QW(dataAddr + 0x368);
						INT64 dStateStrAddr = R_QW(dataAddr);
						CString stateName = UTF82WCS(R_String(dStateStrAddr));
						WORD dValue = R_W(addr_3 + 0x6A);
						BOOL bView = 0;
						if (dValue >> 0xe == 1 && stateName == L"up")
						{
							bView = 1;//��ʾ��
						//	MyTrace(L"0%I64X %s �Ƿ���ʾ%d ״̬%s\r\n", addr_3, cWidgetName, bView, stateName);
							return true;
						}
					//	MyTrace(L"0%I64X %s �Ƿ���ʾ%d ״̬%s\r\n", addr_3, cWidgetName, bView, stateName);
					}
				}
			}
		}
	}
	return false;
}

int UI����::getGameCurStageValue()
{
	DWORD dValue = 0;
	INT64 addr_1 = R_QW(��Ϸģ�� + gb_PacketInfo);
	INT64 dObj = R_QW(addr_1 + go_PacketSocketObj);//��Ϊ0 ��ʾ����
	if (dObj)
	{
		INT64 addr_2 = R_QW(addr_1 + go_GameStageValue);
		dValue = R_DW(addr_2);
		if (dValue == 3)//ѡ������
		{
		}
		else if (dValue == 5)//ѡ��ɫ
		{
		}
		else if (dValue == 7)//ѡ��ɫ����Ϸ
		{
		}
		else if (dValue == 9)//��Ϸ��
		{
		}
		else if (dValue == 10)//��Ϸ����ѡ��ɫ
		{
		}
		else if (dValue == 13)//��Ϸ����ѡ��ɫ
		{
		}
		else if (dValue == 11)//ѡ��ɫ����ѡ������
		{
		}
		else if (dValue == 2)//���������������
		{
		}
		if (dValue == 0)//����
		{
		}
	}
	return dValue;
}

bool UI����::bCheckItemDisassemleWnd()
{
	INT64 ��_UI���� = UI����::getUiObjByName(L"root1.arkui.windowCanvas.itemDisassembleWnd");//root1.arkui.windowCanvas.itemDisassembleWnd
	if (R_BYTE(��_UI���� + 0x27C) == 1)
	{
		return true;
	}
	return false;
}

void UI����::Fun_UiShowCtrl(int dUiId)
{
	INT64 addr_1 = R_QW(��Ϸģ�� + gb_UiList);
	MainUniversalCALL2(addr_1, dUiId, ��Ϸģ�� + gc_UIShowCtrl);

}
void UI����::�ؼ����call(INT64 ����)
{
	UCHAR ��_rdx0[0x100] = { 0 };
	W_DW((ULONG64)&��_rdx0[0], 0x100000C);
	INT64 call��ַ = R_QW(����);
	call��ַ = R_QW(call��ַ + 0x338);

	INT64 rdx = (INT64)&��_rdx0;
	INT64 rcx = ����;

	MainUniversalCALL6(rcx, rdx, 0, 0, 0, 0x100000C, call��ַ);
	//W_Float((ULONG64)&��_rdx0[0], px);


}

CString UI����::UI����1(INT64 ����)
{
	INT64 addr_1 = R_QW(���� + 0x70);
	INT64 addr_2 = R_QW(addr_1 + 0x10);
	INT64 addr_3 = R_QW(addr_2);
	string ·������ = R_String(addr_3);



	return CStringW(·������.c_str());
}




CString UI����::UI����(INT64 ����)
{
	INT64 addr_1 = R_QW(���� + 0x70);
	INT64 addr_2 = R_QW(addr_1 + 0x10);
	INT64 addr_3 = R_QW(addr_2);
	string ·������ = R_String(addr_3);

	if (·������ == "")
	{
		addr_1 = R_QW(���� + 0x618);
		addr_2 = R_QW(addr_1 + 0xF8);
		addr_3 = R_QW(addr_2);
		·������ = R_String(addr_3);
		if (·������ == "")
		{
			addr_1 = R_QW(���� + 0x630);
			addr_2 = R_QW(addr_1);
			·������ = R_String(addr_2);


		}


	}


	return CStringW(·������.c_str());
}
DWORD UI����::��������()
{
	INT64 addr_1 = R_QW(��Ϸģ�� + gb_UiList);
	DWORD dtotal = R_DW(addr_1 + 0x144);
	return dtotal;

}
CString  UI����::���ڷ����ı�()
{
	INT64 addr_1 = R_QW(��Ϸģ�� + gb_UiList);
	DWORD dtotal = R_DW(addr_1 + 0x144);
	INT64 dstart = R_QW(addr_1 + 0x144 - 8);//���������ַ
	CString �����ı� = L"";
	for (long i = 0; i < dtotal; i++)
	{
		if (i >= 500)
		{
			return L"";
		}



		INT64 dUIObj = R_QW(dstart + i * 0xC);

		//DWORD dPraentId = R_DW(dUIObj + 0x12C);//������Ʒ���ֲ���ȫ�ֵ�������
		DWORD dPraentId = R_DW(dUIObj + 0x12C);//������Ʒ���ֲ���ȫ�ֵ�������
		//MyTrace(L"dUIObj 0x%I64X 0x%I64X", dUIObj, dPraentId);
		CString ���� = getMsgBoxMiddleText2(dUIObj);


		�����ı� = �����ı� + ���� + "|";

	}
	return �����ı�;
}

//void UI����::Fun_NarrationAssistance_OnOff(int kaiguan)
//{
//	INT64 UIAddr = UI����::getUiObjByName(L"root1.arkui.frameCanvas.narrationAssistanceFrame");
//	if (UIAddr)
//	{
//		MainUniversalCALL2(UIAddr, kaiguan, ��Ϸģ�� + gc_narrationAssistanceOnOff);
//	}
//}
//
//void UI����::Fun_NarrationAssistance_Continue()
//{
//	INT64 UIAddr = UI����::getUiObjByName(L"root1.arkui.frameCanvas.narrationAssistanceFrame");
//	if (UIAddr)
//	{
//		MainUniversalCALL2(UIAddr, 0, ��Ϸģ�� + gc_NarrationAssistanceContinue);
//	}
//
//}