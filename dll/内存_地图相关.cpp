#include "�ڴ�_��ͼ���.h"

int ��ͼ::ȡ��ͼID()
{
	return R_DW(��Ϸģ�� + ��ַ_����_��ͼID);
}
int ��ͼ::ȡ��ǰ��½ID()
{
	INT64 MapAddr = getMapResAddrById(��ͼ::ȡ��ͼID());
	return R_BYTE(MapAddr + 88);
}

void ��ͼ::����(DWORD ����ID)
{
	INT64 ��_RCX = R_QW(��Ϸģ�� + ��ַ_����_����rcx);
	INT64 ��_dCALL = ��Ϸģ�� + ��ַ_����_����call;
	UCHAR pBuff[0x140] = { 0 };
	W_QW((ULONG64)&pBuff[0x0], 7773890805770);
	W_QW((ULONG64)&pBuff[0x8], -4294967296);
	W_QW((ULONG64)&pBuff[0x20], (ULONG64)&pBuff + 80);
	W_DW((ULONG64)&pBuff[0x128], 0xCF11);// 6��5�� linjinmao �� 2.276719213937e+014); 
	W_DW((ULONG64)&pBuff[0x12C], 1);
	W_DW((ULONG64)&pBuff[0x134], ����ID);
	W_DW((ULONG64)&pBuff[0x13C], 0x300);
	MainUniversalCALL2(��_RCX, (ULONG_PTR)pBuff, ��_dCALL);
}
void ��ͼ::�����Ѽ���͵�(vector<���͵���Ϣ_>& vsk)
{
	���͵���Ϣ_ temp���͵�;
	vsk.clear();
	DWORD dtotal = R_W(��Ϸģ�� + gb_CurTeleportList);
	INT64 dstart = ��Ϸģ�� + gb_CurTeleportList + 2;
	for (DWORD i = 0; i < dtotal; i++)
	{
		DWORD  dTeleportId = R_DW(dstart + i * 4);
		INT64 dTeleportResAddr = getSquareResAddrById(dTeleportId);
		INT64 dTeleportNameAddr = R_QW(dTeleportResAddr + 0x10);
		DWORD Mapid = R_DW(dTeleportResAddr + go_PortalMapId);
		CString cTeleportName = L"��";
		string temp = UnicodeToAnsi(R_CString(dTeleportNameAddr));
		cTeleportName = CString(temp.c_str());
		temp���͵�.cTeleportName = cTeleportName;
		temp���͵�.dTeleportId = dTeleportId;
		temp���͵�.Mapid = Mapid;
		vsk.push_back(temp���͵�);
		/*wchar_t buf[100];
		swprintf(buf, L"������͵� %s %X\r\n", cTeleportName, dTeleportId);*/

	}
}
bool ��ͼ::���͵��Ƿ񼤻�(DWORD ���͵�ID)
{
	vector<���͵���Ϣ_>vsk;
	��ͼ::�����Ѽ���͵�(vsk);
	for (size_t i = 0; i < vsk.size(); i++)
	{
		if (���͵�ID == vsk[i].dTeleportId)
		{
			return true;
		}
	}
	return false;
}
bool ���͵�mark(const ���͵���Ϣ_& o1, const ���͵���Ϣ_& o2)
{
	return o1.Mapid > o2.Mapid;

}
void ��ͼ::ȡĿ���ͼ���͵�(DWORD ��ͼID, vector<���͵���Ϣ_>& vsk)
{
	vector<���͵���Ϣ_>�Ѽ���͵�;
	��ͼ::�����Ѽ���͵�(�Ѽ���͵�);
	for (size_t i = 0; i < �Ѽ���͵�.size(); i++)
	{
		if (�Ѽ���͵�[i].Mapid == ��ͼID)
		{
			vsk.push_back(�Ѽ���͵�[i]);
		}
	}

	if (vsk.size() == 0)
	{
		if (��ͼID == 10801)
		{
			for (size_t i = 0; i < �Ѽ���͵�.size(); i++)
			{
				if (�Ѽ���͵�[i].dTeleportId == 900209)
				{
					vsk.push_back(�Ѽ���͵�[i]);
					break;
				}
			}
			if (vsk.size() == 0)
			{
				for (size_t i = 0; i < �Ѽ���͵�.size(); i++)
				{
					if (�Ѽ���͵�[i].Mapid == 10815)
					{
						vsk.push_back(�Ѽ���͵�[i]);
					}
				}
			}
			::sort(vsk.begin(), vsk.end(), ���͵�mark);
		}
		if (��ͼID == 10816)
		{
			for (size_t i = 0; i < �Ѽ���͵�.size(); i++)
			{
				if (�Ѽ���͵�[i].Mapid == 10801)
				{
					vsk.push_back(�Ѽ���͵�[i]);
				}
			}
			::sort(vsk.begin(), vsk.end(), ���͵�mark);
		}
		if (��ͼID == 10818)
		{
			for (size_t i = 0; i < �Ѽ���͵�.size(); i++)
			{
				if (�Ѽ���͵�[i].Mapid == 10817)
				{
					vsk.push_back(�Ѽ���͵�[i]);
				}
			}
			::sort(vsk.begin(), vsk.end(), ���͵�mark);
		}
		if (��ͼID == 10804)
		{
			for (size_t i = 0; i < �Ѽ���͵�.size(); i++)
			{
				if (�Ѽ���͵�[i].dTeleportId == 900461)
				{
					vsk.push_back(�Ѽ���͵�[i]);
				}
			}
			::sort(vsk.begin(), vsk.end(), ���͵�mark);
		}
		if (��ͼID == 10725)
		{
			for (size_t i = 0; i < �Ѽ���͵�.size(); i++)
			{
				if (�Ѽ���͵�[i].dTeleportId == 0xDBE86)
				{
					vsk.push_back(�Ѽ���͵�[i]);
					break;
				}
			}
			if (vsk.size() == 0)
			{
				for (size_t i = 0; i < �Ѽ���͵�.size(); i++)
				{
					if (�Ѽ���͵�[i].Mapid == 10723)
					{
						vsk.push_back(�Ѽ���͵�[i]);
					}
				}
			}
			::sort(vsk.begin(), vsk.end(), ���͵�mark);
		}
		if (��ͼID == 10423)
		{
			for (size_t i = 0; i < �Ѽ���͵�.size(); i++)
			{
				if (�Ѽ���͵�[i].dTeleportId == 900901)
				{
					vsk.push_back(�Ѽ���͵�[i]);
					break;
				}
			}
			if (vsk.size() == 0)
			{
				for (size_t i = 0; i < �Ѽ���͵�.size(); i++)
				{
					if (�Ѽ���͵�[i].Mapid == 10401)
					{
						vsk.push_back(�Ѽ���͵�[i]);
					}
				}
			}
			::sort(vsk.begin(), vsk.end(), ���͵�mark);
		}
		if (��ͼID == 10423)
		{
			for (size_t i = 0; i < �Ѽ���͵�.size(); i++)
			{
				if (�Ѽ���͵�[i].dTeleportId == 900922)
				{
					vsk.push_back(�Ѽ���͵�[i]);
					break;
				}
			}
			if (vsk.size() == 0)
			{
				for (size_t i = 0; i < �Ѽ���͵�.size(); i++)
				{
					if (�Ѽ���͵�[i].Mapid == 10422)
					{
						vsk.push_back(�Ѽ���͵�[i]);
					}
				}
			}
			::sort(vsk.begin(), vsk.end(), ���͵�mark);
		}
		if (��ͼID == 10424)
		{
			for (size_t i = 0; i < �Ѽ���͵�.size(); i++)
			{
				if (�Ѽ���͵�[i].dTeleportId == 0xDBF26)
				{
					vsk.push_back(�Ѽ���͵�[i]);
					break;
				}
			}
			if (vsk.size() == 0)
			{
				for (size_t i = 0; i < �Ѽ���͵�.size(); i++)
				{
					if (�Ѽ���͵�[i].Mapid == 10401)
					{
						vsk.push_back(�Ѽ���͵�[i]);
					}
				}
			}
			::sort(vsk.begin(), vsk.end(), ���͵�mark);
		}
		if (��ͼID == 10426)
		{
			for (size_t i = 0; i < �Ѽ���͵�.size(); i++)
			{
				if (�Ѽ���͵�[i].dTeleportId == 0xDBF27)
				{
					vsk.push_back(�Ѽ���͵�[i]);
					break;
				}
			}
			if (vsk.size() == 0)
			{
				for (size_t i = 0; i < �Ѽ���͵�.size(); i++)
				{
					if (�Ѽ���͵�[i].Mapid == 10401)
					{
						vsk.push_back(�Ѽ���͵�[i]);
					}
				}
			}
			::sort(vsk.begin(), vsk.end(), ���͵�mark);
		}
		if (��ͼID == 11102)
		{
			for (size_t i = 0; i < �Ѽ���͵�.size(); i++)
			{
				if (�Ѽ���͵�[i].dTeleportId == 0xDBF9E)
				{
					vsk.push_back(�Ѽ���͵�[i]);
					break;
				}
			}
			if (vsk.size() == 0)
			{
				for (size_t i = 0; i < �Ѽ���͵�.size(); i++)
				{
					if (�Ѽ���͵�[i].Mapid == 11111)
					{
						vsk.push_back(�Ѽ���͵�[i]);
					}
				}
			}
			::sort(vsk.begin(), vsk.end(), ���͵�mark);
		}
		if (��ͼID == 11101)
		{
			for (size_t i = 0; i < �Ѽ���͵�.size(); i++)
			{
				if (�Ѽ���͵�[i].dTeleportId == 0xDBF9E)
				{
					vsk.push_back(�Ѽ���͵�[i]);
					break;
				}
			}
			if (vsk.size() == 0)
			{
				for (size_t i = 0; i < �Ѽ���͵�.size(); i++)
				{
					if (�Ѽ���͵�[i].Mapid == 11111)
					{
						vsk.push_back(�Ѽ���͵�[i]);
					}
				}
			}
			::sort(vsk.begin(), vsk.end(), ���͵�mark);
		}
		if (��ͼID == 11113)
		{

			for (size_t i = 0; i < �Ѽ���͵�.size(); i++)
			{
				if (�Ѽ���͵�[i].Mapid == 11101)
				{
					vsk.push_back(�Ѽ���͵�[i]);
				}
			}

			::sort(vsk.begin(), vsk.end(), ���͵�mark);
		}
		if (��ͼID == 11115)
		{

			for (size_t i = 0; i < �Ѽ���͵�.size(); i++)
			{
				if (�Ѽ���͵�[i].Mapid == 11101)
				{
					vsk.push_back(�Ѽ���͵�[i]);
				}
			}

			::sort(vsk.begin(), vsk.end(), ���͵�mark);
		}
	}
}
DWORD ��ͼ::��ȡ�ۿڴ��͵�ID()
{
	INT64 ��_rcx = R_QW(��Ϸģ�� + gb_ResBase);
	INT64 ��_call = ��Ϸģ�� + ��ַ_��ͼ_��ȡ�ۿڴ��͵�ID;
	if (��_rcx == 0)
	{
		return 0;
	}
	INT64 ��_v1 = MainUniversalCALL2_Ret(��_rcx, 0, ��_call);
	return R_DW(��_v1 + 0xAC);
}

