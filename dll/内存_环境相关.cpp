#include "内存_环境相关.h"
vector<DWORD>优先采集ID;
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
		//MyTrace(L"判断隐藏值%d", dVaule);
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
	DWORD dValue = R_BYTE(addr_1);//读字节
	if (dValue == 0)//敌人
	{
		return TRUE;
	}
	return FALSE;
}

BYTE bCheckActorEnemy1(INT64 dObjAddr)
{
	INT64 addr_1 = R_QW(dObjAddr + 0x8C);
	DWORD dValue = R_BYTE(addr_1);//读字节
	return dValue;


}



objInfo_ 环境::getActorInfo(INT64 dObjAddr)
{
	//MyTrace(L"getActorInfo 0");
	objInfo_ bi;
	//memset(&bi, 0, sizeof(objInfo_));
	bi.objBase = dObjAddr;
	bi.dObjId = R_DW(dObjAddr + 0x14);
	bi.dResId = R_DW(dObjAddr + 0x2C);
	bi.ModId = R_DW(dObjAddr + 0x30);
	INT64 dNameAddr = R_QW(dObjAddr + 0x1C);
	CString csName = L"空";
	if (dNameAddr)
	{
		bi.wName = R_CString(dNameAddr);;//dm.ReadStringAddr(dNameAddr,1,0); //
		//wcscpy(bi.wName, csName.GetBuffer(0));
		//bi.wName = csName;
	}
	bi.dType = R_BYTE(dObjAddr + 0x34);
	//MyTrace(L"getActorInfo 1 名称 %s  resId %d type %d", bi.wName,bi.dResId,bi.dType);

	if (bi.dType == 6 || bi.dType == 7 || bi.dType == 8 || bi.dType == 9)
	{
		//bi.dResAddr = dm.ReadIntAddr(dObjAddr + 0xB48,3);
		//bi.dResType = dm.ReadIntAddr(bi.dResAddr + 0x36,6);
		bi.dResType = R_BYTE(dObjAddr + 0xD18);
		//bi.dResShow = R_BYTE(dObjAddr + 0xD15);
		//MyTrace(L"getActorInfo 是否");
		bi.dResShow = CALL_对象是否可交互(dObjAddr);
		//MyTrace(L"getActorInfo 可交互");
		bi.dResOpen = R_BYTE(dObjAddr + 0xD16);
		bi.dPortalOpen = R_BYTE(dObjAddr + go_PortalOpen);
	}
	if (bi.dType == 11)
	{
		bi.dIsDead = R_BYTE(dObjAddr + 偏移_环境_击打道具是否死亡_类型11);
	}
	if (bi.dType == 7)
	{
		bi.dIsDead = R_BYTE(dObjAddr + 偏移_环境_击打道具是否死亡_类型7);
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
		//bi.dIsDead = CALL_怪物是否已死亡(dObjAddr);
		//bi.dIsDead = CALL_对象是否可交互2(dObjAddr);
		INT64 属性对象 = getAttrAddr(R_DW(dObjAddr + 0x14));
		if (属性对象)
		{
			bi.dCurHp = getEncryValue(属性对象, 1);
			bi.dMaxHp = getEncryValue(属性对象, 0x1B);
		}
		bi.dMonsterSkillNum = 环境::获取对象释放技能组(dObjAddr);
	}
	INT64 dTemp = R_QW(dObjAddr + 0x98);//更新-0218
	bi.坐标.x = R_Float(dTemp + 偏移_坐标);//更新-0218
	bi.坐标.y = R_Float(dTemp + 偏移_坐标 + 4);//更新-0218
	bi.坐标.z = R_Float(dTemp + 偏移_坐标 + 8);//更新-0218
	bi.IsHide = bCheckActorHide(dObjAddr);
	bi.IsEnemy = bCheckActorEnemy(dObjAddr);
	bi.dCanAttack = R_BYTE(dObjAddr + 偏移_怪物_不可攻击偏移);
	bi.是否可以攻击= bCheckActorEnemy1(dObjAddr);
	bi.ID1 = R_DW(dObjAddr + 怪物目标);
	//MyTrace(L"对象地址0x%I64X ID %X %s 类型%d 坐标%0.f/%0.f/%0.f 名称%s\n", dObjAddr, bi.dResId, csName, bi.dType, bi.坐标.x, bi.坐标.y, bi.坐标.z, bi.wName);

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
	bi.fDis = GetDis(bi.坐标.x, bi.坐标.y, bi.坐标.z);
	bi.距离 = 常用功能::计算距离(bi.坐标, 本人::取坐标());
	//MyTrace(L"getActorInfo 3");
	//if (dm.ReadIntAddr(dObjAddr + 0x28,4)==0x0002BFFD)
	return bi;

	//swprintf(buf, L"索引%X\r 对象地址0x%I64X ID %X %s 类型%d 坐标%0.f/%0.f/%0.f\r\n", bi.dIndex, bi.dObjAddr, bi.dObjId, bi.csName, bi.dType, bi.x, bi.y,bi.z);

	//MyTrace(L"索引%X\r 对象地址0x%I64X ID %X %s 类型%d 坐标%0.f/%0.f/%0.f\n",dIndex,dObjAddr,dObjId,csName,dType,x,y,z);
}




