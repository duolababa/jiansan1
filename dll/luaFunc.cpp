#pragma once

#include "luaFunc.h"
//#include <string>
//#include "pch.h"
//#include <tuple>
//#include <string>
//#include <vector>
//#include <type_traits>
//#include <functional>
using namespace std;



// ��C++��std::stringת��ΪLua���ַ���
//lua_State* C_L;
//void ��ȫ��LUA״̬��(lua_State* L)
//{
//	C_L = L;
//}
//template <typename FuncPtr, typename... Args>
//void register_function(lua_State* L, const char* name, FuncPtr func)
//{
//	lua_pushlightuserdata(L, (void*)func);
//}
//template <typename FuncPtr, typename... Args>
//int c_to_lua(lua_State* L) {
//	FuncPtr func = lua_touserdata(L, lua_upvalueindex(1)); // ȡ������ָ��
//	int x = luaL_checkinteger(L, 1); // ȡ����һ������
//	int y = luaL_checkinteger(L, 2); // ȡ���ڶ�������
//	int ret = func(x, y); // ���� C ����
//	lua_pushinteger(L, ret); // ������ֵѹ��ջ��
//	return 1; // ���ط���ֵ������
//}
//void CToLua(FuncPtr func,int ����ֵ����, Args... args)
//{
//
//	int count = sizeof...(args);
//	va_list vargs;
//	va_start(vargs, count);
//	//for(size_t i=0;i<)
//	//L = __LUA_ָ��;
//	
//}
int panic(lua_State* L)
{
	const char* message = lua_tostring(L, 1);
	//DebugPrintf("%s\n", message);
	string error_message = message;
	SendMessageToMoConter(111, error_message.c_str());
	// ���������Ϣ
	return 0;
}
lua_State* initLua()
{
	static lua_State* L = NULL;
	if (L == NULL)
	{
		L = luaL_newstate();
		luaL_openlibs(L);
		//lua_atpanic(L, panic);
	}
	return L;
}


bool ִ��lua(lua_State* L,const char * lua����)
{
	
	//const char* ���� = lua����.c_str();
	//MyTrace(L"����LUA");
	//lua_atpanic(L, [](lua_State* L) -> int {
	//	// ���� panic�����������Ϣ
	//	const char* error_message = lua_tostring(L, -1);
	//	DebugPrintf("Lua script error: %s\n", error_message);
	//	return 0;
	//	});
	//if (luaL_loadfile(L, ����) != 0) {
	//	// ����ʧ�ܣ����������Ϣ
	//	MyTrace(L"����ʧ��");
	//	const char* error_message = lua_tostring(L, -1);
	//	string errormssage = error_message;

	//	DebugPrintf("Failed to load Lua script: %s\n", error_message);
	//	lua_pop(L, 1); // �Ӷ�ջ�е���������Ϣ
	//	SendMessageToMoConter(111, errormssage.c_str());
	//	Lua���� = false; lua_close(L); return false;
	//}
	//else {
	//	// ���سɹ���ִ�д���
	//	lua_pcall(L, 0, 0, 0);
	//}
	/*__try
	{
		
		if (luaL_loadstring(L, "if print(1);\nprint(a);\nprint(2);") != LUA_OK) {
			const char* error = lua_tostring(L, -1);
			
			lua_pop(L, 1);
		}
	}
	__except (SEHHandler(GetExceptionInformation()), EXCEPTION_EXECUTE_HANDLER)
	{

	}*/
	bool a = luaL_dofile(L, lua����);
	//MyTrace(L"��� %d", a);
	if (a)
	{
		//MyTrace(L"���");
		string errormssage = lua_tostring(L, -1);

		DebugPrintf("%s\n", lua_tostring(L, -1));
		Lua���� = false;
		lua_close(L);
		return false;
	}
	return true;
}
//void ��ȫ��LUA״̬��(lua_State* L)
//{
//	C_L = L;
//}



// ��C++����ע��Ϊȫ�ֺ���
//typedef int (*CFunc)(lua_State*, void**);
//void register_cpp_function(lua_State* L, const char* name, CFunc func) {
//	lua_pushlightuserdata(L, (void*)func);
//	lua_pushcclosure(L, cpp_function_wrapper, 1);
//	lua_setglobal(L, name);
//}
//
//// ת���������õ�C++����
//int cpp_function_wrapper(lua_State* L) {
//	// ��ȡC++����ָ��
//	CFunc func = (CFunc)lua_touserdata(L, lua_upvalueindex(1));
//
//	// ��ȡ��������
//	int argc = lua_gettop(L);
//
//	// ������������
//	void** args = (void**)malloc(argc * sizeof(void*));
//
//	// ��������
//	int i;
//	for (i = 1; i <= argc; i++) {
//		switch (lua_type(L, i)) {
//		case LUA_TBOOLEAN:
//			args[i - 1] = (void*)(intptr_t)lua_toboolean(L, i);
//			break;
//		case LUA_TNUMBER:
//			args[i - 1] = (void*)(intptr_t)lua_tonumber(L, i);
//			break;
//		case LUA_TSTRING:
//			args[i - 1] = (void*)lua_tostring(L, i);
//			break;
//		default:
//			args[i - 1] = lua_touserdata(L, i);
//			break;
//		}
//	}
//
//	// ����C++����
//	//auto ptr = &func;
//	//MyCallFun::call_function(ptr, args);
//	int ret = (*func)(L, args);
//
//	// �ͷŲ�������
//	free(args);
//
//	// ���ؽ��
//	return ret;
//}

static int LUA_��ʱ(__LUA_ָ��)
{
	DWORD ndArgNum = lua_gettop(L);
	if (ndArgNum <= 0)
	{
		Sleep(100);
		lua_pushboolean(L, FALSE);
		return 1;
	}
	Sleep(lua_tointeger(L, 1));//�ȴ���Ӧ�ĺ�����
	lua_pushboolean(L, TRUE);
	return 1;//����һ������
}

int newadd(int a, int b)
{
	return a + b;
}
//void MyL_�ӷ�()
//{
//	CToLua(&newadd, MyType::������, MyType::������, MyType::������);
//}

static int MovePoint(__LUA_ָ��)
{
	float x = lua_tonumber(L, 1);
	float y = lua_tonumber(L, 2);
	float z = lua_tonumber(L, 3);

	return 0;
}

//int DPrint(CString �ı�)
//{
//	MyTrace(L"%s",�ı�);
//	return 0;
//}

static int ����ս��(__LUA_ָ��)
{
	����::�Զ�ѡ������ս��();

	return 0;
}

static int ��ת_ȡ��ͼID(__LUA_ָ��)
{
	lua_pushinteger(L, ��ͼ::ȡ��ͼID());
	return 1;
}
static int ��ת_�Զ�װ���Ƽ�װ��(__LUA_ָ��)
{
	����::�Զ�װ���Ƽ�װ��();
	return 0;
}
static int ��ת_��־���(__LUA_ָ��)
{
	const char* tmpStr = lua_tostring(L, 1);
	//DebugPrintf("��־:%s", tmpStr);
	string tempStr = tmpStr;
	CString tmp = tempStr.c_str();
	SendMessageToMoConter(112, tmp);
	return 0;
}
static int ��ת_ָ��UI�Ƿ���ʾ(__LUA_ָ��)
{
	USES_CONVERSION;
	const char* tmpStr = lua_tostring(L, 1);
	CString tmp = A2W(tmpStr);
	if (tmp != L"")
	{
		lua_pushboolean(L, UI����::ָ��UI�Ƿ���ʾ(tmp));
	}
	
	return 0;
}

static int ���ô�Ա(__LUA_ָ��)
{

	����::�������д�Ա();
	return 0;

}


static int ѡ��(__LUA_ָ��)
{
	DWORD id = lua_tointeger(L, 1);
	����::luaVoyageShipSelectShip(id);
	return 0;



}

static int �رն��ര��(__LUA_ָ��)
{
	//MyTrace(L"����");
	if (����::�Ƿ��ں�NPC�Ի�())
	{
		����::CALL_�˳�NPC();
		Sleep(2000);
	}
	DWORD size = 0;
	//MyTrace(L"ces");

	size = UI����::��������();

	if (size >= 1)
	{
		for (size_t i = 0; i < size; i++)
		{
			size = UI����::��������();
			if (size >= 1)
			{
				//MyTrace(L"��ʼִ�а���call");
				UI����::�ڴ水��(VK_ESCAPE);
				Sleep(1500);

			}


		}


	}

	return 0;
}


static int �Ƿ�����(__LUA_ָ��)
{
bool x=	UI����::�����ɱ���Ľ����Ƿ��();
lua_pushinteger(L, x);

return 1;
}

static int �Ի����(__LUA_ָ��)
{
	DWORD id = lua_tointeger(L, 1);

	����::Fun_�׶��������CALL(id);
	return 0;

}


static int ��ⴰ��(__LUA_ָ��)
{
	DWORD aa=0;
		
	aa=	UI����::��������();
	lua_pushinteger(L, aa);
	return 1;


}

static int ѡ������(__LUA_ָ��)
{

	const char* tmpStr = lua_tostring(L, 1);
	DWORD x;
	x = ���ù���::ʮ������תʮ����(tmpStr);
	����::CALL_ѡ������(x);
	Sleep(2000);
	����::CALL_�˳�����();
	return 0;

}
static int �������1(__LUA_ָ��)
{
	const char* tmpStr = lua_tostring(L, 1);
	DWORD id = lua_tointeger(L, 2);
	DWORD x;
	x = ���ù���::ʮ������תʮ����(tmpStr);

	����::CALL_������(x, id);
	return 0;


}


static int �������(__LUA_ָ��)
{
	const char* tmpStr = lua_tostring(L, 1);
	DWORD x;
	x = ���ù���::ʮ������תʮ����(tmpStr);

	����::CALL_������(x, -1);
	return 0;
}
static int �ؼ����(__LUA_ָ��)
{
	const char* tmpStr = lua_tostring(L, 1);
	INT64 x;
	x = ���ù���::ʮ������תʮ����(tmpStr);
	UI����::�ؼ����call(x);
	return 0;



}

