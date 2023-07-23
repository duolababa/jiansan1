#include "内存_周常任务.h"
int 周常任务::getUnasTaskPoint()//每周远征积分
{
	INT64 addr_1 =R_QW(游戏模块+gb_UnasTask);
	WORD dWeekPoints =R_W(addr_1 + go_UnasTaskWeekPoint);
	WORD dDayPoints =R_W(addr_1 + go_UnasTaskDayPoint);
	return dWeekPoints + dDayPoints;
}

BOOL 周常任务::CheckQuestInProgress(int dQuestId)
{
	INT64 addr_1 =R_QW(游戏模块+gb_QuestCur);
	long dtotal =R_DW(addr_1 + 0xA8 + 0x10 + 0x18);//更新-0220
	INT64 dKeyAddr =R_QW(addr_1 + 0xA8 + 0x20);//更新-0220
	if (!dKeyAddr)
	{
		dKeyAddr = addr_1 + 0xA8 + 0x10;//更新-0220
	}
	long dKeyValue =R_DW(addr_1 + 0xA8 + 0x10);//更新-0220
	INT64 objStartAddr =R_QW(addr_1 + 0xA8);//更新-0220
	for (DWORD i = 0; i < dtotal; i++)
	{
		long dKeyValue =R_DW(dKeyAddr + (i / 0x20) * 4);
		DWORD dNum = i % 0x20;
		DWORD dCheck = (dKeyValue >> dNum) & 1;
		if (dCheck)
		{
			DWORD dQuesId =R_DW(objStartAddr + i * 0x5 * 4);
			if (dQuestId ==R_DW(objStartAddr + i * 0x5 * 4))
			{
				return TRUE;
			}
		}
	}
	return FALSE;
}

BOOL 周常任务::Fun_CheckUnasWeeklyQuestCon(int dQuestId)
{
	INT64 addr_1 =R_QW(游戏模块+gb_QuestCur);
	return (BOOL)CALL2(addr_1, dQuestId, 游戏模块 + gc_CheckUnasWeeklyQuestCon);
	/*wchar_t buf[100];
	dm.AsmClear();
	dm.AsmAdd(L"sub rsp,40");
	wsprintf(buf, L"MOV EDX, 0%X", dQuestId);
	dm.AsmAdd(buf);
	wsprintf(buf, L"MOV RCX, 0%I64X", addr_1);
	dm.AsmAdd(buf);
	wsprintf(buf, L"mov rdi, 0%I64X", gc_CheckUnasWeeklyQuestCon);
	dm.AsmAdd(buf);
	dm.AsmAdd(L"call rdi");
	dm.AsmAdd(L"add rsp,040");*/
	//return (BOOL)dm.AsmCall(HwndGlobal, 6);
}

INT64 周常任务::Fun_getQuestrResAddrById(int dQuestId)
{
	INT64 addr_1 = R_QW(游戏模块 + gb_QuestCur);
	INT64 dCall = R_QW(addr_1);
	dCall = R_QW(dCall + 0x40);
	//INT64 dRetAddr = dm.VirtualAllocEx(HwndGlobal, 0, 0x100, 0);
	UCHAR BUFF[0x100] = { 0 };
	MainUniversalCALL6(addr_1, 0x12D, dQuestId, (ULONG_PTR)BUFF, 0, 0, dCall);
	INT64 dResAddr = 0;
	//wchar_t buf[100];
	//dm.AsmClear();
	//dm.AsmAdd(L"sub rsp,40");
	//dm.AsmAdd(L"emit 48 C7 44 24 20 00 00 00 00");//mov qword ptr ss:[rsp+0x20], 0x0
	//memset(buf, 0, 200);
	//wsprintf(buf, L"MOV R9, 0%I64X", dRetAddr);
	//dm.AsmAdd(buf);
	//wsprintf(buf, L"MOV R8D, 0%X", dQuestId);
	//dm.AsmAdd(buf);
	//wsprintf(buf, L"MOV EDX, 0%X", 0x12C);
	//dm.AsmAdd(buf);
	//wsprintf(buf, L"MOV RCX, 0%I64X", addr_1);
	//dm.AsmAdd(buf);
	//wsprintf(buf, L"mov rdi, 0%I64X", dCall);
	//dm.AsmAdd(buf);
	//dm.AsmAdd(L"call rdi");
	//dm.AsmAdd(L"add rsp,040");
	//dm.AsmCall(HwndGlobal, 6);
	dResAddr = R_QW((INT64)&BUFF);
	return dResAddr;
}
//DE root1.arkui.windowCanvas.periodQuestNoticeBoardWnd 

