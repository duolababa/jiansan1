#pragma once
#include "pch.h"

extern "C"
{
#include "lua/src/lua.h"
#include "lua/src/lualib.h"
#include "lua/src/lauxlib.h"


}
//#include "LuaJIT-2.1.0-beta3\src\lua.hpp"
//#pragma comment(lib,"LuaJIT-2.1.0-beta3\\src\\lua51.lib")  
//extern "C"
//{
//#include "LuaJIT-2.1.0-beta3\src\lua.h"  
//#include "LuaJIT-2.1.0-beta3\src\lualib.h"  
//}
#define __LUA_ָ�� lua_State* L
void RegLuaScript(lua_State* L);
lua_State* initLua();
bool ִ��lua(lua_State* L, const char* lua����);
 int ��ת_ȡ����������(__LUA_ָ��);
static int ��ת_��־���(__LUA_ָ��);
static int LUA_��ʱ(__LUA_ָ��);
static int ���ô�Ա(__LUA_ָ��);
static int Ѱ·_lua(__LUA_ָ��);
static int LogMsg1(__LUA_ָ��);
static int ����(__LUA_ָ��);
static int ��ȡ������Ϣ(__LUA_ָ��);
static int �ֿ�ȡ����(__LUA_ָ��);
static int �ֿ�ȡ��Ʒ����(__LUA_ָ��);
static int ѡ��(__LUA_ָ��);
static int ��ⴰ��(__LUA_ָ��);
static int �Ի����(__LUA_ָ��);
static int �رն��ര��(__LUA_ָ��);
static int ѡ������(__LUA_ָ��);
static int ȷ��ְҵ(__LUA_ָ��);
static int ������Ļ(__LUA_ָ��);
static int �Զ�����(__LUA_ָ��);

static int ����װ��(__LUA_ָ��);
static int ���ü��ܰ���1(__LUA_ָ��);
static int �������ü���(__LUA_ָ��);
static int �Ƿ��ں���׼������(__LUA_ָ��);
static int �����ж�(__LUA_ָ��);
static int ��ϷС��(__LUA_ָ��);
static int ��ȡְҵ(__LUA_ָ��);
static int ѡ���ɫ��ʼ��Ϸ(__LUA_ָ��);
static int �����ж�(__LUA_ָ��);
static int �������ʯ(__LUA_ָ��);
static int ��ȡ�ۿ�ID(__LUA_ָ��);
static int �Ƿ�ѡ���ɫ����(__LUA_ָ��);
static int ��קҩ��(__LUA_ָ��);
static int ��½ID(__LUA_ָ��);
static int Ѱ·��ͼ(__LUA_ָ��);
static int ��������(__LUA_ָ��);
static int ��������(__LUA_ָ��);
static int ���ESC(__LUA_ָ��);
static int �����Ƿ���(__LUA_ָ��);
static int �����ж�(__LUA_ָ��);
static int ׼������(__LUA_ָ��);
static int ����������(__LUA_ָ��);
static int �����(__LUA_ָ��);
static int �Զ����¼(__LUA_ָ��);
static int ��������(__LUA_ָ��);
static int ��ȡ�������(__LUA_ָ��);
static int ������1(__LUA_ָ��);
static int �����ѯ(__LUA_ָ��);
static int �ɼ�����(__LUA_ָ��);
static int ��������(__LUA_ָ��);
static int ��������1(__LUA_ָ��);
static int ��ȡ�ʼ�(__LUA_ָ��);
static int �һ��ƽ�(__LUA_ָ��);
static int �����̵�(__LUA_ָ��);
static int ��Ϣ��ȡ(__LUA_ָ��);
static int ��ǰ����(__LUA_ָ��);
static int ʣ�༼�ܵ�(__LUA_ָ��);
static int ������Ϣ(__LUA_ָ��);
static int ��������(__LUA_ָ��);
static int ʰȡ(__LUA_ָ��);
static int ����(__LUA_ָ��);
static int �������(__LUA_ָ��);
static int �Ƿ񺽺�����(__LUA_ָ��);



// NPC�̵�::get_ShopItemList(vector<Inventoryinfo_>& vsk)



//UI����::����(CString ���ʽ)
//	lua_register(L, "�����Ƿ���", �����Ƿ���);
//��Ϸģ�� = (UINT64)GetModuleHandleA("LOSTARK.exe");
//��Ϸģ��_EFEngine = (UINT64)GetModuleHandleA("EFEngine.dll");


//	lua_register(L, "��������", ��������);
//����::CALL_���������츳
//void ����::�Զ�װ���Ƽ�װ��()

//lua_register(L, "������Ļ", ������Ļ);
// ActorInfo_ ����::ȡ��ɫ��Ϣ()