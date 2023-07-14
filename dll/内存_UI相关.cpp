#include "内存_UI相关.h"
UIinfo_ getUiObjInfo(INT64 dObjAddr, DWORD dIndex, DWORD dId)
{
	UIinfo_ temp;
	DWORD dShow = R_DW(dObjAddr + 0x27C);//更新-0218
	INT64 addr_1 = R_QW(dObjAddr + 0X18);
	INT64 addr_2 = R_QW(addr_1 + 0x50 + 0X20);//更新-0218
	INT64 dNameAddr = R_QW(addr_2 + 0xF8);
	CString csName = L"空";
	if (dNameAddr)
	{
		csName = CString(R_String(R_QW(dNameAddr)));

	}
	temp.UIObj = dObjAddr;
	temp.CName = csName;
	temp.bShow = dShow;
	temp.dIndex = dIndex;
	temp.dId = dId;
	return temp;
	//if (/*csName.Find(L"quickSlotFrame") > 0*/ dShow)//获取快捷键UI地址
	/*{
		MyTrace(L"索引%X 对象地址0x%I64X ID %X 是否显示%d %s\r\n", dIndex, dObjAddr, dId, dShow, csName);
	}*/

}
void UI功能::getUiList(vector<UIinfo_>& vsk)
{
	//UIinfo_ temp;
	INT64 addr_1 = R_QW(游戏模块 + gb_UiList);
	INT64 addr_2 = R_QW(addr_1 + 0xA4);//更新-0218
	long dtotal = R_DW(addr_2 + 0x21C);
	INT64 objStartAddr = R_QW(addr_2 + 0x1D8);//对象数组地址
	INT64 indexStartAddr = R_QW(addr_2 + 0x214);//索引数组地址
	//MyTrace(L"objStartAddr 0x%I64X indexStartAddr 0x%I64X dtotal %d", objStartAddr, indexStartAddr, dtotal);
	for (long i = 0; i < dtotal; i++)
	{
		long dIndex = R_DW(indexStartAddr + i * 4);
		if (dIndex != 0xFFFFFFFF)
		{
			long dOffest = dIndex * 5 * 4;
			INT64 dObjAddr = R_QW(objStartAddr + dOffest + 4);
			WORD bId = R_W(objStartAddr + dOffest);//读双字节
			//MyTrace(L"dObjAddr 0x%I64X dIndex %D bId %d", dObjAddr, dIndex, bId);
			UIinfo_ temp = getUiObjInfo(dObjAddr, dIndex, bId);
			vsk.push_back(temp);
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
					bId = R_BYTE(objStartAddr + dOffest);//读字节
					UIinfo_ temp2 = getUiObjInfo(dObjAddr, dNextIndex, bId);
					vsk.push_back(temp2);
				}
			}
		}
	}
}
INT64 UI功能::getUiObjById_Old(DWORD ID)
{
	INT64 局_获取序幕对象call = 游戏模块 + 基址_新手_获取序幕对象call;
	INT64 局_获取序幕对象rcx = R_QW(游戏模块 + gb_UiList);
	INT64 reta;
	__try
	{
		__asm
		{
			sub rsp, 0x60
			mov rcx, 局_获取序幕对象rcx
			mov edx, ID
			mov r8, 1
			mov rdi, 局_获取序幕对象call
			call rdi
			add rsp, 0x60
			mov reta, rax
		}
	}
	__except (1)
	{
		DbgPrintf_Mine("getUiObjById error");
		return 0;
	}
	return reta;
}


