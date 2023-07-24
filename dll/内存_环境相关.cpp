#include "�ڴ�_�������.h"
vector<DWORD>���Ȳɼ�ID;
bool flessmark(const objInfo_& o1, const objInfo_& o2)
{
	return o1.fDis < o2.fDis;

}
BOOL bCheckActorHide(INT64 dObjAddr)
{
	int dtotal = R_DW(dObjAddr + go_hj_HideState + 8);
	INT64 dstart = R_QW(dObjAddr + go_hj_HideState);
	for (int i = 0; i < dtotal; i++)
	{
		int dVaule = R_DW(dstart + i * 4);
		//MyTrace(L"�ж�����ֵ%d", dVaule);
		if (dVaule == 2 || dVaule == 4)
		{
			return TRUE;
		}
	}
	return FALSE;
}

BOOL bCheckActorEnemy(INT64 dObjAddr)
{
	INT64 addr_1 = R_QW(dObjAddr + 0x8C);
	DWORD dValue = R_BYTE(addr_1);//���ֽ�
	if (dValue == 0)//����
	{
		return TRUE;
	}
	return FALSE;
}

BYTE bCheckActorEnemy1(INT64 dObjAddr)
{
	INT64 addr_1 = R_QW(dObjAddr + 0x8C);
	DWORD dValue = R_BYTE(addr_1);//���ֽ�
	return dValue;


}



objInfo_ ����::getActorInfo(INT64 dObjAddr)
{
	//MyTrace(L"getActorInfo 0");
	objInfo_ bi;
	//memset(&bi, 0, sizeof(objInfo_));
	bi.objBase = dObjAddr;
	bi.dObjId = R_DW(dObjAddr + 0x14);
	bi.dResId = R_DW(dObjAddr + 0x2C);
	bi.ModId = R_DW(dObjAddr + 0x30);
	INT64 dNameAddr = R_QW(dObjAddr + 0x1C);
	CString csName = L"��";
	if (dNameAddr)
	{
		bi.wName = R_CString(dNameAddr);;//dm.ReadStringAddr(dNameAddr,1,0); //
		//wcscpy(bi.wName, csName.GetBuffer(0));
		//bi.wName = csName;
	}
	bi.dType = R_BYTE(dObjAddr + 0x34);
	//MyTrace(L"getActorInfo 1 ���� %s  resId %d type %d", bi.wName,bi.dResId,bi.dType);

	if (bi.dType == 6 || bi.dType == 7 || bi.dType == 8 || bi.dType == 9)
	{
		//bi.dResAddr = dm.ReadIntAddr(dObjAddr + 0xB48,3);
		//bi.dResType = dm.ReadIntAddr(bi.dResAddr + 0x36,6);
		bi.dResType = R_BYTE(dObjAddr + 0xD18);
		//bi.dResShow = R_BYTE(dObjAddr + 0xD15);
		//MyTrace(L"getActorInfo �Ƿ�");
		bi.dResShow = CALL_�����Ƿ�ɽ���(dObjAddr);
		//MyTrace(L"getActorInfo �ɽ���");
		bi.dResOpen = R_BYTE(dObjAddr + 0xD16);
		bi.dPortalOpen = R_BYTE(dObjAddr + go_PortalOpen);
	}
	if (bi.dType == 11)
	{
		bi.dIsDead = R_BYTE(dObjAddr + ƫ��_����_��������Ƿ�����_����11);
	}
	if (bi.dType == 7)
	{
		bi.dIsDead = R_BYTE(dObjAddr + ƫ��_����_��������Ƿ�����_����7);
	}
	if (bi.dType == 3 || bi.dType == 11)
	{
		bi.dResAddr = getNpcResAddrById(bi.dResId);
		if (bi.dResAddr)
		{
			INT64 dTipsAddr = R_QW(bi.dResAddr + 0x10);
			if (dTipsAddr)
			{
				bi.wTips = R_CString(dTipsAddr);//dm.ReadStringAddr(dNameAddr,1,0); //
				//wcscpy(bi.wName, csName.GetBuffer(0));
				//bi.wName = csName;
			}
		}

	}
	if (bi.dType == 2 || bi.dType == 1)
	{
		//bi.dIsDead = CALL_�����Ƿ�������(dObjAddr);
		//bi.dIsDead = CALL_�����Ƿ�ɽ���2(dObjAddr);
		INT64 ���Զ��� = getAttrAddr(R_DW(dObjAddr + 0x14));
		if (���Զ���)
		{
			bi.dCurHp = getEncryValue(���Զ���, 1);
			bi.dMaxHp = getEncryValue(���Զ���, 0x1B);
		}
		bi.dMonsterSkillNum = ����::��ȡ�����ͷż�����(dObjAddr);
	}
	INT64 dTemp = R_QW(dObjAddr + 0x98);//����-0218
	bi.����.x = R_Float(dTemp + ƫ��_����);//����-0218
	bi.����.y = R_Float(dTemp + ƫ��_���� + 4);//����-0218
	bi.����.z = R_Float(dTemp + ƫ��_���� + 8);//����-0218
	bi.IsHide = bCheckActorHide(dObjAddr);
	bi.IsEnemy = bCheckActorEnemy(dObjAddr);
	bi.dCanAttack = R_BYTE(dObjAddr + ƫ��_����_���ɹ���ƫ��);
	bi.�Ƿ���Թ���= bCheckActorEnemy1(dObjAddr);
	bi.ID1 = R_DW(dObjAddr + ����Ŀ��);
	//MyTrace(L"�����ַ0x%I64X ID %X %s ����%d ����%0.f/%0.f/%0.f ����%s\n", dObjAddr, bi.dResId, csName, bi.dType, bi.����.x, bi.����.y, bi.����.z, bi.wName);

	//MyTrace(L"getActorInfo 2");
	//if (dm.ReadIntAddr(dObjAddr + 0xB2C,4) == 1 || dm.ReadIntAddr(dObjAddr + 0xB28,4) == 1)
	{

	}
	/*if (bi.dType > 3)
	{
		bi.fx = dm.ReadFloatAddr(dObjAddr + 0x50);
		bi.fy = dm.ReadFloatAddr(dObjAddr + 0x54);
		bi.fz = dm.ReadFloatAddr(dObjAddr + 0x58);
	}else
	{
		INT64 dTemp = dm.ReadIntAddr(dObjAddr + 0x124,3);
		bi.fx = dm.ReadFloatAddr(dTemp + 0x44);
		bi.fy = dm.ReadFloatAddr(dTemp + 0x48);
		bi.fz = dm.ReadFloatAddr(dTemp + 0x4C);
	}*/
	bi.fDis = GetDis(bi.����.x, bi.����.y, bi.����.z);
	bi.���� = ���ù���::�������(bi.����, ����::ȡ����());
	//MyTrace(L"getActorInfo 3");
	//if (dm.ReadIntAddr(dObjAddr + 0x28,4)==0x0002BFFD)
	return bi;

	//swprintf(buf, L"����%X\r �����ַ0x%I64X ID %X %s ����%d ����%0.f/%0.f/%0.f\r\n", bi.dIndex, bi.dObjAddr, bi.dObjId, bi.csName, bi.dType, bi.x, bi.y,bi.z);

	//MyTrace(L"����%X\r �����ַ0x%I64X ID %X %s ����%d ����%0.f/%0.f/%0.f\n",dIndex,dObjAddr,dObjId,csName,dType,x,y,z);
}