INT64 ��ͼ::ȡ��������()
{
	INT64 ��_rcx = R_QW(��Ϸģ�� + ��ַ_��ͼ_����);
	INT64 ��_rdx = ��_rcx;
	if (R_DW(��_rcx + 16) == 0)
	{
		return 0;
	}
	DWORD ��_eax = R_DW(��_rcx + 16);
	��_eax = ��_eax - 1;
	��_rcx = ��_eax * 5;
	INT64 ��_rax = R_QW(��_rdx + 8);
	if (R_DW(��_rax + ��_rcx * 4 + 12) == 0)
	{
		return 0;
	}
	��_rax = R_QW(��_rax + ��_rcx * 4 + 4);
	��_rax = R_QW(��_rax);
	return ��_rax;

}

CString ��ͼ::ȡ���ͼ��()
{
	INT64 ��_���ͼrcx = R_QW(��Ϸģ�� + gb_ResBase);
	INT64 ��_���ͼcall = ��Ϸģ�� + ��ַ_��ͼ_��ȡ���ͼ��;
	DWORD ��_��ͼID = ��ͼ::ȡ��ͼID();
	//INT64 ��_��� = (INT64)�����ڴ�2((HANDLE)-1, 100);
	UCHAR ��_���[100] = { 0 };
	MainUniversalCALL4(��_���ͼrcx, INT64(&��_���), ��_��ͼID, 0, ��_���ͼcall);
	CString �������� = R_CString(R_QW(R_QW((INT64)&��_���) + 0x68));
	//CString �������� = CString(temp.c_str());
	//�ͷ��ڴ�2((HANDLE)-1, LPVOID(��_���), 100);
	return ��������;
}
CString ��ͼ::ȡָ����ͼ��(DWORD ��_��ͼID)
{
	INT64 ��_���ͼrcx = R_QW(��Ϸģ�� + gb_ResBase);
	INT64 ��_���ͼcall = ��Ϸģ�� + ��ַ_��ͼ_��ȡ���ͼ��;
	//INT64 ��_��� = (INT64)�����ڴ�2((HANDLE)-1, 100);
	UCHAR ��_���[100] = { 0 };
	MainUniversalCALL4(��_���ͼrcx, (INT64)&��_���, ��_��ͼID, 0, ��_���ͼcall);
	CString �������� = R_CString(R_QW(R_QW((INT64)&��_���) + 0x68));
	//�ͷ��ڴ�2((HANDLE)-1, LPVOID(��_���), 100);
	return ��������;
}

