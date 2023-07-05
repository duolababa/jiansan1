#include "内存_能力刻印相关.h"
INT64 Fun_getAbilityResAddr(DWORD dResId, DWORD dLev)// dTargetIndex  从0开始
{
	INT64 dCall = 游戏模块 + gc_getAbilityResAddr;
	INT64 dRCX = R_QW(游戏模块 + gb_ResBase);
	UCHAR dRetAddr[0x200] = { 0 };
	MainUniversalCALL6(dRCX, (ULONG_PTR)dRetAddr, dResId, dLev, 0, 0, dCall);
	INT64 dRet = 0;
	dRet = R_QW((ULONG_PTR)dRetAddr);
	return dRet;
	/*wchar_t buf[100];
	dm.AsmClear();
	dm.AsmAdd(L"sub rsp,40");
	dm.AsmAdd(L"xor esi, esi");
	dm.AsmAdd(L"mov dword ptr ds:[rsp+20],esi");
	wsprintf(buf, L"MOV R9D, %X", dLev);
	dm.AsmAdd(buf);
	wsprintf(buf, L"MOV R8D, %X", dResId);
	dm.AsmAdd(buf);
	wsprintf(buf, L"MOV RDX, 0%I64X", dRetAddr);
	dm.AsmAdd(buf);
	wsprintf(buf, L"MOV RCX, 0%I64X", dRCX);
	dm.AsmAdd(buf);
	wsprintf(buf, L"mov rdi, 0%I64X", dCall);
	dm.AsmAdd(buf);
	dm.AsmAdd(L"call rdi");
	dm.AsmAdd(L"add rsp,40");
	dm.AsmCall( 6);*/

}

void getAbilityListAll(INT64 dListAddr, DWORD dStartOffest, DWORD dArraySize)
{
	long dtotal = R_DW(dListAddr + dStartOffest + 0x10 + 0x18);
	INT64 dKeyAddr = R_QW(dListAddr + dStartOffest + 0x20);
	if (!dKeyAddr)
	{
		dKeyAddr = dListAddr + dStartOffest + 0x10;
	}
	wchar_t aff[500];
	INT64 objStartAddr = R_QW(dListAddr + dStartOffest);
	for (DWORD i = 0; i < dtotal; i++)
	{
		long dKeyValue = R_DW(dKeyAddr + (i / 0x20) * 4);
		DWORD dNum = i % 0x20;
		DWORD dCheck = (dKeyValue >> dNum) & 1;
		if (dCheck)
		{
			DWORD dId = R_DW(objStartAddr + i * dArraySize);
			if (dId && dId != 0xFFFFFFFF)
			{
				INT64 dObj = R_QW(objStartAddr + i * dArraySize + 4);
				if (dObj)
				{
					INT64 dLevStart = dObj;
					INT64 dLevTotal = R_DW(objStartAddr + i * dArraySize + 4 + 8);
					for (DWORD j = 0; j < dLevTotal; j++)
					{
						if (R_DW(dLevStart + j * 0x1C))
						{
							INT64 dAbilityAttrObj = R_QW(dLevStart + j * 0x1C + 4);
							BYTE dType = R_BYTE(dAbilityAttrObj + 0x14);//类型1 战斗效果 类型2 职业效果
							WORD dJobId = R_W(dAbilityAttrObj + 0x16);//类型2 才判断这
							INT64 dResAddr = Fun_getAbilityResAddr(dId, 1);
							if (dResAddr)
							{
								INT64 dNameAddr = R_QW(dResAddr + 0x20);
								CString csName = L"空";
								if (dNameAddr)
								{
									csName = R_CString(dNameAddr);
								}
								MyTrace(L"地址0x%I64X ID%X 类型%d 职业id%X %s\r\n", dAbilityAttrObj, dId, dType, dJobId, csName);
							}
							break;
						}
					}
				}
			}
		}
	}
}
void 能力刻印::getAbilityEngraveAll()//资源获取所有刻印 类型 职业
{
	DWORD dAbilityEngraveIndex = getResIndexByName(L"AbilityEngrave");
	INT64 dAbilityEngraveAddr = getResAddrById(dAbilityEngraveIndex);
	MyTrace(L"地址0x%I64X \r\n", dAbilityEngraveAddr);
	getAbilityListAll(dAbilityEngraveAddr, 0x20, 0x54);
}


