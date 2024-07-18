#include "内存_通用数据.h"
#include "ntsecapi.h"
#define STATUS_INFO_LENGTH_MISMATCH ((NTSTATUS)0xC0000004L)
typedef NTSTATUS(WINAPI* ZWQUERYSYSTEMINFORMATION)(DWORD, PVOID, DWORD, PDWORD);
typedef enum _OBJECT_INFORMATION_CLASS {
	ObjectBasicInformation,
	ObjectNameInformation,
	ObjectTypeInformation,
	ObjectAllInformation,
	ObjectDataInformation,
} OBJECT_INFORMATION_CLASS;
typedef NTSTATUS(NTAPI* NTQUERYOBJECT)(
	HANDLE Handle,
	OBJECT_INFORMATION_CLASS ObjectInformationClass,
	PVOID ObjectInformation,
	ULONG ObjectInformationLength,
	PULONG ReturnLength
	);

typedef struct _OBJECT_NAME_INFORMATION {
	UNICODE_STRING Name;
} OBJECT_NAME_INFORMATION, * POBJECT_NAME_INFORMATION;

typedef struct _SYSTEM_HANDLE_INFORMATION
{
	ULONG ProcessId;
	UCHAR ObjectTypeNumber;
	UCHAR Flags;
	USHORT Handle;
	PVOID Object;
	ACCESS_MASK GrantedAccess;
}SYSTEM_HANDLE_INFORMATION, * PSYSTEM_HANDLE_INFORMATION;

typedef struct _SYSTEM_HANDLE_INFORMATION_EX
{
	ULONG NumberOfHandles;
	SYSTEM_HANDLE_INFORMATION Information[1];
}SYSTEM_HANDLE_INFORMATION_EX, * PSYSTEM_HANDLE_INFORMATION_EX;
#define SystemHandleInformation 0x10  // 16


ZWQUERYSYSTEMINFORMATION ZwQuerySystemInformation;
NTQUERYOBJECT    NtQueryObject;

LPVOID GetSystemProcessHandleInfo();
bool EnumObjInfo(LPVOID pBuffer, DWORD pid);

LPVOID GetSystemProcessHandleInfo()
{
	ULONG cbBuffer = 0x4000;
	LPVOID pBuffer = NULL;
	NTSTATUS sts;
	do
	{
		pBuffer = malloc(cbBuffer);
		if (pBuffer == NULL)
		{

			return NULL;
		}
		memset(pBuffer, 0, cbBuffer);

		sts = ZwQuerySystemInformation(SystemHandleInformation, pBuffer, cbBuffer, NULL);
		if (sts == STATUS_INFO_LENGTH_MISMATCH)
		{
			free(pBuffer);
			pBuffer = NULL;
			cbBuffer = cbBuffer + 0x4000; // 初始分配的空间不足+4000h
		}
	} while (sts == STATUS_INFO_LENGTH_MISMATCH);
	return pBuffer;
}

bool EnumObjInfo(LPVOID pBuffer, DWORD pid)
{
	char szType[128] = { 0 };
	char szName[512] = { 0 };
	DWORD dwFlags = 0;

	POBJECT_NAME_INFORMATION pNameInfo;
	POBJECT_NAME_INFORMATION pNameType;

	PSYSTEM_HANDLE_INFORMATION_EX pInfo = (PSYSTEM_HANDLE_INFORMATION_EX)pBuffer;
	ULONG OldPID = 0;
	for (DWORD i = 0; i < pInfo->NumberOfHandles; i++)
	{
		if (OldPID != pInfo->Information[i].ProcessId)
		{
			if (pInfo->Information[i].ProcessId == pid)
			{
				HANDLE newHandle = (HANDLE)pInfo->Information[i].Handle;
				//dbgPrint("pid=%d newHandle=%d", pid, newHandle);
				NTSTATUS status1 = NtQueryObject(newHandle, ObjectNameInformation, szName, 512, &dwFlags);
				NTSTATUS status2 = NtQueryObject(newHandle, ObjectTypeInformation, szType, 128, &dwFlags);
				if (status1 != 0xc0000008 && status2 != 0xc0000008)
				{
					pNameInfo = (POBJECT_NAME_INFORMATION)szName;
					pNameType = (POBJECT_NAME_INFORMATION)szType;

					CString str;
					str.Format(L"%wZ", pNameType);
					if (str == "Mutant")
					{
						CString str2;
						str2.Format(L"%wZ", pNameInfo);
				
						if (str2.Find(L"5D2D1767") != -1)
						{
						
							CloseHandle(newHandle);
							return true;
						}
						if (str2.Find(L"0DF11825") != -1)
						{
						
							CloseHandle(newHandle);
							return true;
						}
						if (str2.Find(L"A5DFEC3F") != -1)
						{
							CloseHandle(newHandle);
							return true;
						}
					}
				}

			}
		}
	}
	return false;
}



