#include "�ڴ�_ǩ���ʼ�.h"
void ǩ���ʼ�::get_ExpressMailList(vector<MailInfo_>& vsk)//�ʼ�����
{

	//INT64 go_ExpressMailType = 0x114;
	////?? 83 ?? ?? ?? ?? ?? ?? 0F ?? ?? ?? ?? ?? BA ?? ?? ?? ?? ?? 8B ?? E8 ?? ?? ?? ?? ?? 8B ?? E8 ?? ?? ?? ?? 0F + 0x23 + 3 go_ExpressMailType
	////E8 ?? ?? ?? ?? 0F ?? ?? ?? ?? ?? ?? FE ?? 80 ?? ?? 0F ?? ?? ?? ?? ?? ?? 8D ?? ?? ?? ?? ?? FF ?? ?? ?? ?? ?? 8D +5+3  go_ExpressMailType �ֶ�����
	//INT64 go_ExpressMailState = 0x11C;
	////0F ?? ?? 85 ?? 74 ?? ?? 80 ?? ?? ?? ?? ?? ?? 77 ?? ?? 8B ?? ?? 85 ?? 7E ?? FF +0x7+3 go_ExpressMailState
	//INT64 go_ExpressMailSenderName = 8;
	////?? 8B ?? ?? 33 ?? ?? 8D ?? ?? FF ?? ?? ?? ?? ?? ?? 83 ?? ?? ?? ?? ?? ?? 0F ?? ?? ?? ?? ?? ?? 8B ?? E8 ?? ?? ?? ?? ?? 8D   +26+3  ���ֽ� go_ExpressMailSenderName 
	//INT64 go_ExpressMailTitle = 0x4A;
	////?? 8B ?? FF ?? ?? ?? 8B ?? ?? ?? ?? ?? E8 ?? ?? ?? ?? ?? 8B ?? ?? 85 ?? 0F ?? ?? ?? ?? ?? ?? 8B ?? E8 ?? ?? ?? ?? ?? 8D   +26+3  ���ֽ� go_ExpressMailTitle
	INT64 addr_0 = R_QW(��Ϸģ�� + gb_ExpressMailList);
	INT64 addr_1 = addr_0 + go_ExpressMailCurSel - 0x5C;
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
			INT64 dObjAddr = objStartAddr + i * go_ExpressMailSize + 8;
			INT64 dMailId = R_QW(dObjAddr);
			int dMailType = R_BYTE(dObjAddr + go_ExpressMailType + 8);//ϵͳΪ5 ���Ϊ0
			int dMailState = R_BYTE(dObjAddr + go_ExpressMailState);//2Ϊ�Ѿ���ȡ����
			CString cMailSender = R_CString(dObjAddr + go_ExpressMailSenderName + 8);
			CString cMailTitle = R_CString(dObjAddr + go_ExpressMailTitle + 8);
			BOOL bNeedOpened = FALSE;
			INT64 dMoneyNum = 0;
			if (dMailState == 1)
			{
				if (dMailId && R_QW(dObjAddr + go_ExpressMailOpened) != dMailId)
				{
					bNeedOpened = TRUE;//��Ҫ��
				}
				else
				{
					dMoneyNum = R_QW(dObjAddr + go_ExpressMailMoney1 + go_ExpressMailMoney2);

				}
			}
			MailInfo_ temp;
			temp.dMailId = dMailId;
			temp.dIndex = i;
			temp.dObjAddr = dObjAddr;
			temp.dType = dMailType;
			temp.dState = dMailState;
			temp.dNeedOpen = bNeedOpened;
			temp.dMoneyNum = dMoneyNum;
			temp.������ = cMailSender;
			temp.Ctitle = cMailTitle;
			vsk.push_back(temp);
			MyTrace(L"���%d ��ַ%I64X �ʼ�ID 0x%I64X ����%d ״̬%d �Ƿ�Ҫ��%d �����%I64d ������:%s %s", i, dObjAddr, dMailId, dMailType, dMailState, bNeedOpened, (signed __int64)dMoneyNum, cMailSender, cMailTitle);
		}
	}

}