int 能力刻印::getEngraveDragLevById(int dEngraveId)//获取已经解锁刻印等级
{
	INT64 addr_1 = R_QW(游戏模块 + gb_EngraveList);
	INT64 addr_2 = addr_1 + go_EngraveListStart - 0x44;
	long dtotal = R_DW(addr_2 + 0x44);
	INT64 objStartAddr = R_QW(addr_2);
	INT64 indexStartAddr = R_QW(addr_2 + 0x3C);
	for (size_t i = 0; i < dtotal; i++)
	{
		long dIndex = R_DW(indexStartAddr + i * 4);
		if (dIndex != 0xFFFFFFFF)
		{
			long dOffest = dIndex * 5 * 4;
			if (dEngraveId == R_DW(objStartAddr + dOffest))
			{
				return R_BYTE(objStartAddr + dOffest + 4);
			}
			DWORD dNextIndex = 0;
			while (1)
			{
				dNextIndex = R_DW(objStartAddr + dOffest + 0xC);
				if (dNextIndex == 0xFFFFFFFF)//为-1跳出循环
				{
					break;
				}
				else
				{
					dOffest = dNextIndex * 5 * 4;
					if (dEngraveId == R_DW(objStartAddr + dOffest))
					{
						return R_BYTE(objStartAddr + dOffest + 4);
					}
				}
			}
		}
	}
	return 0;
}
void 能力刻印::Fun_EngraveDrag(int dEngraveId, int dPos)//设置刻印 位置分别为0和1
{
	int dLev = getEngraveDragLevById(dEngraveId);
	if (dLev)
	{
		INT64 dRcx = R_QW(游戏模块 + gb_ShortKey);
		MainUniversalCALL4(dRcx, dPos, dEngraveId, dLev, 游戏模块 + gc_EngraveDrag);
		/*	wchar_t buf[100];
			dm.AsmClear();
			dm.AsmAdd(L"sub rsp,40");
			wsprintf(buf, L"mov r9d, 0%X", dLev);
			dm.AsmAdd(buf);
			wsprintf(buf, L"mov r8d, 0%X", dEngraveId);
			dm.AsmAdd(buf);
			wsprintf(buf, L"mov edx, 0%X", dPos);
			dm.AsmAdd(buf);
			wsprintf(buf, L"mov rcx, 0%I64X", dRcx);
			dm.AsmAdd(buf);
			wsprintf(buf, L"mov rdi, 0%I64X", gc_EngraveDrag);
			dm.AsmAdd(buf);
			dm.AsmAdd(L"call rdi");
			dm.AsmAdd(L"add rsp,040");
			dm.AsmCall( 6);*/
	}
}



void Fun_marbleWndItemSelect(int dIndex)//索引从0开始
{
	INT64 dUiObj = UI功能::getUiObjById(0x21);
	DWORD dShow = R_DW(dUiObj + 0x27C);
	if (dShow)
	{
		int dCurSelIndex = R_DW(dUiObj + go_marbleWndItemCurSel);
		if (dCurSelIndex != dIndex)
		{
			MainUniversalCALL2(dUiObj, dIndex, 游戏模块 + gc_marbleWndItemSelect);
			/*wchar_t buf[100];
			dm.AsmClear();
			dm.AsmAdd(L"sub rsp,040");
			wsprintf(buf, L"MOV EDX, 0%X", dIndex);
			dm.AsmAdd(buf);
			wsprintf(buf, L"MOV RCX, 0%I64X", dUiObj);
			dm.AsmAdd(buf);
			wsprintf(buf, L"MOV RDI, 0%I64X", gc_marbleWndItemSelect);
			dm.AsmAdd(buf);
			dm.AsmAdd(L"call rdi");
			dm.AsmAdd(L"add rsp,040");
			dm.AsmCall(6);*/
		}
	}

}