CString ��ͼ::ȡС��ͼ��()
{
	INT64 ��_rcx = R_QW(��Ϸģ�� + ��ַ_��ͼ_����);
	INT64 ��_call = ��Ϸģ�� + ��ַ_��ͼ_��ȡ��������call;
	INT64 ��_�������� = ��ͼ::ȡ��������();
	UCHAR ��_���[100] = { 0 };
	//INT64 ��_��� = (INT64)�����ڴ�2((HANDLE)-1, 100);
	MainUniversalCALL4(��_rcx, (INT64)&��_���, ��_��������, 0, ��_call);
	CString �������� = R_CString(R_QW((INT64)&��_���));
	//CString �������� = CString(temp.c_str());
	//�ͷ��ڴ�2((HANDLE)-1, LPVOID(��_���), 100);
	return ��������;
}

void ��ͼ::Ѱ·(float x, float y, float z, DWORD modid = 0)
{
	INT64 ��_��ʵ���� = ����::ȡ��ʵ����();
	INT64 ��_RCX = ��_��ʵ���� + ƫ��_��ͼ_Ѱ·rcx;
	����_ ��_��ǰ���� = ����::ȡ����();
	INT64 ��_dCALL = ��Ϸģ�� + ��ַ_��ͼ_Ѱ·call;
	UCHAR pBuff[0x140] = { 0 };

	W_QW((ULONG64)&pBuff[0x0], 4294984384);
	W_Float((ULONG64)&pBuff[0x30], ��_��ǰ����.x);
	W_Float((ULONG64)&pBuff[0x30 + 4], ��_��ǰ����.y);
	W_Float((ULONG64)&pBuff[0x30 + 8], ��_��ǰ����.z);
	W_Float((ULONG64)&pBuff[0x3c], x);
	W_Float((ULONG64)&pBuff[0x3c + 4], y);
	W_Float((ULONG64)&pBuff[0x3c + 8], z);
	W_DW((ULONG64)&pBuff[0x88], modid);
	MainUniversalCALL4(��_RCX, (ULONG_PTR)pBuff, 0, 0, ��_dCALL);
}

