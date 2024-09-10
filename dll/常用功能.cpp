
#include "���ù���.h"
#include <string>
#include <atlstr.h>
#include <iomanip>  
#include <sstream>  
CString ConvertDWORDToString(DWORD value)
{
	char buffer[1000]; // ��������������Ҫ���е�����С  
	sprintf_s(buffer, sizeof(buffer), "%lu", value); // ��DWORDת��Ϊ�ַ���  
	return CString(buffer);
}

CString FloatToString(float value)
{
	char buffer[50];
	sprintf_s(buffer, sizeof(buffer), "%.2f", value);

	return buffer;
}


string ���ù���::ʮ����תʮ������(unsigned long long n) {
	const char* hex_table = "0123456789ABCDEF";
	string hex_str = "";
	while (n > 0) {
		unsigned int remainder = n % 16;
		hex_str = hex_table[remainder] + hex_str;
		n /= 16;
	}
	return hex_str.empty() ? "0" : hex_str;
}

//std::string ���ù���:: ����д(std::string str) { //���ַ���ת��Ϊ��д��ĸ
//	std::transform(str.begin(), str.end(), str.begin(), [](unsigned char c) { return std::toupper(c); });
//	return str;
//}


float ���ù���::�������(����_ ��ǰ����, ����_ �Է�����)
{

	/*double dx = abs(x - ��ɫ��Ϣ.����.x);
	double dy = abs(y - ��ɫ��Ϣ.����.y);
	double dz = abs(z - ��ɫ��Ϣ.����.z);

	double xyz = sqrt(pow(dx, 2) + pow(dy, 2) + pow(dz, 2)) / 100;*/


	////MyTrace(L"�Է�����%0.f/%0.f/%0.f  \n", �Է�����.x, �Է�����.y, �Է�����.z);
	////MyTrace(L"��ǰ����%0.f/%0.f/%0.f  \n", ��ǰ����.x, ��ǰ����.y, ��ǰ����.z);
	float dx = abs(��ǰ����.x - �Է�����.x);
	float dy = abs(��ǰ����.y - �Է�����.y);
	float dz = abs(��ǰ����.z - �Է�����.z);

	float x11 = pow(dx, 2);

	float x22 = pow(dy, 2);
	float x33 = pow(dz, 2);

	float xyz = sqrt(x11 + x22+ x33);
	//float xyz = float xyz = sqrt(x11 + x22); / 100;
	////MyTrace(L"���վ���%0.f\n", xyz);
	return xyz/100;

}

long long ���ù���::hex_to_decimal(string hex_str) {
	long long decimal_num = stoll(hex_str, nullptr, 16);
	return decimal_num;
}



DWORD ���ù���::ʮ������תʮ����(const char* RCX_ֵ)
{
	DWORD x=0;

		std::string hex_str = RCX_ֵ; // ʮ�������ַ���
		int decimal_value = std::stoi(hex_str, nullptr, 16); // ʹ�� stoi ����ת��Ϊʮ������ֵ
		//std::cout << "ʮ�������ַ��� " << hex_str << " ת��Ϊʮ������ֵΪ " << decimal_value << std::endl;
	
	//sscanf(RCX_ֵ, "%X", x);
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