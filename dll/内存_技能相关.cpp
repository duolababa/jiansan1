#include "内存_技能相关.h"
INT64 getSkillResAddrByLev(INT64 dListAddr, DWORD dLev)
{
	long dtotal = R_DW(dListAddr + 0x10 + 0x18);
	INT64 dKeyAddr = R_QW(dListAddr + 0x20);
	if (!dKeyAddr)
	{
		dKeyAddr = dListAddr + 0x10;
	}
	INT64 objStartAddr = R_QW(dListAddr);
	for (DWORD i = 0; i < dtotal; i++)
	{
		long dKeyValue = R_DW(dKeyAddr + (i / 0x20) * 4);
		DWORD dNum = i % 0x20;
		DWORD dCheck = (dKeyValue >> dNum) & 1;
		if (dCheck)
		{
			DWORD dId = R_DW(objStartAddr + i * 0x1C);
			if (dId && dId != 0xFFFFFFFF)
			{
				INT64 dObj = R_QW(objStartAddr + i * 0x1C + 4);
				if (dObj)
				{
					if (R_DW(dObj + 0xC) == dLev)
					{
						return dObj;
					}
				}
			}
		}
	}
	return 0;
}
INT64 getSkillResAddrByIdAndLev(DWORD dResId, DWORD dLev)
{
	DWORD dSkillResTypeIndex = getResIndexByName(L"Skill");
	INT64 dSkillResAddr = getResAddrById(dSkillResTypeIndex);
	////MyTrace(L"getSkillResAddrByIdAndLev 0x%I64X", dSkillResAddr);
	long dtotal = R_DW(dSkillResAddr + 0xAC);
	DWORD dHash = dResId & (dtotal - 1);
	INT64 objStartAddr = R_QW(dSkillResAddr + 0x68);//对象数组地址
	INT64 indexStartAddr = R_QW(dSkillResAddr + 0xA4);//索引数组地址
	INT64 dIndex = R_DW(indexStartAddr + dHash * 4);
	DWORD dOffest = dIndex * 0x54;
	if (dResId == R_DW(objStartAddr + dOffest))
	{
		////MyTrace(L"getSkillResAddrByLev 0x%I64x", objStartAddr + dOffest + 4);
		return getSkillResAddrByLev(objStartAddr + dOffest + 4, dLev);
	}
	else
	{
		DWORD dNextIndex = 0;
		while (1)
		{
			dNextIndex = R_DW(objStartAddr + dOffest + 0x4C);
			if (dNextIndex == 0xFFFFFFFF)//为-1跳出循环
			{
				break;
			}
			else
			{
				dOffest = dNextIndex * 0x54;
				if (dResId == R_DW(objStartAddr + dOffest))
				{
					//MyTrace(L"getSkillResAddrByLev 0x%I64x", objStartAddr + dOffest + 4);
					//return 0
					return getSkillResAddrByLev(objStartAddr + dOffest + 4, dLev);
				}
			}
		}
	}
	return 0;
}
int getSkillNextLevNeedPoints(DWORD dSkillId, DWORD dNextLev)
{
	INT64 dCurSkilllResAddr = getSkillResAddrByIdAndLev(dSkillId, dNextLev);
	if (dCurSkilllResAddr)
	{
		return R_DW(dCurSkilllResAddr + 0xD0);
	}
	return -1;
}

