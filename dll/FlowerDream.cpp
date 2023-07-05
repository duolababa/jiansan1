
#include "pch.h"
#include "FlowerDream.h"
HANDLE 文件句柄;
bool 是否跳出线程 = false;

HANDLE 打开进程(int 进程ID)
{

	return OpenProcess(PROCESS_ALL_ACCESS, FALSE, 进程ID);



}


bool 读内存(HANDLE 进程句柄, LPVOID 要读取的内存地址, LPVOID 存放数据的内存地址, SIZE_T 要读取的长度)
{
	

	SIZE_T OutSize=0;
	bool sta;
    sta = ReadProcessMemory(进程句柄, 要读取的内存地址, 存放数据的内存地址, 要读取的长度, &OutSize);
	if (sta == true && OutSize == 要读取的长度)
	{
		return true;
	}

	return false;

}
bool 读内存2(HANDLE 进程句柄, LPVOID 要读取的内存地址, LPVOID 存放数据的内存地址, SIZE_T 要读取的长度)
{
	SIZE_T OutSize = 0;
	bool sta;
	sta = ReadProcessMemory(进程句柄, 要读取的内存地址, 存放数据的内存地址, 要读取的长度, &OutSize);
	if (sta == true && OutSize == 要读取的长度)
	{
		return true;
	}

	return false;

}

int 读内存整数型(HANDLE 进程句柄, LPVOID 要读取的内存地址)
{
	
	int buff=0;
	bool sta;
	sta = 读内存(进程句柄, 要读取的内存地址,&buff, 4);
	if (sta==false)
	{
	   buff = -100;
	   return buff;
	}
	return buff;

}
int 读内存整数型2(HANDLE 进程句柄, LPVOID 要读取的内存地址)
{
	
	int buff = 0;
	bool sta;
	sta = 读内存(进程句柄, 要读取的内存地址, &buff, 4);
	if (sta == false)
	{
		buff = -100;
		return buff;
	}
	return buff;

}
short 读内存短整数型(HANDLE 进程句柄, LPVOID 要读取的内存地址)
{
	
	short  buff = 0;
	bool sta;
	sta = 读内存(进程句柄, 要读取的内存地址, &buff, 2);
	if (sta == false)
	{
		buff = -100;
		return buff;
	}
	return buff;



}
short 读内存短整数型2(HANDLE 进程句柄, LPVOID 要读取的内存地址)
{
	
	short  buff = 0;
	bool sta;
	sta = 读内存2(进程句柄, 要读取的内存地址, &buff, 2);
	if (sta == false)
	{
		buff = -100;
		return buff;
	}
	return buff;



}
unsigned short 读内存无符号短整数型(HANDLE 进程句柄, LPVOID 要读取的内存地址)
{
	
	unsigned short buff = 0;
	bool sta;
	sta = 读内存(进程句柄, 要读取的内存地址, &buff, 2);
	if (sta == false)
	{
		buff = -100;
		return buff;
	}
	return buff;
}
unsigned short 读内存无符号短整数型2(HANDLE 进程句柄, LPVOID 要读取的内存地址)
{
	
	unsigned short buff = 0;
	bool sta;
	sta = 读内存2(进程句柄, 要读取的内存地址, &buff, 2);
	if (sta == false)
	{
		buff = -100;
		return buff;
	}
	return buff;
}


