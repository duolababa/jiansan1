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

//����·�������Ʒ�Ϊ����ģʽ
//��������Ĳ��Ǿ���·������EXE���ڵ�Ŀ¼�£��½�һ��LOG�ļ��У�log�ļ�������־�ļ�����ΪSMMS2014-10-28.log
//����������Ǿ���·�������Ծ���·��Ϊ׼��
short CLog::SetLogFile(LPCTSTR strPath)
{
	//�������·��Ϊ�գ�������Ϊxxx.log,Ŀ¼ΪEXEͬĿ¼
	if (strPath==NULL)
	{
		// �õ���ǰ���ļ���
		CString m_strFilePath = "D:\\txt.txt";
		m_strFilePath.ReleaseBuffer();
		int m_iPosIndex = m_strFilePath.ReverseFind('\\');
		CString �������� = L"jiansan";
		m_strFilePath = m_strFilePath.Left(m_iPosIndex) + L"\\GameLog\\" + ��������;
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

//��յ�ǰ���ļ����½�
void CLog::CreateNewFile()
{
	//-�򿪹ر��ļ�-
	if(s_strLogFile.IsEmpty())
		SetLogFile(NULL);
	CStdioFile file;
	if(!file.Open(s_strLogFile, CFile::modeCreate))
	{
		CString str;
		str.Format(_T("���ļ�ʧ�ܣ�·��Ϊ��%s"),s_strLogFile);
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
//	sprintf(file,__FILE__); //�ļ���  
////	sprintf(func,__FUNCTION__);//������    
//	line=__LINE__;				//�к�

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
	//-�򿪹ر��ļ�-
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
		int ��ǰ����ID = GetCurrentProcessId();
		str = _T("[") + strPart_Time + _T("]") + _T("\t") + _T(" [") + �������ı�(��ǰ����ID) + _T("]") + strFormat + _T("\n");
		file.WriteString(str);
		file.Close();
	}
	SetEvent(s_hWriteEvent);
	return 1;
}