objInfo_ ����::getActorInfo1(INT64 dObjAddr, ����_ �Լ�����)
{
	//MyTrace(L"getActorInfo 0");
	objInfo_ bi;
	//memset(&bi, 0, sizeof(objInfo_));
	bi.objBase = dObjAddr;
	bi.dObjId = R_DW(dObjAddr + 0x14);
	bi.dResId = R_DW(dObjAddr + 0x2C);
	bi.ModId = R_DW(dObjAddr + 0x30);
	INT64 dNameAddr = R_QW(dObjAddr + 0x1C);
	CString csName = L"��";
	if (dNameAddr)
	{
		bi.wName = R_CString(dNameAddr);;//dm.ReadStringAddr(dNameAddr,1,0); //
		//wcscpy(bi.wName, csName.GetBuffer(0));
		//bi.wName = csName;
	}
	bi.dType = R_BYTE(dObjAddr + 0x34);
	//MyTrace(L"getActorInfo 1 ���� %s  resId %d type %d", bi.wName,bi.dResId,bi.dType);

	if (bi.dType == 6 || bi.dType == 7 || bi.dType == 8 || bi.dType == 9)
	{
		//bi.dResAddr = dm.ReadIntAddr(dObjAddr + 0xB48,3);
		//bi.dResType = dm.ReadIntAddr(bi.dResAddr + 0x36,6);
		bi.dResType = R_BYTE(dObjAddr + 0xD18);
		//bi.dResShow = R_BYTE(dObjAddr + 0xD15);
		//MyTrace(L"getActorInfo �Ƿ�");
		bi.dResShow = CALL_�����Ƿ�ɽ���(dObjAddr);
		//MyTrace(L"getActorInfo �ɽ���");
		bi.dResOpen = R_BYTE(dObjAddr + 0xD16);
		bi.dPortalOpen = R_BYTE(dObjAddr + go_PortalOpen);
	}
	if (bi.dType == 11)
	{
		bi.dIsDead = R_BYTE(dObjAddr + ƫ��_����_��������Ƿ�����_����11);
	}
	if (bi.dType == 7)
	{
		bi.dIsDead = R_BYTE(dObjAddr + ƫ��_����_��������Ƿ�����_����7);
	}
	if (bi.dType == 3 || bi.dType == 11)
	{
		bi.dResAddr = getNpcResAddrById(bi.dResId);
		if (bi.dResAddr)
		{
			INT64 dTipsAddr = R_QW(bi.dResAddr + 0x10);
			if (dTipsAddr)
			{
				bi.wTips = R_CString(dTipsAddr);//dm.ReadStringAddr(dNameAddr,1,0); //
				//wcscpy(bi.wName, csName.GetBuffer(0));
				//bi.wName = csName;
			}
		}

	}
	if (bi.dType == 2 || bi.dType == 1)
	{
		//bi.dIsDead = CALL_�����Ƿ�������(dObjAddr);
		//bi.dIsDead = CALL_�����Ƿ�ɽ���2(dObjAddr);
		INT64 ���Զ��� = getAttrAddr(R_DW(dObjAddr + 0x14));
		if (���Զ���)
		{
			bi.dCurHp = getEncryValue(���Զ���, 1);
			bi.dMaxHp = getEncryValue(���Զ���, 0x1B);
		}
		bi.dMonsterSkillNum = ����::��ȡ�����ͷż�����(dObjAddr);
	}
	INT64 dTemp = R_QW(dObjAddr + 0x98);//����-0218
	bi.����.x = R_Float(dTemp + ƫ��_����);//����-0218
	bi.����.y = R_Float(dTemp + ƫ��_���� + 4);//����-0218
	bi.����.z = R_Float(dTemp + ƫ��_���� + 8);//����-0218
	bi.���� = ���ù���::�������(bi.����, �Լ�����);
	bi.IsHide = bCheckActorHide(dObjAddr);
	bi.IsEnemy = bCheckActorEnemy(dObjAddr);
	bi.dCanAttack = R_BYTE(dObjAddr + ƫ��_����_���ɹ���ƫ��);
	bi.�Ƿ���Թ��� = bCheckActorEnemy1(dObjAddr);


	//MyTrace(L"getActorInfo 2");
	//if (dm.ReadIntAddr(dObjAddr + 0xB2C,4) == 1 || dm.ReadIntAddr(dObjAddr + 0xB28,4) == 1)
	{

	}
	/*if (bi.dType > 3)
	{
		bi.fx = dm.ReadFloatAddr(dObjAddr + 0x50);
		bi.fy = dm.ReadFloatAddr(dObjAddr + 0x54);
		bi.fz = dm.ReadFloatAddr(dObjAddr + 0x58);
	}else
	{
		INT64 dTemp = dm.ReadIntAddr(dObjAddr + 0x124,3);
		bi.fx = dm.ReadFloatAddr(dTemp + 0x44);
		bi.fy = dm.ReadFloatAddr(dTemp + 0x48);
		bi.fz = dm.ReadFloatAddr(dTemp + 0x4C);
	}*/
	bi.fDis = bi.����;
	//MyTrace(L"getActorInfo 3");
	//if (dm.ReadIntAddr(dObjAddr + 0x28,4)==0x0002BFFD)
	return bi;

	//swprintf(buf, L"����%X\r �����ַ0x%I64X ID %X %s ����%d ����%0.f/%0.f/%0.f\r\n",dIndex,dObjAddr,dObjId,csName,dType,x,y,z);

	//MyTrace(L"����%X\r �����ַ0x%I64X ID %X %s ����%d ����%0.f/%0.f/%0.f\n",dIndex,dObjAddr,dObjId,csName,dType,x,y,z);
}