long long 读内存长整数型(HANDLE 进程句柄, LPVOID 要读取的内存地址)
{
	
	long long buff = 0;
	bool sta;
	sta = 读内存(进程句柄, 要读取的内存地址, &buff, 8);
	if (sta == false)
	{
		buff = -100;
		return buff;
	}
	return buff;

}
long long 读内存长整数型2(HANDLE 进程句柄, LPVOID 要读取的内存地址)
{

	long long buff = 0;
	bool sta;
	sta = 读内存2(进程句柄, 要读取的内存地址, &buff, 8);
	if (sta == false)
	{
		buff = -100;
		return buff;
	}
	return buff;

}
float 读内存小数型(HANDLE 进程句柄, LPVOID 要读取的内存地址)
{
	float buff = 0;
	bool sta;
	sta = 读内存(进程句柄, 要读取的内存地址, &buff, 4);
	if (sta == false)
	{
		buff = -100.0f;
		return buff;
	}
	return buff;

}
float 读内存小数型2(HANDLE 进程句柄, LPVOID 要读取的内存地址)
{
	float buff = 0;
	bool sta;
	sta = 读内存2(进程句柄, 要读取的内存地址, &buff, 4);
	if (sta == false)
	{
		buff = -100.0f;
		return buff;
	}
	return buff;

}
double 读内存双精度小数型(HANDLE 进程句柄, LPVOID 要读取的内存地址)
{

	double buff = 0;
	bool sta;
	sta = 读内存(进程句柄, 要读取的内存地址, &buff, 8);
	if (sta == false)
	{
		buff = -100.0f;
		return buff;
	}
	return buff;
}
double 读内存双精度小数型2(HANDLE 进程句柄, LPVOID 要读取的内存地址)
{

	double buff = 0;
	bool sta;
	sta = 读内存2(进程句柄, 要读取的内存地址, &buff, 8);
	if (sta == false)
	{
		buff = -100.0f;
		return buff;
	}
	return buff;
}
char 读内存字节型(HANDLE 进程句柄, LPVOID 要读取的内存地址)
{

	char buff = 0;
	bool sta;
	sta = 读内存(进程句柄, 要读取的内存地址, &buff, 1);
	if (sta == false)
	{
		buff = -100;
		return buff;
	}
	return buff;
}
char 读内存字节型2(HANDLE 进程句柄, LPVOID 要读取的内存地址)
{

	char buff = 0;
	bool sta;
	sta = 读内存2(进程句柄, 要读取的内存地址, &buff, 1);
	if (sta == false)
	{
		buff = -100;
		return buff;
	}
	return buff;
}
int 读内存字节集(HANDLE 进程句柄, LPVOID 要读取的内存地址, int 要读取的长度, PVOID outbuff)
{

	bool sta;
	sta = 读内存(进程句柄, 要读取的内存地址, outbuff, 要读取的长度);
	if (sta == false)
	{
		return  -100;
	}
	return 1;

	

}
int 读内存字节集2(HANDLE 进程句柄, LPVOID 要读取的内存地址, int 要读取的长度, PVOID outbuff)
{

	bool sta;
	sta = 读内存2(进程句柄, 要读取的内存地址, outbuff, 要读取的长度);
	if (sta == false)
	{
		return  -100;
	}
	return 1;



}
wchar_t* 读内存文本型3(HANDLE 进程句柄, LPVOID 要读取的内存地址, int 要读取的文本类型)
{
	char buff = 1;
	wchar_t ubuff[2] = { 1,1 };
	SIZE_T OutSize;
	bool sta;
	wchar_t* str = L"";
	PVOID address = 要读取的内存地址;
	LPVOID lstr = L"";
	int len = 0;
	//CString a = L"";


		if (!IsBadReadPtr(要读取的内存地址, 8)) 
		{
			str = (wchar_t*)要读取的内存地址;
			return str;
		}
	
	return L"";
	
	/*if (要读取的文本类型 == 0)
	{
		while (buff != 0)
		{
			sta = ReadProcessMemory(进程句柄, (PVOID)((LONGLONG)address + len), &buff, 1, &OutSize);
			if (sta == false)
			{
				buff = -100;
				return L"";
			}
			len = len + 1;
		}
		sta = ReadProcessMemory(进程句柄, address, lstr, len, &OutSize);
		if (sta == false)
		{
			return L"";
		}
		return (LPCTSTR)lstr;
	}
	if (要读取的文本类型 == 1)
	{
		while (ubuff[0] != 0 && ubuff[1] != 0)
		{
			sta = ReadProcessMemory(进程句柄, (PVOID)((LONGLONG)address + len), &ubuff, 2, &OutSize);
			if (sta == false)
			{
				return L"";
			}
			len = len + 2;
		}
		sta = ReadProcessMemory(进程句柄, address, lstr, len, &OutSize);
		
		if (sta == false)
		{
			return L"";
		}
		return (LPCTSTR)lstr;
	}
	return L"";*/
}
int 读内存文本型2(HANDLE 进程句柄, LPVOID 要读取的内存地址, int 要读取的文本类型, TCHAR*(*outbuff))
{
	char buff = 1;
	wchar_t ubuff[2] = { 1,1 };
	SIZE_T OutSize;
	bool sta;
	PVOID address = 要读取的内存地址;
	int len = 0;
	TCHAR* Str = _T("");
	
		if (!IsBadReadPtr(要读取的内存地址, 8))
		{
			Str = (wchar_t*)要读取的内存地址;
			*outbuff = Str;
			return wcslen(Str);
		}
	
	*outbuff = L"";
	return buff = -100;
	/*if (要读取的文本类型 == 0)
	{
		while (buff != 0)
		{
			sta = ReadProcessMemory(进程句柄, (PVOID)((LONGLONG)address + len), &buff, 1, &OutSize);
			if (sta == false)
			{
				buff = -100;
				return buff;
			}
			len = len + 1;
		}
		sta = ReadProcessMemory(进程句柄, address, outbuff, len, &OutSize);
		if (sta == false)
		{
			return -100;
		}
		return len;
	}
	if (要读取的文本类型 == 1)
	{
		while (ubuff[0] != 0 && ubuff[1] != 0)
		{
			sta = ReadProcessMemory(进程句柄, (PVOID)((LONGLONG)address + len), &ubuff, 2, &OutSize);
			if (sta == false)
			{
				return -100;
			}
			len = len + 2;
		}
		sta = ReadProcessMemory(进程句柄, address, outbuff, len, &OutSize);
		if (sta == false)
		{
			return  -100;
		}
		return len;
	}
	return  -100;
	*/
}
int 读内存文本型(HANDLE 进程句柄, LPVOID 要读取的内存地址, int 要读取的文本类型, TCHAR*(*outbuff))
{
	
	char buff=1;
	wchar_t ubuff[2] = {1,1};
	SIZE_T OutSize;
	bool sta;
	PVOID address = 要读取的内存地址;
	int len=0;
	wchar_t* Str;

		if (!IsBadReadPtr(要读取的内存地址, 8))
		{
			Str = (wchar_t*)要读取的内存地址;
			*outbuff = Str;
			return wcslen(Str);
		}

	*outbuff = L"";
	return buff = -100;
	/*if (要读取的文本类型==0)
	{
		while (buff!=0)
		{			
			sta = ReadProcessMemory(进程句柄, (PVOID)((LONGLONG)address+len), &buff, 1, &OutSize);
			if (sta == false)
			{
				buff = -100;
				return buff;
			}
			len = len + 1;			
		}		
		sta = ReadProcessMemory(进程句柄, address, outbuff, len, &OutSize);
		if (sta == false)
		{			
			return -100;
		}
		return len;	
	}
	if (要读取的文本类型 == 1)
	{
		while (ubuff[0] != 0 && ubuff[1] != 0)
		{
			sta = ReadProcessMemory(进程句柄, (PVOID)((LONGLONG)address + len), &ubuff, 2, &OutSize);
			if (sta == false)
			{
				return -100;
			}
			len = len + 2;
		}
		sta = ReadProcessMemory(进程句柄, address, outbuff, len, &OutSize);
		if (sta == false)
		{			
			return  -100;
		}
		return len;
	}
	return  -100;*/
}

