#pragma once
#include <vector>

using namespace std;
/*---------------------------------------------------------------------*/
std::string utf8_to_string(const std::string& str);
std::string string_to_utf8(const std::string& str);
wstring	AsciiToUnicode(const string& str);
vector<string> �ָ��ַ���(const string& s, const string& c);
int Split(const string& str, vector<string>& ret_, string sep);
std::string ws2s(const std::wstring& ws);
char* UnicodeToAnsi(const wchar_t* szStr);
CString UTF82WCS(const char* szU8);
void DebugPrintf(char* pszFormat, ...);
void MainUniversalCALL2(UINT64 RCX_ֵ, UINT64 RDX_ֵ, UINT64 CALL_��ַ);
INT64 MainUniversalCALL2_Ret(UINT64 RCX_ֵ, UINT64 RDX_ֵ, UINT64 CALL_��ַ);
void MainUniversalCALL4(UINT64 RCX_ֵ, UINT64 RDX_ֵ, UINT64 R8_ֵ, UINT64 R9_ֵ, UINT64 CALL_��ַ);
INT64 MainUniversalCALL4_Ret(UINT64 RCX_ֵ, UINT64 RDX_ֵ, UINT64 R8_ֵ, UINT64 R9_ֵ, UINT64 CALL_��ַ);
void MainUniversalCALL6(UINT64 RCX_ֵ, UINT64 RDX_ֵ, UINT64 R8_ֵ, UINT64 R9_ֵ, UINT64 rsp_20, UINT64 rsp_28, UINT64 CALL_��ַ);
void MainUniversalCALL8(UINT64 RCX_ֵ, UINT64 RDX_ֵ, UINT64 R8_ֵ, UINT64 R9_ֵ, UINT64 rsp_20, UINT64 rsp_28, UINT64 rsp_30, UINT64 rsp_38, UINT64 CALL_��ַ);
INT64 MainUniversalCALL8_Ret(UINT64 RCX_ֵ, UINT64 RDX_ֵ, UINT64 R8_ֵ, UINT64 R9_ֵ, UINT64 rsp_20, UINT64 rsp_28, UINT64 rsp_30, UINT64 rsp_38, UINT64 CALL_��ַ);
float R_Float(ULONG64 ��_�ڴ��ַ);
double R_double(ULONG64 ��_�ڴ��ַ);

DWORD R_DW(ULONG64 ��_�ڴ��ַ);
BYTE R_BYTE(ULONG64 ��_�ڴ��ַ);
WORD R_W(ULONG64 ��_�ڴ��ַ);
wchar_t* R_CString(INT64 Ҫ��ȡ���ڴ��ַ);
char* R_String(INT64 Ҫ��ȡ���ڴ��ַ);
//int Readint(ULONG64 ��_�ڴ��ַ);
void W_DW(ULONG64 ��_�ڴ��ַ, DWORD ��_д������);
void W_Float(ULONG64 ��_�ڴ��ַ, float ��_д������);
void W_Word(ULONG64 ��_�ڴ��ַ, WORD ��_д������);
void W_QW(ULONG64 ��_�ڴ��ַ, UINT64 ��_д������);
void W_BYTE(ULONG64 ��_�ڴ��ַ, BYTE ��_д������);
void W_CString(INT64 �ڴ��ַ, CString ����);
UINT64 R_QW(UINT64 ��_�ڴ��ַ);
int Random(int min, int max);
/*---------------------------------------------------------------------*/


/*---------------------------------------------------------------------*/
#define __TRY_CODE__ try{
#define __CATCH_CODE__(WRONGSTR) }catch (...){	DebugPrintf(WRONGSTR);}
#define __CATCH_CODE_NUM__(WRONGSTR) }catch (...){	DebugPrintf(WRONGSTR); return NULL;}
#define __CATCH_CODE_MY__(WRONGSTR,MY) }catch (...){	DebugPrintf(WRONGSTR); return MY;}
/*---------------------------------------------------------------------*/


/*---------------------------------------------------------------------*/
// ���߳���ϢID�ṹ��
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


// 2������CALL�ṹ��
struct CallParam2
{
	UINT64 RCX;
	UINT64 RDX;
	UINT64 CALLAddr;
	UINT64 RetVal;
};
// 4������CALL�ṹ��
struct CallParam4
{
	UINT64 RCX;
	UINT64 RDX;
	UINT64 R8;
	UINT64 R9;
	UINT64 CALLAddr;
	UINT64 RetVal;
};

// 6������CALL�ṹ��
struct CallParam6
{
	UINT64 RCX;
	UINT64 RDX;
	UINT64 R8;
	UINT64 R9;
	UINT64 ��5����;
	UINT64 ��6����;
	UINT64 CALLAddr;
	UINT64 RetVal;
};
struct CallParam8
{
	UINT64 RCX;
	UINT64 RDX;
	UINT64 R8;
	UINT64 R9;
	UINT64 ��5����;
	UINT64 ��6����;
	UINT64 ��7����;
	UINT64 ��8����;
	UINT64 CALLAddr;
	UINT64 RetVal;
};
UINT64 CALL2(UINT64 RCX, UINT64 RDX, UINT64 CALL��ַ);
UINT64 CALL4(UINT64 RCX, UINT64 RDX, UINT64 R8, UINT64 R9, UINT64 CALL��ַ);
UINT64 CALL6(UINT64 RCX, UINT64 RDX, UINT64 R8, UINT64 R9, UINT64 ����5_ֵ, UINT64 ����6_ֵ, UINT64 CALL��ַ);
UINT64 CALL8(UINT64 RCX, UINT64 RDX, UINT64 R8, UINT64 R9, UINT64 ����5_ֵ, UINT64 ����6_ֵ, UINT64 ����7_ֵ, UINT64 ����8_ֵ, UINT64 CALL��ַ);
typedef UINT64(*CREYCALL2)(UINT64, UINT64);
/*---------------------------------------------------------------------*/
CString �������Ӣ������(int ����);
DWORD Get_Rel_Angle(float x1, float y1, float x2, float y2);
CString �������ı�(DWORD64 ����);
CString getCommandIndex();
CString randstr(const int len);

enum MyType
{
	�ֽ���,
	��������,
	������,
	��������,
	С����,
	˫����С����,
	�ı���,
};