void 测试多开()
{
	ZwQuerySystemInformation = (ZWQUERYSYSTEMINFORMATION)GetProcAddress(GetModuleHandle(TEXT("ntdll.dll")), "ZwQuerySystemInformation");
	NtQueryObject = (NTQUERYOBJECT)GetProcAddress(GetModuleHandle(TEXT("ntdll.dll")), "NtQueryObject");

	for (size_t i = 0; i < 30; i++)
	{
	//	MyTrace(L"尝试多开！");
		if (EnumObjInfo(GetSystemProcessHandleInfo(), GetCurrentProcessId()) == true)
		{
			MyTrace(L"多开成功！");
			return;
		}
		Sleep(1000);
	}


}



DWORD64 距离计算x(DWORD64 x1, DWORD64 y1,  DWORD64 x2, DWORD64 y2)
{
	DWORD64 a = (DWORD64)labs(x1 - x2) * (DWORD64)labs(x1 - x2);
	DWORD64 b = (DWORD64)labs(y1 - y2) * (DWORD64)labs(y1 - y2);

	return DWORD64(sqrt(a+b));
}


int 距离计算2(坐标_ 源坐标, 坐标_ 目的坐标)
{
	float x = 源坐标.x - 目的坐标.x;
	float y = 源坐标.y - 目的坐标.y;
	float z = 源坐标.z - 目的坐标.z;
	return int(sqrtf(x * x + y * y + z * z));
}
int 距离计算(int x1, int y1, int z1, int x2, int y2, int z2)
{
	float x = x1 - x2;
	float y = y1 - y2;
	float z = z1 - z2;
	return int(sqrtf(float(x * x + y * y + z * z)));
}
float 距离计算3(float x1, float y1, float z1, float x2, float y2, float z2)
{
	float x = x1 - x2;
	float y = y1 - y2;
	float z = z1 - z2;
	return sqrtf(float(x * x + y * y + z * z));
}

SIZE_T getMemoryUse()
{
	//GlobalMemoryStatus();
	HANDLE handle = GetCurrentProcess();
	PROCESS_MEMORY_COUNTERS pmc;
	::GetProcessMemoryInfo(handle, &pmc, sizeof(pmc));

	//MyTrace(L"内存使用=%dMb,峰值内存使用=%dMb,虚拟内存使用=%dMb,峰值虚拟内存使用=%dMb", pmc.WorkingSetSize / 1000 / 1024, pmc.PeakWorkingSetSize / 1000 / 1024,
	//	pmc.PagefileUsage / 1000 / 1024, pmc.PeakPagefileUsage / 1000 / 1024);
	return pmc.WorkingSetSize;
}





