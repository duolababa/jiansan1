////////****************************************************************************
////////****************************************************************************
//////作者：木易鹏
//////网址：www.godyang.com
//////时间：2016年10月28日
//////功能：MFC输出日志
//////使用说明：
//////1.添加引用LOG.h和LOG.cpp文件
//////2.需要输出日志时用以下代码：

//////LOG::D("调试%s","用法类似printf");
//////LOG::I("信息");
//////LOG::W("警告");
//////LOG::E("错误");

//////3.需要删除日志是用以下代码：

//////LOG::DeleteLog();

//////其中，在LOG.h中的  LOGSAVEDAYS   为日志保存天数；
////////****************************************************************************
////////****************************************************************************

#define LOGLEVELDEBUG 1
#define LOGLEVELINFO 2
#define LOGLEVELWARN 3
#define LOGLEVELERROR 4

#define LOGSAVEDAYS 1				//////日志保存天数
//////////////////////////////////////////////////////////////////
#pragma once

class LOG
{
public:

	//获取应用程序所在路径  创建log文件夹  获取log文件夹路径
	static CString CreatLogFolder();

	////////获取日志文件名
	static CString GetLogFileName();

	//////获取当前时间
	static CString GetNowTime();

	////将日志写进log文件
	static BOOL WriteLog(INT LOGLEVEL, CString m_strLogText);
	////调试日志
	static BOOL D(CString m_strLogText, ...);
	////信息日志
	static BOOL I(CString m_strLogText, ...);
	////警告日志
	static BOOL W(CString m_strLogText, ...);
	////错误日志
	static BOOL E(CString m_strLogText, ...);

	//删除过期日志文件
	static void DeleteLog();
protected:

	static HANDLE  s_hWriteEvent;

};
extern LOG wlog;