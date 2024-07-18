#include "pch.h"
#include "通用功能.h"
#include "SpoofCall.h"

using namespace std;



std::wstring generateRandomChineseString(int minLength, int maxLength) {
	srand(time(NULL));

	// 汉字 Unicode 编码范围
	int chineseUnicodeStart = 0x4E00;
	int chineseUnicodeEnd = 0x9FFF;

	// 随机确定字符串长度
	int length = minLength + rand() % (maxLength - minLength + 1);

	// 生成随机汉字
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
	//预转换，得到所需空间的大小;
	int wcsLen = ::MultiByteToWideChar(CP_UTF8, NULL, szU8, strlen(szU8), NULL, 0);

	//分配空间要给'\0'留个空间，MultiByteToWideChar不会给'\0'空间
	wchar_t* wszString = new wchar_t[wcsLen + 1];

	//转换
	::MultiByteToWideChar(CP_UTF8, NULL, szU8, strlen(szU8), wszString, wcsLen);

	//最后加上'\0'
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
			continue;//韩文部分 不做处理
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
				continue;//跳过中文符号

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
	// 预算-缓冲区中宽字节的长度    
	int unicodeLen = MultiByteToWideChar(CP_ACP, 0, str.c_str(), -1, nullptr, 0);
	// 给指向缓冲区的指针变量分配内存    
	wchar_t* pUnicode = (wchar_t*)malloc(sizeof(wchar_t) * unicodeLen);
	// 开始向缓冲区转换字节    
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
	setlocale(LC_ALL, "chs");                                             //中文地区
	const wchar_t* _Source = ws.c_str();
	size_t _Dsize = ws.size() + 1;                                    //比要转换的宽字符个数大1
	char* _Dest = new char[_Dsize];
	memset(_Dest, 0, _Dsize);                                          //初始化缓冲区
	size_t   i;
	wcstombs_s(&i, _Dest, _Dsize, _Source, ws.size());
	std::cout << "i:" << i << std::endl;
	std::string result = _Dest;
	delete[]_Dest;
	setlocale(LC_ALL, curLocale.c_str());                               //设置回原来的locale
	return result;
}
void DebugPrintf(char* pszFormat, ...)
{
	char tmpFormat[1024 * 20];

	// =============================================
	char szbufFormat[0x500];
	char szbufFormat_Game[0x500] = "[AeiyDbg]:";
	va_list argList;
	va_start(argList, pszFormat);//参数列表初始化
	vsprintf_s(szbufFormat, pszFormat, argList);
	strcat_s(szbufFormat_Game, szbufFormat);
	OutputDebugStringA(szbufFormat_Game);

	// =============================================
	sprintf(tmpFormat, "%s", string_to_utf8(szbufFormat_Game).c_str());
	strcat_s(tmpFormat, InputText);
	sprintf(InputText, u8"%s", tmpFormat);

	va_end(argList);
}

float R_Float(ULONG64 参_内存地址)
{
	__try {
		if (IsBadReadPtr((VOID*)参_内存地址, 4))
		{
			return 0.0;
		}
		return *(float*)参_内存地址;
	}
	__except (1)
	{
		DebugPrintf("读小数型出错");
		return 0.0;
	}
}

double R_double(ULONG64 参_内存地址)
{
	__try {
		if (IsBadReadPtr((VOID*)参_内存地址, 4))
		{
			return 0.0;
		}
		return *(double*)参_内存地址;
	}
	__except (1)
	{
		DebugPrintf("读双数型出错");
		return 0.0;
	}
}
void ReadStr(ULONG64 参_内存地址, char* data, int len)
{
	__try {
		if (IsBadReadPtr((VOID*)参_内存地址, len))
		{
			return;
		}
		memcpy(data, (char*)参_内存地址, len);
		return;
	}
	__except (1)
	{
		DebugPrintf("读长整数型出错");
		return;
	}
}


DWORD R_DW(ULONG64 参_内存地址)
{
	__try {
		if (IsBadReadPtr((VOID*)参_内存地址, 4))
		{
			return 0;
		}
		return *(DWORD*)参_内存地址;
	}
	__except (1)
	{
		DebugPrintf("读整数型出错");
		return 0;
	}
}
UINT64 R_QW(UINT64 参_内存地址)
{
	__try {
		if (IsBadReadPtr((VOID*)参_内存地址, 8))
		{
			return 0;
		}
		return *(UINT64*)参_内存地址;
	}
	__except (1)
	{
		DebugPrintf("读长整数型出错");
		return 0;
	}
}