bool UI功能::寻找打开窗口(CString name, INT64& rcx)
{
	CString temp;
	INT64 aaa = R_QW(游戏模块 + gb_UiList);
	temp.Format(L"aaa%I64X", aaa);
	//	DebugPrintf("%s\n", CStringA(temp));
	INT64 a = R_QW(aaa + 0xA4);//更新-0218
	DWORD 总数 = R_DW(a + 0x2D8);
	INT64 rdx = R_QW(a + 0x2F8);//对象数组地址
	//INT64 indexStartAddr = R_QW(addr_2 + 0x214);//索引数组地址
	for (size_t i = 0; i < 总数; i++)
	{

		//INT64 rcx = 0;
		//const char* message = lua_tostring(L, -1);
		//UI功能::寻找打开窗口(CStringW(message), rcx);

		//CString temp;
		//const char* message = lua_tostring(L, -1);
		////INT64 rcx = 0;
		////UI功能::寻找打开窗口(CStringW(message),rcx);
		//INT64 addr=UI功能::getUiObjByName(CStringW(message));

		DWORD rax = i + 1;
		INT64 参数 = rdx + rax * 5 * 4 + 4;

		INT64 addr_1 = R_QW(R_QW(参数) + 0X18);
		INT64 addr_2 = R_QW(addr_1 + 0x50 + 0X20);//更新-0218
		INT64 dNameAddr = R_QW(addr_2 + 0xF8);
		CString name1 = L"空";
		if (dNameAddr)
		{
			 name1 = CString(R_String(R_QW(dNameAddr)));
		//	MyTrace(L"%s", name1.GetString());

		}
	
		//CString name1 = getMsgBoxMiddleText2(R_QW(参数));


		temp.Format(L"%I64X", 参数);

		if (name1 == name)
		{
			rcx = R_QW(参数);
			temp.Format(L"%I64X", 参数);

			//MyTrace(name1);
			return 1;


		}
		//DWORD dIndex = R_DW(indexStartAddr + i * 4);


	}
	return 0;
}
INT64 UI功能::getUiObjById(DWORD ID)
{
	INT64 addr_1 = R_QW(游戏模块 + gb_UiList);
	INT64 addr_2 = R_QW(addr_1 + 0xA4);//更新-0218
	long dtotal = R_DW(addr_2 + 0x21C);
	INT64 objStartAddr = R_QW(addr_2 + 0x1D8);//对象数组地址
	INT64 indexStartAddr = R_QW(addr_2 + 0x214);//索引数组地址
	//MyTrace(L"objStartAddr 0x%I64X indexStartAddr 0x%I64X dtotal %d", objStartAddr, indexStartAddr, dtotal);
	for (size_t i = 0; i < dtotal; i++)
	{
		/*if (i > 3000)
		{
			break;
		}*/
		DWORD dIndex = R_DW(indexStartAddr + i * 4);
		//if (dIndex != 0xFFFFFFFF)
		if (dIndex != -1)
		{
			long dOffest = dIndex * 5 * 4;
			INT64 dObjAddr = R_QW(objStartAddr + dOffest + 4);
			WORD bId = R_W(objStartAddr + dOffest);//读双字节
			if (bId == ID)
			{
				return dObjAddr;
			}
			DWORD dNextIndex = 0;
			DWORD count = 0;
			while (1)
			{
				count = count + 1;
				/*if (count >= 10000)
				{
					return 0;
				}*/
				dNextIndex = R_DW(objStartAddr + dOffest + 0xC);
				if (dNextIndex == -1)//为-1跳出循环
				{
					break;
				}
				else
				{
					dOffest = dNextIndex * 5 * 4;
					dObjAddr = R_QW(objStartAddr + dOffest + 4);
					bId = R_W(objStartAddr + dOffest);//读字节
					if (bId == ID)
					{
						return dObjAddr;
					}
				}
			}
		}
	}
	return 0;
}
INT64 UI功能::getUiObjByName(CString name)
{
	vector<UIinfo_>vsk;
	getUiList(vsk);
	for (size_t i = 0; i < vsk.size(); i++)
	{
		if (vsk[i].CName == name)
		{
			return vsk[i].UIObj;
		}
	}
	return 0;
}
DWORD UI功能::getUiIdByName(CString name)
{
	vector<UIinfo_>vsk;
	getUiList(vsk);
	for (size_t i = 0; i < vsk.size(); i++)
	{
		if (vsk[i].CName == name)
		{
			return vsk[i].dId;
		}
	}
	return 0;
}
INT64 内存_UI_获取按键参数()
{
	/*INT64局_数组头;
	long 局_成员数;
	long i;
	INT64局_Obj;
	INT64局_虚表地址;*/
	//' 获取按键参数;
	INT64 局_v1 = R_QW(R_QW(游戏模块_EFEngine + 基址_UI_按键参数) + 偏移_UI_按键参数);
	if (局_v1 == 0) {
		return 0;
	}
	INT64 局_数组头 = R_QW(局_v1 + 112); // ' 0x70;
	DWORD 局_成员数 = R_DW(局_v1 + 112 + 8); // ' 0x78;
	for (size_t i = 0; i < 局_成员数; i++)
	{
		INT64 局_Obj = R_QW(局_数组头 + i * 8);
		INT64 局_虚表地址 = R_QW(R_QW(局_Obj) + 偏移_UI_按键虚表);
		if (R_BYTE(局_虚表地址 + 174) == 116)
		{
			return 局_Obj;
		}
	}
	return 0;
}
DWORD  内存_UI_键码转换(DWORD  待转换键码)
{
	INT64 局_rcx = 0;
	INT64 局_v1 = R_QW(R_QW(游戏模块_EFEngine + 基址_UI_按键参数) + 偏移_UI_按键参数 - 24);
	INT64 局_rdx = R_QW(局_v1 + 188);  //' 0xBC;
	INT64 局_r8 = R_QW(局_v1 + 128); // ' 80;
	DWORD 局_eax = R_DW(局_rdx + 待转换键码 * 4);
	if (局_eax == -1) {
		return 0;
	}
	do {
		局_rcx = 局_eax;
		局_rdx = 局_rcx + 局_rcx * 4;
		if (R_BYTE(局_r8 + 局_rdx * 4) == 待转换键码) {
			return R_DW(局_r8 + 局_rdx * 4 + 4);
		}
		局_eax = R_DW(局_r8 + 局_rdx * 4 + 12);


	} while (局_eax != -1);
	return 0;
}

bool UI功能::内存按键(DWORD 加密键码, DWORD 类型)
{
	INT64 按键参数 = 内存_UI_获取按键参数();
	if (按键参数 == 0 || 加密键码 == 0)
	{
		return false;
	}
	INT64 dCALL = R_QW(R_QW(按键参数) + 偏移_UI_按键虚表);
	if (dCALL)
	{
		DWORD 局_类型 = 类型;
		DWORD 转换后键码 = 内存_UI_键码转换(加密键码);
		if (局_类型 == 0)
		{
			MainUniversalCALL4(按键参数, 0, 转换后键码, 0, dCALL);
		}
		if (局_类型 == 1)
		{
			MainUniversalCALL4(按键参数, 0, 转换后键码, 1, dCALL);
		}
		if (局_类型 == 2)
		{
			MainUniversalCALL4(按键参数, 0, 转换后键码, 0, dCALL);
			Sleep(100);
			MainUniversalCALL4(按键参数, 0, 转换后键码, 1, dCALL);
		}
		return true;
	}
	return false;

}
bool UI功能::地图是否打开()
{
	INT64 局_UI对象 = UI功能::getUiObjById(152);
	if (R_BYTE(局_UI对象 + 184) == 1)
	{
		return true;
	}
	return false;
}