void Fun_marbleWndItemStartBtn(int dIndex)//能力属性索引 从0开始
{
	if (dIndex > 2)   return;
	INT64 dUiObj = UI功能::getUiObjById(0x21);
	DWORD dShow = R_DW(dUiObj + 0x27C);
	if (dShow)
	{
		int dCurSelIndex = R_DW(dUiObj + go_marbleWndItemCurSel);
		if (dCurSelIndex != dIndex)
		{
			MainUniversalCALL4(dUiObj, dIndex, 1, 0, 游戏模块 + gc_marbleWndItemStartBtn);
			/*wchar_t buf[100];
			dm.AsmClear();
			dm.AsmAdd(L"sub rsp,040");
			wsprintf(buf, L"MOV R8D, 0%X", 1);
			dm.AsmAdd(buf);
			wsprintf(buf, L"MOV EDX, 0%X", dIndex);
			dm.AsmAdd(buf);
			wsprintf(buf, L"MOV RCX, 0%I64X", dUiObj);
			dm.AsmAdd(buf);
			wsprintf(buf, L"MOV RDI, 0%I64X", gc_marbleWndItemStartBtn);
			dm.AsmAdd(buf);
			dm.AsmAdd(L"call rdi");
			dm.AsmAdd(L"add rsp,040");
			dm.AsmCall(6);*/
		}
	}
}
//E8 ? ? ? ? ? ? ? ? ? ? ? ? 8B ? ? ? ? ? ? ? ? ? ? ? ? 85 ? ? 0F ? ? ? ? ? ? ? ? ? ? 80 ? ? ? ? ? ? ? ? ? ? ? ? 0F ? ? ? ? ? ? ? ? ? ? ? ? 83 第一行 gc_getAbilityResAddr
//INT64 Fun_getAbilityResAddr( DWORD dResId, DWORD dLev)// dTargetIndex  从0开始
//{
//	INT64 dCall = 游戏模块+gc_getAbilityResAddr;
//	INT64 dRCX = R_QW(游戏模块 + gb_ResBase);
//	//INT64 dRetAddr = dm.VirtualAllocEx(0, 0x100, 0);
//	UCHAR pBuff[0x100] = { 0 };
//	CALL6(dRCX, ULONG_PTR(pBuff), dResId, dLev, 0, 0, dCall);
//	/*INT64 dRet = 0;
//	wchar_t buf[100];
//	dm.AsmClear();
//	dm.AsmAdd(L"sub rsp,40");
//	dm.AsmAdd(L"xor esi, esi");
//	dm.AsmAdd(L"mov dword ptr ds:[rsp+20],esi");
//	wsprintf(buf, L"MOV R9D, %X", dLev);
//	dm.AsmAdd(buf);
//	wsprintf(buf, L"MOV R8D, %X", dResId);
//	dm.AsmAdd(buf);
//	wsprintf(buf, L"MOV RDX, 0%I64X", dRetAddr);
//	dm.AsmAdd(buf);
//	wsprintf(buf, L"MOV RCX, 0%I64X", dRCX);
//	dm.AsmAdd(buf);
//	wsprintf(buf, L"mov rdi, 0%I64X", dCall);
//	dm.AsmAdd(buf);
//	dm.AsmAdd(L"call rdi");
//	dm.AsmAdd(L"add rsp,40");
//	dm.AsmCall(6);*/
//	INT64 dRet =R_QW(ULONG_PTR(pBuff));
//	return dRet;
//}

CString getAbilityNameById(DWORD dAbilityId)
{
	CString csName = L"空";
	INT64 dResAddr = Fun_getAbilityResAddr(dAbilityId, 1);
	if (dResAddr)
	{
		INT64 dNameAddr = R_QW(dResAddr + 0x20);

		if (dNameAddr)
		{
			csName = R_CString(dNameAddr);
		}
	}
	return csName;
}
void getItemAbilityList(INT64 dItemObj)
{

	int dSuccNum = 0;//成功次数
	WORD dtotal = R_W(dItemObj + go_ItemAbilityTotal);//读双字节
	INT64 dstart = dItemObj + go_ItemAbilityStartAddr + go_ItemAbilityStartOffset;
	for (int i = 0; i < dtotal && i < 3; i++)
	{
		WORD dtotalNum = R_W(dstart + i * 0x10);//读双字节 总共强化次数
		DWORD dAbilityId = R_DW(dstart + 2 - go_ItemAbilityId + i * 0x10);
		for (int j = 0; j < dtotalNum && j < 10; j++)
		{
			BYTE dstate = R_BYTE(dstart + 2 + i * 0x10 + j);//读字节 0未加工 1 加工成功 2加工失败
			CString Name = getAbilityNameById(dAbilityId);
			if (dstate == 1)
			{
				dSuccNum++;
				MyTrace(L"%s 总次数%d 第%d次状态值%d\r\n", Name, dtotalNum, j, dstate);
			}
			if (dstate == 0)
			{
				MyTrace(L"%d 强化 %s 能力[%d]", dAbilityId, Name, j);
				Fun_marbleWndItemStartBtn(j);
				Sleep(1000);
			}
			else
			{
				MyTrace(L"%s 总次数%d 第%d次状态值%d\r\n", Name, dtotalNum, j, dstate);
			}

		}

	}
	MyTrace(L"最终加成成功次数 %d\r\n", dSuccNum);
}

