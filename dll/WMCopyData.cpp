#include "pch.h"
#include "WMCopyData.h"
#include < time.h>
#include "C:\Program Files (x86)\Windows Kits\10\Include\10.0.17763.0\um\timeapi.h"

class ����
{
public:
	DWORD ���ڵ�ͼid;
	int x;
	int y;
	int z;
	int Lev;
	int ��ǰ������;
	char Name[100];
	DWORD64 ����id;
	char My_Name[100];
	DWORD ArTime;
	����()
	{
		Lev = 0;
		���ڵ�ͼid = 0;
		x = y = z = 0;
		memset(Name, 0, 100);
		memset(My_Name, 0, 100);
		����id = 0;
		��ǰ������ = -1;
		ArTime = 0;
	};
	void copy(���� b)
	{
		Lev = b.Lev;
		���ڵ�ͼid = b.���ڵ�ͼid;
		x = b.x;
		y = b.y;
		z = b.z;
		strcpy(Name, b.Name);
		strcpy(My_Name, b.My_Name);
		����id = b.����id;
		ArTime = b.ArTime;
		��ǰ������ = b.��ǰ������;
	};
	void clear()
	{
		Lev = 0;
		���ڵ�ͼid = 0;
		x = y = z = 0;
		memset(Name, 0, 100);
		memset(My_Name, 0, 100);
		����id = 0;
		��ǰ������ = -1;
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
			//MessageBoxA(NULL, "û�з��ֿ���̨����", "����", 0);
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
	cpd.cbData = strlen(toSendmsg) + 1;//���һ�����ȣ���ֹ����

	SendMessageTimeoutA(g_hWnd_kzt, WM_COPYDATA, NULL, (LPARAM)&cpd, SMTO_NORMAL, 1000, 0);
	//::SendMessage(g_hWnd_kzt,WM_COPYDATA,NULL,(LPARAM)&cpd);
	//#pragma pack()

	char tempstrsend[0x200] = {0};
	sprintf(tempstrsend,"xxx-mmm==>1[����:%d]����[%d][%s]", g_hWnd_kzt,tag,msg);
	OutputDebugStringA(tempstrsend);
}
void WINAPI SendMessageToMoConter02(int tag, BYTE* msg, int ����)
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
	cpd.cbData = ����;//���һ�����ȣ���ֹ����
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
	cpd.cbData = strlen(msg);//���һ�����ȣ���ֹ����
	::SendMessageTimeoutA(g_HWnd_yz, WM_COPYDATA, NULL, (LPARAM)&cpd, SMTO_NORMAL, 100, 0);

	/*char tempstrsend[0x200] = {0};
	sprintf(tempstrsend,"xxx-mmm==>1[����:%d]����[%d][%s]",��Ϸ��������,tag,msg);
	OutputDebugStringA(tempstrsend);*/
	//#pragma pack()
}
#include <fstream>
char ͨѶ�ļ�·��[100] = { 0 };
DWORD ͨѶ��־[200];
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
//bool ��ȡͨѶ����(bool �Ƿ�ɾ�� = true)
//{
//	if (ͨѶ�ļ�·��[0] == 0)
//	{
//		//���pkunzip.exe�Ƿ��Ѿ�����
//		/*GetTempPathA(100, ͨѶ�ļ�·��);
//		char tempff[200];
//		sprintf(tempff, "%d.msg", GetCurrentProcessId());
//		strcat(ͨѶ�ļ�·��, tempff);*/
//		strcpy(ͨѶ�ļ�·��, "C:\\M4TempMsg\\");
//		char tempff[200];
//		sprintf(tempff, "%d.msg", ����ID);
//		strcat(ͨѶ�ļ�·��, tempff);
//	}
//	//strcat(ͨѶ�ļ�·��, "C:\\1.msg");
//	//ͨѶ�ļ�·�� = ;
//	if (IsHaveFile(ͨѶ�ļ�·��) == false)
//		return false;
//
//	DWORD dwBytes1;
//	HANDLE hFile1 = CreateFileA(ͨѶ�ļ�·��,
//		GENERIC_READ, 0, NULL, OPEN_EXISTING,
//		FILE_ATTRIBUTE_NORMAL, NULL);
//
//	if (hFile1 == NULL)
//		return 0;
//
//	DWORD filesize = GetFileSize(hFile1, NULL);
//
//	for (int i = 0; i < 200; i++)
//		ͨѶ��־[i] = 0;
//	SetFilePointer(hFile1, 0, NULL, FILE_BEGIN);
//
//	if (ReadFile(hFile1, ͨѶ��־, filesize, &dwBytes1, NULL))
//	{
//		/*strcpy(tejj_fff,"xxx_mmm-->");
//		for(int i = 0;i < 800;i++)
//		{
//			if(i >= 16 && i%16 == 0)
//			{
//				OutputDebugStringA(tejj_fff);
//				strcpy(tejj_fff,"xxx_mmm-->");
//			}
//			sprintf(tuu,"%02x ",��BYTE((DWORD64)ͨѶ��־+i));
//			strcat(tejj_fff,tuu);
//		}
//		OutputDebugStringA(tejj_fff);
//		OutputDebugStringA("xxx-mmm-->====================================");*/
//
//		if (hFile1 != INVALID_HANDLE_VALUE)
//		{
//			CloseHandle(hFile1);
//			if (�Ƿ�ɾ��)
//			{
//				for (int i = 0; i < 100 && IsHaveFile(ͨѶ�ļ�·��); i++)
//				{
//					DeleteFileA(ͨѶ�ļ�·��);
//				}
//			}
//
//
//		}
//		return true;
//	}
//	return false;
//}
void ���ͳ��˲���()
{
	���� ����A;
	����A.ArTime = 332211;
	strcpy(����A.Name,"ÿ�����");
	����A.���ڵ�ͼid = 202010200;
	����A.Lev = 40;
	����A.x = 100;
	����A.y = 101; 
	����A.z = 102;
	����A.����id = 0x123CA0DC0;
	����A.��ǰ������ = 2;
	strcpy(����A.My_Name, "ÿ�����2");
	SendMessageToMoConter02(202, (BYTE*)(&(����A)), sizeof(����));
}

void �����Լ���Ϣ����()
{
	MyPlayerclass �Լ�;
	�Լ�.AtQF = 2;
	�Լ�.Lev = 40;
	�Լ�.Mapid = 202010200;
	�Լ�.PleryID = 57183020012;
	�Լ�.type = 2;
	�Լ�.zy = 123044;
	strcpy(�Լ�.Name,"ÿ�첻����");
	SendMessageToMoConter02(203, (BYTE*)(&(�Լ�)), sizeof(�Լ�));
}

//void ȡ������()
//{
//	if (��ȡͨѶ����())
//	{
//		DbgPrintf_Mine("ͨѶ��־:%d", ͨѶ��־[0]);
//		ͨѶ��־[0] = 0;
//		static ����* tempcr;
//		tempcr = (����*)(&ͨѶ��־[1]);
//		DbgPrintf_Mine("ͨѶ:%s %s", tempcr->Name,tempcr->My_Name);
//	}
//}