#include "协议解析1088.h"
#include"pch.h"

//void findWaytest();
//void 获取当前血当前蓝();
//void 遍历背包测试();
//UINT_PTR 获取背包对象指针(int index);

#define 标题   NULL // "Lost ark ???"
#define 类名   "EFLaunchUnrealUWindowsClient" //UnityWndClass


LRESULT CALLBACK 协议解析_1088(HWND hWnd, UINT wMsg/*WM_USER+10086*/, WPARAM wParam, LPARAM lParam)
{
	//char szClassName[256];
	//GetClassNameA(hWnd, szClassName, 256);

	//if (_stricmp(szClassName, 类名)!=0)  return 0;

	switch (wParam)
	{
	case CMDTYPE::MovePlayer:
	{
		{ //调用移动角色的CALL 指令

			MyTrace(L"Ricardo协议解析1088 CMDTYPE::MovePlayer +>>移动角色 line=%d\n", __LINE__);

			//findWaytest();
		}
		break;
	}
	case CMDTYPE::CmdType_PlayerInfo:
	{
		{
			//获取当前血当前蓝();
		}
		break;
	}
	case CMDTYPE::CmdType_遍历背包测试: //3 CMDTYPE::CmdType3
	{
		{
			MyTrace(L"Ricardo协议解析1088 CmdType_遍历背包测试");

			__try
			{
				//	MessageBeep(1);
					//获取背包对象指针(0);
				//遍历背包测试();
				//	MessageBeep(1);
			}
			__except (1)
			{
				MyTrace(L"Ricardo Error 协议解析1088 CmdType_遍历背包测试  %s %d Error\r\n", __FILE__, __LINE__);
			}

		}
		break;
	}
	case CMDTYPE::CmdType4: //3 CMDTYPE::CmdType4
	{
		MyTrace(L"Ricardo协议解析1088 CmdType4-->>>>>>>>>测试4");
		break;
	}
	case CMDTYPE::CmdType5: //3 CMDTYPE::CmdType4
	{
		MyTrace(L"Ricardo协议解析1088 CmdType5->遍历背包测试");
		//遍历背包测试();
		break;
	}
	case CMDTYPE::CmdType6: //3 CMDTYPE::CmdType4
	{
		MyTrace(L"Ricardo协议解析1088 CmdType6");
		CArray<int, int>showdo;
		//遍历背包测试();
		break;
	}
	}
	return 1;
}