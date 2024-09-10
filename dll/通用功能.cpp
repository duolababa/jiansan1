#include "pch.h"
#include "ͨ�ù���.h"
#include "SpoofCall.h"

using namespace std;



std::wstring generateRandomChineseString(int minLength, int maxLength) {
	srand(time(NULL));

	// ���� Unicode ���뷶Χ
	int chineseUnicodeStart = 0x4E00;
	int chineseUnicodeEnd = 0x9FFF;

	// ���ȷ���ַ�������
	int length = minLength + rand() % (maxLength - minLength + 1);

	// �����������
	std::wstring randomChineseString;
	for (int i = 0; i < length; ++i) {
		int randomUnicode = chineseUnicodeStart + rand() % (chineseUnicodeEnd - chineseUnicodeStart + 1);
		wchar_t randomChineseCharacter = static_cast<wchar_t>(randomUnicode);
		randomChineseString.push_back(randomChineseCharacter);
	}

	return randomChineseString;
}

std::string utf8_to_string(const std::string& str)
{
	int nwLen = MultiByteToWideChar(CP_UTF8, 0, str.c_str(), -1, NULL, 0);
	wchar_t* pwBuf = new wchar_t[nwLen + 1];
	memset(pwBuf, 0, nwLen * 2 + 2);
	MultiByteToWideChar(CP_UTF8, 0, str.c_str(), str.length(), pwBuf, nwLen);

	int nLen = WideCharToMultiByte(CP_ACP, 0, pwBuf, -1, NULL, NULL, NULL, NULL);
	char* pBuf = new char[nLen + 1];
	memset(pBuf, 0, nLen + 1);
	WideCharToMultiByte(CP_ACP, 0, pwBuf, nwLen, pBuf, nLen, NULL, NULL);

	std::string ret = pBuf;
	delete[]pBuf;
	delete[]pwBuf;
	return ret;
}
char* UnicodeToAnsi(const wchar_t* szStr)
{
	int nLen = WideCharToMultiByte(CP_ACP, 0, szStr, -1, NULL, 0, NULL, NULL);
	if (nLen == 0)
	{
		return NULL;
	}
	char* pResult = new char[nLen];
	WideCharToMultiByte(CP_ACP, 0, szStr, -1, pResult, nLen, NULL, NULL);
	return pResult;
}