bool 写内存(HANDLE 进程句柄, LPVOID 要写入的内存地址, LPVOID 要写入的数据所在地址, SIZE_T 要写入的长度)
{
	
	bool sta;
	SIZE_T OutSize = 0;
	DWORD oldprotect;
	sta = WriteProcessMemory(进程句柄, 要写入的内存地址, 要写入的数据所在地址, 要写入的长度, &OutSize);
	if (sta == true && OutSize == 要写入的长度)
	{
		return true;
	}

	VirtualProtectEx(进程句柄, 要写入的内存地址, 1, PAGE_EXECUTE_READWRITE, &oldprotect);

	sta = WriteProcessMemory(进程句柄, 要写入的内存地址, 要写入的数据所在地址, 要写入的长度, &OutSize);

	VirtualProtectEx(进程句柄, 要写入的内存地址, 1, oldprotect, &oldprotect);

	if (sta == true && OutSize == 要写入的长度)
	{
		return true;
	}

	return false;

}


bool 写内存2(HANDLE 进程句柄, LPVOID 要写入的内存地址, LPVOID 要写入的数据所在地址, SIZE_T 要写入的长度)
{

	bool sta;
	SIZE_T OutSize = 0;
	DWORD oldprotect;
	sta = WriteProcessMemory(进程句柄, 要写入的内存地址, 要写入的数据所在地址, 要写入的长度, &OutSize);
	if (sta == true && OutSize == 要写入的长度)
	{
		return true;
	}

	VirtualProtectEx(进程句柄, 要写入的内存地址, 1, PAGE_EXECUTE_READWRITE, &oldprotect);

	sta = WriteProcessMemory(进程句柄, 要写入的内存地址, 要写入的数据所在地址, 要写入的长度, &OutSize);

	VirtualProtectEx(进程句柄, 要写入的内存地址, 1, oldprotect, &oldprotect);

	if (sta == true && OutSize == 要写入的长度)
	{
		return true;
	}

	return false;

}


