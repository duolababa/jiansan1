#pragma once
class CLog
{
public:
	CLog(void);
	~CLog(void);

	//-��־�ļ�-
	//---���û��ָ������ΪEXE����·���µ�LOG\\EXEName.log	
	static short SetLogFile(LPCTSTR strPath=NULL);

	//-ǰ׺-
	//---������������ͬһ���ļ������־������Ϊÿ����������һ��ǰ׺---
	//---ǰ׺����������ʱ��֮ǰ---
	static short SetPrefix(LPCTSTR strPrefix);
	static CString GetNowTime();
	//��ȡ������Ϣ���������ƺ��кţ�
	static short GetDugInfo(LPCSTR pDugInfo=NULL);

	//�½��ļ�
	static void CreateNewFile();

	//-��־��Ϣ-
	//---д����־��Ϣ---
	static short  WriteMsg(LPCTSTR strFormat = NULL);

protected:
	static CString s_errorInfo;
	static CString s_strLogFile;
	static CString s_strLogPrefix;
	static HANDLE  s_hWriteEvent;
};
extern CLog mlog;
