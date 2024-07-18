#include "pch.h"
#include "Log.h"


#define LOG_EVENT _T("Global\\ChyLogWrite")  
CString CLog::s_strLogFile = _T("");  
CString CLog::s_strLogPrefix = _T("");
CString CLog::s_errorInfo=_T("");
HANDLE CLog::s_hWriteEvent = NULL;  
CLog mlog;
#include <locale> 
CLog::CLog(void)
{

}


CLog::~CLog(void)
{
}

//设置路径和名称分为两种模式
//如果给出的不是绝对路径：在EXE所在的目录下，新建一个LOG文件夹，log文件夹下日志文件名称为SMMS2014-10-28.log
//如果给出的是绝对路径：则以绝对路径为准。
short CLog::SetLogFile(LPCTSTR strPath)
{
	//如果给的路径为空，则设置为xxx.log,目录为EXE同目录
	if (strPath==NULL)
	{
		// 得到当前的文件名
		CString m_strFilePath = "D:\\txt.txt";
		m_strFilePath.ReleaseBuffer();
		int m_iPosIndex = m_strFilePath.ReverseFind('\\');
		CString 窗口名称 = L"jiansan";
		m_strFilePath = m_strFilePath.Left(m_iPosIndex) + L"\\GameLog\\" + 窗口名称;
		s_strLogFile = m_strFilePath + L"\\" + CTime::GetCurrentTime().Format(L"%Y-%m-%d") + L".log";
	}
	else
	{
		s_strLogFile.Format(_T("%s.log"),strPath);
	} 
	return 1;
}

short CLog::SetPrefix(LPCTSTR strPrefix)
{
	if(strPrefix && strPrefix[0])
	{
		s_strLogPrefix = strPrefix;
	}
	return 1;
}
CString CLog::GetNowTime()
{
	SYSTEMTIME st;
	CString m_strTime;
	GetLocalTime(&st);
	m_strTime.Format(L"%d-%d-%d %d:%d:%d.%d", st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond, st.wMilliseconds);
	return m_strTime;
}

//清空当前的文件，新建
void CLog::CreateNewFile()
{
	//-打开关闭文件-
	if(s_strLogFile.IsEmpty())
		SetLogFile(NULL);
	CStdioFile file;
	if(!file.Open(s_strLogFile, CFile::modeCreate))
	{
		CString str;
		str.Format(_T("打开文件失败！路径为：%s"),s_strLogFile);
		AfxMessageBox(str);
		exit(0);
	}
	file.Close();
}

short CLog::GetDugInfo(LPCSTR pDugInfo/* =NULL */)
{
//	char file[16];  
////	char func[16];  
//	int line;   
//	sprintf(file,__FILE__); //文件名  
////	sprintf(func,__FUNCTION__);//函数名    
//	line=__LINE__;				//行号

	s_errorInfo.Format(_T("%s"),pDugInfo);

	return 1;
}

short CLog::WriteMsg(LPCTSTR strFormat)
{
	//--
	if(s_hWriteEvent==NULL)
	{
		s_hWriteEvent = OpenEvent(0, FALSE,LOG_EVENT);
		if(s_hWriteEvent==NULL)
			s_hWriteEvent = CreateEvent(NULL, FALSE, TRUE, LOG_EVENT); 
	}
	WaitForSingleObject(s_hWriteEvent, INFINITE);
	//-打开关闭文件-
	if(s_strLogFile.IsEmpty())
		SetLogFile(NULL);
	CStdioFile file;
	setlocale(LC_CTYPE, ("chs"));
	if(file.Open(s_strLogFile, CFile::modeCreate|CFile::modeNoTruncate|CFile::modeWrite))
	{
		file.SeekToEnd();

		CString   strPart_Time;
		{
			SYSTEMTIME sysTime  = {0};
			GetLocalTime(&sysTime);
			strPart_Time.Format(_T("%2d-%2d-%2d %2d:%2d:%2d"),  
			sysTime.wYear,sysTime.wMonth,sysTime.wDay,sysTime.wHour, sysTime.wMinute, sysTime.wSecond); 
		}
		CString  str;
		
		//str = _T("[") + strPart_Time + _T("]") + _T("\t") + s_errorInfo;
		//file.WriteString(str);
		s_errorInfo="";
		int 当前进程ID = GetCurrentProcessId();
		str = _T("[") + strPart_Time + _T("]") + _T("\t") + _T(" [") + 整数到文本(当前进程ID) + _T("]") + strFormat + _T("\n");
		file.WriteString(str);
		file.Close();
	}
	SetEvent(s_hWriteEvent);
	return 1;
}