BYTE R_BYTE(ULONG64 参_内存地址)
{
	__try {
		if (IsBadReadPtr((VOID*)参_内存地址, 1))
		{
			return 0;
		}
		return *(BYTE*)参_内存地址;
	}
	__except (1)
	{
		DebugPrintf("读字节型出错");
		return 0;
	}
}
WORD R_W(ULONG64 参_内存地址)
{
	__try {
		if (IsBadReadPtr((VOID*)参_内存地址, 2))
		{
			return 0;
		}
		return *(WORD*)参_内存地址;
	}
	__except (1)
	{
		DebugPrintf("读短整数型出错");
		return 0;
	}
}
wchar_t* R_CString(INT64 要读取的内存地址)
{
	__try {
		//wchar_t* str = L"";
		//CString a = L"";

		if (!IsBadReadPtr((VOID*)要读取的内存地址, 8))
		{
			return (wchar_t*)要读取的内存地址;
			//return str;
		}
	}
	__except (1)
	{
		DebugPrintf("读文本型出错");
		return L"";
	}
	return L"";


}
char* R_String(INT64 要读取的内存地址)
{
	__try {
	
		//CString a = L"";

		if (!IsBadReadPtr((VOID*)要读取的内存地址, 8))
		{
			return (char*)要读取的内存地址;
		
		}
	}
	__except (1)
	{
		DebugPrintf("读文本型出错");
		return "";
	}
	return "";


}
void W_CString(INT64 内存地址,CString 内容)
{

	//memset(buf, 0, 200);
	wsprintfW((wchar_t*)内存地址, L"%s", 内容);
}
//int Readint(ULONG64 参_内存地址)
//{
//	__try {
//		if (IsBadReadPtr((VOID*)参_内存地址, 4))
//		{
//			return 0;
//		}
//		return *(int*)参_内存地址;
//	}
//	__except (1)
//	{
//		OutputDebugStringA("读整数型出错");
//		return 0;
//	}
//}

void W_DW(ULONG64 参_内存地址, DWORD 参_写入数据)
{
	__try {
		
		if (IsBadReadPtr((VOID*)参_内存地址, 4))
		{
			return;
		}
		DWORD old_protect;
		VirtualProtect((LPVOID)参_内存地址, 4, 64, &old_protect);
		*(DWORD*)参_内存地址 = 参_写入数据;
		VirtualProtect((LPVOID)参_内存地址, 4, old_protect, &old_protect);
	}
	__except (1)
	{
		DebugPrintf("写整数型出错");
	}
}

void W_Float(ULONG64 参_内存地址, float 参_写入数据)
{
	__try {
		
		if (IsBadReadPtr((VOID*)参_内存地址, 4))
		{
			return;
		}
		DWORD old_protect;
		VirtualProtect((LPVOID)参_内存地址, 4, 64, &old_protect);
		*(float*)参_内存地址 = 参_写入数据;
		VirtualProtect((LPVOID)参_内存地址, 4, old_protect, &old_protect);
	}
	__except (1)
	{
		DebugPrintf("写小数型出错");
	}
	
}

