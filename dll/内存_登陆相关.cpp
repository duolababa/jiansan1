#include "内存_登陆相关.h"

int 登陆::服务器遍历(vector<CString>& vsk)
{
	vsk.clear();
	INT64 局_rcx = R_QW(游戏模块 + 基址_登录_选择服务器rcx);
	if (局_rcx == 0)
	{
		return 0;
	}
	INT64 局_数组头 = R_QW(局_rcx + 156);
	DWORD 局_成员数 = R_DW(局_rcx + 164);
	for (size_t i = 0; i < 局_成员数; i++)
	{
		if (i > 500)
		{
			break;
		}
		INT64 局_服务器对象 = 局_数组头 + i * 51;
		string temp = UnicodeToAnsi(R_CString(局_服务器对象 + 0));
		CString 局_服务器名称 = CString(temp.c_str());
		if (局_服务器名称 != L"")
		{
			vsk.push_back(局_服务器名称);
		}

	}
	return 局_成员数;
}

int 登陆::查询服务器序号(CString 服务器名称)
{
	vector<CString>vsk;
	登陆::服务器遍历(vsk);
	for (size_t i = 0; i < vsk.size(); i++)
	{

		if (vsk[i] == 服务器名称)
		{
			return i;
		}
	}
	return -1;
}
bool 登陆::是否在服务器界面()
{
	INT64 局_rcx = R_QW(游戏模块 + 基址_登录_选择服务器rcx);
	int 局_成员数 = R_DW(局_rcx + 164);
	if (局_成员数 > 0)
	{
		return true;
	}
	return false;
}
bool 登陆::CALL_选择服务器(CString 服务器名称)
{
	int 局_服务器序号 = 登陆::查询服务器序号(服务器名称);
	if (局_服务器序号 == -1)
	{
		return false;
	}
	INT64 局_rcx = R_QW(游戏模块 + 基址_登录_选择服务器rcx);
	INT64 局_Call = 游戏模块 + 基址_登录_选择服务器call;
	MainUniversalCALL2(局_rcx, 局_服务器序号, 局_Call);
	return true;
}

bool 登陆::是否出现确认协议()
{
	INT64 局_UI对象 = UI功能::getUiObjById(4);
	if (局_UI对象 == 0)
	{
		return false;
	}
	if (R_DW(局_UI对象 + 184) == 1)
	{
		return true;
	}
	return false;
}
bool 登陆::CALL_确认协议()
{
	INT64 局_UI对象 = UI功能::getUiObjById(4);
	if (局_UI对象 == 0)
	{
		return false;
	}
	INT64 局_call = 游戏模块 + 基址_登录_确认协议call;
	MainUniversalCALL2(局_UI对象, 0, 局_call);
	return true;
}
bool 登陆::CALL_选择职业(CString 职业名)
{
	int 局_职业ID = 0;
	if (职业名 == L"战士")
	{
		局_职业ID = 101;
	}
	else if (职业名 == L"魔法师")
	{
		局_职业ID = 201;
	}
	else if (职业名 == L"格斗家(女)")
	{
		局_职业ID = 301;
	}
	else if (职业名 == L"格斗家(男)")
	{
		局_职业ID = 311;
	}
	else if (职业名 == L"猎人(女)")
	{
		局_职业ID = 501;
	}
	else if (职业名 == L"猎人(男)")
	{
		局_职业ID = 511;
	}
	else if (职业名 == L"猎人")
	{
		局_职业ID = 401;
	}
	else
	{
		return false;
	}
	INT64 局_rcx = 游戏模块 + 基址_登录_选择职业rcx;
	if (局_rcx == 0)
	{
		return false;
	}
	INT64 局_call = 游戏模块 + 基址_登录_选择职业call;
	INT64 崩溃地址 = 局_call + 106;
	W_Word(局_rcx + 0x9C, 局_职业ID);
	MainUniversalCALL2(局_rcx, 0, 局_call);
	return true;
}
bool 登陆::是否在准备界面()
{
	INT64 局_UI对象 = UI功能::getUiObjById(9);
	if (局_UI对象 == 0)
	{
		return false;
	}

	return true;
}
bool 登陆::是否在创建角色界面()
{
	INT64 局_UI对象 = UI功能::getUiObjById(19);
	if (局_UI对象 == 0)
	{
		return false;
	}
	return true;
}