static int ��������(__LUA_ָ��)
{
	const char* tmpStr = lua_tostring(L, 1);
	const char* tmpStr1 = lua_tostring(L, 2);
	DWORD x = 0;
	if (CStringW(tmpStr).Find(CStringW(tmpStr1)) != -1)
	{
		x = 1;

	}
	lua_pushinteger(L, x);
	return 1;

}

static int �ؼ�����(__LUA_ָ��)
{
	const char* tmpStr = lua_tostring(L, 1);
	DWORD x = 0;
	CString �����ı� = UI����::���ڷ����ı�();
	if (�����ı�.Find(CStringW(tmpStr)) != -1 )
	{
		x = 1;

	}
	lua_pushinteger(L, x);
	return 1;

}

static int ������ȴ(__LUA_ָ��)
{
	//MyTrace(L"������ȴc");
	DWORD ��λ1 = lua_tointeger(L, 1);
	DWORD ��λ= lua_tointeger(L, 2);
	vector<ShortCutInfo_>��������;
	BOOL ��ȴ = 0;

	����::get_SkillShortList(��������);
	//MyTrace(L"������ȴ1");
	for (size_t i = 0; i < ��������.size(); i++)
	{
		if (��λ== ��������[i].��λ)
		{
			��ȴ = ��������[i].�Ƿ���ȴ;
			break;
		}

	}

	if (��ȴ == 1)
	{
		lua_pushinteger(L, 0);
	}
	else
	{
		lua_pushinteger(L, 1);
	}


	return 1;
}
static int ������(__LUA_ָ��)
{
	const char* tmpStr = lua_tostring(L, 1);
	DWORD x;
	x = ���ù���::ʮ������תʮ����(tmpStr);

	����::CALL_������(x);

	return 0;
}


static int ��ͼ����(__LUA_ָ��)
{


	CString x = ��ͼ::ȡ���ͼ��();
	lua_pushstring(L, CStringA(x));

	return 1;

}



static int ������(__LUA_ָ��)
{
	ActorInfo_ a = ����::ȡ��ɫ��Ϣ();
	if (a.������ǰ�;� != 100)
	{
		����::CALL_����ֻ(����::getCurVoyageShipResId());
	}

	return 0;
}


static int �����Ƿ����(__LUA_ָ��)
{

	const char* tmpStr = lua_tostring(L, 1);
	DWORD x;
	x = ���ù���::ʮ������תʮ����(tmpStr);
	QuestInfo_ temp;
	vector<QuestInfo_>vsk;

	����::get_CurQuestList(vsk);
	DWORD �Ƿ���� = 0;

	for (size_t i = 0; i < vsk.size(); i++)
	{
		if (vsk[i].dQuestId == x && vsk[i].dQuestId>1)
		{
			�Ƿ���� = 1;

			break;
		}

		/*temp = vsk[i];
		return temp;*/


	}
	lua_pushinteger(L, �Ƿ����);


	return 1;

}


static int �����չ(__LUA_ָ��)
{
	const char* tmpStr = lua_tostring(L, 1);
	DWORD x;
	x = ���ù���::ʮ������תʮ����(tmpStr);
	QuestInfo_ temp;
	vector<QuestInfo_>vsk;
	����::get_CurQuestList(vsk);
	DWORD ����׶� = 0;
	DWORD ����ɽ� = 0;
	MyTrace(L"�жϵ�ID%I64X", x);
	for (size_t i = 0; i < vsk.size(); i++)
	{
		if (vsk[i].dQuestId == x)
		{
			����׶� = vsk[i].dStep;
			����ɽ� = vsk[i].dState;
			break;
		}
	
			/*temp = vsk[i];
			return temp;*/

	
	}
	lua_pushinteger(L, ����׶�);
	lua_pushinteger(L, ����ɽ�);

	return 2;
}
static int �����·(__LUA_ָ��)
{
	const char* tmpStr = lua_tostring(L, 1);
	CString x = L"��";
	 x=���������·(CStringW(tmpStr));


	lua_pushstring(L, CStringA(x));

	return 1;
}


static int �뿪����(__LUA_ָ��)
{

	return 0;
}
static int ���븱��(__LUA_ָ��)
{
	UI����::getMsgBoxTextList();
	return 0;


}



static int �볡(__LUA_ָ��)
{
	if (UI����::���������Ƿ��() == true)
	{
		if (UI����::���븱��())
		{
			//Sleep(2000);
			//UI����::�ڴ水��(VK_RETURN);
		}
	}
//	getMsgBoxTextList()
	return 0;


}
static int ��������(__LUA_ָ��)
{
	bool x = ����::�Ƿ��ڶ���();

	if (x == 1)
	{
		UI����::�ڴ水��(VK_ESCAPE);
		Sleep(3000);
	}

	return 0;

}

static int �����ж�(__LUA_ָ��)
{
	DWORD C = 0;
	vector<Equipinfo_>vsk;
	����::get_UpEquipList(vsk);
	for (size_t i = 0; i < vsk.size(); i++)
	{
		if (vsk[i].�;ö�.��ǰ�;ö� < 5 && vsk[i].ItemName!= L"��")
		{
			C = 1;
			break;

		}

	}

	lua_pushinteger(L, C);
	return 1;

}


static int ����������ѯ(__LUA_ָ��)
{
	const char* tmpStr = lua_tostring(L, 1);
	DWORD x;
	//sscanf(tmpStr, "%x", x);

	x = ���ù���::ʮ������תʮ����(tmpStr);

	INT64 dItemResAddr = getItemResAddrById(x);
	//MyTrace(L"dItemResAddr");
	INT64 dNameAddr = R_QW(dItemResAddr + 0x10);

	CString csName = L"��";
	if (dNameAddr)
	{
		//string sName = UnicodeToAnsi(R_CString(dNameAddr));
		//csName = GetName(dNameAddr);
		//DbgPrintf_Mine("sName %s",sName);
		//csName = CString(sName.c_str());
		csName = R_CString(dNameAddr);


	}
	DWORD ���� = ����::�ɼ�����(x);

	lua_pushinteger(L, ����);
	lua_pushinteger(L, x);
	return 2;
}


static int ����������ѯ(__LUA_ָ��)
{

	const char* tmpStr = lua_tostring(L, 1);
	DWORD x;
	//sscanf(tmpStr, "%x", x);

	x = ���ù���::ʮ������תʮ����(tmpStr);

	vector<Inventoryinfo_>vsk;
	����::get_InventoryItemList(vsk);
	DWORD ��Ʒ���� = 0;
	DWORD ��Ʒ��ID = 0;

	for (size_t i = 0; i < vsk.size(); i++)
	{
		if (vsk[i].ItemName.Find(CStringW(tmpStr)) != -1 || x == vsk[i].ItemResId)
		{
			��Ʒ���� = vsk[i].dNum;
			��Ʒ��ID = vsk[i].ItemResId;
			break;

		}


	}

	lua_pushinteger(L, ��Ʒ����);
	lua_pushinteger(L, ��Ʒ��ID);
	return 2;


}


static int ����ʹ��(__LUA_ָ��)
{
	const char* tmpStr = lua_tostring(L, 1);
	DWORD  num = std::stoi(tmpStr);
	CString �����ı� = UI����::���ڷ����ı�();
	if (�����ı�.Find(CStringW("Inventory")) != -1 || �����ı�.Find(CStringW("������Ʒ")) != -1 || �����ı�.Find(CStringW("����")) != -1)
	{

	}
	else
	{
		UI����::�ڴ水��(DWORD('I'));
	}

	vector<Inventoryinfo_>vsk;
	����::get_InventoryItemList(vsk);
	for (size_t i = 0; i < vsk.size(); i++)
	{
		if (num != 0 && num == vsk[i].dSlotIndex)
		{
			����::ʹ����Ʒ(vsk[i].dindex);
			Sleep(2000); 
			�����ı� = UI����::���ڷ����ı�();
			if (�����ı�.Find(CStringW("Register New Card")) != -1 || �����ı�.Find(CStringW("�¿�ע��")) != -1 || �����ı�.Find(CStringW("ʹ��")) != -1 || �����ı�.Find(CStringW("����¿���")) != -1)
			{
				UI����::�ڴ水��(VK_RETURN);
				Sleep(1000);

			}

		}

	}

	DWORD size = UI����::��������();

	if (size >= 1)
	{
		for (size_t i = 0; i < size; i++)
		{
			size = UI����::��������();
			if (size >= 1)
			{
				//MyTrace(L"��ʼִ�а���call");
				UI����::�ڴ水��(VK_ESCAPE);
				Sleep(1500);

			}


		}


	}

	return 0;
}
static int ����ָ����Ʒ(__LUA_ָ��)
{
	const char* tmpStr = lua_tostring(L, 1);
	DWORD x;
	//sscanf(tmpStr, "%x", x);

	x = ���ù���::ʮ������תʮ����(tmpStr);


	vector<Inventoryinfo_>vsk;
	����::get_InventoryItemList(vsk);
	for (size_t i = 0; i < vsk.size(); i++)
	{
		//if (name.Find(CStringW(�ؼ�����)) != -1 && name.GetLength() != 0)

		if (vsk[i].ItemName.Find(CStringW(tmpStr))!=-1 || x== vsk[i].ItemResId || x== vsk[i].dSlotIndex)
		{
			����::������Ʒcall(vsk[i].ItemId);
			Sleep(2000);

		}

	}

	return 0;
}




static int �������ü���(__LUA_ָ��)
{
	DWORD ����ID = lua_tointeger(L, 1);
	DWORD λ�� = lua_tointeger(L, 2);
	����::CALL_��ݼ����ܰڷ�(����ID, λ��);

	return 0;



}

static int �������ʯ(__LUA_ָ��)
{
	����ʯ::����ʯǿ��();
	return 0;

}



static int �����ж�(__LUA_ָ��)
{
	float x,y,z;
	ActorInfo_ ��ɫ��Ϣ = ����::ȡ��ɫ��Ϣ();
	x = lua_tonumber(L, 1);
	y = lua_tonumber(L, 2);
	z = lua_tonumber(L, 3);


	double dx = abs(x - ��ɫ��Ϣ.����.x);
	double dy = abs(y - ��ɫ��Ϣ.����.y);
	double dz = abs(z - ��ɫ��Ϣ.����.z);

	double xyz = sqrt(pow(dx, 2) + pow(dy, 2) + pow(dz, 2))/100;
	lua_pushnumber(L,xyz);
	MyTrace(L"�����ж� %0.3f,%0.3f,%0.3f ->Ŀ����� %0.3f", x, y, z, xyz);
	return 1;

}

