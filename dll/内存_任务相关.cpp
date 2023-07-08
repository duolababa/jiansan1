#include "内存_任务相关.h"
CString getQuestStepClassString(INT64 dInfoAddr);
//bool 任务::CALL_交任务(DWORD 任务ID)
//{
//	INT64 局_rcx = R_QW(游戏模块 + gb_QuestCur);
//	INT64 局_CALL = R_QW(R_QW(局_rcx) + 120);
//
//	MainUniversalCALL4(局_rcx, 任务ID, 1, -1, 局_CALL);
//	return true;
//}
bool 任务::CALL_交任务(DWORD 任务ID, DWORD 奖励序号)
{
	INT64 局_rcx = R_QW(游戏模块 + gb_QuestCur);
	INT64 局_CALL = R_QW(R_QW(局_rcx) + 120);

	MainUniversalCALL4(局_rcx, 任务ID, 1, 奖励序号, 局_CALL);
	return true;
}

bool 任务::CALL_接任务(DWORD 任务ID)
{
	INT64 局_call = 游戏模块 + 基址_任务_接任务call;
	MainUniversalCALL2(任务ID, 0, 局_call);
	return true;
}

坐标_ 任务::CALL_取任务坐标(DWORD 任务ID, INT64 objbase, INT64 dResAddr)
{

	坐标_ 返回坐标;
	if (!任务ID || !objbase || !dResAddr)
	{
		return 返回坐标;
	}
	DWORD 局_地图ID参数;
	INT64 QuestTypeAddr = R_QW(dResAddr + 0x3C);
	DWORD 判断值 = R_BYTE(dResAddr + 0x124);

	DWORD type = R_BYTE(QuestTypeAddr + 0xB0);

	INT64 dCall1 = 游戏模块 + 基址_任务_获取任务地图ID;

	int 参数1 = R_BYTE(objbase + 8);
	INT64 raxx = MainUniversalCALL2_Ret(dResAddr, 参数1, dCall1);
	if (type == 2)
	{

		局_地图ID参数 = R_DW(raxx + 0x11C);
	}
	if (type == 0 || type == 1 || type == 8 || type == 4 || type == 5)
	{

		if (R_BYTE(objbase + 0x88) == 1)
		{
			局_地图ID参数 = R_DW(raxx + 0x11C);
		}
		if (R_BYTE(objbase + 0x88) == 2)
		{
			局_地图ID参数 = R_DW(QuestTypeAddr + 0xFC);
		}


	}
	//if (type == 5)
	//{
	//	局_地图ID参数 = R_DW(raxx + 0x25C);
	//	//局_地图ID参数 = R_DW(raxx + 0x25C);
	//}
	MyTrace(L"type:%d 局_地图ID参数 %d 状态 %d 可能参数1 %d 可能参数2 %d ", type, 局_地图ID参数, R_BYTE(objbase + 0x88), R_DW(raxx + 0x11C), R_DW(QuestTypeAddr + 0xFC));
	//DWORD 任务ID;
	/*if (任务.dType == 2)
	{
		任务ID = 任务.dQuestId-1;
	}
	else
	{
		任务ID = 任务.dQuestId;
	}*/

	INT64 局_rcx = R_QW(游戏模块 + gb_QuestCur - 8);

	if (局_rcx && !IsBadReadPtr((const void*)局_rcx, sizeof(局_rcx)) && !环境::是否在加载页面2())
	{
		INT64 局_CALL = 游戏模块 + 基址_任务_获取任务坐标;
		UCHAR 局_rdx0[0x100] = { 0 };
		//INT64 局_rdx0 = 0;
		INT64 局_rdx = (INT64)&局_rdx0;
		MainUniversalCALL4(局_rcx, 局_rdx, 局_地图ID参数, 任务ID, 局_CALL);

		返回坐标.大陆ID = R_DW(局_rdx);
		返回坐标.x = R_Float(局_rdx + 4);
		返回坐标.y = R_Float(局_rdx + 8);
		返回坐标.z = R_Float(局_rdx + 12);
		返回坐标.地图ID = R_DW(局_rdx + 20);

	}
	MyTrace(L"返回任务坐标state:%d 返回坐标.地图ID %d 坐标:%0.3f %0.3f %0.3f", 返回坐标.大陆ID, 返回坐标.地图ID, 返回坐标.x, 返回坐标.y, 返回坐标.z);


	return 返回坐标;
}


