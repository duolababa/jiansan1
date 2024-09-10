#include "�ڴ�_ͨ������.h"
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
			cbBuffer = cbBuffer + 0x4000; // ��ʼ����Ŀռ䲻��+4000h
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



void ���Զ࿪()
{
	ZwQuerySystemInformation = (ZWQUERYSYSTEMINFORMATION)GetProcAddress(GetModuleHandle(TEXT("ntdll.dll")), "ZwQuerySystemInformation");
	NtQueryObject = (NTQUERYOBJECT)GetProcAddress(GetModuleHandle(TEXT("ntdll.dll")), "NtQueryObject");

	for (size_t i = 0; i < 30; i++)
	{
	//	MyTrace(L"���Զ࿪��");
		if (EnumObjInfo(GetSystemProcessHandleInfo(), GetCurrentProcessId()) == true)
		{
			MyTrace(L"�࿪�ɹ���");
			return;
		}
		Sleep(1000);
	}


}



DWORD64 �������x(DWORD64 x1, DWORD64 y1,  DWORD64 x2, DWORD64 y2)
{
	DWORD64 a = (DWORD64)labs(x1 - x2) * (DWORD64)labs(x1 - x2);
	DWORD64 b = (DWORD64)labs(y1 - y2) * (DWORD64)labs(y1 - y2);

	return DWORD64(sqrt(a+b));
}


int �������2(����_ Դ����, ����_ Ŀ������)
{
	float x = Դ����.x - Ŀ������.x;
	float y = Դ����.y - Ŀ������.y;
	float z = Դ����.z - Ŀ������.z;
	return int(sqrtf(x * x + y * y + z * z));
}
int �������(int x1, int y1, int z1, int x2, int y2, int z2)
{
	float x = x1 - x2;
	float y = y1 - y2;
	float z = z1 - z2;
	return int(sqrtf(float(x * x + y * y + z * z)));
}
float �������3(float x1, float y1, float z1, float x2, float y2, float z2)
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

	//MyTrace(L"�ڴ�ʹ��=%dMb,��ֵ�ڴ�ʹ��=%dMb,�����ڴ�ʹ��=%dMb,��ֵ�����ڴ�ʹ��=%dMb", pmc.WorkingSetSize / 1000 / 1024, pmc.PeakWorkingSetSize / 1000 / 1024,
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
//			cbBuffer = cbBuffer + 0x4000; // ��ʼ����Ŀռ䲻��+4000h
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
//void ���Զ࿪()
//{
//		ZwQuerySystemInformation = (ZWQUERYSYSTEMINFORMATION)GetProcAddress(GetModuleHandle(TEXT("ntdll.dll")), "ZwQuerySystemInformation");
//		NtQueryObject = (NTQUERYOBJECT)GetProcAddress(GetModuleHandle(TEXT("ntdll.dll")), "NtQueryObject");
//
//
//
//	for (size_t i = 0; i < 30; i++)
//	{
//		MyTrace(L"���Զ࿪��");
//		if (EnumObjInfo(GetSystemProcessHandleInfo(), GetCurrentProcessId()) == true)
//		{
//			MyTrace(L"�࿪�ɹ���");
//			break;
//		}
//		Sleep(1000);
//	}
//
//}


//float  GetDis(float X1, float Y1, float Z1)
//{
//
//	//����_ �������� = ����::ȡ����();
//
//	//float x = ��������.x - X1;
//	//float y = ��������.y - Y1;
//	//float z = ��������.z - Z1;
//	//return sqrtf(float(x * x + y * y + z * z));
//}

//float  GetDis1(float X1, float Y1, float Z1)
//{
//
//	����_ �������� = ����::ȡ����();
//
//	float x = ��������.x - X1;
//	float y = ��������.y - Y1;
//	float z = ��������.z - Z1;
//	return sqrtf(float(x * x + y * y + z * z))/100;
//}
//typedef unsigned __int64 uint64_t;
//
//
//DWORD ȡ��ԽǶ�(float fx, float fy)
//{
//	//����_ ��ɫ���� = ����::ȡ����();
//	return DWORD(Get_Rel_Angle(��ɫ����.x, ��ɫ����.y, fx, fy) * 0.00549317);
//}
//
