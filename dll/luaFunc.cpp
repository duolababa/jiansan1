#pragma once

#include "luaFunc.h"
//#include <string>
//#include "pch.h"
#include <tuple>
#include <string>
#include <vector>
#include <type_traits>
#include <functional>
using namespace std;



// ��C++��std::stringת��ΪLua���ַ���
lua_State* C_L;
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
	const char* message = lua_tostring(L, -1);
	DebugPrintf("%s\n", message);
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
void RegLuaScript(lua_State* L)
{


	lua_register(L, "ȡ����������", ��ת_ȡ����������);
	lua_register(L, "��־���", ��ת_��־���);
	lua_register(L, "��ʱ", LUA_��ʱ);
	//lua_close(L);
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
	MyTrace(L"��� %d",a);
	if (a)
	{
		MyTrace(L"���");
		string errormssage = lua_tostring(L, -1);
		
		DebugPrintf("%s\n", lua_tostring(L, -1));
		Lua���� = false;
		lua_close(L);
		return false;
	}
	return true;
}
void ��ȫ��LUA״̬��(lua_State* L)
{
	C_L = L;
}



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
	��ͼ::����ͼѰ·(x, y, z, 0);
	return 0;
}

//int DPrint(CString �ı�)
//{
//	MyTrace(L"%s",�ı�);
//	return 0;
//}



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
/*
#define __LUA_ָ�� lua_State* L

static int MovePoint(__LUA_ָ��)
{
	float x = lua_tonumber(L, 1);
	float y = lua_tonumber(L, 2);
	float z = lua_tonumber(L, 3);
	��Ϸ����Ⱥ782282356::f˲��(x, y, z);
	//DebugPrintf("������lua[˲��] -- �������� => [%.1f,%.1f,%.1f]\n",x,y,z);
	return 0;
}
static int DbgPrint(__LUA_ָ��)
{
	const char* tmpStr = lua_tostring(L, 1);
	DebugPrintf("%s\n", tmpStr);
	return 0;
}
static int GetMapId(__LUA_ָ��)
{
	lua_pushinteger(L, ��Ϸ����Ⱥ782282356::f��ȡ��ͼID());
	return 1;
}
static int FindWayTo(__LUA_ָ��)
{
	DWORD MAPID = lua_tonumber(L, 1);
	float x = lua_tonumber(L, 2);
	float y = lua_tonumber(L, 3);
	float z = lua_tonumber(L, 4);
	��Ϸ����Ⱥ782282356::CALLѰ·(MAPID, x, y, z);
	return 0;
}
static int GameKeyB(__LUA_ָ��)
{
	DWORD KeyVal = lua_tointeger(L, 1);
	//��Ϸ����Ⱥ782282356::CALL����((UINT64)KeyVal);
	return 0;
}

static int GetFindWayNextPos(__LUA_ָ��)
{
	�ṹ_���� tmpPos = ��Ϸ����Ⱥ782282356::fȡѰ·�¸�Ŀ������();
	lua_pushnumber(L, tmpPos.x);
	lua_pushnumber(L, tmpPos.y);
	lua_pushnumber(L, tmpPos.z);
	return 3;
}
static int GetRolePos(__LUA_ָ��)
{
	�ṹ_���� tmpPos = ��Ϸ����Ⱥ782282356::fȡ��ɫ����();
	lua_pushnumber(L, tmpPos.x);
	lua_pushnumber(L, tmpPos.y);
	lua_pushnumber(L, tmpPos.z);
	return 3;
}
static int GetRoleSateL(__LUA_ָ��)
{
	lua_pushinteger(L, ��Ϸ����Ⱥ782282356::f��ȡ��ɫ״̬());
	return 1;
}
static int IsLoadingL(__LUA_ָ��)
{
	lua_pushboolean(L, ��Ϸ����Ⱥ782282356::f�Ƿ������Ϸ��());
	return 1;
}
static int IsStoryMissionIngL(__LUA_ָ��)
{
	lua_pushboolean(L, ��Ϸ����Ⱥ782282356::f�Ƿ��ھ�����());
	return 1;
}
static int SeckillMonsterL(__LUA_ָ��)
{
	��Ϸ����Ⱥ782282356::f��ɱ����();
	return 0;
}
static int FindWayMoveTo(__LUA_ָ��)
{
	DWORD MAPID = lua_tonumber(L, 1);
	float x = lua_tonumber(L, 2);
	float y = lua_tonumber(L, 3);
	float z = lua_tonumber(L, 4);
	��Ϸ����Ⱥ782282356::fѰ·˲��(MAPID, x, y, z);
	return 0;
}
static int IsFindWayIngL(__LUA_ָ��)
{
	lua_pushboolean(L, ��Ϸ����Ⱥ782282356::f�Ƿ�Ѱ·��());
	return 1;
}
static int GetMainTaskListL(__LUA_ָ��)
{
	��Ϸ����Ⱥ782282356::fȡ�ѽ������б�();
	lua_pushinteger(L, ��Ϸ����Ⱥ782282356::�ѽ������б�.size());
	return 1;
}
static int ��ȡ�ؼ������б�(__LUA_ָ��)
{

	//�ؼ����ܿ�ԴȺ782282356::fȡ�ؼ�����ṹ�б�();
	return 0;
}

static int �Զ���ʼ��Ϸ(__LUA_ָ��)
{
	�ؼ����ܿ�ԴȺ782282356::�����ʼ��Ϸ();
	return 0;
}
static int �������Ͻ�����(__LUA_ָ��)
{
	�ؼ����ܿ�ԴȺ782282356::���������Ի�_���Ͻ�();
	return 0;
}
static int �������Ͻ�����(__LUA_ָ��)
{
	�ؼ����ܿ�ԴȺ782282356::���������Ի�_���Ͻ�();
	return 0;
}
static int ��ʦ�������Ŀ��(__LUA_ָ��)
{
	��Ϸ����Ⱥ782282356::�����������();
	return 0;
}
static int �ؼ�_������Ϸ(__LUA_ָ��)
{
	�ؼ����ܿ�ԴȺ782282356::���������Ϸ();
	return 0;
}
static int  ��������(__LUA_ָ��)
{
	DWORD ��־ = lua_tointeger(L, 1);
	DWORD ����id = lua_tointeger(L, 2);
	��Ϸ����Ⱥ782282356::CALL��������(��־, ����id);
	return 0;
}
static int �ؼ�call(__LUA_ָ��)
{
	char* tmpstr = (char*)lua_tostring(L, 1);
	DWORD ƫ�� = lua_tointeger(L, 2);

	//DebugPrintf("%s\n", tmpstr);	
	�ؼ����ܿ�ԴȺ782282356::CALL�ؼ���ԴȺ782282356(tmpstr, ƫ��);
	return 0;
}

void RegLuaScript()
{

	lua_State* L = luaL_newstate();
	luaL_openlibs(L);

	lua_register(L, "˲��", MovePoint);
	lua_register(L, "ȡ��ͼID", GetMapId);
	lua_register(L, "�������", DbgPrint);
	lua_register(L, "Ѱ·��", FindWayTo);
	lua_register(L, "Ѱ·˲��", FindWayMoveTo);
	lua_register(L, "��ȡ��һ����", GetFindWayNextPos);
	lua_register(L, "��ȡ��ɫ����", GetRolePos);
	lua_register(L, "��ȡ��ɫ״̬", GetRoleSateL);
	lua_register(L, "�Ƿ�����Ϸ��", IsLoadingL);
	lua_register(L, "�Ƿ��ھ�����", IsStoryMissionIngL);
	lua_register(L, "�Ƿ�Ѱ·��", IsFindWayIngL);
	lua_register(L, "��ȡ�ѽ�����", GetMainTaskListL);
	lua_register(L, "ȡ�ؼ������б�", ��ȡ�ؼ������б�);
	lua_register(L, "�Զ���ʼ��Ϸ", �Զ���ʼ��Ϸ);
	lua_register(L, "�Զ��������Ͻ�����", �������Ͻ�����);
	lua_register(L, "�Զ��������Ͻ�����", �������Ͻ�����);
	lua_register(L, "����һ��", ��ʦ�������Ŀ��);
	lua_register(L, "��������", ��������);
	lua_register(L, "�ؼ�CALL", �ؼ�call);
	lua_register(L, "���������Ϸ", �ؼ�_������Ϸ);


	bool a= luaL_dofile(L, "Mir4.lua");

	if (a) DebugPrintf("%s\n", lua_tostring(L, -1));

	lua_close(L);
}

*/