DWORD 技能::getRoleCurSkillPoints()
{
	INT64 addr_1 = R_QW(游戏模块 + gb_AttrList);
	INT64 addr_2 = R_QW(addr_1 + go_AttrList_off1);
	DWORD dCurType = R_BYTE(addr_2 + go_SkillCurPreset);
	INT64 dInfoAddr = R_QW(addr_2 + go_SkillCurPreset - 0x10);
	return R_W(dInfoAddr + dCurType * 2);
}
SkillInfo_ getSkillInfo(INT64 dSkillObj)
{
	////MyTrace(L"1");
	SkillInfo_ temp;
	INT64 dSkillInfo = R_QW(dSkillObj + 0x50);
	DWORD dSkillId = R_DW(dSkillInfo);
	DWORD dSkillLev = R_BYTE(dSkillInfo + 0x4);
	int dNeedPoints = getSkillNextLevNeedPoints(dSkillId, dSkillLev + 1);//新加20220312
	BOOL bCanUpGrade = FALSE;
	if (dNeedPoints)//新加20220312
	{
		if (dNeedPoints <= 技能::getRoleCurSkillPoints())
		{
			bCanUpGrade = TRUE;
		}
	}
	DWORD dSkillD1 = R_BYTE(dSkillInfo + 0x5);//猜测天赋1
	DWORD dSkillD2 = R_BYTE(dSkillInfo + 0x6);
	DWORD dSkillD3 = R_BYTE(dSkillInfo + 0x7);
	DWORD dRange = R_W(dSkillInfo + 0x1C + 8);
	DWORD dSkillType = R_BYTE(dSkillInfo + 0x34 + 8);
	INT64 addr = R_QW(dSkillInfo + 0x10);
	INT64 dNameAddr = R_QW(addr + 0x10);
	CString csName = L"空";
	if (dNameAddr)
	{
		csName = R_CString(dNameAddr);
		//csName = GetName( dNameAddr);//dm.ReadStringAddr(dNameAddr,1,0); //
		//wcscpy(bi.wName,csName.GetBuffer(0));
	}
	////MyTrace(L"2");
	//wchar_t buf[100];
	if (bCanUpGrade)
	{
		temp.dCanUpGrade = true;
		//swprintf(buf, L"地址0x%I64X ID %X 类型%d %s 等级%d 范围%d 升级点数%d 可升级\r\n 天赋1:%d 天赋2:%d 天赋3:%d", dSkillInfo, dSkillId, dSkillType, csName, dSkillLev, dRange, dNeedPoints, dSkillD1, dSkillD2, dSkillD3);

	}
	else
	{
		temp.dCanUpGrade = false;
		//swprintf(buf, L"地址0x%I64X ID %X 类型%d %s 等级%d 范围%d 升级点数%d 不可升级\r\n 天赋1:%d 天赋2:%d 天赋3:%d", dSkillInfo, dSkillId, dSkillType, csName, dSkillLev, dRange, dNeedPoints, dSkillD1, dSkillD2, dSkillD3);

	}
	temp.objBase = dSkillObj;
	temp.InfoObj = dSkillInfo;
	temp.dSkillId = dSkillId;
	temp.dSkillType = dSkillType;
	temp.名称 = csName;
	temp.dUpGradeNeedPoint = dNeedPoints;
	temp.dSkillLev = dSkillLev;
	temp.天赋1 = dSkillD1;
	temp.天赋2 = dSkillD2;
	temp.天赋3 = dSkillD3;
	temp.dRange = dRange;
	temp.是否冷却 = 技能::冷却判断(dSkillObj);
	////MyTrace(L"2.5");
	if (temp.dSkillId == 37100)//魔力释放
	{
		temp.键位 = 8;
	}
	else if (temp.dSkillId == 37110)//瞬闪
	{
		temp.键位 = 9;
	}
	else
	{
		temp.键位 = 通过技能ID获取键码(dSkillId);
	}
	////MyTrace(L"3");
	////MyTrace(L"地址0x%I64X ID %X 类型%d %s \r\n", dSkillInfo, dSkillId, dSkillType, temp.名称);
	return temp;

}
void TravelTree(INT64 BTaddr, vector<SkillInfo_>& vsk)
{
	SkillInfo_ temp;
	BYTE bCheck = R_BYTE(BTaddr + 0x19);
	if (!bCheck)
	{
		DWORD dSkillId = R_DW(BTaddr + 0x20);
		INT64 dSkillObj = R_QW(BTaddr + 0x28);
		temp = getSkillInfo(dSkillObj);
		vsk.push_back(temp);
		INT64 LTNode = R_QW(BTaddr);
		TravelTree(LTNode, vsk);
		INT64 RTNode = R_QW(BTaddr + 0x10);
		TravelTree(RTNode, vsk);

	}
}
void 技能::get_SkillList(vector<SkillInfo_>& vsk)
{
	INT64 addr_1 = R_QW(游戏模块 + gb_ActorList);
	INT64 addr_2 = R_QW(addr_1 + go_hj_myRole/*0x3A4*/);
	INT64 addr_3 = R_QW(addr_2 + 0x18);
	INT64 addr_4 = R_QW(addr_3 + go_sk_offset);
	INT64 addr_5 = R_QW(addr_4 + 0 * 8);
	addr_5 = addr_5 + 4;
	DWORD dtotal = R_DW(addr_5 + 0x8);
	INT64 addr_6 = R_QW(addr_5);
	INT64 addr = R_QW(addr_6 + 8);
	TravelTree(addr, vsk);
}
void getSkillShortInfo(INT64 dSkillArray, DWORD dPage, vector<ShortCutInfo_>& vsk)
{
	ShortCutInfo_ temp;
	for (int i = 0; i < 8; i++)
	{
		DWORD dSkillId = R_DW(dSkillArray + i * 0x14 + 4);
		/*if (dSkillId)
		{*/
		temp.dPage = dPage;
		temp.键位 = i;
		temp.dId = dSkillId;
		temp.type = 1;
		vsk.push_back(temp);
		////MyTrace(L"页面%d 键索引%d 地址0x%I64X  id %X\r\n", dPage, i, dSkillArray, dSkillId);
	//}
	}
}
void TravelTreeSkillShort(INT64 BTaddr, vector<ShortCutInfo_>& vsk, DWORD dCurPage)
{
	BYTE bCheck = R_DW(BTaddr + 0x19);
	if (!bCheck)
	{
		DWORD dPage = R_BYTE(BTaddr + 0x20);
		if (dPage == dCurPage)
		{
			INT64 dSkillArray = R_QW(BTaddr + 0x28);
			getSkillShortInfo(dSkillArray, dPage, vsk);
		}
		/*INT64 dSkillArray = R_QW(BTaddr + 0x28);
		getSkillShortInfo(dSkillArray, dPage, vsk);*/
		INT64 LTNode = R_QW(BTaddr);
		TravelTreeSkillShort(LTNode, vsk, dCurPage);
		INT64 RTNode = R_QW(BTaddr + 0x10);
		TravelTreeSkillShort(RTNode, vsk, dCurPage);

	}
}
void geQuickSlotStateByType(DWORD dSlotType, vector<ShortCutInfo_>& vsk)//战斗技能传0
{
	INT64 dUiObj = UI功能::getUiObjById(0x2D);//quickSlotFrame
	//MyTrace(L"技能obj 0x%I64X", dUiObj);
	dUiObj = R_QW(dUiObj + go_quickSlotFramePageArray);
	if (dUiObj)
	{
		__int64 addr_1 = R_QW(dUiObj + dSlotType * 0x8);
		if (addr_1)
		{
			INT64 addr_2 = getUiFirstAddr(addr_1);
			INT64 addr_3 = getChildUiAddrByStr(addr_2, L"drawCanvas");
			int dTotal = R_DW(addr_3 + 0xE8);
			INT64 dstart = R_QW(addr_3 + 0xE0);
			if (dTotal > 8)
			{
				return;
			}
			for (int i = 0; i < dTotal; i++)
			{

				INT64 addr_4 = R_QW(dstart + i * 0x10);
				INT64 dataAddr = R_QW(addr_4 + 0x150);
				DWORD dStateValue = R_DW(dataAddr + 0x358);
				INT64 dCoolAddr = getChildUiAddrByStr(addr_4, L"coolDown");
				DWORD dCoolValue = R_W(dCoolAddr + 0x6A);
				BOOL bCollView = 0;
				BOOL bIdentityView = 0;
				if (dCoolValue >> 0xe == 1)
				{
					bCollView = 1;//冷却中
				}
				if (bCollView == 1)
				{
					vsk[i].是否冷却 = false;
				}
				else
				{
					vsk[i].是否冷却 = true;
				}

				vsk[i].技能状态 = dStateValue;
			MyTrace(L"快捷键索引%d 0x%I64X 冷却显示%X  状态值 %d \r\n", i, dCoolAddr, bCollView, dStateValue);//dStateValue 正常为0 脱下武器为2 不够能量为3
			}
		}
	}

}
DWORD 技能::get_SkillShortCurPage()
{
	INT64 addr_1 = R_QW(游戏模块 + gb_ShortKey + 8);
	BYTE dCurPage = R_BYTE(addr_1 + 0x9C);
	return dCurPage;
}
DWORD 技能::SKLLADDR(DWORD ID)
{
	INT64 addr_1 = R_QW(R_QW(R_QW(R_QW(游戏模块 + 基址_技能_快捷栏)+0xA8))+0x28);
	DWORD a=R_DW(addr_1 + ID * 5 * 4 + 4);
	return a;
}