void 诞生石::getmarbleWndItemList()
{
	INT64 dUiObj = UI功能::getUiObjById(0x21);//root1.arkui.windowCanvas.marbleWnd 
	int dtotal = R_DW(dUiObj + go_marbleWndItemListTotal);
	INT64 dstart = R_QW(dUiObj + go_marbleWndItemListTotal - 8);
	for (int i = 0; i < dtotal; i++)
	{
		INT64 dItemObj = dstart + i * go_marbleWndItemListSize;
		INT64 dItemSrvId = R_QW(dItemObj + go_marbleWndItemSrvId);
		BYTE dItemCntrType = R_BYTE(dItemObj + go_marbleWndItemCntrType);//读双字节 0XE是仓库 背包是0
		MyTrace(L"0%I64X 0%I64X 容器类型%X\r\n", dItemObj, dItemSrvId, dItemCntrType);
		if (dItemCntrType == 0)
		{
			Fun_marbleWndItemSelect(i);
			getItemAbilityList(dItemObj);
			break;
		}
	}


}
bool 诞生石::诞生石强化()
{
	INT64 dUiObj = UI功能::getUiObjById(0x21);//root1.arkui.windowCanvas.marbleWnd 
	int dtotal = R_DW(dUiObj + go_marbleWndItemListTotal);
	INT64 dstart = R_QW(dUiObj + go_marbleWndItemListTotal - 8);
	for (int i = 0; i < dtotal; i++)
	{
		INT64 dItemObj = dstart + i * go_marbleWndItemListSize;
		INT64 dItemSrvId = R_QW(dItemObj + go_marbleWndItemSrvId);
		BYTE dItemCntrType = R_BYTE(dItemObj + go_marbleWndItemCntrType);//读双字节 0XE是仓库 背包是0
		if (dItemCntrType == 0)
		{
			Fun_marbleWndItemSelect(i);
			getItemAbilityList(dItemObj);
			return true;
		}

	}
	return false;
}



INT64 研磨::getItemBuildUpItemList()//物品遍历
{
	INT64 go_ItemBuildUpItemResId = 偏移_背包_物品resid;//0x6A4;
	//3C 05 74 ?? 3C 06 75 ?? 8B   +8+2 go_ItemBuildUpItemResId
	INT64 go_ItemBuildUpItmeSrvId = 偏移_背包_物品id;//0x690;
	//?? 8B ?? FF ?? ?? ?? 8B ?? ?? ?? ?? ?? ?? 8B ?? B2 ?? E8 ?? ?? ?? ?? ?? 8B ?? ?? 85 ?? 74 ?? ?? 8B   +0x1F+3  go_ItemBuildUpItmeSrvId
	//INT64 go_ItemGradeLev = 偏移_背包_物品强化等级;//0x6A8;
	//0F ?? ?? ?? ?? ?? 0F ?? ?? ?? ?? ?? ?? 3C ?? 0F ?? ?? ?? ?? ?? ?? 85 ?? 0F ?? ?? ?? ?? ?? ?? 8B ?? E8 ?? ?? ?? ?? 0F   +0x21 的CALL进去第一行  go_ItemGradeLev
	INT64 dUiAddr = UI功能::getUiObjById(0x12C);//&"root1.arkui.windowCanvas.itemBuildUpWnd"
	if (dUiAddr)
	{
		INT64 dstart = R_QW(dUiAddr + go_ItemBuildListStart);
		int dtotal = R_DW(dUiAddr + go_ItemBuildListStart + 8);
		for (int i = 0; i < dtotal; i++)
		{
			int dIndex = i;
			INT64 dItemObj = dstart + i * go_ItemBuildListSize;
			BYTE dBagIndex = R_BYTE(dItemObj);
			INT64 dItemSrvId = R_QW(dItemObj + go_ItemBuildUpItmeSrvId + 4);
			DWORD dItemResId = R_DW(dItemObj + go_ItemBuildUpItemResId + 4);
			WORD dItemGradeLev = R_W(dItemObj + go_ItemGradeLev + 0x4) - 100;//当前强化等级，需要减去100
			INT64 dItemResAddr = getItemResAddrById(dItemResId);
			DWORD 物品等阶 = R_W(dItemResAddr + 偏移_背包_物品等级);
			DWORD dSlotIndex = R_DW(dItemResAddr + 0x114);
			DWORD WearId = getEquipWearArg(dSlotIndex);
			INT64 dNameAddr = R_QW(dItemResAddr + 0x10);
			CString csName = L"空";
			if (dNameAddr)
			{
				csName = R_CString(dNameAddr);
			}
			MyTrace(L"地址0%I64X 索引%X 0%I64X 资源ID0%X 装备位置 %d 物品等阶 %d 等级%d %s", dItemObj, dBagIndex, dItemSrvId, dItemResId, WearId, 物品等阶, dItemGradeLev, csName);
		}
	}
	return 0;
}