static int ѡ���ɫ��ʼ��Ϸ(__LUA_ָ��)
{
	DWORD ��� = lua_tointeger(L, 1);
	��½::CALL_������Ϸ(���);

	return 0;
}


static int ��ȡְҵ(__LUA_ָ��)
{
	DWORD ְҵ = 0;

	ActorInfo_ ��ɫ��Ϣ = ����::ȡ��ɫ��Ϣ();
	ְҵ = ��ɫ��Ϣ.ְҵ;

	lua_pushinteger(L, ְҵ);
	//��ɫ��Ϣ.����ָ��
	return 1;
}



static int ��ϷС��(__LUA_ָ��)
{
	����::С��call();

	return 0;
}


static int �����ж�(__LUA_ָ��)
{
	const char* ����ID = lua_tostring(L, 1);
	DWORD x;
	//sscanf(����ID, "%x", x);

	x = ���ù���::ʮ������תʮ����(����ID);


	vector<DWORD>vsk;
	����::get_FinishQuestList(vsk);

	if (����::�����Ƿ������(x, vsk))
	{
		lua_pushinteger(L, 1);
	}
	else
	{
		lua_pushinteger(L, 0);
	}

	return 1;
}


static int ���ü��ܰ���1(__LUA_ָ��)
{
	DWORD ����ID = lua_tointeger(L, 1);
	DWORD ���ܵȼ� = lua_tointeger(L, 2);
	DWORD c = lua_tointeger(L, 3);
	DWORD d = lua_tointeger(L, 4);
	DWORD e = lua_tointeger(L, 5);
	DWORD f = lua_tointeger(L, 6);
����::CALL_���������츳(����ID, ���ܵȼ�,c,d,e);

����::CALL_��ݼ����ܰڷ�(����ID, f);
return 0;

}
//����::CALL_���������츳



static int ����װ��(__LUA_ָ��)
{

	����::�Զ�װ���Ƽ�װ��();
		return 0;
}

//void ����::�Զ�װ���Ƽ�װ��()
static int �Զ�����(__LUA_ָ��)
{
	DWORD ����׶� = lua_tointeger(L, 1);
	const char* ����ID = lua_tostring(L, 2);
	//int x;
	//sscanf(����ID, "%x", x);
	//MyTrace(L"����x %d \r\n", x);
	DWORD id1;

	id1 = ���ù���::ʮ������תʮ����(����ID);

	DWORD id = ����::��ȡ��ǰ�Ի�npc();
	//MyTrace(L"���� %d �������� %s 
	//����::getNpcTaklEndSendArg(NPCResId, ����ID, ����׶�);
	MyTrace(L"id1 %X  id %X   ����׶� %d \r\n", id1, id, ����׶�);
	if (id>=1)
	{

		����::getNpcTaklEndSendArg1(id, id1, ����׶�);

		MyTrace(L"�������\r\n");

	}


	return 0;

}






static int ������Ļ(__LUA_ָ��)
{

	����::CALL_������Ļ();

		return 0;
}



static int ȷ��ְҵ(__LUA_ָ��)
{
	const char* tmpStr = lua_tostring(L, 1);
	DWORD id = lua_tointeger(L, 2);
	DWORD x;
	
	x = ���ù���::ʮ������תʮ����(tmpStr);

	����::CALL_ѡ��ְҵ(x);

	return 0;
}

static int �Ƿ��ں���׼������(__LUA_ָ��)
{
	int ��_UI����;
	��_UI����=	UI����::�Ƿ��ں���׼������();
	if (��_UI����==1)
	{
		lua_pushinteger(L, 1);
	}
	else
	{
		lua_pushinteger(L, 0);
	}
	return 1;

}

static int �ֿ�ȡ��Ʒ����(__LUA_ָ��)
{
	const char* tmpStr = lua_tostring(L, 1);
	


	����::ȡ�����ֿ�(CStringW(tmpStr));


	return 0;

}

static int �ֿ�ȡ����(__LUA_ָ��)
{
	const char* tmpStr = lua_tostring(L, 1);
	����::ȡ�����ֿ�(CStringW(tmpStr));


	return 0;
}

static int ��ͼID(__LUA_ָ��)
{
	lua_pushinteger(L, ��ͼ::ȡ��ͼID());
	return 1;


}



static int �����Ƿ��ٻ�(__LUA_ָ��)
{
	bool x = ����::�Ƿ����ٻ�����();
	lua_pushinteger(L, x);
	return 1;
}
static int �ٻ�����(__LUA_ָ��)
{
	����::�ٻ�����();
		return 0;

}



static int �ֽ�����(__LUA_ָ��)
{
	if (!UI����::���������Ƿ���ʾ())
	{
		UI����::�ڴ水��(DWORD('I'));
		Sleep(1000);
	}
	if (!UI����::bCheckItemDisassemleWnd())
	{
		UI����::Fun_UiShowCtrl(0x25);
		Sleep(1000);
	}

	����::�Զ����call();
	Sleep(1000);
	����::����ֽ���ɫcall();
		����::CALL_ȫ���ֽ�();
	Sleep(3000);
	UI����::Fun_UiShowCtrl(0x25);
	return 0;

}
static int �򿪽���(__LUA_ָ��)
{
	DWORD ���� = lua_tointeger(L, 1);
	UI����::Fun_UiShowCtrl(����);
	return 0;
}



static int ʹ��������Ʒ(__LUA_ָ��)
{
	DWORD ���� = lua_tointeger(L,1);
	����::ʹ��������Ʒ(����);
	return 0;

}
static int ʹ����Ʒ(__LUA_ָ��)
{
	const char* ID = lua_tostring(L, 1);
	DWORD ���� = lua_tointeger(L, 2);
	DWORD addr = ���ù���::ʮ������תʮ����(ID);

	vector<Inventoryinfo_> vsk;
	����::get_InventoryItemList(vsk);
	for (size_t i = 0; i < vsk.size(); i++)
	{
		if (addr == vsk[i].ItemResId)
		{
			if (���� > 1)
			{
				for (size_t b = 0; i < ����; b++)
				{
					����::ʹ����Ʒ(vsk[i].dindex);
					//Sleep(2000);
				}
			}
			else
			{
				����::ʹ����Ʒ(vsk[i].dindex);
				//Sleep(2000);
			}


		
			break;
		}


	}
	return 0;

}


static int ʹ�ö���(__LUA_ָ��)
{
	const char* ID = lua_tostring(L, 1);
	DWORD ���� = lua_tointeger(L, 2);
	DWORD addr = ���ù���::ʮ������תʮ����(ID);

	vector<Inventoryinfo_> vsk;
	����::get_InventoryItemList(vsk);
	for (size_t i = 0; i < vsk.size(); i++)
	{
		if (addr == vsk[i].ItemResId)
		{
			if (����>1)
			{
				for (size_t b = 0; i < ����; b++)
				{
					����::ʹ����Ʒ(vsk[i].dindex);
					Sleep(2000);
				}
			}
			else
			{
				����::ʹ����Ʒ(vsk[i].dindex);
				Sleep(2000);
			}


			����::������Ʒcall(vsk[i].ItemId);
			Sleep(2000);
			break;
		}


	}
	return 0;
}


static int ����ʣ������(__LUA_ָ��)
{

	vector<Inventoryinfo_> vsk;
	����::get_InventoryItemList(vsk);
	DWORD a = 0;

	for (size_t i = 0; i < vsk.size(); i++)
	{
		if (vsk[i].ItemResId > 1)
		{
			a = a + 1;
		}
	}

	lua_pushinteger(L, 100-a);
	return 1;
}


static int ��ȡ������Ϣ(__LUA_ָ��)
{
	����_ �������� = ����::ȡ����();
	INT64 dObjAddr = 0;
	objInfo_ ��ʱ;
	dObjAddr = lua_tointeger(L, 1);
	CString temp;
	vector<CString>arr;
	��ʱ = ����::getActorInfo1(dObjAddr, ��������);
	arr.push_back(��ʱ.wName);
	temp.Format(L"%f", ��ʱ.����.x);//1
	arr.push_back(temp);
	temp.Format(L"%f", ��ʱ.����.y);//2
	arr.push_back(temp);
	temp.Format(L"%f", ��ʱ.����.z);//3
	arr.push_back(temp);

	//double Ѫ�� = 0;

	//if (��ʱ.dCurHp != 0)
	//{
	//	Ѫ�� = (double(��ʱ.dCurHp) / double(��ʱ.dMaxHp)) * 100;
	//}
	//else
	//{
	//	Ѫ�� = 0;
	//}





	temp.Format(L"%d", ��ʱ.dCurHp);
	arr.push_back(temp);
	temp.Format(L"%d", ��ʱ.dCurHp);//4
	arr.push_back(temp);//5
	temp.Format(L"%d", ��ʱ.dResId);
	arr.push_back(temp);//6
	temp.Format(L"%d", ��ʱ.dType);
	arr.push_back(temp);//7
	temp.Format(L"%d", ��ʱ.dType);
	arr.push_back(temp);//8
	temp.Format(L"%s", ��ʱ.wName);
	arr.push_back(temp);//9
	temp.Format(L"%f", ��ʱ.fDis);
	arr.push_back(temp);//10
	temp.Format(L"%f", ��ʱ.����.z);//11
	arr.push_back(temp);
	lua_newtable(L);
	//lua_pushnumber(L, ��ɫ��Ϣ.��ǰѪ)
	lua_pushnumber(L, -1);
	lua_rawseti(L, -2, 0);
	for (size_t i = 0; i < arr.size(); i++)
	{
		lua_pushstring(L, CStringA(arr[i]));
		lua_rawseti(L, -2, i);
	}
	return 1;
}


