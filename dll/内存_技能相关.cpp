#include "�ڴ�_�������.h"
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
	INT64 objStartAddr = R_QW(dSkillResAddr + 0x68);//���������ַ
	INT64 indexStartAddr = R_QW(dSkillResAddr + 0xA4);//���������ַ
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
			if (dNextIndex == 0xFFFFFFFF)//Ϊ-1����ѭ��
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

DWORD ����::getRoleCurSkillPoints()
{
	INT64 addr_1 = R_QW(��Ϸģ�� + gb_AttrList);
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
	int dNeedPoints = getSkillNextLevNeedPoints(dSkillId, dSkillLev + 1);//�¼�20220312
	BOOL bCanUpGrade = FALSE;
	if (dNeedPoints)//�¼�20220312
	{
		if (dNeedPoints <= ����::getRoleCurSkillPoints())
		{
			bCanUpGrade = TRUE;
		}
	}
	DWORD dSkillD1 = R_BYTE(dSkillInfo + 0x5);//�²��츳1
	DWORD dSkillD2 = R_BYTE(dSkillInfo + 0x6);
	DWORD dSkillD3 = R_BYTE(dSkillInfo + 0x7);
	DWORD dRange = R_W(dSkillInfo + 0x1C + 8);
	DWORD dSkillType = R_BYTE(dSkillInfo + 0x34 + 8);
	INT64 addr = R_QW(dSkillInfo + 0x10);
	INT64 dNameAddr = R_QW(addr + 0x10);
	CString csName = L"��";
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
		//swprintf(buf, L"��ַ0x%I64X ID %X ����%d %s �ȼ�%d ��Χ%d ��������%d ������\r\n �츳1:%d �츳2:%d �츳3:%d", dSkillInfo, dSkillId, dSkillType, csName, dSkillLev, dRange, dNeedPoints, dSkillD1, dSkillD2, dSkillD3);

	}
	else
	{
		temp.dCanUpGrade = false;
		//swprintf(buf, L"��ַ0x%I64X ID %X ����%d %s �ȼ�%d ��Χ%d ��������%d ��������\r\n �츳1:%d �츳2:%d �츳3:%d", dSkillInfo, dSkillId, dSkillType, csName, dSkillLev, dRange, dNeedPoints, dSkillD1, dSkillD2, dSkillD3);

	}
	temp.objBase = dSkillObj;
	temp.InfoObj = dSkillInfo;
	temp.dSkillId = dSkillId;
	temp.dSkillType = dSkillType;
	temp.���� = csName;
	temp.dUpGradeNeedPoint = dNeedPoints;
	temp.dSkillLev = dSkillLev;
	temp.�츳1 = dSkillD1;
	temp.�츳2 = dSkillD2;
	temp.�츳3 = dSkillD3;
	temp.dRange = dRange;
	temp.�Ƿ���ȴ = ����::��ȴ�ж�(dSkillObj);
	////MyTrace(L"2.5");
	if (temp.dSkillId == 37100)//ħ���ͷ�
	{
		temp.��λ = 8;
	}
	else if (temp.dSkillId == 37110)//˲��
	{
		temp.��λ = 9;
	}
	else
	{
		temp.��λ = ͨ������ID��ȡ����(dSkillId);
	}
	////MyTrace(L"3");
	////MyTrace(L"��ַ0x%I64X ID %X ����%d %s \r\n", dSkillInfo, dSkillId, dSkillType, temp.����);
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
void ����::get_SkillList(vector<SkillInfo_>& vsk)
{
	INT64 addr_1 = R_QW(��Ϸģ�� + gb_ActorList);
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
		temp.��λ = i;
		temp.dId = dSkillId;
		temp.type = 1;
		vsk.push_back(temp);
		////MyTrace(L"ҳ��%d ������%d ��ַ0x%I64X  id %X\r\n", dPage, i, dSkillArray, dSkillId);
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
void geQuickSlotStateByType(DWORD dSlotType, vector<ShortCutInfo_>& vsk)//ս�����ܴ�0
{
	INT64 dUiObj = UI����::getUiObjById(0x2D);//quickSlotFrame
	//MyTrace(L"����obj 0x%I64X", dUiObj);
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
					bCollView = 1;//��ȴ��
				}
				if (bCollView == 1)
				{
					vsk[i].�Ƿ���ȴ = false;
				}
				else
				{
					vsk[i].�Ƿ���ȴ = true;
				}

				vsk[i].����״̬ = dStateValue;
			MyTrace(L"��ݼ�����%d 0x%I64X ��ȴ��ʾ%X  ״ֵ̬ %d \r\n", i, dCoolAddr, bCollView, dStateValue);//dStateValue ����Ϊ0 ��������Ϊ2 ��������Ϊ3
			}
		}
	}

}
DWORD ����::get_SkillShortCurPage()
{
	INT64 addr_1 = R_QW(��Ϸģ�� + gb_ShortKey + 8);
	BYTE dCurPage = R_BYTE(addr_1 + 0x9C);
	return dCurPage;
}
DWORD ����::SKLLADDR(DWORD ID)
{
	INT64 addr_1 = R_QW(R_QW(R_QW(R_QW(��Ϸģ�� + ��ַ_����_�����)+0xA8))+0x28);
	DWORD a=R_DW(addr_1 + ID * 5 * 4 + 4);
	return a;
}





