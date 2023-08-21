#include "pch.h"
#include "通信程序集.h"
int udpsocket句柄 = 0;
//sockaddr fs;
struct sockaddr_in fs;

bool UDP发送(char* 发送IP, int 端口, CString 发送内容)
{
	USES_CONVERSION;
	char* 发送内容A = T2A(发送内容);
	if (udpsocket句柄 == 0)
	{
		WSADATA 套接字信息;
		WSAStartup(257, &套接字信息);
		udpsocket句柄 = socket(AF_INET, SOCK_DGRAM, 17);
	}
	fs.sin_family = AF_INET;
	fs.sin_addr.s_addr = inet_addr(发送IP);
	fs.sin_port = htons(端口);
	if (sendto(udpsocket句柄, 发送内容A, strlen(发送内容A), 0, (struct sockaddr*)&fs, sizeof(fs)) == -1)
	{
		return false;
	}
	return true;

}
void 发送给控制台(CString 包头, CString 内容)
{
	UDP发送("127.0.0.1", 38384, 包头 + L";" + 内容);
}

void 发送给控制台1(CString 包头, CString 包中, CString 内容)
{
    UDP发送("127.0.0.1", 38384, 包头 + L";" + 包中 + L";" + 内容);
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

//void 发送_资格验证uri()
//{
//    if (总控IP != L"")
//    {
//        USES_CONVERSION;
//        CString 本机IP = GetLocalIP();
//        CString 发送数据;
//        CString 账号字串 = bCheckAccountVerfiy();
//        CString url = L"https://humanverify.mir4global.com/web/captcha/auth?VerifyID=" + 编码_Base64编码(账号字串);
//        //MyTrace(L"资格验证:%s %s", url, 总控IP);
//        if (窗口名称 == L"")
//        {
//            窗口名称 = L"未知窗口";
//        }
//        发送数据.Format(L"%s|%s|%s", 本机IP, 窗口名称, url);
// 
//        UDP发送(W2A(总控IP), 19830, L"资格验证;" + 发送数据);
//        SendMessageToMoConter03(200, L"资格验证;" + 发送数据);
//    }
//}