int ����::CALL_�����Ƿ�ɽ���(INT64 ��������ָ��)
{
	if (��������ָ�� && !IsBadReadPtr((const void*)��������ָ��, sizeof(��������ָ��)))
	{
		INT64 CALL = R_QW(R_QW(��������ָ��) + go_ActorShow);
		//INT64 CALL = ��Ϸģ�� + gc_ActorShow;
		if (CALL && !IsBadReadPtr((const void*)CALL, sizeof(CALL)))
		{
			return (int)CALL2(��������ָ��, 0, CALL);
		}

	}
	return 0;
}
int ����::CALL_�����Ƿ�ɽ���2(INT64 ��������ָ��)
{
	if (��������ָ�� && !IsBadReadPtr((const void*)��������ָ��, sizeof(��������ָ��)))
	{
		INT64 CALL = R_QW(R_QW(��������ָ��) + go_ActorShow + 8);
		//INT64 CALL = ��Ϸģ�� + gc_ActorShow;
		if (CALL && !IsBadReadPtr((const void*)CALL, sizeof(CALL)))
		{
			return (int)CALL2(��������ָ��, 0, CALL);
		}

	}
	return 0;
}
int ����::CALL_�����Ƿ�������(INT64 ��������ָ��)
{
	if (��������ָ�� && !IsBadReadPtr((const void*)��������ָ��, sizeof(��������ָ��)))
	{
		INT64 CALL = R_QW(R_QW(��������ָ��) + 0x210);
		if (CALL && !IsBadReadPtr((const void*)CALL, sizeof(CALL)))
		{
			return (int)MainUniversalCALL2_Ret(��������ָ��, 0, CALL);
		}

	}
	return 0;
}
void ����::����ȫ����������(vector<objInfo_>& vsk)
{
	vsk.clear();
	objInfo_ ��ʱ;
	INT64 addr_1 = R_QW(��Ϸģ�� + gb_ActorList);
	long dtotal = R_QW(addr_1 + 0x9C + 8 + 0x10 + 0x18);//����-0218
	INT64 objStartAddr = R_QW(addr_1 + 0x9C + 8);////����-0218 ���������ַ
	INT64 dKeyAddr = R_QW(addr_1 + 0x9C + 8 + 0x20);//����-0218
	if (!dKeyAddr)
	{
		dKeyAddr = addr_1 + 0x9C + 8 + 0x10;//����-0218
	}
	for (long i = 0; i < dtotal; i++)
	{
		long dKeyValue = R_DW(dKeyAddr + (i / 0x20) * 4);
		DWORD dNum = i % 0x20;
		DWORD dCheck = (dKeyValue >> dNum) & 1;
		if (dCheck)
		{
			DWORD dObjId = R_DW(objStartAddr + i * 0x3 * 8);
			if (dObjId && dObjId != 0xFFFFFFFF)
			{
				INT64 dObjAddr = R_QW(objStartAddr + i * 0x3 * 8 + 8);
				//MyTrace(L"dObjAddr 0X%I64X", dObjAddr);
				��ʱ = ����::getActorInfo(dObjAddr);
				if (��ʱ.dResId != 0)
				{
					��ʱ.dObjId = dObjId;
					if (��ʱ.dResId == 0x2B066 || ��ʱ.dResId == 0x2B052)
					{
						continue;
					}

					if (��ʱ.dType == 2 && ��ʱ.�Ƿ���Թ��� != 0)
					{
						continue;
					}
					vsk.push_back(��ʱ);
				}

			}
		}
	}
	::sort(vsk.begin(), vsk.end(), flessmark);
}

void ����::����ȫ����������2(vector<objInfo_>& vsk, ����_ �Լ�����)
{
	vsk.clear();
	objInfo_ ��ʱ;
	INT64 addr_1 = R_QW(��Ϸģ�� + gb_ActorList);
	long dtotal = R_QW(addr_1 + 0x9C + 8 + 0x10 + 0x18);//����-0218
	INT64 objStartAddr = R_QW(addr_1 + 0x9C + 8);////����-0218 ���������ַ
	INT64 dKeyAddr = R_QW(addr_1 + 0x9C + 8 + 0x20);//����-0218
	if (!dKeyAddr)
	{
		dKeyAddr = addr_1 + 0x9C + 8 + 0x10;//����-0218
	}
	for (long i = 0; i < dtotal; i++)
	{
		long dKeyValue = R_DW(dKeyAddr + (i / 0x20) * 4);
		DWORD dNum = i % 0x20;
		DWORD dCheck = (dKeyValue >> dNum) & 1;
		if (dCheck)
		{
			DWORD dObjId = R_DW(objStartAddr + i * 0x3 * 8);
			if (dObjId && dObjId != 0xFFFFFFFF)
			{
				INT64 dObjAddr = R_QW(objStartAddr + i * 0x3 * 8 + 8);
				//MyTrace(L"dObjAddr 0X%I64X", dObjAddr);
				��ʱ = ����::getActorInfo1(dObjAddr,�Լ�����);


				if (��ʱ.dResId != 0)
				{
					��ʱ.dObjId = dObjId;
					if (��ʱ.dResId == 0x2B066 || ��ʱ.dResId == 0x2B052)
					{
						continue;
					}

					if (��ʱ.dType == 2 && ��ʱ.�Ƿ���Թ��� != 0)
					{
						continue;
					}
					vsk.push_back(��ʱ);
				}

			}
		}
	}
	::sort(vsk.begin(), vsk.end(), flessmark);


}




