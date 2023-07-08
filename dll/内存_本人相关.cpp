#include "内存_本人相关.h"

INT64 本人::取真实对象()
{
	return R_QW(R_QW(游戏模块 + 基址_个人_坐标) + 160);
}
INT64 本人::取对象()
{
	INT64 局_遍历基址 = 游戏模块 + 基址_个人_遍历;
	INT64 局_虚表判断地址 = 游戏模块 + 基址_个人_判断虚表;
	INT64 局_rcx = R_QW(R_QW(局_遍历基址) + 0xA4) + 0x2F8;
	INT64 局_数组头 = R_QW(局_rcx);
	DWORD 局_数量 = R_DW(局_rcx + 0x28);
	for (size_t i = 0; i < 局_数量; i++)
	{
		INT64 局_对象 = R_QW(局_数组头 + i * 5 * 4 + 4);
		if (局_对象 != 0)
		{
			INT64 局_临时虚表地址 = R_QW(R_QW(局_对象) + 0x58);
			if (局_临时虚表地址 == 局_虚表判断地址)
			{
				return 局_对象;
			}
		}
	}
	return 0;
}
void 本人::CALL_发包复活(DWORD 复活类型)
{
	INT64 局_rcx = R_QW(游戏模块 + 基址_封包_发包rcx);
	INT64 局_call = 游戏模块 + 基址_封包_发包call;
	INT64 局_复活包头 = 游戏模块 + 基址_个人_复活包头;
	UCHAR pBuff[0x24] = { 0 };
	W_QW((ULONG64)&pBuff[0x0], 局_复活包头);
	W_QW((ULONG64)&pBuff[0x8], 0);
	W_QW((ULONG64)&pBuff[0x10], 0);
	W_Word((ULONG64)&pBuff[0x16], 0x230);
	W_BYTE((ULONG64)&pBuff[0x17], 复活类型);
	MainUniversalCALL2(局_rcx, (ULONG_PTR)pBuff, 局_call);
	//*(DWORD*)&pBuff[0x0]
}

void 本人::改移动速度(bool 开关, float 修改值)
{
	INT64 局_速度校验地址 = 游戏模块 + 基址_个人_速度校验地址;
	INT64 局_速度地址 = R_QW(本人::取真实对象() + 偏移_本人_移速1) + 偏移_本人_移速2;
	if (开关)
	{
		BYTE 修改[2] = { 235,33 };
		DWORD old_protect;
		VirtualProtect((LPVOID)局_速度校验地址, 2, 64, &old_protect);
		memcpy((LPVOID)局_速度校验地址, (void*)&修改, 2);
		VirtualProtect((LPVOID)局_速度校验地址, 2, old_protect, &old_protect);
		W_Float(局_速度地址, 修改值);
	}
	else
	{
		BYTE 修改[2] = { 117,33 };
		DWORD old_protect;
		VirtualProtect((LPVOID)局_速度校验地址, 2, 64, &old_protect);
		memcpy((LPVOID)局_速度校验地址, (void*)&修改, 2);
		VirtualProtect((LPVOID)局_速度校验地址, 2, old_protect, &old_protect);
	}
}
bool 本人::乐谱遍历(vector<乐谱信息_>& vsk)
{
	vsk.clear();
	乐谱信息_ temp;
	INT64 局_rcx = R_QW(游戏模块 + 基址_个人_乐谱遍历rcx);
	if (!局_rcx)
	{
		return false;
	}
	INT64 局_rdx = R_QW(游戏模块 + 基址_个人_乐谱遍历rdx);
	if (!局_rdx)
	{
		return false;
	}
	INT64 局_CALL = 游戏模块 + 基址_个人_乐谱遍历call;
	for (size_t i = 1; i <= 22; i++)
	{
		if (i == 20)
		{
			continue;
		}
		INT64 ret = CALL4(局_rcx, 局_rdx, i, 0, 局_CALL);
		if (ret)
		{
			temp.Obj = R_QW(R_QW(ret) + 12);
			temp.序号 = i;
			temp.名称 = CString(UnicodeToAnsi(R_CString(R_QW(temp.Obj + 0x20))));
			MyTrace(L"0x%I64X 序号:%d 名称：%s", temp.Obj, temp.序号, temp.名称);
			vsk.push_back(temp);
		}

	}
	return true;
}

