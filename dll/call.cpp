#include "call.h"

EXTERN_C void  setHookCallBackProc(INT64);
EXTERN_C void HookCallBack_1();
EXTERN_C void  setHookCRC_01(INT64);
//EXTERN_C QWORD g_hWowModuleBase;
//void Addasm(int a, int b)
EXTERN_C void HookCallBack_2();

extern "C"
{
	QWORD g_hWowModuleBase;
	int mceshi = 100;
	void callceshi()
	{
		mceshi = 101;

	}
	
}

 std::mutex mtx;

void _HookProc(__int64 pAddress, __int64 crc_val, __int64 count, __int64 nNo)
{
	DbgPrintf_Mine("pAddress %I64X   crc_val 0x%I64X  count 0x%I64X  nNo 0x%I64X   \r\n", pAddress, crc_val, count, nNo);
	//HMODULE hModule = GetModuleHandle(NULL);
	//__int64 nCRC = crc_val;
	//__int64 pRVA = pAddress - (__int64)hModule;

	//for (int i = 0; i < CRC_NUM; i++)
	//{
	//	//先判断是否是正常地址CRC
	//	if (pRVA <= g_crc[i].m_nAddress && g_crc[i].m_nAddress < (pRVA + count * 8)) {
	//		nCRC = g_crc[i].m_nVal;
	//	}
	//	else if (g_crc[i].m_nVal_1)
	//	{//是跨段的CRC
	//		if (pRVA <= (g_crc[i].m_nAddress + 0xF) && (g_crc[i].m_nAddress + 0xF) < (pRVA + count * 8)) {
	//			nCRC = g_crc[i].m_nVal_1;
	//		}
	//	}
	//}
	//char* sName=NULL;
	//if (nNo >= 1)
	//{
	//	CStringA a = (char*)crc_val;
	//	CString b = CStringW(a);
	//	
	//	//CLog::WriteMsg((LPCTSTR)b);
	//

	//	if (nNo < 2000 && nNo!=0x33 && nNo != 0x14 && nNo != 0x45 && nNo != 0x47 && nNo != 0x50 && nNo != 0x4d && nNo != 0xe && nNo != 0x47)
	//	{
	//		DbgPrintf_Mine("nNo %I64X   字符%s  \r\n", nNo, a);
	//	}
	//
	//}



	
		return ;

}

void HookCRC_01()
{
	CInlineHook_x64 hook64;
	__int64 pAddress = 游戏模块_kguix64 + 0x2351D0;

	hook64.InlineHook15(pAddress, (__int64)HookCallBack_2, 15);
}


void HOOk初始化()
{


	__int64 hWowModuleBase = 游戏模块_kguix64;
		setHookCRC_01(0x2351D0);
		__int64 hWowModule = setGameModule(hWowModuleBase);

		MyTrace(L"模块地址 0x%I64X  初始化地址 0x%I64X 0x%I64X", hWowModule , hWowModuleBase ,setGameModule);

		setHookCallBackProc((__int64)_HookProc);

		MyTrace(L"_HookProc%I64X", _HookProc);
		//CLog::CreateNewFile();

		HookCRC_01();



}

class CriticalSection {
private:
	CRITICAL_SECTION m_cs;

public:
	CriticalSection() {
		InitializeCriticalSection(&m_cs);
	}

	~CriticalSection() {
		DeleteCriticalSection(&m_cs);
	}

	void Enter() {
		EnterCriticalSection(&m_cs);
	}

	void Leave() {
		LeaveCriticalSection(&m_cs);
	}

	// 可以添加其他方法根据需要
};

CriticalSection cs;