objInfo_ 环境::getActorInfo1(INT64 dObjAddr, 坐标_ 自己坐标)
{
	//MyTrace(L"getActorInfo 0");
	objInfo_ bi;
	//memset(&bi, 0, sizeof(objInfo_));
	bi.objBase = dObjAddr;
	bi.dObjId = R_DW(dObjAddr + 0x14);
	bi.dResId = R_DW(dObjAddr + 0x2C);
	bi.ModId = R_DW(dObjAddr + 0x30);
	INT64 dNameAddr = R_QW(dObjAddr + 0x1C);
	CString csName = L"空";
	if (dNameAddr)
	{
		bi.wName = R_CString(dNameAddr);;//dm.ReadStringAddr(dNameAddr,1,0); //
		//wcscpy(bi.wName, csName.GetBuffer(0));
		//bi.wName = csName;
	}
	bi.dType = R_BYTE(dObjAddr + 0x34);
	//MyTrace(L"getActorInfo 1 名称 %s  resId %d type %d", bi.wName,bi.dResId,bi.dType);

	if (bi.dType == 6 || bi.dType == 7 || bi.dType == 8 || bi.dType == 9)
	{
		//bi.dResAddr = dm.ReadIntAddr(dObjAddr + 0xB48,3);
		//bi.dResType = dm.ReadIntAddr(bi.dResAddr + 0x36,6);
		bi.dResType = R_BYTE(dObjAddr + 0xD18);
		//bi.dResShow = R_BYTE(dObjAddr + 0xD15);
		//MyTrace(L"getActorInfo 是否");
		bi.dResShow = CALL_对象是否可交互(dObjAddr);
		//MyTrace(L"getActorInfo 可交互");
		bi.dResOpen = R_BYTE(dObjAddr + 0xD16);
		bi.dPortalOpen = R_BYTE(dObjAddr + go_PortalOpen);
	}
	if (bi.dType == 11)
	{
		bi.dIsDead = R_BYTE(dObjAddr + 偏移_环境_击打道具是否死亡_类型11);
	}
	if (bi.dType == 7)
	{
		bi.dIsDead = R_BYTE(dObjAddr + 偏移_环境_击打道具是否死亡_类型7);
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
		//bi.dIsDead = CALL_怪物是否已死亡(dObjAddr);
		//bi.dIsDead = CALL_对象是否可交互2(dObjAddr);
		INT64 属性对象 = getAttrAddr(R_DW(dObjAddr + 0x14));
		if (属性对象)
		{
			bi.dCurHp = getEncryValue(属性对象, 1);
			bi.dMaxHp = getEncryValue(属性对象, 0x1B);
		}
		bi.dMonsterSkillNum = 环境::获取对象释放技能组(dObjAddr);
	}
	INT64 dTemp = R_QW(dObjAddr + 0x98);//更新-0218
	bi.坐标.x = R_Float(dTemp + 偏移_坐标);//更新-0218
	bi.坐标.y = R_Float(dTemp + 偏移_坐标 + 4);//更新-0218
	bi.坐标.z = R_Float(dTemp + 偏移_坐标 + 8);//更新-0218
	bi.距离 = 常用功能::计算距离(bi.坐标, 自己坐标);
	bi.IsHide = bCheckActorHide(dObjAddr);
	bi.IsEnemy = bCheckActorEnemy(dObjAddr);
	bi.dCanAttack = R_BYTE(dObjAddr + 偏移_怪物_不可攻击偏移);
	bi.是否可以攻击 = bCheckActorEnemy1(dObjAddr);


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
	bi.fDis = bi.距离;
	//MyTrace(L"getActorInfo 3");
	//if (dm.ReadIntAddr(dObjAddr + 0x28,4)==0x0002BFFD)
	return bi;

	//swprintf(buf, L"索引%X\r 对象地址0x%I64X ID %X %s 类型%d 坐标%0.f/%0.f/%0.f\r\n",dIndex,dObjAddr,dObjId,csName,dType,x,y,z);

	//MyTrace(L"索引%X\r 对象地址0x%I64X ID %X %s 类型%d 坐标%0.f/%0.f/%0.f\n",dIndex,dObjAddr,dObjId,csName,dType,x,y,z);
}


