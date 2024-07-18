#include "内存_混沌副本相关.h"
void gettReverseRuinListAll(INT64 dListAddr, DWORD dStartOffest, DWORD dArraySize, vector<副本信息_>& vsk)//混沌副本参数
{
	副本信息_ 临时;
	vsk.clear();
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

			//MyTrace(L"objStartAddr地址0x%I64x \r\n", objStartAddr);
			
				INT64 dObj = R_QW(objStartAddr + i * dArraySize + 4);
				if (dObj)
				{
					INT64 dLevStart = dObj;
					DWORD dLevTotal = R_DW(objStartAddr + i * dArraySize + 4 + 8);
					//MyTrace(L"dLevStart地址0x%I64X ID%X \r\n", dLevStart, dLevTotal);
					for (DWORD j = 0; j < dLevTotal; j++)
					{
					
						int dFbId = R_DW(dLevStart + j * 0x1C);//进入混沌用副本参数
						if (dFbId)
						{

							INT64 dResAddr = R_QW(dLevStart + j * 0x1C + 4);
							if (dResAddr)
							{
								INT64 dNameAddr = R_QW(dResAddr + 0x10);
								CString csName = L"空";
								if (dNameAddr)
								{
									临时.ID = dFbId;

									临时.csName = R_CString(dNameAddr);
									vsk.push_back(临时);
								}
								//MyTrace(L"地址0x%I64X ID%X %s\r\n", dResAddr, dFbId, 临时.csName);
							}
						}
					}
				}
			
		}
	}
}
DWORD getReverseRuinAll(CString csName)//资源获取混沌资源
{
	DWORD dReverseRuinIndex = getResIndexByName(L"ReverseRuin");
	INT64 dReverseRuinAddr = getResAddrById(dReverseRuinIndex);
	if (dReverseRuinAddr == 0)
	{
		return 0;
	}
	MyTrace(L"地址0x%I64X \r\n", dReverseRuinAddr);
	vector<副本信息_> vsk;
	//	return getResAddrByTypeId(getResIndexByName(L"ZoneBase"), dResId, 0x68, 0x4C, 0x54);
	gettReverseRuinListAll(dReverseRuinAddr, 0x68, 0x54, vsk);
	DWORD iterm = 0;

	for (size_t i = 0; i < vsk.size(); i++)
	{
		//MyTrace(L"%s ", csName);
		if (vsk[i].csName.Find(csName) != -1)
		{
			iterm = vsk[i].ID;
			break;
		}
	}
	return iterm;


}
void Fun_DungeonEntranceChaoEnter(int dId)
{

	INT64 dInfo = R_QW(游戏模块 + gb_EntranceInfo);
	W_DW(dInfo + go_DungeonEntranceInfoArg + 8, 0x7D0);
	W_DW(dInfo + go_DungeonEntranceInfoArg + 0xC, dId);
	W_BYTE(dInfo + go_DungeonEntranceInfoArg + 0x10, 7);
	MainUniversalCALL2(dInfo, 0, 游戏模块 + gc_DungeonEntranceEnter);
	//CString cBuf;
	//dm.AsmClear();
	//dm.AsmAdd(L"sub rsp,40");
	//dm.AsmAdd(L"xor edx,edx");
	//dm.AsmAdd(MyFormat(cBuf, L"mov rcx, 0%I64X", dInfo));
	//dm.AsmAdd(MyFormat(cBuf, L"mov rdi, 0%I64X", gc_DungeonEntranceEnter));
	//dm.AsmAdd(L"call rdi");
	//dm.AsmAdd(L"add rsp,040");
	//dm.AsmCall( 6);
}

BYTE getChaosDungeonState()
{
	INT64 addr_1 = R_QW(游戏模块 + gb_ChaosDungeonInfo);
	return R_BYTE(addr_1 + go_ChaosDungeonState);//读字节 1未开始 2已开始打怪 4时间结束
}
INT64 取混沌气息()
{
	return 背包::getMoneyNumByType(0x65);
}