INT64 call_luatostring(char* script)
{
	cs.Enter();
	char* 结果 = NULL;
	INT64 add=0;
	INT64 qwLuastate = R_QW(R_QW(jieshiqircx + 游戏模块_kguix64) + jieshiqi);//解释器
	INT64 qcallAddr = 游戏模块_kguix64 + qLuaLoadString;
	INT64 qPcallAddr = 游戏模块_kguix64 + qLuaPCALL;
	INT64 qpopaddr = 游戏模块_kguix64 + qLUApop;
	INT64 qLuaTostringcalladdr = 游戏模块_kguix64 + qLuaTostringCall;

	INT64 pBuff = (INT64)script;
	if (*(char*)qcallAddr != 0x48)
	{
		//MyTrace(L"Lua qcalladdr地址错误");
		return 0;
	}
	if (qwLuastate>0)
	{
	
		MainUniversalCALL2(qwLuastate, (ULONG_PTR)pBuff,qcallAddr);
	
		MainUniversalCALL6(qwLuastate, 0, 4294967295, 1, qwLuastate, 0, qPcallAddr);
		add=	MainUniversalCALL4_Ret(qwLuastate,-1,0,0, qLuaTostringcalladdr);

	}
	cs.Leave();
	return add;

}

INT64 fun获取背包指针()
{
	INT64 addr = R_QW(游戏模块 + DATA_BASE_BACK-0x8);
	INT64 arg = addr + DATA_OF_OBJBA_OF1 + DATA_OF_OBJBA_OF2;



	return arg;

}

CString 弹窗信息()
{//[[[[[[[594508+kguix64.dll.0]+14F0+4ad0]+1A8]+1c8]+18]+2a8]+40]
	CString cTxt = " ";
	INT64 addr = R_QW(R_QW(游戏模块_kguix64 + 信息框) + 弹窗1 + 弹窗2) + 0x1A8;
	INT64 addr1 = R_QW(addr);
	
	if (addr1 == 0)
	{
		return cTxt;
	}
	//MyTrace(L"0x%I64X", R_QW(R_QW(R_QW(addr1 + 0x1C8) + 0x18) + 0x2A8) + 0x40);
	addr1 = R_QW(R_QW(R_QW(R_QW(addr1 + 0x1C8) + 0x18) + 0x2A8) + 0x40);
	//ReadStr(addr1, (char*)返回值.c_str(), 0xc);
	//返回值= (char*)addr1
	//const char* utf16Str = reinterpret_cast<const char*>(addr1); // 将 addr1 解释为                         以字节序列表示的 UTF-16 字符串

	cTxt = R_CString(addr1);
	return cTxt;
		//返回值 = (char*)(addr1);
		//MyTrace(L"%s", CStringA(返回值));
		//return 返回值;
}

bool 是否在过图()
{
	INT64 addr1 = 游戏模块 + 是否过图 + 0x28;
	INT64 addr = R_QW(addr1);
	MyTrace(L"是否在过图 %d", addr);
	if (addr == 0)
	{
		return 1;
	}
	return 0;
}


bool 是否掉线()
{
	CString text =" ";
	INT64 是否登陆 = call_luatostring("local framex ='0';if IsDropLinePanelOpened() then framex = '1' end return framex; ");
	text = CStringW(CStringA((char*)是否登陆));
	MyTrace(L"是否掉线 %s", CStringW(CStringA((char*)是否登陆)));
	if (text == "1")
	{
		return 1;
	}
	else
	{
		return 0;
	}
	

}






INT64 fun人物指针()
{
	INT64 addr = R_QW(游戏模块 + DATA_BASE_BACK-0x8);
	return addr;
}

