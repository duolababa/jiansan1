#include "pch.h"
#include "WMCopyData.h"
#include < time.h>
#include "C:\Program Files (x86)\Windows Kits\10\Include\10.0.17763.0\um\timeapi.h"

class 仇人
{
public:
	DWORD 所在地图id;
	int x;
	int y;
	int z;
	int Lev;
	int 当前所在区;
	char Name[100];
	DWORD64 明文id;
	char My_Name[100];
	DWORD ArTime;
	仇人()
	{
		Lev = 0;
		所在地图id = 0;
		x = y = z = 0;
		memset(Name, 0, 100);
		memset(My_Name, 0, 100);
		明文id = 0;
		当前所在区 = -1;
		ArTime = 0;
	};
	void copy(仇人 b)
	{
		Lev = b.Lev;
		所在地图id = b.所在地图id;
		x = b.x;
		y = b.y;
		z = b.z;
		strcpy(Name, b.Name);
		strcpy(My_Name, b.My_Name);
		明文id = b.明文id;
		ArTime = b.ArTime;
		当前所在区 = b.当前所在区;
	};
	void clear()
	{
		Lev = 0;
		所在地图id = 0;
		x = y = z = 0;
		memset(Name, 0, 100);
		memset(My_Name, 0, 100);
		明文id = 0;
		当前所在区 = -1;
		ArTime = 0;
	};
};