CString UTF82WCS(const char* szU8)
{
	//Ԥת�����õ�����ռ�Ĵ�С;
	int wcsLen = ::MultiByteToWideChar(CP_UTF8, NULL, szU8, strlen(szU8), NULL, 0);

	//����ռ�Ҫ��'\0'�����ռ䣬MultiByteToWideChar�����'\0'�ռ�
	wchar_t* wszString = new wchar_t[wcsLen + 1];

	//ת��
	::MultiByteToWideChar(CP_UTF8, NULL, szU8, strlen(szU8), wszString, wcsLen);

	//������'\0'
	wszString[wcsLen] = '\0';
	BYTE m_code[1000] = { 0 };
	memcpy(m_code, wszString, wcsLen * 2);
	WORD dUCode = 0;
	for (int k = 0; k < wcsLen; k++)
	{
		dUCode = *(WORD*)(m_code + k * 2);
		////MyTrace(L"%X",dUCode);
		if (dUCode > 0xAC00 && dUCode < 0xE000)
		{
			continue;//���Ĳ��� ��������
		}
		if (dUCode >= 0xE000 && dUCode < 0xFF00)
		{
			dUCode = dUCode - 0x8000;
			*(WORD*)(m_code + k * 2) = dUCode;
		}
		if (dUCode >= 0xE00 && dUCode < 0x4E00)
		{
			if (dUCode >= 0x2000 && dUCode <= 0x3100)
			{
				continue;//�������ķ���

			}

			dUCode = dUCode + 0x4000;
			*(WORD*)(m_code + k * 2) = dUCode;
		}
	}
	CString unicodeString = (wchar_t*)m_code;

	delete[] wszString;
	wszString = NULL;

	return unicodeString;
}
wstring	AsciiToUnicode(const string& str)
{
	// Ԥ��-�������п��ֽڵĳ���    
	int unicodeLen = MultiByteToWideChar(CP_ACP, 0, str.c_str(), -1, nullptr, 0);
	// ��ָ�򻺳�����ָ����������ڴ�    
	wchar_t* pUnicode = (wchar_t*)malloc(sizeof(wchar_t) * unicodeLen);
	// ��ʼ�򻺳���ת���ֽ�    
	MultiByteToWideChar(CP_ACP, 0, str.c_str(), -1, pUnicode, unicodeLen);
	wstring ret_str = pUnicode;
	free(pUnicode);
	return ret_str;
}
std::string string_to_utf8(const std::string& str)
{
	int nwLen = MultiByteToWideChar(CP_ACP, 0, str.c_str(), -1, NULL, 0);
	wchar_t* pwBuf = new wchar_t[nwLen + 1];
	memset(pwBuf, 0, nwLen * 2 + 2);
	MultiByteToWideChar(CP_ACP, 0, str.c_str(), str.length(), pwBuf, nwLen);
	int nLen = WideCharToMultiByte(CP_UTF8, 0, pwBuf, -1, NULL, NULL, NULL, NULL);
	char* pBuf = new char[nLen + 1];
	memset(pBuf, 0, nLen + 1);
	WideCharToMultiByte(CP_UTF8, 0, pwBuf, nwLen, pBuf, nLen, NULL, NULL);

	std::string ret = pBuf;
	delete[]pwBuf;
	delete[]pBuf;

	return ret;
}
std::string ws2s(const std::wstring& ws)
{
	std::string curLocale = setlocale(LC_ALL, NULL);        // curLocale = "C";
	setlocale(LC_ALL, "chs");                                             //���ĵ���
	const wchar_t* _Source = ws.c_str();
	size_t _Dsize = ws.size() + 1;                                    //��Ҫת���Ŀ��ַ�������1
	char* _Dest = new char[_Dsize];
	memset(_Dest, 0, _Dsize);                                          //��ʼ��������
	size_t   i;
	wcstombs_s(&i, _Dest, _Dsize, _Source, ws.size());
	std::cout << "i:" << i << std::endl;
	std::string result = _Dest;
	delete[]_Dest;
	setlocale(LC_ALL, curLocale.c_str());                               //���û�ԭ����locale
	return result;
}
void DebugPrintf(char* pszFormat, ...)
{
	char tmpFormat[1024 * 20];

	// =============================================
	char szbufFormat[0x500];
	char szbufFormat_Game[0x500] = "[AeiyDbg]:";
	va_list argList;
	va_start(argList, pszFormat);//�����б��ʼ��
	vsprintf_s(szbufFormat, pszFormat, argList);
	strcat_s(szbufFormat_Game, szbufFormat);
	OutputDebugStringA(szbufFormat_Game);

	// =============================================
	sprintf(tmpFormat, "%s", string_to_utf8(szbufFormat_Game).c_str());
	strcat_s(tmpFormat, InputText);
	sprintf(InputText, u8"%s", tmpFormat);

	va_end(argList);
}

float R_Float(ULONG64 ��_�ڴ��ַ)
{
	__try {
		if (IsBadReadPtr((VOID*)��_�ڴ��ַ, 4))
		{
			return 0.0;
		}
		return *(float*)��_�ڴ��ַ;
	}
	__except (1)
	{
		DebugPrintf("��С���ͳ���");
		return 0.0;
	}
}

double R_double(ULONG64 ��_�ڴ��ַ)
{
	__try {
		if (IsBadReadPtr((VOID*)��_�ڴ��ַ, 4))
		{
			return 0.0;
		}
		return *(double*)��_�ڴ��ַ;
	}
	__except (1)
	{
		DebugPrintf("��˫���ͳ���");
		return 0.0;
	}
}
void ReadStr(ULONG64 ��_�ڴ��ַ, char* data, int len)
{
	__try {
		if (IsBadReadPtr((VOID*)��_�ڴ��ַ, len))
		{
			return;
		}
		memcpy(data, (char*)��_�ڴ��ַ, len);
		return;
	}
	__except (1)
	{
		DebugPrintf("���������ͳ���");
		return;
	}
}