INT64 getQuesResArrayAddr()
{
	//INT64 gb_Res = 0x141e243f8;//0x141687b28;
	//gb_QuestRes = dm.GetModuleBaseAddr(L"LOSTARK.exe") + 0x44D32D0;//0x423F8C0;
	INT64 addr_1 = R_QW(游戏模块 + gb_QuestRes);
	INT64 addr_2 = addr_1 + 0xA0;////更新-0220 0x50;
	long dtotal = R_DW(addr_2 + 0x44);
	INT64 objStartAddr = R_QW(addr_2);//对象数组地址
	INT64 indexStartAddr = R_QW(addr_2 + 0x3C);//索引数组地址
	for (long i = 0; i < dtotal; i++)
	{
		long dIndex = R_DW(indexStartAddr + i * 4);
		if (dIndex != 0xFFFFFFFF)
		{
			long dOffest = dIndex * 5 * 4;
			INT64 dObjAddr = R_QW(objStartAddr + dOffest + 4);
			DWORD dId = R_DW(objStartAddr + dOffest);
			if (dId == 1)
			{
				//MyTrace(L"对象地址0x%I64X\r\n", dObjAddr);
				return dObjAddr;
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
					dObjAddr = R_QW(objStartAddr + dOffest + 4);
					dId = R_DW(objStartAddr + dOffest);
					if (dId == 1)
					{
						//MyTrace(L"对象地址0x%I64X", dObjAddr);
						return dObjAddr;
					}
				}
			}
		}
	}
	return 0;
}
void getQuestStepInfo(INT64 dResAddr, DWORD dStep, QuestInfo_& bi)
{
	long dtotal = R_DW(dResAddr + 0x4C + 0x10 + 0x18);//更新-0220
	INT64 objStartAddr = R_QW(dResAddr + 0x4C);//更新-0220
	for (DWORD i = 0; i < dtotal; i++)
	{
		if (R_DW(objStartAddr + i * 0x5 * 4) == dStep)
		{
			INT64 dStepInfoAddr = R_QW(objStartAddr + i * 0x5 * 4 + 4);
			INT64 dconStartAddr = R_QW(dStepInfoAddr + 0x68);//更新-0220
			long dconTotal = R_DW(dStepInfoAddr + 0x70);//更新-0220

			for (DWORD k = 0; k < dconTotal; k++)
			{
				INT64 dInfoAddr = R_QW(dconStartAddr + k * 8);
				CString QuestOption = getQuestStepClassString(dInfoAddr);
				bi.QuestOption = QuestOption;
				INT64 dNameAddr = R_QW(dInfoAddr + 0x20);//任务目标描述
				DWORD dNum = R_DW(dInfoAddr + 0x48);//要完成的数量 //更新-0220
				DWORD dId = 0;
				if (R_DW(dInfoAddr + 0x70))//
				{
					dId = R_DW(R_QW(dInfoAddr + 0x68));//获取目标ID 
					bi.TargetId = dId;
				}
				bi.TargetNum = dNum;
				//MyTrace(L"任务目标 数量 %d\r\n", dNum);
				DWORD dStrLen = R_DW(dInfoAddr + 0x20 + 8) - 1;
				INT64 dRealNameAddr = getStringAddr(0, dNameAddr, dStrLen);
				//MyTrace(L"dRealNameAddr 0x%I64x", dRealNameAddr);
				CString csName = R_CString(dRealNameAddr);
				bi.DescribeName = csName;
				if (dconTotal == bi.子任务进度.size())
				{
					bi.子任务进度[k].TargetID = dId;
					bi.子任务进度[k].任务描述 = csName;
				}
				//MyTrace(L"%s\r\n 0x%I64X ", csName, dRealNameAddr);

			}
		}
	}
}
void 任务::getQuestCurStepInfo(INT64 dObj, QuestInfo_& bi, vector<SubQuestNeed_>& 子任务进度组)
{
	SubQuestNeed_ ci;
	//INT64 dCurConStartAddr = R_QW(dObj + 0x8C8,3);
	//long dCurConTotal = dm.ReadIntAddr(dObj + 0x8D0,4);
	/*INT64 dCurConStartAddr = R_QW(dObj + 0x6D0,3);
	long dCurConTotal = dm.ReadIntAddr(dObj + 0x6D8,4);*/
	INT64 dCurConStartAddr = R_QW(dObj + go_QuestStepCompStart);//更新-0220
	long dCurConTotal = R_DW(dObj + go_QuestStepCompStart + 8);//更新-0220
	for (DWORD i = 0; i < dCurConTotal; i++)
	{
		DWORD dCurNum = R_DW(dCurConStartAddr + 0x60 * i + 4);//更新-0220
		DWORD dNeedNum = R_DW(dCurConStartAddr + 0x60 * i + 8);//更新-0220
		bi.CurNum = dCurNum;
		bi.NeedNum = dNeedNum;
		ci.dCur = dCurNum;
		ci.dNeed = dNeedNum;
		子任务进度组.push_back(ci);
	}
}
INT64 getQuestResAddrById(DWORD dResId)
{
	INT64 QuesResArrayAddr = getQuesResArrayAddr();
	if (QuesResArrayAddr)
	{
		QuesResArrayAddr = QuesResArrayAddr + 0x8;
		long dtotal = R_DW(QuesResArrayAddr + 0x28);
		INT64 objStartAddr = R_QW(QuesResArrayAddr);//对象数组地址
		for (int i = 0; i < dtotal; i++)
		{
			if (R_DW(objStartAddr + i * 0x38 + 0x4) == dResId)
			{
				if (R_DW(objStartAddr + i * 0x38 + 0x4 + 0x1C) == 4)
				{
					return R_QW(objStartAddr + i * 0x38 + 0x28);//更新-0220 ;
				}

			}

		}
	}
	return 0;
}
void getQuestInfo(INT64 dObj, QuestInfo_& bi)
{
	vector<SubQuestNeed_>子任务进度组;
	任务::getQuestCurStepInfo(dObj, bi, 子任务进度组);
	bi.子任务进度 = 子任务进度组;
	bi.objBase = dObj;
	bi.dQuestId = R_DW(dObj);
	bi.dStep = R_BYTE(dObj + 0x8);//单字节
	bi.dState = R_W(dObj + 0x88);//双字节 1为正在做 2 为可交 //更新-0220
	bi.dResAddr = getQuestResAddrById(bi.dQuestId);
	INT64 dResInfoAddr = R_QW(bi.dResAddr + 0x3C);//更新-0220
	bi.dType = R_BYTE(dResInfoAddr + 0xB0);//更新-0220
	if (bi.dType == 0)
	{
		if (R_DW(dResInfoAddr + 0x100 + 4))//不为0已经做过了？ //更新-0220
		{
			bi.IsFinish = 1;
		}
	}
	INT64 dNameAddr = R_QW(dObj + 0xC);
	CString csName = L"空";
	if (dNameAddr)
	{
		csName = R_CString(dNameAddr);//dm.ReadStringAddr(dNameAddr,1,0); //
		bi.QuestName = csName;
		/*wcscpy(bi.wName, csName.GetBuffer(0));*/
	}
	dNameAddr = R_QW(dResInfoAddr + 0x1C + 0x3C);//更新-0220
	DWORD dStrLen = R_DW(dResInfoAddr + 0x1C + 0x3C + 8) - 1;//更新-0220  这个看下就行
	// INT64 dVlaue = getStringAddr( 0, dNameAddr, dStrLen);

	//CString cSumary = GetName(getStringAddr( 0, dNameAddr, dStrLen));
	// MyTrace(L"%s \r\n",cSumary);

	//if (bi.dQuestId == 0x3157A)
	{
		getQuestStepInfo(bi.dResAddr, bi.dStep, bi);
	}

	// MyTrace(L"地址%I64X 资源地址%I64X 任务ID %X 步骤%d 状态 %d\r\n",dObj,dResAddr,dQuestId,dStep,dState);
}