_stu对象 fun人物信息列表()
{
	INT64  arg二叉结构指针 = fun人物指针();

	_stu对象 var对象数据;

	INT64  DataBase = arg二叉结构指针;
	DWORD x = R_DW(DataBase + DATA_OF_OBJECT_TREE_X);
	DWORD y = R_DW(DataBase + DATA_OF_OBJECT_TREE_Y);
	DWORD z = R_DW(DataBase + DATA_OF_OBJECT_TREE_Z);
	DWORD hp = R_DW(DataBase + DATA_OF_OBJECT_TREE_HP);
	DWORD Maxhp = R_DW(DataBase + DATA_OF_OBJECT_TREE_HP + 8);
	DWORD 等级 = R_DW(DataBase + DATA_OF_OBJECT_TREE_LV);
	DWORD 是否起码= R_DW(DataBase + DATA_OF_OBJECT_TREE_是否骑马);
	DWORD 走路 = R_DW(DataBase+ DATA_OF_OBJECT_TREE_行走状态);
	DWORD 金币 = R_DW(DataBase + DATA_OF_OBJECT_TREE_Money);
	DWORD 金币1 = R_DW(DataBase + DATA_OF_OBJECT_TREE_Money1);
	DWORD 锁 = R_DW(DataBase + OBJ_user_suo);
	DWORD LENGQUE = R_DW(DataBase + DATA_OF_OBJBA_jineng);
	DWORD zhandou = R_DW(DataBase + DATA_OF_OBJBA_战斗状态);
	DWORD 过图 = R_DW(DataBase + 0x320);
	CStringA  地图 = L" ";
	CStringA  名字 =L" ";
	地图 = (char*)(R_QW(DataBase + 0x60)+0x3C);
	名字=(char*)(DataBase + DATA_OF_OBJECT_TREE_NAME);
	//DOWRD x= R_DW(arg二叉结构指针 + DATA_OF_OBJECT_TREE_ID);

	var对象数据.m_结构地址 = DataBase;
	//var对象数据.ID = (INT64)ID;
	var对象数据.游戏坐标.x = x;
	var对象数据.游戏坐标.y = y;
	var对象数据.游戏坐标.z = z;
	var对象数据.name = CStringW(名字);
	//var对象数据.m_血量.m_Min = hp;
	//var对象数据.m_血量.m_Max = Maxhp;
	var对象数据.血量 = hp;
	var对象数据.行走状态 = 走路;
	var对象数据.骑行状态 = 是否起码;
	var对象数据.金币 = 金币;
	var对象数据.通宝 = 金币1;
	var对象数据.等级 = 等级;
	var对象数据.地图 = 地图;
	var对象数据.战斗 = zhandou;
	var对象数据.过图 = 过图;
	if (锁== 131071)
	{
		var对象数据.玲珑锁 = 1;
	}
	else
	{
		var对象数据.玲珑锁 = 0;
	}

	var对象数据.冷却 = LENGQUE;

	return var对象数据;
}

//
//INT64 fun获取背包数据首地址(int arg位置)
//{
//	INT64 var背包基质 = fun获取背包指针();
//
//	return (var背包基质 + arg位置 * DATA_OF_OBJBA_SIZE);
//}
//
//
//DWORD 获取背包数组大小(int arg位置)
//{
//	return R_QW(fun获取背包数据首地址(arg位置) + DATA_OF_OBJBA_SIZE);
//}


_stu背包 fun获取背包数据()
{
	_stu背包 var背包数据;
	var背包数据.m_数据.clear();
	var背包数据.m_行囊数量 = 6;
	INT64 var背包基质 = fun获取背包指针();
	var背包数据.背包总数 = 0;
	if (var背包基质)
	{
		for (int i = 1; i <= 5; i++)
		{
			_stu行囊 var行囊数据;

			var行囊数据.m_位置 = i;

			DWORD 背包大小 = R_DW(var背包基质 + i * DATA_OF_OBJBA_SIZE);
			var背包数据.背包总数 = var背包数据.背包总数 + 背包大小;
			if (背包大小)
			{
				var行囊数据.m_最大存放数量 = 背包大小;
				//var行囊数据.m_最大存放数量 = 背包大小;
				for (int j = 0; j < 背包大小; j++)
				{
					INT64 背包对象首地址= R_QW(var背包基质 + i * DATA_OF_OBJBA_SIZE+j*0x8+0x8);
					if (背包对象首地址 == 0)
					{
						continue;
					}


					_stu物品 var物品数据;
					DWORD 物品数量 = R_DW(背包对象首地址 + DATA_OF_OBJBA_TREE_NUM);
					DWORD 物品ID = R_DW(背包对象首地址 + DATA_OF_OBJBA_TREE_ID);
					DWORD 物品类型 = R_DW(R_QW(背包对象首地址 + 0x10)+ DATA_OF_OBJBA_TREE_type);


					CStringA  名字 = (char*)(R_QW(背包对象首地址 + 0x10) + DATA_OF_OBJBA_TREE_NAME);

					var物品数据.m数量._设置(物品数量,-1);
					var物品数据.m_ID = 物品ID;
					var物品数据.m_物品结构地址 = 背包对象首地址;
					var物品数据.物品类型 = 物品类型;

					var物品数据.name= CStringW(名字);
					var行囊数据.m_数据.push_back(var物品数据);
			
					var背包数据.背包总数 = var背包数据.背包总数 - 1;
					
					//MyTrace(L"物品数量 %d  物品对象0x%I64X  物品 ID %d",物品数量, 背包对象首地址 , 物品ID);

				

				}
				var背包数据.m_数据.push_back(var行囊数据);
			}
			else

			{
				var行囊数据.m_最大存放数量 = -1;
				var背包数据.m_行囊数量 = var背包数据.m_行囊数量 - 1;
				var背包数据.m_数据.push_back(var行囊数据);
		

			}

		}



	}

	//MyTrace(L"背包总大小 %d ", 背包总大小);
	return var背包数据;
}





