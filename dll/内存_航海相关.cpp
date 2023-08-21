#include "�ڴ�_�������.h"


DWORD ����::getRoleCrewList(vector<CrewInfo_>& vsk)//��ӵ�д�Ա�б�
{
	INT64 addr_1 = R_QW(��Ϸģ�� + gb_AttrList);
	INT64 addr_2 = R_QW(addr_1 + go_AttrList_off1);
	INT64 dstart = R_QW(addr_2 + go_VoyageCrewTotal - 0x8);
	INT64 dtotal = R_DW(addr_2 + go_VoyageCrewTotal);
	for (size_t i = 0; i < dtotal; i++)
	{
		DWORD dResId = R_DW(dstart + i * 4);
		INT64 dResAddr = getCrewResAddrById(dResId);
		INT64 dNameAddr = R_QW(dResAddr + 0x38);
		CString csName = L"";

		if (dNameAddr)
		{
			csName = R_CString(dNameAddr);
		}
		CrewInfo_ temp;
		temp.dResAddr = dResAddr;
		temp.dResId = dResId;
		temp.wName = csName;
		vsk.push_back(temp);
		//VoyageShipAddCrew( dResId);
		//MyTrace(L"��ǰ��ӵ�� ��ԱID %X 0x%I64X %s \r\n", dResId, dResAddr, csName);
	}
	return 0;
}

void ����::VoyageShipAddCrew(int dResId)//��Ӵ�Ա
{
	INT64 dInfo = R_QW(��Ϸģ�� + gb_VoyageData);
	MainUniversalCALL4(dInfo, dResId, 0xFFFFFFFF, 0, ��Ϸģ�� + gc_VoyageShipAddCrew);
	//wchar_t buf[100];
	//dm.AsmClear();
	//dm.AsmAdd(L"sub rsp,40");
	//wsprintf(buf, L"mov r8d, 0%X", 0xFFFFFFFF);
	//dm.AsmAdd(buf);
	//wsprintf(buf, L"mov edx, 0%X", dResId);
	//dm.AsmAdd(buf);
	//wsprintf(buf, L"mov rcx, 0%I64X", dInfo);
	//dm.AsmAdd(buf);
	//wsprintf(buf, L"mov rdi, 0%I64X", gc_VoyageShipAddCrew);
	//dm.AsmAdd(buf);
	//dm.AsmAdd(L"call rdi");
	//dm.AsmAdd(L"add rsp,040");
	//dm.AsmCall( 3);
}

void ����::VoyageShipDelCrew(int dIndex)//ɾ����Ա ���������� ���Ǵ�Ա��ԴID
{
	INT64 dInfo = R_QW(��Ϸģ�� + gb_VoyageData);
	MainUniversalCALL2(dInfo, dIndex, ��Ϸģ�� + gc_VoyageShipDelCrew);
	/*wchar_t buf[100];
	dm.AsmClear();
	dm.AsmAdd(L"sub rsp,40");
	wsprintf(buf, L"mov edx, 0%X", dIndex);
	dm.AsmAdd(buf);
	wsprintf(buf, L"mov rcx, 0%I64X", dInfo);
	dm.AsmAdd(buf);
	wsprintf(buf, L"mov rdi, 0%I64X", gc_VoyageShipDelCrew);
	dm.AsmAdd(buf);
	dm.AsmAdd(L"call rdi");
	dm.AsmAdd(L"add rsp,040");
	dm.AsmCall( 3);*/
}


int getVoyageShipTotal()//����ѽ�����ֻ����
{
	INT64 addr_1 = R_QW(��Ϸģ�� + gb_AttrList);
	INT64 addr_2 = R_QW(addr_1 + go_AttrList_off1);
	return R_DW(addr_2 + go_VoyageCrewTotal - 0x10);
}

