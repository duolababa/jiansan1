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
	//	//���ж��Ƿ���������ַCRC
	//	if (pRVA <= g_crc[i].m_nAddress && g_crc[i].m_nAddress < (pRVA + count * 8)) {
	//		nCRC = g_crc[i].m_nVal;
	//	}
	//	else if (g_crc[i].m_nVal_1)
	//	{//�ǿ�ε�CRC
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
	//		DbgPrintf_Mine("nNo %I64X   �ַ�%s  \r\n", nNo, a);
	//	}
	//
	//}



	
		return ;

}

void HookCRC_01()
{
	CInlineHook_x64 hook64;
	__int64 pAddress = ��Ϸģ��_kguix64 + 0x2351D0;

	hook64.InlineHook15(pAddress, (__int64)HookCallBack_2, 15);
}


void HOOk��ʼ��()
{


	__int64 hWowModuleBase = ��Ϸģ��_kguix64;
		setHookCRC_01(0x2351D0);
		__int64 hWowModule = setGameModule(hWowModuleBase);

		MyTrace(L"ģ���ַ 0x%I64X  ��ʼ����ַ 0x%I64X 0x%I64X", hWowModule , hWowModuleBase ,setGameModule);

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

	// ���������������������Ҫ
};

CriticalSection cs;