void W_Word(ULONG64 参_内存地址, WORD 参_写入数据)
{
	__try {
		if (IsBadReadPtr((VOID*)参_内存地址, 2))
		{
			return;
		}
		DWORD old_protect;
		VirtualProtect((LPVOID)参_内存地址, 2, 64, &old_protect);
		*(WORD*)参_内存地址 = 参_写入数据;
		VirtualProtect((LPVOID)参_内存地址, 2, old_protect, &old_protect);
	}

	__except (1)
	{
		DebugPrintf("写短整数出错");
	}
}
void W_BYTE(ULONG64 参_内存地址, BYTE 参_写入数据)
{
	__try {
		if (IsBadReadPtr((VOID*)参_内存地址, 2))
		{
			return;
		}
		DWORD old_protect;
		VirtualProtect((LPVOID)参_内存地址, 1, 64, &old_protect);
		*(BYTE*)参_内存地址 = 参_写入数据;
		VirtualProtect((LPVOID)参_内存地址, 1, old_protect, &old_protect);
	}

	__except (1)
	{
		DebugPrintf("写短整数出错");
	}
}
void W_QW(ULONG64 参_内存地址, UINT64 参_写入数据)
{
	__try {
		if (IsBadReadPtr((VOID*)参_内存地址, 8))
		{
			return;
		}
		DWORD old_protect;
		VirtualProtect((LPVOID)参_内存地址, 8, 64, &old_protect);
		*(UINT64*)参_内存地址 = 参_写入数据;
		VirtualProtect((LPVOID)参_内存地址, 8, old_protect, &old_protect);
	}
	__except (1)
	{
		DebugPrintf("写长整数出错");
	}
}
UINT64 CALL2(UINT64 RCX, UINT64 RDX, UINT64 CALL地址)
{
	__try {
		if (1)
		{
		//	DebugPrintf("SPOFcall 开始执行");
			uintptr_t(__fastcall * CALL2)(UINT64, UINT64) = nullptr;
			if (IsBadReadPtr((const void*)CALL地址, sizeof(CALL地址))) return NULL;
			CALL2 = reinterpret_cast<decltype(CALL2)>(CALL地址);
			return SpoofCall<uintptr_t>(CALL2, RCX, RDX);
		}
		else
		{
			typedef UINT64(_fastcall* game_function)(UINT64, UINT64);
			if (IsBadReadPtr((const void*)CALL地址, sizeof(CALL地址))) return NULL;
			auto _通用CALL = reinterpret_cast<game_function> (CALL地址);
			return _通用CALL(RCX, RDX);
		}
	}
	__except (1) {
		DebugPrintf("通用CALL2  出错\n");
	}
	return 0;
}

UINT64 CALL4(UINT64 RCX, UINT64 RDX, UINT64 R8, UINT64 R9, UINT64 CALL地址)
{
	__try {
		if (1)
		{
			uintptr_t(__fastcall * CALL4)(UINT64, UINT64, UINT64, UINT64) = nullptr;
			if (IsBadReadPtr((const void*)CALL地址, sizeof(CALL地址))) return NULL;
			CALL4 = reinterpret_cast<decltype(CALL4)>(CALL地址);
			return SpoofCall<uintptr_t>(CALL4, RCX, RDX, R8, R9);
		}
		else
		{
				typedef UINT64(_fastcall* game_function)(UINT64, UINT64, UINT64, UINT64);
				if (IsBadReadPtr((const void*)CALL地址, sizeof(CALL地址))) return NULL;
				auto _通用CALL = reinterpret_cast<game_function> (CALL地址);
				return _通用CALL(RCX, RDX, R8, R9);
		}
	}
	__except (1) {
		DebugPrintf("通用CALL4  出错\n");
	}
	return 0;
}
UINT64 CALL6(UINT64 RCX, UINT64 RDX, UINT64 R8, UINT64 R9, UINT64 参数5_值, UINT64 参数6_值, UINT64 CALL地址)
{
	__try {

		if (1)
		{
			uintptr_t(__fastcall * CALL6)(UINT64, UINT64, UINT64, UINT64, UINT64, UINT64) = nullptr;
			if (IsBadReadPtr((const void*)CALL地址, sizeof(CALL地址))) return NULL;
			CALL6 = reinterpret_cast<decltype(CALL6)>(CALL地址);
			return SpoofCall<uintptr_t>(CALL6, RCX, RDX, R8, R9, 参数5_值, 参数6_值);
		}
		else
		{

			typedef UINT64(_fastcall* game_function)(UINT64, UINT64, UINT64, UINT64, UINT64, UINT64);
			if (IsBadReadPtr((const void*)CALL地址, sizeof(CALL地址))) return NULL;
			auto _通用CALL = reinterpret_cast<game_function> (CALL地址);
			return _通用CALL(RCX, RDX, R8, R9, 参数5_值, 参数6_值);
		}
	}


	__except (1) {
		DebugPrintf("通用CALL6  出错\n");
	}





	return 0;
}

