////////****************************************************************************
////////****************************************************************************
//////���ߣ�ľ����
//////��ַ��www.godyang.com
//////ʱ�䣺2016��10��28��
//////���ܣ�MFC�����־
//////ʹ��˵����
//////1.�������LOG.h��LOG.cpp�ļ�
//////2.��Ҫ�����־ʱ�����´��룺

//////LOG::D("����");
//////LOG::I("��Ϣ");
//////LOG::W("����");
//////LOG::E("����");

//////3.��Ҫɾ����־�������´��룺

//////LOG::DeleteLog();

//////���У���LOG.h�е�  LOGSAVEDAYS   Ϊ��־����������
////////****************************************************************************
////////****************************************************************************

#include "pch.h"
#include "Clog.h"
LOG wlog;
#define LOG_EVENT _T("Global\\ChyLogWrite")  

HANDLE LOG::s_hWriteEvent = NULL;

//��ȡӦ�ó�������·��  ����log�ļ���  ��ȡlog�ļ���·��
CString LOG::CreatLogFolder()
{
	CString m_strFilePath = "D:\\txt.txt";
	m_strFilePath.ReleaseBuffer();
	int m_iPosIndex = m_strFilePath.ReverseFind('\\');


	CString �������� = "jiansan";

	//if (�������� = L"")
	//{
	//	�������� = ��ȡmir4config�ڵ�����();
	//}
	CString m_strFilePath1 = m_strFilePath.Left(m_iPosIndex) + L"\\GameLog";
	CString m_strFilePath2 = m_strFilePath1 + L"\\" + ��������;

	CFileFind m_FileFind;
	
	//bool i = m_FileFind.FindFile(m_strFilePath);
	//MyTrace(L"Ԥ���� %s �Ƿ��ҵ� %d", m_strFilePath, i);
	if (!m_FileFind.FindFile(m_strFilePath1))
	{
		//MyTrace(L"���� %s", m_strFilePath);
		CreateDirectoryW(m_strFilePath1, NULL);
	}
	if (!m_FileFind.FindFile(m_strFilePath2))
	{
		//MyTrace(L"���� %s", m_strFilePath);
		CreateDirectoryW(m_strFilePath2, NULL);
	}

	return m_strFilePath2;
}


//////��ȡ��־�ļ���
CString LOG::GetLogFileName()
{
	CString m_strFileName;
	m_strFileName = CTime::GetCurrentTime().Format(L"%Y-%m-%d") + L".log";
	return m_strFileName;
}

//////��ȡ��ǰʱ��
CString LOG::GetNowTime()
{
	SYSTEMTIME st;
	CString m_strTime;
	GetLocalTime(&st);
	m_strTime.Format(L"%04d-%02d-%02d %02d:%02d:%02d.%03d", st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond, st.wMilliseconds);
	return m_strTime;
}

////����־д��log�ļ�
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
		//��ȡӦ�ó�������·��  ����log�ļ���  ��ȡlog�ļ���·��
		CString m_sLogFolderPath = CreatLogFolder();
		//////��ȡ��־�ļ���
		CString m_sLogFileName = GetLogFileName();
		/////��־�ļ�·��

		CString m_sLogFilePath = m_sLogFolderPath + L"\\" + m_sLogFileName;
		////�ļ�����
		CStdioFile m_SFile;
		setlocale(LC_CTYPE, ("chs"));
	
		if (m_SFile.Open(m_sLogFilePath, CFile::modeCreate | CFile::modeNoTruncate | CFile::modeReadWrite))
		{
			/////��ȡ��ǰʱ��
			CString m_strTime = GetNowTime();
			//////��־ ʱ��   ++   �ȼ�  ++ ����
			CString m_sErrorMessage;
			////////��־---ʱ��
			m_sErrorMessage = L"[" + m_strTime + L"] ";
			////////��־----�ȼ�
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
			////////��־----����
			int ��ǰ����ID = GetCurrentProcessId();
			m_sErrorMessage+= L"[" + �������ı�(��ǰ����ID) + L"] ";
			m_sErrorMessage += m_strLogText + L"\n";
			//////д��־�ļ�
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

////������־
BOOL LOG::D(CString m_strLogText, ...)
{
	TCHAR str_tmp[2048];
	va_list vArgList;                            //����һ��va_list�͵ı���,���������ָ�������ָ��.
	va_start(vArgList, m_strLogText);                 //��va_start���ʼ������,�����ĵڶ��������ǵ�һ���ɱ������ǰһ������,��һ���̶��Ĳ���
	_vsntprintf(str_tmp, 2048, m_strLogText, vArgList); //ע��,��Ҫ©��ǰ���_
	va_end(vArgList);                            //��va_end������ɱ�����Ļ�ȡ

	BOOL m_bwritelog = WriteLog(LOGLEVELDEBUG, str_tmp);
	return m_bwritelog;
}

////��Ϣ��־
BOOL LOG::I(CString m_strLogText, ...)
{
	TCHAR str_tmp[2048];
	va_list vArgList;                            //����һ��va_list�͵ı���,���������ָ�������ָ��.
	va_start(vArgList, m_strLogText);                 //��va_start���ʼ������,�����ĵڶ��������ǵ�һ���ɱ������ǰһ������,��һ���̶��Ĳ���
	_vsntprintf(str_tmp, 2048, m_strLogText, vArgList); //ע��,��Ҫ©��ǰ���_
	va_end(vArgList);                            //��va_end������ɱ�����Ļ�ȡ

	BOOL m_bwritelog = WriteLog(LOGLEVELINFO, str_tmp);
	return m_bwritelog;
}

////������־
BOOL LOG::W(CString m_strLogText, ...)
{


	TCHAR str_tmp[2048];
	va_list vArgList;                            //����һ��va_list�͵ı���,���������ָ�������ָ��.
	va_start(vArgList, m_strLogText);                 //��va_start���ʼ������,�����ĵڶ��������ǵ�һ���ɱ������ǰһ������,��һ���̶��Ĳ���
	_vsntprintf(str_tmp, 2048, m_strLogText, vArgList); //ע��,��Ҫ©��ǰ���_
	va_end(vArgList);                            //��va_end������ɱ�����Ļ�ȡ

	BOOL m_bwritelog = WriteLog(LOGLEVELWARN, str_tmp);
	return m_bwritelog;
}

////������־
BOOL LOG::E(CString m_strLogText, ...)
{
	TCHAR str_tmp[2048];
	va_list vArgList;                            //����һ��va_list�͵ı���,���������ָ�������ָ��.
	va_start(vArgList, m_strLogText);                 //��va_start���ʼ������,�����ĵڶ��������ǵ�һ���ɱ������ǰһ������,��һ���̶��Ĳ���
	_vsntprintf(str_tmp, 2048, m_strLogText, vArgList); //ע��,��Ҫ©��ǰ���_
	va_end(vArgList);                            //��va_end������ɱ�����Ļ�ȡ

	BOOL m_bwritelog = WriteLog(LOGLEVELERROR, str_tmp);
	return m_bwritelog;
}

//ɾ��������־�ļ�
void LOG::DeleteLog()
{

	//��ȡӦ�ó�������·��  ����log�ļ���  ��ȡlog�ļ���·��
	CString m_sLogFolderPath = CreatLogFolder();
	////��־�ļ�·��
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

		if (nSecond > LOGSAVEDAYS * 24 * 60 * 60)//��ʱ������
		{
			CString strFile;
			strFile.Format(L"%s\\%s", m_sLogFolderPath, finder.GetFileName());
			DeleteFile(strFile);
		}
	}
}