int 环境::CALL_对象是否可交互(INT64 环境对象指针)
{
	if (环境对象指针 && !IsBadReadPtr((const void*)环境对象指针, sizeof(环境对象指针)))
	{
		INT64 CALL = R_QW(R_QW(环境对象指针) + go_ActorShow);
		//INT64 CALL = 游戏模块 + gc_ActorShow;
		if (CALL && !IsBadReadPtr((const void*)CALL, sizeof(CALL)))
		{
			return (int)CALL2(环境对象指针, 0, CALL);
		}

	}
	return 0;
}
int 环境::CALL_对象是否可交互2(INT64 环境对象指针)
{
	if (环境对象指针 && !IsBadReadPtr((const void*)环境对象指针, sizeof(环境对象指针)))
	{
		INT64 CALL = R_QW(R_QW(环境对象指针) + go_ActorShow + 8);
		//INT64 CALL = 游戏模块 + gc_ActorShow;
		if (CALL && !IsBadReadPtr((const void*)CALL, sizeof(CALL)))
		{
			return (int)CALL2(环境对象指针, 0, CALL);
		}

	}
	return 0;
}
int 环境::CALL_怪物是否已死亡(INT64 环境对象指针)
{
	if (环境对象指针 && !IsBadReadPtr((const void*)环境对象指针, sizeof(环境对象指针)))
	{
		INT64 CALL = R_QW(R_QW(环境对象指针) + 0x210);
		if (CALL && !IsBadReadPtr((const void*)CALL, sizeof(CALL)))
		{
			return (int)MainUniversalCALL2_Ret(环境对象指针, 0, CALL);
		}

	}
	return 0;
}
void 环境::遍历全部环境对象(vector<objInfo_>& vsk)
{
	vsk.clear();
	objInfo_ 临时;
	INT64 addr_1 = R_QW(游戏模块 + gb_ActorList);
	long dtotal = R_QW(addr_1 + 0x9C + 8 + 0x10 + 0x18);//更新-0218
	INT64 objStartAddr = R_QW(addr_1 + 0x9C + 8);////更新-0218 对象数组地址
	INT64 dKeyAddr = R_QW(addr_1 + 0x9C + 8 + 0x20);//更新-0218
	if (!dKeyAddr)
	{
		dKeyAddr = addr_1 + 0x9C + 8 + 0x10;//更新-0218
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
				临时 = 环境::getActorInfo(dObjAddr);
				if (临时.dResId != 0)
				{
					临时.dObjId = dObjId;
					if (临时.dResId == 0x2B066 || 临时.dResId == 0x2B052)
					{
						continue;
					}

					if (临时.dType == 2 && 临时.是否可以攻击 != 0)
					{
						continue;
					}
					vsk.push_back(临时);
				}

			}
		}
	}
	::sort(vsk.begin(), vsk.end(), flessmark);
}

void 环境::遍历全部环境对象2(vector<objInfo_>& vsk, 坐标_ 自己坐标)
{
	vsk.clear();
	objInfo_ 临时;
	INT64 addr_1 = R_QW(游戏模块 + gb_ActorList);
	long dtotal = R_QW(addr_1 + 0x9C + 8 + 0x10 + 0x18);//更新-0218
	INT64 objStartAddr = R_QW(addr_1 + 0x9C + 8);////更新-0218 对象数组地址
	INT64 dKeyAddr = R_QW(addr_1 + 0x9C + 8 + 0x20);//更新-0218
	if (!dKeyAddr)
	{
		dKeyAddr = addr_1 + 0x9C + 8 + 0x10;//更新-0218
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
				临时 = 环境::getActorInfo1(dObjAddr,自己坐标);


				if (临时.dResId != 0)
				{
					临时.dObjId = dObjId;
					if (临时.dResId == 0x2B066 || 临时.dResId == 0x2B052)
					{
						continue;
					}

					if (临时.dType == 2 && 临时.是否可以攻击 != 0)
					{
						continue;
					}
					vsk.push_back(临时);
				}

			}
		}
	}
	::sort(vsk.begin(), vsk.end(), flessmark);


}




void 环境::遍历全部环境对象1(vector<objInfo_>& vsk)
{
	ActorInfo_ 角色信息 = 本人::取角色信息();
	vsk.clear();
	objInfo_ 临时;
	INT64 addr_1 = R_QW(游戏模块 + gb_ActorList);
	long dtotal = R_QW(addr_1 + 0x9C + 8 + 0x10 + 0x18);//更新-0218
	INT64 objStartAddr = R_QW(addr_1 + 0x9C + 8);////更新-0218 对象数组地址
	INT64 dKeyAddr = R_QW(addr_1 + 0x9C + 8 + 0x20);//更新-0218
	if (!dKeyAddr)
	{
		dKeyAddr = addr_1 + 0x9C + 8 + 0x10;//更新-0218
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
				临时 = 环境::getActorInfo(dObjAddr);
				if (临时.dResId != 0)
				{
					临时.dObjId = dObjId;

					if (临时.dResId == 0x2B066 || 临时.dResId == 0x2B052)
					{
						continue;
					}

					if (临时.dType == 2 && 临时.是否可以攻击 != 0 )
					{
						continue;
					}
				

					vsk.push_back(临时);
				}

			}
		}
	}
	::sort(vsk.begin(), vsk.end(), flessmark);
}

bool 坐标计算(const 坐标_& o1, const 坐标_& o2)
{
	return o1.fDis < o2.fDis;

}
void 最近线路(CString ID文本, vector<坐标_>& vsk)
{
	CArray<CString, CString>分割;
	CArray<CString, CString>分割1;

	vsk.clear();
	if (ID文本.Find(L"|") != -1)
	{
		文本分割(ID文本, '|', &分割);
		if (分割.GetCount() == 0)
		{
			vsk.clear();
		}
		else
		{
			for (size_t i = 0; i < 分割.GetCount(); i++)
			{
				文本分割(分割[i], ',', &分割1);
				if (分割1.GetCount() != 0)
				{ 
					坐标_  x = 本人::取坐标();
					坐标_ 临时;
					临时.x = _ttof(分割1[1]);
					临时.y = _ttof(分割1[2]);
					临时.z = _ttof(分割1[3]);
					临时.fDis = 常用功能::计算距离(临时, x);
					临时.数组位置 = i;
					vsk.push_back(临时);
				}
			

			}
		}
	}
	::sort(vsk.begin(), vsk.end(), 坐标计算);
}