DWORD 本人::取当前船只ID()
{
	return R_DW(R_QW(游戏模块 + 基址_UI_航海出港rcx) + 256);
}
DWORD 本人::获取InteractPropState状态()
{
	INT64 局_个人真实对象 = 本人::取真实对象();
	DWORD InteractPropState = R_DW(局_个人真实对象 + go_GetInteractPropState);
	return InteractPropState;
}
ActorInfo_ 本人::取角色信息()
{
	ActorInfo_ 临时角色信息;
	INT64 局_个人真实对象 = 本人::取真实对象();
	INT64 局_个人对象 = 本人::取对象();
	临时角色信息.名称 = R_CString(R_QW(局_个人真实对象 + 0x1C));
	临时角色信息.等级 = R_W(R_QW(R_QW(游戏模块 + gb_AttrList) + 0xE4) + 30);
	INT64 属性对象 = getAttrAddr(R_DW(局_个人真实对象 + 0x14));
	//MyTrace(L"取角色信息 %s %d 0x%I64X",临时角色信息.名称, 临时角色信息.等级, 属性对象);
	临时角色信息.装备评分 = R_Float(属性对象 + 偏移_本人_装备评分);
	/*临时角色信息.当前血 = getEncryValue(属性对象, 1);
	临时角色信息.当前蓝 = getEncryValue(属性对象, 2);
	临时角色信息.最大血 = getEncryValue(属性对象, 0x1B);
	临时角色信息.最大蓝 = getEncryValue(属性对象, 0x1C);*/
	临时角色信息.当前血 = R_DW(局_个人对象 + 偏移_本人_最大血 + 4);
	临时角色信息.当前蓝 = R_DW(局_个人对象 + 偏移_本人_最大血 + 12);
	临时角色信息.最大血 = R_DW(局_个人对象 + 偏移_本人_最大血);
	临时角色信息.最大蓝 = R_DW(局_个人对象 + 偏移_本人_最大血 + 8);
	临时角色信息.航海当前耐久 = R_DW(属性对象 + 偏移_本人_航海耐久);
	临时角色信息.航海最大耐久 = R_DW(属性对象 + 偏移_本人_航海耐久 + 4);
	INT64 addr2 = R_QW(局_个人真实对象 + 偏移_个人_当前怒气值);
	DWORD 当前怒气值 = R_DW(addr2 + 0x14);
	临时角色信息.怒气值 = 当前怒气值;
	临时角色信息.InteractPropState = R_DW(局_个人真实对象 + go_GetInteractPropState);
	INT64 addr3 = R_QW(R_QW(局_个人真实对象 + 偏移_个人_当前动作 + 0x30));
	DWORD 当前动作值 = R_DW(addr3 + 0x30);
	//DWORD 举起状态 = R_DW(局_个人真实对象 + 0x234);
	临时角色信息.当前动作 = 当前动作值;
	临时角色信息.举起状态 = 举起东西状态();
	//MyTrace(L"取角色信息2 %d %d/%d  %d %d %d 举起 %d", 临时角色信息.装备评分, 临时角色信息.当前血, 临时角色信息.最大血, 临时角色信息.航海当前耐久, 临时角色信息.怒气值, 临时角色信息.InteractPropState, 临时角色信息.举起状态);
	/// <summary>
	/// /////////////////////
	/// </summary>
	/// <returns></returns>
	INT64 局_v1 = R_QW(R_QW(R_QW(R_QW(游戏模块 + 基址_个人_坐标) + 0x94) + 0x10) + 0x27C);
	//INT64 局_v1 = R_QW(R_QW(游戏模块 + 基址_个人_坐标) + 0x94);
	临时角色信息.坐标.x = R_Float(局_v1 + 偏移_坐标);
	临时角色信息.坐标.y = R_Float(局_v1 + 偏移_坐标 + 4);
	临时角色信息.坐标.z = R_Float(局_v1 + 偏移_坐标 + 8);
	//MyTrace(L"取角色信息3");
	//MyTrace(L"装备评分 %0.3f", R_Float(属性对象 + 偏移_本人_装备评分));
	return 临时角色信息;
}

