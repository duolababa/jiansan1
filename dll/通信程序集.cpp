#include "pch.h"
#include "ͨ�ų���.h"
int udpsocket��� = 0;
//sockaddr fs;
struct sockaddr_in fs;

bool UDP����(char* ����IP, int �˿�, CString ��������)
{
	USES_CONVERSION;
	char* ��������A = T2A(��������);
	if (udpsocket��� == 0)
	{
		WSADATA �׽�����Ϣ;
		WSAStartup(257, &�׽�����Ϣ);
		udpsocket��� = socket(AF_INET, SOCK_DGRAM, 17);
	}
	fs.sin_family = AF_INET;
	fs.sin_addr.s_addr = inet_addr(����IP);
	fs.sin_port = htons(�˿�);
	if (sendto(udpsocket���, ��������A, strlen(��������A), 0, (struct sockaddr*)&fs, sizeof(fs)) == -1)
	{
		return false;
	}
	return true;

}
void ���͸�����̨(CString ��ͷ, CString ����)
{
	UDP����("127.0.0.1", 38384, ��ͷ + L";" + ����);
}

void ���͸�����̨1(CString ��ͷ, CString ����, CString ����)
{
    UDP����("127.0.0.1", 38384, ��ͷ + L";" + ���� + L";" + ����);
}
CString GetLocalIP()
{
    USES_CONVERSION;
    WSADATA wsaData;
    int err = WSAStartup(MAKEWORD(2, 0), &wsaData);
    if (err != 0)
    {
        return L"";
    }

    char szHostName[MAX_PATH] = { 0 };
    int nRetCode;
    nRetCode = gethostname(szHostName, sizeof(szHostName));

    char* lpLocalIP;
    PHOSTENT hostinfo;

    if (nRetCode != 0)
    {
        WSACleanup();
        return L"";
    }

    hostinfo = gethostbyname(szHostName);
    lpLocalIP = inet_ntoa(*(struct in_addr*)*hostinfo->h_addr_list);

    WSACleanup();

    return A2W(lpLocalIP);
}

//void ����_�ʸ���֤uri()
//{
//    if (�ܿ�IP != L"")
//    {
//        USES_CONVERSION;
//        CString ����IP = GetLocalIP();
//        CString ��������;
//        CString �˺��ִ� = bCheckAccountVerfiy();
//        CString url = L"https://humanverify.mir4global.com/web/captcha/auth?VerifyID=" + ����_Base64����(�˺��ִ�);
//        //MyTrace(L"�ʸ���֤:%s %s", url, �ܿ�IP);
//        if (�������� == L"")
//        {
//            �������� = L"δ֪����";
//        }
//        ��������.Format(L"%s|%s|%s", ����IP, ��������, url);
// 
//        UDP����(W2A(�ܿ�IP), 19830, L"�ʸ���֤;" + ��������);
//        SendMessageToMoConter03(200, L"�ʸ���֤;" + ��������);
//    }
//}