HWND g_hWnd_kzt;
HWND g_HWnd_yz;
void WINAPI SendMessageToMoConter(int tag, CString CMSG)
{
	//#pragma pack(16)


//if (g_hWnd_kzt == NULL)
	{
		char* windowClassName1 = "abcdefg";
		g_hWnd_kzt = ::FindWindowA(windowClassName1, NULL);
		if (g_hWnd_kzt == NULL)
		{
			//MessageBoxA(NULL, "没有发现控制台程序", "错误", 0);
			//ExitProcess(0);
			return;
		}
	}
	USES_CONVERSION;
	char* msg = T2A(CMSG);
	char toSendmsg[0x2048] = { 0 }; memset(toSendmsg, 0, 0x2048);
	sprintf(toSendmsg, "%d_%s", GameIndex, msg);

	COPYDATASTRUCT cpd;
	cpd.lpData = (PVOID)toSendmsg;
	cpd.dwData = tag;
	cpd.cbData = strlen(toSendmsg) + 1;//多加一个长度，防止乱码

	SendMessageTimeoutA(g_hWnd_kzt, WM_COPYDATA, NULL, (LPARAM)&cpd, SMTO_NORMAL, 1000, 0);
	//::SendMessage(g_hWnd_kzt,WM_COPYDATA,NULL,(LPARAM)&cpd);
	//#pragma pack()

	char tempstrsend[0x200] = {0};
	sprintf(tempstrsend,"xxx-mmm==>1[窗口:%d]发来[%d][%s]", g_hWnd_kzt,tag,msg);
	OutputDebugStringA(tempstrsend);
}
void WINAPI SendMessageToMoConter02(int tag, BYTE* msg, int 长度)
{
	//#pragma pack(16)


	if (g_hWnd_kzt == NULL)
	{
		char* windowClassName1 = "abcdefg";
		g_hWnd_kzt = ::FindWindowA(windowClassName1, NULL);
		if (g_hWnd_kzt == NULL)
		{
			return;
		}
	}

	COPYDATASTRUCT cpd;
	cpd.lpData = (PVOID)msg;
	cpd.dwData = GameIndex * 10000 + tag;
	cpd.cbData = 长度;//多加一个长度，防止乱码
	::SendMessageTimeoutA(g_hWnd_kzt, WM_COPYDATA, NULL, (LPARAM)&cpd, SMTO_NORMAL, 100, 0);


	//#pragma pack()
}
void WINAPI SendMessageToMoConter03(int tag, CString CMSG)
{
	//#pragma pack(16)


	if (g_HWnd_yz == NULL)
	{
		char* windowClassName1 = "abcdefg";
		g_HWnd_yz = ::FindWindowA(windowClassName1, NULL);
		if (g_HWnd_yz == NULL)
		{
			return;
		}
	}
	USES_CONVERSION;
	char* msg = T2A(CMSG);
	COPYDATASTRUCT cpd;
	cpd.lpData = (PVOID)msg;
	cpd.dwData = GameIndex * 10000 + tag;
	cpd.cbData = strlen(msg);//多加一个长度，防止乱码
	::SendMessageTimeoutA(g_HWnd_yz, WM_COPYDATA, NULL, (LPARAM)&cpd, SMTO_NORMAL, 100, 0);

	/*char tempstrsend[0x200] = {0};
	sprintf(tempstrsend,"xxx-mmm==>1[窗口:%d]发来[%d][%s]",游戏窗口索引,tag,msg);
	OutputDebugStringA(tempstrsend);*/
	//#pragma pack()
}
#include <fstream>
char 通讯文件路径[100] = { 0 };
DWORD 通讯标志[200];
bool IsHaveFile(const char* FILENAME)
{
	fstream _file;
	_file.open(FILENAME, ios::in);
	if (!_file)
	{
		return false;
	}
	else
	{
		return true;
	}
}
//bool 获取通讯内容(bool 是否删除 = true)
//{
//	if (通讯文件路径[0] == 0)
//	{
//		//检查pkunzip.exe是否已经存在
//		/*GetTempPathA(100, 通讯文件路径);
//		char tempff[200];
//		sprintf(tempff, "%d.msg", GetCurrentProcessId());
//		strcat(通讯文件路径, tempff);*/
//		strcpy(通讯文件路径, "C:\\M4TempMsg\\");
//		char tempff[200];
//		sprintf(tempff, "%d.msg", 进程ID);
//		strcat(通讯文件路径, tempff);
//	}
//	//strcat(通讯文件路径, "C:\\1.msg");
//	//通讯文件路径 = ;
//	if (IsHaveFile(通讯文件路径) == false)
//		return false;
//
//	DWORD dwBytes1;
//	HANDLE hFile1 = CreateFileA(通讯文件路径,
//		GENERIC_READ, 0, NULL, OPEN_EXISTING,
//		FILE_ATTRIBUTE_NORMAL, NULL);
//
//	if (hFile1 == NULL)
//		return 0;
//
//	DWORD filesize = GetFileSize(hFile1, NULL);
//
//	for (int i = 0; i < 200; i++)
//		通讯标志[i] = 0;
//	SetFilePointer(hFile1, 0, NULL, FILE_BEGIN);
//
//	if (ReadFile(hFile1, 通讯标志, filesize, &dwBytes1, NULL))
//	{
//		/*strcpy(tejj_fff,"xxx_mmm-->");
//		for(int i = 0;i < 800;i++)
//		{
//			if(i >= 16 && i%16 == 0)
//			{
//				OutputDebugStringA(tejj_fff);
//				strcpy(tejj_fff,"xxx_mmm-->");
//			}
//			sprintf(tuu,"%02x ",读BYTE((DWORD64)通讯标志+i));
//			strcat(tejj_fff,tuu);
//		}
//		OutputDebugStringA(tejj_fff);
//		OutputDebugStringA("xxx-mmm-->====================================");*/
//
//		if (hFile1 != INVALID_HANDLE_VALUE)
//		{
//			CloseHandle(hFile1);
//			if (是否删除)
//			{
//				for (int i = 0; i < 100 && IsHaveFile(通讯文件路径); i++)
//				{
//					DeleteFileA(通讯文件路径);
//				}
//			}
//
//
//		}
//		return true;
//	}
//	return false;
//}
void 发送仇人测试()
{
	仇人 仇人A;
	仇人A.ArTime = 332211;
	strcpy(仇人A.Name,"每天快乐");
	仇人A.所在地图id = 202010200;
	仇人A.Lev = 40;
	仇人A.x = 100;
	仇人A.y = 101; 
	仇人A.z = 102;
	仇人A.明文id = 0x123CA0DC0;
	仇人A.当前所在区 = 2;
	strcpy(仇人A.My_Name, "每天快乐2");
	SendMessageToMoConter02(202, (BYTE*)(&(仇人A)), sizeof(仇人));
}

void 发送自己信息测试()
{
	MyPlayerclass 自己;
	自己.AtQF = 2;
	自己.Lev = 40;
	自己.Mapid = 202010200;
	自己.PleryID = 57183020012;
	自己.type = 2;
	自己.zy = 123044;
	strcpy(自己.Name,"每天不快乐");
	SendMessageToMoConter02(203, (BYTE*)(&(自己)), sizeof(自己));
}

//void 取出数据()
//{
//	if (获取通讯内容())
//	{
//		DbgPrintf_Mine("通讯标志:%d", 通讯标志[0]);
//		通讯标志[0] = 0;
//		static 仇人* tempcr;
//		tempcr = (仇人*)(&通讯标志[1]);
//		DbgPrintf_Mine("通讯:%s %s", tempcr->Name,tempcr->My_Name);
//	}
//}