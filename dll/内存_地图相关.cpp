#include "内存_地图相关.h"

int 地图::取地图ID()
{
	return R_DW(游戏模块 + 基址_环境_地图ID);
}
int 地图::取当前大陆ID()
{
	INT64 MapAddr = getMapResAddrById(地图::取地图ID());
	return R_BYTE(MapAddr + 88);
}

void 地图::传送(DWORD 传送ID)
{
	INT64 局_RCX = R_QW(游戏模块 + 基址_环境_传送rcx);
	INT64 局_dCALL = 游戏模块 + 基址_环境_传送call;
	UCHAR pBuff[0x140] = { 0 };
	W_QW((ULONG64)&pBuff[0x0], 7773890805770);
	W_QW((ULONG64)&pBuff[0x8], -4294967296);
	W_QW((ULONG64)&pBuff[0x20], (ULONG64)&pBuff + 80);
	W_DW((ULONG64)&pBuff[0x128], 0xCF11);// 6月5日 linjinmao 改 2.276719213937e+014); 
	W_DW((ULONG64)&pBuff[0x12C], 1);
	W_DW((ULONG64)&pBuff[0x134], 传送ID);
	W_DW((ULONG64)&pBuff[0x13C], 0x300);
	MainUniversalCALL2(局_RCX, (ULONG_PTR)pBuff, 局_dCALL);
}
void 地图::遍历已激活传送点(vector<传送点信息_>& vsk)
{
	传送点信息_ temp传送点;
	vsk.clear();
	DWORD dtotal = R_W(游戏模块 + gb_CurTeleportList);
	INT64 dstart = 游戏模块 + gb_CurTeleportList + 2;
	for (DWORD i = 0; i < dtotal; i++)
	{
		DWORD  dTeleportId = R_DW(dstart + i * 4);
		INT64 dTeleportResAddr = getSquareResAddrById(dTeleportId);
		INT64 dTeleportNameAddr = R_QW(dTeleportResAddr + 0x10);
		DWORD Mapid = R_DW(dTeleportResAddr + go_PortalMapId);
		CString cTeleportName = L"空";
		string temp = UnicodeToAnsi(R_CString(dTeleportNameAddr));
		cTeleportName = CString(temp.c_str());
		temp传送点.cTeleportName = cTeleportName;
		temp传送点.dTeleportId = dTeleportId;
		temp传送点.Mapid = Mapid;
		vsk.push_back(temp传送点);
		/*wchar_t buf[100];
		swprintf(buf, L"己激活传送点 %s %X\r\n", cTeleportName, dTeleportId);*/

	}
}
bool 地图::传送点是否激活(DWORD 传送点ID)
{
	vector<传送点信息_>vsk;
	地图::遍历已激活传送点(vsk);
	for (size_t i = 0; i < vsk.size(); i++)
	{
		if (传送点ID == vsk[i].dTeleportId)
		{
			return true;
		}
	}
	return false;
}
bool 传送点mark(const 传送点信息_& o1, const 传送点信息_& o2)
{
	return o1.Mapid > o2.Mapid;

}
void 地图::取目标地图传送点(DWORD 地图ID, vector<传送点信息_>& vsk)
{
	vector<传送点信息_>已激活传送点;
	地图::遍历已激活传送点(已激活传送点);
	for (size_t i = 0; i < 已激活传送点.size(); i++)
	{
		if (已激活传送点[i].Mapid == 地图ID)
		{
			vsk.push_back(已激活传送点[i]);
		}
	}

	if (vsk.size() == 0)
	{
		if (地图ID == 10801)
		{
			for (size_t i = 0; i < 已激活传送点.size(); i++)
			{
				if (已激活传送点[i].dTeleportId == 900209)
				{
					vsk.push_back(已激活传送点[i]);
					break;
				}
			}
			if (vsk.size() == 0)
			{
				for (size_t i = 0; i < 已激活传送点.size(); i++)
				{
					if (已激活传送点[i].Mapid == 10815)
					{
						vsk.push_back(已激活传送点[i]);
					}
				}
			}
			::sort(vsk.begin(), vsk.end(), 传送点mark);
		}
		if (地图ID == 10816)
		{
			for (size_t i = 0; i < 已激活传送点.size(); i++)
			{
				if (已激活传送点[i].Mapid == 10801)
				{
					vsk.push_back(已激活传送点[i]);
				}
			}
			::sort(vsk.begin(), vsk.end(), 传送点mark);
		}
		if (地图ID == 10818)
		{
			for (size_t i = 0; i < 已激活传送点.size(); i++)
			{
				if (已激活传送点[i].Mapid == 10817)
				{
					vsk.push_back(已激活传送点[i]);
				}
			}
			::sort(vsk.begin(), vsk.end(), 传送点mark);
		}
		if (地图ID == 10804)
		{
			for (size_t i = 0; i < 已激活传送点.size(); i++)
			{
				if (已激活传送点[i].dTeleportId == 900461)
				{
					vsk.push_back(已激活传送点[i]);
				}
			}
			::sort(vsk.begin(), vsk.end(), 传送点mark);
		}
		if (地图ID == 10725)
		{
			for (size_t i = 0; i < 已激活传送点.size(); i++)
			{
				if (已激活传送点[i].dTeleportId == 0xDBE86)
				{
					vsk.push_back(已激活传送点[i]);
					break;
				}
			}
			if (vsk.size() == 0)
			{
				for (size_t i = 0; i < 已激活传送点.size(); i++)
				{
					if (已激活传送点[i].Mapid == 10723)
					{
						vsk.push_back(已激活传送点[i]);
					}
				}
			}
			::sort(vsk.begin(), vsk.end(), 传送点mark);
		}
		if (地图ID == 10423)
		{
			for (size_t i = 0; i < 已激活传送点.size(); i++)
			{
				if (已激活传送点[i].dTeleportId == 900901)
				{
					vsk.push_back(已激活传送点[i]);
					break;
				}
			}
			if (vsk.size() == 0)
			{
				for (size_t i = 0; i < 已激活传送点.size(); i++)
				{
					if (已激活传送点[i].Mapid == 10401)
					{
						vsk.push_back(已激活传送点[i]);
					}
				}
			}
			::sort(vsk.begin(), vsk.end(), 传送点mark);
		}
		if (地图ID == 10423)
		{
			for (size_t i = 0; i < 已激活传送点.size(); i++)
			{
				if (已激活传送点[i].dTeleportId == 900922)
				{
					vsk.push_back(已激活传送点[i]);
					break;
				}
			}
			if (vsk.size() == 0)
			{
				for (size_t i = 0; i < 已激活传送点.size(); i++)
				{
					if (已激活传送点[i].Mapid == 10422)
					{
						vsk.push_back(已激活传送点[i]);
					}
				}
			}
			::sort(vsk.begin(), vsk.end(), 传送点mark);
		}
		if (地图ID == 10424)
		{
			for (size_t i = 0; i < 已激活传送点.size(); i++)
			{
				if (已激活传送点[i].dTeleportId == 0xDBF26)
				{
					vsk.push_back(已激活传送点[i]);
					break;
				}
			}
			if (vsk.size() == 0)
			{
				for (size_t i = 0; i < 已激活传送点.size(); i++)
				{
					if (已激活传送点[i].Mapid == 10401)
					{
						vsk.push_back(已激活传送点[i]);
					}
				}
			}
			::sort(vsk.begin(), vsk.end(), 传送点mark);
		}
		if (地图ID == 10426)
		{
			for (size_t i = 0; i < 已激活传送点.size(); i++)
			{
				if (已激活传送点[i].dTeleportId == 0xDBF27)
				{
					vsk.push_back(已激活传送点[i]);
					break;
				}
			}
			if (vsk.size() == 0)
			{
				for (size_t i = 0; i < 已激活传送点.size(); i++)
				{
					if (已激活传送点[i].Mapid == 10401)
					{
						vsk.push_back(已激活传送点[i]);
					}
				}
			}
			::sort(vsk.begin(), vsk.end(), 传送点mark);
		}
		if (地图ID == 11102)
		{
			for (size_t i = 0; i < 已激活传送点.size(); i++)
			{
				if (已激活传送点[i].dTeleportId == 0xDBF9E)
				{
					vsk.push_back(已激活传送点[i]);
					break;
				}
			}
			if (vsk.size() == 0)
			{
				for (size_t i = 0; i < 已激活传送点.size(); i++)
				{
					if (已激活传送点[i].Mapid == 11111)
					{
						vsk.push_back(已激活传送点[i]);
					}
				}
			}
			::sort(vsk.begin(), vsk.end(), 传送点mark);
		}
		if (地图ID == 11101)
		{
			for (size_t i = 0; i < 已激活传送点.size(); i++)
			{
				if (已激活传送点[i].dTeleportId == 0xDBF9E)
				{
					vsk.push_back(已激活传送点[i]);
					break;
				}
			}
			if (vsk.size() == 0)
			{
				for (size_t i = 0; i < 已激活传送点.size(); i++)
				{
					if (已激活传送点[i].Mapid == 11111)
					{
						vsk.push_back(已激活传送点[i]);
					}
				}
			}
			::sort(vsk.begin(), vsk.end(), 传送点mark);
		}
		if (地图ID == 11113)
		{

			for (size_t i = 0; i < 已激活传送点.size(); i++)
			{
				if (已激活传送点[i].Mapid == 11101)
				{
					vsk.push_back(已激活传送点[i]);
				}
			}

			::sort(vsk.begin(), vsk.end(), 传送点mark);
		}
		if (地图ID == 11115)
		{

			for (size_t i = 0; i < 已激活传送点.size(); i++)
			{
				if (已激活传送点[i].Mapid == 11101)
				{
					vsk.push_back(已激活传送点[i]);
				}
			}

			::sort(vsk.begin(), vsk.end(), 传送点mark);
		}
	}
}
DWORD 地图::获取港口传送点ID()
{
	INT64 局_rcx = R_QW(游戏模块 + gb_ResBase);
	INT64 局_call = 游戏模块 + 基址_地图_获取港口传送点ID;
	if (局_rcx == 0)
	{
		return 0;
	}
	INT64 局_v1 = MainUniversalCALL2_Ret(局_rcx, 0, 局_call);
	return R_DW(局_v1 + 0xAC);
}

