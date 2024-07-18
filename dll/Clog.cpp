////////****************************************************************************
////////****************************************************************************
//////作者：木易鹏
//////网址：www.godyang.com
//////时间：2016年10月28日
//////功能：MFC输出日志
//////使用说明：
//////1.添加引用LOG.h和LOG.cpp文件
//////2.需要输出日志时用以下代码：

//////LOG::D("调试");
//////LOG::I("信息");
//////LOG::W("警告");
//////LOG::E("错误");

//////3.需要删除日志是用以下代码：

//////LOG::DeleteLog();

//////其中，在LOG.h中的  LOGSAVEDAYS   为日志保存天数；
////////****************************************************************************
////////****************************************************************************

#include "pch.h"
#include "Clog.h"
LOG wlog;
#define LOG_EVENT _T("Global\\ChyLogWrite")  

HANDLE LOG::s_hWriteEvent = NULL;

//获取应用程序所在路径  创建log文件夹  获取log文件夹路径
CString LOG::CreatLogFolder()
{
	CString m_strFilePath = "D:\\txt.txt";
	m_strFilePath.ReleaseBuffer();
	int m_iPosIndex = m_strFilePath.ReverseFind('\\');


	CString 窗口名称 = "jiansan";

	//if (窗口名称 = L"")
	//{
	//	窗口名称 = 获取mir4config节点名称();
	//}
	CString m_strFilePath1 = m_strFilePath.Left(m_iPosIndex) + L"\\GameLog";
	CString m_strFilePath2 = m_strFilePath1 + L"\\" + 窗口名称;

	CFileFind m_FileFind;
	
	//bool i = m_FileFind.FindFile(m_strFilePath);
	//MyTrace(L"预创建 %s 是否找到 %d", m_strFilePath, i);
	if (!m_FileFind.FindFile(m_strFilePath1))
	{
		//MyTrace(L"创建 %s", m_strFilePath);
		CreateDirectoryW(m_strFilePath1, NULL);
	}
	if (!m_FileFind.FindFile(m_strFilePath2))
	{
		//MyTrace(L"创建 %s", m_strFilePath);
		CreateDirectoryW(m_strFilePath2, NULL);
	}

	return m_strFilePath2;
}


//////获取日志文件名
CString LOG::GetLogFileName()
{
	CString m_strFileName;
	m_strFileName = CTime::GetCurrentTime().Format(L"%Y-%m-%d") + L".log";
	return m_strFileName;
}

//////获取当前时间
CString LOG::GetNowTime()
{
	SYSTEMTIME st;
	CString m_strTime;
	GetLocalTime(&st);
	m_strTime.Format(L"%04d-%02d-%02d %02d:%02d:%02d.%03d", st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond, st.wMilliseconds);
	return m_strTime;
}

////将日志写进log文件
BOOL LOG::WriteLog(INT LOGLEVEL, CString m_strLogText)
{
	if (s_hWriteEvent == NULL)
	{
		s_hWriteEvent = OpenEvent(0, FALSE, LOG_EVENT);
		if (s_hWriteEvent == NULL)
			s_hWriteEvent = CreateEvent(NULL, FALSE, TRUE, LOG_EVENT);
	}
	WaitForSingleObject(s_hWriteEvent, INFINITE);
	try
	{
		//获取应用程序所在路径  创建log文件夹  获取log文件夹路径
		CString m_sLogFolderPath = CreatLogFolder();
		//////获取日志文件名
		CString m_sLogFileName = GetLogFileName();
		/////日志文件路径

		CString m_sLogFilePath = m_sLogFolderPath + L"\\" + m_sLogFileName;
		////文件操作
		CStdioFile m_SFile;
		setlocale(LC_CTYPE, ("chs"));
	
		if (m_SFile.Open(m_sLogFilePath, CFile::modeCreate | CFile::modeNoTruncate | CFile::modeReadWrite))
		{
			/////获取当前时间
			CString m_strTime = GetNowTime();
			//////日志 时间   ++   等级  ++ 内容
			CString m_sErrorMessage;
			////////日志---时间
			m_sErrorMessage = L"[" + m_strTime + L"] ";
			////////日志----等级
			switch (LOGLEVEL)
			{
			case LOGLEVELDEBUG:
				m_sErrorMessage += L"[ DEBUG ] ";
				break;
			case LOGLEVELINFO:
				m_sErrorMessage += L"[ INFO  ] ";
				break;
			case LOGLEVELWARN:
				m_sErrorMessage += L"[ WARN ] ";
				break;
			case LOGLEVELERROR:
				m_sErrorMessage += L"[ ERROR ] ";
				break;
			}
			////////日志----内容
			int 当前进程ID = GetCurrentProcessId();
			m_sErrorMessage+= L"[" + 整数到文本(当前进程ID) + L"] ";
			m_sErrorMessage += m_strLogText + L"\n";
			//////写日志文件
			m_SFile.SeekToEnd();
			//char* m_szMessage;
			//m_szMessage = (char*)(LPCTSTR)m_sErrorMessage;
			m_SFile.WriteString(m_sErrorMessage);
			//m_SFile.Write(m_szMessage, lstrlenA(m_szMessage));
			m_SFile.Close();
		}
		

		SetEvent(s_hWriteEvent);
	}
	catch (CFileException &CFileException)
	{
		return false;
	}
	return true;
}

