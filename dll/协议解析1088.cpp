#include "Э�����1088.h"
#include"pch.h"

//void findWaytest();
//void ��ȡ��ǰѪ��ǰ��();
//void ������������();
//UINT_PTR ��ȡ��������ָ��(int index);

#define ����   NULL // "Lost ark ???"
#define ����   "EFLaunchUnrealUWindowsClient" //UnityWndClass


LRESULT CALLBACK Э�����_1088(HWND hWnd, UINT wMsg/*WM_USER+10086*/, WPARAM wParam, LPARAM lParam)
{
	//char szClassName[256];
	//GetClassNameA(hWnd, szClassName, 256);

	//if (_stricmp(szClassName, ����)!=0)  return 0;

	switch (wParam)
	{
	case CMDTYPE::MovePlayer:
	{
		{ //�����ƶ���ɫ��CALL ָ��

			MyTrace(L"RicardoЭ�����1088 CMDTYPE::MovePlayer +>>�ƶ���ɫ line=%d\n", __LINE__);

			//findWaytest();
		}
		break;
	}
	case CMDTYPE::CmdType_PlayerInfo:
	{
		{
			//��ȡ��ǰѪ��ǰ��();
		}
		break;
	}
	case CMDTYPE::CmdType_������������: //3 CMDTYPE::CmdType3
	{
		{
			MyTrace(L"RicardoЭ�����1088 CmdType_������������");

			__try
			{
				//	MessageBeep(1);
					//��ȡ��������ָ��(0);
				//������������();
				//	MessageBeep(1);
			}
			__except (1)
			{
				MyTrace(L"Ricardo Error Э�����1088 CmdType_������������  %s %d Error\r\n", __FILE__, __LINE__);
			}

		}
		break;
	}
	case CMDTYPE::CmdType4: //3 CMDTYPE::CmdType4
	{
		MyTrace(L"RicardoЭ�����1088 CmdType4-->>>>>>>>>����4");
		break;
	}
	case CMDTYPE::CmdType5: //3 CMDTYPE::CmdType4
	{
		MyTrace(L"RicardoЭ�����1088 CmdType5->������������");
		//������������();
		break;
	}
	case CMDTYPE::CmdType6: //3 CMDTYPE::CmdType4
	{
		MyTrace(L"RicardoЭ�����1088 CmdType6");
		CArray<int, int>showdo;
		//������������();
		break;
	}
	}
	return 1;
}