CString 返回最近线路(CString ID文本)
{
	CArray<CString, CString>分割;
	CArray<CString, CString>分割1;
	CString temp;
	vector<坐标_>vsk;
	最近线路(ID文本, vsk);
	if (vsk.size() > 0)
	{
		DWORD 最近数组序号 = vsk[0].数组位置;

		if (ID文本.Find(L"|") != -1)
		{
			文本分割(ID文本, '|', &分割);
			if (分割.GetCount() != 0)
			{
				for (size_t i = 0; i < 分割.GetCount(); i++)
				{
					if (i >= 最近数组序号)
					{
						文本分割(分割[i], ',', &分割1);
						if (分割1.GetCount() != 0)
						{
							temp = temp + 分割[1] + "," + 分割[2] + "," + 分割[3] + "|";
						}

					}


				}

			}

		}
	}

	return temp;

}

void 环境::遍历指定全部环境对象(DWORD dtype, vector<objInfo_>& vsk)
{
	vsk.clear();
	objInfo_ 临时;
	INT64 addr_1 = R_QW(游戏模块 + gb_ActorList);
	long dtotal = R_QW(addr_1 + 0x9C + 8 + 0x10 + 0x18);//更新-0218
	INT64 objStartAddr = R_QW(addr_1 + 0x9C + 8);////更新-0218 对象数组地址
	INT64 dKeyAddr = R_QW(addr_1 + 0x9C + 8 + 0x20);//更新-0218
	if (!dKeyAddr)
	{
		dKeyAddr = addr_1 + 0x9C + 8 + 0x10;//更新-0218
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
					临时 = 环境::getActorInfo(dObjAddr);
					if (临时.dResId != 0)
					{
						临时.dObjId = dObjId;
						vsk.push_back(临时);
					}
				}


			}
		}
	}
	::sort(vsk.begin(), vsk.end(), flessmark);
}


DWORD 环境::范围怪物数量(DWORD 距离)
{
	objInfo_ temp;
	vector<objInfo_>vsk;
	DWORD 数量 = 0;
	环境::遍历全部环境对象1(vsk);
	for (size_t i = 0; i < vsk.size(); i++)
	{
		if (vsk[i].dType == 2 || vsk[i].dType == 3)
		{
			if (vsk[i].dCurHp >= 1 && vsk[i].wName != L"" && vsk[i].IsHide == 0)
			{
				if (vsk[i].距离 < 距离)
				{
					数量 = 数量 + 1;


				}
			}
		}
	}

	return 数量;

}
DWORD 环境::范围怪物数量1(DWORD 距离)
{
	objInfo_ temp;
	vector<objInfo_>vsk;
	DWORD 数量 = 0;
	环境::遍历全部环境对象1(vsk);
	for (size_t i = 0; i < vsk.size(); i++)
	{
		if (vsk[i].dType == 2 )
		{
			if (vsk[i].dCurHp >= 1 && vsk[i].wName != L"" && vsk[i].IsHide == 0)
			{
				if (vsk[i].距离 < 距离)
				{
					数量 = 数量 + 1;


				}
			}
		}
	}

	return 数量;

}



bool 环境::判断怪物(INT64 对象)
{
	INT64 局_判断虚表地址 = R_QW(R_QW(对象) + 偏移_环境_对象虚表);
	INT64 局_指令地址 = 局_判断虚表地址 + 321;
	INT64 局_指令地址2 = 局_指令地址 + 3;
	DWORD 局_临时 = R_QW(局_指令地址2);
	INT64 判断地址 = 局_指令地址 + 局_临时 + 7;
	//CString 文本标识 = CString(UnicodeToAnsi(R_CString(判断地址)));
	CString 文本标识2 = R_CString(判断地址);
	//MyTrace(L"文本标识 %s", 文本标识);
	//MyTrace(L"文本标识2 %s", 文本标识2);
	if (文本标识2 == L"OUTLINE_MONSTER_ENEMY")
	{
		return true;
	}
	return false;

}

void 环境::小退call()
{
	INT64 rcx = 0;

	bool 是否打开 = UI功能::寻找打开窗口("root1.arkui.windowCanvas.exitMenuWindow", rcx);
	if (rcx >= 1)
	{

		MyTrace(L"0X%I64X", rcx);
		MainUniversalCALL4(rcx, 0x1F, 2, 0, 游戏模块 + 基址_小退call);
		Sleep(2000);
	//	UI功能::内存按键(VK_RETURN);
	}


}