void 周常任务::get_UnasDailyQuestList(vector<周长日常_>& 日常)//遍历日常任务 那个可接 那个不可接
{
	周长日常_ temp;
	日常.clear();
	INT64 addr_1 =R_QW(游戏模块+gb_UnasTask);
	addr_1 = addr_1 + go_UnasWeeklyQuestStart + 0x48;
	long dtotal =R_DW(addr_1 + 0x10 + 0x18);
	INT64 dKeyAddr =R_QW(addr_1 + 0x20);
	if (!dKeyAddr)
	{
		dKeyAddr = addr_1 + 0x10;
	}
	long dKeyValue =R_DW(addr_1 + 0x10);
	INT64 objStartAddr =R_QW(addr_1);
	for (int i = 0; i < dtotal; i++)
	{
		long dKeyValue =R_DW(dKeyAddr + (i / 0x20) * 4);
		int dNum = i % 0x20;
		int dCheck = (dKeyValue >> dNum) & 1;
		if (dCheck)
		{
			int dQuestId =R_DW(objStartAddr + i * 0x14);
			INT64 dObj =R_QW(objStartAddr + i * 0x14 + 4);
			//INT64 dQuestResAddr = Fun_getQuestrResAddrById( dQuestId);
			//INT64 dQuestNameAddr = R_QW(dQuestResAddr + 0xC);
			INT64 dQuestResAddr = getQuestResAddrById( dQuestId);
			//MyTrace(L"0x%llx", dQuestResAddr);
			INT64 dInfoAddr = R_QW(dQuestResAddr + 0x3C);
			INT64 dNameAddr = R_QW(dInfoAddr + 0x34);
			DWORD dStrLen = R_DW(dInfoAddr + 0x34 + 8) - 1;
			INT64 dRealNameAddr = getStringAddr(0, dNameAddr, dStrLen);
			CString cQuestName = R_CString(dRealNameAddr);
			//CString cQuestName = R_CString(dRealNameAddr);
			BOOL isQuestProgress = CheckQuestInProgress( dQuestId);//任务已接
		
			
			BOOL bState =R_DW(dObj + go_UnasWeeklyQuestState);
			BOOL isQuestCon = Fun_CheckUnasWeeklyQuestCon( dQuestId);

			temp.ID = dQuestId;
			temp.csName = cQuestName;


			if (isQuestProgress)//已接
			{
				temp.状态 = 1;
			//	MyTrace(L"0%I64X  进行中任务 ID %d<0x%X>  %s", dObj, dQuestId, dQuestId, cQuestName);
			}
			else
			{
				if (bState)
				{
					temp.状态 = 2;
					//	MyTrace(L"0%I64X  可接任务 ID %d<0x%X>  %s", dObj, dQuestId, dQuestId, cQuestName);
				}
				else
				{
					if (isQuestCon)
					{
						temp.状态 = 3;
						//	MyTrace(L"0%I64X  已完成任务 ID %d<0x%X>  %s", dObj, dQuestId, dQuestId, cQuestName);
					}
					else
					{
						temp.状态 = 0;
						//	MyTrace(L"0%I64X  不符合条件未显示任务 ID %d<0x%X>  %s", dObj, dQuestId, dQuestId, cQuestName);
					}
				}
			}
			日常.push_back(temp);


		}
	}
}