DWORD R_DW(ULONG64 ��_�ڴ��ַ)
{
	__try {
		if (IsBadReadPtr((VOID*)��_�ڴ��ַ, 4))
		{
			return 0;
		}
		return *(DWORD*)��_�ڴ��ַ;
	}
	__except (1)
	{
		DebugPrintf("�������ͳ���");
		return 0;
	}
}
UINT64 R_QW(UINT64 ��_�ڴ��ַ)
{
	__try {
		if (IsBadReadPtr((VOID*)��_�ڴ��ַ, 8))
		{
			return 0;
		}
		return *(UINT64*)��_�ڴ��ַ;
	}
	__except (1)
	{
		DebugPrintf("���������ͳ���");
		return 0;
	}
}




BYTE R_BYTE(ULONG64 ��_�ڴ��ַ)
{
	__try {
		if (IsBadReadPtr((VOID*)��_�ڴ��ַ, 1))
		{
			return 0;
		}
		return *(BYTE*)��_�ڴ��ַ;
	}
	__except (1)
	{
		DebugPrintf("���ֽ��ͳ���");
		return 0;
	}
}
WORD R_W(ULONG64 ��_�ڴ��ַ)
{
	__try {
		if (IsBadReadPtr((VOID*)��_�ڴ��ַ, 2))
		{
			return 0;
		}
		return *(WORD*)��_�ڴ��ַ;
	}
	__except (1)
	{
		DebugPrintf("���������ͳ���");
		return 0;
	}
}
wchar_t* R_CString(INT64 Ҫ��ȡ���ڴ��ַ)
{
	__try {
		//wchar_t* str = L"";
		//CString a = L"";

		if (!IsBadReadPtr((VOID*)Ҫ��ȡ���ڴ��ַ, 8))
		{
			return (wchar_t*)Ҫ��ȡ���ڴ��ַ;
			//return str;
		}
	}
	__except (1)
	{
		DebugPrintf("���ı��ͳ���");
		return L"";
	}
	return L"";


}
char* R_String(INT64 Ҫ��ȡ���ڴ��ַ)
{
	__try {
	
		//CString a = L"";

		if (!IsBadReadPtr((VOID*)Ҫ��ȡ���ڴ��ַ, 8))
		{
			return (char*)Ҫ��ȡ���ڴ��ַ;
		
		}
	}
	__except (1)
	{
		DebugPrintf("���ı��ͳ���");
		return "";
	}
	return "";


}
void W_CString(INT64 �ڴ��ַ,CString ����)
{

	//memset(buf, 0, 200);
	wsprintfW((wchar_t*)�ڴ��ַ, L"%s", ����);
}
//int Readint(ULONG64 ��_�ڴ��ַ)
//{
//	__try {
//		if (IsBadReadPtr((VOID*)��_�ڴ��ַ, 4))
//		{
//			return 0;
//		}
//		return *(int*)��_�ڴ��ַ;
//	}
//	__except (1)
//	{
//		OutputDebugStringA("�������ͳ���");
//		return 0;
//	}
//}

void W_DW(ULONG64 ��_�ڴ��ַ, DWORD ��_д������)
{
	__try {
		
		if (IsBadReadPtr((VOID*)��_�ڴ��ַ, 4))
		{
			return;
		}
		DWORD old_protect;
		VirtualProtect((LPVOID)��_�ڴ��ַ, 4, 64, &old_protect);
		*(DWORD*)��_�ڴ��ַ = ��_д������;
		VirtualProtect((LPVOID)��_�ڴ��ַ, 4, old_protect, &old_protect);
	}
	__except (1)
	{
		DebugPrintf("д�����ͳ���");
	}
}

void W_Float(ULONG64 ��_�ڴ��ַ, float ��_д������)
{
	__try {
		
		if (IsBadReadPtr((VOID*)��_�ڴ��ַ, 4))
		{
			return;
		}
		DWORD old_protect;
		VirtualProtect((LPVOID)��_�ڴ��ַ, 4, 64, &old_protect);
		*(float*)��_�ڴ��ַ = ��_д������;
		VirtualProtect((LPVOID)��_�ڴ��ַ, 4, old_protect, &old_protect);
	}
	__except (1)
	{
		DebugPrintf("дС���ͳ���");
	}
	
}