DWORD ����::getCurVoyageShipResId()
{
	INT64 addr_1 = R_QW(��Ϸģ�� + gb_VoyageData);
	int dCurShipResId = R_DW(addr_1 + go_VoyageCurShipId);//��ǰѡ�д�ID
	int dCurShipLev = R_DW(addr_1 + go_VoyageCurShipId - 4);//��ǰѡ�д��ȼ�
	return dCurShipResId;
}
void getVoyageShipList(vector<ShipInfo_>& ShipGroup, vector<CrewInfo_>& CrewGroup)//������ �������ô�Ա����
{
	INT64 addr_1 = R_QW(��Ϸģ�� + gb_VoyageData);
	int dCurShipResId = R_DW(addr_1 + go_VoyageCurShipId);//��ǰѡ�д�ID
	int dCurShipLev = R_DW(addr_1 + go_VoyageCurShipId - 4);//��ǰѡ�д��ȼ�
	INT64 dstart = R_QW(addr_1 + go_VoyageCurShipId - 0x48);
	int dtotal = R_DW(addr_1 + go_VoyageCurShipId - 0x48 + 8);
	for (size_t i = 0; i < dtotal; i++)
	{
		INT64 dObj = dstart + i * 0x40 + 4;
		int dShipResId = R_DW(dObj);
		WORD dShipLev = R_W(dObj + 4);//˫�ֽ�
		INT64 dCrewStart = R_QW(dObj + 0x18);
		int dCrewTotal = R_DW(dObj + 0x18 + 8);
		for (size_t j = 0; j < dCrewTotal; j++)//JΪɾ����Աʱ��Ҫ�Ĳ���
		{

			int dCrewResId = R_DW(dCrewStart + j * 4);
			CrewInfo_ Crewtemp;
			Crewtemp.dIndex = j;
			Crewtemp.dShipId = dShipResId;
			Crewtemp.dResId = dCrewResId;
			CrewGroup.push_back(Crewtemp);

			////MyTrace(L"��ID %X ��ѡ��ԱID %X\r\n", dShipResId, dCrewResId);
		}
		INT64 dResAddr = getShipResAddrById(dShipResId);
		INT64 dNameAddr = R_QW(dResAddr + 0x10);
		CString csName = L"";
		if (dNameAddr)
		{
			csName = R_CString(dNameAddr);
		}
		ShipInfo_ tempShip;
		tempShip.dResId = dShipResId;
		tempShip.dObj = dObj;
		tempShip.dLev = dShipLev;
		tempShip.wName = csName;
		ShipGroup.push_back(tempShip);
		////MyTrace(L"��ID %X %s �ȼ�%d\r\n", dShipResId, csName, dShipLev);
	}

}

bool ����::Yesornonauticalpicture()
{
	INT64 dUiObj = UI����::getUiObjById(0xB2);//"root1.arkui.frameCanvas.anchorFrame"
	if (dUiObj)
	{

		DWORD dShow = R_DW(dUiObj + 0x27C);
		if (dShow)
		{
			return true;
		}
	}

	return false;
}


void VoyageShipSelectShip(int dIndex)//ѡ��ֻ
{
	INT64 dUiObj = UI����::getUiObjById(0xB2);//"root1.arkui.frameCanvas.anchorFrame"
	if (dUiObj)
	{

		DWORD dShow = R_DW(dUiObj + 0x27C);
		if (dShow)
		{
			MainUniversalCALL2(dUiObj, dIndex, ��Ϸģ�� + gc_VoyageShipSelectShip);
			/*	wchar_t buf[100];
				dm.AsmClear();
				dm.AsmAdd(L"sub rsp,40");
				wsprintf(buf, L"mov edx, 0%X", dIndex);
				dm.AsmAdd(buf);
				wsprintf(buf, L"mov rcx, 0%I64X", dUiObj);
				dm.AsmAdd(buf);
				wsprintf(buf, L"mov rdi, 0%I64X", gc_VoyageShipSelectShip);
				dm.AsmAdd(buf);
				dm.AsmAdd(L"call rdi");
				dm.AsmAdd(L"add rsp,040");
				dm.AsmCall( 6);*/
		}
	}
}