DWORD 环境::读取当前对话npc()
{
	DWORD b = 0;

	INT64 局_rcx = R_QW(游戏模块 + 基址_环境_退出npc对话);


	b = R_DW(局_rcx + 0x10C);

	return b;


}
bool 环境::判断NPC(INT64 对象)
{
	INT64 局_判断虚表地址 = R_QW(R_QW(对象) + 偏移_环境_对象虚表);
	INT64 局_指令地址 = 局_判断虚表地址 + 1000;
	INT64 局_指令地址2 = 局_指令地址 + 3;
	DWORD 局_临时 = R_QW(局_指令地址2);
	INT64 判断地址 = 局_指令地址 + 局_临时 + 7;
	//CString 文本标识 = CString(UnicodeToAnsi(R_CString(判断地址)));
	CString 文本标识2 = R_CString(判断地址);
	//MyTrace(L"文本标识 %s", 文本标识2);
	if (文本标识2 == L"OUTLINE_NPC_FRIENDLY")
	{
		return true;
	}
	return false;

}
bool 环境::判断地面物品(INT64 对象)
{
	INT64 局_判断虚表地址 = R_QW(R_QW(对象) + 偏移_环境_对象虚表);
	//*(BYTE*)&局_判断虚表地址[0] = 0x33;
	/*BYTE B对象[3] = { 0 };
	读内存字节集((HANDLE)-1, (LPVOID)局_判断虚表地址, 3, &B对象);*/
	if (R_BYTE(局_判断虚表地址) == 0x33 && R_BYTE(局_判断虚表地址 + 1) == 0xC0 && R_BYTE(局_判断虚表地址 + 2) == 0xC3)
	{
		return true;
	}
	return false;
}
bool 环境::判断采集物(INT64 对象)
{
	INT64 局_判断虚表地址 = R_QW(R_QW(对象) + 偏移_环境_对象虚表);
	INT64 局_指令地址 = 局_判断虚表地址 + 40;
	INT64 局_指令地址2 = 局_指令地址 + 3;
	DWORD 局_临时 = R_QW(局_指令地址2);
	INT64 判断地址 = 局_指令地址 + 局_临时 + 7;
	//CString 文本标识 = CString(UnicodeToAnsi(R_CString(判断地址)));
	CString 文本标识2 = R_CString(判断地址);
	if (文本标识2 == L"OUTLINE_PROP_TOUCH")
	{
		return true;
	}
	return false;

}
bool 环境::判断击打道具(INT64 对象)
{
	INT64 局_判断虚表地址 = R_QW(R_QW(对象) + 偏移_环境_对象虚表);
	INT64 局_指令地址 = 局_判断虚表地址 + 56;
	INT64 局_指令地址2 = 局_指令地址 + 3;
	DWORD 局_临时 = R_QW(局_指令地址2);
	INT64 判断地址 = 局_指令地址 + 局_临时 + 7;
	//CString 文本标识 = CString(UnicodeToAnsi(R_CString(判断地址)));
	CString 文本标识2 = R_CString(判断地址);
	if (文本标识2 == L"OUTLINE_PROP_HIT")
	{
		if (R_DW(对象 + 偏移_类型_击打道具 + 4) == 1)
		{
			return true;
		}
		if (R_DW(对象 + 偏移_类型_击打道具) == 1)
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
bool 环境::击打道具是否死亡(INT64 对象)
{
	if (R_DW(对象 + 偏移_环境_击打道具是否死亡) == 1)
	{
		return true;
	}
	return false;

}

void 环境::遍历怪物(vector<objInfo_>& 数组)
{
	数组.clear();
	vector<objInfo_>vsk;
	环境::遍历指定全部环境对象(2, vsk);
	for (size_t i = 0; i < vsk.size(); i++)
	{

		if ((/*环境::判断怪物(vsk[i].objBase)|| */vsk[i].dType == 2) && vsk[i].dCurHp > 0 && vsk[i].dResId != 0x1FCFC && vsk[i].IsEnemy == true && ID是否已存在(vsk[i].dResId, 暂时不打ID) == false && vsk[i].IsHide == false && vsk[i].dResId != 0xA8B39)
		{
			if (vsk[i].dResId == 0x22F74 || vsk[i].dResId == 0x22F7E)
			{
				if (vsk[i].dCurHp <= 180)
				{
					continue;
				}
			}
			数组.push_back(vsk[i]);
			continue;
		}
		if (vsk[i].dResId == 0x2A106)
		{
			数组.push_back(vsk[i]);
		}
		//if ((/*环境::判断怪物(vsk[i].objBase)|| */vsk[i].dType == 2) && vsk[i].dResId == 0x2A40E)
		//{
		//	数组.push_back(vsk[i]);
		//}
	}
	::sort(数组.begin(), 数组.end(), flessmark);
}

void 环境::遍历NPC(vector<objInfo_>& 数组)
{
	数组.clear();
	vector<objInfo_>vsk;
	环境::遍历指定全部环境对象(3, vsk);
	for (size_t i = 0; i < vsk.size(); i++)
	{
		//if (环境::判断NPC(vsk[i].objBase))
		//{
		数组.push_back(vsk[i]);
		//}
	}
	::sort(数组.begin(), 数组.end(), flessmark);
}
objInfo_ 环境::取指定类型NPC(CString tips)
{
	objInfo_ temp;
	vector<objInfo_>vsk;
	环境::遍历NPC(vsk);
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
void 环境::遍历采集物(vector<objInfo_>& 数组)
{
	数组.clear();
	vector<objInfo_>vsk;
	环境::遍历指定全部环境对象(6, vsk);
	for (size_t i = 0; i < vsk.size(); i++)
	{
		if (/*环境::判断采集物(vsk[i].objBase) &&*/ vsk[i].dType == 6)
		{
			数组.push_back(vsk[i]);
		}
	}
}

void 环境::遍历击打道具(vector<objInfo_>& 数组)
{
	数组.clear();
	vector<objInfo_>vsk;
	MyTrace(L"%s 7", __FUNCTIONW__);
	环境::遍历指定全部环境对象(7, vsk);
	for (size_t i = 0; i < vsk.size(); i++)
	{
		if (ID是否已存在(vsk[i].dResId, 暂时不打ID))
		{
			continue;
		}
		if ((/*环境::判断击打道具(vsk[i].objBase) || */vsk[i].dType == 7) && 击打道具是否死亡(vsk[i].objBase) == false && vsk[i].dResShow == 1 && vsk[i].dIsDead != 0)
		{
			数组.push_back(vsk[i]);
			continue;
		}
		/*if (vsk[i].dType == 7 && 击打道具是否死亡(vsk[i].objBase) == false  && vsk[i].dIsDead == 5 && vsk[i].IsEnemy==true)
		{
			数组.push_back(vsk[i]);

		}*/
		/*if (vsk[i].wName == L"tip.name.tower_82204")
		{
			数组.push_back(vsk[i]);
		}*/
	}
	MyTrace(L"%s 11", __FUNCTIONW__);
	环境::遍历指定全部环境对象(11, vsk);
	for (size_t i = 0; i < vsk.size(); i++)
	{
		if (ID是否已存在(vsk[i].dResId, 暂时不打ID))
		{
			continue;
		}
		if (vsk[i].dType == 11 && vsk[i].dIsDead == 0)
		{
			数组.push_back(vsk[i]);
		}
	}
	::sort(数组.begin(), 数组.end(), flessmark);
}

void 环境::遍历地面物品(vector<objInfo_>& 数组)
{
	数组.clear();
	vector<objInfo_>vsk;
	环境::遍历指定全部环境对象(4, vsk);
	for (size_t i = 0; i < vsk.size(); i++)
	{
		数组.push_back(vsk[i]);
	}
}
void 环境::遍历电梯(vector<objInfo_>& 数组)
{
	数组.clear();
	vector<objInfo_>vsk;
	环境::遍历指定全部环境对象(15, vsk);
	for (size_t i = 0; i < vsk.size(); i++)
	{
		if (vsk[i].dType == 15 && vsk[i].fDis < 500)
		{
			数组.push_back(vsk[i]);
		}
	}
	::sort(数组.begin(), 数组.end(), flessmark);
}
void 环境::遍历传送门(vector<objInfo_>& 数组)
{
	数组.clear();
	vector<objInfo_>vsk;
	环境::遍历全部环境对象(vsk);
	for (size_t i = 0; i < vsk.size(); i++)
	{
		if (vsk[i].dResId == 0x1181D || vsk[i].dResId == 0x1398C || vsk[i].dResId == 0x139A1 || vsk[i].dResId == 0x92BC7 || vsk[i].dResId == 0x139A2 || vsk[i].dResId == 0x14410 || vsk[i].dResId == 0x1AE33 || vsk[i].dResId == 0x1155E || vsk[i].dResId == 0x4F1B || vsk[i].dResId == 0xA02B || vsk[i].dResId == 0xA08C || vsk[i].dResId == 0xA607 || vsk[i].dResId == 0xA090 || vsk[i].dResId == 0x1B4C2
			|| vsk[i].dResId == 0x1B5EE || vsk[i].dResId == 0x1B1B7)
		{
			/*if (地图::指定地点是否可到达_M(vsk[i].坐标.x, vsk[i].坐标.y, vsk[i].坐标.z))
			{*/
			数组.push_back(vsk[i]);
			//}

		}
	}
	::sort(数组.begin(), 数组.end(), flessmark);
}
objInfo_ 环境::取指定对象信息(DWORD ResId)
{
	objInfo_ temp;
	vector<objInfo_>vsk;
	遍历全部环境对象(vsk);
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
objInfo_ 环境::取随机怪物信息()
{
	objInfo_ temp;
	vector<objInfo_>vsk;
	遍历全部环境对象(vsk);
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
objInfo_ 环境::取指定采集对象信息(DWORD ResId)
{
	objInfo_ temp;
	vector<objInfo_>vsk;
	遍历全部环境对象(vsk);
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

objInfo_ 环境::取指定任务显示对象信息(DWORD ResId, DWORD ResShow)
{
	objInfo_ temp;
	vector<objInfo_>vsk;
	遍历全部环境对象(vsk);
	for (size_t i = 0; i < vsk.size(); i++)
	{
		if ((ResId == vsk[i].dResId || ID是否已存在(vsk[i].dResId, 优先采集ID)) && vsk[i].dResShow == ResShow)
		{
			temp = vsk[i];
			break;
		}
	}
	return temp;
}
objInfo_ 环境::取指定范围任务显示对象信息(float x, float y, float z, float 距离, DWORD ResId)
{
	objInfo_ temp;
	vector<objInfo_>vsk;
	遍历全部环境对象(vsk);
	for (size_t i = 0; i < vsk.size(); i++)
	{

		if (ResId == vsk[i].dResId && vsk[i].dResShow == 1)
		{

			if (距离计算3(x, y, z, vsk[i].坐标.x, vsk[i].坐标.y, vsk[i].坐标.z) < 距离)
			{
				temp = vsk[i];
				break;
			}

		}
		if (ID是否已存在(vsk[i].dResId, 优先采集ID) == true && vsk[i].dResShow == 1)
		{
			if (距离计算3(x, y, z, vsk[i].坐标.x, vsk[i].坐标.y, vsk[i].坐标.z) < 距离)
			{
				temp = vsk[i];
				break;
			}

		}
	}
	return temp;
}
坐标_ 环境::取对象坐标(INT64 对象)
{
	坐标_ 坐标;
	INT64 局_坐标地址 = R_QW(对象 + 148 + 4);
	坐标.x = R_Float(局_坐标地址 + 偏移_坐标);
	坐标.y = R_Float(局_坐标地址 + 偏移_坐标 + 4);
	坐标.z = R_Float(局_坐标地址 + 偏移_坐标 + 8);
	return 坐标;
}
bool 环境::CALL_打开NPC(INT64 对象)
{
	坐标_ 坐标 = 环境::取对象坐标(对象);
	INT64 局_关键值 = R_QW(对象 + 148 + 4);
	INT64 局_rcx = R_QW(R_QW(R_QW(游戏模块 + 基址_个人_坐标) + 0x94) + 16);
	if (局_rcx == 0)
	{
		return false;
	}
	UCHAR pBuff[0x30] = { 0 };
	W_QW((ULONG64)&pBuff[0x0], 0);
	W_QW((ULONG64)&pBuff[0x8], 0);
	W_QW((ULONG64)&pBuff[0x10], 0);
	W_Float((ULONG64)&pBuff[0x18], 坐标.x);
	W_Float((ULONG64)&pBuff[0x1C], 坐标.y);
	W_Float((ULONG64)&pBuff[0x20], 坐标.z);
	W_QW((ULONG64)&pBuff[0x28], 局_关键值);
	MainUniversalCALL2(局_rcx, (ULONG_PTR)pBuff, 游戏模块 + 基址_环境_打开npc);
	return true;

}
bool 环境::CALL_退出NPC()
{
	INT64 局_rcx = R_QW(游戏模块 + 基址_环境_退出npc对话);
	INT64 局_call = R_QW(R_QW(局_rcx) + 0x40);
	if (局_rcx == 0 || 局_call == 0)
	{
		return false;
	}
	MainUniversalCALL2(局_rcx, 2, 局_call);
	return true;
}
bool 环境::CALL_NPC对话分支(int 对话序号)
{
	INT64 局_rcx = R_QW(游戏模块 + 基址_环境_退出npc对话);
	if (局_rcx == 0)
	{
		return false;
	}
	MainUniversalCALL4(局_rcx, 4, 2, 对话序号, 游戏模块 + 基址_环境_npc对话分支call);
	return true;
}
int 环境::读取当前对话NPC()
{
	INT64 局_rcx = R_QW(游戏模块 + 基址_环境_退出npc对话);
	if (局_rcx)
	{
		return R_DW(局_rcx + 0x170);
	}
	return 0;
}
bool 环境::是否在和NPC对话()
{
	DWORD 局_标志 = R_DW(R_QW(游戏模块 + 基址_环境_npc对话标志) + 88);
	if (局_标志 == 1)
	{
		return true;
	}
	return false;
}

bool 环境::是否在加载页面()
{
	DWORD 局_标志 = R_DW(游戏模块 + 基址_环境_是否处于加载界面);
	if (局_标志 == 1)
	{
		return true;
	}
	return false;
}
bool 环境::是否在加载页面2()
{
	INT64 局_rcx = R_QW(游戏模块 + gb_判断加载基址);
	局_rcx = R_QW(局_rcx + go_加载偏移1);
	DWORD 局_标志 = R_DW(局_rcx + go_加载偏移2);
	if (局_标志 == 1 || 局_标志 == 2)
	{
		return true;
	}
	return false;
}
bool 环境::是否在动画()
{
	DWORD 局_标志 = R_DW(R_QW(游戏模块 + 基址_环境_判断动画) + 136);
	if (局_标志 == 0)
	{
		return false;
	}
	return true;
}

DWORD 环境::剩余气息查询()
{
	DWORD 局_标志 = R_DW(R_QW(游戏模块 + 基址_环境_判断动画) + 0x58);
	return 局_标志;
 }


bool 环境::拾物(INT64 对象)
{
	INT64 局_call = 游戏模块 + 基址_环境_拾物call;
	INT64 局_rcx = R_QW(R_QW(R_QW(游戏模块 + 基址_环境_传送rcx - 8) + 偏移_环境_拾物) + 偏移_环境_拾物2);
	if (!局_rcx)
	{
		return false;
	}
	DWORD 局_物品id = R_DW(对象 + 20);
	MainUniversalCALL2(局_rcx, 局_物品id, 局_call);
	return true;
}

bool 环境::CALL_点击指定NPC(CString 对象名称)
{
	vector<objInfo_>数组;
	环境::遍历NPC(数组);
	for (size_t i = 0; i < 数组.size(); i++)
	{
		if (对象名称 == 数组[i].wName)
		{
			环境::CALL_打开NPC(数组[i].objBase);
			return true;
		}
	}
	return false;
}
bool 环境::CALL_点击指定NPC_ByResId(DWORD ResId)
{
	vector<objInfo_>数组;
	环境::遍历NPC(数组);
	for (size_t i = 0; i < 数组.size(); i++)
	{
		if (ResId == 数组[i].dResId && !数组[i].IsHide)
		{
			MyTrace(L"打开NPC,0x%I64X", 数组[i].objBase);
			环境::CALL_打开NPC(数组[i].objBase);
			return true;
		}
	}
	return false;
}
float 环境::获取对象角度值(INT64 obj)
{
	if (obj)
	{
		INT64 addr1 = R_QW(obj + 0x98);
		float addr2 = R_DW(addr1 + 偏移_其他_面向角度 + 4);
		return addr2;
	}
	return 0;
}
int 环境::获取对象释放技能组(INT64 obj)
{
	DWORD 数量 = 0;
	if (obj)
	{
		INT64 addr1 = R_QW(obj + 0x98);
		INT64 数组头 = R_QW(addr1 + 0x15C);
		DWORD 数组数量 = R_DW(addr1 + 0x15C + 8);
		//for (size_t i = 0; i < 数组数量; i++)
		//{
		//	INT64 技能释放对象 = R_QW(数组头 + i * 8);
		//	DWORD 技能ID = R_DW(技能释放对象 + 0x448);
		//	float x = R_Float(技能释放对象 + 偏移_坐标);
		//	float y = R_Float(技能释放对象 + 偏移_坐标 + 4);
		//	float z = R_Float(技能释放对象 + 偏移_坐标 + 8);
		//	//MyTrace(L"对象 0x%I64X 技能ID %d %0.3f %0.3f %0.3f", 技能释放对象, 技能ID, x, y, z);
		//}
		数量 = 数组数量;
	}
	return 数量;
}

bool NPC::CALL_ShopBuyAddItem(int dItemIndex)//索引从1开始 先调用添加
{
	INT64 addr_1 = R_QW(游戏模块 + gb_ShopBase);
	if (addr_1 == 0)
	{
		return false;
	}
	int dTotal = R_DW(addr_1 + go_ShopBuyItemListStart + 8);
	if (dTotal <= 10)//最多添加10个
	{
		MainUniversalCALL4(addr_1, dItemIndex, 1, 0, 游戏模块 + gc_ShopBuyAddItem);
		return true;
	}
	return false;
}

bool NPC::ShopBuyItemClick()//点击购买按钮
{

	INT64 addr_1 = R_QW(游戏模块 + gb_ShopBase);
	if (R_DW(addr_1 + go_ShopBuyItemState) == 0)//状态
	{
		if (R_DW(addr_1 + go_ShopBuyItemListStart + 8))//判断添加物品
		{
			UCHAR buff[0x1000] = { 0 };
			MainUniversalCALL2((ULONG_PTR)buff, 0, 游戏模块 + gc_ShopBuyItem);
			return true;
		}

	}
	return false;
}

void NPC::get_ShopItemList(vector<Inventoryinfo_>& 商店购买组)
{

	商店购买组.clear();
	INT64 addr_1 = R_QW(游戏模块 + gb_ShopBase);
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
			商店购买组.push_back(temp);
			/*wchar_t buf[100];
			swprintf(buf, L"索引%d 资源ID %X %s 类型%X 价格%d\r\n", dIndex, dResId, csName, dSlotIndex, dPrice);
			g_String.Insert(g_String.GetLength(), buf);*/
		}
	}
}
DWORD 环境::获取当前电梯ID()
{
	return R_DW(游戏模块 + 偏移_环境_升降机标志);
}

void 环境::加入优先采集ID(CString ID文本)
{
	CArray<CString, CString>返回文本组;
	优先采集ID.clear();
	if (ID文本.Find(L"|") == -1)
	{
		if (ID是否已存在(_ttoi(ID文本), 优先采集ID) == false)
		{
			优先采集ID.push_back(_ttoi(ID文本));
		}
	}
	else
	{
		文本分割(ID文本, '|', &返回文本组);
		if (返回文本组.GetCount() == 0)
		{
			优先采集ID.clear();
		}
		else
		{

			for (size_t i = 0; i < 返回文本组.GetCount(); i++)
			{
				if (ID是否已存在(_ttoi(返回文本组[i]), 优先采集ID) == false)
				{
					优先采集ID.push_back(_ttoi(返回文本组[i]));
				}

			}
		}
	}
}