bool UI功能::怪物击杀求饶界面是否打开()
{
	INT64 局_UI对象 = UI功能::getUiObjById(0x177);//ID 31 是否显示0 topRightInfoNoticeFrame
	if (R_BYTE(局_UI对象 + 0x27C) == 0)
	{
		return true;
	}
	return false;
}
bool UI功能::经验条界面是否显示()
{
	INT64 局_UI对象 = UI功能::getUiObjById(0x64);//ID 31 是否显示0  root1.arkui.frameCanvas.experienceFrame
	if (R_BYTE(局_UI对象 + 0x27C) == 1)
	{
		return true;
	}
	return false;
}
bool UI功能::背包界面是否显示()
{
	INT64 局_UI对象 = UI功能::getUiObjById(0x1A);//ID 31 是否显示0  root1.arkui.windowCanvas.inventoryWnd
	if (R_BYTE(局_UI对象 + 0x27C) == 1)
	{
		//MyTrace(L"背包显示");
		return true;
	}
	return false;
}
bool UI功能::大地图是否显示()
{
	INT64 局_UI对象 = UI功能::getUiObjById(0x23D);//ID 98 是否显示0   root1.arkui.windowCanvas.worldMapWnd
	if (R_BYTE(局_UI对象 + 0x27C) == 1)
	{
		return true;
	}
	return false;
}
bool UI功能::体验职业中界面是否显示()
{
	INT64 局_UI对象 = UI功能::getUiObjById(0x1DC);//I 是否显示0   root1.arkui.frameCanvas.sorceressSkinFrame
	if (局_UI对象 == 0)
	{
		局_UI对象 = UI功能::getUiObjById(0xDC);
	}
	if (R_BYTE(局_UI对象 + 0x27C) == 1)
	{
		return true;
	}
	return false;
}
bool UI功能::副本界面是否打开()
{
	INT64 局_UI对象 = UI功能::getUiObjById(168);
	INT64 局_UI对象2 = UI功能::getUiObjById(198);
	INT64 局_UI对象3 = UI功能::getUiObjById(0x99);

	if (局_UI对象)
	{
		if (R_BYTE(局_UI对象 + 偏移_UI_显示) == 1)
		{
			return true;
		}
	}
	if (局_UI对象2)
	{
		if (R_BYTE(局_UI对象2 + 偏移_UI_显示) == 1)
		{
			return true;
		}
	}
	if (局_UI对象3)
	{
		if (R_BYTE(局_UI对象3 + 偏移_UI_显示) == 1)
		{
			return true;
		}
	}

	return false;
}
bool UI功能::航海出港()
{
	if (UI功能::是否在航海准备界面() == false)
	{
		内存按键('Z');
		return false;
	}
	INT64 dCALL = 游戏模块 + 基址_UI_航海出港call;
	INT64 dRCX = R_QW(游戏模块 + 基址_UI_航海出港rcx);
	if (dRCX != 0)
	{
		MainUniversalCALL2(dRCX, 0, dCALL);
		return true;
	}
	return false;
}
bool UI功能::航海入港()
{
	if (UI功能::是否在航海准备界面() == false)
	{
		内存按键('Z');
		return false;
	}
	INT64 dCALL = 游戏模块 + 基址_UI_航海入港call;
	INT64 dRCX = R_QW(游戏模块 + 基址_UI_航海出港rcx);
	if (dRCX != 0)
	{
		MainUniversalCALL2(dRCX, 0, dCALL);
		return true;
	}
	return false;
}

bool UI功能::进入副本()
{
	INT64 局_UI对象 = UI功能::getUiObjById(168);

	if (局_UI对象)
	{
		if (R_BYTE(局_UI对象 + 偏移_UI_显示) == 1)
		{
			INT64 局_rcx = 局_UI对象 + 偏移_UI_进入副本按钮;
			INT64 dCALL = 游戏模块 + 基址_副本_进入其他副本call;
			MainUniversalCALL2(局_rcx, 0, dCALL);
			return true;
		}
	}
	INT64 局_UI对象2 = UI功能::getUiObjById(198);
	if (局_UI对象2)
	{
		if (R_BYTE(局_UI对象2 + 偏移_UI_显示) == 1)
		{
			INT64 局_rcx = 局_UI对象2;
			INT64 dCALL = 游戏模块 + 基址_副本_入场CALL;
			MainUniversalCALL2(局_rcx, 0, dCALL);
			return true;
		}
	}
	INT64 局_UI对象3 = UI功能::getUiObjById(0x99);
	if (局_UI对象3)
	{
		if (R_BYTE(局_UI对象3 + 偏移_UI_显示) == 1)
		{
			INT64 局_rcx = 局_UI对象3 + 偏移_UI_进入副本按钮;
			INT64 dCALL = 游戏模块 + 基址_副本_进入其他副本call;
			MainUniversalCALL2(局_rcx, 0, dCALL);
			return true;
		}
	}


	return false;
}
INT64 内存_UI_取采集标识对象()
{
	string 局_文本标识;
	CString WName;
	INT64 局_rcx = R_QW(R_QW(游戏模块 + 基址_个人_遍历) + 164);
	INT64 局_数组头 = R_QW(局_rcx + 760);
	int 局_成员数 = R_DW(局_rcx + 800);
	for (size_t i = 0; i < 局_成员数; i++)
	{
		INT64 局_对象 = R_QW(局_数组头 + (i - 1) * 5 * 4 + 4);
		if (局_对象 != 0) {

			局_文本标识 = UnicodeToAnsi(R_CString(R_QW(R_QW(局_对象 + 188))));
			WName = CString(局_文本标识.c_str());
		}
		if (WName.Find(L"DataArray") != -1)
		{
			return 局_对象;
		}
	}
	return 0;
}


