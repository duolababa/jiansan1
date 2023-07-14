#pragma once
#include "pch.h"
class 登陆
{
public:

	static int 服务器遍历(vector<CString>& vsk);

	static int 查询服务器序号(CString 服务器名称);

	static bool 是否在服务器界面();

	static bool CALL_选择服务器(CString 服务器名称);

	static bool 是否出现确认协议();

	static bool CALL_确认协议();

	static bool CALL_选择职业(CString 职业名);

	static bool 是否在准备界面();

	static bool 是否在创建角色界面();

	static bool 是否在选择职业界面();

	static bool CALL_创建角色(int 创建次数);

	static bool CALL_打开创建角色(int 序号);

	static int  CALL_角色遍历(vector<登陆角色信息_>& vsk);

	static void get_CharacterList(vector<登陆角色信息_>& vsk);

	static 登陆角色信息_ getCharacterInfoByIndex(int 序号);

	static bool CALL_进入游戏(int 角色序号);

	static int getJumpMapCheck(int dIndex);

	static void getJmpMapList();

};