void ����::����ȫ����������1(vector<objInfo_>& vsk)
{
	ActorInfo_ ��ɫ��Ϣ = ����::ȡ��ɫ��Ϣ();
	vsk.clear();
	objInfo_ ��ʱ;
	INT64 addr_1 = R_QW(��Ϸģ�� + gb_ActorList);
	long dtotal = R_QW(addr_1 + 0x9C + 8 + 0x10 + 0x18);//����-0218
	INT64 objStartAddr = R_QW(addr_1 + 0x9C + 8);////����-0218 ���������ַ
	INT64 dKeyAddr = R_QW(addr_1 + 0x9C + 8 + 0x20);//����-0218
	if (!dKeyAddr)
	{
		dKeyAddr = addr_1 + 0x9C + 8 + 0x10;//����-0218
	}
	for (long i = 0; i < dtotal; i++)
	{
		long dKeyValue = R_DW(dKeyAddr + (i / 0x20) * 4);
		DWORD dNum = i % 0x20;
		DWORD dCheck = (dKeyValue >> dNum) & 1;
		if (dCheck)
		{
			DWORD dObjId = R_DW(objStartAddr + i * 0x3 * 8);
			if (dObjId && dObjId != 0xFFFFFFFF)
			{
				INT64 dObjAddr = R_QW(objStartAddr + i * 0x3 * 8 + 8);
				//MyTrace(L"dObjAddr 0X%I64X", dObjAddr);
				��ʱ = ����::getActorInfo(dObjAddr);
				if (��ʱ.dResId != 0)
				{
					��ʱ.dObjId = dObjId;

					if (��ʱ.dResId == 0x2B066 || ��ʱ.dResId == 0x2B052)
					{
						continue;
					}

					if (��ʱ.dType == 2 && ��ʱ.�Ƿ���Թ��� != 0 )
					{
						continue;
					}
				

					vsk.push_back(��ʱ);
				}

			}
		}
	}
	::sort(vsk.begin(), vsk.end(), flessmark);
}

bool �������(const ����_& o1, const ����_& o2)
{
	return o1.fDis < o2.fDis;

}
void �����·(CString ID�ı�, vector<����_>& vsk)
{
	CArray<CString, CString>�ָ�;
	CArray<CString, CString>�ָ�1;

	vsk.clear();
	if (ID�ı�.Find(L"|") != -1)
	{
		�ı��ָ�(ID�ı�, '|', &�ָ�);
		if (�ָ�.GetCount() == 0)
		{
			vsk.clear();
		}
		else
		{
			for (size_t i = 0; i < �ָ�.GetCount(); i++)
			{
				�ı��ָ�(�ָ�[i], ',', &�ָ�1);
				if (�ָ�1.GetCount() != 0)
				{ 
					����_  x = ����::ȡ����();
					����_ ��ʱ;
					��ʱ.x = _ttof(�ָ�1[1]);
					��ʱ.y = _ttof(�ָ�1[2]);
					��ʱ.z = _ttof(�ָ�1[3]);
					��ʱ.fDis = ���ù���::�������(��ʱ, x);
					��ʱ.����λ�� = i;
					vsk.push_back(��ʱ);
				}
			

			}
		}
	}
	::sort(vsk.begin(), vsk.end(), �������);
}


CString ���������·(CString ID�ı�)
{
	CArray<CString, CString>�ָ�;
	CArray<CString, CString>�ָ�1;
	CString temp;
	vector<����_>vsk;
	�����·(ID�ı�, vsk);
	if (vsk.size() > 0)
	{
		DWORD ���������� = vsk[0].����λ��;

		if (ID�ı�.Find(L"|") != -1)
		{
			�ı��ָ�(ID�ı�, '|', &�ָ�);
			if (�ָ�.GetCount() != 0)
			{
				for (size_t i = 0; i < �ָ�.GetCount(); i++)
				{
					if (i >= ����������)
					{
						�ı��ָ�(�ָ�[i], ',', &�ָ�1);
						if (�ָ�1.GetCount() != 0)
						{
							temp = temp + �ָ�[1] + "," + �ָ�[2] + "," + �ָ�[3] + "|";
						}

					}


				}

			}

		}
	}

	return temp;

}

void ����::����ָ��ȫ����������(DWORD dtype, vector<objInfo_>& vsk)
{
	vsk.clear();
	objInfo_ ��ʱ;
	INT64 addr_1 = R_QW(��Ϸģ�� + gb_ActorList);
	long dtotal = R_QW(addr_1 + 0x9C + 8 + 0x10 + 0x18);//����-0218
	INT64 objStartAddr = R_QW(addr_1 + 0x9C + 8);////����-0218 ���������ַ
	INT64 dKeyAddr = R_QW(addr_1 + 0x9C + 8 + 0x20);//����-0218
	if (!dKeyAddr)
	{
		dKeyAddr = addr_1 + 0x9C + 8 + 0x10;//����-0218
	}
	for (long i = 0; i < dtotal; i++)
	{
		long dKeyValue = R_DW(dKeyAddr + (i / 0x20) * 4);
		DWORD dNum = i % 0x20;
		DWORD dCheck = (dKeyValue >> dNum) & 1;
		if (dCheck)
		{
			DWORD dObjId = R_DW(objStartAddr + i * 0x3 * 8);
			if (dObjId && dObjId != 0xFFFFFFFF)
			{
				INT64 dObjAddr = R_QW(objStartAddr + i * 0x3 * 8 + 8);
				DWORD type = R_BYTE(dObjAddr + 0x34);
				if (type == dtype)
				{
					//MyTrace(L"dObjAddr 0X%I64X", dObjAddr);
					��ʱ = ����::getActorInfo(dObjAddr);
					if (��ʱ.dResId != 0)
					{
						��ʱ.dObjId = dObjId;
						vsk.push_back(��ʱ);
					}
				}


			}
		}
	}
	::sort(vsk.begin(), vsk.end(), flessmark);
}


DWORD ����::��Χ��������(DWORD ����)
{
	objInfo_ temp;
	vector<objInfo_>vsk;
	DWORD ���� = 0;
	����::����ȫ����������1(vsk);
	for (size_t i = 0; i < vsk.size(); i++)
	{
		if (vsk[i].dType == 2 || vsk[i].dType == 3)
		{
			if (vsk[i].dCurHp >= 1 && vsk[i].wName != L"" && vsk[i].IsHide == 0)
			{
				if (vsk[i].���� < ����)
				{
					���� = ���� + 1;


				}
			}
		}
	}

	return ����;

}
DWORD ����::��Χ��������1(DWORD ����)
{
	objInfo_ temp;
	vector<objInfo_>vsk;
	DWORD ���� = 0;
	����::����ȫ����������1(vsk);
	for (size_t i = 0; i < vsk.size(); i++)
	{
		if (vsk[i].dType == 2 )
		{
			if (vsk[i].dCurHp >= 1 && vsk[i].wName != L"" && vsk[i].IsHide == 0)
			{
				if (vsk[i].���� < ����)
				{
					���� = ���� + 1;


				}
			}
		}
	}

	return ����;

}