void W_Word(ULONG64 ��_�ڴ��ַ, WORD ��_д������)
{
	__try {
		if (IsBadReadPtr((VOID*)��_�ڴ��ַ, 2))
		{
			return;
		}
		DWORD old_protect;
		VirtualProtect((LPVOID)��_�ڴ��ַ, 2, 64, &old_protect);
		*(WORD*)��_�ڴ��ַ = ��_д������;
		VirtualProtect((LPVOID)��_�ڴ��ַ, 2, old_protect, &old_protect);
	}

	__except (1)
	{
		DebugPrintf("д����������");
	}
}
void W_BYTE(ULONG64 ��_�ڴ��ַ, BYTE ��_д������)
{
	__try {
		if (IsBadReadPtr((VOID*)��_�ڴ��ַ, 2))
		{
			return;
		}
		DWORD old_protect;
		VirtualProtect((LPVOID)��_�ڴ��ַ, 1, 64, &old_protect);
		*(BYTE*)��_�ڴ��ַ = ��_д������;
		VirtualProtect((LPVOID)��_�ڴ��ַ, 1, old_protect, &old_protect);
	}

	__except (1)
	{
		DebugPrintf("д����������");
	}
}
void W_QW(ULONG64 ��_�ڴ��ַ, UINT64 ��_д������)
{
	__try {
		if (IsBadReadPtr((VOID*)��_�ڴ��ַ, 8))
		{
			return;
		}
		DWORD old_protect;
		VirtualProtect((LPVOID)��_�ڴ��ַ, 8, 64, &old_protect);
		*(UINT64*)��_�ڴ��ַ = ��_д������;
		VirtualProtect((LPVOID)��_�ڴ��ַ, 8, old_protect, &old_protect);
	}
	__except (1)
	{
		DebugPrintf("д����������");
	}
}
UINT64 CALL2(UINT64 RCX, UINT64 RDX, UINT64 CALL��ַ)
{
	__try {
		if (1)
		{
		//	DebugPrintf("SPOFcall ��ʼִ��");
			uintptr_t(__fastcall * CALL2)(UINT64, UINT64) = nullptr;
			if (IsBadReadPtr((const void*)CALL��ַ, sizeof(CALL��ַ))) return NULL;
			CALL2 = reinterpret_cast<decltype(CALL2)>(CALL��ַ);
			return SpoofCall<uintptr_t>(CALL2, RCX, RDX);
		}
		else
		{
			typedef UINT64(_fastcall* game_function)(UINT64, UINT64);
			if (IsBadReadPtr((const void*)CALL��ַ, sizeof(CALL��ַ))) return NULL;
			auto _ͨ��CALL = reinterpret_cast<game_function> (CALL��ַ);
			return _ͨ��CALL(RCX, RDX);
		}
	}
	__except (1) {
		DebugPrintf("ͨ��CALL2  ����\n");
	}
	return 0;
}

UINT64 CALL4(UINT64 RCX, UINT64 RDX, UINT64 R8, UINT64 R9, UINT64 CALL��ַ)
{
	__try {
		if (1)
		{
			uintptr_t(__fastcall * CALL4)(UINT64, UINT64, UINT64, UINT64) = nullptr;
			if (IsBadReadPtr((const void*)CALL��ַ, sizeof(CALL��ַ))) return NULL;
			CALL4 = reinterpret_cast<decltype(CALL4)>(CALL��ַ);
			return SpoofCall<uintptr_t>(CALL4, RCX, RDX, R8, R9);
		}
		else
		{
				typedef UINT64(_fastcall* game_function)(UINT64, UINT64, UINT64, UINT64);
				if (IsBadReadPtr((const void*)CALL��ַ, sizeof(CALL��ַ))) return NULL;
				auto _ͨ��CALL = reinterpret_cast<game_function> (CALL��ַ);
				return _ͨ��CALL(RCX, RDX, R8, R9);
		}
	}
	__except (1) {
		DebugPrintf("ͨ��CALL4  ����\n");
	}
	return 0;
}
UINT64 CALL6(UINT64 RCX, UINT64 RDX, UINT64 R8, UINT64 R9, UINT64 ����5_ֵ, UINT64 ����6_ֵ, UINT64 CALL��ַ)
{
	__try {

		if (1)
		{
			uintptr_t(__fastcall * CALL6)(UINT64, UINT64, UINT64, UINT64, UINT64, UINT64) = nullptr;
			if (IsBadReadPtr((const void*)CALL��ַ, sizeof(CALL��ַ))) return NULL;
			CALL6 = reinterpret_cast<decltype(CALL6)>(CALL��ַ);
			return SpoofCall<uintptr_t>(CALL6, RCX, RDX, R8, R9, ����5_ֵ, ����6_ֵ);
		}
		else
		{

			typedef UINT64(_fastcall* game_function)(UINT64, UINT64, UINT64, UINT64, UINT64, UINT64);
			if (IsBadReadPtr((const void*)CALL��ַ, sizeof(CALL��ַ))) return NULL;
			auto _ͨ��CALL = reinterpret_cast<game_function> (CALL��ַ);
			return _ͨ��CALL(RCX, RDX, R8, R9, ����5_ֵ, ����6_ֵ);
		}
	}


	__except (1) {
		DebugPrintf("ͨ��CALL6  ����\n");
	}





	return 0;
}