void 任务::get_CurQuestList(vector<QuestInfo_>& vsk)
{
	//gb_QuestCur = dm.GetModuleBaseAddr(L"LOSTARK.exe") + 0x4504C48;//0x4270C78;
	INT64 addr_1 = R_QW(游戏模块 + gb_QuestCur);
	long dtotal = R_DW(addr_1 + 0xD0);//更新-0220
	INT64 dKeyAddr = R_QW(addr_1 + 0xC8);//更新-0220
	if (!dKeyAddr)
	{
		dKeyAddr = addr_1 + 0xB8;//更新-0220
	}
	long dKeyValue = R_DW(addr_1 + 0xB8);//更新-0220
	INT64 objStartAddr = R_QW(addr_1 + 0xA8);//更新-0220
	for (DWORD i = 0; i < dtotal; i++)
	{
		long dKeyValue = R_DW(dKeyAddr + (i / 0x20) * 4);
		DWORD dNum = i % 0x20;
		DWORD dCheck = (dKeyValue >> dNum) & 1;
		if (dCheck)
		{
			DWORD dQuesId = R_DW(objStartAddr + i * 0x5 * 4);
			if (dQuesId && dQuesId != 0xFFFFFFFF)
			{
				INT64 dObj = R_QW(objStartAddr + i * 0x5 * 4 + 4);
				if (dObj)
				{
					if (R_DW(dObj + 4) && R_W(dObj + 0xC))
					{
						dObj = dObj + 0x10;//更新-0220
						QuestInfo_ bi;
						//memset(&bi, 0, sizeof(_QuestInfo));
						getQuestInfo(dObj, bi);
						vsk.push_back(bi);
					}
				}
			}
		}
	}
}



BOOL 任务::bCheckGuildQuestState(DWORD dQuestId)//指引可接
{
	//bool result = (BOOL)MainUniversalCALL4_Ret(0, 1, dQuestId, 0, 游戏模块 + gc_CheckGuildQuest);
	bool result = (BOOL)CALL4(0, 1, dQuestId, 0, 游戏模块 + gc_CheckGuildQuest);
	return result;
	/*wchar_t buf[100];
	dm.AsmClear();
	dm.AsmAdd(L"sub rsp,020");
	memset(buf, 0, 200);
	wsprintf(buf, L"mov r8d, 0%X", dQuestId);
	dm.AsmAdd(buf);
	memset(buf, 0, 200);
	wsprintf(buf, L"mov edx, 0%X", 1);
	dm.AsmAdd(buf);
	memset(buf, 0, 200);
	wsprintf(buf, L"mov rdi, 0%I64X", gc_CheckGuildQuest);
	dm.AsmAdd(buf);
	dm.AsmAdd(L"call rdi");
	dm.AsmAdd(L"add rsp,020");
	return (BOOL)dm.AsmCall(6);*/
}

void 任务::get_GuideList(vector<QuestInfo_>& vsk)//指导
{
	vsk.clear();
	QuestInfo_ temp;
	int dtotal = R_DW(游戏模块 + gb_GuildQuestList + 0x10 + 0x18);
	INT64 objStartAddr = R_QW(游戏模块 + gb_GuildQuestList);
	for (int i = 0; i < dtotal; i++)
	{
		DWORD dQuestId = R_DW(objStartAddr + i * 0x10 + 4);
		if (dQuestId)
		{
			//if (bCheckGuildQuestState(dQuestId))
			{
				INT64 dResAddr = getQuestResAddrById(dQuestId);
				if (dResAddr)
				{
					INT64 dInfoAddr = R_QW(dResAddr + 0x3C);
					INT64 dNameAddr = R_QW(dInfoAddr + 0x34);
					DWORD dStrLen = R_DW(dInfoAddr + 0x34 + 8) - 1;
					INT64 dRealNameAddr = getStringAddr(0, dNameAddr, dStrLen);
					CString csName = R_CString(dRealNameAddr);
					temp.dQuestId = dQuestId;
					temp.QuestName = csName;
					vsk.push_back(temp);
					wchar_t buf[MAX_PATH];
					//swprintf(buf, L"%X %s 0x%I64X \r\n", dQuestId, csName, dRealNameAddr);
					//MyTrace(buf);
				}
			}
		}
	}
}



