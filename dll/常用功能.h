#pragma once
#include "pch.h"

class 常用功能
{
public:

static string 十进制转十六进制(unsigned long long n);
//atic std::string 到大写(std::string str);
static DWORD 十六进制转十进制(const char* RCX_值);
static float 计算距离(坐标_ 当前距离, 坐标_ 对方距离);

static INT64 hex_to_decimal(string hex_str);

};
CString ConvertDWORDToString(DWORD value);
CString FloatToString(float value);
//sscanf(任务ID, "%x", x);