static int ��ȡ������Ϣ(__LUA_ָ��)
{
	CString aa = "0";
	ActorInfo_ ��ɫ��Ϣ = ����::ȡ��ɫ��Ϣ();
	vector<CString>arr;
	CString temp;


	arr.push_back(��ɫ��Ϣ.����);
	temp.Format(L"%f", ��ɫ��Ϣ.����.x);//1
	arr.push_back(temp);
	temp.Format(L"%f", ��ɫ��Ϣ.����.y);//2
	arr.push_back(temp);
	temp.Format(L"%f", ��ɫ��Ϣ.����.z);//3
	arr.push_back(temp);

	/*if (��ʱ��ɫ��Ϣ.��������;� != 0)
	{
		��ʱ��ɫ��Ϣ.������ǰ�;� = floor((double)������ǰ�;� / (double)��ʱ��ɫ��Ϣ.��������;� * 100);
	}
	else
	{
		��ʱ��ɫ��Ϣ.������ǰ�;� = 0;
	}*/
	double Ѫ�� = 0;

	if (��ɫ��Ϣ.���Ѫ != 0)
	{
		 Ѫ�� = (double(��ɫ��Ϣ.��ǰѪ) / double(��ɫ��Ϣ.���Ѫ)) * 100;
	}
	else
	{
		 Ѫ�� = 0;
	}

	temp.Format(L"%f", Ѫ��);
	arr.push_back(temp);//4

	double ���� = (double(��ɫ��Ϣ.��ǰ��) / double(��ɫ��Ϣ.�����)) * 100;
	temp.Format(L"%f", ����);
	arr.push_back(temp);//5
	arr.push_back(��ɫ��Ϣ.����);//6
	temp.Format(L"%d", ��ɫ��Ϣ.�ȼ�);
	arr.push_back(temp);//7

	temp.Format(L"%d", ��ɫ��Ϣ.��ǰ����);
	arr.push_back(temp);//8
	temp.Format(L"%d", ��ɫ��Ϣ.����״̬);
	arr.push_back(temp);//9
	temp.Format(L"%d", ��ɫ��Ϣ.����״̬);
	arr.push_back(temp);//10
	//temp.Format(L"%d", ��ɫ��Ϣ.����״̬);
	arr.push_back(aa);//11
	temp.Format(L"%d", ��ɫ��Ϣ.����״̬);
	arr.push_back(temp);//12
	


	double ���� = ��ɫ��Ϣ.������ǰ�;�;
	temp.Format(L"%f", ����);
	arr.push_back(temp);//13
	temp.Format(L"%d", ��ɫ��Ϣ.װ������);
	arr.push_back(temp);//14
	temp.Format(L"%d", ��ɫ��Ϣ.��ǰѪ);
	arr.push_back(temp);//15
	temp.Format(L"%I64X", ��ɫ��Ϣ.����ָ��);
	arr.push_back(temp);//16
	temp.Format(L"%d", ��ɫ��Ϣ.ŭ��ֵ);
	arr.push_back(temp);//17
	lua_newtable(L);
	//lua_pushnumber(L, ��ɫ��Ϣ.��ǰѪ)
	lua_pushnumber(L, -1);
	lua_rawseti(L,-2,0);
	for (size_t i = 0; i < arr.size(); i++)
	{
		lua_pushstring(L, CStringA(arr[i]));
		lua_rawseti(L, -2, i);
	}
	/*lua_newtable(L);
	lua_pushstring(L, "����");
	lua_pushstring(L, CStringA(��ɫ��Ϣ.����));
	lua_settable(L, -3);
	lua_pushstring(L, "�ȼ�");
	lua_pushinteger(L, ��ɫ��Ϣ.�ȼ�);
	lua_settable(L, -3);*/


//	DebugPrintf("%s\n", CStringA(��ɫ��Ϣ.����));
////	��ɫ��Ϣ.��ǰѪ
//	//string str = to_string(��ɫ��Ϣ.��ǰѪ);
//	//const char* char_str = str.c_str();
//	lua_pushnumber(L, ��ɫ��Ϣ.��ǰѪ);
	return 1;
}
// ActorInfo_ ����::ȡ��ɫ��Ϣ()

static int ׼������(__LUA_ָ��)
{
	UI����::׼������();
	return 0;


}
static int �Ƿ��NPC(__LUA_ָ��)
{
	bool x = ����::�Ƿ��ں�NPC�Ի�();


	lua_pushinteger(L, x);

	return 1;

}

static int �����ж�(__LUA_ָ��)
{
	//if (���Կ���==1)
	//{
	//	lua_Exit
	//	luaL_error(L,"ֹͣ����");
	//	���Կ��� = 0;

	//}
	lua_pushinteger(L, ���Կ���);

	return 1;


}

static int ��������(__LUA_ָ��)
{
	DWORD ����� = lua_tointeger(L, 1);
	CString ���ʽ;
	if (����� == 1)
	{
		���ʽ = L"��������";
		UI����::����(���ʽ);
	}
	else

	{
		���ʽ = L"�ݵ㸴��";
		UI����::����(���ʽ);
	}

	return 0;


}

static int �ɼ�����(__LUA_ָ��)
{
	const char* �ؼ����� = lua_tostring(L, 1);
	DWORD addr=����::�ɼ�����(���ù���::ʮ������תʮ����(�ؼ�����));
	lua_pushinteger(L, addr);
	return 1;

}

static int �����ѯ(__LUA_ָ��)
{
	const char* �ؼ����� = lua_tostring(L, 1);

	//MyTrace(L"�ؼ����� %s", CStringW(�ؼ�����));
	INT64 x;

	x=���ù���::hex_to_decimal(�ؼ�����);

	//MyTrace(L"�ؼ����� %I64d", x);
	//a = �ؼ�����;
	//stoi(a,0,16);
	//MyTrace(L"�ؼ����� %s", a);
	//x=temp.Format(L"%I64X", �ؼ�����);




	CString	name = UI����::UI����1(x);
	MyTrace(L"�ؼ����� %s", name);
	lua_pushstring(L, CStringA(name));

	return 1;
}


static int ������1(__LUA_ָ��)
{
	const char* �ؼ����� = lua_tostring(L,1);
	const char* �ؼ����� = lua_tostring(L, 2);
	INT64 x;
	x = ���ù���::hex_to_decimal(�ؼ�����);
	CString	name = UI����::UI����1(x);

	MyTrace(L"�ؼ����� %s", name);
	if (name.Find(CStringW(�ؼ�����))!=-1 && name.GetLength()!=0)
	{ 
		MyTrace(L"��ʼ���");
		UI����::�ؼ����call(x);
	}

	return 0;
}


static int ��ȡ�������(__LUA_ָ��)
{
	float x = lua_tonumber(L, 1);
	float y = lua_tonumber(L, 2);

	INT64 addr = ����::����ȡ����call(x, y);
	//CString(���ù���::ʮ����תʮ������(addr).c_str())
//	MyTrace(L"addr,0x%I64X", addr);
		lua_pushstring(L, ���ù���::ʮ����תʮ������(addr).c_str());

	return 1;

}



static int �����Ƿ���(__LUA_ָ��)
{
	DWORD ���͵�ID = lua_tointeger(L, 1);


	bool id = ��ͼ::���͵��Ƿ񼤻�(���͵�ID);
	if (id==1)
	{
		lua_pushinteger(L, 1);
	}
	else
	{
		lua_pushinteger(L, 0);
	}

	return 1;

}


static int ��������(__LUA_ָ��)
{
	const char* tmpStr = lua_tostring(L, 1);
	DWORD x;
	x = ���ù���::ʮ������תʮ����(tmpStr);
	����::����call����(x);
	return 0;
}
static int ���ESC(__LUA_ָ��)
{
	INT64 rcx = 0;
	bool �Ƿ�� = UI����::Ѱ�Ҵ򿪴���("root1.arkui.windowCanvas.exitMenuWindow", rcx);
	if (rcx >= 1)
	{
		DWORD dResId = R_DW(rcx + 0xB8);
		if (dResId == 1)
		{
			lua_pushinteger(L, 1);
		}
		else

		{
			lua_pushinteger(L, 0);
		}
	}
	else
	{
		lua_pushinteger(L, 0);
	}
	return 1;


}
static int ��������(__LUA_ָ��)
{
	��Ϸģ�� = (UINT64)GetModuleHandleA("LOSTARK.exe");
	��Ϸģ��_EFEngine = (UINT64)GetModuleHandleA("EFEngine.dll");
	return 0;

}

static int Ѱ·��ͼ(__LUA_ָ��)
{
	DWORD ID=����::��ȡ��ǰ����ID();
	lua_pushinteger(L, ID);
	return 1;

}



static int ����(__LUA_ָ��)
{
	ActorInfo_ ��ɫ��Ϣ = ����::ȡ��ɫ��Ϣ();
	float x = lua_tonumber(L, 1);
	float y = lua_tonumber(L, 2);
	float z = lua_tonumber(L, 3);
	DWORD ���� = lua_tointeger(L, 4);
	DWORD ���� = lua_tointeger(L, 5);
	const char* ָ��ID = lua_tostring(L, 6);
	����_ ָ������;
	ָ������.x = x;
	ָ������.y = y;
	ָ������.z = z;

	DWORD obj���� = 999999;
	INT64 ������� = 0;

	vector<objInfo_>vsk;
	����::����ȫ����������2(vsk, ָ������);

	CArray<CString, CString>�ָ�;
	CArray<CString, CString>�ָ�1;
	for (size_t i = 0; i < vsk.size(); i++)
	{
		if (vsk[i].dType == 2)
		{
			if (vsk[i].�Ƿ���Թ��� != 0)
			{
				continue;
			}
			if (vsk[i].dCurHp >= 1)
			{

			}
			else
			{
				continue;
			}

		}

		if (vsk[i].dType == ����)
		{
		

				if (��ɫ��Ϣ.����ָ�� == vsk[i].objBase)
				{
					continue;
				}
			

				if (vsk[i].fDis < ����)
				{
				
					if (ָ��ID != nullptr)
					{
						// �ǿղ���
						if (strchr(ָ��ID, '|') != nullptr)
						{
							�ı��ָ�(CStringW(ָ��ID), '|', &�ָ�);
							DWORD ���� = 0;
							if (�ָ�.GetCount() != 0)
							{
								for (size_t C = 0; C < �ָ�.GetCount(); C++)
								{
									x = ���ù���::ʮ������תʮ����(CStringA(�ָ�[C]));
									if (vsk[i].dResId == x)
									{
										���� = 1;
										break;
									}

								}

							}

							if (���� = 0)
							{
								continue;
							}

						}
						else
						{
							DWORD ���� = 0;
							x = ���ù���::ʮ������תʮ����(ָ��ID);
							if (vsk[i].dResId == x)
							{
							
							}
							else

							{
								continue;
							}


						}


					}
				



					if (vsk[i].fDis < obj����)
					{
						obj���� = vsk[i].fDis;
						������� = vsk[i].objBase;

					}



				}
			
		}
	}


	lua_pushinteger(L, �������);

	return 1;
}