bool 登陆::是否在选择职业界面()
{
	INT64 局_UI对象 = R_QW(游戏模块 + 基址_登录_选择职业rcx);
	if (局_UI对象 == 0)
	{
		return false;
	}
	if (R_BYTE(局_UI对象 + 92) == 0)
	{
		return false;
	}
	return true;
}
wchar_t* 尾[12] = { L"jan",L"feb",L"mar",L"apr",L"may",L"jun",L"jul",L"aug",L"sept",L"oct",L"nov",L"dec" };
wchar_t* 尾2[7] = { L"mon",L"tues",L"wed",L"thur",L"fri",L"sat",L"sun" };
wchar_t* 尾3[4] = { L"spr",L"sum",L"aut",L"win" };
wchar_t* 尾4[4] = { L"east",L"west",L"nort",L"sort" };
bool 登陆::CALL_创建角色(int  创建次数)
{
	bool mode = true;
	INT64 局_call = 游戏模块 + 基址_登录_创建角色;
	if (!创建次数)
	{
		创建次数 = 3;
	}
	INT64 cStringClassPtr = 0;
	for (size_t i = 0; i < 创建次数; i++)
	{
		srand(time(NULL));
		CString 名称;
		//CString 首字 = 随机生成英文名字(1);
		switch ((rand() % 4))
		{
		case 1:
			名称 = randstr(Random(6, 12)) + 尾[Random(0, 11)];
			break;
		case 2:
			名称 = randstr(Random(6, 12)) + 尾2[Random(0, 6)];
			break;
		case 3:
			名称 = randstr(Random(6, 12)) + 尾3[Random(0, 3)];
			break;
		default:
			名称 = randstr(Random(6, 12)) + 尾4[Random(0, 3)];
			break;
		}

		MyTrace(L"生成名称 %s", 名称);
		if (mode)
		{
			cStringClassPtr = (DWORD64)申请内存2((HANDLE)-1, 0x100);
			W_QW(cStringClassPtr, UINT64(名称.GetBuffer()));
			W_QW(cStringClassPtr + 8, 名称.GetLength() + 1);
			MainUniversalCALL4(0x3ED, 0x5A, cStringClassPtr, 0, 局_call);
		}
		else
		{
			temp名称指针 cStringClassPtr2;
			cStringClassPtr2.名称obj = INT64(名称.GetBuffer());
			cStringClassPtr2.长度 = 名称.GetLength() + 1;
			MainUniversalCALL4(0x3ED, 0x5A, (UINT64)&cStringClassPtr2, 0, 局_call);
		}
		Sleep(1000);
		UI功能::内存按键(VK_RETURN);
		Sleep(2000);
		if (mode)
		{
			释放内存2((HANDLE)-1, LPVOID(cStringClassPtr), 0x100);
		}
		return true;

	}
	/*if (mode)
	{
		释放内存2((HANDLE)-1, LPVOID(cStringClassPtr), 0x100);
	}*/
	return false;
}
bool 登陆::CALL_打开创建角色(int 序号)
{
	INT64 局_call = 游戏模块 + 基址_登录_打开创建角色call;
	INT64 局_rcx = UI功能::getUiObjById(12);
	if (局_rcx == 0)
	{
		return false;
	}
	MainUniversalCALL2(局_rcx, 序号, 局_call);
	return true;
}
int 登陆::CALL_角色遍历(vector<登陆角色信息_>& vsk)
{
	vsk.clear();
	登陆角色信息_ temp;
	INT64 局_call = 游戏模块 + 基址_登录_创建角色;
	INT64 局_R9 = (DWORD64)申请内存2((HANDLE)-1, 0x100);
	MainUniversalCALL4(0x3EB, 0x19, 0, 局_R9, 局_call);
	INT64 局_数组头 = R_QW(局_R9);
	DWORD 数量 = R_DW(局_R9 + 8);
	for (size_t i = 0; i < 数量; i++)
	{
		temp.对象指针 = R_QW(局_数组头 + i * 8);
		if (temp.对象指针 != 0)
		{
			temp.dIndex = i;
			string stemp = UnicodeToAnsi(R_CString(temp.对象指针 + 416));
			temp.名称 = CString(stemp.c_str());
			temp.等级 = R_DW(temp.对象指针 + 0x278);
			vsk.push_back(temp);
		}
	}
	return 数量;
}
void 登陆::get_CharacterList(vector<登陆角色信息_>& vsk)
{
	vsk.clear();
	登陆角色信息_ temp;
	INT64 addr_1 = R_QW(游戏模块 + gb_CharacterList);
	DWORD dtotal = R_DW(addr_1 + go_CharacterListStart + 8);
	INT64 objStartAddr = R_QW(addr_1 + go_CharacterListStart);
	DWORD dSize = go_CharacterListSize;
	for (DWORD i = 0; i < dtotal; i++)
	{
		INT64  dCharacterInfo = objStartAddr + i * dSize;
		INT64 dNameAddr = dCharacterInfo + go_CharacterName;
		INT64 dSrvId = R_QW(dCharacterInfo + go_CharacterSrvId);
		DWORD dIndex = R_W(dCharacterInfo + go_CharacterIndex);
		DWORD dJobId = R_W(dCharacterInfo + go_CharacterJob);
		DWORD dLev = R_W(dCharacterInfo + go_CharacterLev);
		CString cName = L"";
		if (dNameAddr)
		{
			cName = R_CString(dNameAddr);
			/*wchar_t buf[100];
			swprintf(buf, L"地址0x%I64X %s id %I64X 职业ID %X 等级%d\r\n", dCharacterInfo, cName, dSrvId, dJobId, dLev);
			MyTrace(buf);*/
		}
		temp.dIndex = dIndex;
		temp.dJob = dJobId;
		temp.等级 = dLev;
		temp.名称 = cName;
		temp.对象指针 = dCharacterInfo;
		temp.SrvId = dSrvId;
		vsk.push_back(temp);
	}

}
登陆角色信息_ 登陆::getCharacterInfoByIndex(int 序号)
{
	登陆角色信息_ temp;
	vector<登陆角色信息_>vsk;
	登陆::get_CharacterList(vsk);
	for (size_t i = 0; i < vsk.size(); i++)
	{
		if (vsk[i].dIndex == 序号)
		{
			return vsk[i];
		}
	}
	return temp;
}
bool 登陆::CALL_进入游戏(int 角色序号)
{
	INT64 局_rcx = R_QW(游戏模块 + 基址_登录_进入游戏rcx);
	if (局_rcx == 0)
	{
		return false;
	}
	MainUniversalCALL2(局_rcx, 角色序号, 游戏模块 + 基址_登录_进入游戏call);
	return true;
}