INT64 fun获取第第一个参数指针()
{
	INT64 addr=R_QW(游戏模块+ DATA_BASE_BOJECT);
	INT64 arg = R_QW(addr + DATA_OF_OBJCT_0F1);
	arg = R_QW(arg + 0x28);
	arg = R_QW(arg + DATA_OF_BOJCT_OF3);


	MyTrace(L" 游戏模块  0x%I64X 第一个指针 0x%I64X", 游戏模块, arg);

	return arg;

}




INT64 fun获取第第2个参数指针(DWORD xx)
{
	INT64 addr = R_QW(游戏模块 + DATA_BASE_BOJECT);
	INT64 arg = R_QW(addr + DATA_OF_OBJCT_0F1);
	arg = R_QW(arg + xx);
	arg = R_QW(arg + DATA_OF_BOJCT_OF3);


	MyTrace(L" 游戏模块  0x%I64X 第一个指针 0x%I64X", 游戏模块, arg);

	return arg;

}



void fun递归遍历地面对象列表(INT64 arg二叉结构指针, _stu对象列表& arg对象列表, _stu对象 人物对象)
{
	if (R_BYTE(arg二叉结构指针 + DATA_OF_OBJECT_TREE_FLAG) != 0)
	{
		return;
	}
	DWORD ID = R_DW(arg二叉结构指针 + DATA_OF_OBJECT_TREE_ID);
	INT64  DataBase = R_QW(arg二叉结构指针 + DATA_OF_OBJECT_TREE_PDATA);
	DWORD x = R_DW(DataBase + DATA_OF_OBJECT_TREE_X);
	DWORD y = R_DW(DataBase + DATA_OF_OBJECT_TREE_Y);
	DWORD z = R_DW(DataBase + DATA_OF_OBJECT_TREE_Z);
	DWORD hp = R_DW(DataBase + DATA_OF_OBJECT_TREE_HP);
	DWORD Maxhp = R_DW(DataBase + DATA_OF_OBJECT_TREE_HP + 8);
	DWORD 等级 = R_DW(DataBase + DATA_OF_OBJECT_TREE_LV);


	CStringA 名字 = (char*)(DataBase + DATA_OF_OBJECT_TREE_NAME + 4);
		//  MyTrace(L" 名字%s", 名字);
	


	//DOWRD x= R_DW(arg二叉结构指针 + DATA_OF_OBJECT_TREE_ID);
	_stu对象 var对象数据;
	var对象数据.m_结构地址 = DataBase;
	var对象数据.ID = (INT64)ID;
	var对象数据.游戏坐标.x = x;
	var对象数据.游戏坐标.y = y;
	var对象数据.游戏坐标.z = z;
	var对象数据.name = CStringW(名字);
	//var对象数据.m_血量.m_Min = hp;
	//var对象数据.m_血量.m_Max = Maxhp;
	var对象数据.m_血量._设置(hp, Maxhp);



	var对象数据.等级 = 等级;
	var对象数据.距离 = 距离计算x(人物对象.游戏坐标.x, 人物对象.游戏坐标.y, var对象数据.游戏坐标.x, var对象数据.游戏坐标.y) / 100;
	arg对象列表.m_数据.push_back(var对象数据);
	INT64 Tree1 = R_QW(arg二叉结构指针 + 0x0);
	INT64 Tree2 = R_QW(arg二叉结构指针 + 0x10);


	if (Tree1)
	{
		fun递归遍历地面对象列表(Tree1, arg对象列表, 人物对象);
	}


	if (Tree2)
	{
		fun递归遍历地面对象列表(Tree2, arg对象列表, 人物对象);
	}




}