static int ����(__LUA_ָ��)
{
	float x = lua_tonumber(L, 1);
	float y = lua_tonumber(L, 2);
	float z = lua_tonumber(L, 3);
	����_ ָ������;
	ָ������.x = x;
	ָ������.y = y;
	ָ������.z = z;
	����::�������();
	����::д�������굽���(ָ������);

	return 0;
}
static int ����ID(__LUA_ָ��)
{
	DWORD ID = 0;
	ID=����::�������();
	lua_pushinteger(L, ID);
	return 1;
}

static int ����(__LUA_ָ��)
{
	DWORD ����ID = lua_tointeger(L, 1);
	DWORD ����ID1 = lua_tointeger(L, 2);
	��ͼ::����(����ID);

	return 0;
}
static int �����(__LUA_ָ��)
{
	DWORD ID = lua_tointeger(L, 1);
	if (ID == 1)
	{
		UI����::��������();
	}
	else
	{
		UI����::�������();

	}
	return 0;
}
static int �ȴ�(__LUA_ָ��)
{
	DWORD dd = lua_tointeger(L, 1);
	Sleep(dd);
	return 0;

}



static int �رնԻ�(__LUA_ָ��)
{
	if (����::�Ƿ��ں�NPC�Ի�())
	{
		����::CALL_�˳�NPC();
		Sleep(2000);
	}
	return 0;
}


static int ����1(__LUA_ָ��)
{
	const char* a = lua_tostring(L, 1);
	DWORD dd = lua_tointeger(L, 2);
	CString tmpStr = CStringA(a);


	if (tmpStr == L"Q")
	{
		UI����::�ڴ水��1(g_Q, dd);
		return 0;
	}


	if (tmpStr == L"F2")
	{

		UI����::�ڴ水��(g_F2, dd);
		return 0;
	}
	if (tmpStr == L"M")
	{

		UI����::�ڴ水��1(g_M, dd);
		return 0;
	}
	if (tmpStr == L"F6")
	{

		UI����::�ڴ水��(g_F6, dd);
		return 0;
	}
	if (tmpStr == L"�ո�")
	{

		UI����::�ڴ水��(g_�ո�, dd);
		return 0;
	}
	if (tmpStr == L"N")
	{

		UI����::�ڴ水��1(g_N, dd);
		return 0;
	}
	if (tmpStr == L"C")
	{

		UI����::�ڴ水��1(g_C, dd);
		return 0;
	}
	if (tmpStr == L"I")
	{

		UI����::�ڴ水��1(g_I, dd);
		return 0;
	}
	if (tmpStr == L"G")
	{

		UI����::�ڴ水��1(g_G, dd);
		return 0;
	}
	if (tmpStr == L"W")
	{

		UI����::�ڴ水��1(g_W, dd);
		return 0;
	}
	if (tmpStr == L"E")
	{

		UI����::�ڴ水��1(g_E, dd);
		return 0;
	}
	if (tmpStr == L"R")
	{

		UI����::�ڴ水��1(g_R, dd);
		return 0;
	}
	if (tmpStr == L"Z")
	{

		UI����::�ڴ水��1(g_Z, dd);
		return 0;
	}
	if (tmpStr == L"B")
	{

		UI����::�ڴ水��1(g_B, dd);
		return 0;
	}
	if (tmpStr == L"V")
	{

		UI����::�ڴ水��1(g_V, dd);
		return 0;
	}

	if (tmpStr == L"A")
	{

		UI����::�ڴ水��1(g_A, dd);
		return 0;
	}


	if (tmpStr == L"S")
	{

		UI����::�ڴ水��1(g_S, dd);
		return 0;
	}
	if (tmpStr == L"D")
	{

		UI����::�ڴ水��1(g_D, dd);
		return 0;
	}
	if (tmpStr == L"F")
	{

		UI����::�ڴ水��1(g_F, dd);
		return 0;
	}
	if (tmpStr == L"1")
	{

		UI����::�ڴ水��1(g_1, dd);
		return 0;
	}

	if (tmpStr == L"2")
	{

		UI����::�ڴ水��1(g_2, dd);
		return 0;
	}
	if (tmpStr == L"3")
	{

		UI����::�ڴ水��1(g_3, dd);
		return 0;
	}


	if (tmpStr == L"4")
	{

		UI����::�ڴ水��1(g_4, dd);
		return 0;
	}


	if (tmpStr == L"5")
	{

		UI����::�ڴ水��1(g_5, dd);
		return 0;
	}


	if (tmpStr == L"6")
	{

		UI����::�ڴ水��1(g_6, dd);
		return 0;
	}


	if (tmpStr == L"7")
	{

		UI����::�ڴ水��1(g_7, dd);
		return 0;
	}



	if (tmpStr == L"8")
	{

		UI����::�ڴ水��1(g_8, dd);
		return 0;
	}


	if (tmpStr == L"9")
	{

		UI����::�ڴ水��1(g_9, dd);
		return 0;
	}

	if (tmpStr == L"F1")
	{

		UI����::�ڴ水��1(g_F1, dd);
		return 0;
	}

	if (tmpStr == L"F3")
	{

		UI����::�ڴ水��1(g_F3, dd);
		return 0;
	}
	if (tmpStr == L"F4")
	{

		UI����::�ڴ水��1(g_F4, dd);
		return 0;
	}
	if (tmpStr == L"F5")
	{

		UI����::�ڴ水��1(g_F5, dd);
		return 0;
	}


	if (tmpStr == L"F6")
	{

		UI����::�ڴ水��1(g_F6, dd);
		return 0;
	}
	if (tmpStr == L"Y")
	{

		UI����::�ڴ水��1(g_Y, dd);
		return 0;
	}
	if (tmpStr == L"X")
	{
		UI����::�ڴ水��1(g_X, dd);
		return 0;
	}
	if (tmpStr == L"ESC")
	{

		UI����::�ڴ水��(g_ESC, dd);
		return 0;
	}
	if (tmpStr == L"ENTER")
	{
		UI����::�ڴ水��(g_ENTER, dd);
		return 0;
	}



	return 0;
}


static int �°���(__LUA_ָ��)
{
	const char* a = lua_tostring(L, 1);

	CString tmpStr = CStringA(a);

	if (tmpStr == L"Q")
	{
		UI����::�ڴ水��1(g_Q);
		return 0;
	}


	if (tmpStr == L"F2")
	{

		UI����::�ڴ水��1(g_F2);
		return 0;
	}
	if (tmpStr == L"M")
	{

		UI����::�ڴ水��1(g_M);
		return 0;
	}
	if (tmpStr == L"F6")
	{

		UI����::�ڴ水��1(g_F6);
		return 0;
	}
	if (tmpStr == L"�ո�")
	{

		UI����::�ڴ水��1(g_�ո�);
		return 0;
	}
	if (tmpStr == L"N")
	{

		UI����::�ڴ水��1(g_N);
		return 0;
	}
	if (tmpStr == L"C")
	{

		UI����::�ڴ水��1(g_C);
		return 0;
	}
	if (tmpStr == L"I")
	{

		UI����::�ڴ水��1(g_I);
		return 0;
	}
	if (tmpStr == L"G")
	{

		UI����::�ڴ水��1(g_G);
		return 0;
	}
	if (tmpStr == L"W")
	{

		UI����::�ڴ水��1(g_W);
		return 0;
	}
	if (tmpStr == L"E")
	{

		UI����::�ڴ水��1(g_E);
		return 0;
	}
	if (tmpStr == L"R")
	{

		UI����::�ڴ水��1(g_R);
		return 0;
	}
	if (tmpStr == L"Z")
	{

		UI����::�ڴ水��1(g_Z);
		return 0;
	}
	if (tmpStr == L"B")
	{

		UI����::�ڴ水��1(g_B);
		return 0;
	}
	if (tmpStr == L"V")
	{

		UI����::�ڴ水��1(g_V);
		return 0;
	}

	if (tmpStr == L"A")
	{

		UI����::�ڴ水��1(g_A);
		return 0;
	}


	if (tmpStr == L"S")
	{

		UI����::�ڴ水��1(g_S);
		return 0;
	}
	if (tmpStr == L"D")
	{

		UI����::�ڴ水��1(g_D);
		return 0;
	}
	if (tmpStr == L"F")
	{

		UI����::�ڴ水��1(g_F);
		return 0;
	}
	if (tmpStr == L"1")
	{

		UI����::�ڴ水��1(g_1);
		return 0;
	}

	if (tmpStr == L"2")
	{

		UI����::�ڴ水��1(g_2);
		return 0;
	}
	if (tmpStr == L"3")
	{

		UI����::�ڴ水��1(g_3);
		return 0;
	}


	if (tmpStr == L"4")
	{

		UI����::�ڴ水��1(g_4);
		return 0;
	}


	if (tmpStr == L"5")
	{

		UI����::�ڴ水��1(g_5);
		return 0;
	}


	if (tmpStr == L"6")
	{

		UI����::�ڴ水��1(g_6);
		return 0;
	}


	if (tmpStr == L"7")
	{

		UI����::�ڴ水��1(g_7);
		return 0;
	}



	if (tmpStr == L"8")
	{

		UI����::�ڴ水��1(g_8);
		return 0;
	}


	if (tmpStr == L"9")
	{

		UI����::�ڴ水��1(g_9);
		return 0;
	}

	if (tmpStr == L"F1")
	{

		UI����::�ڴ水��1(g_F1);
		return 0;
	}

	if (tmpStr == L"F3")
	{

		UI����::�ڴ水��1(g_F3);
		return 0;
	}
	if (tmpStr == L"F4")
	{

		UI����::�ڴ水��1(g_F4);
		return 0;
	}
	if (tmpStr == L"F5")
	{

		UI����::�ڴ水��1(g_F5);
		return 0;
	}


	if (tmpStr == L"F6")
	{

		UI����::�ڴ水��1(g_F6);
		return 0;
	}
	if (tmpStr == L"Y")
	{

		UI����::�ڴ水��1(g_Y);
		return 0;
	}
	if (tmpStr == L"X")
	{
		UI����::�ڴ水��1(g_X);
		return 0;
	}
	if (tmpStr == L"ESC")
	{

		UI����::�ڴ水��1(g_ESC);
		return 0;
	}
	if (tmpStr == L"ENTER")
	{
		UI����::�ڴ水��1(g_ENTER);
		return 0;
	}


	return 0;
}