INT64 地图::取场景对象()
{
	INT64 局_rcx = R_QW(游戏模块 + 基址_地图_环境);
	INT64 局_rdx = 局_rcx;
	if (R_DW(局_rcx + 16) == 0)
	{
		return 0;
	}
	DWORD 局_eax = R_DW(局_rcx + 16);
	局_eax = 局_eax - 1;
	局_rcx = 局_eax * 5;
	INT64 局_rax = R_QW(局_rdx + 8);
	if (R_DW(局_rax + 局_rcx * 4 + 12) == 0)
	{
		return 0;
	}
	局_rax = R_QW(局_rax + 局_rcx * 4 + 4);
	局_rax = R_QW(局_rax);
	return 局_rax;

}

CString 地图::取大地图名()
{
	INT64 局_大地图rcx = R_QW(游戏模块 + gb_ResBase);
	INT64 局_大地图call = 游戏模块 + 基址_地图_获取大地图名;
	DWORD 局_地图ID = 地图::取地图ID();
	//INT64 局_结果 = (INT64)申请内存2((HANDLE)-1, 100);
	UCHAR 局_结果[100] = { 0 };
	MainUniversalCALL4(局_大地图rcx, INT64(&局_结果), 局_地图ID, 0, 局_大地图call);
	CString 返回名称 = R_CString(R_QW(R_QW((INT64)&局_结果) + 0x68));
	//CString 返回名称 = CString(temp.c_str());
	//释放内存2((HANDLE)-1, LPVOID(局_结果), 100);
	return 返回名称;
}
CString 地图::取指定地图名(DWORD 局_地图ID)
{
	INT64 局_大地图rcx = R_QW(游戏模块 + gb_ResBase);
	INT64 局_大地图call = 游戏模块 + 基址_地图_获取大地图名;
	//INT64 局_结果 = (INT64)申请内存2((HANDLE)-1, 100);
	UCHAR 局_结果[100] = { 0 };
	MainUniversalCALL4(局_大地图rcx, (INT64)&局_结果, 局_地图ID, 0, 局_大地图call);
	CString 返回名称 = R_CString(R_QW(R_QW((INT64)&局_结果) + 0x68));
	//释放内存2((HANDLE)-1, LPVOID(局_结果), 100);
	return 返回名称;
}