bool UI功能::是否出现G()
{
	INT64 局_UI对象 = 内存_UI_取采集标识对象();
	if (局_UI对象 == 0)
	{
		return false;
	}
	if (R_DW(局_UI对象 + 偏移_其他_采集标识) == 0)
	{
		return false;
	}
	return true;
}
bool UI功能::是否读条()
{
	INT64 局_本人真实对象 = 本人::取真实对象();
	if (局_本人真实对象 == 0)
	{
		return false;
	}
	INT64 局_V1 = R_QW(局_本人真实对象 + 偏移_UI_读条1);
	if (局_V1 == 0)
	{
		return false;
	}
	INT64 局_V2 = 局_V1 + 偏移_UI_读条2;
	for (size_t i = 0; i < 9; i++)
	{
		if (R_DW(局_V2 + i * 4) == 1)
		{
			return true;
		}
	}

	return false;
}
bool UI功能::是否在航海准备界面()
{
	INT64 局_UI对象 = UI功能::getUiObjById(178);
	if (局_UI对象 == 0)
	{
		return false;
	}
	if (R_DW(局_UI对象 + 偏移_UI_航海界面) == 1)
	{
		return true;
	}
	return false;
}

bool UI功能::是否在交接任务界面()
{
	INT64 局_UI对象 = UI功能::getUiObjById(50);
	if (局_UI对象 == 0)
	{
		return false;
	}
	if (R_DW(局_UI对象 + 偏移_UI_显示) == 1)
	{
		return true;
	}
	return false;
}
bool UI功能::准备出航()
{
	if (!UI功能::大地图是否显示())
	{
		UI功能::内存按键('M');
		Sleep(2000);
		return false;
	}
	//INT64 局_UI对象 = UI功能::getUiObjById(152);
	INT64 局_UI对象 = UI功能::getUiObjById(573);
	if (局_UI对象 == 0)
	{
		return false;
	}
	if (R_DW(局_UI对象 + 偏移_UI_显示) != 1)
	{
		return false;
	}
	MainUniversalCALL2(局_UI对象, 0, 游戏模块 + 基址_UI_准备出航call);
	return true;
}

