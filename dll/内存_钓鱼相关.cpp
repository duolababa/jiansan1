#include "内存_钓鱼相关.h"
void 钓鱼::Fun_FishThrow_屏幕(int dPx, int dPy)
{
	INT64 局_真实对象 = 本人::取真实对象();
	INT64 局_RCX = 局_真实对象 + 偏移_地图_寻路rcx;
	坐标_ 局_当前坐标 = 本人::取坐标();
	INT64 局_dCALL = 游戏模块 + 基址_地图_寻路call;
	INT64 dMuoseInfo = R_QW(游戏模块 + gb_MouseInfo);
	W_DW(dMuoseInfo + go_MousePoint, dPx);
	W_DW(dMuoseInfo + go_MousePoint+4, dPy);
	UCHAR pBuff[0x140] = { 0 };
	W_QW((ULONG64)&pBuff[0x0], 0xA00004040);
	W_DW((ULONG64)&pBuff[0xDC], 0x11300);
	W_DW((ULONG64)&pBuff[0xE0], 1);
	MainUniversalCALL4(局_RCX, (ULONG_PTR)pBuff, 0, 0, 局_dCALL);
}
void 钓鱼::Fun_FishThrow_世界坐标(float fx, float fy,float fz)
{
	INT64 局_真实对象 = 本人::取真实对象();
	INT64 局_RCX = 局_真实对象 + 偏移_地图_寻路rcx;
	坐标_ 局_当前坐标 = 本人::取坐标();
	INT64 局_dCALL = 游戏模块 + 基址_地图_寻路call;
	技能::写怪物坐标到鼠标2(fx, fy, fz);
	UCHAR pBuff[0x140] = { 0 };
	W_QW((ULONG64)&pBuff[0x0], 0xA00004040);
	W_DW((ULONG64)&pBuff[0xDC], 0x11300);
	W_DW((ULONG64)&pBuff[0xE0], 1);
	MainUniversalCALL4(局_RCX, (ULONG_PTR)pBuff, 0, 0, 局_dCALL);
}


//浮标状态
int 钓鱼::getFishObjState()//5为初始化 1为普通 3为来鱼 2为出现感叹
{

	INT64 addr_3 = 本人::取真实对象();
	INT64 dTemp = R_QW(addr_3 + 0x94);//更新-0218
	INT64 dFishObj = R_QW(dTemp + go_Role_FishObj);
	if (dFishObj)
	{
		return R_BYTE(dFishObj + go_Role_FishObj_State);
	}
	return -1;
}




//当前快捷键页面类型
int 钓鱼::getquickSlotFrameType()//1普通 3 生活 5骑马
{
	INT64 dUiObj = UI功能::getUiObjById( 0x2D);//quickSlotFrame
	if (dUiObj)
	{
		return R_DW(dUiObj + go_QuickSlotType);
	}
	return 0;
}


void 钓鱼::捕鱼()
{
	for (size_t i = 0; i < 3000; i++)
	{
		DWORD X = 钓鱼::getquickSlotFrameType();
		if (X == 2)
		{
			UI功能::内存按键(DWORD('E'));
			return;
		}

		Sleep(100);
	}


}