CString 地图::取小地图名()
{
	INT64 局_rcx = R_QW(游戏模块 + 基址_地图_环境);
	INT64 局_call = 游戏模块 + 基址_地图_获取环境名字call;
	INT64 局_场景对象 = 地图::取场景对象();
	UCHAR 局_结果[100] = { 0 };
	//INT64 局_结果 = (INT64)申请内存2((HANDLE)-1, 100);
	MainUniversalCALL4(局_rcx, (INT64)&局_结果, 局_场景对象, 0, 局_call);
	CString 返回名称 = R_CString(R_QW((INT64)&局_结果));
	//CString 返回名称 = CString(temp.c_str());
	//释放内存2((HANDLE)-1, LPVOID(局_结果), 100);
	return 返回名称;
}

void 地图::寻路(float x, float y, float z, DWORD modid = 0)
{
	INT64 局_真实对象 = 本人::取真实对象();
	INT64 局_RCX = 局_真实对象 + 偏移_地图_寻路rcx;
	坐标_ 局_当前坐标 = 本人::取坐标();
	INT64 局_dCALL = 游戏模块 + 基址_地图_寻路call;
	UCHAR pBuff[0x140] = { 0 };

	W_QW((ULONG64)&pBuff[0x0], 4294984384);
	W_Float((ULONG64)&pBuff[0x30], 局_当前坐标.x);
	W_Float((ULONG64)&pBuff[0x30 + 4], 局_当前坐标.y);
	W_Float((ULONG64)&pBuff[0x30 + 8], 局_当前坐标.z);
	W_Float((ULONG64)&pBuff[0x3c], x);
	W_Float((ULONG64)&pBuff[0x3c + 4], y);
	W_Float((ULONG64)&pBuff[0x3c + 8], z);
	W_DW((ULONG64)&pBuff[0x88], modid);
	MainUniversalCALL4(局_RCX, (ULONG_PTR)pBuff, 0, 0, 局_dCALL);
}