UINT64 CALL8(UINT64 RCX, UINT64 RDX, UINT64 R8, UINT64 R9, UINT64 参数5_值, UINT64 参数6_值, UINT64 参数7_值, UINT64 参数8_值, UINT64 CALL地址)
{
	__try {
		if (1)
		{
			uintptr_t(__fastcall * CALL8)(UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64) = nullptr;
			if (IsBadReadPtr((const void*)CALL地址, sizeof(CALL地址))) return NULL;
			CALL8 = reinterpret_cast<decltype(CALL8)>(CALL地址);
			return SpoofCall<uintptr_t>(CALL8, RCX, RDX, R8, R9, 参数5_值, 参数6_值, 参数7_值, 参数8_值);

		}
		else
		{
			typedef UINT64(_fastcall* game_function)(UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64, UINT64);
			if (IsBadReadPtr((const void*)CALL地址, sizeof(CALL地址))) return NULL;
			auto _通用CALL = reinterpret_cast<game_function> (CALL地址);
			return _通用CALL(RCX, RDX, R8, R9, 参数5_值, 参数6_值, 参数7_值, 参数8_值);
		}
	}
	__except (1) {
		DebugPrintf("通用CALL8  出错\n");
	}
	return 0;
}

//把字符串s按照字符串c进行切分得到vector_v 
vector<string> 分割字符串(const string& s, const string& c)
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
// 2个参数CALL主线程调用
void MainUniversalCALL2(UINT64 RCX_值, UINT64 RDX_值, UINT64 CALL_地址)
{
	CallParam2 CALLArg;
	CALLArg.RCX = RCX_值;
	CALLArg.RDX = RDX_值;
	CALLArg.CALLAddr = CALL_地址;
	//MyTrace(L"执行消息好 %d 窗口句柄 %d", 注册消息值 , g_hWnd);
	//PostMessageA(g_hWnd, 注册消息值, Msgid::CallCanUse2, (LPARAM)&CALLArg);
	SendMessageTimeoutA(g_hWnd, 注册消息值, Msgid::CallCanUse2, (LPARAM)&CALLArg, SMTO_NORMAL, 1000, 0);
	//::SendMessageA(g_hWnd, 注册消息值, Msgid::CallCanUse2, (LPARAM)&CALLArg);
}
INT64 MainUniversalCALL2_Ret(UINT64 RCX_值, UINT64 RDX_值, UINT64 CALL_地址)
{
	CallParam2 CALLArg;
	CALLArg.RCX = RCX_值;
	CALLArg.RDX = RDX_值;
	CALLArg.CALLAddr = CALL_地址;
	SendMessageTimeoutA(g_hWnd, 注册消息值, Msgid::CallCanUse2, (LPARAM)&CALLArg, SMTO_NORMAL, 1000, 0);
	return CALLArg.RetVal;
	//::SendMessageA(g_hWnd, 注册消息值, Msgid::CallCanUse2, (LPARAM)&CALLArg);
}


