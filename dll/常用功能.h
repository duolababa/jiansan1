#pragma once
#include "pch.h"

class ���ù���
{
public:

static string ʮ����תʮ������(unsigned long long n);
//atic std::string ����д(std::string str);
static DWORD ʮ������תʮ����(const char* RCX_ֵ);
static float �������(����_ ��ǰ����, ����_ �Է�����);

static INT64 hex_to_decimal(string hex_str);

};
CString ConvertDWORDToString(DWORD value);
CString FloatToString(float value);
//sscanf(����ID, "%x", x);