
#include "pch.h"
#include "FlowerDream.h"
HANDLE �ļ����;
bool �Ƿ������߳� = false;

HANDLE �򿪽���(int ����ID)
{

	return OpenProcess(PROCESS_ALL_ACCESS, FALSE, ����ID);



}


bool ���ڴ�(HANDLE ���̾��, LPVOID Ҫ��ȡ���ڴ��ַ, LPVOID ������ݵ��ڴ��ַ, SIZE_T Ҫ��ȡ�ĳ���)
{
	

	SIZE_T OutSize=0;
	bool sta;
    sta = ReadProcessMemory(���̾��, Ҫ��ȡ���ڴ��ַ, ������ݵ��ڴ��ַ, Ҫ��ȡ�ĳ���, &OutSize);
	if (sta == true && OutSize == Ҫ��ȡ�ĳ���)
	{
		return true;
	}

	return false;

}
bool ���ڴ�2(HANDLE ���̾��, LPVOID Ҫ��ȡ���ڴ��ַ, LPVOID ������ݵ��ڴ��ַ, SIZE_T Ҫ��ȡ�ĳ���)
{
	SIZE_T OutSize = 0;
	bool sta;
	sta = ReadProcessMemory(���̾��, Ҫ��ȡ���ڴ��ַ, ������ݵ��ڴ��ַ, Ҫ��ȡ�ĳ���, &OutSize);
	if (sta == true && OutSize == Ҫ��ȡ�ĳ���)
	{
		return true;
	}

	return false;

}

int ���ڴ�������(HANDLE ���̾��, LPVOID Ҫ��ȡ���ڴ��ַ)
{
	
	int buff=0;
	bool sta;
	sta = ���ڴ�(���̾��, Ҫ��ȡ���ڴ��ַ,&buff, 4);
	if (sta==false)
	{
	   buff = -100;
	   return buff;
	}
	return buff;

}
int ���ڴ�������2(HANDLE ���̾��, LPVOID Ҫ��ȡ���ڴ��ַ)
{
	
	int buff = 0;
	bool sta;
	sta = ���ڴ�(���̾��, Ҫ��ȡ���ڴ��ַ, &buff, 4);
	if (sta == false)
	{
		buff = -100;
		return buff;
	}
	return buff;

}
short ���ڴ��������(HANDLE ���̾��, LPVOID Ҫ��ȡ���ڴ��ַ)
{
	
	short  buff = 0;
	bool sta;
	sta = ���ڴ�(���̾��, Ҫ��ȡ���ڴ��ַ, &buff, 2);
	if (sta == false)
	{
		buff = -100;
		return buff;
	}
	return buff;



}
short ���ڴ��������2(HANDLE ���̾��, LPVOID Ҫ��ȡ���ڴ��ַ)
{
	
	short  buff = 0;
	bool sta;
	sta = ���ڴ�2(���̾��, Ҫ��ȡ���ڴ��ַ, &buff, 2);
	if (sta == false)
	{
		buff = -100;
		return buff;
	}
	return buff;



}
unsigned short ���ڴ��޷��Ŷ�������(HANDLE ���̾��, LPVOID Ҫ��ȡ���ڴ��ַ)
{
	
	unsigned short buff = 0;
	bool sta;
	sta = ���ڴ�(���̾��, Ҫ��ȡ���ڴ��ַ, &buff, 2);
	if (sta == false)
	{
		buff = -100;
		return buff;
	}
	return buff;
}
unsigned short ���ڴ��޷��Ŷ�������2(HANDLE ���̾��, LPVOID Ҫ��ȡ���ڴ��ַ)
{
	
	unsigned short buff = 0;
	bool sta;
	sta = ���ڴ�2(���̾��, Ҫ��ȡ���ڴ��ַ, &buff, 2);
	if (sta == false)
	{
		buff = -100;
		return buff;
	}
	return buff;
}