void getMiddle_textFieldAddr(INT64 dChildAddr, INT64& dRetAddr)
{
	if (dRetAddr) return;
	INT64 dstart = R_QW(dChildAddr + 0xE0);
	DWORD dtotal = R_DW(dChildAddr + 0xE8);
	if (dtotal < 5 && dstart)//防止读到不是数组地址造成死循环
	{
		for (DWORD j = 0; j < dtotal; j++)
		{
			INT64 dTempAddr = R_QW(dstart + j * 0x10);
			INT64 dStrAddr = R_QW(dTempAddr + 0x70);
			if (dStrAddr)
			{
				dStrAddr = R_QW(dStrAddr + 0x10);
				dStrAddr = R_QW(dStrAddr);
				CString cName = CString(R_String(dStrAddr));
				if (_tcscmp(cName, L"textField") == 0)
				{
					dRetAddr = dTempAddr;
				//	MyTrace(L"文本地址%I64X", dTempAddr);
				}
			}
			getMiddle_textFieldAddr(dTempAddr, dRetAddr);
		}
	}
}
void getMsgBoxMiddleText(INT64 dUIObj)
{
	INT64 addr_1 = R_QW(dUIObj + 0x18);
	INT64 addr_2 = R_QW(addr_1 + 0x70);
	INT64 addr_3 = R_QW(addr_2 + 0x60);
	INT64 dstart = R_QW(addr_3 + 0xE0);
	long dtotal = R_DW(addr_3 + 0xE8);
	for (DWORD i = 0; i < dtotal; i++)
	{
		INT64 dChildAddr = R_QW(dstart + i * 0x10);
		INT64 dStrAddr = R_QW(dChildAddr + 0x70);
		if (dStrAddr)
		{
			dStrAddr = R_QW(dStrAddr + 0x10);
			dStrAddr = R_QW(dStrAddr);
			CString cName = CString(R_String(dStrAddr));
			if (_tcscmp(cName, L"middleComponent") == 0 || _tcscmp(cName, L"titleBtn") == 0)
			{

				INT64 dTextAddr = 0;
				getMiddle_textFieldAddr(dChildAddr, dTextAddr);
				if (dTextAddr)
				{
					dStrAddr = R_QW(dTextAddr + 0x108);
					CString cTxt = UTF82WCS(R_String(dStrAddr + 0xB));//大漠读的UTF8格式
					//MyTrace(L"地址%I64X %s", dTextAddr, cTxt);
					//if (cTxt.Find(L"进入") != -1 || cTxt.Find(L"Enter") != -1)
					//{
					//	Fun_MsgBoxConfirm(dUIObj);
					//	return;
					//}*/
					////return cTxt;

				}

			}

		}
	}
}
void Fun_MsgBoxConfirm(INT64 dUIObj)
{
	if (dUIObj)
	{
		INT64  dCall = 游戏模块 + gc_MsgBoxConfirm;
		MainUniversalCALL2(dUIObj, 0, dCall);
	}

}
bool  UI功能::getMsgBoxTextList()
{
	INT64 addr_1 = R_QW(游戏模块 + gb_UiList);
	DWORD dtotal = R_DW(addr_1 + 0x144);
	INT64 dstart = R_QW(addr_1 + 0x13C);//对象数组地址
	for (long i = 0; i < dtotal; i++)
	{
		INT64 dUIObj = R_QW(dstart + i * 0xC);

		//DWORD dPraentId = R_DW(dUIObj + 0x12C);//丢弃物品这种不是全局弹窗的用
		DWORD dPraentId = R_DW(dUIObj + 0x12C);//丢弃物品这种不是全局弹窗的用
	//	MyTrace(L"dUIObj 0x%I64X 0x%I64X", dUIObj, dPraentId);
		CString 窗口文本 = getMsgBoxMiddleText2(dUIObj);
		MyTrace(L"窗口文本 %s", 窗口文本);
		if (窗口文本.Find(L"Enter the Chaos Dungeon") != -1 || 窗口文本.Find(L"Do you want to go back to the character selection screen") != -1 || 窗口文本.Find(L"Teleport") != -1 || 窗口文本.Find(L"空间移动") != -1)
			//if (dPraentId == 1)
		{
			MyTrace(L"点击游戏内确定弹窗");
			Fun_MsgBoxConfirm(dUIObj);
			return false;
		}
		if (窗口文本.Find(L"Enter the Chaos Dungeon") != -1 || 窗口文本.Find(L"Do you want to go back to the character selection screen") != -1 || 窗口文本.Find(L"Teleport") != -1 || 窗口文本.Find(L"作为你的返回点吗") != -1)
			//if (dPraentId == 1)
		{
			MyTrace(L"点击绑定回城城市");
			Fun_MsgBoxConfirm(dUIObj);
			return false;
		}
		if (窗口文本.Find(L"Enter the Chaos Dungeon") != -1 || 窗口文本.Find(L"Do you want to go back to the character selection screen") != -1 || 窗口文本.Find(L"Teleport") != -1 || 窗口文本.Find(L"雇佣船员") != -1)
			//if (dPraentId == 1)
		{
			MyTrace(L"雇佣船员");
			Fun_MsgBoxConfirm(dUIObj);
			return false;
		}
		if (窗口文本.Find(L"Enter the Chaos Dungeon") != -1 || 窗口文本.Find(L"Do you want to go back to the character selection screen") != -1 || 窗口文本.Find(L"Teleport") != -1 || 窗口文本.Find(L"准备出航") != -1)
			//if (dPraentId == 1)
		{
			MyTrace(L"准备出航");
			Fun_MsgBoxConfirm(dUIObj);
			return false;
		}
		//getMsgBoxMiddleText(dUIObj);


	}
	return true;
}

CString UI功能::getMsgBoxMiddleText2(INT64 dUIObj)
{
	INT64 addr_1 = R_QW(dUIObj + 0x18);
	INT64 addr_2 = R_QW(addr_1 + 0x70);
	INT64 addr_3 = R_QW(addr_2 + 0x60);
	INT64 dstart = R_QW(addr_3 + 0xE0);
	long dtotal = R_DW(addr_3 + 0xE8);
	CString 返回文本 = L"";
	for (DWORD i = 0; i < dtotal; i++)
	{
		INT64 dChildAddr = R_QW(dstart + i * 0x10);
		INT64 dStrAddr = R_QW(dChildAddr + 0x70);
		if (dStrAddr)
		{
			dStrAddr = R_QW(dStrAddr + 0x10);
			dStrAddr = R_QW(dStrAddr);
			CString cName = CString(R_String(dStrAddr));
			if (_tcscmp(cName, L"middleComponent") == 0 || _tcscmp(cName, L"titleBtn") == 0)
			{

				INT64 dTextAddr = 0;
				getMiddle_textFieldAddr(dChildAddr, dTextAddr);
				if (dTextAddr)
				{
					dStrAddr = R_QW(dTextAddr + 0x108);
					CString cTxt = UTF82WCS(R_String(dStrAddr + 0xB));//大漠读的UTF8格式
					返回文本 = 返回文本 + cTxt;
					/*MyTrace(L"地址%I64X %s", dTextAddr, cTxt);
					if (cTxt.Find(L"进入") != -1 || cTxt.Find(L"Enter") != -1)
					{
						Fun_MsgBoxConfirm(dUIObj);
						return;
					}*/
					//return cTxt;

				}

			}

		}
	}
	return 返回文本;
}
CString  UI功能::getMsgBoxText()
{
	INT64 addr_1 = R_QW(游戏模块 + gb_UiList);
	DWORD dtotal = R_DW(addr_1 + 0x144);
	INT64 dstart = R_QW(addr_1 + 0x13C);//对象数组地址
	for (long i = 0; i < dtotal; i++)
	{
		if (i >= 500)
		{
			return L"";
		}
		INT64 dUIObj = R_QW(dstart + i * 0xC);
		DWORD dPraentId = R_DW(dUIObj + 0x12C);//丢弃物品这种不是全局弹窗的用
		return getMsgBoxMiddleText2(dUIObj);


	}
	return L"";
}
CString  UI功能::getMsgBoxText_全()
{
	INT64 addr_1 = R_QW(游戏模块 + gb_UiList);
	DWORD dtotal = R_DW(addr_1 + 0x144);
	INT64 dstart = R_QW(addr_1 + 0x13C);//对象数组地址
	CString 返回文本 = L"";
	for (long i = 0; i < dtotal; i++)
	{
		if (i >= 500)
		{
			return L"";
		}
		INT64 dUIObj = R_QW(dstart + i * 0xC);
		DWORD dPraentId = R_DW(dUIObj + 0x12C);//丢弃物品这种不是全局弹窗的用
		CString 返回 = getMsgBoxMiddleText2(dUIObj);
		返回文本 = 返回文本 + 返回 + "|";

	}
	return 返回文本;
}

