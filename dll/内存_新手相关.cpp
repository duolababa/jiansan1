#include "内存_新手相关.h"
bool 新手::CALL_跳过序幕()
{
	//INT64 局_获取序幕对象call = 游戏模块 + 基址_新手_获取序幕对象call;
	//INT64 局_获取序幕对象rcx = R_QW(游戏模块 + 基址_新手_获取序幕对象rcx);
	INT64 局_跳过序幕CALL = 游戏模块 + 基址_新手_跳过序幕call;
	INT64 局_序幕参数 = UI功能::getUiObjById(0x166);
	if (局_序幕参数 == 0)
	{
		return false;
	}
	MainUniversalCALL2(局_序幕参数, 0, 局_跳过序幕CALL);
	return true;
}
bool 新手::CALL_退出体验()
{
	INT64 rcx=0;


		for (int i = 0; i < 10; ++i)
		{
			bool 是否打开 = UI功能::寻找打开窗口("root1.arkui.frameCanvas.classPreviewCanvas", rcx);
			if (rcx >= 1)
			{

				INT64 局_call = 游戏模块 + 基址_新手_退出体验call;
				MainUniversalCALL4(rcx, 0, 0, 0, 局_call);
				Sleep(3000);
				CString 弹窗文本 = UI功能::窗口反馈文本();
				if (弹窗文本.Find(L"End Test") != -1)
				{
					UI功能::内存按键1(g_ENTER);
					break;
				}
				//End Test
			}
			Sleep(3000);
		}

	






	return true;
}

bool 新手::CALL_选择体验(DWORD 职业ID)
{
	INT64 局_call = 游戏模块 + 基址_新手_选择职业call;
	MainUniversalCALL4(职业ID, 1,0,0, 局_call);
	return true;
}

bool 新手::CALL_选择职业(DWORD 职业ID)
{
	INT64 局_call = 游戏模块 + 基址_新手_选择职业call;
	MainUniversalCALL2(职业ID, 2, 局_call);
	return true;
}
bool 直升::CALL_跳过序幕(DWORD index, DWORD  rdx1)
{
	//INT64 局_获取序幕对象call = 游戏模块 + 基址_新手_获取序幕对象call;
	//INT64 局_获取序幕对象rcx = R_QW(游戏模块 + 基址_新手_获取序幕对象rcx);
	INT64 rcx = R_QW(游戏模块 + 基址_直升_跳过序幕rcx);
	INT64 dCALL = 游戏模块 + 基址_直升_跳过序幕call;
	if (rcx)
	{
		MainUniversalCALL4(rcx, rdx1, index, 0, dCALL);
		return true;
	}
	return false;

}