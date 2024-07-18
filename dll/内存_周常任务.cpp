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
	return (BOOL)MainUniversalCALL2_Ret(addr_1, dQuestId, 游戏模块 + gc_CheckUnasWeeklyQuestCon);
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
	addr_1 = addr_1 + go_UnasWeeklyQuestStart ;
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
			////MyTrace(L"0x%llx", dQuestResAddr);
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

			temp.dObj = dObj;
			if (isQuestProgress)//已接
			{
				temp.状态 = 1;
			//	//MyTrace(L"0%I64X  进行中任务 ID %d<0x%X>  %s", dObj, dQuestId, dQuestId, cQuestName);
			}
			else
			{
				if (bState)
				{
					temp.状态 = 2;
					//	//MyTrace(L"0%I64X  可接任务 ID %d<0x%X>  %s", dObj, dQuestId, dQuestId, cQuestName);
				}
				else
				{
					if (isQuestCon)
					{
						temp.状态 = 3;
						//	//MyTrace(L"0%I64X  已完成任务 ID %d<0x%X>  %s", dObj, dQuestId, dQuestId, cQuestName);
					}
					else
					{
						temp.状态 = 0;
						//	//MyTrace(L"0%I64X  不符合条件未显示任务 ID %d<0x%X>  %s", dObj, dQuestId, dQuestId, cQuestName);
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
	addr_1 = addr_1 + go_UnasWeeklyQuestStart-0x48;
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
			////MyTrace(L"0x%llx", dQuestResAddr);
			INT64 dInfoAddr = R_QW(dQuestResAddr + 0x3C);
			INT64 dNameAddr = R_QW(dInfoAddr + 0x34);
			DWORD dStrLen = R_DW(dInfoAddr + 0x34 + 8) - 1;
			INT64 dRealNameAddr = getStringAddr(0, dNameAddr, dStrLen);
			CString cQuestName = R_CString(dRealNameAddr);
			BOOL isQuestCon = Fun_CheckUnasWeeklyQuestCon(dQuestId);
			int dWeeklyQuestType =R_DW(dObj + go_UnasWeeklyQuestType);
			BOOL bState =R_DW(dObj + go_UnasWeeklyQuestState);

			temp.dObj = dObj;
			temp.ID = dQuestId;
			temp.csName = cQuestName;
			if (isQuestProgress)//已接
			{
				temp.状态 = 1;
				//	//MyTrace(L"0%I64X  进行中任务 ID %d<0x%X>  %s", dObj, dQuestId, dQuestId, cQuestName);
			}
			else
			{
				if (bState)
				{
					temp.状态 = 2;
					////MyTrace(L"0%I64X  可接任务 ID %d<0x%X>  %s", dObj, dQuestId, dQuestId, cQuestName);
				}
				else
				{
					if (isQuestCon)
					{
						temp.状态 = 3;
						////MyTrace(L"0%I64X  已完成任务 ID %d<0x%X>  %s", dObj, dQuestId, dQuestId, cQuestName);
					}
					else
					{
						temp.状态 = 0;
						//	//MyTrace(L"0%I64X  不符合条件未显示任务 ID %d<0x%X>  %s", dObj, dQuestId, dQuestId, cQuestName);
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

	int X = 周常任务::getUnasTaskPoint();

	return X ;


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

void gei_guild(vector<工会_>& 临时)
{
	工会_ temp;
	临时.clear();
	INT64 addr_1 = R_QW(游戏模块 + 行会rcx);
	//[[0x50B5D90+LOSTARK.0]+ 0xB128]+0*88
	INT64 addr_2 = R_QW(addr_1 + g_行会遍历);
	long dtotal = R_DW(addr_1 + g_行会遍历 + 8);
	for (int i = 0; i < dtotal; i++)
	{
		INT64 addr = addr_2  + i * 0x88;
		//INT64 dRealNameAddr = R_QW(addr);
			temp.行会名称= R_CString(R_QW(addr+8));
			//temp.行会等级 = R_CString(R_QW(addr+0x8));
			temp.行会会长 = R_CString(R_QW(addr + 0x28));
			temp.行会人数 = R_CString(R_QW(addr + 0x38));
			temp.行会name = R_CString(R_QW(addr + 0x40));
			temp.行会ID = R_QW(addr);
			//MyTrace(L" addr %I64X 行会ID %I64x 名称%s  人数%s 行会会长%s ", addr,temp.行会ID ,temp.行会名称 , temp.行会人数,temp.行会会长);
			临时.push_back(temp);
	}


}

void 创建公会()
{
	wchar_t* 尾[12] = { L"jan",L"feb",L"mar",L"apr",L"may",L"jun",L"jul",L"aug",L"sept",L"oct",L"nov",L"dec" };
	wchar_t* 尾2[7] = { L"mon",L"tues",L"wed",L"thur",L"fri",L"sat",L"sun" };
	wchar_t* 尾3[4] = { L"spr",L"sum",L"aut",L"win" };
	wchar_t* 尾4[4] = { L"east",L"west",L"nort",L"sort" };
	srand(time(NULL));
	CString 名称;
	//CString 首字 = 随机生成英文名字(1);v
	switch ((rand() % 4))
	{
	case 1:
		名称 = randstr(Random(6, 13)) + 尾[Random(0, 11)];
	case 2:
		名称 = randstr(Random(6, 14)) + 尾2[Random(0, 6)];
	case 3:
		名称 = randstr(Random(6, 15)) + 尾3[Random(0, 3)];
	default:
		名称 = randstr(Random(6, 16)) + 尾4[Random(0, 3)];
	}

	INT64 addr_1 = R_QW(游戏模块 + 行会rcx);
	INT64 局_call = 游戏模块 + 创建公会call;
	temp名称指针 cStringClassPtr2;
	cStringClassPtr2.名称obj = INT64(名称.GetBuffer());
	cStringClassPtr2.长度 = 名称.GetLength() + 1;
	UCHAR pBuff[0x100] = { 0 };
	W_QW((ULONG64)&pBuff[0x48], (UINT64)&cStringClassPtr2);
	MainUniversalCALL6(addr_1, (UINT64)&cStringClassPtr2, 0, 1, (ULONG_PTR)pBuff,0, 局_call);




}



void 搜索工会(CString 名称)
{
	INT64 addr_1 = R_QW(游戏模块 + 行会rcx);
	INT64 call = 游戏模块 + 搜索行会call;
	temp名称指针 cStringClassPtr2;
	cStringClassPtr2.名称obj = INT64(名称.GetBuffer());
	cStringClassPtr2.长度 = 名称.GetLength() + 1;

	MainUniversalCALL4(addr_1, 2, (UINT64)&cStringClassPtr2, 0, call);

}


CString 加入的公会名称()
{
	CString 行会 = L" ";
	INT64 addr_1 = R_QW(游戏模块 + 行会rcx);
	INT64 name =addr_1 +当前工会名称+当前工会名称1;

	行会 = R_CString(name);

	return 行会;
}



bool 公会是否加入()
{
	INT64 addr_1 = R_QW(游戏模块 + 行会rcx);
	DWORD 是否打开 = R_DW(addr_1 + 是否加入工会);   //48 8D 88 ?? ?? ?? ?? 48 8B 01 FF 50 ?? 48 8B 0D ?? ?? ?? ?? E8 ?? ?? ?? ?? 48 85 C0 0F 84 ?? ?? ?? ?? 48 8D B8 ?? ?? ?? ?? 48 85 FF  +0x14  进call   +0x0

	if (是否打开 > 1)
	{
		return 1;
	}
	return 0;



}


void 离开工会()
{
	INT64 rcx = 0;
	DWORD x = 0;
	bool 是否打开 = UI功能::寻找打开窗口("root1.arkui.windowCanvas.guildPortalWnd", rcx);
	if (rcx >= 1)
	{
		DWORD dResId = R_DW(rcx + 偏移_UI_显示);
		if (dResId == 1)
		{
			MainUniversalCALL2(rcx, 0, 游戏模块 + 基址_工会_离开call);
		}
	}

	else

	{
		bool 是否打开 = UI功能::寻找打开窗口("root1.arkui.windowCanvas.guildJoinWnd", rcx);
		DWORD dResId = R_DW(rcx + 偏移_UI_显示);
		if (dResId == 1)
		{
			MainUniversalCALL2(rcx, 0, 游戏模块 + 基址_工会_离开call);
		}

	}





}



void 工会捐赠(DWORD 金币)
{

	INT64 局_rcx = R_QW(游戏模块 + 基址_封包_发包rcx);
	INT64 局_call = 游戏模块 + 基址_封包_发包call;
	INT64 局_复活包头 = 游戏模块 + 基址_工会_捐赠rdx;

	UCHAR pBuff[0x100] = { 0 };
	W_QW((ULONG64)&pBuff[0x0], 局_复活包头);
	W_BYTE((ULONG64)&pBuff[0x18], 0x8);
	W_DW((ULONG64)&pBuff[0x19], 金币);

	MainUniversalCALL2(局_rcx, (ULONG_PTR)pBuff, 局_call);
}



void 输入工会密码call(INT64 ID, CString 密码)
{
	INT64 call = 游戏模块 + 基址_组队_踢出队伍call;
	INT64 rcx = R_QW(游戏模块 + 基址_组队_离开队伍rcx);
	INT64 rdx = 游戏模块 + 基址_工会_输入密码rdx;

	temp名称指针 cStringClassPtr2;
	cStringClassPtr2.名称obj = INT64(密码.GetBuffer());
	cStringClassPtr2.长度 = 密码.GetLength() + 1;
	UCHAR pBuff[0x100] = { 0 };
	W_QW((ULONG64)&pBuff[0x0], rdx);
	W_BYTE((ULONG64)&pBuff[0x19], 0x2);
	//W_DW((ULONG64)&pBuff[0x2C], 0xC1CB);
	W_CString((ULONG64)&pBuff[0x1A],密码);
	//W_Word((ULONG64)&pBuff[0x2C],0x71);

	W_QW((ULONG64)&pBuff[0x30], ID);

	////MyTrace(L"  行会ID %I64X ", ID);
	////MyTrace(L" addr %I64X", (ULONG64)&pBuff+0x18);
MainUniversalCALL6(rcx, (ULONG_PTR)pBuff, 0, 0, (UINT64)&cStringClassPtr2, 0, call);
	////MyTrace(L" addr %I64X", R_QW(R_QW((UINT64)&cStringClassPtr2)));


	//INT64 局_rcx = R_QW(游戏模块 + 基址_封包_发包rcx);
	//INT64 局_call = 游戏模块 + 基址_封包_发包call;
	//INT64 局_复活包头 = 游戏模块 + 基址_个人_复活包头;
	//UCHAR pBuff[0x24] = { 0 };
	//W_QW((ULONG64)&pBuff[0x0], 局_复活包头);
	//W_QW((ULONG64)&pBuff[0x8], 0);
	//W_QW((ULONG64)&pBuff[0x10], 0);
	//W_Word((ULONG64)&pBuff[0x16], 0x230);
	//W_BYTE((ULONG64)&pBuff[0x17], 复活类型);
	//MainUniversalCALL2(局_rcx, (ULONG_PTR)pBuff, 局_call);

}

bool 打开工会签到界面()
{
	INT64 rcx = 0;



	DWORD x = 0;





	bool 是否打开 = UI功能::寻找打开窗口("root1.arkui.windowCanvas.guildPortalWnd", rcx);

	if (rcx >= 1)
	{
		DWORD dResId = R_DW(rcx + 偏移_UI_显示);
		if (dResId == 1)
		{
			MainUniversalCALL6(rcx, 0, 0, 0, 1, 0, 游戏模块 + gc_CheckAbilityStone);
			x = 1;
			return x;
		}
	}
	else
	{
		bool 是否打开 = UI功能::寻找打开窗口("root1.arkui.windowCanvas.guildJoinWnd", rcx);

		if (rcx >= 1)
		{
			DWORD dResId = R_DW(rcx + 偏移_UI_显示);
			if (dResId == 1)
			{
				MainUniversalCALL6(rcx, 0, 0, 0, 1, 0, 游戏模块 + gc_CheckAbilityStone);
				x = 1;
				return x;
			}
		}


	}







	return x;



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