bool 是否要做指引任务(DWORD QuestID)
{
	if (QuestID == 0x451FD9)//451FD9 [指引] 了解宠物 0x23105963780 
	{
		return true;
	}
	if (QuestID == 0x451FDA)//451FDA [指引] 最好在一起 0x23105963780 
	{
		return true;
	}
	if (QuestID == 0x10EC6E)//天灾守护者讨伐资格证明
	{
		return true;
	}
	if (QuestID == 0x10EC6F)//加工能力石
	{
		return true;
	}
	if (QuestID == 0x451FD0)//加工能力石
	{
		return true;
	}
	return false;
}
QuestInfo_ 任务::取出可接指引任务()
{
	QuestInfo_ temp;
	vector<QuestInfo_>vsk;
	任务::get_GuideList(vsk);
	for (size_t i = 0; i < vsk.size(); i++)
	{
		if (是否要做指引任务(vsk[i].dQuestId))
		{
			if (bCheckGuildQuestState(vsk[i].dQuestId))
			{
				temp = vsk[i];
				break;
			}
		}

	}
	return temp;
}
QuestInfo_ 任务::取出世界任务()
{
	QuestInfo_ temp;
	vector<QuestInfo_>vsk;
	任务::get_CurQuestList(vsk);
	for (size_t i = 0; i < vsk.size(); i++)
	{
		if (vsk[i].dType == 5)
		{
			temp = vsk[i];
			return temp;

		}
	}
	return temp;
}
QuestInfo_ 任务::取出主线任务()
{
	QuestInfo_ temp;
	vector<QuestInfo_>vsk;
	任务::get_CurQuestList(vsk);
	for (size_t i = 0; i < vsk.size(); i++)
	{
		if (vsk[i].dType == 2)
		{
			temp = vsk[i];
			return temp;

		}
	}
	for (size_t i = 0; i < vsk.size(); i++)
	{
		if (vsk[i].dType == 0 && vsk[i].dQuestId != 4500001)
		{
			temp = vsk[i];
			return temp;
		}
	}
	for (size_t i = 0; i < vsk.size(); i++)
	{
		if (vsk[i].dType == 5)
		{
			temp = vsk[i];
			break;
		}
	}
	return temp;
}
QuestInfo_ 任务::取出主线子任务()
{
	QuestInfo_ temp;
	vector<QuestInfo_>vsk;
	任务::get_CurQuestList(vsk);
	for (size_t i = 0; i < vsk.size(); i++)
	{
		if (vsk[i].dType == 2)
		{
			temp = vsk[i];
			break;
		}
	}
	return temp;
}
QuestInfo_ 任务::取出其他任务()
{
	QuestInfo_ temp;
	vector<QuestInfo_>vsk;
	任务::get_CurQuestList(vsk);
	for (size_t i = 0; i < vsk.size(); i++)
	{
		if (vsk[i].dType != 2 && vsk[i].dType != 0)
		{
			temp = vsk[i];
			break;
		}
	}
	return temp;
}
QuestInfo_ 任务::取出指定主线任务(DWORD 任务ID)
{
	QuestInfo_ temp;
	vector<QuestInfo_>vsk;
	任务::get_CurQuestList(vsk);
	for (size_t i = 0; i < vsk.size(); i++)
	{
		if ((vsk[i].dType == 2 || vsk[i].dType == 0 || vsk[i].dType == 5) && vsk[i].dQuestId == 任务ID)
		{
			temp = vsk[i];
			break;
		}
	}
	return temp;
}
QuestInfo_ 任务::取出指定世界任务(DWORD 任务ID)
{
	QuestInfo_ temp;
	vector<QuestInfo_>vsk;
	任务::get_CurQuestList(vsk);
	for (size_t i = 0; i < vsk.size(); i++)
	{
		if (vsk[i].dType == 5 && vsk[i].dQuestId == 任务ID)
		{
			temp = vsk[i];
			break;
		}
	}
	return temp;
}
QuestInfo_ 任务::取出指定支线任务(DWORD 任务ID)
{
	QuestInfo_ temp;
	vector<QuestInfo_>vsk;
	任务::get_CurQuestList(vsk);
	for (size_t i = 0; i < vsk.size(); i++)
	{
		if ((vsk[i].dType == 1 || vsk[i].dType == 8) && vsk[i].dQuestId == 任务ID)
		{
			temp = vsk[i];
			break;
		}
	}
	if (temp.QuestName != L"")
	{
		MyTrace(L"QuestName %s QuestId %x dStep %d", temp.QuestName, temp.dQuestId, temp.dStep);
	}

	return temp;
}