bool 本人::是否在骑马()
{
	INT64 局_人物对象 = 本人::取对象();
	bool 局_骑马状态 = R_BYTE(局_人物对象 + 偏移_本人_骑马状态);
	return 局_骑马状态;
}

bool 本人::是否在走路()
{
	INT64 局_人物对象 = 本人::取真实对象();
	bool 局_状态值 = R_BYTE(R_QW(局_人物对象 + 偏移_本人_走路状态) + 0x2C);
	return 局_状态值;
}
bool 本人::是否在走路2()
{
	INT64 局_个人真实对象 = 本人::取真实对象();
	INT64 addr3 = R_QW(R_QW(局_个人真实对象 + 偏移_个人_当前动作 + 0x30));
	DWORD 当前动作值 = R_DW(addr3 + 0x30);
	if (当前动作值 == 1)
	{
		return true;
	}
	return false;
}

DWORD 本人::举起东西状态()
{
	INT64 局_状态对象 = R_QW(游戏模块 + gb_ActorTakeStatus);
	DWORD 局_状态值 = R_DW(局_状态对象 + 8);
	return 局_状态值;
}

void 本人::CALL_做社交动作(DWORD 动作值)//62014
{
	INT64 局_rcx = R_QW(游戏模块 + 基址_个人_社交动作rcx);
	INT64 dCALL = 游戏模块 + 基址_个人_社交动作call;
	MainUniversalCALL2(局_rcx, 动作值, dCALL);
}

void 本人::CALL_使用坐骑(DWORD 坐骑ID)//62014
{
	INT64 局_rcx = R_QW(游戏模块 + 基址_背包_遍历);
	INT64 dCALL = 游戏模块 + 基址_坐骑_使用坐骑call;
	MainUniversalCALL2(局_rcx, 坐骑ID, dCALL);
}

void 本人::CALL_修理船只(DWORD 船只ID)//62014
{
	INT64 局_rcx = R_QW(游戏模块 + 基址_UI_航海出港rcx);
	INT64 dCALL = 游戏模块 + 基址_本人_修理船只call;
	MainUniversalCALL2(局_rcx, 船只ID, dCALL);
}
void 本人::CALL_演奏乐谱(DWORD 乐谱序号)//62014
{


	INT64 局_rcx = R_QW(游戏模块 + 基址_个人_演奏乐谱rcx);
	INT64 dCALL = 游戏模块 + 基址_个人_演奏乐谱call;
	MainUniversalCALL4(局_rcx, 乐谱序号, 0, 0, dCALL);
	/*序号：1 对象：000001ED650B36C0 名字：逃生之歌
		序号：2 对象：000001ED650B31C0 名字：勇气之歌
		序号：3 对象：000001ED650B3080 名字：共鸣之歌
		序号：4 对象：000001ED650B2F40 名字：特里希温之歌
		序号：5 对象：000001ED650B2E00 名字：心潮如歌
		序号：6 对象：000001ED650B2CC0 名字：诱惑之歌
		序号：7 对象：000001ED650B2B80 名字：春天之歌
		序号：8 对象：000001ED650B2A40 名字：爱情小夜曲
		序号：9 对象：000001ED650B7900 名字：森林小步舞曲
		序号：10 对象：000001ED650B77C0 名字：暮光安魂曲
		序号：11 对象：000001ED650B7680 名字：回想之歌
		序号：12 对象：000001ED65074340 名字：星光之歌
		序号：13 对象：000001ED65074480 名字：天界和声
		序号：14 对象：000001ED650740C0 名字：寂静的哀悼曲
		序号：15 对象：000001ED65074200 名字：宁静的领地之歌
		序号：16 对象：000001EC512A4840 名字：庆典之歌
		序号：17 对象：000001EC512A0D80 名字：永恒之歌
		序号：18 对象：000001ECE4A18A80 名字：回归之歌
		序号：19 对象：000001ECE4A18BC0 名字：浪漫兵器
		序号：21 对象：000001ECE4A190C0 名字：凄婉安魂曲
		序号：22 对象：000001ECE4A17180 名字：和谐之歌*/
}
void 本人::CALL_打开分解()//62014
{
	INT64 局_rcx = R_QW(游戏模块 + 基址_个人_打开分解rcx);
	INT64 dCALL = 游戏模块 + 基址_个人_打开分解call;
	MainUniversalCALL4(局_rcx, 0x25, 0, 0, dCALL);
}

