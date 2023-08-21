#pragma once

#include "pch.h"
//void getUiList(vector<UIinfo_>& vsk);
class UI功能
{
public:
	static void getUiList(vector<UIinfo_>& vsk);
	static INT64 getUiObjById(DWORD ID);
	static INT64 getUiObjByName(CString name);
	static DWORD getUiIdByName(CString name);
	static INT64 getUiObjById_Old(DWORD ID);
	static bool 寻找打开窗口(CString name, INT64& rcx);

	static void 点击进入副本();
	static CString 节点唯一标识(INT64 对象, INT64& 返回对象);

	static bool 内存按键1(DWORD 加密按键, DWORD 类型 = 2);
	static bool 内存按键(DWORD 加密按键, DWORD 类型=2);
	static bool 地图是否打开();
	static bool 怪物击杀求饶界面是否打开();
	static bool 经验条界面是否显示();
	static bool 背包界面是否显示();
	static bool 大地图是否显示();
	static bool 体验职业中界面是否显示();
	static bool 副本界面是否打开();
	static bool 航海出港();
	static bool 航海入港();
	static bool 进入副本();
	static bool 是否出现G();
	static bool 是否读条();
	static bool 是否在航海准备界面();
	static bool 是否在交接任务界面();
	static bool 准备出航();
	static bool getMsgBoxTextList();
	static CString getMsgBoxMiddleText2(INT64 dUIObj);
	static CString getMsgBoxText();
	static CString getMsgBoxText_全();
	static void getNpcTalkSelectList(vector<CString>& 对话组);
	static bool 指定UI是否显示(CString UIName);
	static bool 商店是否打开();
	static bool 退出菜单是否打开();
	static bool UI功能::复活界面是否显示();
	static bool 复活(CString 复活方式);
	static int UI功能::get_DeadSceneList(CString 复活方式);
	static CString getUiName(INT64 dObjAddr);
	static bool get_DeadSceneListBtnState();
	static int getGameCurStageValue();
	static bool bCheckItemDisassemleWnd();
	static void Fun_UiShowCtrl(int dUiId);
	static DWORD 窗口数量();
	static CString UI名称(INT64 对象);
	static CString UI名称1(INT64 对象);
	static void 控件点击call(INT64 对象);
	static CString 窗口反馈文本();
	static bool 游戏IP异常();
	static void UI功能::控件输入call(INT64 对象, CString name);
	//static void Fun_NarrationAssistance_OnOff(int kaiguan);
	//static void Fun_NarrationAssistance_Continue();
	/*void generateBmp(BYTE* pData, int width, int height, LPCTSTR filename);
	void 生成(BYTE* pDATA, int 宽度, int 高度, LPCTSTR 路径);*/
private:
};

INT64 getChildUiAddrByStr(INT64 dParentAddr, CString cChildName);
INT64 getUiFirstAddr(INT64 dUiObj);
CString UTF82WCS(const char* szU8);
void Fun_MsgBoxConfirm(INT64 dUIObj);
void 混沌下一关();
void 混沌选项卡();