QuestInfo_ 任务::取出触发任务()
{
	QuestInfo_ temp;
	vector<QuestInfo_>vsk;
	任务::get_CurQuestList(vsk);
	for (size_t i = 0; i < vsk.size(); i++)
	{
		if (vsk[i].dType == 4)
		{
			temp = vsk[i];
			break;
		}
	}
	return temp;
}
QuestInfo_ 任务::取出副本任务()
{
	QuestInfo_ temp;
	vector<QuestInfo_>vsk;
	任务::get_CurQuestList(vsk);
	for (size_t i = 0; i < vsk.size(); i++)
	{
		if (vsk[i].dType == 2)
		{
			temp = vsk[i];
			break;
		}
	}
	return temp;
}
bool 任务::是否已接任务(DWORD 任务ID)
{
	vector<QuestInfo_>vsk;
	任务::get_CurQuestList(vsk);
	for (size_t i = 0; i < vsk.size(); i++)
	{
		if (vsk[i].dQuestId == 任务ID)
		{
			return true;
		}
	}
	return false;
}
void 任务::get_FinishQuestList(vector<DWORD>& vsk)
{
	//gb_QuestCur = dm.GetModuleBaseAddr(L"LOSTARK.exe") + 0x4504C48;//0x4270C78;
	INT64 addr_1 = R_QW(游戏模块 + gb_QuestCur);
	long dtotal = R_DW(addr_1 + 偏移_任务_已完成任务 + 0x10 + 0x18);//更新-0220 '?? 8D ?? ?? ?? ?? ?? ?? 33 ?? ?? 8D ?? ?? ?? 8B ?? ?? ?? ?? ?? E8 ?? ?? ?? ?? ?? 63 ?? ?? ?? ?? 8B ?? ?? ?? ?? 8D +3
	INT64 objStartAddr = R_QW(addr_1 + 偏移_任务_已完成任务);
	for (DWORD i = 0; i < dtotal; i++)
	{
		DWORD dIndex = R_DW(objStartAddr + i * 0x4 * 4);
		if (dIndex != 0xFFFFFFFF)
		{
			DWORD dQuesId = R_DW(objStartAddr + i * 0x4 * 4 + 4);
			vsk.push_back(dQuesId);
			//MyTrace(L"已完成任务ID 0x%X\r\n", dQuesId);
		}
	}

}

bool 任务::任务是否已完成(DWORD 任务ID, vector<DWORD>& vsk)
{
	for (size_t i = 0; i < vsk.size(); i++)
	{
		if (vsk[i] == 任务ID)
		{
			return true;
		}
	}
	return false;
}



INT64 getNpcQuestTalkListResAddr(int dNpcResId)
{
	INT64 addr_1 = R_QW(游戏模块 + gb_QuestRes);
	UCHAR dInfoAddr[0x100] = { 0 };
	//UCHAR dlangAddr[0x100] = { 0 };
	CString dlang = L"USA";
	//INT64 dInfoAddr = dm.VirtualAllocEx( 0, 0x100, 0);
	//INT64 dlangAddr = dm.VirtualAllocEx( 0, 0x100, 0);
	W_DW((INT64)&dInfoAddr[4], dNpcResId);
	W_QW((INT64)&dInfoAddr[0x18], (UINT64)dlang.GetBuffer());
	W_DW((INT64)&dInfoAddr[0x20], 4);
	W_DW((INT64)&dInfoAddr[0x24], 4);
	//dm.WriteIntAddr( dInfoAddr + 4, 0, dNpcResId);
	//dm.WriteStringAddr( dlangAddr, 1, L"USA");
	/*dm.WriteIntAddr( dInfoAddr + 0x18, LEN_INT64, dlangAddr);
	dm.WriteIntAddr( dInfoAddr + 0x20, LEN_DWORD, 4);
	dm.WriteIntAddr( dInfoAddr + 0x24, LEN_DWORD, 4);*/
	return MainUniversalCALL4_Ret(addr_1, 2, (ULONG_PTR)dInfoAddr, 0, 游戏模块 + gc_GetNpcQuestTalkResList);
	/*CString cBuf;
	dm.AsmClear();
	dm.AsmAdd(L"mov edx, 02");
	dm.AsmAdd(MyFormat(cBuf, L"mov r8, 0%I64X", dInfoAddr));
	dm.AsmAdd(MyFormat(cBuf, L"mov rcx, 0%I64X", addr_1));
	dm.AsmAdd(MyFormat(cBuf, L"mov rdi, 0%I64X", gc_GetNpcQuestTalkResList));
	dm.AsmAdd(L"sub rsp,040");
	dm.AsmAdd(L"call rdi");
	dm.AsmAdd(L"add rsp,040");
	return dm.AsmCall( 6);*/
}

INT64 getNpcQuestTalkResAddr(INT64 dNpcQuestTalkListAddr, int dTaklResId)
{
	DWORD dArraySize = 0x14;
	DWORD dNextOffest = 0xC;
	DWORD dResId = dTaklResId;
	INT64 dResAddr = dNpcQuestTalkListAddr;
	DWORD dStartOffest = 0x4C;
	long dtotal = R_DW(dResAddr + dStartOffest + 0x44);
	DWORD dHash = dResId & (dtotal - 1);
	INT64 objStartAddr = R_QW(dResAddr + dStartOffest);//对象数组地址
	INT64 indexStartAddr = R_QW(dResAddr + dStartOffest + 0x3C);//索引数组地址
	INT64 dIndex = R_DW(indexStartAddr + dHash * 4);
	DWORD dOffest = dIndex * dArraySize;
	INT64 dObjAddr = R_QW(objStartAddr + dOffest + 4);
	if (dResId == R_DW(objStartAddr + dOffest))
	{
		return dObjAddr;
	}
	else
	{
		DWORD dNextIndex = 0;
		while (1)
		{
			dNextIndex = R_DW(objStartAddr + dOffest + dNextOffest);
			if (dNextIndex == 0xFFFFFFFF)//为-1跳出循环
			{
				break;
			}
			else
			{
				dOffest = dNextIndex * dArraySize;
				dObjAddr = R_QW(objStartAddr + dOffest + 4);
				if (dResId == R_DW(objStartAddr + dOffest))
				{
					// MyTrace(L"地址0x%I64X \r\n",dObjAddr); 
					return dObjAddr;
				}
			}
		}
	}
	return 0;
}