void fun递归遍历对象列表(INT64 arg二叉结构指针, _stu对象列表& arg对象列表, _stu对象 人物对象)
{
	if (R_BYTE(arg二叉结构指针 +DATA_OF_OBJECT_TREE_FLAG) != 0)
	{
		return;
	}
	DWORD ID = R_DW(arg二叉结构指针+ DATA_OF_OBJECT_TREE_ID);
	INT64  DataBase = R_QW(arg二叉结构指针 + DATA_OF_OBJECT_TREE_PDATA);
	DWORD x= R_DW(DataBase + DATA_OF_OBJECT_TREE_X);
	DWORD y = R_DW(DataBase + DATA_OF_OBJECT_TREE_Y);
	DWORD z = R_DW(DataBase + DATA_OF_OBJECT_TREE_Z);
	DWORD hp= R_DW(DataBase + DATA_OF_OBJECT_TREE_HP);
	DWORD Maxhp = R_DW(DataBase + DATA_OF_OBJECT_TREE_HP+8);
	DWORD 等级= R_DW(DataBase + DATA_OF_OBJECT_TREE_LV);
	CStringA  名字 = L" ";
	if (R_DW(DataBase + DATA_OF_OBJECT_TREE_NAME) == 1)
	{
		  名字 = (char*)(DataBase + DATA_OF_OBJECT_TREE_NAME+4);
		//  MyTrace(L" 名字%s", 名字);
	}
	else
	{
		  名字 = (char*)(DataBase + DATA_OF_OBJECT_TREE_NAME);
	}


	//DOWRD x= R_DW(arg二叉结构指针 + DATA_OF_OBJECT_TREE_ID);
	_stu对象 var对象数据;
	var对象数据.m_结构地址 = DataBase;
	var对象数据.ID = (INT64)ID;
	var对象数据.游戏坐标.x = x;
	var对象数据.游戏坐标.y = y;
	var对象数据.游戏坐标.z = z;
	var对象数据.name = CStringW(名字);
	//var对象数据.m_血量.m_Min = hp;
	//var对象数据.m_血量.m_Max = Maxhp;
	var对象数据.m_血量._设置(hp, Maxhp);



	var对象数据.等级 = 等级;
	var对象数据.距离 = 距离计算x(人物对象.游戏坐标.x, 人物对象.游戏坐标.y, var对象数据.游戏坐标.x, var对象数据.游戏坐标.y) ;
	arg对象列表.m_数据.push_back(var对象数据);
	INT64 Tree1= R_QW(arg二叉结构指针 + 0x0);
	INT64 Tree2 = R_QW(arg二叉结构指针 + 0x10);


	if (Tree1)
	{
		fun递归遍历对象列表(Tree1, arg对象列表, 人物对象);
	}
	

	if (Tree2)
	{
		fun递归遍历对象列表(Tree2, arg对象列表, 人物对象);
	}




}


_stu对象列表 fun获取对象数据()
{
	_stu对象列表 var对象数据列表;
	var对象数据列表.m_数据.clear();
	_stu对象 xx = fun人物信息列表();
	fun递归遍历对象列表(fun获取第第2个参数指针(0x8), var对象数据列表, xx);
	fun递归遍历对象列表(fun获取第第2个参数指针(0x20), var对象数据列表, xx);
	fun递归遍历对象列表(fun获取第第2个参数指针(0x38), var对象数据列表, xx);
	fun递归遍历地面对象列表(fun获取第第2个参数指针(0x50), var对象数据列表, xx);
	fun递归遍历对象列表(fun获取第第2个参数指针(0x68), var对象数据列表, xx);
	return var对象数据列表;

}

void anjianCALL(DWORD r8, DWORD r9, DWORD rdx)
{

	INT64 addr = R_QW(游戏模块_kguix64 + anjianrcx)+ anjianr8;

	INT64 call = 游戏模块_kguix64 + anjiancall;

	MainUniversalCALL6(addr,rdx,r8,r9,0, r8, call);

}