long long ���ڴ泤������(HANDLE ���̾��, LPVOID Ҫ��ȡ���ڴ��ַ)
{
	
	long long buff = 0;
	bool sta;
	sta = ���ڴ�(���̾��, Ҫ��ȡ���ڴ��ַ, &buff, 8);
	if (sta == false)
	{
		buff = -100;
		return buff;
	}
	return buff;

}
long long ���ڴ泤������2(HANDLE ���̾��, LPVOID Ҫ��ȡ���ڴ��ַ)
{

	long long buff = 0;
	bool sta;
	sta = ���ڴ�2(���̾��, Ҫ��ȡ���ڴ��ַ, &buff, 8);
	if (sta == false)
	{
		buff = -100;
		return buff;
	}
	return buff;

}
float ���ڴ�С����(HANDLE ���̾��, LPVOID Ҫ��ȡ���ڴ��ַ)
{
	float buff = 0;
	bool sta;
	sta = ���ڴ�(���̾��, Ҫ��ȡ���ڴ��ַ, &buff, 4);
	if (sta == false)
	{
		buff = -100.0f;
		return buff;
	}
	return buff;

}
float ���ڴ�С����2(HANDLE ���̾��, LPVOID Ҫ��ȡ���ڴ��ַ)
{
	float buff = 0;
	bool sta;
	sta = ���ڴ�2(���̾��, Ҫ��ȡ���ڴ��ַ, &buff, 4);
	if (sta == false)
	{
		buff = -100.0f;
		return buff;
	}
	return buff;

}
double ���ڴ�˫����С����(HANDLE ���̾��, LPVOID Ҫ��ȡ���ڴ��ַ)
{

	double buff = 0;
	bool sta;
	sta = ���ڴ�(���̾��, Ҫ��ȡ���ڴ��ַ, &buff, 8);
	if (sta == false)
	{
		buff = -100.0f;
		return buff;
	}
	return buff;
}
double ���ڴ�˫����С����2(HANDLE ���̾��, LPVOID Ҫ��ȡ���ڴ��ַ)
{

	double buff = 0;
	bool sta;
	sta = ���ڴ�2(���̾��, Ҫ��ȡ���ڴ��ַ, &buff, 8);
	if (sta == false)
	{
		buff = -100.0f;
		return buff;
	}
	return buff;
}
char ���ڴ��ֽ���(HANDLE ���̾��, LPVOID Ҫ��ȡ���ڴ��ַ)
{

	char buff = 0;
	bool sta;
	sta = ���ڴ�(���̾��, Ҫ��ȡ���ڴ��ַ, &buff, 1);
	if (sta == false)
	{
		buff = -100;
		return buff;
	}
	return buff;
}
char ���ڴ��ֽ���2(HANDLE ���̾��, LPVOID Ҫ��ȡ���ڴ��ַ)
{

	char buff = 0;
	bool sta;
	sta = ���ڴ�2(���̾��, Ҫ��ȡ���ڴ��ַ, &buff, 1);
	if (sta == false)
	{
		buff = -100;
		return buff;
	}
	return buff;
}
int ���ڴ��ֽڼ�(HANDLE ���̾��, LPVOID Ҫ��ȡ���ڴ��ַ, int Ҫ��ȡ�ĳ���, PVOID outbuff)
{

	bool sta;
	sta = ���ڴ�(���̾��, Ҫ��ȡ���ڴ��ַ, outbuff, Ҫ��ȡ�ĳ���);
	if (sta == false)
	{
		return  -100;
	}
	return 1;

	

}
int ���ڴ��ֽڼ�2(HANDLE ���̾��, LPVOID Ҫ��ȡ���ڴ��ַ, int Ҫ��ȡ�ĳ���, PVOID outbuff)
{

	bool sta;
	sta = ���ڴ�2(���̾��, Ҫ��ȡ���ڴ��ַ, outbuff, Ҫ��ȡ�ĳ���);
	if (sta == false)
	{
		return  -100;
	}
	return 1;



}
wchar_t* ���ڴ��ı���3(HANDLE ���̾��, LPVOID Ҫ��ȡ���ڴ��ַ, int Ҫ��ȡ���ı�����)
{
	char buff = 1;
	wchar_t ubuff[2] = { 1,1 };
	SIZE_T OutSize;
	bool sta;
	wchar_t* str = L"";
	PVOID address = Ҫ��ȡ���ڴ��ַ;
	LPVOID lstr = L"";
	int len = 0;
	//CString a = L"";


		if (!IsBadReadPtr(Ҫ��ȡ���ڴ��ַ, 8)) 
		{
			str = (wchar_t*)Ҫ��ȡ���ڴ��ַ;
			return str;
		}
	
	return L"";
	
	/*if (Ҫ��ȡ���ı����� == 0)
	{
		while (buff != 0)
		{
			sta = ReadProcessMemory(���̾��, (PVOID)((LONGLONG)address + len), &buff, 1, &OutSize);
			if (sta == false)
			{
				buff = -100;
				return L"";
			}
			len = len + 1;
		}
		sta = ReadProcessMemory(���̾��, address, lstr, len, &OutSize);
		if (sta == false)
		{
			return L"";
		}
		return (LPCTSTR)lstr;
	}
	if (Ҫ��ȡ���ı����� == 1)
	{
		while (ubuff[0] != 0 && ubuff[1] != 0)
		{
			sta = ReadProcessMemory(���̾��, (PVOID)((LONGLONG)address + len), &ubuff, 2, &OutSize);
			if (sta == false)
			{
				return L"";
			}
			len = len + 2;
		}
		sta = ReadProcessMemory(���̾��, address, lstr, len, &OutSize);
		
		if (sta == false)
		{
			return L"";
		}
		return (LPCTSTR)lstr;
	}
	return L"";*/
}
int ���ڴ��ı���2(HANDLE ���̾��, LPVOID Ҫ��ȡ���ڴ��ַ, int Ҫ��ȡ���ı�����, TCHAR*(*outbuff))
{
	char buff = 1;
	wchar_t ubuff[2] = { 1,1 };
	SIZE_T OutSize;
	bool sta;
	PVOID address = Ҫ��ȡ���ڴ��ַ;
	int len = 0;
	TCHAR* Str = _T("");
	
		if (!IsBadReadPtr(Ҫ��ȡ���ڴ��ַ, 8))
		{
			Str = (wchar_t*)Ҫ��ȡ���ڴ��ַ;
			*outbuff = Str;
			return wcslen(Str);
		}
	
	*outbuff = L"";
	return buff = -100;
	/*if (Ҫ��ȡ���ı����� == 0)
	{
		while (buff != 0)
		{
			sta = ReadProcessMemory(���̾��, (PVOID)((LONGLONG)address + len), &buff, 1, &OutSize);
			if (sta == false)
			{
				buff = -100;
				return buff;
			}
			len = len + 1;
		}
		sta = ReadProcessMemory(���̾��, address, outbuff, len, &OutSize);
		if (sta == false)
		{
			return -100;
		}
		return len;
	}
	if (Ҫ��ȡ���ı����� == 1)
	{
		while (ubuff[0] != 0 && ubuff[1] != 0)
		{
			sta = ReadProcessMemory(���̾��, (PVOID)((LONGLONG)address + len), &ubuff, 2, &OutSize);
			if (sta == false)
			{
				return -100;
			}
			len = len + 2;
		}
		sta = ReadProcessMemory(���̾��, address, outbuff, len, &OutSize);
		if (sta == false)
		{
			return  -100;
		}
		return len;
	}
	return  -100;
	*/
}
int ���ڴ��ı���(HANDLE ���̾��, LPVOID Ҫ��ȡ���ڴ��ַ, int Ҫ��ȡ���ı�����, TCHAR*(*outbuff))
{
	
	char buff=1;
	wchar_t ubuff[2] = {1,1};
	SIZE_T OutSize;
	bool sta;
	PVOID address = Ҫ��ȡ���ڴ��ַ;
	int len=0;
	wchar_t* Str;

		if (!IsBadReadPtr(Ҫ��ȡ���ڴ��ַ, 8))
		{
			Str = (wchar_t*)Ҫ��ȡ���ڴ��ַ;
			*outbuff = Str;
			return wcslen(Str);
		}

	*outbuff = L"";
	return buff = -100;
	/*if (Ҫ��ȡ���ı�����==0)
	{
		while (buff!=0)
		{			
			sta = ReadProcessMemory(���̾��, (PVOID)((LONGLONG)address+len), &buff, 1, &OutSize);
			if (sta == false)
			{
				buff = -100;
				return buff;
			}
			len = len + 1;			
		}		
		sta = ReadProcessMemory(���̾��, address, outbuff, len, &OutSize);
		if (sta == false)
		{			
			return -100;
		}
		return len;	
	}
	if (Ҫ��ȡ���ı����� == 1)
	{
		while (ubuff[0] != 0 && ubuff[1] != 0)
		{
			sta = ReadProcessMemory(���̾��, (PVOID)((LONGLONG)address + len), &ubuff, 2, &OutSize);
			if (sta == false)
			{
				return -100;
			}
			len = len + 2;
		}
		sta = ReadProcessMemory(���̾��, address, outbuff, len, &OutSize);
		if (sta == false)
		{			
			return  -100;
		}
		return len;
	}
	return  -100;*/
}