CString getQuestTalkClassString(INT64 dInfoAddr)
{
	CString cClassName = L"";
	INT64 dClassAddr = R_QW(dInfoAddr);
	INT64 dClassStrFunAddr = R_QW(dClassAddr + 0x30);
	INT64 dClassStrAddr = R_DW(dClassStrFunAddr + 1 + 0x32) + dClassStrFunAddr + 5 + 0x32;
	cClassName = R_CString(dClassStrAddr);
	return cClassName;
}
_QuestTalkInfo g_QuestTalkInfoList[2000];
void getAllQuestNpcTalkList(INT64 dNpcQuestTalkListAddr, int dTalkResId, int dParentId, int& dTalkTotal)
{

	if (!dTalkResId || dTalkTotal > 1000) return;
	//MyTrace(L"dTalkResId %d dTalkTotal %d ", dTalkResId, dTalkTotal);
	INT64 dResAddr = getNpcQuestTalkResAddr(dNpcQuestTalkListAddr, dTalkResId);
	if (dResAddr)
	{
		g_QuestTalkInfoList[dTalkTotal].dTalkId = dTalkResId;
		g_QuestTalkInfoList[dTalkTotal].dParentId = dParentId;
		g_QuestTalkInfoList[dTalkTotal].dResAddr = dResAddr;
		wcsncpy(g_QuestTalkInfoList[dTalkTotal].wName, getQuestTalkClassString(dResAddr).GetBuffer(0), MAX_PATH);

		dTalkTotal = dTalkTotal + 1;
		INT64 dstart = R_QW(dResAddr + 0xC);
		int dtotal = R_DW(dResAddr + 0x14);
		for (DWORD i = 0; i < dtotal; i++)
		{
			int dNextTalkResId = R_DW(dstart + i * 4);
			getAllQuestNpcTalkList(dNpcQuestTalkListAddr, dNextTalkResId, dTalkResId, dTalkTotal);
		}
	}

}
int getQuestNpcTalkAchievementAddr(INT64 dNpcQuestTalkListAddr, INT64 dTalkAddr)
{
	MyTrace(L"getQuestNpcTalkAchievementAddr 1");
	memset(g_QuestTalkInfoList, 0, sizeof(_QuestTalkInfo) * 2000);
	//MyTrace(L"getQuestNpcTalkAchievementAddr 2");
	int dTalkTotal = 0;
	int dTalkId = R_DW(dTalkAddr + 8);
	getAllQuestNpcTalkList(dNpcQuestTalkListAddr, dTalkId, 0, dTalkTotal);
	MyTrace(L"getQuestNpcTalkAchievementAddr 3 dTalkTotal %d", dTalkTotal);
	for (int i = 0; i < dTalkTotal; i++)
	{
		MyTrace(L"地址%I64X 父ID%X 对话ID%X %s", g_QuestTalkInfoList[i].dResAddr, g_QuestTalkInfoList[i].dParentId, g_QuestTalkInfoList[i].dTalkId, g_QuestTalkInfoList[i].wName);//CEFTalkConditionSeq_Achievement
		if (wcscmp(g_QuestTalkInfoList[i].wName, L"CEFTalkConditionSeq_Achievement") == 0)
		{
			MyTrace(L"Find it 地址%I64X 父ID%X 对话ID%X %s", g_QuestTalkInfoList[i].dResAddr, g_QuestTalkInfoList[i].dParentId, g_QuestTalkInfoList[i].dTalkId, g_QuestTalkInfoList[i].wName);
			return R_DW(g_QuestTalkInfoList[i].dResAddr + 0x54);
		}
	}
	return 0;
}
int getNpcTaklEndSendArgFinally(int dNpcResId, int dQuestId, int dType, int dStep)
{
	INT64 go_NpcQuestTalkListStart = 0x114;
	INT64 dNpcQuestTalkListAddr = getNpcQuestTalkListResAddr(dNpcResId);
	MyTrace(L"dNpcQuestTalkListAddr 0x%I64x", dNpcQuestTalkListAddr);
	if (!dNpcQuestTalkListAddr) return 0;
	INT64 addr_1 = dNpcQuestTalkListAddr + go_NpcQuestTalkListStart;
	long dtotal = R_DW(addr_1 + 0x10 + 0x18);
	INT64 dKeyAddr = R_QW(addr_1 + 0x20);
	if (!dKeyAddr)
	{
		dKeyAddr = addr_1 + 0x10;
	}
	long dKeyValue = R_DW(addr_1 + 0x10);
	INT64 objStartAddr = R_QW(addr_1);
	for (int i = 0; i < dtotal; i++)
	{
		long dKeyValue = R_DW(dKeyAddr + (i / 0x20) * 4);
		int dNum = i % 0x20;
		int dCheck = (dKeyValue >> dNum) & 1;
		if (dCheck)
		{
			INT64 dObjAddr = objStartAddr + i * 0x14;
			if (R_DW(dObjAddr) == dQuestId)//比较任务ID
			{
				INT64 dInfo = R_QW(dObjAddr + 4);
				if (dType == R_DW(dInfo + 0x44))
				{
					if (dType == 4)
					{
						if (dStep == R_DW(dInfo + 0x4C))
						{
							return getQuestNpcTalkAchievementAddr(dNpcQuestTalkListAddr, dInfo);
						}
					}
					else
					{
						//MyTrace(L"对话首地址 %I64X", dInfo);
						return getQuestNpcTalkAchievementAddr(dNpcQuestTalkListAddr, dInfo);
					}

				}
			}
		}
	}
	return 0;
}
int 任务::getNpcTaklEndSendArg(int dNpcResId, int dQuestId, int dStep)
{
	// 
	int 返回值 = 0;
	INT64 addr_1 = R_QW(游戏模块 + gb_QuestCur);
	UCHAR dInfoAddr[0x100] = { 0 };
	MainUniversalCALL4(addr_1, dNpcResId, (ULONG_PTR)dInfoAddr, 0, 游戏模块 + gc_GetNpcQuestTalkCurList);
	MyTrace(L"获取信息");
	//DbgPrintf_Mine("获取信息 %s", __FUNCTION__);
	//INT64 dInfoAddr = dm.VirtualAllocEx( 0, 0x100, 0);
	/*CString cBuf;
	dm.AsmClear();
	dm.AsmAdd(L"xor r9d,r9d");
	dm.AsmAdd(MyFormat(cBuf, L"mov r8, 0%I64X", dInfoAddr));
	dm.AsmAdd(MyFormat(cBuf, L"mov edx, 0%X", dNpcResId));
	dm.AsmAdd(MyFormat(cBuf, L"mov rcx, 0%I64X", addr_1));
	dm.AsmAdd(MyFormat(cBuf, L"mov rdi, 0%I64X", gc_GetNpcQuestTalkCurList));
	dm.AsmAdd(L"sub rsp,040");
	dm.AsmAdd(L"call rdi");
	dm.AsmAdd(L"add rsp,040");
	dm.AsmCall( 6);*/
	int dtotal = R_DW((INT64)&dInfoAddr + 8);
	if (dtotal)
	{
		INT64 dstart = R_QW((INT64)&dInfoAddr);//更新-0220
		for (DWORD i = 0; i < dtotal; i++)
		{
			INT64 dObj = dstart + i * 8;
			int dType = R_DW(dObj);
			if (dQuestId == R_DW(dObj + 4))
			{
				int dArg = getNpcTaklEndSendArgFinally(dNpcResId, dQuestId, dType, dStep);
				返回值 = dArg;
				MyTrace(L"类型 %X 任务ID%X 发包所需参数值%X \r\n", dType, dQuestId, dArg);//类型4是可直接交的 类型3是显示问号的完成任务
				//return dArg;
			}

		}
		///////////////////////释放指针///////////////////////////////////////////////////
		MainUniversalCALL2((ULONG_PTR)dInfoAddr, 0, 游戏模块 + gc_GameListFree);
		return 返回值;
		/*dm.AsmClear();
		dm.AsmAdd(L"xor edx,edx");
		dm.AsmAdd(MyFormat(cBuf, L"mov rcx, 0%I64X", dInfoAddr));
		dm.AsmAdd(MyFormat(cBuf, L"mov rdi, 0%I64X", gc_GameListFree));
		dm.AsmAdd(L"sub rsp,040");
		dm.AsmAdd(L"call rdi");
		dm.AsmAdd(L"add rsp,040");
		dm.AsmCall( 6);*/

	}
	return  0;
}