INT64 getChildUiAddrByStr(INT64 dParentAddr, CString cChildName)
{
	INT64 dstart = R_QW(dParentAddr + 0xE0);
	long dtotal = R_DW(dParentAddr + 0xE8);
	for (DWORD i = 0; i < dtotal; i++)
	{
		INT64 dChildAddr = R_QW(dstart + i * 0x10);
		INT64 dStrAddr = R_QW(dChildAddr + 0x70);
		if (dStrAddr)
		{
			dStrAddr = R_QW(dStrAddr + 0x10);
			dStrAddr = R_QW(dStrAddr);
			CString cName = CString(R_String(dStrAddr));
			//MyTrace(L"0x%I64X %s", dStrAddr, cName);
			if (_tcscmp(cName, cChildName) == 0)
			{
				return dChildAddr;
			}
		}
	}
	return 0;
}

INT64 getUiFirstAddr(INT64 dUiObj)
{
	//INT64 addr_1 = R_QW(dUiObj + 0x18);
	//INT64 addr_2 =R_QW(addr_1 + 0x70);
	INT64 addr_3 = R_QW(R_QW(R_QW(dUiObj + 0x18) + 0x70) + 0x60);
	return addr_3;
}

void UI功能::getNpcTalkSelectList(vector<CString>& 对话组)
{
	对话组.clear();
	INT64 dUiObj = UI功能::getUiObjById(0x1B);;//interactionMainFrame 
	INT64 addr_first = getUiFirstAddr(dUiObj);
	INT64 addr_1 = getChildUiAddrByStr(addr_first, L"talkSelectButtonGroup");
	DWORD dShow = R_W(addr_1 + 0x6A);
	//MyTrace(L"0x%I64x / 0x%I64x / 0x%I64x %d", dUiObj, addr_first,addr_1,dShow >> 0xe);
	if (dShow >> 0xe == 1)//判断显示
	{

		INT64 dstart = R_QW(addr_1 + 0xE0);
		long dTotal = R_DW(addr_1 + 0xE8);
		for (int i = 0; i < dTotal; i++)
		{
			INT64 addr_2 = R_QW(dstart + i * 0x10);
			dShow = R_W(addr_2 + 0x6A);
			//MyTrace(L"addr_2 0x%I64x /  %d", addr_2, dShow >> 0xe);
			if (dShow >> 0xe == 1)//判断显示
			{
				INT64 dStrAddr = R_QW(addr_2 + 0x70);
				if (dStrAddr)
				{
					dStrAddr = R_QW(dStrAddr + 0x10);
					dStrAddr = R_QW(dStrAddr);
					CString cName = CString(R_String(dStrAddr));
					//MyTrace(L"cName %s",cName);
					if (_tcsstr(cName, L"talkButtonGroup_"))//判断是否包含字符串talkButton_
					{
						INT64 dstart2 = R_QW(addr_2 + 0xE0);
						long dTotal2 = R_DW(addr_2 + 0xE8);
						for (int j = 0; j < dTotal2; j++)
						{
							INT64 addr_4 = R_QW(dstart2 + j * 0x10);
							DWORD dShow4 = R_W(addr_4 + 0x6A);
							DWORD straddr = R_QW(addr_4 + 0x70);
							straddr = R_QW(straddr + 0x10);
							straddr = R_QW(straddr);
							CString cstrName = CString(R_String(straddr));
							//MyTrace(L"%s addr_4 0x%I64x /  %d", cstrName, addr_4, dShow4 >> 0xe);
							if (dShow4 >> 0xe == 1)//判断显示
							{
								INT64 addr_3 = getChildUiAddrByStr(addr_4, L"tf");
								if (addr_3)
								{
									dShow = R_W(addr_3 + 0x6A);
									//MyTrace(L"addr_3 0x%I64x /  %d", addr_2, dShow >> 0xe);
									if (dShow >> 0xe == 1)//判断显示
									{
										INT64 dTextAddr = R_QW(addr_3 + 0x108);
										//MyTrace(L"dTextAddr 0x%I64X", dTextAddr);
										//string sText = R_CString(dTextAddr+0xB);
										CString cText = UTF82WCS(R_String(dTextAddr + 0xB));
										对话组.push_back(cText);
										//MyTrace(L"对话: %s", cText);
										//wchar_t buf[MAX_PATH];
										/*swprintf(buf, L"地址0x%I64X %s 0x%I64X %s\r\n", addr_2, cName, dTextAddr,cText);
										MyTrace(L"对话: %s", buf);*/
									}
								}
							}
						}
					}
				}
			}
		}
	}
}