INT64 call_luatostring(char* script)
{
	cs.Enter();
	char* ��� = NULL;
	INT64 add=0;
	INT64 qwLuastate = R_QW(R_QW(jieshiqircx + ��Ϸģ��_kguix64) + jieshiqi);//������
	INT64 qcallAddr = ��Ϸģ��_kguix64 + qLuaLoadString;
	INT64 qPcallAddr = ��Ϸģ��_kguix64 + qLuaPCALL;
	INT64 qpopaddr = ��Ϸģ��_kguix64 + qLUApop;
	INT64 qLuaTostringcalladdr = ��Ϸģ��_kguix64 + qLuaTostringCall;

	INT64 pBuff = (INT64)script;
	if (*(char*)qcallAddr != 0x48)
	{
		//MyTrace(L"Lua qcalladdr��ַ����");
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

INT64 fun��ȡ����ָ��()
{
	INT64 addr = R_QW(��Ϸģ�� + DATA_BASE_BACK-0x8);
	INT64 arg = addr + DATA_OF_OBJBA_OF1 + DATA_OF_OBJBA_OF2;



	return arg;

}

CString ������Ϣ()
{//[[[[[[[594508+kguix64.dll.0]+14F0+4ad0]+1A8]+1c8]+18]+2a8]+40]
	CString cTxt = " ";
	INT64 addr = R_QW(R_QW(��Ϸģ��_kguix64 + ��Ϣ��) + ����1 + ����2) + 0x1A8;
	INT64 addr1 = R_QW(addr);
	
	if (addr1 == 0)
	{
		return cTxt;
	}
	//MyTrace(L"0x%I64X", R_QW(R_QW(R_QW(addr1 + 0x1C8) + 0x18) + 0x2A8) + 0x40);
	addr1 = R_QW(R_QW(R_QW(R_QW(addr1 + 0x1C8) + 0x18) + 0x2A8) + 0x40);
	//ReadStr(addr1, (char*)����ֵ.c_str(), 0xc);
	//����ֵ= (char*)addr1
	//const char* utf16Str = reinterpret_cast<const char*>(addr1); // �� addr1 ����Ϊ                         ���ֽ����б�ʾ�� UTF-16 �ַ���

	cTxt = R_CString(addr1);
	return cTxt;
		//����ֵ = (char*)(addr1);
		//MyTrace(L"%s", CStringA(����ֵ));
		//return ����ֵ;
}

bool �Ƿ��ڹ�ͼ()
{
	INT64 addr1 = ��Ϸģ�� + �Ƿ��ͼ + 0x28;
	INT64 addr = R_QW(addr1);
	MyTrace(L"�Ƿ��ڹ�ͼ %d", addr);
	if (addr == 0)
	{
		return 1;
	}
	return 0;
}


bool �Ƿ����()
{
	CString text =" ";
	INT64 �Ƿ��½ = call_luatostring("local framex ='0';if IsDropLinePanelOpened() then framex = '1' end return framex; ");
	text = CStringW(CStringA((char*)�Ƿ��½));
	MyTrace(L"�Ƿ���� %s", CStringW(CStringA((char*)�Ƿ��½)));
	if (text == "1")
	{
		return 1;
	}
	else
	{
		return 0;
	}
	

}






INT64 fun����ָ��()
{
	INT64 addr = R_QW(��Ϸģ�� + DATA_BASE_BACK-0x8);
	return addr;
}

_stu���� fun������Ϣ�б�()
{
	INT64  arg����ṹָ�� = fun����ָ��();

	_stu���� var��������;

	INT64  DataBase = arg����ṹָ��;
	DWORD x = R_DW(DataBase + DATA_OF_OBJECT_TREE_X);
	DWORD y = R_DW(DataBase + DATA_OF_OBJECT_TREE_Y);
	DWORD z = R_DW(DataBase + DATA_OF_OBJECT_TREE_Z);
	DWORD hp = R_DW(DataBase + DATA_OF_OBJECT_TREE_HP);
	DWORD Maxhp = R_DW(DataBase + DATA_OF_OBJECT_TREE_HP + 8);
	DWORD �ȼ� = R_DW(DataBase + DATA_OF_OBJECT_TREE_LV);
	DWORD �Ƿ�����= R_DW(DataBase + DATA_OF_OBJECT_TREE_�Ƿ�����);
	DWORD ��· = R_DW(DataBase+ DATA_OF_OBJECT_TREE_����״̬);
	DWORD ��� = R_DW(DataBase + DATA_OF_OBJECT_TREE_Money);
	DWORD ���1 = R_DW(DataBase + DATA_OF_OBJECT_TREE_Money1);
	DWORD �� = R_DW(DataBase + OBJ_user_suo);
	DWORD LENGQUE = R_DW(DataBase + DATA_OF_OBJBA_jineng);
	DWORD zhandou = R_DW(DataBase + DATA_OF_OBJBA_ս��״̬);
	DWORD ��ͼ = R_DW(DataBase + 0x320);
	CStringA  ��ͼ = L" ";
	CStringA  ���� =L" ";
	��ͼ = (char*)(R_QW(DataBase + 0x60)+0x3C);
	����=(char*)(DataBase + DATA_OF_OBJECT_TREE_NAME);
	//DOWRD x= R_DW(arg����ṹָ�� + DATA_OF_OBJECT_TREE_ID);

	var��������.m_�ṹ��ַ = DataBase;
	//var��������.ID = (INT64)ID;
	var��������.��Ϸ����.x = x;
	var��������.��Ϸ����.y = y;
	var��������.��Ϸ����.z = z;
	var��������.name = CStringW(����);
	//var��������.m_Ѫ��.m_Min = hp;
	//var��������.m_Ѫ��.m_Max = Maxhp;
	var��������.Ѫ�� = hp;
	var��������.����״̬ = ��·;
	var��������.����״̬ = �Ƿ�����;
	var��������.��� = ���;
	var��������.ͨ�� = ���1;
	var��������.�ȼ� = �ȼ�;
	var��������.��ͼ = ��ͼ;
	var��������.ս�� = zhandou;
	var��������.��ͼ = ��ͼ;
	if (��== 131071)
	{
		var��������.������ = 1;
	}
	else
	{
		var��������.������ = 0;
	}

	var��������.��ȴ = LENGQUE;

	return var��������;
}

//
//INT64 fun��ȡ���������׵�ַ(int argλ��)
//{
//	INT64 var�������� = fun��ȡ����ָ��();
//
//	return (var�������� + argλ�� * DATA_OF_OBJBA_SIZE);
//}
//
//
//DWORD ��ȡ���������С(int argλ��)
//{
//	return R_QW(fun��ȡ���������׵�ַ(argλ��) + DATA_OF_OBJBA_SIZE);
//}


_stu���� fun��ȡ��������()
{
	_stu���� var��������;
	var��������.m_����.clear();
	var��������.m_�������� = 6;
	INT64 var�������� = fun��ȡ����ָ��();
	var��������.�������� = 0;
	if (var��������)
	{
		for (int i = 1; i <= 5; i++)
		{
			_stu���� var��������;

			var��������.m_λ�� = i;

			DWORD ������С = R_DW(var�������� + i * DATA_OF_OBJBA_SIZE);
			var��������.�������� = var��������.�������� + ������С;
			if (������С)
			{
				var��������.m_��������� = ������С;
				//var��������.m_��������� = ������С;
				for (int j = 0; j < ������С; j++)
				{
					INT64 ���������׵�ַ= R_QW(var�������� + i * DATA_OF_OBJBA_SIZE+j*0x8+0x8);
					if (���������׵�ַ == 0)
					{
						continue;
					}


					_stu��Ʒ var��Ʒ����;
					DWORD ��Ʒ���� = R_DW(���������׵�ַ + DATA_OF_OBJBA_TREE_NUM);
					DWORD ��ƷID = R_DW(���������׵�ַ + DATA_OF_OBJBA_TREE_ID);
					DWORD ��Ʒ���� = R_DW(R_QW(���������׵�ַ + 0x10)+ DATA_OF_OBJBA_TREE_type);


					CStringA  ���� = (char*)(R_QW(���������׵�ַ + 0x10) + DATA_OF_OBJBA_TREE_NAME);

					var��Ʒ����.m����._����(��Ʒ����,-1);
					var��Ʒ����.m_ID = ��ƷID;
					var��Ʒ����.m_��Ʒ�ṹ��ַ = ���������׵�ַ;
					var��Ʒ����.��Ʒ���� = ��Ʒ����;

					var��Ʒ����.name= CStringW(����);
					var��������.m_����.push_back(var��Ʒ����);
			
					var��������.�������� = var��������.�������� - 1;
					
					//MyTrace(L"��Ʒ���� %d  ��Ʒ����0x%I64X  ��Ʒ ID %d",��Ʒ����, ���������׵�ַ , ��ƷID);

				

				}
				var��������.m_����.push_back(var��������);
			}
			else

			{
				var��������.m_��������� = -1;
				var��������.m_�������� = var��������.m_�������� - 1;
				var��������.m_����.push_back(var��������);
		

			}

		}



	}

	//MyTrace(L"�����ܴ�С %d ", �����ܴ�С);
	return var��������;
}





INT64 fun��ȡ�ڵ�һ������ָ��()
{
	INT64 addr=R_QW(��Ϸģ��+ DATA_BASE_BOJECT);
	INT64 arg = R_QW(addr + DATA_OF_OBJCT_0F1);
	arg = R_QW(arg + 0x28);
	arg = R_QW(arg + DATA_OF_BOJCT_OF3);


	MyTrace(L" ��Ϸģ��  0x%I64X ��һ��ָ�� 0x%I64X", ��Ϸģ��, arg);

	return arg;

}




INT64 fun��ȡ�ڵ�2������ָ��(DWORD xx)
{
	INT64 addr = R_QW(��Ϸģ�� + DATA_BASE_BOJECT);
	INT64 arg = R_QW(addr + DATA_OF_OBJCT_0F1);
	arg = R_QW(arg + xx);
	arg = R_QW(arg + DATA_OF_BOJCT_OF3);


	MyTrace(L" ��Ϸģ��  0x%I64X ��һ��ָ�� 0x%I64X", ��Ϸģ��, arg);

	return arg;

}



void fun�ݹ������������б�(INT64 arg����ṹָ��, _stu�����б�& arg�����б�, _stu���� �������)
{
	if (R_BYTE(arg����ṹָ�� + DATA_OF_OBJECT_TREE_FLAG) != 0)
	{
		return;
	}
	DWORD ID = R_DW(arg����ṹָ�� + DATA_OF_OBJECT_TREE_ID);
	INT64  DataBase = R_QW(arg����ṹָ�� + DATA_OF_OBJECT_TREE_PDATA);
	DWORD x = R_DW(DataBase + DATA_OF_OBJECT_TREE_X);
	DWORD y = R_DW(DataBase + DATA_OF_OBJECT_TREE_Y);
	DWORD z = R_DW(DataBase + DATA_OF_OBJECT_TREE_Z);
	DWORD hp = R_DW(DataBase + DATA_OF_OBJECT_TREE_HP);
	DWORD Maxhp = R_DW(DataBase + DATA_OF_OBJECT_TREE_HP + 8);
	DWORD �ȼ� = R_DW(DataBase + DATA_OF_OBJECT_TREE_LV);


	CStringA ���� = (char*)(DataBase + DATA_OF_OBJECT_TREE_NAME + 4);
		//  MyTrace(L" ����%s", ����);
	


	//DOWRD x= R_DW(arg����ṹָ�� + DATA_OF_OBJECT_TREE_ID);
	_stu���� var��������;
	var��������.m_�ṹ��ַ = DataBase;
	var��������.ID = (INT64)ID;
	var��������.��Ϸ����.x = x;
	var��������.��Ϸ����.y = y;
	var��������.��Ϸ����.z = z;
	var��������.name = CStringW(����);
	//var��������.m_Ѫ��.m_Min = hp;
	//var��������.m_Ѫ��.m_Max = Maxhp;
	var��������.m_Ѫ��._����(hp, Maxhp);



	var��������.�ȼ� = �ȼ�;
	var��������.���� = �������x(�������.��Ϸ����.x, �������.��Ϸ����.y, var��������.��Ϸ����.x, var��������.��Ϸ����.y) / 100;
	arg�����б�.m_����.push_back(var��������);
	INT64 Tree1 = R_QW(arg����ṹָ�� + 0x0);
	INT64 Tree2 = R_QW(arg����ṹָ�� + 0x10);


	if (Tree1)
	{
		fun�ݹ������������б�(Tree1, arg�����б�, �������);
	}


	if (Tree2)
	{
		fun�ݹ������������б�(Tree2, arg�����б�, �������);
	}




}





void fun�ݹ���������б�(INT64 arg����ṹָ��, _stu�����б�& arg�����б�, _stu���� �������)
{
	if (R_BYTE(arg����ṹָ�� +DATA_OF_OBJECT_TREE_FLAG) != 0)
	{
		return;
	}
	DWORD ID = R_DW(arg����ṹָ��+ DATA_OF_OBJECT_TREE_ID);
	INT64  DataBase = R_QW(arg����ṹָ�� + DATA_OF_OBJECT_TREE_PDATA);
	DWORD x= R_DW(DataBase + DATA_OF_OBJECT_TREE_X);
	DWORD y = R_DW(DataBase + DATA_OF_OBJECT_TREE_Y);
	DWORD z = R_DW(DataBase + DATA_OF_OBJECT_TREE_Z);
	DWORD hp= R_DW(DataBase + DATA_OF_OBJECT_TREE_HP);
	DWORD Maxhp = R_DW(DataBase + DATA_OF_OBJECT_TREE_HP+8);
	DWORD �ȼ�= R_DW(DataBase + DATA_OF_OBJECT_TREE_LV);
	CStringA  ���� = L" ";
	if (R_DW(DataBase + DATA_OF_OBJECT_TREE_NAME) == 1)
	{
		  ���� = (char*)(DataBase + DATA_OF_OBJECT_TREE_NAME+4);
		//  MyTrace(L" ����%s", ����);
	}
	else
	{
		  ���� = (char*)(DataBase + DATA_OF_OBJECT_TREE_NAME);
	}


	//DOWRD x= R_DW(arg����ṹָ�� + DATA_OF_OBJECT_TREE_ID);
	_stu���� var��������;
	var��������.m_�ṹ��ַ = DataBase;
	var��������.ID = (INT64)ID;
	var��������.��Ϸ����.x = x;
	var��������.��Ϸ����.y = y;
	var��������.��Ϸ����.z = z;
	var��������.name = CStringW(����);
	//var��������.m_Ѫ��.m_Min = hp;
	//var��������.m_Ѫ��.m_Max = Maxhp;
	var��������.m_Ѫ��._����(hp, Maxhp);



	var��������.�ȼ� = �ȼ�;
	var��������.���� = �������x(�������.��Ϸ����.x, �������.��Ϸ����.y, var��������.��Ϸ����.x, var��������.��Ϸ����.y) ;
	arg�����б�.m_����.push_back(var��������);
	INT64 Tree1= R_QW(arg����ṹָ�� + 0x0);
	INT64 Tree2 = R_QW(arg����ṹָ�� + 0x10);


	if (Tree1)
	{
		fun�ݹ���������б�(Tree1, arg�����б�, �������);
	}
	

	if (Tree2)
	{
		fun�ݹ���������б�(Tree2, arg�����б�, �������);
	}




}


_stu�����б� fun��ȡ��������()
{
	_stu�����б� var���������б�;
	var���������б�.m_����.clear();
	_stu���� xx = fun������Ϣ�б�();
	fun�ݹ���������б�(fun��ȡ�ڵ�2������ָ��(0x8), var���������б�, xx);
	fun�ݹ���������б�(fun��ȡ�ڵ�2������ָ��(0x20), var���������б�, xx);
	fun�ݹ���������б�(fun��ȡ�ڵ�2������ָ��(0x38), var���������б�, xx);
	fun�ݹ������������б�(fun��ȡ�ڵ�2������ָ��(0x50), var���������б�, xx);
	fun�ݹ���������б�(fun��ȡ�ڵ�2������ָ��(0x68), var���������б�, xx);
	return var���������б�;

}

void anjianCALL(DWORD r8, DWORD r9, DWORD rdx)
{

	INT64 addr = R_QW(��Ϸģ��_kguix64 + anjianrcx)+ anjianr8;

	INT64 call = ��Ϸģ��_kguix64 + anjiancall;

	MainUniversalCALL6(addr,rdx,r8,r9,0, r8, call);

}