bool 写内存整数型(HANDLE 进程句柄, LPVOID 要写入的内存地址, int wirtebuff)
{

	bool sta;
	sta = 写内存(进程句柄, 要写入的内存地址, &wirtebuff, 4);
	return sta;

}
bool 写内存整数型2(HANDLE 进程句柄, LPVOID 要写入的内存地址, int wirtebuff)
{

	bool sta;
	sta = 写内存2(进程句柄, 要写入的内存地址, &wirtebuff, 4);
	return sta;

}
bool 写内存短整数型(HANDLE 进程句柄, LPVOID 要写入的内存地址, short wirtebuff)
{

	bool sta;
	sta = 写内存(进程句柄, 要写入的内存地址, &wirtebuff, 2);
	return sta;

}
bool 写内存短整数型2(HANDLE 进程句柄, LPVOID 要写入的内存地址, short wirtebuff)
{

	bool sta;
	sta = 写内存2(进程句柄, 要写入的内存地址, &wirtebuff, 2);
	return sta;

}
bool 写内存无符号短整数型(HANDLE 进程句柄, LPVOID 要写入的内存地址, unsigned short wirtebuff)
{

	bool sta;
	sta = 写内存(进程句柄, 要写入的内存地址, &wirtebuff, 2);
	return sta;

}
bool 写内存无符号短整数型2(HANDLE 进程句柄, LPVOID 要写入的内存地址, unsigned short wirtebuff)
{

	bool sta;
	sta = 写内存2(进程句柄, 要写入的内存地址, &wirtebuff, 2);
	return sta;

}
bool 写内存长整数型(HANDLE 进程句柄, LPVOID 要写入的内存地址, long long wirtebuff)
{
	bool sta;
	sta = 写内存(进程句柄, 要写入的内存地址, &wirtebuff, 8);
	return sta;
}
bool 写内存长整数型2(HANDLE 进程句柄, LPVOID 要写入的内存地址, long long wirtebuff)
{
	bool sta;
	sta = 写内存2(进程句柄, 要写入的内存地址, &wirtebuff, 8);
	return sta;
}
bool 写内存小数型(HANDLE 进程句柄, LPVOID 要写入的内存地址, float wirtebuff)
{

	bool sta;
	sta = 写内存(进程句柄, 要写入的内存地址, &wirtebuff, 4);
	return sta;


}
bool 写内存小数型2(HANDLE 进程句柄, LPVOID 要写入的内存地址, float wirtebuff)
{

	bool sta;
	sta = 写内存2(进程句柄, 要写入的内存地址, &wirtebuff, 4);
	return sta;


}
bool 写内存双精度小数型(HANDLE 进程句柄, LPVOID 要写入的内存地址, double wirtebuff)
{

	bool sta;
	sta = 写内存(进程句柄, 要写入的内存地址, &wirtebuff, 8);
	return sta;


}
bool 写内存双精度小数型2(HANDLE 进程句柄, LPVOID 要写入的内存地址, double wirtebuff)
{

	bool sta;
	sta = 写内存2(进程句柄, 要写入的内存地址, &wirtebuff, 8);
	return sta;


}
bool 写内存字节集(HANDLE 进程句柄, LPVOID 要写入的内存地址, LPVOID 要写入的数据所在地址, SIZE_T 要写入的长度)
{


	bool sta;
	sta = 写内存(进程句柄, 要写入的内存地址, 要写入的数据所在地址, 要写入的长度);
	return sta;


}
bool 写内存字节集2(HANDLE 进程句柄, LPVOID 要写入的内存地址, LPVOID 要写入的数据所在地址, SIZE_T 要写入的长度)
{


	bool sta;
	sta = 写内存2(进程句柄, 要写入的内存地址, 要写入的数据所在地址, 要写入的长度);
	return sta;


}
bool 写内存字节型(HANDLE 进程句柄, LPVOID 要写入的内存地址, char wirtebuff)
{
	bool sta;
	sta = 写内存(进程句柄, 要写入的内存地址, &wirtebuff, 1);
	return sta;
}
bool 写内存字节型2(HANDLE 进程句柄, LPVOID 要写入的内存地址, char wirtebuff)
{
	bool sta;
	sta = 写内存2(进程句柄, 要写入的内存地址, &wirtebuff, 1);
	return sta;
}
CString 取运行目录()
{
	TCHAR exeFullPath[MAX_PATH];
	GetModuleFileName(NULL, exeFullPath, MAX_PATH);
	CString str = exeFullPath;
	int a = str.ReverseFind('\\');
	str = str.Left(a);
	return  str;
}