bool ����::ָ����Ա�Ƿ��ϴ�(DWORD dResId)
{
	vector<ShipInfo_> ShipGroup;
	vector<CrewInfo_> CrewGroup;
	getVoyageShipList(ShipGroup, CrewGroup);
	for (size_t i = 0; i < CrewGroup.size(); i++)
	{
		if (CrewGroup[i].dResId == dResId)
		{
			return true;
		}
	}
	return false;
}
bool ����::ָ����Ա�Ƿ�������װ���Ĵ�(DWORD dResId)
{
	DWORD dShipID = ����::getCurVoyageShipResId();
	vector<ShipInfo_> ShipGroup;
	vector<CrewInfo_> CrewGroup;
	getVoyageShipList(ShipGroup, CrewGroup);
	for (size_t i = 0; i < CrewGroup.size(); i++)
	{
		if (CrewGroup[i].dResId == dResId)
		{
			if (CrewGroup[i].dShipId == dShipID)
			{
				return true;
			}

		}
	}
	return false;
}
void ����::ɾ�����д�Ա()
{
	//MyTrace(L"ɾ�����д�Ա");
	vector<ShipInfo_> ShipGroup;
	vector<CrewInfo_> CrewGroup;
	getVoyageShipList(ShipGroup, CrewGroup);
	for (size_t i = 0; i < CrewGroup.size(); i++)
	{
		VoyageShipDelCrew(CrewGroup[i].dIndex);
		Sleep(100);
	}
}
void ����::�������д�Ա()
{
	//MyTrace(L"�������д�Ա");
	vector<CrewInfo_> CrewGroup;
	getRoleCrewList(CrewGroup);
	for (size_t i = 0; i < CrewGroup.size(); i++)
	{
		if (i >= 2)
		{
			return;
		}
		VoyageShipAddCrew(CrewGroup[i].dResId);
		Sleep(100);
	}
}
bool ����::�Զ�ѡ������ս��()
{
	//MyTrace(L"ѡ������ս��");
	DWORD �ѽ�����ֻ���� = getVoyageShipTotal();
	if (�ѽ�����ֻ���� == 1)
	{
		if (getCurVoyageShipResId() == 0x2008)
		{
			return true;
		}
		else
		{
			VoyageShipSelectShip(0);
			�������д�Ա();
		}
	}
	if (�ѽ�����ֻ���� == 2)
	{
		if (getCurVoyageShipResId() == 0x2009)
		{
			return true;
		}
		else
		{
			VoyageShipSelectShip(1);
			�������д�Ա();
		}
	}
	if (�ѽ�����ֻ���� == 3)
	{
		if (getCurVoyageShipResId() == 0x200B)
		{
			return true;
		}
		else
		{
			VoyageShipSelectShip(2);
			�������д�Ա();
		}
	}
	if (�ѽ�����ֻ���� == 4)
	{
		if (getCurVoyageShipResId() == 0x200F)
		{
			return true;
		}
		else
		{
			VoyageShipSelectShip(3);
			�������д�Ա();
		}
	}
	if (�ѽ�����ֻ���� == 5)
	{
		if (getCurVoyageShipResId() == 0x200D)
		{
			return true;
		}
		else
		{
			VoyageShipSelectShip(4);
			�������д�Ա();
		}
	}
	if (�ѽ�����ֻ���� == 6)
	{
		if (getCurVoyageShipResId() == 0x200E)
		{
			return true;
		}
		else
		{
			VoyageShipSelectShip(5);
			�������д�Ա();
		}
	}
	if (�ѽ�����ֻ���� == 7)
	{
		if (getCurVoyageShipResId() == 0x200A)
		{
			return true;
		}
		else
		{
			VoyageShipSelectShip(6);
			�������д�Ա();
		}
	}
	if (�ѽ�����ֻ���� == 8)
	{
		if (getCurVoyageShipResId() == 0x200A)
		{
			return true;
		}
		else
		{
			VoyageShipSelectShip(7);
			�������д�Ա();
		}
	}
	return false;
}

void ����::����call����(DWORD dResId)
{
	DWORD rdx = dResId;
	INT64 rcx =0;
	bool �Ƿ�� = UI����::Ѱ�Ҵ򿪴���("root1.arkui.windowCanvas.voyageLinerWnd", rcx);
	if (rcx >= 1)
	{
	//	INT64 rcx1=R_QW(rcx);
		W_DW(rcx+ g_ShipsetID, dResId);
		////MyTrace(L"ѡ������ս��0x%I64X " , rcx);
			MainUniversalCALL6(rcx, 0, 0, 1,0,2, ��Ϸģ�� + ��ַ_����call);

	}
}

void ����::luaVoyageShipSelectShip(int dIndex)//ѡ��ֻ
{

	VoyageShipSelectShip(dIndex);

}