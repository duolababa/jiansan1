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
	MyTrace(L"����");
	if (����::�Ƿ��ں�NPC�Ի�())
	{
		����::CALL_�˳�NPC();
		Sleep(2000);
	}
	DWORD size = 0;
	MyTrace(L"ces");

	size = UI����::��������();

	if (size >= 1)
	{
		for (size_t i = 0; i < size; i++)
		{
			size = UI����::��������();
			if (size >= 1)
			{
				MyTrace(L"��ʼִ�а���call");
				UI����::�ڴ水��(VK_ESCAPE);
				Sleep(1500);

			}


		}


	}

	return 0;
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
	//sscanf(tmpStr, "%x", x);

	x = ���ù���::ʮ������תʮ����(tmpStr);
	����::CALL_ѡ������(x);
	Sleep(2000);
	����::CALL_�˳�����();
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
	MyTrace(L"id1 %X  id %X \r\n", id1, id);
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
	double Ѫ�� = (double(��ɫ��Ϣ.��ǰѪ) / double(��ɫ��Ϣ.���Ѫ)) * 100;

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
	


	double ���� = (double(��ɫ��Ϣ.������ǰ�;�) / double(��ɫ��Ϣ.��������;�)) * 100;
	temp.Format(L"%f", ����);
	arr.push_back(temp);//13
	temp.Format(L"%d", ��ɫ��Ϣ.װ������);
	arr.push_back(temp);//14
	temp.Format(L"%d", ��ɫ��Ϣ.��ǰѪ);
	arr.push_back(temp);//15
	temp.Format(L"%I64X", ��ɫ��Ϣ.����ָ��);
	arr.push_back(temp);//16
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


static int �����ж�(__LUA_ָ��)
{
	if (���Կ���==1)
	{
		luaL_error(L,"ֹͣ����");


	}
	return 0;


}

static int ��������(__LUA_ָ��)
{
	DWORD ����� = lua_tointeger(L, 1);
	CString ���ʽ;
	if (����� == 1)
	{
		���ʽ = "root";
		UI����::����(���ʽ);
	}
	else

	{
		���ʽ = "root";
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
	MyTrace(L"addr,0x%I64X", addr);
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
	}

	INT64 addr =����::����ȡ����call(3460, 11640);
	if (addr>1)
	{
		�����ı�1=UI����::UI����(addr);
		if (�����ı�1.Find(L"init_btn") != -1)
		{


		}
		
	}
		


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

static int ��������(__LUA_ָ��)
{
	DWORD ���� = lua_tointeger(L, 1);
	DWORD add = 0;

	add = ����::��Χ��������(����);
	lua_pushinteger(L, add);
	return 1;
}


static int �����(__LUA_ָ��)
{
	DWORD ���� = lua_tointeger(L, 1);
	const char* ���� = lua_tostring(L, 2);

	
	INT64 addr = ����::�������2(����, ����);
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

static int ����(__LUA_ָ��)
{
	vector<objInfo_>vsk;
	����::����ȫ����������1(vsk);
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
	MyTrace(L"��ʼ���");
	MyTrace(L"%s", CStringW(message));

	return 0;

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
	lua_register(L, "������1", ������1);
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



	//����::�Զ�ѡ������ս��
	//lua_close(L);
}



//CStringW  	const char*ת��CString
//CStringA     CStringת��const char*