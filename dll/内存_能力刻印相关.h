#pragma once
#include "pch.h"
class 能力刻印
{
public:
	static void getAbilityEngraveAll();
	static int getEngraveDragLevById(int dEngraveId);
	static void Fun_EngraveDrag(int dEngraveId, int dPos);
};
class 诞生石
{
public:

	static void getmarbleWndItemList();
	static bool 诞生石强化();

};

class 研磨
{
public:
	static INT64 getItemBuildUpItemList();//研磨界面物品遍历 ok
	static BOOL bCheckitemBuildUpRenderTargetGroupShow();//判断最终成功窗口
	static BOOL bCheckitemBuildUpSuccess_mc();//判断最终成功窗口
	static BOOL bCheckitemBuildUpFail_mc();//判断最终成功窗口
	static int 研磨::Fun_ReadItemBuildUpListSelect();
	//static BOOL bCheckItemBuildUpLevelWndContentChildWindowShow(DWORD dChildIndex);
	//static void Fun_ItemBuildUpListSelect(int dIndex);	//选择需要强化物品 索引从0开始 ok
	//static void Fun_ItemBuildUpLevelUp();//主界面 升级按钮点击 ok
	//static void Fun_ItemBuildUpLevelUpGrade();// 主界面装备研磨按钮点击   ok

	//static void Fun_ItemBuildUpChildMaxClick();//子界面1 max按钮点击   ok
	//static void Fun_ItemBuildUpChildLevelUpBtnClick();//子界面1 成长点击  ok	

	//static void Fun_ItemBuildUpChildLevelUpGradeBtnClick();	//子界面2 装备研磨点击 ok

	//static void Fun_ItemBuildLevUpResult();//查看结果按钮 点击   ok
	static void Fun_ItemBuildLevUpSucess();//结果确定 点击  ok 放在Fun_ItemBuildLevUpResult 后调用 中间加点延迟5000
	//static bool 研磨::选定装备是否可升级();
	static BOOL bCheckItemBuildUpLevelWndContentChildWindowShow(DWORD dChildIndex);

	static bool 强化装备();
	static bool 强化装备(int lv);
};