// 4个参数CALL主线程调用
void MainUniversalCALL4(UINT64 RCX_值, UINT64 RDX_值, UINT64 R8_值, UINT64 R9_值, UINT64 CALL_地址)
{
	CallParam4 CALLArg;
	CALLArg.RCX = RCX_值;
	CALLArg.RDX = RDX_值;
	CALLArg.R8 = R8_值;
	CALLArg.R9 = R9_值;
	CALLArg.CALLAddr = CALL_地址;
	::SendMessageA(g_hWnd, 注册消息值, Msgid::CallCanUse, (LPARAM)&CALLArg);
}
INT64 MainUniversalCALL4_Ret(UINT64 RCX_值, UINT64 RDX_值, UINT64 R8_值, UINT64 R9_值, UINT64 CALL_地址)
{
	CallParam4 CALLArg;
	CALLArg.RCX = RCX_值;
	CALLArg.RDX = RDX_值;
	CALLArg.R8 = R8_值;
	CALLArg.R9 = R9_值;
	CALLArg.CALLAddr = CALL_地址;
	SendMessageTimeoutA(g_hWnd, 注册消息值, Msgid::CallCanUse, (LPARAM)&CALLArg, SMTO_NORMAL, 1000, 0);
	return CALLArg.RetVal;
}
void MainUniversalCALL6(UINT64 RCX_值, UINT64 RDX_值, UINT64 R8_值, UINT64 R9_值, UINT64 rsp_20, UINT64 rsp_28, UINT64 CALL_地址)
{
	CallParam6 CALLArg;
	CALLArg.RCX = RCX_值;
	CALLArg.RDX = RDX_值;
	CALLArg.R8 = R8_值;
	CALLArg.R9 = R9_值;
	CALLArg.第5参数 = rsp_20;
	CALLArg.第6参数 = rsp_28;
	CALLArg.CALLAddr = CALL_地址;
	::SendMessageA(g_hWnd, 注册消息值, Msgid::CallCanUse1, (LPARAM)&CALLArg);
}
void MainUniversalCALL8(UINT64 RCX_值, UINT64 RDX_值, UINT64 R8_值, UINT64 R9_值, UINT64 rsp_20, UINT64 rsp_28, UINT64 rsp_30, UINT64 rsp_38, UINT64 CALL_地址)
{
	CallParam8 CALLArg;
	CALLArg.RCX = RCX_值;
	CALLArg.RDX = RDX_值;
	CALLArg.R8 = R8_值;
	CALLArg.R9 = R9_值;
	CALLArg.第5参数 = rsp_20;
	CALLArg.第6参数 = rsp_28;
	CALLArg.第7参数 = rsp_30;
	CALLArg.第8参数 = rsp_38;
	CALLArg.CALLAddr = CALL_地址;
	::SendMessageA(g_hWnd, 注册消息值, Msgid::CallCanUse3, (LPARAM)&CALLArg);
}
INT64 MainUniversalCALL8_Ret(UINT64 RCX_值, UINT64 RDX_值, UINT64 R8_值, UINT64 R9_值, UINT64 rsp_20, UINT64 rsp_28, UINT64 rsp_30, UINT64 rsp_38, UINT64 CALL_地址)
{
	CallParam8 CALLArg;
	CALLArg.RCX = RCX_值;
	CALLArg.RDX = RDX_值;
	CALLArg.R8 = R8_值;
	CALLArg.R9 = R9_值;
	CALLArg.第5参数 = rsp_20;
	CALLArg.第6参数 = rsp_28;
	CALLArg.第7参数 = rsp_30;
	CALLArg.第8参数 = rsp_38;
	CALLArg.CALLAddr = CALL_地址;
	SendMessageTimeoutA(g_hWnd, 注册消息值, Msgid::CallCanUse3, (LPARAM)&CALLArg, SMTO_NORMAL, 1000, 0);
	return CALLArg.RetVal;
}
int Random(int min, int max)
{
	srand(static_cast<unsigned int>(time(nullptr)));
	int 返回值;

	返回值 = rand() % (max - min + 1) + min;
	return 返回值;
}
CString 随机生成英文名字(int 长度)
{
	srand((unsigned)time(NULL));
	CString 返回值;
	for (int i = 0; i < 长度; i++)
	{
		int intValue = 'a' + rand() % 26;
		//int intValue = (int)(Random(1, 26) + 97);
		返回值 = 返回值 + (char)intValue;
	}
	return 返回值;

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
	if (x2 > x1 && y2 > y1) { // 第一象限
		TarAngle = (atan((y2 - y1) / (x2 - x1)) * 180 / PI);
	}
	if (x2 < x1 && y2 > y1) { // 第二象限
		TarAngle = (180 - (atan((y2 - y1) / (x1 - x2)) * 180 / PI));
	}
	if (x2 < x1 && y2 < y1) { // 第三象限
		TarAngle = (270 - (atan((x1 - x2) / (y1 - y2)) * 180 / PI));
	}
	if (x2 > x1 && y2 < y1) { // 第四象限
		TarAngle = (360 - (atan((y1 - y2) / (x2 - x1)) * 180 / PI));
	}
	if (x2 > x1 && y2 == y1) { // X轴正方向
		TarAngle = 0;
	}
	if (x2 < x1 && y2 == y1) { // X轴负方向
		TarAngle = 180;
	}
	if (x2 == x1 && y2 > y1) { // Y轴正方向
		TarAngle = 90;
	}
	if (x2 == x1 && y2 < y1) { // Y轴负方向
		TarAngle = 270;
	}
	if (x2 == x1 && y2 == y1) { // 原点
		TarAngle = 0;
	}
	TarAngle = TarAngle / 0.00549317;
	return (DWORD)TarAngle;
}

CString 整数到文本(DWORD64 整数)
{
	CString cStr;
	cStr.Format(_T("%ld"), 整数);
	return cStr;
}
CString getCommandIndex()
{
	CString Commadline = GetCommandLineW();
	int 索引 = Commadline.ReverseFind('=');
	CString ddindex = Commadline.Right(Commadline.GetLength() - 索引 - 1);
	return ddindex;
}