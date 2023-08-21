#pragma once
#include <vector>

using namespace std;
/*---------------------------------------------------------------------*/
std::string utf8_to_string(const std::string& str);
std::string string_to_utf8(const std::string& str);
wstring	AsciiToUnicode(const string& str);
vector<string> 分割字符串(const string& s, const string& c);
int Split(const string& str, vector<string>& ret_, string sep);
std::string ws2s(const std::wstring& ws);
char* UnicodeToAnsi(const wchar_t* szStr);
CString UTF82WCS(const char* szU8);
void DebugPrintf(char* pszFormat, ...);
void MainUniversalCALL2(UINT64 RCX_值, UINT64 RDX_值, UINT64 CALL_地址);
INT64 MainUniversalCALL2_Ret(UINT64 RCX_值, UINT64 RDX_值, UINT64 CALL_地址);
void MainUniversalCALL4(UINT64 RCX_值, UINT64 RDX_值, UINT64 R8_值, UINT64 R9_值, UINT64 CALL_地址);
INT64 MainUniversalCALL4_Ret(UINT64 RCX_值, UINT64 RDX_值, UINT64 R8_值, UINT64 R9_值, UINT64 CALL_地址);
void MainUniversalCALL6(UINT64 RCX_值, UINT64 RDX_值, UINT64 R8_值, UINT64 R9_值, UINT64 rsp_20, UINT64 rsp_28, UINT64 CALL_地址);
void MainUniversalCALL8(UINT64 RCX_值, UINT64 RDX_值, UINT64 R8_值, UINT64 R9_值, UINT64 rsp_20, UINT64 rsp_28, UINT64 rsp_30, UINT64 rsp_38, UINT64 CALL_地址);
INT64 MainUniversalCALL8_Ret(UINT64 RCX_值, UINT64 RDX_值, UINT64 R8_值, UINT64 R9_值, UINT64 rsp_20, UINT64 rsp_28, UINT64 rsp_30, UINT64 rsp_38, UINT64 CALL_地址);
float R_Float(ULONG64 参_内存地址);
double R_double(ULONG64 参_内存地址);

DWORD R_DW(ULONG64 参_内存地址);
BYTE R_BYTE(ULONG64 参_内存地址);
WORD R_W(ULONG64 参_内存地址);
wchar_t* R_CString(INT64 要读取的内存地址);
char* R_String(INT64 要读取的内存地址);
//int Readint(ULONG64 参_内存地址);
void W_DW(ULONG64 参_内存地址, DWORD 参_写入数据);
void W_Float(ULONG64 参_内存地址, float 参_写入数据);
void W_Word(ULONG64 参_内存地址, WORD 参_写入数据);
void W_QW(ULONG64 参_内存地址, UINT64 参_写入数据);
void W_BYTE(ULONG64 参_内存地址, BYTE 参_写入数据);
void W_CString(INT64 内存地址, CString 内容);
UINT64 R_QW(UINT64 参_内存地址);
int Random(int min, int max);
/*---------------------------------------------------------------------*/


/*---------------------------------------------------------------------*/
#define __TRY_CODE__ try{
#define __CATCH_CODE__(WRONGSTR) }catch (...){	DebugPrintf(WRONGSTR);}
#define __CATCH_CODE_NUM__(WRONGSTR) }catch (...){	DebugPrintf(WRONGSTR); return NULL;}
#define __CATCH_CODE_MY__(WRONGSTR,MY) }catch (...){	DebugPrintf(WRONGSTR); return MY;}
/*---------------------------------------------------------------------*/


/*---------------------------------------------------------------------*/
// 主线程消息ID结构体
enum Msgid
{
	CallCanUse,
	CallCanUse1,
	CallCanUse2,
	CallCanUse3,
	CallLua,
	Mouse,
	CALLCanArrive,
	CALLExpeditionInRecv,
};

union Base
{
	QWORD address;
	BYTE data[8];
};


// 2个参数CALL结构体
struct CallParam2
{
	UINT64 RCX;
	UINT64 RDX;
	UINT64 CALLAddr;
	UINT64 RetVal;
};
// 4个参数CALL结构体
struct CallParam4
{
	UINT64 RCX;
	UINT64 RDX;
	UINT64 R8;
	UINT64 R9;
	UINT64 CALLAddr;
	UINT64 RetVal;
};

// 6个参数CALL结构体
struct CallParam6
{
	UINT64 RCX;
	UINT64 RDX;
	UINT64 R8;
	UINT64 R9;
	UINT64 第5参数;
	UINT64 第6参数;
	UINT64 CALLAddr;
	UINT64 RetVal;
};
struct CallParam8
{
	UINT64 RCX;
	UINT64 RDX;
	UINT64 R8;
	UINT64 R9;
	UINT64 第5参数;
	UINT64 第6参数;
	UINT64 第7参数;
	UINT64 第8参数;
	UINT64 CALLAddr;
	UINT64 RetVal;
};
UINT64 CALL2(UINT64 RCX, UINT64 RDX, UINT64 CALL地址);
UINT64 CALL4(UINT64 RCX, UINT64 RDX, UINT64 R8, UINT64 R9, UINT64 CALL地址);
UINT64 CALL6(UINT64 RCX, UINT64 RDX, UINT64 R8, UINT64 R9, UINT64 参数5_值, UINT64 参数6_值, UINT64 CALL地址);
UINT64 CALL8(UINT64 RCX, UINT64 RDX, UINT64 R8, UINT64 R9, UINT64 参数5_值, UINT64 参数6_值, UINT64 参数7_值, UINT64 参数8_值, UINT64 CALL地址);
typedef UINT64(*CREYCALL2)(UINT64, UINT64);
/*---------------------------------------------------------------------*/
CString 随机生成英文名字(int 长度);
DWORD Get_Rel_Angle(float x1, float y1, float x2, float y2);
CString 整数到文本(DWORD64 整数);
CString getCommandIndex();
CString randstr(const int len);

enum MyType
{
	字节型,
	短整数型,
	整数型,
	长整数型,
	小数型,
	双精度小数型,
	文本型,
};