void ����::get_SkillShortList(vector<ShortCutInfo_>& vsk)
{
	vsk.clear();
	INT64 addr_1 = R_QW(��Ϸģ�� + gb_ShortKey + 8);
	BYTE dCurPage = R_BYTE(addr_1 + 0x9C);
	INT64 addr_2 = R_QW(addr_1 + 0xA8);
	INT64 addr = R_QW(addr_2 + 8);
	TravelTreeSkillShort(addr, vsk, dCurPage);
	geQuickSlotStateByType(dCurPage, vsk);
}


void ����::get_SkillShortList1(vector<ShortCutInfo_>& vsk, DWORD xxx)
{
	vsk.clear();
	INT64 addr_1 = R_QW(��Ϸģ�� + gb_ShortKey + 8);
	BYTE dCurPage = R_BYTE(addr_1 + 0x9C);
	INT64 addr_2 = R_QW(addr_1 + 0xA8);
	INT64 addr = R_QW(addr_2 + 8);
	TravelTreeSkillShort(addr, vsk, dCurPage);
	geQuickSlotStateByType(xxx, vsk);


}


void ����::get_RightShortList(vector<ShortCutInfo_>& vsk)
{
	vsk.clear();
	ShortCutInfo_ temp;
	INT64 addr_1 = R_QW(��Ϸģ�� + gb_ShortKey);
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
			temp.���� = Name;
			temp.��λ = i + 1;
			vsk.push_back(temp);
			//MyTrace(L"dStartAddr 0x%I64X %d�� ��Ʒid %X %s\r\n", dStartAddr, i + 1, dItemId, Name);
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
			temp.���� = Name;
			temp.��λ = i + 1;
			vsk.push_back(temp);
			//MyTrace(L"%d�� ս����Ʒid %X %s \r\n", i + 1, dItemId, Name);
		}

	}
}