UINT64 CALL8(UINT64 RCX, UINT64 RDX, UINT64 R8, UINT64 R9, UINT64 ����5_ֵ, UINT64 ����6_ֵ, UINT64 ����7_ֵ, UINT64 ����8_ֵ, UINT64 CALL��ַ)
{
	__try {
		if (1)
		{
			uintptr_t(__fastcall * CALL8)(UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64) = nullptr;
			if (IsBadReadPtr((const void*)CALL��ַ, sizeof(CALL��ַ))) return NULL;
			CALL8 = reinterpret_cast<decltype(CALL8)>(CALL��ַ);
			return SpoofCall<uintptr_t>(CALL8, RCX, RDX, R8, R9, ����5_ֵ, ����6_ֵ, ����7_ֵ, ����8_ֵ);

		}
		else
		{
			typedef UINT64(_fastcall* game_function)(UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64);
			if (IsBadReadPtr((const void*)CALL��ַ, sizeof(CALL��ַ))) return NULL;
			auto _ͨ��CALL = reinterpret_cast<game_function> (CALL��ַ);
			return _ͨ��CALL(RCX, RDX, R8, R9, ����5_ֵ, ����6_ֵ, ����7_ֵ, ����8_ֵ);
		}
	}
	__except (1) {
		DebugPrintf("ͨ��CALL8  ����\n");
	}
	return 0;
}

//���ַ���s�����ַ���c�����зֵõ�vector_v 
vector<string> �ָ��ַ���(const string& s, const string& c)
{
	vector<string> v;
	int pos1 = 0, pos2;
	while ((pos2 = s.find(c, pos1)) != -1) {
		v.push_back(s.substr(pos1, pos2 - pos1));
		pos1 = pos2 + c.size();
	}
	if (pos1 != s.length())
		v.push_back(s.substr(pos1));
	return v;
}
int Split(const string& str, vector<string>& ret_, string sep)
{
	int ubound = 0;
	if (str.empty())
	{
		return ubound;
	}

	string tmp;
	string::size_type pos_begin = 0;// str.find_first_not_of(sep);
	string::size_type comma_pos = 0;

	while (pos_begin != string::npos)
	{
		comma_pos = str.find(sep, pos_begin);

		if (comma_pos != string::npos)
		{
			tmp = str.substr(pos_begin, comma_pos - pos_begin);
			pos_begin = comma_pos + sep.length();
		}
		else
		{
			tmp = str.substr(pos_begin);
			pos_begin = comma_pos;
		}

		if (!tmp.empty())
		{
			ubound++;
			ret_.push_back(tmp);
			tmp.clear();
		}
	}
	return ubound;
}
// 2������CALL���̵߳���
void MainUniversalCALL2(UINT64 RCX_ֵ, UINT64 RDX_ֵ, UINT64 CALL_��ַ)
{
	CallParam2 CALLArg;
	CALLArg.RCX = RCX_ֵ;
	CALLArg.RDX = RDX_ֵ;
	CALLArg.CALLAddr = CALL_��ַ;
	//MyTrace(L"ִ����Ϣ�� %d ���ھ�� %d", ע����Ϣֵ , g_hWnd);
	//PostMessageA(g_hWnd, ע����Ϣֵ, Msgid::CallCanUse2, (LPARAM)&CALLArg);
	SendMessageTimeoutA(g_hWnd, ע����Ϣֵ, Msgid::CallCanUse2, (LPARAM)&CALLArg, SMTO_NORMAL, 1000, 0);
	//::SendMessageA(g_hWnd, ע����Ϣֵ, Msgid::CallCanUse2, (LPARAM)&CALLArg);
}
INT64 MainUniversalCALL2_Ret(UINT64 RCX_ֵ, UINT64 RDX_ֵ, UINT64 CALL_��ַ)
{
	CallParam2 CALLArg;
	CALLArg.RCX = RCX_ֵ;
	CALLArg.RDX = RDX_ֵ;
	CALLArg.CALLAddr = CALL_��ַ;
	SendMessageTimeoutA(g_hWnd, ע����Ϣֵ, Msgid::CallCanUse2, (LPARAM)&CALLArg, SMTO_NORMAL, 1000, 0);
	return CALLArg.RetVal;
	//::SendMessageA(g_hWnd, ע����Ϣֵ, Msgid::CallCanUse2, (LPARAM)&CALLArg);
}


