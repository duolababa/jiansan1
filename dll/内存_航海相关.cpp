#include "内存_航海相关.h"


DWORD 航海::getRoleCrewList(vector<CrewInfo_>& vsk)//已拥有船员列表
{
	INT64 addr_1 = R_QW(游戏模块 + gb_AttrList);
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
		//MyTrace(L"当前已拥有 船员ID %X 0x%I64X %s \r\n", dResId, dResAddr, csName);
	}
	return 0;
}

void 航海::VoyageShipAddCrew(int dResId)//添加船员
{
	INT64 dInfo = R_QW(游戏模块 + gb_VoyageData);
	MainUniversalCALL4(dInfo, dResId, 0xFFFFFFFF, 0, 游戏模块 + gc_VoyageShipAddCrew);
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

void 航海::VoyageShipDelCrew(int dIndex)//删除船员 参数是索引 不是船员资源ID
{
	INT64 dInfo = R_QW(游戏模块 + gb_VoyageData);
	MainUniversalCALL2(dInfo, dIndex, 游戏模块 + gc_VoyageShipDelCrew);
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


int getVoyageShipTotal()//获得已解锁船只总数
{
	INT64 addr_1 = R_QW(游戏模块 + gb_AttrList);
	INT64 addr_2 = R_QW(addr_1 + go_AttrList_off1);
	return R_DW(addr_2 + go_VoyageCrewTotal - 0x10);
}

DWORD 航海::getCurVoyageShipResId()
{
	INT64 addr_1 = R_QW(游戏模块 + gb_VoyageData);
	int dCurShipResId = R_DW(addr_1 + go_VoyageCurShipId);//当前选中船ID
	int dCurShipLev = R_DW(addr_1 + go_VoyageCurShipId - 4);//当前选中船等级
	return dCurShipResId;
}
void getVoyageShipList(vector<ShipInfo_>& ShipGroup, vector<CrewInfo_>& CrewGroup)//船遍历 含已设置船员数组
{
	INT64 addr_1 = R_QW(游戏模块 + gb_VoyageData);
	int dCurShipResId = R_DW(addr_1 + go_VoyageCurShipId);//当前选中船ID
	int dCurShipLev = R_DW(addr_1 + go_VoyageCurShipId - 4);//当前选中船等级
	INT64 dstart = R_QW(addr_1 + go_VoyageCurShipId - 0x48);
	int dtotal = R_DW(addr_1 + go_VoyageCurShipId - 0x48 + 8);
	for (size_t i = 0; i < dtotal; i++)
	{
		INT64 dObj = dstart + i * 0x40 + 4;
		int dShipResId = R_DW(dObj);
		WORD dShipLev = R_W(dObj + 4);//双字节
		INT64 dCrewStart = R_QW(dObj + 0x18);
		int dCrewTotal = R_DW(dObj + 0x18 + 8);
		for (size_t j = 0; j < dCrewTotal; j++)//J为删除船员时需要的参数
		{

			int dCrewResId = R_DW(dCrewStart + j * 4);
			CrewInfo_ Crewtemp;
			Crewtemp.dIndex = j;
			Crewtemp.dShipId = dShipResId;
			Crewtemp.dResId = dCrewResId;
			CrewGroup.push_back(Crewtemp);

			////MyTrace(L"船ID %X 已选择船员ID %X\r\n", dShipResId, dCrewResId);
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
		////MyTrace(L"船ID %X %s 等级%d\r\n", dShipResId, csName, dShipLev);
	}

}

bool 航海::Yesornonauticalpicture()
{
	INT64 dUiObj = UI功能::getUiObjById(0xB2);//"root1.arkui.frameCanvas.anchorFrame"
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


void VoyageShipSelectShip(int dIndex)//选择船只
{
	INT64 dUiObj = UI功能::getUiObjById(0xB2);//"root1.arkui.frameCanvas.anchorFrame"
	if (dUiObj)
	{

		DWORD dShow = R_DW(dUiObj + 0x27C);
		if (dShow)
		{
			MainUniversalCALL2(dUiObj, dIndex, 游戏模块 + gc_VoyageShipSelectShip);
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

bool 航海::指定船员是否上船(DWORD dResId)
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
bool 航海::指定船员是否上了已装备的船(DWORD dResId)
{
	DWORD dShipID = 航海::getCurVoyageShipResId();
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
void 航海::删除所有船员()
{
	//MyTrace(L"删除所有船员");
	vector<ShipInfo_> ShipGroup;
	vector<CrewInfo_> CrewGroup;
	getVoyageShipList(ShipGroup, CrewGroup);
	for (size_t i = 0; i < CrewGroup.size(); i++)
	{
		VoyageShipDelCrew(CrewGroup[i].dIndex);
		Sleep(100);
	}
}
void 航海::设置所有船员()
{
	//MyTrace(L"设置所有船员");
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
bool 航海::自动选择最优战船()
{
	//MyTrace(L"选择最优战船");
	DWORD 已解锁船只数量 = getVoyageShipTotal();
	if (已解锁船只数量 == 1)
	{
		if (getCurVoyageShipResId() == 0x2008)
		{
			return true;
		}
		else
		{
			VoyageShipSelectShip(0);
			设置所有船员();
		}
	}
	if (已解锁船只数量 == 2)
	{
		if (getCurVoyageShipResId() == 0x2009)
		{
			return true;
		}
		else
		{
			VoyageShipSelectShip(1);
			设置所有船员();
		}
	}
	if (已解锁船只数量 == 3)
	{
		if (getCurVoyageShipResId() == 0x200B)
		{
			return true;
		}
		else
		{
			VoyageShipSelectShip(2);
			设置所有船员();
		}
	}
	if (已解锁船只数量 == 4)
	{
		if (getCurVoyageShipResId() == 0x200F)
		{
			return true;
		}
		else
		{
			VoyageShipSelectShip(3);
			设置所有船员();
		}
	}
	if (已解锁船只数量 == 5)
	{
		if (getCurVoyageShipResId() == 0x200D)
		{
			return true;
		}
		else
		{
			VoyageShipSelectShip(4);
			设置所有船员();
		}
	}
	if (已解锁船只数量 == 6)
	{
		if (getCurVoyageShipResId() == 0x200E)
		{
			return true;
		}
		else
		{
			VoyageShipSelectShip(5);
			设置所有船员();
		}
	}
	if (已解锁船只数量 == 7)
	{
		if (getCurVoyageShipResId() == 0x200A)
		{
			return true;
		}
		else
		{
			VoyageShipSelectShip(6);
			设置所有船员();
		}
	}
	if (已解锁船只数量 == 8)
	{
		if (getCurVoyageShipResId() == 0x200A)
		{
			return true;
		}
		else
		{
			VoyageShipSelectShip(7);
			设置所有船员();
		}
	}
	return false;
}

void 航海::坐船call功能(DWORD dResId)
{
	DWORD rdx = dResId;
	INT64 rcx =0;
	bool 是否打开 = UI功能::寻找打开窗口("root1.arkui.windowCanvas.voyageLinerWnd", rcx);
	if (rcx >= 1)
	{
	//	INT64 rcx1=R_QW(rcx);
		W_DW(rcx+ g_ShipsetID, dResId);
		////MyTrace(L"选择最优战船0x%I64X " , rcx);
			MainUniversalCALL6(rcx, 0, 0, 1,0,2, 游戏模块 + 基址_坐船call);

	}
}

void 航海::luaVoyageShipSelectShip(int dIndex)//选择船只
{

	VoyageShipSelectShip(dIndex);

}