static int ����(__LUA_ָ��)
{
//	DWORD ID = lua_tointeger(L, 1);
	const char* tmpStr = lua_tostring(L, 1);
	DWORD x;
	//sscanf(tmpStr, "%x", x);

	x = ���ù���::ʮ������תʮ����(tmpStr);
	����::CALL_���罻����(x);
	return 0;
}


static int ����(__LUA_ָ��)
{
	DWORD ID = lua_tointeger(L, 1);
	����::CALL_��������(ID);

	return 0;
}



static int �����NPC(__LUA_ָ��)
{
	ActorInfo_ ��ɫ��Ϣ = ����::ȡ��ɫ��Ϣ();
	DWORD ���� = 0;
	vector<objInfo_>vsk;
	 ���� = lua_tointeger(L, 1);
	 DWORD NPCID = 0;

	����::����ȫ����������2(vsk, ��ɫ��Ϣ.����);
	for (size_t i = 0; i < vsk.size(); i++)
	{
		if (vsk[i].fDis < ����)
		{
			if (vsk[i].dType==3)
			{

				����::CALL_���ָ��NPC_ByResId(vsk[i].dResId);
				Sleep(1500);
				break;
			}

		}

	}
	return 0;
}



static int ��Ʒ��Ϣ(__LUA_ָ��)
{
	const char* tmpStr = lua_tostring(L, 1);
	DWORD x;
	//sscanf(tmpStr, "%x", x);

	x = ���ù���::ʮ������תʮ����(tmpStr);

	vector<Inventoryinfo_>vsk;
	����::get_InventoryItemList(vsk);
	DWORD ��Ʒ���� = 0;
	DWORD ��Ʒ��ID = 0;

	for (size_t i = 0; i < vsk.size(); i++)
	{
		if (vsk[i].ItemName.Find(CStringW(tmpStr)) != -1 || x == vsk[i].ItemResId)
		{
			��Ʒ���� = vsk[i].dNum;
		
			break;

		}


	}

	lua_pushinteger(L, ��Ʒ����);

	return 1;

}


static int ����(__LUA_ָ��)
{
	DWORD ID = 0;
	ID = ����::�������();
	ActorInfo_ a = ����::ȡ��ɫ��Ϣ();
	if (a.����״̬ == 0 && ID>1)
	{

		����::CALL_ʹ������(ID);
		Sleep(2000);
	}



	return 0;
}



static int �ɷ񵽴�(__LUA_ָ��)
{
	float x = lua_tonumber(L, 1);
	float y = lua_tonumber(L, 2);
	float z = lua_tonumber(L, 3);
	bool c = ��ͼ::ָ���ص��Ƿ�ɵ���_p(x, y, z);

	lua_pushinteger(L, c);
	return 1;
}
static int Ѱ·1(__LUA_ָ��)
{
	float x = lua_tonumber(L, 1);
	float y = lua_tonumber(L, 2);
	float z = lua_tonumber(L, 3);
	DWORD D = lua_tointeger(L, 4);

	��ͼ::Ѱ·(x, y, z, D);
	return 0;
}




static int Ѱ·_lua(__LUA_ָ��) 
{
	float x = lua_tonumber(L, 1);
	float y = lua_tonumber(L, 2);
	float z = lua_tonumber(L, 3);



	��ͼ::����ͼѰ·(x,y,z,0);
	
	return 0;

}

static int ��קҩ��(__LUA_ָ��)
{
	DWORD x1 = lua_tointeger(L, 1);
	DWORD x2 = lua_tointeger(L, 2);
	DWORD x3 = lua_tointeger(L, 3);
	DWORD x4 = lua_tointeger(L, 4);
	����::ҩƷ��קcall(x1, x2, x3, x4);

	return 0;
}


static int �Ƿ�ѡ���ɫ����(__LUA_ָ��)
{
	//characterselect.fla_desc
	if(��½::�Ƿ���׼������()==1)
	{
		lua_pushinteger(L, 1);
	}
	else
	{
		lua_pushinteger(L, 0);
	}
	return 1;

}

static int ��ȡ�ۿ�ID(__LUA_ָ��)
{
	DWORD ��½ID = ��ͼ::ȡ��ǰ��½ID();
	lua_pushinteger(L, ��½ID);

	return 1;

}

static int ��ԭ����(__LUA_ָ��)
{
	CString �����ı� = UI����::���ڷ����ı�();
	CString �����ı�1 = "";

	if (�����ı�.Find(L"Combat Skills") == -1)
	{
		UI����::�ڴ水��(DWORD('K'));
		Sleep(3000);
	}

	INT64 addr =����::����ȡ����call(3460, 11640);
	if (addr>1)
	{
		MyTrace(L"%I64X", addr);
		�����ı�1=UI����::UI����(addr);
		if (�����ı�1.Find(L"init_btn") != -1)
		{
			UI����::�ؼ����call(addr);
			Sleep(2000);

		}
		
	}
	
	if (UI����::���ڷ����ı�().Find(L"����")!=-1 || UI����::���ڷ����ı�().Find(L"Restore preset defaults")!=-1)
	{
		UI����::�ڴ水��(VK_RETURN);
		Sleep(2000);
	}


	return 0;


}

static int �Ƿ񶯻�����(__LUA_ָ��)
{
	bool  x = ����::�Ƿ��ڼ���ҳ��();

	if (x != 0)
	{
		lua_pushinteger(L, 1);
	}
	else
	{
		lua_pushinteger(L, 0);
	}
	return 1;

}
static int ά��(__LUA_ָ��)
{
	
	����::ά��װ��(1);
	return 0;
}
static int ʣ����Ϣ(__LUA_ָ��)
{
	DWORD x = ����::ʣ����Ϣ��ѯ();
	lua_pushinteger(L, x);
	return 1;


}

static int �����ж�(__LUA_ָ��)
{
	DWORD x1 = lua_tointeger(L, 1);

	bool x = ����::ָ��λ��������Ƿ���װ��(x1);//0 �ɼ����� 1 ��ľ���� 2 �ɿ󹤾� 3 ���Թ��� 4 ���㹤�� 5 ���Ź���
		if (x != 0)
		{
			lua_pushinteger(L, 1);
		}
		else
		{
			lua_pushinteger(L, 0);
		}
	return 1;
}


static int �Ƿ񶯻�����1(__LUA_ָ��)
{
	bool x = ����::�Ƿ��ڼ���ҳ��2();
		if (x != 0)
		{
			lua_pushinteger(L, 1);
		}
		else
		{
			lua_pushinteger(L, 0);
		}
		return 1;
}
static int ���򹤾�(__LUA_ָ��)
{
	DWORD x1 = lua_tointeger(L, 1);
	DWORD x2 = lua_tointeger(L, 2);
	DWORD x3 = lua_tointeger(L, 3);

	NPC�̵�::Fun_ShopBuyAddItem(x1, x3);
	Sleep(1000);
	NPC�̵�::Fub_ShopBuyItemClick();
	return 0;

}


static int �Ƿ񺽺�����(__LUA_ָ��)
{
	bool data = ����::Yesornonauticalpicture();

	lua_pushinteger(L, data);

	return 1;
}
static int �������(__LUA_ָ��)
{
	INT64 x = ����::getMoneyNumByType(2);

	lua_pushinteger(L, x);

	return 1;
}



static int �����ж�(__LUA_ָ��)
{
	int a = ����::getquickSlotFrameType();
		lua_pushinteger(L, a);

	return 1;
}

static int ����(__LUA_ָ��)
{
	����::����();

	return 0;

}

static int ʰȡ(__LUA_ָ��)
{
	DWORD ID = lua_tointeger(L, 1);
	����::ʰȡ(ID);

	return 0;
}



static int ��������(__LUA_ָ��)
{
	DWORD ID = lua_tointeger(L, 1);
	DWORD a = ����::ָ��������Ʒ����(ID);
	lua_pushinteger(L, a);
	return 1;
}

static int ������Ϣ(__LUA_ָ��)
{
	DWORD ID = lua_tointeger(L, 1);

	vector<SkillInfo_>vsk;
	����::get_SkillList(vsk);
	//MyTrace(L"�Զ���������2");
	SkillInfo_ SKILL;
	SKILL=����::ȡ��ָ��������Ϣ(ID, vsk);
	lua_pushinteger(L, SKILL.dSkillLev);
	lua_pushinteger(L, SKILL.�츳1);
	lua_pushinteger(L, SKILL.�츳2);
	lua_pushinteger(L, SKILL.�츳3);

	return 4;
}

static int ʣ�༼�ܵ�(__LUA_ָ��)
{
	DWORD x = ����::getRoleCurSkillPoints();
	lua_pushinteger(L, x);
	return 1;
}


static int ��ǰ����(__LUA_ָ��)
{
	DWORD ID = lua_tointeger(L, 1);
	DWORD add = ����::SKLLADDR(ID);
	lua_pushinteger(L, add);
	return 1;


}


static int ��Ϣ��ȡ(__LUA_ָ��)
{
	DWORD ID = lua_tointeger(L, 1);
	INT64 x= ����::getMoneyNumByType(ID);

	lua_pushinteger(L, x);
	return 1;
}


static int �һ��ƽ�(__LUA_ָ��)
{
	DWORD ID = lua_tointeger(L, 1);
	DWORD ID1 = lua_tointeger(L, 2);
	NPC�̵�::Fun_BarterShopExchange(ID, ID1);
	return 0;


}