void 周常任务::get_UnasWeeklyQuesList(vector<周长日常_>& 日常)////遍历周常任务 那个可接 那个不可接
{
	周长日常_ temp;
	日常.clear();
	INT64 addr_1 =R_QW(游戏模块+gb_UnasTask);
	addr_1 = addr_1 + go_UnasWeeklyQuestStart;
	long dtotal =R_DW(addr_1 + 0x10 + 0x18);
	INT64 dKeyAddr =R_QW(addr_1 + 0x20);
	if (!dKeyAddr)
	{
		dKeyAddr = addr_1 + 0x10;
	}
	long dKeyValue =R_DW(addr_1 + 0x10);
	INT64 objStartAddr =R_QW(addr_1);
	for (int i = 0; i < dtotal; i++)
	{
		long dKeyValue =R_DW(dKeyAddr + (i / 0x20) * 4);
		int dNum = i % 0x20;
		int dCheck = (dKeyValue >> dNum) & 1;
		if (dCheck)
		{
			int dQuestId =R_QW(objStartAddr + i * 0x14);
			INT64 dObj =R_QW(objStartAddr + i * 0x14 + 4);
			//INT64 dQuestResAddr = Fun_getQuestrResAddrById( dQuestId);
			BOOL isQuestProgress = CheckQuestInProgress( dQuestId);//任务已接
			//INT64 dQuestNameAddr =R_QW(dQuestResAddr + 0xC);
			//CString cQuestName = R_CString(dQuestNameAddr);
			INT64 dQuestResAddr = getQuestResAddrById(dQuestId);
			//MyTrace(L"0x%llx", dQuestResAddr);
			INT64 dInfoAddr = R_QW(dQuestResAddr + 0x3C);
			INT64 dNameAddr = R_QW(dInfoAddr + 0x34);
			DWORD dStrLen = R_DW(dInfoAddr + 0x34 + 8) - 1;
			INT64 dRealNameAddr = getStringAddr(0, dNameAddr, dStrLen);
			CString cQuestName = R_CString(dRealNameAddr);
			BOOL isQuestCon = Fun_CheckUnasWeeklyQuestCon(dQuestId);
			int dWeeklyQuestType =R_DW(dObj + go_UnasWeeklyQuestType);
			BOOL bState =R_DW(dObj + go_UnasWeeklyQuestState);


			temp.ID = dQuestId;
			temp.csName = cQuestName;
			if (isQuestProgress)//已接
			{
				temp.状态 = 1;
				//	MyTrace(L"0%I64X  进行中任务 ID %d<0x%X>  %s", dObj, dQuestId, dQuestId, cQuestName);
			}
			else
			{
				if (bState)
				{
					temp.状态 = 2;
					//MyTrace(L"0%I64X  可接任务 ID %d<0x%X>  %s", dObj, dQuestId, dQuestId, cQuestName);
				}
				else
				{
					if (isQuestCon)
					{
						temp.状态 = 3;
						//MyTrace(L"0%I64X  已完成任务 ID %d<0x%X>  %s", dObj, dQuestId, dQuestId, cQuestName);
					}
					else
					{
						temp.状态 = 0;
						//	MyTrace(L"0%I64X  不符合条件未显示任务 ID %d<0x%X>  %s", dObj, dQuestId, dQuestId, cQuestName);
					}
				}
			}
			日常.push_back(temp);
		}
	}
}


int 周常任务::周常任务状态(int _dQuestId)//
{
	周长日常_ temp;
	vector<周长日常_>vsk;

	周常任务::get_UnasWeeklyQuesList(vsk);
	for (size_t i = 0; i < vsk.size(); i++)
	{
		if (vsk[i].ID == _dQuestId)
		{
			return vsk[i].状态;
		}

	}

	return 0;
}
void 周常任务::领取徽章()
{
	INT64 addr_1 = R_QW(游戏模块 + gb_UnasTask);
	INT64 call = 游戏模块 + 徽章领取call;

	for (int i = 0; i < 5; i++)
	{
		MainUniversalCALL4(addr_1, i, 0, 0, call);
		Sleep(1500);

	}
}


int 周常任务::周长积分()
{
	INT64 addr_1 = R_QW(游戏模块 + gb_UnasTask);

	DWORD X=R_W(addr_1+0x35A);
	DWORD X1 = R_W(addr_1 + 0x35A-2);


	return X + X1;


}


int 周常任务::日常任务状态(int _dQuestId)//遍历日常任务 那个可接 那个不可接
{
	周长日常_ temp;
	vector<周长日常_>vsk;

	周常任务::get_UnasDailyQuestList(vsk);
	for (size_t i = 0; i < vsk.size(); i++)
	{
		if (vsk[i].ID == _dQuestId)
		{
			return vsk[i].状态;
		}

	}


	return 0;
}