///CALL 

void Fun_ItemBuildUpListSelect(int dIndex)//选择需要强化物品 索引从0开始
{
	INT64 dUiAddr = UI功能::getUiObjById(0x12C);//&"root1.arkui.windowCanvas.itemBuildUpWnd"
	if (dUiAddr)
	{
		int dShow = R_DW(dUiAddr + 0x27C);
		if (dShow)
		{
			INT64 dItemListAddr = R_QW(dUiAddr + go_ItemBuildUpSelect);
			INT64 addr_1 = R_QW(dItemListAddr + 0x18);
			INT64 addr_2 = R_QW(addr_1 + 0x70);
			W_DW(addr_2 + 0x318, dIndex);
			MainUniversalCALL2(dUiAddr, 0, 游戏模块 + gc_ItemBuildUpListSelectIndex);

			/*CString cBuf;
			dm.AsmClear();
			dm.AsmAdd(MyFormat(cBuf, L"mov rcx, 0%I64X", dUiAddr));
			dm.AsmAdd(MyFormat(cBuf, L"mov rdi, 0%I64X", gc_ItemBuildUpListSelectIndex));
			dm.AsmAdd(L"sub rsp,040");
			dm.AsmAdd(L"call rdi");
			dm.AsmAdd(L"add rsp,040");
			dm.AsmCall( 6);*/
		}
	}
}


BOOL bCheckItemBuildUpLevelWndContentChildWindowShow(DWORD dChildIndex)
{
	INT64 dUiAddr = UI功能::getUiObjById(0x12C);//&"root1.arkui.windowCanvas.itemBuildUpWnd"
	if (dUiAddr)
	{
		int dShow = R_DW(dUiAddr + 0x27C);
		if (dShow)
		{
			INT64 addr_first = getUiFirstAddr(dUiAddr);
			INT64 addr_1 = getChildUiAddrByStr(addr_first, L"ItemBuildUpLevelWndContent");
			INT64 addr_2 = getChildUiAddrByStr(addr_1, L"childWindow");
			DWORD dChildWindow = R_W(addr_2 + 0x6A);
			if (dChildWindow >> 0xe == 1)//判断显示
			{
				INT64 dUiDataAddr = R_QW(addr_2 + 0x150);
				if (dUiDataAddr)
				{
					if (R_DW(dUiDataAddr + 0x2F8) == dChildIndex)
					{
						return TRUE;
					}
				}
			}
		}
	}
	return FALSE;
}

void Fun_ItemBuildUpLevelUp()
{
	INT64 dUiAddr = UI功能::getUiObjById(0x12C);//&"root1.arkui.windowCanvas.itemBuildUpWnd"
	if (dUiAddr)
	{
		int dShow = R_DW(dUiAddr + 0x27C);
		if (dShow)
		{
			if (!bCheckItemBuildUpLevelWndContentChildWindowShow(0))//0参数是成长子窗口
			{
				MainUniversalCALL2(dUiAddr, 0, 游戏模块 + gc_ItemBuildUpLevelUp);
				/*CString cBuf;
				dm.AsmClear();
				dm.AsmAdd(MyFormat(cBuf, L"mov rcx, 0%I64X", dUiAddr));
				dm.AsmAdd(MyFormat(cBuf, L"mov rdi, 0%I64X", gc_ItemBuildUpLevelUp));
				dm.AsmAdd(L"sub rsp,040");
				dm.AsmAdd(L"call rdi");
				dm.AsmAdd(L"add rsp,040");
				dm.AsmCall( 6);*/
			}
		}
	}
}