void 技能::get_SkillShortList(vector<ShortCutInfo_>& vsk)
{
	vsk.clear();
	INT64 addr_1 = R_QW(游戏模块 + gb_ShortKey + 8);
	BYTE dCurPage = R_BYTE(addr_1 + 0x9C);
	INT64 addr_2 = R_QW(addr_1 + 0xA8);
	INT64 addr = R_QW(addr_2 + 8);
	TravelTreeSkillShort(addr, vsk, dCurPage);
	geQuickSlotStateByType(dCurPage, vsk);
}


void 技能::get_SkillShortList1(vector<ShortCutInfo_>& vsk, DWORD xxx)
{
	vsk.clear();
	INT64 addr_1 = R_QW(游戏模块 + gb_ShortKey + 8);
	BYTE dCurPage = R_BYTE(addr_1 + 0x9C);
	INT64 addr_2 = R_QW(addr_1 + 0xA8);
	INT64 addr = R_QW(addr_2 + 8);
	TravelTreeSkillShort(addr, vsk, dCurPage);
	geQuickSlotStateByType(xxx, vsk);


}


void 技能::get_RightShortList(vector<ShortCutInfo_>& vsk)
{
	vsk.clear();
	ShortCutInfo_ temp;
	INT64 addr_1 = R_QW(游戏模块 + gb_ShortKey);
	INT64 addr_2 = R_QW(addr_1 + go_AttrList_off1);
	DWORD dCurPage = R_BYTE(addr_2 + go_ShortKey_CurPage);
	DWORD dPageSize = 0xC3;
	for (int i = 0; i < 6; i++)
	{
		INT64 dStartAddr = addr_2 + go_ShortKey_CurPage + 1;
		DWORD dItemId = R_DW(dStartAddr + (i + 1) * 0xF + dCurPage * dPageSize);
		if (dItemId)
		{
			INT64 dItemResAddr = getItemResAddrById(dItemId);
			INT64 dNameAddr = R_QW(dItemResAddr + 0x10);
			CString Name = CString(UnicodeToAnsi(R_CString(dNameAddr)));
			temp.dId = dItemId;
			temp.dPage = dCurPage;
			temp.objBase = addr_2;
			temp.type = 2;
			temp.名称 = Name;
			temp.键位 = i + 1;
			vsk.push_back(temp);
			//MyTrace(L"dStartAddr 0x%I64X %d键 物品id %X %s\r\n", dStartAddr, i + 1, dItemId, Name);
		}

	}
	for (int i = 0; i < 4; i++)
	{
		//INT64 dStartAddr = addr_2 + go_ShortKey_CurPage + 0x6D;
		INT64 dStartAddr = addr_2 + go_ShortKey_CurPage + 1;
		DWORD dItemId = R_DW(dStartAddr + (i + 7) * 0xF + dCurPage * dPageSize);
		if (dItemId)
		{
			INT64 dItemResAddr = getItemResAddrById(dItemId);
			INT64 dNameAddr = R_QW(dItemResAddr + 0x10);
			CString Name = CString(UnicodeToAnsi(R_CString(dNameAddr)));
			temp.dId = dItemId;
			temp.dPage = dCurPage;
			temp.objBase = addr_2;
			temp.type = 3;
			temp.名称 = Name;
			temp.键位 = i + 1;
			vsk.push_back(temp);
			//MyTrace(L"%d键 战斗物品id %X %s \r\n", i + 1, dItemId, Name);
		}

	}
}