static int �����̵�(__LUA_ָ��)
{
	vector<Inventoryinfo_>vsk;
	NPC�̵�::get_ShopItemList(vsk);
	return 0;
}


static int ��ȡ�ʼ�(__LUA_ָ��)
{
	ǩ���ʼ�::�ʼ���ȡ();

	return 0;

}
static int ��������1(__LUA_ָ��)
{
	DWORD ���� = lua_tointeger(L, 1);
	DWORD add = 0;

	add = ����::��Χ��������1(����);
	lua_pushinteger(L, add);
	return 1;


}

static int ��������������(__LUA_ָ��)
{
	DWORD x = ����::��������������();
	lua_pushinteger(L, x);
	return 1;
}




static int ��������(__LUA_ָ��)
{
	DWORD ���� = lua_tointeger(L, 1);
	DWORD add = 0;

	add = ����::��Χ��������(����);
	lua_pushinteger(L, add);
	return 1;
}

static int ���������(__LUA_ָ��)
{
	DWORD ���� = lua_tointeger(L, 1);
	const char* ���� = lua_tostring(L, 2);

	INT64 addr = 0;
	addr = ����::������﹥��(����, ����);
	lua_pushinteger(L, addr);
	return 1;
}



static int �����(__LUA_ָ��)
{
	DWORD ���� = lua_tointeger(L, 1);
	const char* ���� = lua_tostring(L, 2);

	INT64 addr = 0;
	 addr = ����::�������2(����, ����);
	lua_pushinteger(L, addr);
	return 1;
}

static int ����������(__LUA_ָ��)
{
	DWORD ���� = lua_tointeger(L, 1);
//	DWORD add = 0;
	INT64 addr=����::�������1(����);

	lua_pushinteger(L,addr);
	MyTrace(L"����������0x%I64X\n", addr);
	return 1;


}

static int ��½ID(__LUA_ָ��)
{
	DWORD ��½ID = ��ͼ::ȡ��ǰ��½ID();
	lua_pushinteger(L, ��½ID);

	return 1;

}

static int �򿪻��縱��(__LUA_ָ��)
{
	DWORD ���� = lua_tointeger(L, 1);
	 Fun_DungeonEntranceChaoEnter(����);
	 return 0;

}


static int ��ȡ������Ϣ(__LUA_ָ��)
{
	const char* tmpStr = lua_tostring(L, 1);
	//DebugPrintf("��־:%s", tmpStr);
	string tempStr = tmpStr;
	CString tmp = tempStr.c_str();
	DWORD id=getReverseRuinAll(tmp);

	lua_pushinteger(L, id);
	return 1;


}



static int ����1(__LUA_ָ��)
{
	//const char* tmpStr = lua_tostring(L, 1);
	////DebugPrintf("��־:%s", tmpStr);
	//string tempStr = tmpStr;
	//CString tmp = tempStr.c_str();
	//getReverseRuinAll();
	return 0;

}

static int ����(__LUA_ָ��)
{


	ActorInfo_ ��ɫ��Ϣ = ����::ȡ��ɫ��Ϣ();

	MyTrace(L"��ɫ��Ϣ0x%I64X �������0x%I64X  ID1 0x%I64X" ,��ɫ��Ϣ.����ָ��, ��ɫ��Ϣ.����ָ�� + g_�Ƿ�����, ��ɫ��Ϣ.ID1);

	vector<objInfo_>vsk;
	����::����ȫ����������1(vsk);
	for (size_t i = 0; i < vsk.size(); i++)
	{
		if (vsk[i].dType == 2 && vsk[i].IsHide == 1)
		{
			continue;
		}

		
		MyTrace(L"�����ַ0x%I64X ID %X  ID1 %d  %s ����%d ����%0.f/%0.f/%0.f ����%s ���� %0.3f \n", vsk[i].objBase, vsk[i].dResId, vsk[i].ModId, vsk[i].wName, vsk[i].dType, vsk[i].����.x, vsk[i].����.y, vsk[i].����.z, vsk[i].wName,vsk[i].����);
	}




	//MyTrace(L"�����ַ0x%I64X ID %X %s ����%d ����%0.f/%0.f/%0.f ����%s\n", dObjAddr, bi.dResId, csName, bi.dType, bi.����.x, bi.����.y, bi.����.z, bi.wName);


	vector<QuestInfo_>vsk1;
	����::get_CurQuestList(vsk1);

	vector<Inventoryinfo_> vsk2;
	����::get_InventoryItemList(vsk2);
	DWORD a = 0;

	for (size_t i = 0; i < vsk2.size(); i++)
	{
		MyTrace(L"λ��%d  ��ƷID 0x%I64X ��ԴID  0x%I64X ����%d  ��������%d �;�%d  ���� %s \r\n", vsk2[i].dindex, vsk2[i].ItemId,vsk2[i].ItemResId, vsk2[i].dNum, vsk2[i].dSlotIndex, vsk2[i].�;ö�.��ǰ�;ö�,vsk2[i].ItemName);
		/*wchar_t buf[MAX_PATH];
		swprintf(buf, L"λ��%X ��ַ0x%I64X ��ƷID 0x%I64X ��ԴID %X ��ַ0x%I64X ����%d %s ��λ%X ��������%d ��������%d �;�%d/%d\r\n", i, dStart + i * dSize, dItemId, dItmeResId, dItemResAddr, dNum, csName, dSlotIndex, getEquipWearArg(dSlotIndex), dBoxType, temp.�;ö�.��ǰ�;ö�, temp.�;ö�.����;ö�);
		MyTrace(buf);*/
	/*	if (vsk[i].dSlotIndex == ID && ID != 0)
		{
			a = a + 1;


		}*/

		/*	if (vsk[i].ItemName.Find(��Ʒ����) != -1)
			{
				����::ʹ����Ʒ2(vsk[i].dindex);
				break;
			}*/
	}




	CString �����ı� = L"��";
	�����ı� = UI����::���ڷ����ı�();
	MyTrace(L"�����ı�%s", �����ı�.GetString());
	//DWORD ��½ID = ��ͼ::ȡ��ǰ��½ID();
	return 0;

	

}


static int �Զ����¼(__LUA_ָ��)
{
	const char* message = lua_tostring(L, 1);

	MyTrace(L"%s", CStringW(message));

	return 0;
}



static int LogMsg1(__LUA_ָ��)
{
	const char* message = lua_tostring(L, 1);
	//const char* message = lua_tostring(L, -1);
	//DebugPrintf("%s\n", message);
	//string error_message = message;
	//MyTrace(L"��ʼ���");
	MyTrace(L"%s", CStringW(message));

	return 0;

}
static int ȡ������(__LUA_ָ��)
{
	����::����������();
	return 0;

}


static int �������Ƿ����(__LUA_ָ��)
{
	QuestInfo_ temp;
	vector<QuestInfo_>vsk;
	����::get_CurQuestList(vsk);
	const char* tmpStr = lua_tostring(L, 1);
	DWORD ����� =  lua_tointeger(L, 2);
	DWORD x1=0;
	DWORD x;
	x = ���ù���::ʮ������תʮ����(tmpStr);
	for (size_t i = 0; i < vsk.size(); i++)
	{
	MyTrace(L"����ID %I64X  ���������� %d", vsk[i].dQuestId, vsk[i].���������.size());
		if (x==vsk[i].dQuestId)
		{
			//MyTrace(L"ƥ��ɹ�");
			if (vsk[i].���������.size() >= �����)
			{

				MyTrace(L"dCur %d  dNeed %d", vsk[i].���������[����� - 1].dCur, vsk[i].���������[����� - 1].dNeed);
			//	MyTrace(L"������������� %d  ", vsk[i].���������.size());
				if (vsk[i].���������[����� - 1].dCur == vsk[i].���������[����� - 1].dNeed)
				{
					x1 = 1;
					break;

				}

			}


		}

	}

	lua_pushinteger(L, x1);

	return 1;

}