BOOL ǩ���ʼ�::bCheckExpressMailWndShow()//�жϴ�����ʾ
{
	INT64 dUiObj = UI����::getUiObjById(0xC2);//root1.arkui.frameCanvas.topHUDFrame 
	INT64 addr_first = getUiFirstAddr(dUiObj);
	INT64 addr_NoticeGroup = getChildUiAddrByStr(addr_first, L"alarmNoticeGroup");
	DWORD dMiniShow = R_W(addr_NoticeGroup + 0x6A);
	if (dMiniShow >> 0xe == 1)//�ж���ʾ
	{
		return TRUE;
	}
	return FALSE;
}
void ǩ���ʼ�::Fun_ExpressMailDel(INT64 dMailId)//ɾ���ʼ�
{
	INT64 addr_0 = R_QW(��Ϸģ�� + gb_ExpressMailList);
	W_QW(addr_0 + go_ExpressMailCurSel, dMailId);
	MainUniversalCALL2(0, 0, ��Ϸģ�� + gc_ExpressMailDel);
}
void ǩ���ʼ�::Fun_ExpressMailGetItemAll(INT64 dMailId)//��ȡ�ʼ���Ʒ
{
	INT64 addr_0 = R_QW(��Ϸģ�� + gb_ExpressMailList);
	W_QW(addr_0 + go_ExpressMailCurSel, dMailId);
	MainUniversalCALL2(0, 0, ��Ϸģ�� + gc_ExpressMailGetItemAll);

}
void ǩ���ʼ�::Fun_ExpressMailSelectByIndex(int dIndex)//��ָ���ʼ� ��������� ���ʼ�ID
{
	INT64 dUiObj = UI����::getUiObjById(0xC2);//root1.arkui.frameCanvas.topHUDFrame 
	MainUniversalCALL2(dUiObj, dIndex, ��Ϸģ�� + gc_ExpressMailSelectByIndex);

}
void ǩ���ʼ�::Fun_ExpressMailWndShow()//�����ʼ���Ϣ������ʾ
{
	INT64 dUiObj = UI����::getUiObjById(0xC2);//root1.arkui.frameCanvas.topHUDFrame 
	MainUniversalCALL2(dUiObj, 0, ��Ϸģ�� + gc_ExpressMailWndShowClick);
}

void ǩ���ʼ�::�ʼ���ȡ()
{
	vector<MailInfo_>vsk;
	get_ExpressMailList(vsk);
	if (vsk.size() > 0)
	{
		if (!bCheckExpressMailWndShow())
		{
			Fun_ExpressMailWndShow();
			Sleep(1000);
		}
		for (size_t i = 0; i < vsk.size(); i++)
		{
			if (vsk[i].dState == 1)
			{
				MyTrace(L"��ȡ[%s]=>[%s]��[%d]�ʼ�����", vsk[i].������, vsk[i].Ctitle, vsk[i].dIndex);
				Fun_ExpressMailSelectByIndex(vsk[i].dIndex);
				Fun_ExpressMailGetItemAll(vsk[i].dMailId);
				Sleep(500);
				//break;
			}
		}
	}
	get_ExpressMailList(vsk);
	if (vsk.size() > 0)
	{
		if (!bCheckExpressMailWndShow())
		{
			Fun_ExpressMailWndShow();
		}
		for (size_t i = 0; i < vsk.size(); i++)
		{
			if (vsk[i].dState == 2)
			{
				MyTrace(L"ɾ��[%s]=>[%s]��[%d]�ʼ�����", vsk[i].������, vsk[i].Ctitle, vsk[i].dIndex);
				Fun_ExpressMailSelectByIndex(vsk[i].dIndex);
				Fun_ExpressMailDel(vsk[i].dMailId);
				Sleep(500);
				//break;
			}
		}
	}
	if (bCheckExpressMailWndShow())
	{
		Fun_ExpressMailWndShow();
	}
}