bool UI功能::指定UI是否显示(CString UIName)
{
	INT64 局_UI对象 = UI功能::getUiObjByName(UIName);
	if (R_BYTE(局_UI对象 + 0x27C) == 1)
	{
		return true;
	}
	return false;
}
bool UI功能::商店是否打开()
{
	INT64 局_UI对象 = UI功能::getUiObjById(0x1F);//arkui.windowCanvas.marketWnd
	if (R_BYTE(局_UI对象 + 0x27C) == 1)
	{
		return true;
	}
	return false;
}
bool UI功能::退出菜单是否打开()
{
	INT64 局_UI对象 = UI功能::getUiObjById(0x29);//root1.arkui.windowCanvas.exitMenuWindow
	if (R_BYTE(局_UI对象 + 0x27C) == 1)
	{
		return true;
	}
	return false;
}


bool UI功能::复活界面是否显示()
{
	INT64 局_UI对象 = UI功能::getUiObjById(0x3A);//ID 31 是否显示0  root1.arkui.windowCanvas.inventoryWnd
	if (R_BYTE(局_UI对象 + 0x27C) == 1)
	{
		MyTrace(L"复活界面显示");
		return true;
	}
	return false;
}

bool UI功能::复活(CString 复活方式)
{
	if (UI功能::get_DeadSceneListBtnState())
	{
		int 复活type = UI功能::get_DeadSceneList(复活方式);
		if (复活type != -1)
		{
			INT64 dCALL = 游戏模块 + gc_deadSceneWndBtn;
			INT64 dRCX = UI功能::getUiObjById(0x3A);
			if (dRCX != 0)
			{
				MainUniversalCALL2(dRCX, 复活type, dCALL);
				return true;
			}
		}
		else
		{
			MyTrace(L"复活type错误");
			return false;
		}
	}
	return false;
}

int UI功能::get_DeadSceneList(CString 复活方式)
{
	INT64 dUiObj = UI功能::getUiObjById(0x3A);
	if (dUiObj)
	{
		DWORD dShow = R_DW(dUiObj + 0x27C);
		if (dShow)
		{
			INT64 dtotal = R_QW(dUiObj + go_deadSceneTotal);
			INT64 dstart = dUiObj + go_deadSceneStart;
			for (DWORD i = 0; i < dtotal; i++)
			{
				DWORD dType = R_DW(dstart + i * 0x28);
				INT64 dTexAddr = R_QW(dstart + i * 0x28 + 0x4);
				CString cName = L"空";
				cName = R_CString(dTexAddr);
				if (cName == 复活方式)
				{
					return dType;
				}
			//	MyTrace(L"UI地址0x%I64X 索引%d 类型%d %s\r\n", dUiObj, i, dType, cName);
			}

		}
	}
	return -1;
}

CString UI功能::getUiName(INT64 dObjAddr)
{
	INT64 addr_1 = R_QW(dObjAddr + 0X18);
	INT64 addr_2 = R_QW(addr_1 + 0x70);
	INT64 dNameAddr = R_QW(addr_2 + 0xF8);
	CString csName = L"空";
	if (dNameAddr)
	{
		//MyTrace(L"csName 长度 %d  内容 %s", sizeof(R_String(R_QW(dNameAddr))), UTF82WCS(R_String(R_QW(dNameAddr))));
		csName = UTF82WCS((R_String(R_QW(dNameAddr))));
	}
	return csName;
}

bool UI功能::get_DeadSceneListBtnState()//获取复活按钮状态
{

	INT64 dUiObj = UI功能::getUiObjById(0x3A);
	if (dUiObj)
	{
		DWORD dShow = R_DW(dUiObj + 0x27C);
		if (dShow)
		{
			long dtotal = R_DW(dUiObj + go_DeadSceneChildList + 0x10 + 0x18);//__int64 go_DeadSceneChildList = 0x17C;
			INT64 dKeyAddr = R_QW(dUiObj + go_DeadSceneChildList + +0x20);//对象数组地址
			if (!dKeyAddr)
			{
				dKeyAddr = dUiObj + go_DeadSceneChildList + 0x10;
			}
			long dKeyValue = R_DW(dKeyAddr);
			INT64 objStartAddr = R_QW(dUiObj + go_DeadSceneChildList);
			for (DWORD i = 0; i < dtotal; i++)
			{
				long dKeyValue = R_DW(dKeyAddr + (i / 0x20) * 4);
				DWORD dNum = i % 0x20;
				DWORD dCheck = (dKeyValue >> dNum) & 1;
				if (dCheck)
				{
					INT64 dObj = R_QW(objStartAddr + i * 0x18 + 0x8);
					if (dObj)
					{
						if (R_QW(dObj + 8) == 0) continue;
						CString cWidgetName = getUiName(dObj);
						INT64 addr_3 = getUiFirstAddr(dObj);
						INT64 dataAddr = R_QW(addr_3 + 0x150);
						dataAddr = R_QW(dataAddr + 0x368);
						INT64 dStateStrAddr = R_QW(dataAddr);
						CString stateName = UTF82WCS(R_String(dStateStrAddr));
						WORD dValue = R_W(addr_3 + 0x6A);
						BOOL bView = 0;
						if (dValue >> 0xe == 1 && stateName == L"up")
						{
							bView = 1;//显示中
						//	MyTrace(L"0%I64X %s 是否显示%d 状态%s\r\n", addr_3, cWidgetName, bView, stateName);
							return true;
						}
					//	MyTrace(L"0%I64X %s 是否显示%d 状态%s\r\n", addr_3, cWidgetName, bView, stateName);
					}
				}
			}
		}
	}
	return false;
}