static int ��������Ϣ(__LUA_ָ��)
{
	QuestInfo_ temp;
	vector<QuestInfo_>vsk;
	����::get_CurQuestList(vsk);
	const char* tmpStr = lua_tostring(L, 1);
	DWORD ����� = lua_tointeger(L, 2);
	DWORD x1 = 0;
	DWORD x2 = 0;
	DWORD x;
	x = ���ù���::ʮ������תʮ����(tmpStr);
	for (size_t i = 0; i < vsk.size(); i++)
	{
		MyTrace(L"����ID %I64X  ���������� %d", vsk[i].dQuestId, vsk[i].���������.size());
		if (x == vsk[i].dQuestId)
		{
			//MyTrace(L"ƥ��ɹ�");
			if (vsk[i].���������.size() >= �����)
			{
				x1 = vsk[i].���������[����� - 1].dCur;
				x2 = vsk[i].���������[����� - 1].dNeed;
				MyTrace(L"dCur %d  dNeed %d", vsk[i].���������[����� - 1].dCur, vsk[i].���������[����� - 1].dNeed);
				break;
				//	MyTrace(L"������������� %d  ", vsk[i].���������.size());
			/*	if (vsk[i].���������[����� - 1].dCur == vsk[i].���������[����� - 1].dNeed)
				{
					x1 = 1;
					break;

				}*/

			}


		}

	}

	lua_pushinteger(L, x1);

	return 1;

}



 int ��ת_ȡ����������(__LUA_ָ��)
{
	//USES_CONVERSION;
	QuestInfo_ �������� = ����::ȡ����������();
	MyTrace(L"������������%s ���������� %d", ��������.QuestName, ��������.���������.size());
	// ����"���������"��
	
	MyTrace(L"2");
	lua_newtable(L);	
	lua_pushstring(L, "objBase");
	lua_pushinteger(L, ��������.objBase);
	lua_settable(L, -3);
	lua_pushstring(L, "dResAddr");
	lua_pushinteger(L, ��������.dResAddr);
	lua_settable(L, -3);
	lua_pushstring(L, "dQuestId");
	lua_pushnumber(L, ��������.dQuestId);
	lua_settable(L, -3);
	lua_pushstring(L, "dStep");
	lua_pushnumber(L, ��������.dStep);
	lua_settable(L, -3);
	lua_pushstring(L, "dState");
	lua_pushnumber(L, ��������.dState);
	lua_settable(L, -3);
	lua_pushstring(L, "dType");
	lua_pushnumber(L, ��������.dType);
	lua_settable(L, -3);
	lua_pushstring(L, "IsFinish");
	lua_pushnumber(L, ��������.IsFinish);
	lua_settable(L, -3);
	lua_pushstring(L, "QuestName");
	lua_pushstring(L, CStringA(��������.QuestName));
	lua_settable(L, -3);
	lua_pushstring(L, "CurNum");
	lua_pushnumber(L, ��������.CurNum);
	lua_settable(L, -3);
	lua_pushstring(L, "NeedNum");
	lua_pushnumber(L, ��������.NeedNum);
	lua_settable(L, -3);
	lua_pushstring(L, "TargetId");
	lua_pushnumber(L, ��������.TargetId);
	lua_settable(L, -3);
	lua_pushstring(L, "QuestOption");
	lua_pushstring(L, CStringA(��������.QuestOption));
	lua_settable(L, -3);
	lua_pushstring(L, "�������������");
	lua_pushnumber(L, ��������.���������.size());
	lua_settable(L, -3);
	lua_pushstring(L, "���������");
	lua_newtable(L);
	for (size_t i = 0; i < ��������.���������.size(); i++)
	{
		char buffer[10];
		sprintf(buffer, "%d", i + 1);
		lua_pushstring(L, buffer);
		MyTrace(L"1");
		lua_newtable(L);
		lua_pushstring(L, "��������");
		lua_pushstring(L, CStringA(��������.���������[i].��������));
		lua_settable(L, -3);
		lua_pushstring(L, "TargetId");
		lua_pushnumber(L, ��������.���������[i].TargetID);
		lua_settable(L, -3);
		lua_pushstring(L, "dCur");
		lua_pushnumber(L, ��������.���������[i].dCur);
		lua_settable(L, -3);
		lua_pushstring(L, "dNeed");
		lua_pushnumber(L, ��������.���������[i].dNeed);
		lua_settable(L, -3);
		// ������1��ӵ����������table��
		lua_settable(L, -3);
		
	}
	lua_settable(L, -3);

	
	MyTrace(L"3");
	return 1;
}


void RegLuaScript(lua_State* L)//luaע�ắ��
{


	lua_register(L, "ȡ����������", ��ת_ȡ����������);
	lua_register(L, "��־���", ��ת_��־���);
	lua_register(L, "��ʱ", LUA_��ʱ);
	lua_register(L, "���ô�Ա", ���ô�Ա);
	lua_register(L, "Ѱ·", Ѱ·_lua);
	lua_register(L, "ѡ������", ����ս��);
	lua_register(L, "msg", LogMsg1);
	lua_register(L, "��ȡ������Ϣ", ��ȡ������Ϣ);
	lua_register(L, "����", ����);
	lua_register(L, "�ֿ�ȡ��Ʒ����", �ֿ�ȡ��Ʒ����);
	lua_register(L, "�ֿ�ȡ����", �ֿ�ȡ����);
	lua_register(L, "ѡ������", ѡ��);
	lua_register(L, "�Ի����", �Ի����);
	lua_register(L, "��ⴰ��",��ⴰ��);
	lua_register(L, "ѡ������", ѡ������);
	lua_register(L, "ȷ��ְҵ", ȷ��ְҵ);
	lua_register(L, "������Ļ", ������Ļ);
	lua_register(L, "�Զ�����", �Զ�����);
	lua_register(L, "����װ��", ����װ��);
	lua_register(L, "���ü��ܰ���1", ���ü��ܰ���1);
	lua_register(L, "�������ü���", �������ü���);
	lua_register(L, "�Ƿ񵽴ﺽ������", �Ƿ��ں���׼������);
	lua_register(L, "��ϷС��", ��ϷС��);
	lua_register(L, "��ȡְҵ", ��ȡְҵ);
	lua_register(L, "ѡ���ɫ��ʼ��Ϸ", ѡ���ɫ��ʼ��Ϸ);
	lua_register(L, "�����ж�", �����ж�);
	lua_register(L, "�������ʯ", �������ʯ);
	lua_register(L, "��ȡ�ۿ�ID", ��ȡ�ۿ�ID);
	lua_register(L, "�Ƿ�ѡ���ɫ����", �Ƿ�ѡ���ɫ����);
	lua_register(L, "��קҩ��", ��קҩ��);
	lua_register(L, "��½ID", ��½ID);
	lua_register(L, "Ѱ·��ͼ", Ѱ·��ͼ);
	lua_register(L, "��������", ��������);
	lua_register(L, "��������", ��������);
	lua_register(L, "���ESC", ���ESC);
	lua_register(L, "�����Ƿ���", �����Ƿ���);
	lua_register(L, "�����ж�", �����ж�);
	lua_register(L, "׼������", ׼������);
	lua_register(L, "����������", ����������);
	lua_register(L, "�����", �����);
	lua_register(L, "�Զ����¼", �Զ����¼);
	lua_register(L, "��������", ��������);
	lua_register(L, "��ȡ�������", ��ȡ�������);
	lua_register(L, "������", ������1);
	lua_register(L, "�����ѯ", �����ѯ);
	lua_register(L, "�رն��ര��", �رն��ര��);
	lua_register(L, "�����ж�", �����ж�);
	lua_register(L, "������Ʒ����", �ɼ�����);
	lua_register(L, "��������", ��������);
	lua_register(L, "��������1", ��������1);
	lua_register(L, "��ȡ�ʼ�", ��ȡ�ʼ�);
	lua_register(L, "�һ��ƽ�", �һ��ƽ�);
	lua_register(L, "�����̵�", �����̵�);
	lua_register(L, "��Ϣ��ȡ", ��Ϣ��ȡ);

	lua_register(L, "��ǰ����", ��ǰ����);
	lua_register(L, "���ܵ�", ʣ�༼�ܵ�);
	lua_register(L, "������Ϣ", ������Ϣ);

	lua_register(L, "��������", ��������);
	lua_register(L, "ʰȡ", ʰȡ);
	lua_register(L, "����", ����);
	lua_register(L, "�Ƿ񺽺�����", �Ƿ񺽺�����);
	lua_register(L, "�Ƿ񶯻�����1", �Ƿ񶯻�����1);
	lua_register(L, "�Ƿ񶯻�����", �Ƿ񶯻�����);
	lua_register(L, "�����ж�", �����ж�);
	lua_register(L, "ά��", ά��);
	lua_register(L, "ʣ����Ϣ", ʣ����Ϣ);
	lua_register(L, "����ָ����Ʒ", ����ָ����Ʒ);
	lua_register(L, "����ʹ��", ����ʹ��);
	lua_register(L, "����������ѯ", ����������ѯ);
	lua_register(L, "�����ж�", �����ж�);
	lua_register(L, "�������", �������);
	lua_register(L, "�ؼ����", �ؼ����);
	lua_register(L, "��������", ��������);
	lua_register(L, "�ؼ�����", �ؼ�����);
	lua_register(L, "��������", ��������);
	lua_register(L, "�볡", �볡);
	lua_register(L, "���븱��", ���븱��);
	lua_register(L, "�뿪����", �뿪����);
	//lua_register(L, "�����·", �����·);
	lua_register(L, "�����չ", �����չ);
	lua_register(L, "�����Ƿ����", �����Ƿ����);
	lua_register(L, "������", ������);
	lua_register(L, "������ȴ", ������ȴ);
	lua_register(L, "������", ������);
	lua_register(L, "��ͼ����", ��ͼ����);
	lua_register(L, "����", ����);
	lua_register(L, "����", ����);
	lua_register(L, "�Ƿ��NPC", �Ƿ��NPC);
	lua_register(L, "�������Ƿ����", �������Ƿ����);
	lua_register(L, "ȡ������", ȡ������);
	lua_register(L, "��ȡ������Ϣ", ��ȡ������Ϣ);
	lua_register(L, "��ͼID", ��ͼID);
	lua_register(L, "�����Ƿ��ٻ�", �����Ƿ��ٻ�);
	lua_register(L, "�ٻ�����", �ٻ�����);
	lua_register(L, "����ʣ������", ����ʣ������);
	lua_register(L, "�ֽ�����", �ֽ�����);
	lua_register(L, "ʹ�ö���", ʹ�ö���);
	lua_register(L, "ʹ��������Ʒ", ʹ��������Ʒ);
	lua_register(L, "ʹ����Ʒ", ʹ����Ʒ);
	lua_register(L, "�ɷ񵽴�", �ɷ񵽴�);
	lua_register(L, "����ID", ����ID);
	lua_register(L, "����", ����);
	lua_register(L, "��Ʒ��Ϣ", ��Ʒ��Ϣ);
	lua_register(L, "�����NPC", �����NPC);
	lua_register(L, "����", ����);
	lua_register(L, "�����", �����);
	lua_register(L, "����", ����);
	lua_register(L, "����", ����);
	lua_register(L, "�°���", �°���);
	lua_register(L, "�رնԻ�", �رնԻ�);
	lua_register(L, "�ȴ�", �ȴ�);
	lua_register(L, "Ѱ·1", Ѱ·1);
	lua_register(L, "�������1", �������1);
	lua_register(L, "��������Ϣ", ��������Ϣ);
	lua_register(L, "���򹤾�", ���򹤾�);
	lua_register(L, "��ԭ����", ��ԭ����);
	lua_register(L, "�Ƿ�����", �Ƿ�����);
	lua_register(L, "����1", ����1);
	lua_register(L, "���������", ���������);
	lua_register(L, "��������������", ��������������);
	lua_register(L, "�����ж�", �����ж�);
	lua_register(L, "����1", ����1);
	lua_register(L, "�򿪽���", �򿪽���);
	lua_register(L, "��ȡ������Ϣ", ��ȡ������Ϣ);
	lua_register(L, "�򿪻��縱��", �򿪻��縱��);

	
	//����::�Զ�ѡ������ս��
	//lua_close(L);
}



//CStringW  	const char*ת��CString
//CStringA     CStringת��const char*