bool ��ͼ::����ͼѰ·(float x, float y, float z, DWORD modid = 0)
{
	/*if (GetDis(x, y, z) <= 100)
	{
		return true;
	}*/
	bool �Ƿ�Ѱ· = ����::�Ƿ�����·();
	if (�Ƿ�Ѱ· == false)
	{
		��ͼ::Ѱ·(x, y, z, modid);
		return true;
	}
	MyTrace(L"Ѱ·��");
	return false;
}

bool ��ͼ::ָ���ص��Ƿ�ɵ���(float x, float y, float z)
{
	DWORD reta = 0;
	INT64 dCALL = ��Ϸģ�� + ��ַ_��ͼ_Ŀ�ĵ�ַ�Ƿ�ɴ�Call;
	INT64 ��_rsi = ����::ȡ��ʵ����();
	INT64 ��_�����ַ = ����::ȡ�����ַ();
	UCHAR pBuff[0x100] = { 0 };
	W_Float((ULONG64)&pBuff[0], x);
	W_Float((ULONG64)&pBuff[4], y);
	W_Float((ULONG64)&pBuff[8], z);
	INT64 ��_R9 = (INT64)&pBuff;
	__try {
		__asm
		{
			mov rsi, ��_rsi
			mov rax, qword ptr ds : [rsi]
			mov rcx, rsi
			sub rsp, 0x28
			call qword ptr ds : [rax + ��ַ_��ͼ_Ŀ�ĵ�ַ�Ƿ�ɴ�_rax��ȡƫ��]
			add rsp, 0x28
			mov r14, rax
			sub rsp, 0x60
			mov r9, ��_R9
			mov rcx, r14
			mov rdx, ��_�����ַ
			mov r8, 0
			mov dword ptr ss : [rsp + 0x20] , 0
			mov dword ptr ss : [rsp + 0x28] , 0
			mov dword ptr ss : [rsp + 0x30] , 1
			mov rdi, dCALL
			call rdi
			add rsp, 0x60
			mov reta, eax

		}
	}
	__except (1)
	{
		DbgPrintf_Mine("ָ���ص��Ƿ�ɵ��� �쳣");
		return false;
	}
	MyTrace(L"reta %d", reta);
	if (reta == 1)
	{
		return true;
	}
	return false;
}
bool ��ͼ::ָ���ص��Ƿ�ɵ���_M(float x, float y, float z)
{

	����_ CALLArg;
	CALLArg.x = x;
	CALLArg.y = y;
	CALLArg.z = z;
	SendMessageTimeoutA(g_hWnd, ע����Ϣֵ, Msgid::CALLCanArrive, (LPARAM)&CALLArg, SMTO_NORMAL, 2000, 0);
	//MyTrace(L"����ֵ %d", CALLArg.�Ƿ�ɴ�);
	return (CALLArg.�Ƿ�ɴ�);
}