bool ǩ���ʼ�::get_AttendanceList()
{
	INT64 addr_1 = R_QW(��Ϸģ�� + gb_Attendance);
	INT64 dstart = R_QW(addr_1 + go_AttendanceListStart);
	int dTotal = (R_QW(addr_1 + go_AttendanceListStart + 8) - dstart) / 0x18;
	bool �Ƿ���Ҫǩ�� = false;
	for (size_t i = 0; i < dTotal; i++)
	{

		INT64 dTabId = R_QW(dstart + i * 0x18);
		INT64 dTabObj = R_QW(dstart + i * 0x18 + 8);
		int dTabTotalDays = R_DW(dTabObj + 0x30);
		for (int k = 0; k < 2; k++)//KΪ0����� Ϊ1���ۻ�
		{

			INT64 dTabStart = R_QW(dTabObj + k * 0x18);
			int dTabTotal = (R_QW(dTabObj + k * 0x18 + 8) - dTabStart) / 0x18;
			for (size_t j = 0; j < dTabTotal; j++)//��ȡCALLҪ�õ�J
			{
				INT64 dItemInfo = dTabStart + j * 0x18;
				int dResId = R_DW(dItemInfo);
				int dNum = R_DW(dItemInfo + 4);
				int dNeedDay = R_DW(dItemInfo + 0xC);
				int IsTake = R_DW(dItemInfo + 0x10);
				if (dTabTotalDays >= dNeedDay)
				{
					if (!IsTake)
					{
						�Ƿ���Ҫǩ�� = true;
						MyTrace(L"0x%I64x ǩ�������㹻 %d ��ȡ Tab %X k %d j %d", dstart, dTabTotalDays, dTabId, k, j);
						Fun_AttendanceTake(dTabId, k, j);
						//ǩ�������㹻������ȡ
					}
				}
				INT64 dResAddr = getItemResAddrById(dResId);
				INT64 dNameAddr = R_QW(dResAddr + 0x10);
				CString csName = L"��";
				if (dNameAddr)
				{
					csName = R_CString(dNameAddr);
				}
				//MyTrace(L"��ǰTAB ID %X ��ǩ������%d ����%d ����J %d��Ʒ��ԴID %X ��������%d �Ƿ�����%d %s", dTabId, dTabTotalDays, k, j, dResId, dNeedDay, IsTake, csName);
			}

		}
	}
	return �Ƿ���Ҫǩ��;
}

void ǩ���ʼ�::Fun_AttendanceTake(INT64 dTabId, int k, int j)
{
	UCHAR dInfoAddr[0x200] = { 0 };
	W_QW((INT64)&dInfoAddr[0], dTabId);

	INT64 addr_1 = R_QW(��Ϸģ�� + gb_Attendance);
	MainUniversalCALL4(addr_1, (ULONG_PTR)dInfoAddr, k, j, ��Ϸģ�� + gc_AttendanceTake);

}

int getHotTimeEventStateByIndex(int dIndex)
{
	INT64 addr_1 = R_QW(��Ϸģ�� + gb_hottimeEvent);
	return MainUniversalCALL4_Ret(addr_1, 1, dIndex, 0, ��Ϸģ�� + gc_hottimeEventRewardCheck);
	//int dRet = -1;
	//CString cBuf;
	//dm.AsmClear();
	//dm.AsmAdd(L"mov edx,1");
	//dm.AsmAdd(MyFormat(cBuf, L"mov r8d, 0%X", dIndex));
	//dm.AsmAdd(MyFormat(cBuf, L"mov rcx, 0%I64X", addr_1));
	//dm.AsmAdd(MyFormat(cBuf, L"mov rdi, 0%I64X", gc_hottimeEventRewardCheck));
	//dm.AsmAdd(L"sub rsp,040");
	//dm.AsmAdd(L"call rdi");
	//dm.AsmAdd(L"add rsp,040");
	//dRet = (int)dm.AsmCall( 6);
	//return dRet;
}
int ǩ���ʼ�::getCurHotTimeEventIndex()//��ȡ����ȡ�Ľ�������
{
	for (DWORD i = 0; i < 4; i++)
	{
		if (getHotTimeEventStateByIndex(i) == 0)
		{
			return i;
		}
	}
	return -1;
}

void ǩ���ʼ�::Fun_hottimeEventRewardTake(int dIndex)//��ȡ����
{
	if (dIndex == -1) return;
	INT64 addr_1 = R_QW(��Ϸģ�� + gb_hottimeEvent);
	MainUniversalCALL4(addr_1, 1, dIndex, 0, ��Ϸģ�� + gc_hottimeEventRewardTake);
	/*CString cBuf;
	dm.AsmClear();
	dm.AsmAdd(L"mov edx,1");
	dm.AsmAdd(MyFormat(cBuf, L"mov r8d, 0%X", dIndex));
	dm.AsmAdd(MyFormat(cBuf, L"mov rcx, 0%I64X", addr_1));
	dm.AsmAdd(MyFormat(cBuf, L"mov rdi, 0%I64X", gc_hottimeEventRewardTake));
	dm.AsmAdd(L"sub rsp,040");
	dm.AsmAdd(L"call rdi");
	dm.AsmAdd(L"add rsp,040");
	dm.AsmCall( 6);*/
}