//
//if (*(BYTE*)&szBuf[dwCodeIndex + 0x1] == 0x8B
//	&& *(BYTE*)&szBuf[dwCodeIndex + 0x7] == 0xE8
//	&& *(BYTE*)&szBuf[dwCodeIndex + 0xD] == 0x89
//	&& *(BYTE*)&szBuf[dwCodeIndex + 0x14] == 0x8D
//	&& *(BYTE*)&szBuf[dwCodeIndex + 0x18] == 0x33
//	&& *(BYTE*)&szBuf[dwCodeIndex + 0x1B] == 0x8D
//	&& *(BYTE*)&szBuf[dwCodeIndex + 0x21] == 0xE8
//	&& *(BYTE*)&szBuf[dwCodeIndex + 0x28] == 0x8D)
//{//?? 8B ?? ?? ?? ?? ?? E8 ?? ?? ?? ?? ?? 89 ?? ?? ?? ?? ?? ?? 8D ?? ?? ?? 33 ?? ?? 8D ?? ?? ?? ?? ?? E8 ?? ?? ?? ?? ?? ?? 8D  定位到两处，第一处第一行
//	if (gb_UnasTask) continue;
//	gb_UnasTask = *(INT*)(dwCodeIndex + szBuf + 3 + 0x0) + dwCodeIndex + 0x0 + 3 + 4 + 0x1000 + dModuleBase;
//	wsprintf(aff, L"INT64 gb_UnasTask = 0x%I64X;//代码地址0%I64X\r\n", ScanStringFun(dModuleBase, gb_UnasTask), dwCodeIndex + dStart);
//	temp = *(INT*)(dwCodeIndex + szBuf + 1 + 0x7) + dwCodeIndex + 0x7 + 1 + 4 + (DWORD)szBuf;
//	go_UnasWeeklyQuestStart = *(INT*)(temp + 3);
//	wsprintf(aff, L"INT64 go_UnasWeeklyQuestStart = 0x%I64X;//代码地址0%I64X\r\n", ScanStringFun(dModuleBase, go_UnasWeeklyQuestStart), dwCodeIndex + dStart);
//	str.Insert(str.GetLength(), aff);
//}
//if (*(BYTE*)&szBuf[dwCodeIndex + 0x0] == 0x8B
//	&& *(BYTE*)&szBuf[dwCodeIndex + 0x6] == 0x85
//	&& *(BYTE*)&szBuf[dwCodeIndex + 0x8] == 0x0F
//	&& *(BYTE*)&szBuf[dwCodeIndex + 0xE] == 0x83
//	&& *(BYTE*)&szBuf[dwCodeIndex + 0x11] == 0x75
//	&& *(BYTE*)&szBuf[dwCodeIndex + 0x13] == 0x83
//	&& *(BYTE*)&szBuf[dwCodeIndex + 0x1A] == 0x0F
//	&& *(BYTE*)&szBuf[dwCodeIndex + 0x20] == 0x83)
//{//8B ?? ?? ?? ?? ?? 85 ?? 0F ?? ?? ?? ?? ?? 83 ?? ?? 75 ?? 83 ?? ?? ?? ?? ?? ?? 0F ?? ?? ?? ?? ?? 83
//	go_UnasWeeklyQuestState = *(INT*)(dwCodeIndex + szBuf + 0x13 + 2);
//	wsprintf(aff, L"INT64 go_UnasWeeklyQuestState = 0x%I64X;//代码地址0%I64X\r\n", ScanStringFun(dModuleBase, go_UnasWeeklyQuestState), dwCodeIndex + dStart);
//	str.Insert(str.GetLength(), aff);
//}
//if (*(BYTE*)&szBuf[dwCodeIndex + 0x1] == 0x8B
//	&& *(BYTE*)&szBuf[dwCodeIndex + 0x7] == 0x85
//	&& *(BYTE*)&szBuf[dwCodeIndex + 0x9] == 0x74
//	&& *(BYTE*)&szBuf[dwCodeIndex + 0xB] == 0x83
//	&& *(BYTE*)&szBuf[dwCodeIndex + 0xE] == 0x75
//	&& *(BYTE*)&szBuf[dwCodeIndex + 0x10] == 0x83
//	&& *(BYTE*)&szBuf[dwCodeIndex + 0x17] == 0x0F)
//{//?? 8B ?? ?? ?? ?? ?? 85 ?? 74 ?? 83 ?? ?? 75 ?? 83 ?? ?? ?? ?? ?? ?? 0F
//	go_UnasWeeklyQuestType = *(INT*)(dwCodeIndex + szBuf + 0x10 + 2);
//	wsprintf(aff, L"INT64 go_UnasWeeklyQuestType  = 0x%I64X;//代码地址0%I64X\r\n", ScanStringFun(dModuleBase, go_UnasWeeklyQuestType), dwCodeIndex + dStart);
//	str.Insert(str.GetLength(), aff);
//}
//if (*(BYTE*)&szBuf[dwCodeIndex + 0x0] == 0xE8
//	&& *(BYTE*)&szBuf[dwCodeIndex + 0x5] == 0x0F
//	&& *(BYTE*)&szBuf[dwCodeIndex + 0xC] == 0x0F
//	&& *(BYTE*)&szBuf[dwCodeIndex + 0x13] == 0x03
//	&& *(BYTE*)&szBuf[dwCodeIndex + 0x15] == 0x3B
//	&& *(BYTE*)&szBuf[dwCodeIndex + 0x17] == 0x7F
//	&& *(BYTE*)&szBuf[dwCodeIndex + 0x19] == 0x33
//	&& *(BYTE*)&szBuf[dwCodeIndex + 0x1B] == 0x33
//	&& *(BYTE*)&szBuf[dwCodeIndex + 0x1E] == 0x0F
//	&& *(BYTE*)&szBuf[dwCodeIndex + 0x26] == 0x85)
//{//E8 ?? ?? ?? ?? 0F ?? ?? ?? ?? ?? ?? 0F ?? ?? ?? ?? ?? ?? 03 ?? 3B ?? 7F ?? 33 ?? 33 ?? ?? 0F ?? ?? ?? ?? ?? ?? ?? 85
//	go_UnasTaskWeekPoint = *(INT*)(dwCodeIndex + szBuf + 0x5 + 3);
//	wsprintf(aff, L"INT64 go_UnasTaskWeekPoint = 0x%I64X;//代码地址0%I64X\r\n", ScanStringFun(dModuleBase, go_UnasTaskWeekPoint), dwCodeIndex + dStart);
//	str.Insert(str.GetLength(), aff);
//	go_UnasTaskDayPoint = *(INT*)(dwCodeIndex + szBuf + 0xC + 3);
//	wsprintf(aff, L"INT64 go_UnasTaskDayPoint  = 0x%I64X;//代码地址0%I64X\r\n", ScanStringFun(dModuleBase, go_UnasTaskDayPoint), dwCodeIndex + dStart);
//	str.Insert(str.GetLength(), aff);
//}
//if (*(BYTE*)&szBuf[dwCodeIndex + 0x0] == 0xE8
//	&& *(BYTE*)&szBuf[dwCodeIndex + 0x5] == 0x33
//	&& *(BYTE*)&szBuf[dwCodeIndex + 0x7] == 0x8B
//	&& *(BYTE*)&szBuf[dwCodeIndex + 0x9] == 0x83
//	&& *(BYTE*)&szBuf[dwCodeIndex + 0xC] == 0x75
//	&& *(BYTE*)&szBuf[dwCodeIndex + 0xE] == 0x39
//	&& *(BYTE*)&szBuf[dwCodeIndex + 0x14] == 0x0F
//	&& *(BYTE*)&szBuf[dwCodeIndex + 0x19] == 0x83
//	&& *(BYTE*)&szBuf[dwCodeIndex + 0x1E] == 0x75)
//{//E8 ?? ?? ?? ?? 33 ?? 8B ?? 83 ?? ?? 75 ?? 39 ?? ?? ?? ?? ?? 0F ?? ?? ?? ?? 83 ?? ?? ?? ?? 75
//	gc_CheckUnasWeeklyQuestCon = *(INT*)(dwCodeIndex + szBuf + 1 + 0x0) + dwCodeIndex + 0X0 + 1 + 4 + 0x1000 + dModuleBase;
//	wsprintf(aff, L"INT64 gc_CheckUnasWeeklyQuestCon = 0x%I64X;//代码地址0%I64X\r\n", ScanStringFun(dModuleBase, gc_CheckUnasWeeklyQuestCon), dwCodeIndex + dStart);
//	str.Insert(str.GetLength(), aff);
//}