void Fun_ItemBuildUpChildMaxClick()
{
	INT64 dUiAddr = UI功能::getUiObjById(0x12C);//&"root1.arkui.windowCanvas.itemBuildUpWnd"
	if (dUiAddr)
	{
		int dShow = R_DW(dUiAddr + 0x27C);
		if (dShow)
		{
			INT64 dEnhanceInfo = R_QW(dUiAddr + go_ItemBuildCurItemSrvId - 0x18);
			MainUniversalCALL4(dEnhanceInfo, 0, 0, 0, 游戏模块 + gc_ItemBuildUpMaxBtn);
			/*CString cBuf;
			dm.AsmClear();
			dm.AsmAdd(MyFormat(cBuf, L"MOV RCX, 0%I64X", dEnhanceInfo));
			dm.AsmAdd(MyFormat(cBuf, L"mov rdi, 0%I64X", gc_ItemBuildUpMaxBtn));
			dm.AsmAdd(L"mov r8, 0");
			dm.AsmAdd(L"mov r9, 0");
			dm.AsmAdd(L"sub rsp,040");
			dm.AsmAdd(L"call rdi");
			dm.AsmAdd(L"add rsp,040");
			dm.AsmCall( 6);*/
		}
	}
}
void Fun_ItemBuildUpChildLevelUpBtnClick()
{
	INT64 dUiAddr = UI功能::getUiObjById(0x12C);//&"root1.arkui.windowCanvas.itemBuildUpWnd"
	if (dUiAddr)
	{
		int dShow = R_DW(dUiAddr + 0x27C);
		if (dShow)
		{
			INT64 dEnhanceInfo = R_QW(dUiAddr + go_ItemBuildCurItemSrvId - 0x18);
			INT64 dCurExp = R_QW(dEnhanceInfo + go_ItemBuildUpCurExp);
			INT64 dMaxExp = R_QW(dEnhanceInfo + go_ItemBuildUpCurExp + 8);
			if (dMaxExp)
			{
				if (dMaxExp > dCurExp)//判断经验值
				{
					MainUniversalCALL2(dEnhanceInfo, 0, 游戏模块 + gc_ItemBuildUpChildLevelUpBtn);
					/*CString cBuf;
					dm.AsmClear();
					dm.AsmAdd(MyFormat(cBuf, L"mov rcx, 0%I64X", dEnhanceInfo));
					dm.AsmAdd(MyFormat(cBuf, L"mov rdi, 0%I64X", gc_ItemBuildUpChildLevelUpBtn));
					dm.AsmAdd(L"sub rsp,040");
					dm.AsmAdd(L"call rdi");
					dm.AsmAdd(L"add rsp,040");
					dm.AsmCall( 6);*/

				}

			}
		}
	}
}

void Fun_ItemBuildUpLevelUpGrade()
{
	INT64 dUiAddr = UI功能::getUiObjById(0x12C);//&"root1.arkui.windowCanvas.itemBuildUpWnd"
	if (dUiAddr)
	{
		int dShow = R_DW(dUiAddr + 0x27C);
		if (dShow)
		{
			if (!bCheckItemBuildUpLevelWndContentChildWindowShow(1))
			{
				MainUniversalCALL2(dUiAddr, 0, 游戏模块 + gc_ItemBuildUpLevelUpGrade);
				/*CString cBuf;
				dm.AsmClear();
				dm.AsmAdd(MyFormat(cBuf, L"mov rcx, 0%I64X", dUiAddr));
				dm.AsmAdd(MyFormat(cBuf, L"mov rdi, 0%I64X", gc_ItemBuildUpLevelUpGrade));
				dm.AsmAdd(L"sub rsp,040");
				dm.AsmAdd(L"call rdi");
				dm.AsmAdd(L"add rsp,040");
				dm.AsmCall( 6);*/
			}
		}
	}
}