void 本人::CALL_全部分解()//62014
{
	INT64 局_rcx = R_QW(游戏模块 + 基址_个人_分解rcx);
	INT64 dCALL = 游戏模块 + 基址_个人_分解call;
	MainUniversalCALL4(局_rcx, 0, 0, 0, dCALL);
}

坐标_ 本人::取坐标()
{
	坐标_ 临时坐标;
	INT64 局_v1 = R_QW(R_QW(R_QW(R_QW(游戏模块 + 基址_个人_坐标) + 0x94) + 0x10) + 0x27C);
	//MyTrace(L"0x%I64x", 局_v1);
	//INT64 局_v1 =R_QW(R_QW(游戏模块 + 基址_个人_坐标) + 0x94);
	临时坐标.x = R_Float(局_v1 + 偏移_坐标);
	临时坐标.y = R_Float(局_v1 + 偏移_坐标 + 4);
	临时坐标.z = R_Float(局_v1 + 偏移_坐标 + 8);
	//MyTrace(L"装备评分 %0.3f", R_Float(属性对象 + 偏移_本人_装备评分));
	return 临时坐标;
}
INT64 本人::取坐标基址()
{
	INT64 局_v1 = R_QW(R_QW(R_QW(R_QW(游戏模块 + 基址_个人_坐标) + 0x94) + 0x10) + 0x27C);

	return 局_v1;
}
bool 本人::是否已召唤宠物()
{
	INT64 局_RCX = R_QW(游戏模块 + 基址_个人_召唤宠物rcx);
	if (R_QW(局_RCX + 0xB4))
	{
		return true;
	}
	return false;
}
void 本人::遍历宠物(vector<INT64>& 宠物ID)
{
	宠物ID.clear();
	INT64 局_RCX = R_QW(游戏模块 + 基址_个人_召唤宠物rcx);
	INT64 数组首 = R_QW(局_RCX + 0x9C);
	INT64 数组尾 = R_QW(局_RCX + 0xA4);
	DWORD total = (数组尾 - 数组首) / 0x10;
	for (size_t i = 0; i < total; i++)
	{
		INT64 addr = R_QW(数组首 + i * 0x10);
		INT64 ID = R_QW(addr);
		宠物ID.push_back(ID);
	}
}
bool 本人::CALL_召唤宠物(INT64 宠物ID)
{
	INT64 局_RCX = R_QW(游戏模块 + 基址_个人_召唤宠物rcx);
	if (R_QW(局_RCX + 0xB4))
	{
		return false;
	}
	MainUniversalCALL2(局_RCX, 宠物ID, 游戏模块 + 基址_个人_召唤宠物call);
	return true;
}
bool 本人::召唤宠物()
{
	if (!是否已召唤宠物())
	{
		vector<INT64>宠物ID组;
		遍历宠物(宠物ID组);
		if (宠物ID组.size() != 0)
		{
			CALL_召唤宠物(宠物ID组[0]);
		}
		else
		{
			if (!UI功能::背包界面是否显示())
			{
				UI功能::Fun_UiShowCtrl(0x1A);
			}
			背包::使用背包指定物品_ByResId(0x24A4A);
			Sleep(1000);
			UI功能::内存按键(VK_RETURN);
			if (UI功能::背包界面是否显示())
			{
				UI功能::Fun_UiShowCtrl(0x1A);
			}
		}
		return false;
	}
	else
	{
		return true;
	}

}
//bool 本人::使用表情CALL(DWORD 表情id)
//{
//	INT64 使用表情rcx = R_QW(游戏模块 + 基址_个人_使用表情rcx);
//	INT64 使用表情call = 游戏模块 + 基址_个人_使用表情call;
//	if (使用表情rcx == 0)
//	{
//		return false;
//	}
//	MainUniversalCALL2(使用表情rcx, 表情id, 使用表情call);
//	return true;
//}
bool 本人::get_ActionTimingTime()
{
	INT64 addr_1 = R_QW(游戏模块 + gb_ActorList);
	INT64 addr_2 = R_QW(addr_1 + go_hj_myRole);
	INT64 addr_3 = R_QW(addr_2 + 0x18);
	INT64 addr_4 = R_QW(addr_3 + go_hj_VehicleId + 0x10);//真实地址
	INT64 addr_Data = R_QW(addr_4 + go_ActionTimingData);
	if (addr_Data)
	{
		for (int i = 0; i < 9; i++)
		{
			int dState = R_DW(addr_4 + go_ActionTimingData + 0x8 + i * 4);
			if (dState != 0)
			{
				float dCurTime = R_Float(addr_Data);
				float dMaxTime = R_Float(addr_Data + go_ActionTimingMaxTime - 8);
				if (dCurTime < dMaxTime)
				{
					MyTrace(L"时间 %0.f / %0.f", dCurTime, dMaxTime);
					return true;
				}

			}
		}
	}
	return false;
}