DWORD ͨ������ID��ȡ����(DWORD SKILLID)
{
	vector<ShortCutInfo_>vsk;
	����::get_SkillShortList(vsk);
	for (size_t i = 0; i < vsk.size(); i++)
	{
		if (SKILLID == vsk[i].dId)
		{
			return vsk[i].��λ;
		}
	}
	return -1;
}
bool ����::��ȴ�ж�(INT64 ���ܶ���ָ��)
{
	float ��_�жϱ�־ = R_Float(���ܶ���ָ�� + 36);
	if (��_�жϱ�־ == 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

//int ����::ȡ��ʹ�ü��ܵ���()
//{
//	INT64 v1 = R_QW(R_QW(��Ϸģ�� + gb_AttrList) + 220);
//	INT64 v2 = R_QW(v1 + ƫ��_����_���ܵ���);
//}
//void ����::��������(DWORD ����ID,DWORD Ŀ��ȼ�)
//{
//	INT64 ��_rcx=
//}

bool ����::д�������굽���(����_ ��������)
{
	INT64 ����ַ = R_QW(R_QW(��Ϸģ�� + ��ַ_���_����) + 176) + ƫ��_���_����;
	if (����ַ == 0)
	{
		return false;
	}
	if (IsBadReadPtr((VOID*)����ַ, 8))
	{
		return false;
	}
	INT64 ����ַy = ����ַ + 4;
	INT64 ��Ϸ����ת���CALL = ��Ϸģ�� + ��ַ_���_��Ϸ����ת���call;
	INT64 ��_���_��Ϸ����ת���rcx = ��Ϸģ�� + ��ַ_���_��Ϸ����ת���rcx;
	//����_ ��_����ָ��;
	UCHAR pBuff[0x100] = { 0 };
	W_Float((ULONG64)&pBuff[0], ��������.x);
	W_Float((ULONG64)&pBuff[4], ��������.y);
	W_Float((ULONG64)&pBuff[8], ��������.z);
	INT64 ��_����ָ�� = (ULONG64)&pBuff;
	//��_����ָ�� = ��������;
	/*INT64 ��_����ָ�� = INT64(�����ڴ�2(HANDLE(-1), 100));
	W_Float(��_����ָ��, ��������.x);
	W_Float(��_����ָ��+4, ��������.y);
	W_Float(��_����ָ�� + 8, ��������.z);
	INT64 ��_�����ָ�� = INT64(�����ڴ�2(HANDLE(-1), 100));*/
	UCHAR pBuff2[0x100] = { 0 };
	INT64 ��_�����ָ�� = (INT64)&pBuff2;
	MainUniversalCALL4(��_���_��Ϸ����ת���rcx, ��_����ָ��, ��_�����ָ��, 0, ��Ϸ����ת���CALL);
	int intValue = static_cast<int>(std::round(R_Float(��_�����ָ��)));
	int x = intValue;
	intValue = static_cast<int>(std::round(R_Float(��_�����ָ��+4)));
	int y = intValue;
		W_DW(����ַ,x);
		W_DW(����ַ+4, y);

	return true;
}

bool ����::д�������굽���2(float fx, float fy, float fz)
{
	INT64 dMuoseInfo = R_QW(��Ϸģ�� + gb_MouseInfo);
	if (dMuoseInfo == 0)
	{
		return false;
	}
	if (IsBadReadPtr((VOID*)dMuoseInfo, 8))
	{
		return false;
	}
	INT64 ��Ϸ����ת���CALL = ��Ϸģ�� + ��ַ_���_��Ϸ����ת���call;
	INT64 ��_���_��Ϸ����ת���rcx = ��Ϸģ�� + ��ַ_���_��Ϸ����ת���rcx;
	//����_ ��_����ָ��;
	UCHAR pBuff[0x100] = { 0 };
	W_Float((ULONG64)&pBuff[0], fx);
	W_Float((ULONG64)&pBuff[4], fy);
	W_Float((ULONG64)&pBuff[8], fz);
	INT64 ��_����ָ�� = (ULONG64)&pBuff;
	//��_����ָ�� = ��������;
	/*INT64 ��_����ָ�� = INT64(�����ڴ�2(HANDLE(-1), 100));
	W_Float(��_����ָ��, ��������.x);
	W_Float(��_����ָ��+4, ��������.y);
	W_Float(��_����ָ�� + 8, ��������.z);
	INT64 ��_�����ָ�� = INT64(�����ڴ�2(HANDLE(-1), 100));*/
	UCHAR pBuff2[0x100] = { 0 };
	INT64 ��_�����ָ�� = (INT64)&pBuff2;
	MainUniversalCALL4(��_���_��Ϸ����ת���rcx, ��_����ָ��, ��_�����ָ��, 0, ��Ϸ����ת���CALL);
	int dPx = R_DW(��_�����ָ��);
	int dPy = R_DW(��_�����ָ�� + 4);
	W_DW(dMuoseInfo + go_MousePoint, dPx);
	W_DW(dMuoseInfo + go_MousePoint + 4, dPy);
	//�ͷ��ڴ�2(HANDLE(-1), (LPVOID)��_�����ָ��, 100);
	//�ͷ��ڴ�2(HANDLE(-1), (LPVOID)��_����ָ��, 100);
	//CALL4(��_���_��Ϸ����ת���rcx, ULONG_PTR(pBuff), (INT64)&��_�����ָ��, 0,��Ϸ����ת���CALL);
	/*//MyTrace(L"ת����� %d,%d", R_DW(��_�����ָ��), R_DW(��_�����ָ�� + 4));
	W_DW(����ַ, R_DW(��_�����ָ��));
	W_DW(����ַ + 4, R_DW(��_�����ָ�� + 4));*/
	return true;
}

DWORD ����::���ܼ���ת��(int ��λ)
{
	if (��λ == 0)//Q
	{
		return DWORD('Q');
	}
	else if (��λ == 1)//W
	{
		return DWORD('W');
	}
	else if (��λ == 2)//E
	{
		return DWORD('E');
	}
	else if (��λ == 3) // R
	{
		return DWORD('R');
	}
	else if (��λ == 4) // A
	{
		return DWORD('A');
	}
	else if (��λ == 5) // S
	{
		return DWORD('S');
	}
	else if (��λ == 6) // D
	{
		return DWORD('D');
	}
	else if (��λ == 7) // F
	{
		return DWORD('F');
	}
	else if (��λ == 8) // Z
	{
		return DWORD('Z');
	}
	else if (��λ == 9) // X
	{
		return DWORD('X');
	}
	return 0;
}

DWORD ����::�Ҳ��ݼ�����ת��(int type, int ��λ)
{
	if (type == 2)
	{
		if (��λ == 1)//Q
		{
			return DWORD(VK_F1);
		}
		else if (��λ == 2)//W
		{
			return DWORD('5');
		}
		else if (��λ == 3)//E
		{
			return DWORD('6');
		}
		else if (��λ == 4) // R
		{
			return DWORD('7');
		}
		else if (��λ == 5) // A
		{
			return DWORD('8');
		}
		else if (��λ == 6) // S
		{
			return DWORD('9');
		}
	}
	if (type == 1)
	{
		if (��λ == 1)//Q
		{
			return DWORD('1');
		}
		else if (��λ == 2)//W
		{
			return DWORD('2');
		}
		else if (��λ == 3)//E
		{
			return DWORD('3');
		}
		else if (��λ == 4) // R
		{
			return DWORD('4');
		}

	}
	return 0;
}

void ����::�����ͷ�(����_ ��������)
{
	vector<SkillInfo_>��������;
	����::get_SkillList(��������);
	����::�������();
	����::д�������굽���(��������);
	//����::д�������굽���2(��������.x, ��������.y, ��������.z);
	//����::д�������굽���(��������);
	bool �Ƿ��ͷż��� = false;
	for (size_t i = 0; i < ��������.size(); i++)
	{
		if (��������[i].�Ƿ���ȴ == true && ��������[i].��λ != -1 && ��������[i].��λ != 8 && ��������[i].��λ != 9)
		{
			//MyTrace(L"ʹ�ü��� %s %d", ��������[i].����, ��������[i].��λ);
			if (��������[i].dSkillId == 37340)//�����ٻ�
			{
				UI����::�ڴ水��(����::���ܼ���ת��(��������[i].��λ), 0);
				Sleep(5000);
				UI����::�ڴ水��(����::���ܼ���ת��(��������[i].��λ), 1);
				�Ƿ��ͷż��� = true;
				break;
			}
			else if (��������[i].dSkillId == 37240)//�����ٻ�
			{
				UI����::�ڴ水��(����::���ܼ���ת��(��������[i].��λ));
				Sleep(800);
				UI����::�ڴ水��(����::���ܼ���ת��(��������[i].��λ));
				Sleep(500);
				�Ƿ��ͷż��� = true;
				break;
			}
			else if (��������[i].dSkillId == 37270) //�췣;
			{
				UI����::�ڴ水��(����::���ܼ���ת��(��������[i].��λ));
				Sleep(300);
				UI����::�ڴ水��(����::���ܼ���ת��(��������[i].��λ));
				Sleep(3000);
				�Ƿ��ͷż��� = true;
				break;
			}
			else
			{
				UI����::�ڴ水��(����::���ܼ���ת��(��������[i].��λ));
				�Ƿ��ͷż��� = true;
				Sleep(500);
				break;
			}
		}
	}
	if (�Ƿ��ͷż��� == false)
	{
		UI����::�ڴ水��(DWORD('C'));
		Sleep(300);
	}
	����::����������();
}

void ����::�������()
{
	char У��[] = { 0xCC };
	д�ڴ��ֽڼ�((HANDLE)-1, (LPVOID)(��Ϸģ�� + ��ַ_���_���д���ַ), LPVOID(&У��), 1);
}
void ����::����������()
{
	char У��2[] = { 0xE8 };
	д�ڴ��ֽڼ�((HANDLE)-1, (LPVOID)(��Ϸģ�� + ��ַ_���_���д���ַ), LPVOID(&У��2), 1);
}
void ����::�����ͷ�2(����_ ��������)
{
	vector<ShortCutInfo_>��������;
	����::get_SkillShortList(��������);
	����::�������();
	����::д�������굽���(��������);
	//����::д�������굽���2(��������.x, ��������.y, ��������.z);
	//����::д�������굽���(��������);
	bool �Ƿ��ͷż��� = false;

	for (size_t i = 0; i < ��������.size(); i++)
	{
		if (��������[i].dPage == 0)
		{
			if (��������[i].dId > 0 && ��������[i].�Ƿ���ȴ == true && ��������[i].����״̬ == 0 && ��������[i].��λ != -1 && ��������[i].��λ != 8 && ��������[i].��λ != 9)
			{
				//MyTrace(L"ʹ�ü��� %d", ��������[i].��λ);
				if (��������[i].dId == 37340)//�����ٻ�
				{
					UI����::�ڴ水��(����::���ܼ���ת��(��������[i].��λ), 0);
					Sleep(5000);
					UI����::�ڴ水��(����::���ܼ���ת��(��������[i].��λ), 1);
					�Ƿ��ͷż��� = true;
					break;
				}
				else if (��������[i].dId == 37240)//�����ٻ�
				{
					UI����::�ڴ水��(����::���ܼ���ת��(��������[i].��λ));
					Sleep(800);
					UI����::�ڴ水��(����::���ܼ���ת��(��������[i].��λ));
					Sleep(500);
					�Ƿ��ͷż��� = true;
					break;
				}
				else if (��������[i].dId == 37270) //�췣;
				{
					UI����::�ڴ水��(����::���ܼ���ת��(��������[i].��λ));
					Sleep(300);
					UI����::�ڴ水��(����::���ܼ���ת��(��������[i].��λ));
					Sleep(3000);
					�Ƿ��ͷż��� = true;
					break;
				}
				else
				{
					UI����::�ڴ水��(����::���ܼ���ת��(��������[i].��λ));
					�Ƿ��ͷż��� = true;
					Sleep(500);
					break;
				}
			}
		}
		else
		{
			if (��������[i].��λ == 3)
			{
				continue;
			}
			else
			{
				if (��������[i].dId == 0x174A8)
				{
					UI����::�ڴ水��(����::���ܼ���ת��(��������[i].��λ), 0);
					Sleep(1500);
					UI����::�ڴ水��(����::���ܼ���ת��(��������[i].��λ), 1);
					�Ƿ��ͷż��� = true;
					Sleep(500);
					break;
				}

				//MyTrace(L"dpage %d ʹ�ü��� %d ID %X", ��������[i].dPage, ��������[i].��λ, ��������[i].dId);
				UI����::�ڴ水��(����::���ܼ���ת��(��������[i].��λ));
				�Ƿ��ͷż��� = true;
				Sleep(300);
				continue;
			}
		}

	}
	if (�Ƿ��ͷż��� == false)
	{
		if (����::get_SkillShortCurPage() == 0)
		{
			UI����::�ڴ水��(DWORD('C'));
			Sleep(300);
		}

	}
	����::����������();
}
void ���Դ��(INT64 ����obj)
{
	clock_t ���ʱ�� = ȡ����ʱ��();
	while (ȡ����ʱ��() - ���ʱ�� <= 1 * 60 * 1000)
	{
		objInfo_ ������Ϣ = ����::getActorInfo(����obj);
		if (������Ϣ.dCurHp <= 0)
		{
			//MyTrace(L"%s ���������� %0.3f, %0.3f, %0.3f", ������Ϣ.wName, ������Ϣ.����.x, ������Ϣ.����.y, ������Ϣ.����.z);
			break;
		}
		else
		{
			//MyTrace(L"�������� %s %d/%d %0.3f, %0.3f, %0.3f", ������Ϣ.wName, ������Ϣ.dCurHp, ������Ϣ.dMaxHp, ������Ϣ.����.x, ������Ϣ.����.y, ������Ϣ.����.z);
			����::�����ͷ�(������Ϣ.����);
		}
	}
}

SkillInfo_ ����::ȡ��ָ��������Ϣ(DWORD SkillID, vector<SkillInfo_>& vsk)
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

bool ����::CALL_���������츳(DWORD ����ID, DWORD �ȼ�, DWORD ����1, DWORD ����2, DWORD ����3)
{
	//MyTrace(L"�������� %d �ȼ� %d", ����ID, �ȼ�);
	INT64 ��_RCX = R_QW(��Ϸģ�� + ��ַ_���_����rcx);
	if (��_RCX == 0)
	{
		return false;
	}
	INT64 ��_CALL = ��Ϸģ�� + ��ַ_���_����call;
	INT64 ��_��ͷ = ��Ϸģ�� + ��ַ_����_�������ܰ�ͷ;
	UCHAR puff[0x1000] = { 0 };
	//W_QW((INT64)&puff[0], ��_��ͷ);
	//W_QW((INT64)&puff[8], 0);
	//W_QW((INT64)&puff[16], 0);
	//W_BYTE((INT64)&puff[24], 1);
	//W_DW((INT64)&puff[26], ����ID);
	//W_BYTE((INT64)&puff[33], �ȼ�);
	//W_BYTE((INT64)&puff[0x1E], ����1);
	//W_BYTE((INT64)&puff[0x1F], ����2);
	//W_BYTE((INT64)&puff[0x20], ����3);

	/*W_QW((INT64)&puff[0], ��_��ͷ);
	W_QW((INT64)&puff[8], 0);
	W_QW((INT64)&puff[16], 0);
	W_BYTE((INT64)&puff[24], 1);
	W_DW((INT64)&puff[0x1A], ����ID);
	W_BYTE((INT64)&puff[0x1E], �ȼ�);
	W_BYTE((INT64)&puff[0x1F], ����1);
	W_BYTE((INT64)&puff[0x20], ����2);
	W_BYTE((INT64)&puff[0x21], ����3);*/
	/*W_QW((INT64)&puff[0], ��_��ͷ);
	W_QW((INT64)&puff[8], 0);
	W_QW((INT64)&puff[16], 0);
	W_BYTE((INT64)&puff[24], 1);
	W_DW((INT64)&puff[0x1B], ����ID);
	W_BYTE((INT64)&puff[0x1A], �ȼ�);
	W_BYTE((INT64)&puff[0x1F], ����1);
	W_BYTE((INT64)&puff[0x20], ����2);
	W_BYTE((INT64)&puff[0x21], ����3);*/
	for (size_t i = 0; i <= 15; i++)
	{
		W_QW((INT64)&puff[0x28 + i * 0xE], 0x100010001);
		//W_Word((INT64)&puff[0x21 + i * 0xE + 4], 1);
	}
	W_QW((INT64)&puff[0], ��_��ͷ);
	W_QW((INT64)&puff[8], 0);
	W_QW((INT64)&puff[16], 0);
	W_BYTE((INT64)&puff[0x18], 1);
	W_BYTE((INT64)&puff[0x20], �ȼ�);
	W_DW((INT64)&puff[0x21], ����ID);
	W_BYTE((INT64)&puff[0x25], ����1);
	W_BYTE((INT64)&puff[0x26], ����2);
	W_BYTE((INT64)&puff[0x27], ����3);



	//W_DW((INT64)&puff[0x110], 0xC0);
	MainUniversalCALL2(��_RCX, (ULONG_PTR)puff, ��_CALL);

	return true;
}
bool ����::�Զ���������(DWORD ����ID, DWORD �ȼ�, DWORD ����1, DWORD ����2, DWORD ����3, DWORD ���ȵȼ�)
{
	////MyTrace(L"�Զ���������1");
	vector<SkillInfo_>vsk;
	get_SkillList(vsk);
	////MyTrace(L"�Զ���������2");
	SkillInfo_ SKILL;
	SKILL = ȡ��ָ��������Ϣ(����ID, vsk);

	if (SKILL.dSkillId = ����ID)
	{
		//MyTrace(L"�Զ��������� SKill %d  %d �츳1 %d �츳2 %d �츳3 %d", SKILL.dSkillId, SKILL.dSkillLev, SKILL.�츳1, SKILL.�츳2, SKILL.�츳3);
		if (SKILL.dSkillLev >= 4)
		{
			if (SKILL.�츳1 != ����1)
			{
				����::CALL_���������츳(SKILL.dSkillId, SKILL.dSkillLev, ����1, SKILL.�츳2, SKILL.�츳3);
			}
		}
		if (SKILL.dSkillLev >= 7)
		{
			if (SKILL.�츳2 != ����2)
			{
				����::CALL_���������츳(SKILL.dSkillId, SKILL.dSkillLev, ����1, ����2, SKILL.�츳3);
			}
		}
		if (SKILL.dSkillLev == 10)
		{
			if (SKILL.�츳3 != ����3)
			{
				����::CALL_���������츳(SKILL.dSkillId, SKILL.dSkillLev, ����1, ����2, ����3);
			}
		}

		if (SKILL.dCanUpGrade == true && SKILL.dSkillLev < �ȼ�)
		{
			//MyTrace(L"�������� %s", SKILL.����);
			����::CALL_���������츳(SKILL.dSkillId, SKILL.dSkillLev + 1, SKILL.�츳1, SKILL.�츳2, SKILL.�츳3);
			return false;
		}
		if (SKILL.dSkillLev < ���ȵȼ�)
		{
			return false;
		}

	}
	//Ů��
	return true;
}
void  ����::�Զ�����Ů�׼���()
{
	if (!����::�Զ���������(37200, 10, 2, 2, 1, 7))
	{
		return;
	}
	if (!����::�Զ���������(37320, 10, 3, 1, 1))
	{
		return;
	}
	if (!����::�Զ���������(37310, 10, 1, 1, 1))
	{
		return;
	}
	if (!����::�Զ���������(37210, 10, 1, 1, 1))
	{
		return;
	}

	if (!����::�Զ���������(37270, 10, 3, 2, 1))
	{
		return;
	}
	if (!����::�Զ���������(37230, 10, 3, 3, 1))
	{
		return;
	}
	if (!����::�Զ���������(37260, 10, 3, 3, 1))
	{
		return;
	}
	if (!����::�Զ���������(37280, 10, 3, 3, 1))
	{
		return;
	}
	if (!����::�Զ���������(37220, 10, 1, 1, 1))
	{
		return;
	}
}

void ����::CALL_��ݼ����ܰڷ�(DWORD ����ID, DWORD λ��)
{
	INT64 dRCX = R_QW(��Ϸģ�� + gb_ShortKey + 0x8);
	INT64 dCALL = ��Ϸģ�� + gc_SkillShortKeySet;
	DWORD dCurIndex = 0xFFFFFFFF;//�Ӽ������Ϸ�
	MainUniversalCALL6(dRCX, dCurIndex, 0, λ��, ����ID, 0, dCALL);
}
DWORD ����::�жϼ��ܵȼ�(DWORD ����ID)
{
	vector<SkillInfo_>vsk;
	get_SkillList(vsk);
	for (size_t i = 0; i < vsk.size(); i++)
	{
		if (vsk[i].dSkillId == ����ID)
		{
			return vsk[i].dSkillLev;
		}
	}
	return 0;
}

void ����::�ڷ���ѧϰ����()
{
	if (����::get_SkillShortCurPage() == 0)
	{
		////MyTrace(L"�жϼ��ܼӵ�ʱ��2");
		vector<ShortCutInfo_>vsk;
		����::get_SkillShortList(vsk);
		////MyTrace(L"�жϼ��ܼӵ�ʱ��3");
		for (size_t i = 0; i < vsk.size(); i++)
		{
			if (i == 0)
			{
				if (vsk[i].dId != 37260)
				{
					if (����::�жϼ��ܵȼ�(37260) > 0)
					{
						//MyTrace(L"�жϼ��ܼӵ�ʱ��37260");
						����::CALL_��ݼ����ܰڷ�(37260, i);
					}
				}
			}
			if (i == 1)
			{
				if (vsk[i].dId != 37280)
				{
					if (����::�жϼ��ܵȼ�(37280) > 0)
					{
						//MyTrace(L"�жϼ��ܼӵ�ʱ��37280");
						����::CALL_��ݼ����ܰڷ�(37280, i);
					}
				}
			}
			if (i == 2)
			{
				if (vsk[i].dId != 37320)
				{
					if (����::�жϼ��ܵȼ�(37320) > 0)
					{
						//MyTrace(L"�жϼ��ܼӵ�ʱ��37320");
						����::CALL_��ݼ����ܰڷ�(37320, i);
					}
				}
			}
			if (i == 3)
			{
				if (vsk[i].dId != 37310)
				{
					if (����::�жϼ��ܵȼ�(37310) > 0)
					{
						//MyTrace(L"�жϼ��ܼӵ�ʱ��37310");
						����::CALL_��ݼ����ܰڷ�(37310, i);
					}
				}
			}
			if (i == 4)
			{
				if (vsk[i].dId != 37210)
				{
					if (����::�жϼ��ܵȼ�(37210) > 0)
					{
						//MyTrace(L"�жϼ��ܼӵ�ʱ��37210");
						����::CALL_��ݼ����ܰڷ�(37210, i);
					}
				}
			}
			if (i == 5)
			{
				if (vsk[i].dId != 37220)
				{
					if (����::�жϼ��ܵȼ�(37220) > 0)
					{
						//MyTrace(L"�жϼ��ܼӵ�ʱ��37220");
						����::CALL_��ݼ����ܰڷ�(37220, i);
					}
				}
			}
			if (i == 6)
			{
				if (vsk[i].dId != 37230)
				{
					if (����::�жϼ��ܵȼ�(37230) > 0)
					{
						//MyTrace(L"�жϼ��ܼӵ�ʱ��37230");
						����::CALL_��ݼ����ܰڷ�(37230, i);
					}
				}
			}
			if (i == 7)
			{
				if (vsk[i].dId != 37200)
				{
					if (����::�жϼ��ܵȼ�(37200) > 0)
					{
						//MyTrace(L"�жϼ��ܼӵ�ʱ��37200");
						����::CALL_��ݼ����ܰڷ�(37200, i);
					}
				}
			}

		}
		//Sleep(2000);
		//MyTrace(L"��������");
		����::�Զ�����Ů�׼���();
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
	
		ULONG64 dwManID = R_QW(R_QW(��Ϸģ��+��ַ_����_����) + 0xA0);
		ULONG64 dwEcx = dwManID + go_UseSkillOffset;
		BYTE Buf[500] = {0};
		if (dwManID != 0)
		{
			ULONG64 dwSecBase = R_QW(dwManID + go_ManPoBaseOffset);
			float px = R_Float(dwSecBase + ƫ��_����);
			float py = R_Float(dwSecBase + ƫ��_����+4);
			float pz = R_Float(dwSecBase + ƫ��_����+8);
			float AngleX;
			float AngleY;
			float AngleZ;
			CalcAngel(px,py,pz,x,y,z,AngleX,AngleY,AngleZ);
			//
			*(ULONG64*)(Buf + 0x0) = 0x240044040;
			//����float
			*(float*)(Buf + 0x24) = AngleX;
			*(float*)(Buf + 0x28) = AngleY;
			//�������
			*(float*)(Buf + 0x30) = px;
			*(float*)(Buf + 0x34) = py;
			*(float*)(Buf + 0x38) = pz;
			*(float*)(Buf + 0x3C) = px;
			*(float*)(Buf + 0x40) = py;
			*(float*)(Buf + 0x44) = pz;
			//��������float
			*(float*)(Buf + 0x54) = AngleX;
			*(float*)(Buf + 0x58) = AngleY;
			//����
			*(BYTE*)(Buf + 0xA0) = 1;
			*(BYTE*)(Buf + 0xA4) = 1;//A0 �� A4 Ҫ��ͬ
			*(BYTE*)(Buf + 0xDC) = 1;
			*(int*)(Buf + 0x10C) = -1;
			*(DWORD*)(Buf + 0x114) = dwSkillID;
			*(DWORD*)(Buf + 0x118) = -1;//���ܵȼ� 0 ����
			MainUniversalCALL4(dwEcx, (ULONG64)Buf, 0, 0, ��Ϸģ�� + gc_UseSkillCall);
			//ResetArgs();
			//MyRcx = dwEcx;
			//MyRdx = (ULONG64)Buf;
			//MyR8 = 0;
			//MyAsmCall = UseSkillCall;
			//DoCall();//ʹ�ü���
		}
	
}