bool д�ڴ�(HANDLE ���̾��, LPVOID Ҫд����ڴ��ַ, LPVOID Ҫд����������ڵ�ַ, SIZE_T Ҫд��ĳ���)
{
	
	bool sta;
	SIZE_T OutSize = 0;
	DWORD oldprotect;
	sta = WriteProcessMemory(���̾��, Ҫд����ڴ��ַ, Ҫд����������ڵ�ַ, Ҫд��ĳ���, &OutSize);
	if (sta == true && OutSize == Ҫд��ĳ���)
	{
		return true;
	}

	VirtualProtectEx(���̾��, Ҫд����ڴ��ַ, 1, PAGE_EXECUTE_READWRITE, &oldprotect);

	sta = WriteProcessMemory(���̾��, Ҫд����ڴ��ַ, Ҫд����������ڵ�ַ, Ҫд��ĳ���, &OutSize);

	VirtualProtectEx(���̾��, Ҫд����ڴ��ַ, 1, oldprotect, &oldprotect);

	if (sta == true && OutSize == Ҫд��ĳ���)
	{
		return true;
	}

	return false;

}


bool д�ڴ�2(HANDLE ���̾��, LPVOID Ҫд����ڴ��ַ, LPVOID Ҫд����������ڵ�ַ, SIZE_T Ҫд��ĳ���)
{

	bool sta;
	SIZE_T OutSize = 0;
	DWORD oldprotect;
	sta = WriteProcessMemory(���̾��, Ҫд����ڴ��ַ, Ҫд����������ڵ�ַ, Ҫд��ĳ���, &OutSize);
	if (sta == true && OutSize == Ҫд��ĳ���)
	{
		return true;
	}

	VirtualProtectEx(���̾��, Ҫд����ڴ��ַ, 1, PAGE_EXECUTE_READWRITE, &oldprotect);

	sta = WriteProcessMemory(���̾��, Ҫд����ڴ��ַ, Ҫд����������ڵ�ַ, Ҫд��ĳ���, &OutSize);

	VirtualProtectEx(���̾��, Ҫд����ڴ��ַ, 1, oldprotect, &oldprotect);

	if (sta == true && OutSize == Ҫд��ĳ���)
	{
		return true;
	}

	return false;

}