//LPVOID GetSystemProcessHandleInfo()
//{
//	ULONG cbBuffer = 0x4000;
//	LPVOID pBuffer = NULL;
//	NTSTATUS sts;
//	do
//	{
//		pBuffer = malloc(cbBuffer);
//		if (pBuffer == NULL)
//		{
//
//			return NULL;
//		}
//		memset(pBuffer, 0, cbBuffer);
//
//		sts = ZwQuerySystemInformation(SystemHandleInformation, pBuffer, cbBuffer, NULL);
//		if (sts == STATUS_INFO_LENGTH_MISMATCH)
//		{
//			free(pBuffer);
//			pBuffer = NULL;
//			cbBuffer = cbBuffer + 0x4000; // 初始分配的空间不足+4000h
//		}
//	} while (sts == STATUS_INFO_LENGTH_MISMATCH);
//	return pBuffer;
//}
//
//bool EnumObjInfo(LPVOID pBuffer, DWORD pid)
//{
//	char szType[128] = { 0 };
//	char szName[512] = { 0 };
//	DWORD dwFlags = 0;
//
//	POBJECT_NAME_INFORMATION pNameInfo;
//	POBJECT_NAME_INFORMATION pNameType;
//
//	PSYSTEM_HANDLE_INFORMATION_EX pInfo = (PSYSTEM_HANDLE_INFORMATION_EX)pBuffer;
//	ULONG OldPID = 0;
//	for (DWORD i = 0; i < pInfo->NumberOfHandles; i++)
//	{
//		if (pInfo->Handles[i].UniqueProcessId == pid)
//		{
//			HANDLE newHandle = (HANDLE)pInfo->Handles[i].HandleValue;
//			MyTrace(L"pid=%d newHandle=%d", pid, newHandle);
//			NTSTATUS status1 = NtQueryObject(newHandle, ObjectNameInformation, szName, 512, &dwFlags);
//			NTSTATUS status2 = NtQueryObject(newHandle, ObjectTypeInformation, szType, 128, &dwFlags);
//			if (status1 != 0xc0000008 && status2 != 0xc0000008)
//			{
//				pNameInfo = (POBJECT_NAME_INFORMATION)szName;
//				pNameType = (POBJECT_NAME_INFORMATION)szType;
//
//				CString str;
//
//				str.Format(L"%wZ", pNameType);
//				if (str == "Mutant")
//				{
//					CString str2;
//					str2.Format(L"%wZ", pNameInfo);
//
//					if (str2.Find(L"5D2D1767") != -1)
//					{
//
//						CloseHandle(newHandle);
//						return true;
//					}
//					if (str2.Find(L"0DF11825") != -1)
//					{
//
//						CloseHandle(newHandle);
//						return true;
//					}
//					if (str2.Find(L"A5DFEC3F") != -1)
//					{
//						CloseHandle(newHandle);
//						return true;
//					}
//				}
//			}
//
//		}
//	}
//	return 0;
//}
//
//
//void 测试多开()
//{
//		ZwQuerySystemInformation = (ZWQUERYSYSTEMINFORMATION)GetProcAddress(GetModuleHandle(TEXT("ntdll.dll")), "ZwQuerySystemInformation");
//		NtQueryObject = (NTQUERYOBJECT)GetProcAddress(GetModuleHandle(TEXT("ntdll.dll")), "NtQueryObject");
//
//
//
//	for (size_t i = 0; i < 30; i++)
//	{
//		MyTrace(L"尝试多开！");
//		if (EnumObjInfo(GetSystemProcessHandleInfo(), GetCurrentProcessId()) == true)
//		{
//			MyTrace(L"多开成功！");
//			break;
//		}
//		Sleep(1000);
//	}
//
//}


//float  GetDis(float X1, float Y1, float Z1)
//{
//
//	//坐标_ 本人坐标 = 本人::取坐标();
//
//	//float x = 本人坐标.x - X1;
//	//float y = 本人坐标.y - Y1;
//	//float z = 本人坐标.z - Z1;
//	//return sqrtf(float(x * x + y * y + z * z));
//}

//float  GetDis1(float X1, float Y1, float Z1)
//{
//
//	坐标_ 本人坐标 = 本人::取坐标();
//
//	float x = 本人坐标.x - X1;
//	float y = 本人坐标.y - Y1;
//	float z = 本人坐标.z - Z1;
//	return sqrtf(float(x * x + y * y + z * z))/100;
//}
//typedef unsigned __int64 uint64_t;
//
//
//DWORD 取相对角度(float fx, float fy)
//{
//	//坐标_ 角色坐标 = 本人::取坐标();
//	return DWORD(Get_Rel_Angle(角色坐标.x, 角色坐标.y, fx, fy) * 0.00549317);
//}
//