int 任务::getNpcTaklEndSendArg1(int dNpcResId, int dQuestId, int dStep)
{
	// 
	int 返回值 = 0;
	INT64 addr_1 = R_QW(游戏模块 + gb_QuestCur);
	UCHAR dInfoAddr[0x100] = { 0 };
	MainUniversalCALL4(addr_1, dNpcResId, (ULONG_PTR)dInfoAddr, 0, 游戏模块 + gc_GetNpcQuestTalkCurList);
	MyTrace(L"获取信息");
	//DbgPrintf_Mine("获取信息 %s", __FUNCTION__);
	//INT64 dInfoAddr = dm.VirtualAllocEx( 0, 0x100, 0);
	/*CString cBuf;
	dm.AsmClear();
	dm.AsmAdd(L"xor r9d,r9d");
	dm.AsmAdd(MyFormat(cBuf, L"mov r8, 0%I64X", dInfoAddr));
	dm.AsmAdd(MyFormat(cBuf, L"mov edx, 0%X", dNpcResId));
	dm.AsmAdd(MyFormat(cBuf, L"mov rcx, 0%I64X", addr_1));
	dm.AsmAdd(MyFormat(cBuf, L"mov rdi, 0%I64X", gc_GetNpcQuestTalkCurList));
	dm.AsmAdd(L"sub rsp,040");
	dm.AsmAdd(L"call rdi");
	dm.AsmAdd(L"add rsp,040");
	dm.AsmCall( 6);*/
	int dtotal = R_DW((INT64)&dInfoAddr + 8);
	if (dtotal)
	{
		INT64 dstart = R_QW((INT64)&dInfoAddr);//更新-0220
		for (DWORD i = 0; i < dtotal; i++)
		{
			INT64 dObj = dstart + i * 8;
			int dType = R_DW(dObj);
			if (dQuestId == R_DW(dObj + 4))
			{
				int dArg = getNpcTaklEndSendArgFinally(dNpcResId, dQuestId, dType, dStep);
				返回值 = dArg;
				MyTrace(L"类型 %X 任务ID%X 发包所需参数值%X \r\n", dType, dQuestId, dArg);//类型4是可直接交的 类型3是显示问号的完成任务
				if (dType == 4)								   //return dArg;
				{
					MyTrace(L"开始执行call");
					任务::Fun_阶段任务完成CALL(dArg);
					MyTrace(L"执行call结束");
				}
				if (dType == 3)
				{
					任务::CALL_交任务(dQuestId, -1);
				}
			}

		}
		///////////////////////释放指针///////////////////////////////////////////////////
		MainUniversalCALL2((ULONG_PTR)dInfoAddr, 0, 游戏模块 + gc_GameListFree);
		return 返回值;
		/*dm.AsmClear();
		dm.AsmAdd(L"xor edx,edx");
		dm.AsmAdd(MyFormat(cBuf, L"mov rcx, 0%I64X", dInfoAddr));
		dm.AsmAdd(MyFormat(cBuf, L"mov rdi, 0%I64X", gc_GameListFree));
		dm.AsmAdd(L"sub rsp,040");
		dm.AsmAdd(L"call rdi");
		dm.AsmAdd(L"add rsp,040");
		dm.AsmCall( 6);*/

	}
	return  0;
}