bool ����::�жϹ���(INT64 ����)
{
	INT64 ��_�ж�����ַ = R_QW(R_QW(����) + ƫ��_����_�������);
	INT64 ��_ָ���ַ = ��_�ж�����ַ + 321;
	INT64 ��_ָ���ַ2 = ��_ָ���ַ + 3;
	DWORD ��_��ʱ = R_QW(��_ָ���ַ2);
	INT64 �жϵ�ַ = ��_ָ���ַ + ��_��ʱ + 7;
	//CString �ı���ʶ = CString(UnicodeToAnsi(R_CString(�жϵ�ַ)));
	CString �ı���ʶ2 = R_CString(�жϵ�ַ);
	//MyTrace(L"�ı���ʶ %s", �ı���ʶ);
	//MyTrace(L"�ı���ʶ2 %s", �ı���ʶ2);
	if (�ı���ʶ2 == L"OUTLINE_MONSTER_ENEMY")
	{
		return true;
	}
	return false;

}

void ����::С��call()
{
	INT64 rcx = 0;

	bool �Ƿ�� = UI����::Ѱ�Ҵ򿪴���("root1.arkui.windowCanvas.exitMenuWindow", rcx);
	if (rcx >= 1)
	{

		MyTrace(L"0X%I64X", rcx);
		MainUniversalCALL4(rcx, 0x1F, 2, 0, ��Ϸģ�� + ��ַ_С��call);
		Sleep(2000);
	//	UI����::�ڴ水��(VK_RETURN);
	}


}


