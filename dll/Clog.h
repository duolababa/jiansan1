////////****************************************************************************
////////****************************************************************************
//////���ߣ�ľ����
//////��ַ��www.godyang.com
//////ʱ�䣺2016��10��28��
//////���ܣ�MFC�����־
//////ʹ��˵����
//////1.�������LOG.h��LOG.cpp�ļ�
//////2.��Ҫ�����־ʱ�����´��룺

//////LOG::D("����%s","�÷�����printf");
//////LOG::I("��Ϣ");
//////LOG::W("����");
//////LOG::E("����");

//////3.��Ҫɾ����־�������´��룺

//////LOG::DeleteLog();

//////���У���LOG.h�е�  LOGSAVEDAYS   Ϊ��־����������
////////****************************************************************************
////////****************************************************************************

#define LOGLEVELDEBUG 1
#define LOGLEVELINFO 2
#define LOGLEVELWARN 3
#define LOGLEVELERROR 4

#define LOGSAVEDAYS 1				//////��־��������
//////////////////////////////////////////////////////////////////
#pragma once

class LOG
{
public:

	//��ȡӦ�ó�������·��  ����log�ļ���  ��ȡlog�ļ���·��
	static CString CreatLogFolder();

	////////��ȡ��־�ļ���
	static CString GetLogFileName();

	//////��ȡ��ǰʱ��
	static CString GetNowTime();

	////����־д��log�ļ�
	static BOOL WriteLog(INT LOGLEVEL, CString m_strLogText);
	////������־
	static BOOL D(CString m_strLogText, ...);
	////��Ϣ��־
	static BOOL I(CString m_strLogText, ...);
	////������־
	static BOOL W(CString m_strLogText, ...);
	////������־
	static BOOL E(CString m_strLogText, ...);

	//ɾ��������־�ļ�
	static void DeleteLog();
protected:

	static HANDLE  s_hWriteEvent;

};
extern LOG wlog;