BOOL bCheckExpeditionRecd(WORD dLev)
{
	INT64 addr_1 = R_QW(��Ϸģ�� + gb_ExpeditionRecdList);
	int dtotal = R_DW(addr_1 + go_ExpeditionRecdStart + 8);
	INT64 objStartAddr = R_QW(addr_1 + go_ExpeditionRecdStart);
	for (size_t i = 0; i < dtotal; i++)
	{
		if (R_W(objStartAddr + i * 2) == dLev)
		{
			return TRUE;
		}
	}
	return FALSE;
}
void �ɾ���ȡ::getExpeditionInfo()//����
{
	WORD dExpeditionCurLev = R_W(��Ϸģ�� + gb_ExpeditionLev);
	for (WORD i = 0; i < dExpeditionCurLev; i++)
	{
		if (bCheckExpeditionRecd(i + 1))
		{
			//MyTrace(L"Զ��Lv%d ����ȡ", i + 1);
		}
		else
		{
			MyTrace(L"Զ��Lv%d δ��ȡ", i + 1);
			�ɾ���ȡ::Fun_ExpeditionInRecv_M(i + 1);
			Sleep(500);
		}
	}
}

void �ɾ���ȡ::Fun_ExpeditionInRecv(int dLev)//��ȡԶ���ӽ���CALL
{
	INT64 dMemCall = R_QW(��Ϸģ�� + gc_MemAlloc);
	INT64 dCall = ��Ϸģ�� + gc_ExpeditionInRecv;
	UCHAR dInfoAddr[0x200] = { 0 };
	//INT64 dInfoAddr = dm.VirtualAllocEx( 0, 0x100, 0);
	W_DW((ULONG64)&dInfoAddr[0x8], 1);
	W_DW((ULONG64)&dInfoAddr[0xC], 1);
	//dm.WriteIntAddr( dInfoAddr + 8, LEN_DWORD, 1);
	//dm.WriteIntAddr( dInfoAddr + 0xC, LEN_DWORD, 1);
	/*MainUniversalCALL4((ULONG_PTR)dInfoAddr, 0, 1, 2, dMemCall);*/
	INT64 rcxx = (ULONG_PTR)dInfoAddr;
	__asm
	{
		sub rsp, 0x40
		mov r9d, 2
		mov r8d, 1
		xor edx, edx
		mov rcx, rcxx
		mov rdi, dMemCall
		call rdi
		add rsp, 0x40
		mov edx, dLev
		mov word ptr ds : [rax] , dx
		sub rsp, 0x40
		mov rdx, rcxx
		mov rdi, dCall
		call rdi
		add rsp, 0x40
	}
	//wchar_t buf[100];
	//dm.AsmClear();
	//dm.AsmAdd(L"sub rsp,40");
	//dm.AsmAdd(L"mov r9d, 2");
	//dm.AsmAdd(L"mov r8d, 1");
	//dm.AsmAdd(L"xor edx, edx");
	//wsprintf(buf, L"mov rcx, 0%I64X", dInfoAddr);
	//dm.AsmAdd(buf);
	//wsprintf(buf, L"mov rdi, 0%I64X", dMemCall);
	//dm.AsmAdd(buf);
	//dm.AsmAdd(L"call rdi");
	//dm.AsmAdd(L"add rsp,040");
	//wsprintf(buf, L"mov edx, 0%X", dLev);
	//dm.AsmAdd(buf);
	//dm.AsmAdd(L"emit 66 89 10");//mov word ptr ds:[rax], dx
	//dm.AsmAdd(L"sub rsp,40");
	//wsprintf(buf, L"mov rdx, 0%I64X", dInfoAddr);
	//dm.AsmAdd(buf);
	//wsprintf(buf, L"mov rdi, 0%I64X", gc_ExpeditionInRecv);
	//dm.AsmAdd(buf);
	//dm.AsmAdd(L"call rdi");
	//dm.AsmAdd(L"add rsp,040");
	//dm.AsmCall( 6);
	//dm.VirtualFreeEx( dInfoAddr);
}
void �ɾ���ȡ::Fun_ExpeditionInRecv_M(int dLev)
{

	CallParam2 CALLArg;
	CALLArg.RDX = dLev;
	SendMessageTimeoutA(g_hWnd, ע����Ϣֵ, Msgid::CALLExpeditionInRecv, (LPARAM)&CALLArg, SMTO_NORMAL, 1000, 0);
	//MyTrace(L"����ֵ %d", CALLArg.�Ƿ�ɴ�);

}
INT64 get_BookCurInfoByIndex(int dIndex)
{
	INT64 addr_1 = R_QW(��Ϸģ�� + gb_BookCurInfo);
	int dtotal = R_DW(addr_1 + go_BookCurInfoStart + 8);
	INT64 dstartAddr = R_QW(addr_1 + go_BookCurInfoStart);
	if (dIndex < dtotal)
	{
		return R_QW(dstartAddr + dIndex * 8);
	}
	return 0;
}
bool Fun_getBookListReward(DWORD dMapIndex)
{

	INT64 ��_RCX = R_QW(��Ϸģ�� + ��ַ_���_����rcx);
	if (��_RCX == 0)
	{
		return false;
	}
	INT64 ��_CALL = ��Ϸģ�� + ��ַ_���_����call;
	INT64 ��_��ͷ = ��Ϸģ�� + gb_getBookReward��ͷ;
	UCHAR puff[0x100] = { 0 };


	W_QW((INT64)&puff[0], ��_��ͷ);
	W_QW((INT64)&puff[0x40 - 0x38], 0);
	W_QW((INT64)&puff[0x48 - 0x38], 0);
	W_BYTE((INT64)&puff[0x52 - 0x38], 0);
	W_BYTE((INT64)&puff[go_getBookRewardSendArg - 0x38], dMapIndex);
	MainUniversalCALL2(��_RCX, (ULONG_PTR)puff, ��_CALL);
	return true;

}
void �ɾ���ȡ::get_BookListInfo()
{
	//go_BookCurPorcess  = 0xE0;
	//go_BookCurPorcess  = 0xE4;
	//go_BookTakeedItemNum  = 0x98;
	DWORD dAdvBookIndex = getResIndexByName(L"AdvBook");
	INT64 dBookResAddr = getResAddrById(dAdvBookIndex);
	//MyTrace(L"��ַ0x%I64X \r\n", dBookResAddr);
	int dtotal = R_DW(dBookResAddr + 0x60);
	INT64 dstartAddr = R_QW(dBookResAddr + 0x58);
	for (int i = 0; i < dtotal; i++)
	{
		INT64 dObj = R_QW(dstartAddr + i * 0x10);
		BYTE dMapIndex = R_BYTE(dObj + 0x8);
		DWORD dListIndex = R_DW(dObj + 0x10);//�б�˳�� ʵ������λ�� �����Ӧ����
		INT64 dCurObjInfo = get_BookCurInfoByIndex(dMapIndex);
		if (dCurObjInfo)
		{
			int dRewardItemNum = R_DW(dCurObjInfo + go_BookRewardItemNum);//����ȡ��Ʒ����
			int dCurPorcess = R_DW(dCurObjInfo + go_BookCurPorcess);//��ǰ����
			int dMaxPorcess = R_DW(dCurObjInfo + go_BookCurPorcess + 4);//�ܽ���
			int dTakeedNum = R_DW(dCurObjInfo + go_BookTakeedItemNum + 8);//����ȡ��Ʒ����
			if (dTakeedNum > 10)
			{
				continue;
			}
			if (dTakeedNum < dRewardItemNum && dCurPorcess != 0)
			{
				MyTrace(L"�б�˳��%d %X 0x%I64X �ܽ�������%d  ����ȡ����%d ����ֵ%d/%d\r\n", dListIndex, dMapIndex, dCurObjInfo, dRewardItemNum, dTakeedNum, dCurPorcess, dMaxPorcess);
				Fun_getBookListReward(dMapIndex);
				Sleep(500);
				//С��˵���п���ȡ�� ����˵����ȡ����
			}

		}


	}
}