bool д�ڴ�������(HANDLE ���̾��, LPVOID Ҫд����ڴ��ַ, int wirtebuff)
{

	bool sta;
	sta = д�ڴ�(���̾��, Ҫд����ڴ��ַ, &wirtebuff, 4);
	return sta;

}
bool д�ڴ�������2(HANDLE ���̾��, LPVOID Ҫд����ڴ��ַ, int wirtebuff)
{

	bool sta;
	sta = д�ڴ�2(���̾��, Ҫд����ڴ��ַ, &wirtebuff, 4);
	return sta;

}
bool д�ڴ��������(HANDLE ���̾��, LPVOID Ҫд����ڴ��ַ, short wirtebuff)
{

	bool sta;
	sta = д�ڴ�(���̾��, Ҫд����ڴ��ַ, &wirtebuff, 2);
	return sta;

}
bool д�ڴ��������2(HANDLE ���̾��, LPVOID Ҫд����ڴ��ַ, short wirtebuff)
{

	bool sta;
	sta = д�ڴ�2(���̾��, Ҫд����ڴ��ַ, &wirtebuff, 2);
	return sta;

}
bool д�ڴ��޷��Ŷ�������(HANDLE ���̾��, LPVOID Ҫд����ڴ��ַ, unsigned short wirtebuff)
{

	bool sta;
	sta = д�ڴ�(���̾��, Ҫд����ڴ��ַ, &wirtebuff, 2);
	return sta;

}
bool д�ڴ��޷��Ŷ�������2(HANDLE ���̾��, LPVOID Ҫд����ڴ��ַ, unsigned short wirtebuff)
{

	bool sta;
	sta = д�ڴ�2(���̾��, Ҫд����ڴ��ַ, &wirtebuff, 2);
	return sta;

}
bool д�ڴ泤������(HANDLE ���̾��, LPVOID Ҫд����ڴ��ַ, long long wirtebuff)
{
	bool sta;
	sta = д�ڴ�(���̾��, Ҫд����ڴ��ַ, &wirtebuff, 8);
	return sta;
}
bool д�ڴ泤������2(HANDLE ���̾��, LPVOID Ҫд����ڴ��ַ, long long wirtebuff)
{
	bool sta;
	sta = д�ڴ�2(���̾��, Ҫд����ڴ��ַ, &wirtebuff, 8);
	return sta;
}
bool д�ڴ�С����(HANDLE ���̾��, LPVOID Ҫд����ڴ��ַ, float wirtebuff)
{

	bool sta;
	sta = д�ڴ�(���̾��, Ҫд����ڴ��ַ, &wirtebuff, 4);
	return sta;


}
bool д�ڴ�С����2(HANDLE ���̾��, LPVOID Ҫд����ڴ��ַ, float wirtebuff)
{

	bool sta;
	sta = д�ڴ�2(���̾��, Ҫд����ڴ��ַ, &wirtebuff, 4);
	return sta;


}
bool д�ڴ�˫����С����(HANDLE ���̾��, LPVOID Ҫд����ڴ��ַ, double wirtebuff)
{

	bool sta;
	sta = д�ڴ�(���̾��, Ҫд����ڴ��ַ, &wirtebuff, 8);
	return sta;


}
bool д�ڴ�˫����С����2(HANDLE ���̾��, LPVOID Ҫд����ڴ��ַ, double wirtebuff)
{

	bool sta;
	sta = д�ڴ�2(���̾��, Ҫд����ڴ��ַ, &wirtebuff, 8);
	return sta;


}
bool д�ڴ��ֽڼ�(HANDLE ���̾��, LPVOID Ҫд����ڴ��ַ, LPVOID Ҫд����������ڵ�ַ, SIZE_T Ҫд��ĳ���)
{


	bool sta;
	sta = д�ڴ�(���̾��, Ҫд����ڴ��ַ, Ҫд����������ڵ�ַ, Ҫд��ĳ���);
	return sta;


}
bool д�ڴ��ֽڼ�2(HANDLE ���̾��, LPVOID Ҫд����ڴ��ַ, LPVOID Ҫд����������ڵ�ַ, SIZE_T Ҫд��ĳ���)
{


	bool sta;
	sta = д�ڴ�2(���̾��, Ҫд����ڴ��ַ, Ҫд����������ڵ�ַ, Ҫд��ĳ���);
	return sta;


}
bool д�ڴ��ֽ���(HANDLE ���̾��, LPVOID Ҫд����ڴ��ַ, char wirtebuff)
{
	bool sta;
	sta = д�ڴ�(���̾��, Ҫд����ڴ��ַ, &wirtebuff, 1);
	return sta;
}
bool д�ڴ��ֽ���2(HANDLE ���̾��, LPVOID Ҫд����ڴ��ַ, char wirtebuff)
{
	bool sta;
	sta = д�ڴ�2(���̾��, Ҫд����ڴ��ַ, &wirtebuff, 1);
	return sta;
}
CString ȡ����Ŀ¼()
{
	TCHAR exeFullPath[MAX_PATH];
	GetModuleFileName(NULL, exeFullPath, MAX_PATH);
	CString str = exeFullPath;
	int a = str.ReverseFind('\\');
	str = str.Left(a);
	return  str;
}

