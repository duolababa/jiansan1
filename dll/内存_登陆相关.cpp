#include "内存_登陆相关.h"
#include <random>
int 登陆::服务器遍历(vector<CString>& vsk)
{
	vsk.clear();
	INT64 局_rcx = R_QW(游戏模块 + 基址_登录_选择服务器rcx);
	if (局_rcx == 0)
	{
		return 0;//[[0x50B7888+lostark.0]+9c]+0*33+3
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
		string temp = UnicodeToAnsi(R_CString(局_服务器对象 +3));
		CString 局_服务器名称 = CString(temp.c_str());
		if (局_服务器名称 != L"")
		{
			MyTrace(L"%s", 局_服务器名称);
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
	else if (职业名 == L"武女")
	{
		局_职业ID = 301;
	}
	else if (职业名 == L"武男")
	{
		局_职业ID = 311;
	}
	else if (职业名 == L"男枪")
	{
		局_职业ID = 501;
	}
	else if (职业名 == L"女枪")
	{
		局_职业ID = 511;
	}
	else if (职业名 == L"刺客")
	{
		局_职业ID = 401;
	}
	else if (职业名 == L"专家")
	{
		局_职业ID = 601;
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

std::string generateRandomString(int minLength, int maxLength) {
	// 随机数引擎和分布
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<int> dist(0, 25); // 生成 0 到 25 之间的整数

	// 生成字符串长度
	std::random_device rdLength;
	std::mt19937 genLength(rdLength());
	std::uniform_int_distribution<int> distLength(minLength, maxLength);
	int length = distLength(genLength);

	// 生成第一个字母（大写字母）
	char firstLetter = 'A' + dist(gen);

	// 生成剩余字母
	std::string randomString;
	randomString += firstLetter;

	for (int i = 1; i < length; i++) {
		char letter = 'a' + dist(gen);
		randomString += letter;
	}

	return randomString;
}


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

		CString 名称;
		名称 = CStringA(generateRandomString(12, 15).c_str());

			temp名称指针 cStringClassPtr2;
			cStringClassPtr2.名称obj = INT64(名称.GetBuffer());
			cStringClassPtr2.长度 = 名称.GetLength() + 1;
			MainUniversalCALL4(0x3ED, 0x5D, (UINT64)&cStringClassPtr2, 0, 局_call);
		//}45 33 C9 4C 8D 44 24 ?? 8D 57 ?? B9 ?? ?? ?? ??      RCX  +B     RDX  B
		Sleep(1000);

		UI功能::内存按键1(g_ENTER);
		Sleep(2000);
		return true;

	}

	return false;
}

bool 登陆::登录点击角色(int 序号)
{
	INT64 局_call = 游戏模块 + 切换角色call;
	INT64 局_UI对象 = R_QW(游戏模块 + 基址_登录_进入游戏rcx);
	if (局_UI对象 == 0)
	{
		return false;
	}
	MainUniversalCALL4(局_UI对象, 序号, 1, 0, 局_call);
	return true;
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
//int 登陆::CALL_角色遍历(vector<登陆角色信息_>& vsk)
//{
//	vsk.clear();
//	登陆角色信息_ temp;
//	INT64 局_call = 游戏模块 + 基址_登录_创建角色;
//	INT64 局_R9 = (DWORD64)申请内存2((HANDLE)-1, 0x100);
//	MainUniversalCALL4(0x3EB, 0x19, 0, 局_R9, 局_call);
//	INT64 局_数组头 = R_QW(局_R9);
//	DWORD 数量 = R_DW(局_R9 + 8);
//	for (size_t i = 0; i < 数量; i++)
//	{
//		temp.对象指针 = R_QW(局_数组头 + i * 8);
//		if (temp.对象指针 != 0)
//		{
//			temp.dIndex = i;
//			string stemp = UnicodeToAnsi(R_CString(temp.对象指针 + 416));
//			temp.名称 = CString(stemp.c_str());
//			temp.等级 = R_DW(temp.对象指针 + 0x278);
//			vsk.push_back(temp);
//		}
//	}
//	return 数量;
//}
DWORD getCharacterGetJumpState(__int64 dCharacterInfo)
{
	if (!dCharacterInfo) return 0;
	INT64 ret = MainUniversalCALL2_Ret(dCharacterInfo, 0, 游戏模块 + gc_CharacterGetJumpState);
	/*wchar_t buf[100];
	dm.AsmClear();
	dm.AsmAdd(L"sub rsp,040");
	wsprintf(buf, L"MOV RCX, 0%I64X", dCharacterInfo);
	dm.AsmAdd(buf);
	wsprintf(buf, L"MOV RDI, 0%I64X", gc_CharacterGetJumpState);
	dm.AsmAdd(buf);
	dm.AsmAdd(L"call rdi");
	dm.AsmAdd(L"add rsp,040");*/
	return (DWORD)ret;
}
void 登陆::get_CharacterList(vector<登陆角色信息_>& vsk)
{
	vsk.clear();
	角色信息 ="";
	CString 临时职业=L" ";
	CString 临时装等=L" ";
	登陆角色信息_ temp;
	INT64 addr_1 = R_QW(游戏模块 + gb_CharacterList);
	DWORD dtotal = R_DW(addr_1 + go_CharacterListStart + 8);
	INT64 objStartAddr = R_QW(addr_1 + go_CharacterListStart);
	DWORD dSize = go_CharacterListSize;
	for (DWORD i = 0; i < dtotal; i++)
	{//[[0x50B52C8+LOSTARK.0]+A4]+0*0x1AE4
		INT64  dCharacterInfo = objStartAddr + i * dSize;
		DWORD dJumpState = getCharacterGetJumpState(dCharacterInfo);//为1直升中 为3 可直升
		INT64 dNameAddr = dCharacterInfo + go_CharacterName;
		INT64 dSrvId = R_QW(dCharacterInfo + go_CharacterSrvId);
		DWORD dIndex = R_W(dCharacterInfo + go_CharacterIndex);
		DWORD dJobId = R_W(dCharacterInfo + go_CharacterJob);
		DWORD dLev = R_W(dCharacterInfo + go_CharacterLev);
		float 装等=R_Float(dCharacterInfo + go_Character装等评分);

		CString cName = L"";
		if (dNameAddr)
		{
			cName = R_CString(dNameAddr);
			wchar_t buf[100];
			swprintf(buf, L"地址0x%I64X %s id %I64X 职业ID %X 等级%d 装等 %0.3f\r\n", dCharacterInfo, cName, dSrvId, dJobId, dLev, 装等);
			MyTrace(buf);
		}
		temp.dIndex = dIndex;
		temp.dJob = dJobId;
		temp.等级 = dLev;
		temp.装等 = 装等;

		temp.直升状态 = dJumpState;
		temp.名称 = cName;
		temp.对象指针 = dCharacterInfo;
		temp.SrvId = dSrvId;
		临时职业 = 临时职业 + ConvertDWORDToString(dJobId)+L"|";
		临时装等 = 临时装等 + ConvertDWORDToString((int)temp.装等) + L"|";

		//temp.Format(L"%f", 角色信息.坐标.z);//3
		//arr.push_back(temp);
		
		//	发送给控制台1(ConvertDWORDToString(GameIndex), "登录", "初始化成功");
		vsk.push_back(temp);
	}
	角色信息 = 临时装等+ 临时职业;
	发送给控制台1(ConvertDWORDToString(GameIndex), L"装等职业", 角色信息);
}
//登陆角色信息_ 登陆::getCharacterInfoByIndex(int 序号)
//{
//	登陆角色信息_ temp;
//	vector<登陆角色信息_>vsk;
//	登陆::get_CharacterList(vsk);
//	for (size_t i = 0; i < vsk.size(); i++)
//	{
//		if (vsk[i].dIndex == 序号)
//		{
//			return vsk[i];
//		}
//	}
//	return temp;
//}
bool 登陆::CALL_进入游戏(int 角色序号)
{
	INT64 局_rcx = R_QW(游戏模块 + 基址_登录_进入游戏rcx);
	if (局_rcx == 0)
	{
		return false;
	}
	当前执行角色 = 角色序号;
	MainUniversalCALL2(局_rcx, 角色序号, 游戏模块 + 基址_登录_进入游戏call);
	//Sleep(5000);
	//INT64 addr = 0;
	//CString	name = L" ";
	// addr = 环境::鼠标获取对象call(11300,13540);
	////MyTrace(L"执行第1个call");
	//if (addr > 1)
	//{
	//
	//	name = UI功能::UI名称1(addr);
	//	if (name.GetLength() != 0 && name.Find(L"start") != -1)
	//	{
	//		UI功能::控件点击call(addr);
	//		Sleep(3000);
	//	}

	//}

	//addr = 0;
	//name = L" ";
	//addr = 环境::鼠标获取对象call(10740,3340);
	////MyTrace(L"执行第1个call");
	//if (addr > 1)
	//{
	//
	//	name = UI功能::UI名称1(addr);
	//	if (name.GetLength() != 0 && name.Find(L"tab_0") != -1)
	//	{
	//		UI功能::控件点击call(addr);
	//		Sleep(3000);
	//	}

	//}

	//addr = 0;
	//name = L" ";
	//addr = 环境::鼠标获取对象call(12760,13520);
	////MyTrace(L"执行第1个call");
	//if (addr > 1)
	//{

	//	name = UI功能::UI名称1(addr);
	//	if (name.GetLength() != 0 && name.Find(L"start_btn") != -1)
	//	{
	//		UI功能::控件点击call(addr);
	//		Sleep(3000);
	//	}

	//}

	//addr = 0;
	//name = L" ";
	//addr = 环境::鼠标获取对象call(12820,13620);
	////MyTrace(L"执行第1个call");
	//if (addr > 1)
	//{

	//	name = UI功能::UI名称1(addr);
	//	if (name.GetLength() != 0 && name.Find(L"gameStartBtn") != -1)
	//	{
	//		UI功能::控件点击call(addr);
	//		Sleep(3000);
	//	}

	//}





	return true;
}
int 登陆::getJumpMapCheck(int dIndex)//索引从1开始
{
	__int64 addr_1 = R_QW(游戏模块 + gb_AccountSpecInfo);
	BYTE dCurSeverIndex = R_BYTE(游戏模块 + gb_CurSeverIndex);//读字节
	INT64 ret = MainUniversalCALL4_Ret(addr_1, 3, dIndex, dCurSeverIndex, 游戏模块 + gc_AccountSpecCheck);
	/*wchar_t buf[100];
	dm.AsmClear();
	dm.AsmAdd(L"sub rsp,040");
	wsprintf(buf, L"MOV R9D, 0%X", dCurSeverIndex);
	dm.AsmAdd(buf);
	wsprintf(buf, L"MOV R8D, 0%X", dIndex);
	dm.AsmAdd(buf);
	wsprintf(buf, L"MOV EDX, 0%X", 3);
	dm.AsmAdd(buf);
	wsprintf(buf, L"MOV RCX, 0%I64X", addr_1);
	dm.AsmAdd(buf);
	wsprintf(buf, L"MOV RDI, 0%I64X", gc_AccountSpecCheck);
	dm.AsmAdd(buf);
	dm.AsmAdd(L"call rdi");
	dm.AsmAdd(L"add rsp,040");*/
	return (DWORD)ret;
}
DWORD 登陆::getJmpMapList()//获取直升阶段地图信息
{
	for (int i = 0; i < 6; i++)
	{
		if (getJumpMapCheck(i + 1))
		{
			return i + 1;
		MyTrace(L"直升地图%d 有券", i + 1);
		}
	
	}
	return 0;
}
void 登陆::Fun_UseJumpByIndex(__int64 dCharacterSrvId, int dIndex)//索引从1开始  使用直升
{
	__int64 addr_1 = R_QW(游戏模块 + gb_CharacterList);
	BYTE dCurSeverIndex = R_BYTE(游戏模块 + gb_CurSeverIndex);//读字节
	MainUniversalCALL4_Ret(addr_1, dCharacterSrvId, 3, dIndex, 游戏模块 + gc_UesJumpByIndex);
	//wchar_t buf[100];
	//dm.AsmClear();
	//dm.AsmAdd(L"sub rsp,040");
	//wsprintf(buf, L"MOV R9D, 0%X", dIndex);
	//dm.AsmAdd(buf);
	//wsprintf(buf, L"MOV R8D, 0%X", 3);
	//dm.AsmAdd(buf);
	//wsprintf(buf, L"MOV RDX, 0%I64X", dCharacterSrvId);
	//dm.AsmAdd(buf);
	//wsprintf(buf, L"MOV RCX, 0%I64X", addr_1);
	//dm.AsmAdd(buf);
	//wsprintf(buf, L"MOV RDI, 0%I64X", gc_UesJumpByIndex);
	//dm.AsmAdd(buf);
	//dm.AsmAdd(L"call rdi");
	//dm.AsmAdd(L"add rsp,040");
	//return (DWORD)dm.AsmCall(HwndGlobal, 6);
}
登陆角色信息_ 登陆::getCharacterInfoByName(CString Name)
{
	登陆角色信息_ temp;
	vector<登陆角色信息_>vsk;
	登陆::get_CharacterList(vsk);
	for (size_t i = 0; i < vsk.size(); i++)
	{
		if (vsk[i].名称 == Name)
		{
			return vsk[i];
		}
	}
	return temp;
}




登陆角色信息_ 登陆::getCharacterInfoByIndex(int 序号)
{
	登陆角色信息_ temp;
	for (size_t i = 0; i < 全_角色列表.size(); i++)
	{
		if (全_角色列表[i].dIndex == 序号)
		{
			return 全_角色列表[i];
		}
	}
	/*登陆角色信息_ temp;
	vector<登陆角色信息_>vsk;
	登陆::get_CharacterList(vsk);
	for (size_t i = 0; i < vsk.size(); i++)
	{
		if (vsk[i].dIndex == 序号)
		{
			return vsk[i];
		}
	}*/
	return temp;
}
bool 是否存在此角色(登陆角色信息_ 角色信息)
{
	for (size_t i = 0; i < 全_角色列表.size(); i++)
	{
		if (角色信息.名称 == 全_角色列表[i].名称)
		{
			return true;
		}
	}
	return false;
}
void 登陆::初始化全局角色列表(vector<登陆角色信息_>& vsk)
{
	//MyTrace(L"vsk.size %d,  全_角色列表.size  %d,  直升状态  %d ", vsk.size(), 全_角色列表.size());
	if (vsk.size() != 全_角色列表.size())
	{
		if (全_角色列表.size() == 0)
		{
			全_角色列表.assign(vsk.begin(), vsk.end());
		}
		else if (vsk.size() > 全_角色列表.size())
		{
			for (size_t i = 0; i < vsk.size(); i++)
			{
				//MyTrace(L"遍历角色  %s  ,dIndex %d,  SrvId  %d,  dJob  %d,  直升状态  %d ",vsk[i].名称, vsk[i].dIndex, vsk[i].SrvId, vsk[i].dJob, vsk[i].直升状态);
				if (是否存在此角色(vsk[i]) == false)
				{
					全_角色列表.push_back(vsk[i]);

				}
			}
		}
	}
}
int 登陆::取任务已完成角色数量()
{
	int i = 0;
	for (size_t i = 0; i < 全_角色列表.size(); i++)
	{
		if (全_角色列表[i].任务是否完成 == true)
		{
			i++;
		}
	}
	/*登陆角色信息_ temp;
	vector<登陆角色信息_>vsk;
	登陆::get_CharacterList(vsk);
	for (size_t i = 0; i < vsk.size(); i++)
	{
		if (vsk[i].dIndex == 序号)
		{
			return vsk[i];
		}
	}*/
	return i;
}
void 登陆::设置任务已完成(CString 名称)
{



	for (size_t i = 0; i < 全_角色列表.size(); i++)
	{
		//MyTrace(L"遍历角色2  %s  ,dIndex %d,  SrvId  %d,  dJob  %d,  直升状态  %d ",全_角色列表[i].名称, 全_角色列表[i].dIndex, 全_角色列表[i].SrvId, 全_角色列表[i].dJob, 全_角色列表[i].直升状态);
		if (名称 == 全_角色列表[i].名称)
		{
			//MyTrace(L"设置角色完成1-50任务");
			全_角色列表[i].任务是否完成 = true;

			//break;
		}
	}
}
登陆角色信息_ 登陆::取未完成任务的角色()
{
	登陆角色信息_ temp;
	for (size_t i = 0; i < 全_角色列表.size(); i++)
	{
		if (全_角色列表[i].任务是否完成 == false)
		{
			return 全_角色列表[i];
		}
	}

	return temp;
}