
#include "常用功能.h"
#include <string>
#include <atlstr.h>
#include <iomanip>  
#include <sstream>  
CString ConvertDWORDToString(DWORD value)
{
	char buffer[1000]; // 缓冲区，根据需要自行调整大小  
	sprintf_s(buffer, sizeof(buffer), "%lu", value); // 将DWORD转换为字符串  
	return CString(buffer);
}

CString FloatToString(float value)
{
	char buffer[50];
	sprintf_s(buffer, sizeof(buffer), "%.2f", value);

	return buffer;
}


string 常用功能::十进制转十六进制(unsigned long long n) {
	const char* hex_table = "0123456789ABCDEF";
	string hex_str = "";
	while (n > 0) {
		unsigned int remainder = n % 16;
		hex_str = hex_table[remainder] + hex_str;
		n /= 16;
	}
	return hex_str.empty() ? "0" : hex_str;
}

//std::string 常用功能:: 到大写(std::string str) { //将字符串转换为大写字母
//	std::transform(str.begin(), str.end(), str.begin(), [](unsigned char c) { return std::toupper(c); });
//	return str;
//}


float 常用功能::计算距离(坐标_ 当前距离, 坐标_ 对方距离)
{

	/*double dx = abs(x - 角色信息.坐标.x);
	double dy = abs(y - 角色信息.坐标.y);
	double dz = abs(z - 角色信息.坐标.z);

	double xyz = sqrt(pow(dx, 2) + pow(dy, 2) + pow(dz, 2)) / 100;*/


	////MyTrace(L"对方坐标%0.f/%0.f/%0.f  \n", 对方距离.x, 对方距离.y, 对方距离.z);
	////MyTrace(L"当前坐标%0.f/%0.f/%0.f  \n", 当前距离.x, 当前距离.y, 当前距离.z);
	float dx = abs(当前距离.x - 对方距离.x);
	float dy = abs(当前距离.y - 对方距离.y);
	float dz = abs(当前距离.z - 对方距离.z);

	float x11 = pow(dx, 2);

	float x22 = pow(dy, 2);
	float x33 = pow(dz, 2);

	float xyz = sqrt(x11 + x22+ x33);
	//float xyz = float xyz = sqrt(x11 + x22); / 100;
	////MyTrace(L"最终距离%0.f\n", xyz);
	return xyz/100;

}

long long 常用功能::hex_to_decimal(string hex_str) {
	long long decimal_num = stoll(hex_str, nullptr, 16);
	return decimal_num;
}



DWORD 常用功能::十六进制转十进制(const char* RCX_值)
{
	DWORD x=0;

		std::string hex_str = RCX_值; // 十六进制字符串
		int decimal_value = std::stoi(hex_str, nullptr, 16); // 使用 stoi 函数转换为十进制数值
		//std::cout << "十六进制字符串 " << hex_str << " 转换为十进制数值为 " << decimal_value << std::endl;
	
	//sscanf(RCX_值, "%X", x);
	return decimal_value;

}

//std::string CStringToString(const CString& cstr)
//{
//	if (IsBadReadPtr((const void*)_pHostBase, sizeof(_pHostBase))) return L"";
//	ULONG_PTR Name = R_ULONGPTR(_pHostBase + OFF_HOSTNAME);
//	if (IsBadReadPtr((const void*)Name, sizeof(Name))) return L"";
//	string pName = (char*)Name;
//	pName = utf8_to_string(pName);
//	CString c_name = CString(pName.c_str());
//	return c_name;
//}