HANDLE ���ļ�(LPCWSTR �ļ�ȫ·��)
{
	HANDLE �ļ����;
	�ļ����=CreateFileW(�ļ�ȫ·��, FILE_ALL_ACCESS, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	return �ļ����;
}

int д�ļ�(HANDLE �ļ����,LPCVOID Ҫд����������ڵ�ַ,DWORD Ҫд����ֽ���)
{
	DWORD outsize;
	bool sta;
	sta=WriteFile(�ļ����, Ҫд����������ڵ�ַ, Ҫд����ֽ���, &outsize, NULL);
	if (sta==true)
	{
		return outsize;
	}

	return 0;

}
int ���ļ�(HANDLE �ļ����, LPVOID Ҫ�������������ڵ�ַ, DWORD Ҫ�������ֽ���)
{
	DWORD outsize;
	bool sta;
	sta=ReadFile(�ļ����, Ҫ�������������ڵ�ַ, Ҫ�������ֽ���, &outsize, NULL);
	if (sta==true)
	{
		return outsize;
	}
	return 0;
}

string Read(LPCWSTR filePath)
{
	HANDLE pFile;
	DWORD fileSize;
	char* buffer, * tmpBuf;
	string �����ı�;
	DWORD dwBytesRead, dwBytesToRead, tmpLen;

	pFile = CreateFileW(filePath, FILE_ALL_ACCESS, 0, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	if (pFile == INVALID_HANDLE_VALUE)
	{
		printf("open file error!\n");
		CloseHandle(pFile);
		return FALSE;
	}

	fileSize = GetFileSize(pFile, NULL);          //�õ��ļ��Ĵ�С

	buffer = (char*)malloc(fileSize);
	ZeroMemory(buffer, fileSize);
	dwBytesToRead = fileSize;
	dwBytesRead = 0;
	tmpBuf = buffer;

	do {                                       //ѭ�����ļ���ȷ�������������ļ�    

		ReadFile(pFile, tmpBuf, dwBytesToRead, &dwBytesRead, NULL);

		if (dwBytesRead == 0)
		{
			break;
		}
			
		dwBytesToRead -= dwBytesRead;
		tmpBuf += dwBytesRead;

	} while (dwBytesToRead > 0);

	//  TODO ������������� buffer
	OutputDebugStringW(CString(buffer));
	�����ı� = buffer;
	free(buffer);
	CloseHandle(pFile);

	return �����ı�;
}


LPVOID �����ڴ�2(HANDLE ���̾��, int Ҫ������ڴ��С)
{



	return VirtualAllocEx(���̾��, 0, Ҫ������ڴ��С, MEM_COMMIT, PAGE_EXECUTE_READWRITE);




}


bool �ͷ��ڴ�2(HANDLE ���̾��, LPVOID �ͷŵĵ�ַ,int �ڴ��С)
{



	return VirtualFreeEx(���̾��, �ͷŵĵ�ַ, �ڴ��С, 32768);




}