int UI功能::getGameCurStageValue()
{
	DWORD dValue = 0;
	INT64 addr_1 = R_QW(游戏模块 + gb_PacketInfo);
	INT64 dObj = R_QW(addr_1 + go_PacketSocketObj);//这为0 表示掉线
	if (dObj)
	{
		INT64 addr_2 = R_QW(addr_1 + go_GameStageValue);
		dValue = R_DW(addr_2);
		if (dValue == 3)//选服务器
		{
		}
		else if (dValue == 5)//选角色
		{
		}
		else if (dValue == 7)//选角色进游戏
		{
		}
		else if (dValue == 9)//游戏中
		{
		}
		else if (dValue == 10)//游戏返回选角色
		{
		}
		else if (dValue == 13)//游戏返回选角色
		{
		}
		else if (dValue == 11)//选角色返回选服务器
		{
		}
		else if (dValue == 2)//可能是载入服务器
		{
		}
		if (dValue == 0)//掉线
		{
		}
	}
	return dValue;
}

bool UI功能::bCheckItemDisassemleWnd()
{
	INT64 局_UI对象 = UI功能::getUiObjByName(L"root1.arkui.windowCanvas.itemDisassembleWnd");//root1.arkui.windowCanvas.itemDisassembleWnd
	if (R_BYTE(局_UI对象 + 0x27C) == 1)
	{
		return true;
	}
	return false;
}

void UI功能::Fun_UiShowCtrl(int dUiId)
{
	INT64 addr_1 = R_QW(游戏模块 + gb_UiList);
	MainUniversalCALL2(addr_1, dUiId, 游戏模块 + gc_UIShowCtrl);

}
void UI功能::控件点击call(INT64 对象)
{
	UCHAR 局_rdx0[0x100] = { 0 };
	W_DW((ULONG64)&局_rdx0[0], 0x100000C);
	INT64 call地址 = R_QW(对象);
	call地址 = R_QW(call地址 + 0x338);

	INT64 rdx = (INT64)&局_rdx0;
	INT64 rcx = 对象;

	MainUniversalCALL6(rcx, rdx, 0, 0, 0, 0x100000C, call地址);
	//W_Float((ULONG64)&局_rdx0[0], px);


}

CString UI功能::UI名称1(INT64 对象)
{
	INT64 addr_1 = R_QW(对象 + 0x70);
	INT64 addr_2 = R_QW(addr_1 + 0x10);
	INT64 addr_3 = R_QW(addr_2);
	string 路径名称 = R_String(addr_3);



	return CStringW(路径名称.c_str());
}




CString UI功能::UI名称(INT64 对象)
{
	INT64 addr_1 = R_QW(对象 + 0x70);
	INT64 addr_2 = R_QW(addr_1 + 0x10);
	INT64 addr_3 = R_QW(addr_2);
	string 路径名称 = R_String(addr_3);

	if (路径名称 == "")
	{
		addr_1 = R_QW(对象 + 0x618);
		addr_2 = R_QW(addr_1 + 0xF8);
		addr_3 = R_QW(addr_2);
		路径名称 = R_String(addr_3);
		if (路径名称 == "")
		{
			addr_1 = R_QW(对象 + 0x630);
			addr_2 = R_QW(addr_1);
			路径名称 = R_String(addr_2);


		}


	}


	return CStringW(路径名称.c_str());
}
DWORD UI功能::窗口数量()
{
	INT64 addr_1 = R_QW(游戏模块 + gb_UiList);
	DWORD dtotal = R_DW(addr_1 + 0x144);
	return dtotal;

}
CString  UI功能::窗口反馈文本()
{
	INT64 addr_1 = R_QW(游戏模块 + gb_UiList);
	DWORD dtotal = R_DW(addr_1 + 0x144);
	INT64 dstart = R_QW(addr_1 + 0x144 - 8);//对象数组地址
	CString 返回文本 = L"";
	for (long i = 0; i < dtotal; i++)
	{
		if (i >= 500)
		{
			return L"";
		}



		INT64 dUIObj = R_QW(dstart + i * 0xC);

		//DWORD dPraentId = R_DW(dUIObj + 0x12C);//丢弃物品这种不是全局弹窗的用
		DWORD dPraentId = R_DW(dUIObj + 0x12C);//丢弃物品这种不是全局弹窗的用
		//MyTrace(L"dUIObj 0x%I64X 0x%I64X", dUIObj, dPraentId);
		CString 返回 = getMsgBoxMiddleText2(dUIObj);


		返回文本 = 返回文本 + 返回 + "|";

	}
	return 返回文本;
}

//void UI功能::Fun_NarrationAssistance_OnOff(int kaiguan)
//{
//	INT64 UIAddr = UI功能::getUiObjByName(L"root1.arkui.frameCanvas.narrationAssistanceFrame");
//	if (UIAddr)
//	{
//		MainUniversalCALL2(UIAddr, kaiguan, 游戏模块 + gc_narrationAssistanceOnOff);
//	}
//}
//
//void UI功能::Fun_NarrationAssistance_Continue()
//{
//	INT64 UIAddr = UI功能::getUiObjByName(L"root1.arkui.frameCanvas.narrationAssistanceFrame");
//	if (UIAddr)
//	{
//		MainUniversalCALL2(UIAddr, 0, 游戏模块 + gc_NarrationAssistanceContinue);
//	}
//
//}