////调试日志
BOOL LOG::D(CString m_strLogText, ...)
{
	TCHAR str_tmp[2048];
	va_list vArgList;                            //定义一个va_list型的变量,这个变量是指向参数的指针.
	va_start(vArgList, m_strLogText);                 //用va_start宏初始化变量,这个宏的第二个参数是第一个可变参数的前一个参数,是一个固定的参数
	_vsntprintf(str_tmp, 2048, m_strLogText, vArgList); //注意,不要漏掉前面的_
	va_end(vArgList);                            //用va_end宏结束可变参数的获取

	BOOL m_bwritelog = WriteLog(LOGLEVELDEBUG, str_tmp);
	return m_bwritelog;
}

////信息日志
BOOL LOG::I(CString m_strLogText, ...)
{
	TCHAR str_tmp[2048];
	va_list vArgList;                            //定义一个va_list型的变量,这个变量是指向参数的指针.
	va_start(vArgList, m_strLogText);                 //用va_start宏初始化变量,这个宏的第二个参数是第一个可变参数的前一个参数,是一个固定的参数
	_vsntprintf(str_tmp, 2048, m_strLogText, vArgList); //注意,不要漏掉前面的_
	va_end(vArgList);                            //用va_end宏结束可变参数的获取

	BOOL m_bwritelog = WriteLog(LOGLEVELINFO, str_tmp);
	return m_bwritelog;
}

////警告日志
BOOL LOG::W(CString m_strLogText, ...)
{


	TCHAR str_tmp[2048];
	va_list vArgList;                            //定义一个va_list型的变量,这个变量是指向参数的指针.
	va_start(vArgList, m_strLogText);                 //用va_start宏初始化变量,这个宏的第二个参数是第一个可变参数的前一个参数,是一个固定的参数
	_vsntprintf(str_tmp, 2048, m_strLogText, vArgList); //注意,不要漏掉前面的_
	va_end(vArgList);                            //用va_end宏结束可变参数的获取

	BOOL m_bwritelog = WriteLog(LOGLEVELWARN, str_tmp);
	return m_bwritelog;
}

////错误日志
BOOL LOG::E(CString m_strLogText, ...)
{
	TCHAR str_tmp[2048];
	va_list vArgList;                            //定义一个va_list型的变量,这个变量是指向参数的指针.
	va_start(vArgList, m_strLogText);                 //用va_start宏初始化变量,这个宏的第二个参数是第一个可变参数的前一个参数,是一个固定的参数
	_vsntprintf(str_tmp, 2048, m_strLogText, vArgList); //注意,不要漏掉前面的_
	va_end(vArgList);                            //用va_end宏结束可变参数的获取

	BOOL m_bwritelog = WriteLog(LOGLEVELERROR, str_tmp);
	return m_bwritelog;
}

//删除过期日志文件
void LOG::DeleteLog()
{

	//获取应用程序所在路径  创建log文件夹  获取log文件夹路径
	CString m_sLogFolderPath = CreatLogFolder();
	////日志文件路径
	CString strLogFile;
	strLogFile.Format(L"%s\\*.log", m_sLogFolderPath);
	CFileFind finder;

	BOOL bWorking = finder.FindFile(strLogFile);

	while (bWorking)
	{
		bWorking = finder.FindNextFile();

		CTime currentTime = CTime::GetCurrentTime();
		CTime timeFile;
		finder.GetLastAccessTime(timeFile);
		CTimeSpan ts = currentTime - timeFile;
		int nSecond = (int)ts.GetTotalSeconds();

		if (nSecond > LOGSAVEDAYS * 24 * 60 * 60)//超时，过期
		{
			CString strFile;
			strFile.Format(L"%s\\%s", m_sLogFolderPath, finder.GetFileName());
			DeleteFile(strFile);
		}
	}
}