DWORD 通过技能ID获取键码(DWORD SKILLID)
{
	vector<ShortCutInfo_>vsk;
	技能::get_SkillShortList(vsk);
	for (size_t i = 0; i < vsk.size(); i++)
	{
		if (SKILLID == vsk[i].dId)
		{
			return vsk[i].键位;
		}
	}
	return -1;
}
bool 技能::冷却判断(INT64 技能对象指针)
{
	float 局_判断标志 = R_Float(技能对象指针 + 36);
	if (局_判断标志 == 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

//int 技能::取可使用技能点数()
//{
//	INT64 v1 = R_QW(R_QW(游戏模块 + gb_AttrList) + 220);
//	INT64 v2 = R_QW(v1 + 偏移_技能_技能点数);
//}
//void 技能::升级技能(DWORD 技能ID,DWORD 目标等级)
//{
//	INT64 局_rcx=
//}

bool 技能::写怪物坐标到鼠标(坐标_ 怪物坐标)
{
	INT64 鼠标地址 = R_QW(R_QW(游戏模块 + 基址_鼠标_坐标) + 176) + 偏移_鼠标_坐标;
	if (鼠标地址 == 0)
	{
		return false;
	}
	if (IsBadReadPtr((VOID*)鼠标地址, 8))
	{
		return false;
	}
	INT64 鼠标地址y = 鼠标地址 + 4;
	INT64 游戏坐标转鼠标CALL = 游戏模块 + 基址_鼠标_游戏坐标转鼠标call;
	INT64 局_鼠标_游戏坐标转鼠标rcx = 游戏模块 + 基址_鼠标_游戏坐标转鼠标rcx;
	//坐标_ 局_坐标指针;
	UCHAR pBuff[0x100] = { 0 };
	W_Float((ULONG64)&pBuff[0], 怪物坐标.x);
	W_Float((ULONG64)&pBuff[4], 怪物坐标.y);
	W_Float((ULONG64)&pBuff[8], 怪物坐标.z);
	INT64 局_坐标指针 = (ULONG64)&pBuff;
	//局_坐标指针 = 怪物坐标;
	/*INT64 局_坐标指针 = INT64(申请内存2(HANDLE(-1), 100));
	W_Float(局_坐标指针, 怪物坐标.x);
	W_Float(局_坐标指针+4, 怪物坐标.y);
	W_Float(局_坐标指针 + 8, 怪物坐标.z);
	INT64 局_鼠标结果指针 = INT64(申请内存2(HANDLE(-1), 100));*/
	UCHAR pBuff2[0x100] = { 0 };
	INT64 局_鼠标结果指针 = (INT64)&pBuff2;
	MainUniversalCALL4(局_鼠标_游戏坐标转鼠标rcx, 局_坐标指针, 局_鼠标结果指针, 0, 游戏坐标转鼠标CALL);
	int intValue = static_cast<int>(std::round(R_Float(局_鼠标结果指针)));
	int x = intValue;
	intValue = static_cast<int>(std::round(R_Float(局_鼠标结果指针+4)));
	int y = intValue;
		W_DW(鼠标地址,x);
		W_DW(鼠标地址+4, y);

	return true;
}

bool 技能::写怪物坐标到鼠标2(float fx, float fy, float fz)
{
	INT64 dMuoseInfo = R_QW(游戏模块 + gb_MouseInfo);
	if (dMuoseInfo == 0)
	{
		return false;
	}
	if (IsBadReadPtr((VOID*)dMuoseInfo, 8))
	{
		return false;
	}
	INT64 游戏坐标转鼠标CALL = 游戏模块 + 基址_鼠标_游戏坐标转鼠标call;
	INT64 局_鼠标_游戏坐标转鼠标rcx = 游戏模块 + 基址_鼠标_游戏坐标转鼠标rcx;
	//坐标_ 局_坐标指针;
	UCHAR pBuff[0x100] = { 0 };
	W_Float((ULONG64)&pBuff[0], fx);
	W_Float((ULONG64)&pBuff[4], fy);
	W_Float((ULONG64)&pBuff[8], fz);
	INT64 局_坐标指针 = (ULONG64)&pBuff;
	//局_坐标指针 = 怪物坐标;
	/*INT64 局_坐标指针 = INT64(申请内存2(HANDLE(-1), 100));
	W_Float(局_坐标指针, 怪物坐标.x);
	W_Float(局_坐标指针+4, 怪物坐标.y);
	W_Float(局_坐标指针 + 8, 怪物坐标.z);
	INT64 局_鼠标结果指针 = INT64(申请内存2(HANDLE(-1), 100));*/
	UCHAR pBuff2[0x100] = { 0 };
	INT64 局_鼠标结果指针 = (INT64)&pBuff2;
	MainUniversalCALL4(局_鼠标_游戏坐标转鼠标rcx, 局_坐标指针, 局_鼠标结果指针, 0, 游戏坐标转鼠标CALL);
	int dPx = R_DW(局_鼠标结果指针);
	int dPy = R_DW(局_鼠标结果指针 + 4);
	W_DW(dMuoseInfo + go_MousePoint, dPx);
	W_DW(dMuoseInfo + go_MousePoint + 4, dPy);
	//释放内存2(HANDLE(-1), (LPVOID)局_鼠标结果指针, 100);
	//释放内存2(HANDLE(-1), (LPVOID)局_坐标指针, 100);
	//CALL4(局_鼠标_游戏坐标转鼠标rcx, ULONG_PTR(pBuff), (INT64)&局_鼠标结果指针, 0,游戏坐标转鼠标CALL);
	/*//MyTrace(L"转换结果 %d,%d", R_DW(局_鼠标结果指针), R_DW(局_鼠标结果指针 + 4));
	W_DW(鼠标地址, R_DW(局_鼠标结果指针));
	W_DW(鼠标地址 + 4, R_DW(局_鼠标结果指针 + 4));*/
	return true;
}

DWORD 技能::技能键码转换(int 键位)
{
	if (键位 == 0)//Q
	{
		return DWORD('Q');
	}
	else if (键位 == 1)//W
	{
		return DWORD('W');
	}
	else if (键位 == 2)//E
	{
		return DWORD('E');
	}
	else if (键位 == 3) // R
	{
		return DWORD('R');
	}
	else if (键位 == 4) // A
	{
		return DWORD('A');
	}
	else if (键位 == 5) // S
	{
		return DWORD('S');
	}
	else if (键位 == 6) // D
	{
		return DWORD('D');
	}
	else if (键位 == 7) // F
	{
		return DWORD('F');
	}
	else if (键位 == 8) // Z
	{
		return DWORD('Z');
	}
	else if (键位 == 9) // X
	{
		return DWORD('X');
	}
	return 0;
}

DWORD 技能::右侧快捷键键码转换(int type, int 键位)
{
	if (type == 2)
	{
		if (键位 == 1)//Q
		{
			return DWORD(VK_F1);
		}
		else if (键位 == 2)//W
		{
			return DWORD('5');
		}
		else if (键位 == 3)//E
		{
			return DWORD('6');
		}
		else if (键位 == 4) // R
		{
			return DWORD('7');
		}
		else if (键位 == 5) // A
		{
			return DWORD('8');
		}
		else if (键位 == 6) // S
		{
			return DWORD('9');
		}
	}
	if (type == 1)
	{
		if (键位 == 1)//Q
		{
			return DWORD('1');
		}
		else if (键位 == 2)//W
		{
			return DWORD('2');
		}
		else if (键位 == 3)//E
		{
			return DWORD('3');
		}
		else if (键位 == 4) // R
		{
			return DWORD('4');
		}

	}
	return 0;
}

void 技能::技能释放(坐标_ 怪物坐标)
{
	vector<SkillInfo_>技能数组;
	技能::get_SkillList(技能数组);
	技能::屏蔽鼠标();
	技能::写怪物坐标到鼠标(怪物坐标);
	//技能::写怪物坐标到鼠标2(怪物坐标.x, 怪物坐标.y, 怪物坐标.z);
	//技能::写怪物坐标到鼠标(怪物坐标);
	bool 是否释放技能 = false;
	for (size_t i = 0; i < 技能数组.size(); i++)
	{
		if (技能数组[i].是否冷却 == true && 技能数组[i].键位 != -1 && 技能数组[i].键位 != 8 && 技能数组[i].键位 != 9)
		{
			//MyTrace(L"使用技能 %s %d", 技能数组[i].名称, 技能数组[i].键位);
			if (技能数组[i].dSkillId == 37340)//极寒召唤
			{
				UI功能::内存按键(技能::技能键码转换(技能数组[i].键位), 0);
				Sleep(5000);
				UI功能::内存按键(技能::技能键码转换(技能数组[i].键位), 1);
				是否释放技能 = true;
				break;
			}
			else if (技能数组[i].dSkillId == 37240)//极寒召唤
			{
				UI功能::内存按键(技能::技能键码转换(技能数组[i].键位));
				Sleep(800);
				UI功能::内存按键(技能::技能键码转换(技能数组[i].键位));
				Sleep(500);
				是否释放技能 = true;
				break;
			}
			else if (技能数组[i].dSkillId == 37270) //天罚;
			{
				UI功能::内存按键(技能::技能键码转换(技能数组[i].键位));
				Sleep(300);
				UI功能::内存按键(技能::技能键码转换(技能数组[i].键位));
				Sleep(3000);
				是否释放技能 = true;
				break;
			}
			else
			{
				UI功能::内存按键(技能::技能键码转换(技能数组[i].键位));
				是否释放技能 = true;
				Sleep(500);
				break;
			}
		}
	}
	if (是否释放技能 == false)
	{
		UI功能::内存按键(DWORD('C'));
		Sleep(300);
	}
	技能::解除屏蔽鼠标();
}

void 技能::屏蔽鼠标()
{
	char 校验[] = { 0xCC };
	写内存字节集((HANDLE)-1, (LPVOID)(游戏模块 + 基址_鼠标_鼠标写入地址), LPVOID(&校验), 1);
}
void 技能::解除屏蔽鼠标()
{
	char 校验2[] = { 0xE8 };
	写内存字节集((HANDLE)-1, (LPVOID)(游戏模块 + 基址_鼠标_鼠标写入地址), LPVOID(&校验2), 1);
}
void 技能::技能释放2(坐标_ 怪物坐标)
{
	vector<ShortCutInfo_>技能数组;
	技能::get_SkillShortList(技能数组);
	技能::屏蔽鼠标();
	技能::写怪物坐标到鼠标(怪物坐标);
	//技能::写怪物坐标到鼠标2(怪物坐标.x, 怪物坐标.y, 怪物坐标.z);
	//技能::写怪物坐标到鼠标(怪物坐标);
	bool 是否释放技能 = false;

	for (size_t i = 0; i < 技能数组.size(); i++)
	{
		if (技能数组[i].dPage == 0)
		{
			if (技能数组[i].dId > 0 && 技能数组[i].是否冷却 == true && 技能数组[i].技能状态 == 0 && 技能数组[i].键位 != -1 && 技能数组[i].键位 != 8 && 技能数组[i].键位 != 9)
			{
				//MyTrace(L"使用技能 %d", 技能数组[i].键位);
				if (技能数组[i].dId == 37340)//极寒召唤
				{
					UI功能::内存按键(技能::技能键码转换(技能数组[i].键位), 0);
					Sleep(5000);
					UI功能::内存按键(技能::技能键码转换(技能数组[i].键位), 1);
					是否释放技能 = true;
					break;
				}
				else if (技能数组[i].dId == 37240)//极寒召唤
				{
					UI功能::内存按键(技能::技能键码转换(技能数组[i].键位));
					Sleep(800);
					UI功能::内存按键(技能::技能键码转换(技能数组[i].键位));
					Sleep(500);
					是否释放技能 = true;
					break;
				}
				else if (技能数组[i].dId == 37270) //天罚;
				{
					UI功能::内存按键(技能::技能键码转换(技能数组[i].键位));
					Sleep(300);
					UI功能::内存按键(技能::技能键码转换(技能数组[i].键位));
					Sleep(3000);
					是否释放技能 = true;
					break;
				}
				else
				{
					UI功能::内存按键(技能::技能键码转换(技能数组[i].键位));
					是否释放技能 = true;
					Sleep(500);
					break;
				}
			}
		}
		else
		{
			if (技能数组[i].键位 == 3)
			{
				continue;
			}
			else
			{
				if (技能数组[i].dId == 0x174A8)
				{
					UI功能::内存按键(技能::技能键码转换(技能数组[i].键位), 0);
					Sleep(1500);
					UI功能::内存按键(技能::技能键码转换(技能数组[i].键位), 1);
					是否释放技能 = true;
					Sleep(500);
					break;
				}

				//MyTrace(L"dpage %d 使用技能 %d ID %X", 技能数组[i].dPage, 技能数组[i].键位, 技能数组[i].dId);
				UI功能::内存按键(技能::技能键码转换(技能数组[i].键位));
				是否释放技能 = true;
				Sleep(300);
				continue;
			}
		}

	}
	if (是否释放技能 == false)
	{
		if (技能::get_SkillShortCurPage() == 0)
		{
			UI功能::内存按键(DWORD('C'));
			Sleep(300);
		}

	}
	技能::解除屏蔽鼠标();
}
void 测试打怪(INT64 怪物obj)
{
	clock_t 打怪时间 = 取启动时间();
	while (取启动时间() - 打怪时间 <= 1 * 60 * 1000)
	{
		objInfo_ 怪物信息 = 环境::getActorInfo(怪物obj);
		if (怪物信息.dCurHp <= 0)
		{
			//MyTrace(L"%s 怪物已死亡 %0.3f, %0.3f, %0.3f", 怪物信息.wName, 怪物信息.坐标.x, 怪物信息.坐标.y, 怪物信息.坐标.z);
			break;
		}
		else
		{
			//MyTrace(L"攻击怪物 %s %d/%d %0.3f, %0.3f, %0.3f", 怪物信息.wName, 怪物信息.dCurHp, 怪物信息.dMaxHp, 怪物信息.坐标.x, 怪物信息.坐标.y, 怪物信息.坐标.z);
			技能::技能释放(怪物信息.坐标);
		}
	}
}

SkillInfo_ 技能::取出指定技能信息(DWORD SkillID, vector<SkillInfo_>& vsk)
{
	SkillInfo_ temp;
	for (size_t i = 0; i < vsk.size(); i++)
	{
		if (SkillID == vsk[i].dSkillId)
		{
			temp = vsk[i];
			break;
		}
	}
	return temp;

}

bool 技能::CALL_升级技能天赋(DWORD 技能ID, DWORD 等级, DWORD 特性1, DWORD 特性2, DWORD 特性3)
{
	//MyTrace(L"升级技能 %d 等级 %d", 技能ID, 等级);
	INT64 局_RCX = R_QW(游戏模块 + 基址_封包_发包rcx);
	if (局_RCX == 0)
	{
		return false;
	}
	INT64 局_CALL = 游戏模块 + 基址_封包_发包call;
	INT64 局_包头 = 游戏模块 + 基址_技能_升级技能包头;
	UCHAR puff[0x1000] = { 0 };
	//W_QW((INT64)&puff[0], 局_包头);
	//W_QW((INT64)&puff[8], 0);
	//W_QW((INT64)&puff[16], 0);
	//W_BYTE((INT64)&puff[24], 1);
	//W_DW((INT64)&puff[26], 技能ID);
	//W_BYTE((INT64)&puff[33], 等级);
	//W_BYTE((INT64)&puff[0x1E], 特性1);
	//W_BYTE((INT64)&puff[0x1F], 特性2);
	//W_BYTE((INT64)&puff[0x20], 特性3);

	/*W_QW((INT64)&puff[0], 局_包头);
	W_QW((INT64)&puff[8], 0);
	W_QW((INT64)&puff[16], 0);
	W_BYTE((INT64)&puff[24], 1);
	W_DW((INT64)&puff[0x1A], 技能ID);
	W_BYTE((INT64)&puff[0x1E], 等级);
	W_BYTE((INT64)&puff[0x1F], 特性1);
	W_BYTE((INT64)&puff[0x20], 特性2);
	W_BYTE((INT64)&puff[0x21], 特性3);*/
	/*W_QW((INT64)&puff[0], 局_包头);
	W_QW((INT64)&puff[8], 0);
	W_QW((INT64)&puff[16], 0);
	W_BYTE((INT64)&puff[24], 1);
	W_DW((INT64)&puff[0x1B], 技能ID);
	W_BYTE((INT64)&puff[0x1A], 等级);
	W_BYTE((INT64)&puff[0x1F], 特性1);
	W_BYTE((INT64)&puff[0x20], 特性2);
	W_BYTE((INT64)&puff[0x21], 特性3);*/
	for (size_t i = 0; i <= 15; i++)
	{
		W_QW((INT64)&puff[0x28 + i * 0xE], 0x100010001);
		//W_Word((INT64)&puff[0x21 + i * 0xE + 4], 1);
	}
	W_QW((INT64)&puff[0], 局_包头);
	W_QW((INT64)&puff[8], 0);
	W_QW((INT64)&puff[16], 0);
	W_BYTE((INT64)&puff[0x18], 1);
	W_BYTE((INT64)&puff[0x20], 等级);
	W_DW((INT64)&puff[0x21], 技能ID);
	W_BYTE((INT64)&puff[0x25], 特性1);
	W_BYTE((INT64)&puff[0x26], 特性2);
	W_BYTE((INT64)&puff[0x27], 特性3);



	//W_DW((INT64)&puff[0x110], 0xC0);
	MainUniversalCALL2(局_RCX, (ULONG_PTR)puff, 局_CALL);

	return true;
}
bool 技能::自动升级技能(DWORD 技能ID, DWORD 等级, DWORD 特性1, DWORD 特性2, DWORD 特性3, DWORD 优先等级)
{
	////MyTrace(L"自动升级技能1");
	vector<SkillInfo_>vsk;
	get_SkillList(vsk);
	////MyTrace(L"自动升级技能2");
	SkillInfo_ SKILL;
	SKILL = 取出指定技能信息(技能ID, vsk);

	if (SKILL.dSkillId = 技能ID)
	{
		//MyTrace(L"自动升级技能 SKill %d  %d 天赋1 %d 天赋2 %d 天赋3 %d", SKILL.dSkillId, SKILL.dSkillLev, SKILL.天赋1, SKILL.天赋2, SKILL.天赋3);
		if (SKILL.dSkillLev >= 4)
		{
			if (SKILL.天赋1 != 特性1)
			{
				技能::CALL_升级技能天赋(SKILL.dSkillId, SKILL.dSkillLev, 特性1, SKILL.天赋2, SKILL.天赋3);
			}
		}
		if (SKILL.dSkillLev >= 7)
		{
			if (SKILL.天赋2 != 特性2)
			{
				技能::CALL_升级技能天赋(SKILL.dSkillId, SKILL.dSkillLev, 特性1, 特性2, SKILL.天赋3);
			}
		}
		if (SKILL.dSkillLev == 10)
		{
			if (SKILL.天赋3 != 特性3)
			{
				技能::CALL_升级技能天赋(SKILL.dSkillId, SKILL.dSkillLev, 特性1, 特性2, 特性3);
			}
		}

		if (SKILL.dCanUpGrade == true && SKILL.dSkillLev < 等级)
		{
			//MyTrace(L"技能升级 %s", SKILL.名称);
			技能::CALL_升级技能天赋(SKILL.dSkillId, SKILL.dSkillLev + 1, SKILL.天赋1, SKILL.天赋2, SKILL.天赋3);
			return false;
		}
		if (SKILL.dSkillLev < 优先等级)
		{
			return false;
		}

	}
	//女巫
	return true;
}
void  技能::自动升级女巫技能()
{
	if (!技能::自动升级技能(37200, 10, 2, 2, 1, 7))
	{
		return;
	}
	if (!技能::自动升级技能(37320, 10, 3, 1, 1))
	{
		return;
	}
	if (!技能::自动升级技能(37310, 10, 1, 1, 1))
	{
		return;
	}
	if (!技能::自动升级技能(37210, 10, 1, 1, 1))
	{
		return;
	}

	if (!技能::自动升级技能(37270, 10, 3, 2, 1))
	{
		return;
	}
	if (!技能::自动升级技能(37230, 10, 3, 3, 1))
	{
		return;
	}
	if (!技能::自动升级技能(37260, 10, 3, 3, 1))
	{
		return;
	}
	if (!技能::自动升级技能(37280, 10, 3, 3, 1))
	{
		return;
	}
	if (!技能::自动升级技能(37220, 10, 1, 1, 1))
	{
		return;
	}
}

void 技能::CALL_快捷键技能摆放(DWORD 技能ID, DWORD 位置)
{
	INT64 dRCX = R_QW(游戏模块 + gb_ShortKey + 0x8);
	INT64 dCALL = 游戏模块 + gc_SkillShortKeySet;
	DWORD dCurIndex = 0xFFFFFFFF;//从技能拦拖放
	MainUniversalCALL6(dRCX, dCurIndex, 0, 位置, 技能ID, 0, dCALL);
}
DWORD 技能::判断技能等级(DWORD 技能ID)
{
	vector<SkillInfo_>vsk;
	get_SkillList(vsk);
	for (size_t i = 0; i < vsk.size(); i++)
	{
		if (vsk[i].dSkillId == 技能ID)
		{
			return vsk[i].dSkillLev;
		}
	}
	return 0;
}

void 技能::摆放与学习技能()
{
	if (技能::get_SkillShortCurPage() == 0)
	{
		////MyTrace(L"判断技能加点时间2");
		vector<ShortCutInfo_>vsk;
		技能::get_SkillShortList(vsk);
		////MyTrace(L"判断技能加点时间3");
		for (size_t i = 0; i < vsk.size(); i++)
		{
			if (i == 0)
			{
				if (vsk[i].dId != 37260)
				{
					if (技能::判断技能等级(37260) > 0)
					{
						//MyTrace(L"判断技能加点时间37260");
						技能::CALL_快捷键技能摆放(37260, i);
					}
				}
			}
			if (i == 1)
			{
				if (vsk[i].dId != 37280)
				{
					if (技能::判断技能等级(37280) > 0)
					{
						//MyTrace(L"判断技能加点时间37280");
						技能::CALL_快捷键技能摆放(37280, i);
					}
				}
			}
			if (i == 2)
			{
				if (vsk[i].dId != 37320)
				{
					if (技能::判断技能等级(37320) > 0)
					{
						//MyTrace(L"判断技能加点时间37320");
						技能::CALL_快捷键技能摆放(37320, i);
					}
				}
			}
			if (i == 3)
			{
				if (vsk[i].dId != 37310)
				{
					if (技能::判断技能等级(37310) > 0)
					{
						//MyTrace(L"判断技能加点时间37310");
						技能::CALL_快捷键技能摆放(37310, i);
					}
				}
			}
			if (i == 4)
			{
				if (vsk[i].dId != 37210)
				{
					if (技能::判断技能等级(37210) > 0)
					{
						//MyTrace(L"判断技能加点时间37210");
						技能::CALL_快捷键技能摆放(37210, i);
					}
				}
			}
			if (i == 5)
			{
				if (vsk[i].dId != 37220)
				{
					if (技能::判断技能等级(37220) > 0)
					{
						//MyTrace(L"判断技能加点时间37220");
						技能::CALL_快捷键技能摆放(37220, i);
					}
				}
			}
			if (i == 6)
			{
				if (vsk[i].dId != 37230)
				{
					if (技能::判断技能等级(37230) > 0)
					{
						//MyTrace(L"判断技能加点时间37230");
						技能::CALL_快捷键技能摆放(37230, i);
					}
				}
			}
			if (i == 7)
			{
				if (vsk[i].dId != 37200)
				{
					if (技能::判断技能等级(37200) > 0)
					{
						//MyTrace(L"判断技能加点时间37200");
						技能::CALL_快捷键技能摆放(37200, i);
					}
				}
			}

		}
		//Sleep(2000);
		//MyTrace(L"升级技能");
		技能::自动升级女巫技能();
	}
}

void CalcAngel(float RenX, float RenY, float RenZ, float X, float Y, float Z, float& AngelX, float& AngelY, float& AngelZ)
{
	float xx[10] = { 0,0,0 };
	xx[0] = X - RenX;
	xx[1] = Y - RenY;

	AngelX = xx[0];
	AngelY = xx[1];
}

void UseSkill_C(DWORD dwSkillID, float x, float y, float z)
{
	
		ULONG64 dwManID = R_QW(R_QW(游戏模块+基址_个人_坐标) + 0xA0);
		ULONG64 dwEcx = dwManID + go_UseSkillOffset;
		BYTE Buf[500] = {0};
		if (dwManID != 0)
		{
			ULONG64 dwSecBase = R_QW(dwManID + go_ManPoBaseOffset);
			float px = R_Float(dwSecBase + 偏移_坐标);
			float py = R_Float(dwSecBase + 偏移_坐标+4);
			float pz = R_Float(dwSecBase + 偏移_坐标+8);
			float AngleX;
			float AngleY;
			float AngleZ;
			CalcAngel(px,py,pz,x,y,z,AngleX,AngleY,AngleZ);
			//
			*(ULONG64*)(Buf + 0x0) = 0x240044040;
			//面向float
			*(float*)(Buf + 0x24) = AngleX;
			*(float*)(Buf + 0x28) = AngleY;
			//玩家坐标
			*(float*)(Buf + 0x30) = px;
			*(float*)(Buf + 0x34) = py;
			*(float*)(Buf + 0x38) = pz;
			*(float*)(Buf + 0x3C) = px;
			*(float*)(Buf + 0x40) = py;
			*(float*)(Buf + 0x44) = pz;
			//技能面向float
			*(float*)(Buf + 0x54) = AngleX;
			*(float*)(Buf + 0x58) = AngleY;
			//技能
			*(BYTE*)(Buf + 0xA0) = 1;
			*(BYTE*)(Buf + 0xA4) = 1;//A0 和 A4 要相同
			*(BYTE*)(Buf + 0xDC) = 1;
			*(int*)(Buf + 0x10C) = -1;
			*(DWORD*)(Buf + 0x114) = dwSkillID;
			*(DWORD*)(Buf + 0x118) = -1;//技能等级 0 就行
			MainUniversalCALL4(dwEcx, (ULONG64)Buf, 0, 0, 游戏模块 + gc_UseSkillCall);
			//ResetArgs();
			//MyRcx = dwEcx;
			//MyRdx = (ULONG64)Buf;
			//MyR8 = 0;
			//MyAsmCall = UseSkillCall;
			//DoCall();//使用技能
		}
	
}