// 4������CALL���̵߳���
void MainUniversalCALL4(UINT64 RCX_ֵ, UINT64 RDX_ֵ, UINT64 R8_ֵ, UINT64 R9_ֵ, UINT64 CALL_��ַ)
{
	CallParam4 CALLArg;
	CALLArg.RCX = RCX_ֵ;
	CALLArg.RDX = RDX_ֵ;
	CALLArg.R8 = R8_ֵ;
	CALLArg.R9 = R9_ֵ;
	CALLArg.CALLAddr = CALL_��ַ;
	::SendMessageA(g_hWnd, ע����Ϣֵ, Msgid::CallCanUse, (LPARAM)&CALLArg);
}
INT64 MainUniversalCALL4_Ret(UINT64 RCX_ֵ, UINT64 RDX_ֵ, UINT64 R8_ֵ, UINT64 R9_ֵ, UINT64 CALL_��ַ)
{
	CallParam4 CALLArg;
	CALLArg.RCX = RCX_ֵ;
	CALLArg.RDX = RDX_ֵ;
	CALLArg.R8 = R8_ֵ;
	CALLArg.R9 = R9_ֵ;
	CALLArg.CALLAddr = CALL_��ַ;
	SendMessageTimeoutA(g_hWnd, ע����Ϣֵ, Msgid::CallCanUse, (LPARAM)&CALLArg, SMTO_NORMAL, 1000, 0);
	return CALLArg.RetVal;
}
void MainUniversalCALL6(UINT64 RCX_ֵ, UINT64 RDX_ֵ, UINT64 R8_ֵ, UINT64 R9_ֵ, UINT64 rsp_20, UINT64 rsp_28, UINT64 CALL_��ַ)
{
	CallParam6 CALLArg;
	CALLArg.RCX = RCX_ֵ;
	CALLArg.RDX = RDX_ֵ;
	CALLArg.R8 = R8_ֵ;
	CALLArg.R9 = R9_ֵ;
	CALLArg.��5���� = rsp_20;
	CALLArg.��6���� = rsp_28;
	CALLArg.CALLAddr = CALL_��ַ;
	::SendMessageA(g_hWnd, ע����Ϣֵ, Msgid::CallCanUse1, (LPARAM)&CALLArg);
}
void MainUniversalCALL8(UINT64 RCX_ֵ, UINT64 RDX_ֵ, UINT64 R8_ֵ, UINT64 R9_ֵ, UINT64 rsp_20, UINT64 rsp_28, UINT64 rsp_30, UINT64 rsp_38, UINT64 CALL_��ַ)
{
	CallParam8 CALLArg;
	CALLArg.RCX = RCX_ֵ;
	CALLArg.RDX = RDX_ֵ;
	CALLArg.R8 = R8_ֵ;
	CALLArg.R9 = R9_ֵ;
	CALLArg.��5���� = rsp_20;
	CALLArg.��6���� = rsp_28;
	CALLArg.��7���� = rsp_30;
	CALLArg.��8���� = rsp_38;
	CALLArg.CALLAddr = CALL_��ַ;
	::SendMessageA(g_hWnd, ע����Ϣֵ, Msgid::CallCanUse3, (LPARAM)&CALLArg);
}
INT64 MainUniversalCALL8_Ret(UINT64 RCX_ֵ, UINT64 RDX_ֵ, UINT64 R8_ֵ, UINT64 R9_ֵ, UINT64 rsp_20, UINT64 rsp_28, UINT64 rsp_30, UINT64 rsp_38, UINT64 CALL_��ַ)
{
	CallParam8 CALLArg;
	CALLArg.RCX = RCX_ֵ;
	CALLArg.RDX = RDX_ֵ;
	CALLArg.R8 = R8_ֵ;
	CALLArg.R9 = R9_ֵ;
	CALLArg.��5���� = rsp_20;
	CALLArg.��6���� = rsp_28;
	CALLArg.��7���� = rsp_30;
	CALLArg.��8���� = rsp_38;
	CALLArg.CALLAddr = CALL_��ַ;
	SendMessageTimeoutA(g_hWnd, ע����Ϣֵ, Msgid::CallCanUse3, (LPARAM)&CALLArg, SMTO_NORMAL, 1000, 0);
	return CALLArg.RetVal;
}
int Random(int min, int max)
{
	srand(static_cast<unsigned int>(time(nullptr)));
	int ����ֵ;

	����ֵ = rand() % (max - min + 1) + min;
	return ����ֵ;
}
CString �������Ӣ������(int ����)
{
	srand((unsigned)time(NULL));
	CString ����ֵ;
	for (int i = 0; i < ����; i++)
	{
		int intValue = 'a' + rand() % 26;
		//int intValue = (int)(Random(1, 26) + 97);
		����ֵ = ����ֵ + (char)intValue;
	}
	return ����ֵ;

}
CString randstr(const int len)
{
	CString cstr;
	char str[25];
	srand(time(NULL));
	int i;
	for (i = 0; i < len; ++i)
	{
		if (i == 0)
		{
			str[i]= 'A' + rand() % 26;
		}
		else
		{
			str[i] = 'a' + rand() % 26;
		}
	}
	str[len] = '\0';
	cstr = str;
	return cstr;
}
#define PI 3.14159265358979323846
DWORD Get_Rel_Angle(float x1, float y1, float x2, float y2)
{
	float TarAngle = 0;
	if (x2 > x1 && y2 > y1) { // ��һ����
		TarAngle = (atan((y2 - y1) / (x2 - x1)) * 180 / PI);
	}
	if (x2 < x1 && y2 > y1) { // �ڶ�����
		TarAngle = (180 - (atan((y2 - y1) / (x1 - x2)) * 180 / PI));
	}
	if (x2 < x1 && y2 < y1) { // ��������
		TarAngle = (270 - (atan((x1 - x2) / (y1 - y2)) * 180 / PI));
	}
	if (x2 > x1 && y2 < y1) { // ��������
		TarAngle = (360 - (atan((y1 - y2) / (x2 - x1)) * 180 / PI));
	}
	if (x2 > x1 && y2 == y1) { // X��������
		TarAngle = 0;
	}
	if (x2 < x1 && y2 == y1) { // X�Ḻ����
		TarAngle = 180;
	}
	if (x2 == x1 && y2 > y1) { // Y��������
		TarAngle = 90;
	}
	if (x2 == x1 && y2 < y1) { // Y�Ḻ����
		TarAngle = 270;
	}
	if (x2 == x1 && y2 == y1) { // ԭ��
		TarAngle = 0;
	}
	TarAngle = TarAngle / 0.00549317;
	return (DWORD)TarAngle;
}

CString �������ı�(DWORD64 ����)
{
	CString cStr;
	cStr.Format(_T("%ld"), ����);
	return cStr;
}
CString getCommandIndex()
{
	CString Commadline = GetCommandLineW();
	int ���� = Commadline.ReverseFind('=');
	CString ddindex = Commadline.Right(Commadline.GetLength() - ���� - 1);
	return ddindex;
}