INT64 本人::最近怪物(DWORD 距离)
{
	ActorInfo_ add = 取角色信息();
	objInfo_ temp;
	vector<objInfo_>vsk;
	环境::遍历全部环境对象1(vsk);
	DWORD obj距离 = 999999;
	INT64 返回指针 = 0;

	for (size_t i = 0; i < vsk.size(); i++)
	{
		if (vsk[i].dType == 2)
		{
			if (vsk[i].dCurHp >= 1 && vsk[i].wName != L"")
			{
				if (vsk[i].距离 < 距离)
				{
					if (vsk[i].距离 < obj距离)
					{
						obj距离 = vsk[i].距离;
						返回指针 = vsk[i].dObjId;

					}
				}
			}

		}
	}
	return 返回指针;


}




INT64 本人::最近怪物1(DWORD 距离)
{

	objInfo_ temp;
	vector<objInfo_>vsk;
	环境::遍历全部环境对象1(vsk);
	DWORD obj距离 = 999999;
	INT64 返回指针 = 0;

	for (size_t i = 0; i < vsk.size(); i++)
	{
		if (vsk[i].dType == 2)
		{
			if (vsk[i].dCurHp >= 1 && vsk[i].wName != L"" && vsk[i].IsHide == 0)
			{
				if (vsk[i].距离 < 距离)
				{


					返回指针 = vsk[i].objBase;
					break;

				}
			}

		}
	}
	return 返回指针;


}




INT64 本人::最近怪物2(DWORD 距离, CString ID文本)
{
	CArray<CString, CString>返回文本组;
	ActorInfo_ add = 取角色信息();
	objInfo_ temp;
	vector<objInfo_>vsk;
	环境::遍历全部环境对象1(vsk);
	DWORD obj距离 = 999999;
	INT64 返回指针 = 0;

	for (size_t i = 0; i < vsk.size(); i++)
	{
		if (vsk[i].dType == 2)
		{
			if (vsk[i].dCurHp >= 1 && vsk[i].wName != L"" && vsk[i].IsHide == 0 && vsk[i].是否可以攻击 == 0)
			{
				if (vsk[i].距离 < 距离)
				{
					if (ID文本 == L"")
					{
						返回指针 = vsk[i].objBase;
						break;
					}
					else
					{
						if (ID文本.Find(L"|") == -1)
						{
							DWORD 临时id = 常用功能::十六进制转十进制(CStringA(ID文本));
							if (临时id == vsk[i].dResId)
							{
								返回指针 = vsk[i].objBase;
								break;
							}
						}
						else
						{
							文本分割(ID文本, '|', &返回文本组);
							if (返回文本组.GetCount() == 0)
							{
								返回指针 = 0;
								break;
							}
							else
							{
								for (size_t i = 0; i < 返回文本组.GetCount(); i++)
								{
									DWORD 临时id = 0;

									临时id = 常用功能::十六进制转十进制(CStringA(ID文本));
									if (临时id == vsk[i].dResId)
									{
										返回指针 = vsk[i].objBase;
										return 返回指针;

									}


								}


							}


						}
					}
				}
			}

		}
	}
	return 返回指针;


}