CString getQuestStepClassString(INT64 dInfoAddr)
{
	//CString cClassName = L"";
	INT64 dClassAddr = R_QW(dInfoAddr);
	INT64 dClassStrFunAddr = R_QW(dClassAddr);
	INT64 dClassStrAddr = R_DW(dClassStrFunAddr + 1 + 0x32) + dClassStrFunAddr + 5 + 0x32;
	CString cClassName = R_CString(dClassStrAddr);
	return cClassName;
}

int 任务::bCheckQuestStepIsEndNpcTalk(INT64 dResAddr, DWORD dStep)
{
	long dtotal = R_DW(dResAddr + 0x4C + 0x10 + 0x18);//更新-0220
	INT64 objStartAddr = R_QW(dResAddr + 0x4C);//更新-0220
	for (DWORD i = 0; i < dtotal; i++)
	{
		if (R_DW(objStartAddr + i * 0x5 * 4) == dStep)
		{
			INT64 dStepInfoAddr = R_QW(objStartAddr + i * 0x5 * 4 + 4);
			INT64 dconStartAddr = R_QW(dStepInfoAddr + 0x68);//更新-0220
			long dconTotal = R_DW(dStepInfoAddr + 0x70);//更新-0220
			for (DWORD k = 0; k < dconTotal; k++)
			{
				INT64 dInfoAddr = R_QW(dconStartAddr + k * 8);
				if (getQuestStepClassString(dInfoAddr).Compare(L"CEFQuestOption_End_TalkNPC") == 0)
				{
					if (R_DW(dInfoAddr + 0x70))//
					{
						return R_DW(R_QW(dInfoAddr + 0x68));//获取目标ID 
					}
				}
			}
		}
	}
	return 0;
}

void 任务::Fun_阶段任务完成CALL(DWORD SendArg)
{
	UCHAR dInfoAddr[0x1000] = { 0 };
	//INT64 dInfoAddr2 = (INT64)申请内存2(HANDLE(-1), 0x100);
	//INT64 dInfoAddr = dm.VirtualAllocEx( 0, 0x100, 0);
	MainUniversalCALL2((ULONG_PTR)dInfoAddr, SendArg, 游戏模块 + 基址_任务_阶段任务完成call);
	//释放内存2(HANDLE(-1), LPVOID(dInfoAddr2), 0x100);
}

QuestInfo_ 任务::取出寻找方舟任务()
{
	QuestInfo_ temp;
	vector<QuestInfo_>vsk;
	任务::get_CurQuestList(vsk);
	for (size_t i = 0; i < vsk.size(); i++)
	{
		if (vsk[i].dQuestId == 4500001)
		{
			temp = vsk[i];
			return temp;
		}
	}
	return temp;
}


INT64 环境::鼠标获取对象call(float px, float y)
{
	INT64 ret = 0;
	INT64 rcx = 0;
	INT64 call = 游戏模块_EFEngine + en鼠标call;
	INT64 x = 0;
	x = R_QW(游戏模块 + en鼠标基址);
	//MyTrace(L"打开rcx,0x%I64X", 游戏模块_EFEngine + en鼠标基址);
	x = R_QW(x);
	//MyTrace(L"打开rcx,0x%I64X", x);
	x = R_QW(x + 0x2F0);
	x = R_QW(x);
	rcx = R_QW(x + 0x3C);
	// MyTrace(L"打开rcx,0x%I64X", rcx);
	DWORD r9 = 1;
	DWORD r8 = 0;
	UCHAR 局_rdx0[0x100] = { 0 };
	W_Float((ULONG64)&局_rdx0[0], px);
	W_Float((ULONG64)&局_rdx0[4], y);
	// MyTrace(L"px x %0.3f %0.3f", px, y);
	INT64 rdx = (INT64)&局_rdx0;
	ret = MainUniversalCALL4_Ret(rcx, rdx, r8, r9, call);

	return ret;


}