bool 地图::本地图寻路(float x, float y, float z, DWORD modid = 0)
{
	/*if (GetDis(x, y, z) <= 100)
	{
		return true;
	}*/
	bool 是否寻路 = 本人::是否在走路();
	if (是否寻路 == false)
	{
		地图::寻路(x, y, z, modid);
		return true;
	}
	MyTrace(L"寻路中");
	return false;
}

bool 地图::指定地点是否可到达(float x, float y, float z)
{
	DWORD reta = 0;
	INT64 dCALL = 游戏模块 + 基址_地图_目的地址是否可达Call;
	INT64 局_rsi = 本人::取真实对象();
	INT64 局_坐标基址 = 本人::取坐标基址();
	UCHAR pBuff[0x100] = { 0 };
	W_Float((ULONG64)&pBuff[0], x);
	W_Float((ULONG64)&pBuff[4], y);
	W_Float((ULONG64)&pBuff[8], z);
	INT64 局_R9 = (INT64)&pBuff;
	__try {
		__asm
		{
			mov rsi, 局_rsi
			mov rax, qword ptr ds : [rsi]
			mov rcx, rsi
			sub rsp, 0x28
			call qword ptr ds : [rax + 基址_地图_目的地址是否可达_rax获取偏移]
			add rsp, 0x28
			mov r14, rax
			sub rsp, 0x60
			mov r9, 局_R9
			mov rcx, r14
			mov rdx, 局_坐标基址
			mov r8, 0
			mov dword ptr ss : [rsp + 0x20] , 0
			mov dword ptr ss : [rsp + 0x28] , 0
			mov dword ptr ss : [rsp + 0x30] , 1
			mov rdi, dCALL
			call rdi
			add rsp, 0x60
			mov reta, eax

		}
	}
	__except (1)
	{
		DbgPrintf_Mine("指定地点是否可到达 异常");
		return false;
	}
	MyTrace(L"reta %d", reta);
	if (reta == 1)
	{
		return true;
	}
	return false;
}
bool 地图::指定地点是否可到达_M(float x, float y, float z)
{

	坐标_ CALLArg;
	CALLArg.x = x;
	CALLArg.y = y;
	CALLArg.z = z;
	SendMessageTimeoutA(g_hWnd, 注册消息值, Msgid::CALLCanArrive, (LPARAM)&CALLArg, SMTO_NORMAL, 2000, 0);
	//MyTrace(L"返回值 %d", CALLArg.是否可达);
	return (CALLArg.是否可达);
}