HANDLE 打开文件(LPCWSTR 文件全路径)
{
	HANDLE 文件句柄;
	文件句柄=CreateFileW(文件全路径, FILE_ALL_ACCESS, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	return 文件句柄;
}

int 写文件(HANDLE 文件句柄,LPCVOID 要写入的数据所在地址,DWORD 要写入的字节数)
{
	DWORD outsize;
	bool sta;
	sta=WriteFile(文件句柄, 要写入的数据所在地址, 要写入的字节数, &outsize, NULL);
	if (sta==true)
	{
		return outsize;
	}

	return 0;

}
int 读文件(HANDLE 文件句柄, LPVOID 要读出的数据所在地址, DWORD 要读出的字节数)
{
	DWORD outsize;
	bool sta;
	sta=ReadFile(文件句柄, 要读出的数据所在地址, 要读出的字节数, &outsize, NULL);
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
	string 返回文本;
	DWORD dwBytesRead, dwBytesToRead, tmpLen;

	pFile = CreateFileW(filePath, FILE_ALL_ACCESS, 0, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	if (pFile == INVALID_HANDLE_VALUE)
	{
		printf("open file error!\n");
		CloseHandle(pFile);
		return FALSE;
	}

	fileSize = GetFileSize(pFile, NULL);          //得到文件的大小

	buffer = (char*)malloc(fileSize);
	ZeroMemory(buffer, fileSize);
	dwBytesToRead = fileSize;
	dwBytesRead = 0;
	tmpBuf = buffer;

	do {                                       //循环读文件，确保读出完整的文件    

		ReadFile(pFile, tmpBuf, dwBytesToRead, &dwBytesRead, NULL);

		if (dwBytesRead == 0)
		{
			break;
		}
			
		dwBytesToRead -= dwBytesRead;
		tmpBuf += dwBytesRead;

	} while (dwBytesToRead > 0);

	//  TODO 处理读到的数据 buffer
	OutputDebugStringW(CString(buffer));
	返回文本 = buffer;
	free(buffer);
	CloseHandle(pFile);

	return 返回文本;
}


LPVOID 申请内存2(HANDLE 进程句柄, int 要申请的内存大小)
{



	return VirtualAllocEx(进程句柄, 0, 要申请的内存大小, MEM_COMMIT, PAGE_EXECUTE_READWRITE);




}


bool 释放内存2(HANDLE 进程句柄, LPVOID 释放的地址,int 内存大小)
{



	return VirtualFreeEx(进程句柄, 释放的地址, 内存大小, 32768);




}


