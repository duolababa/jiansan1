#pragma once
#include "pch.h"
class ǩ���ʼ�
{
public:
	static void get_ExpressMailList(vector<MailInfo_>& vsk);
	static BOOL bCheckExpressMailWndShow();
	static void Fun_ExpressMailDel(INT64 dMailId);
	static void Fun_ExpressMailGetItemAll(INT64 dMailId);
	static void Fun_ExpressMailSelectByIndex(int dIndex);
	static void Fun_ExpressMailWndShow();
	static void �ʼ���ȡ();
	static bool get_AttendanceList();
	static void Fun_AttendanceTake(INT64 dTabId, int k, int j);
	static int getCurHotTimeEventIndex();
	static void Fun_hottimeEventRewardTake(int dIndex);
	
};
class �ɾ���ȡ
{
public:

	static void getExpeditionInfo();

	static void Fun_ExpeditionInRecv_M(int dLev);
	static void get_BookListInfo();
	static void Fun_ExpeditionInRecv(int dLev);
	static void ��ս��ȡ();
};