void Fun_ItemBuildUpChildLevelUpGradeBtnClick()//子窗口强化按钮点击
{
	INT64 dUiAddr = UI功能::getUiObjById(0x12C);//&"root1.arkui.windowCanvas.itemBuildUpWnd"
	if (dUiAddr)
	{
		int dShow = R_DW(dUiAddr + 0x27C);
		if (dShow)
		{
			INT64 dEnhanceInfo = R_QW(dUiAddr + go_ItemBuildCurItemSrvId - 0x10);
			MainUniversalCALL2(dEnhanceInfo, 0, 游戏模块 + gc_ItemBuildUpChildLevelUpGradeBtn);
			/*wchar_t buf[100];
			CString cBuf;
			dm.AsmAdd(MyFormat(cBuf, L"mov rcx, 0%I64X", dEnhanceInfo));
			dm.AsmAdd(MyFormat(cBuf, L"mov rdi, 0%I64X", gc_ItemBuildUpChildLevelUpGradeBtn));
			dm.AsmAdd(L"sub rsp,040");
			dm.AsmAdd(L"call rdi");
			dm.AsmAdd(L"add rsp,040");
			dm.AsmCall( 6);*/

		}
	}
}

BOOL bCheckitemBuildUpRenderTargetGroupShow()//判断最终成功窗口
{
	INT64 dUiAddr = UI功能::getUiObjById(0x12C);//&"root1.arkui.windowCanvas.itemBuildUpWnd"
	if (dUiAddr)
	{
		int dShow = R_DW(dUiAddr + 0x27C);
		if (dShow)
		{
			INT64 addr_first = getUiFirstAddr(dUiAddr);
			INT64 addr_1 = getChildUiAddrByStr(addr_first, L"ItemBuildUpLevelWndContent");
			INT64 addr_2 = getChildUiAddrByStr(addr_1, L"itemBuildUpRenderTargetGroup");
			DWORD dChildWindow = R_W(addr_2 + 0x6A);
			if (dChildWindow >> 0xe == 1)//判断显示
			{
				return TRUE;
			}
		}
	}
	return FALSE;
}


void Fun_ItemBuildLevUpResult()
{

	INT64 dUiAddr = UI功能::getUiObjById(0x12C);//&"root1.arkui.windowCanvas.itemBuildUpWnd"
	if (dUiAddr)
	{
		int dShow = R_DW(dUiAddr + 0x27C);
		if (dShow)
		{
			if (bCheckitemBuildUpRenderTargetGroupShow())
			{
				MainUniversalCALL2(dUiAddr, 0, 游戏模块 + gc_ItemBuildLevUpResult);
				/*CString cBuf;
				dm.AsmClear();
				dm.AsmAdd(MyFormat(cBuf, L"mov rcx, 0%I64X", dUiAddr));
				dm.AsmAdd(MyFormat(cBuf, L"mov rdi, 0%I64X", gc_ItemBuildLevUpResult));
				dm.AsmAdd(L"sub rsp,040");
				dm.AsmAdd(L"call rdi");
				dm.AsmAdd(L"add rsp,040");
				dm.AsmCall( 6);*/
			}

		}

	}
}


void Fun_ItemBuildLevUpSucess()//放在Fun_ItemBuildLevUpResult 后调用 中间加点延迟5000
{

	INT64 dUiAddr = UI功能::getUiObjById(0x12C);//&"root1.arkui.windowCanvas.itemBuildUpWnd"
	if (dUiAddr)
	{
		int dShow = R_DW(dUiAddr + 0x27C);
		if (dShow)
		{
			if (bCheckitemBuildUpRenderTargetGroupShow())
			{
				MainUniversalCALL2(dUiAddr, 0, 游戏模块 + gc_ItemBuildLevUpSucess);
				/*CString cBuf;
				dm.AsmClear();
				dm.AsmAdd(MyFormat(cBuf, L"mov rcx, 0%I64X", dUiAddr));
				dm.AsmAdd(MyFormat(cBuf, L"mov rdi, 0%I64X", gc_ItemBuildLevUpSucess));
				dm.AsmAdd(L"sub rsp,040");
				dm.AsmAdd(L"call rdi");
				dm.AsmAdd(L"add rsp,040");
				dm.AsmCall( 6);*/
			}

		}

	}
}
bool Fun_石头是否加工完成(INT64 ItemObj)
{
	if (ItemObj)
	{
		INT64 rcxx = R_QW(游戏模块 + gb_AttrList);
		DWORD ret = CALL2(rcxx, ItemObj, 游戏模块 + gc_CheckAbilityStone);
		if (ret != 0)
		{
			return true;
		}
	}
	return false;
}

void 强化302装备()
{


}