DWORD ����::��ȡ��ǰ�Ի�npc()
{
	DWORD b = 0;

	INT64 ��_rcx = R_QW(��Ϸģ�� + ��ַ_����_�˳�npc�Ի�);


	b = R_DW(��_rcx + 0x10C);

	return b;


}
bool ����::�ж�NPC(INT64 ����)
{
	INT64 ��_�ж�����ַ = R_QW(R_QW(����) + ƫ��_����_�������);
	INT64 ��_ָ���ַ = ��_�ж�����ַ + 1000;
	INT64 ��_ָ���ַ2 = ��_ָ���ַ + 3;
	DWORD ��_��ʱ = R_QW(��_ָ���ַ2);
	INT64 �жϵ�ַ = ��_ָ���ַ + ��_��ʱ + 7;
	//CString �ı���ʶ = CString(UnicodeToAnsi(R_CString(�жϵ�ַ)));
	CString �ı���ʶ2 = R_CString(�жϵ�ַ);
	//MyTrace(L"�ı���ʶ %s", �ı���ʶ2);
	if (�ı���ʶ2 == L"OUTLINE_NPC_FRIENDLY")
	{
		return true;
	}
	return false;

}
bool ����::�жϵ�����Ʒ(INT64 ����)
{
	INT64 ��_�ж�����ַ = R_QW(R_QW(����) + ƫ��_����_�������);
	//*(BYTE*)&��_�ж�����ַ[0] = 0x33;
	/*BYTE B����[3] = { 0 };
	���ڴ��ֽڼ�((HANDLE)-1, (LPVOID)��_�ж�����ַ, 3, &B����);*/
	if (R_BYTE(��_�ж�����ַ) == 0x33 && R_BYTE(��_�ж�����ַ + 1) == 0xC0 && R_BYTE(��_�ж�����ַ + 2) == 0xC3)
	{
		return true;
	}
	return false;
}
bool ����::�жϲɼ���(INT64 ����)
{
	INT64 ��_�ж�����ַ = R_QW(R_QW(����) + ƫ��_����_�������);
	INT64 ��_ָ���ַ = ��_�ж�����ַ + 40;
	INT64 ��_ָ���ַ2 = ��_ָ���ַ + 3;
	DWORD ��_��ʱ = R_QW(��_ָ���ַ2);
	INT64 �жϵ�ַ = ��_ָ���ַ + ��_��ʱ + 7;
	//CString �ı���ʶ = CString(UnicodeToAnsi(R_CString(�жϵ�ַ)));
	CString �ı���ʶ2 = R_CString(�жϵ�ַ);
	if (�ı���ʶ2 == L"OUTLINE_PROP_TOUCH")
	{
		return true;
	}
	return false;

}
bool ����::�жϻ������(INT64 ����)
{
	INT64 ��_�ж�����ַ = R_QW(R_QW(����) + ƫ��_����_�������);
	INT64 ��_ָ���ַ = ��_�ж�����ַ + 56;
	INT64 ��_ָ���ַ2 = ��_ָ���ַ + 3;
	DWORD ��_��ʱ = R_QW(��_ָ���ַ2);
	INT64 �жϵ�ַ = ��_ָ���ַ + ��_��ʱ + 7;
	//CString �ı���ʶ = CString(UnicodeToAnsi(R_CString(�жϵ�ַ)));
	CString �ı���ʶ2 = R_CString(�жϵ�ַ);
	if (�ı���ʶ2 == L"OUTLINE_PROP_HIT")
	{
		if (R_DW(���� + ƫ��_����_������� + 4) == 1)
		{
			return true;
		}
		if (R_DW(���� + ƫ��_����_�������) == 1)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	return false;

}
bool ����::��������Ƿ�����(INT64 ����)
{
	if (R_DW(���� + ƫ��_����_��������Ƿ�����) == 1)
	{
		return true;
	}
	return false;

}

void ����::��������(vector<objInfo_>& ����)
{
	����.clear();
	vector<objInfo_>vsk;
	����::����ָ��ȫ����������(2, vsk);
	for (size_t i = 0; i < vsk.size(); i++)
	{

		if ((/*����::�жϹ���(vsk[i].objBase)|| */vsk[i].dType == 2) && vsk[i].dCurHp > 0 && vsk[i].dResId != 0x1FCFC && vsk[i].IsEnemy == true && ID�Ƿ��Ѵ���(vsk[i].dResId, ��ʱ����ID) == false && vsk[i].IsHide == false && vsk[i].dResId != 0xA8B39)
		{
			if (vsk[i].dResId == 0x22F74 || vsk[i].dResId == 0x22F7E)
			{
				if (vsk[i].dCurHp <= 180)
				{
					continue;
				}
			}
			����.push_back(vsk[i]);
			continue;
		}
		if (vsk[i].dResId == 0x2A106)
		{
			����.push_back(vsk[i]);
		}
		//if ((/*����::�жϹ���(vsk[i].objBase)|| */vsk[i].dType == 2) && vsk[i].dResId == 0x2A40E)
		//{
		//	����.push_back(vsk[i]);
		//}
	}
	::sort(����.begin(), ����.end(), flessmark);
}

void ����::����NPC(vector<objInfo_>& ����)
{
	����.clear();
	vector<objInfo_>vsk;
	����::����ָ��ȫ����������(3, vsk);
	for (size_t i = 0; i < vsk.size(); i++)
	{
		//if (����::�ж�NPC(vsk[i].objBase))
		//{
		����.push_back(vsk[i]);
		//}
	}
	::sort(����.begin(), ����.end(), flessmark);
}
objInfo_ ����::ȡָ������NPC(CString tips)
{
	objInfo_ temp;
	vector<objInfo_>vsk;
	����::����NPC(vsk);
	for (size_t i = 0; i < vsk.size(); i++)
	{
		//MyTrace(L"NPC:%s tips:%s", vsk[i].wName, vsk[i].wTips);
		if (vsk[i].wTips == tips)
		{
			return vsk[i];
		}
	}
	return temp;
}
void ����::�����ɼ���(vector<objInfo_>& ����)
{
	����.clear();
	vector<objInfo_>vsk;
	����::����ָ��ȫ����������(6, vsk);
	for (size_t i = 0; i < vsk.size(); i++)
	{
		if (/*����::�жϲɼ���(vsk[i].objBase) &&*/ vsk[i].dType == 6)
		{
			����.push_back(vsk[i]);
		}
	}
}

void ����::�����������(vector<objInfo_>& ����)
{
	����.clear();
	vector<objInfo_>vsk;
	MyTrace(L"%s 7", __FUNCTIONW__);
	����::����ָ��ȫ����������(7, vsk);
	for (size_t i = 0; i < vsk.size(); i++)
	{
		if (ID�Ƿ��Ѵ���(vsk[i].dResId, ��ʱ����ID))
		{
			continue;
		}
		if ((/*����::�жϻ������(vsk[i].objBase) || */vsk[i].dType == 7) && ��������Ƿ�����(vsk[i].objBase) == false && vsk[i].dResShow == 1 && vsk[i].dIsDead != 0)
		{
			����.push_back(vsk[i]);
			continue;
		}
		/*if (vsk[i].dType == 7 && ��������Ƿ�����(vsk[i].objBase) == false  && vsk[i].dIsDead == 5 && vsk[i].IsEnemy==true)
		{
			����.push_back(vsk[i]);

		}*/
		/*if (vsk[i].wName == L"tip.name.tower_82204")
		{
			����.push_back(vsk[i]);
		}*/
	}
	MyTrace(L"%s 11", __FUNCTIONW__);
	����::����ָ��ȫ����������(11, vsk);
	for (size_t i = 0; i < vsk.size(); i++)
	{
		if (ID�Ƿ��Ѵ���(vsk[i].dResId, ��ʱ����ID))
		{
			continue;
		}
		if (vsk[i].dType == 11 && vsk[i].dIsDead == 0)
		{
			����.push_back(vsk[i]);
		}
	}
	::sort(����.begin(), ����.end(), flessmark);
}

void ����::����������Ʒ(vector<objInfo_>& ����)
{
	����.clear();
	vector<objInfo_>vsk;
	����::����ָ��ȫ����������(4, vsk);
	for (size_t i = 0; i < vsk.size(); i++)
	{
		����.push_back(vsk[i]);
	}
}
void ����::��������(vector<objInfo_>& ����)
{
	����.clear();
	vector<objInfo_>vsk;
	����::����ָ��ȫ����������(15, vsk);
	for (size_t i = 0; i < vsk.size(); i++)
	{
		if (vsk[i].dType == 15 && vsk[i].fDis < 500)
		{
			����.push_back(vsk[i]);
		}
	}
	::sort(����.begin(), ����.end(), flessmark);
}
void ����::����������(vector<objInfo_>& ����)
{
	����.clear();
	vector<objInfo_>vsk;
	����::����ȫ����������(vsk);
	for (size_t i = 0; i < vsk.size(); i++)
	{
		if (vsk[i].dResId == 0x1181D || vsk[i].dResId == 0x1398C || vsk[i].dResId == 0x139A1 || vsk[i].dResId == 0x92BC7 || vsk[i].dResId == 0x139A2 || vsk[i].dResId == 0x14410 || vsk[i].dResId == 0x1AE33 || vsk[i].dResId == 0x1155E || vsk[i].dResId == 0x4F1B || vsk[i].dResId == 0xA02B || vsk[i].dResId == 0xA08C || vsk[i].dResId == 0xA607 || vsk[i].dResId == 0xA090 || vsk[i].dResId == 0x1B4C2
			|| vsk[i].dResId == 0x1B5EE || vsk[i].dResId == 0x1B1B7)
		{
			/*if (��ͼ::ָ���ص��Ƿ�ɵ���_M(vsk[i].����.x, vsk[i].����.y, vsk[i].����.z))
			{*/
			����.push_back(vsk[i]);
			//}

		}
	}
	::sort(����.begin(), ����.end(), flessmark);
}
objInfo_ ����::ȡָ��������Ϣ(DWORD ResId)
{
	objInfo_ temp;
	vector<objInfo_>vsk;
	����ȫ����������(vsk);
	for (size_t i = 0; i < vsk.size(); i++)
	{
		if (ResId == vsk[i].dResId)
		{
			temp = vsk[i];
			break;
		}
	}
	return temp;
}
objInfo_ ����::ȡ���������Ϣ()
{
	objInfo_ temp;
	vector<objInfo_>vsk;
	����ȫ����������(vsk);
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
objInfo_ ����::ȡָ���ɼ�������Ϣ(DWORD ResId)
{
	objInfo_ temp;
	vector<objInfo_>vsk;
	����ȫ����������(vsk);
	for (size_t i = 0; i < vsk.size(); i++)
	{
		if (ResId == vsk[i].dResId && vsk[i].dPortalOpen != 4)
		{
			temp = vsk[i];
			break;
		}
	}
	return temp;
}

objInfo_ ����::ȡָ��������ʾ������Ϣ(DWORD ResId, DWORD ResShow)
{
	objInfo_ temp;
	vector<objInfo_>vsk;
	����ȫ����������(vsk);
	for (size_t i = 0; i < vsk.size(); i++)
	{
		if ((ResId == vsk[i].dResId || ID�Ƿ��Ѵ���(vsk[i].dResId, ���Ȳɼ�ID)) && vsk[i].dResShow == ResShow)
		{
			temp = vsk[i];
			break;
		}
	}
	return temp;
}
objInfo_ ����::ȡָ����Χ������ʾ������Ϣ(float x, float y, float z, float ����, DWORD ResId)
{
	objInfo_ temp;
	vector<objInfo_>vsk;
	����ȫ����������(vsk);
	for (size_t i = 0; i < vsk.size(); i++)
	{

		if (ResId == vsk[i].dResId && vsk[i].dResShow == 1)
		{

			if (�������3(x, y, z, vsk[i].����.x, vsk[i].����.y, vsk[i].����.z) < ����)
			{
				temp = vsk[i];
				break;
			}

		}
		if (ID�Ƿ��Ѵ���(vsk[i].dResId, ���Ȳɼ�ID) == true && vsk[i].dResShow == 1)
		{
			if (�������3(x, y, z, vsk[i].����.x, vsk[i].����.y, vsk[i].����.z) < ����)
			{
				temp = vsk[i];
				break;
			}

		}
	}
	return temp;
}
����_ ����::ȡ��������(INT64 ����)
{
	����_ ����;
	INT64 ��_�����ַ = R_QW(���� + 148 + 4);
	����.x = R_Float(��_�����ַ + ƫ��_����);
	����.y = R_Float(��_�����ַ + ƫ��_���� + 4);
	����.z = R_Float(��_�����ַ + ƫ��_���� + 8);
	return ����;
}
bool ����::CALL_��NPC(INT64 ����)
{
	����_ ���� = ����::ȡ��������(����);
	INT64 ��_�ؼ�ֵ = R_QW(���� + 148 + 4);
	INT64 ��_rcx = R_QW(R_QW(R_QW(��Ϸģ�� + ��ַ_����_����) + 0x94) + 16);
	if (��_rcx == 0)
	{
		return false;
	}
	UCHAR pBuff[0x30] = { 0 };
	W_QW((ULONG64)&pBuff[0x0], 0);
	W_QW((ULONG64)&pBuff[0x8], 0);
	W_QW((ULONG64)&pBuff[0x10], 0);
	W_Float((ULONG64)&pBuff[0x18], ����.x);
	W_Float((ULONG64)&pBuff[0x1C], ����.y);
	W_Float((ULONG64)&pBuff[0x20], ����.z);
	W_QW((ULONG64)&pBuff[0x28], ��_�ؼ�ֵ);
	MainUniversalCALL2(��_rcx, (ULONG_PTR)pBuff, ��Ϸģ�� + ��ַ_����_��npc);
	return true;

}
bool ����::CALL_�˳�NPC()
{
	INT64 ��_rcx = R_QW(��Ϸģ�� + ��ַ_����_�˳�npc�Ի�);
	INT64 ��_call = R_QW(R_QW(��_rcx) + 0x40);
	if (��_rcx == 0 || ��_call == 0)
	{
		return false;
	}
	MainUniversalCALL2(��_rcx, 2, ��_call);
	return true;
}
bool ����::CALL_NPC�Ի���֧(int �Ի����)
{
	INT64 ��_rcx = R_QW(��Ϸģ�� + ��ַ_����_�˳�npc�Ի�);
	if (��_rcx == 0)
	{
		return false;
	}
	MainUniversalCALL4(��_rcx, 4, 2, �Ի����, ��Ϸģ�� + ��ַ_����_npc�Ի���֧call);
	return true;
}
int ����::��ȡ��ǰ�Ի�NPC()
{
	INT64 ��_rcx = R_QW(��Ϸģ�� + ��ַ_����_�˳�npc�Ի�);
	if (��_rcx)
	{
		return R_DW(��_rcx + 0x170);
	}
	return 0;
}
bool ����::�Ƿ��ں�NPC�Ի�()
{
	DWORD ��_��־ = R_DW(R_QW(��Ϸģ�� + ��ַ_����_npc�Ի���־) + 88);
	if (��_��־ == 1)
	{
		return true;
	}
	return false;
}

bool ����::�Ƿ��ڼ���ҳ��()
{
	DWORD ��_��־ = R_DW(��Ϸģ�� + ��ַ_����_�Ƿ��ڼ��ؽ���);
	if (��_��־ == 1)
	{
		return true;
	}
	return false;
}
bool ����::�Ƿ��ڼ���ҳ��2()
{
	INT64 ��_rcx = R_QW(��Ϸģ�� + gb_�жϼ��ػ�ַ);
	��_rcx = R_QW(��_rcx + go_����ƫ��1);
	DWORD ��_��־ = R_DW(��_rcx + go_����ƫ��2);
	if (��_��־ == 1 || ��_��־ == 2)
	{
		return true;
	}
	return false;
}
bool ����::�Ƿ��ڶ���()
{
	DWORD ��_��־ = R_DW(R_QW(��Ϸģ�� + ��ַ_����_�ж϶���) + 136);
	if (��_��־ == 0)
	{
		return false;
	}
	return true;
}

DWORD ����::ʣ����Ϣ��ѯ()
{
	DWORD ��_��־ = R_DW(R_QW(��Ϸģ�� + ��ַ_����_�ж϶���) + 0x58);
	return ��_��־;
 }


bool ����::ʰ��(INT64 ����)
{
	INT64 ��_call = ��Ϸģ�� + ��ַ_����_ʰ��call;
	INT64 ��_rcx = R_QW(R_QW(R_QW(��Ϸģ�� + ��ַ_����_����rcx - 8) + ƫ��_����_ʰ��) + ƫ��_����_ʰ��2);
	if (!��_rcx)
	{
		return false;
	}
	DWORD ��_��Ʒid = R_DW(���� + 20);
	MainUniversalCALL2(��_rcx, ��_��Ʒid, ��_call);
	return true;
}

bool ����::CALL_���ָ��NPC(CString ��������)
{
	vector<objInfo_>����;
	����::����NPC(����);
	for (size_t i = 0; i < ����.size(); i++)
	{
		if (�������� == ����[i].wName)
		{
			����::CALL_��NPC(����[i].objBase);
			return true;
		}
	}
	return false;
}
bool ����::CALL_���ָ��NPC_ByResId(DWORD ResId)
{
	vector<objInfo_>����;
	����::����NPC(����);
	for (size_t i = 0; i < ����.size(); i++)
	{
		if (ResId == ����[i].dResId && !����[i].IsHide)
		{
			MyTrace(L"��NPC,0x%I64X", ����[i].objBase);
			����::CALL_��NPC(����[i].objBase);
			return true;
		}
	}
	return false;
}
float ����::��ȡ����Ƕ�ֵ(INT64 obj)
{
	if (obj)
	{
		INT64 addr1 = R_QW(obj + 0x98);
		float addr2 = R_DW(addr1 + ƫ��_����_����Ƕ� + 4);
		return addr2;
	}
	return 0;
}
int ����::��ȡ�����ͷż�����(INT64 obj)
{
	DWORD ���� = 0;
	if (obj)
	{
		INT64 addr1 = R_QW(obj + 0x98);
		INT64 ����ͷ = R_QW(addr1 + 0x15C);
		DWORD �������� = R_DW(addr1 + 0x15C + 8);
		//for (size_t i = 0; i < ��������; i++)
		//{
		//	INT64 �����ͷŶ��� = R_QW(����ͷ + i * 8);
		//	DWORD ����ID = R_DW(�����ͷŶ��� + 0x448);
		//	float x = R_Float(�����ͷŶ��� + ƫ��_����);
		//	float y = R_Float(�����ͷŶ��� + ƫ��_���� + 4);
		//	float z = R_Float(�����ͷŶ��� + ƫ��_���� + 8);
		//	//MyTrace(L"���� 0x%I64X ����ID %d %0.3f %0.3f %0.3f", �����ͷŶ���, ����ID, x, y, z);
		//}
		���� = ��������;
	}
	return ����;
}

bool NPC::CALL_ShopBuyAddItem(int dItemIndex)//������1��ʼ �ȵ������
{
	INT64 addr_1 = R_QW(��Ϸģ�� + gb_ShopBase);
	if (addr_1 == 0)
	{
		return false;
	}
	int dTotal = R_DW(addr_1 + go_ShopBuyItemListStart + 8);
	if (dTotal <= 10)//������10��
	{
		MainUniversalCALL4(addr_1, dItemIndex, 1, 0, ��Ϸģ�� + gc_ShopBuyAddItem);
		return true;
	}
	return false;
}

bool NPC::ShopBuyItemClick()//�������ť
{

	INT64 addr_1 = R_QW(��Ϸģ�� + gb_ShopBase);
	if (R_DW(addr_1 + go_ShopBuyItemState) == 0)//״̬
	{
		if (R_DW(addr_1 + go_ShopBuyItemListStart + 8))//�ж������Ʒ
		{
			UCHAR buff[0x1000] = { 0 };
			MainUniversalCALL2((ULONG_PTR)buff, 0, ��Ϸģ�� + gc_ShopBuyItem);
			return true;
		}

	}
	return false;
}

void NPC::get_ShopItemList(vector<Inventoryinfo_>& �̵깺����)
{

	�̵깺����.clear();
	INT64 addr_1 = R_QW(��Ϸģ�� + gb_ShopBase);
	DWORD dOffest = go_ShopListStart + 4;
	long dtotal = R_DW(addr_1 + dOffest + 0x10 + 0x18);
	INT64 dKeyAddr = R_QW(addr_1 + dOffest + 0x20);
	if (!dKeyAddr)
	{
		dKeyAddr = addr_1 + dOffest + 0x10;
	}
	long dKeyValue = R_DW(addr_1 + dOffest + 0x10);
	INT64 objStartAddr = R_QW(addr_1 + dOffest);
	for (DWORD i = 0; i < dtotal; i++)
	{
		long dKeyValue = R_DW(dKeyAddr + (i / 0x20) * 4);
		DWORD dNum = i % 0x20;
		DWORD dCheck = (dKeyValue >> dNum) & 1;
		if (dCheck)
		{
			DWORD dIndex = R_BYTE(objStartAddr + i * 0xF8);
			DWORD dResId = R_DW(objStartAddr + i * 0xF8 + 0xC);
			DWORD dPrice = R_DW(objStartAddr + i * 0xF8 + 0x20);
			INT64 dResAddr = getItemResAddrById(dResId);
			INT64 dNameAddr = R_QW(dResAddr + 0x10);
			DWORD dSlotIndex = R_DW(dResAddr + 0x114);
			CString csName = L"";
			if (dNameAddr)
			{
				csName = R_CString(dNameAddr);
			}
			Inventoryinfo_ temp;
			temp.dindex = dIndex;
			temp.ItemResId = dResId;
			temp.dPrice = dPrice;
			temp.ItemName = csName;
			�̵깺����.push_back(temp);
			/*wchar_t buf[100];
			swprintf(buf, L"����%d ��ԴID %X %s ����%X �۸�%d\r\n", dIndex, dResId, csName, dSlotIndex, dPrice);
			g_String.Insert(g_String.GetLength(), buf);*/
		}
	}
}
DWORD ����::��ȡ��ǰ����ID()
{
	return R_DW(��Ϸģ�� + ƫ��_����_��������־);
}

void ����::�������Ȳɼ�ID(CString ID�ı�)
{
	CArray<CString, CString>�����ı���;
	���Ȳɼ�ID.clear();
	if (ID�ı�.Find(L"|") == -1)
	{
		if (ID�Ƿ��Ѵ���(_ttoi(ID�ı�), ���Ȳɼ�ID) == false)
		{
			���Ȳɼ�ID.push_back(_ttoi(ID�ı�));
		}
	}
	else
	{
		�ı��ָ�(ID�ı�, '|', &�����ı���);
		if (�����ı���.GetCount() == 0)
		{
			���Ȳɼ�ID.clear();
		}
		else
		{

			for (size_t i = 0; i < �����ı���.GetCount(); i++)
			{
				if (ID�Ƿ��Ѵ���(_ttoi(�����ı���[i]), ���Ȳɼ�ID) == false)
				{
					���Ȳɼ�ID.push_back(_ttoi(�����ı���[i]));
				}

			}
		}
	}
}