#pragma once
#include "pch.h"
class �ܳ�����
{
public:
	static int getUnasTaskPoint();
	static BOOL CheckQuestInProgress(int dQuestId);
	static BOOL Fun_CheckUnasWeeklyQuestCon(int dQuestId);
	static INT64 Fun_getQuestrResAddrById(int dQuestId);
	static void get_UnasDailyQuestList(vector<�ܳ��ճ�_>& �ճ�);
	static void get_UnasWeeklyQuesList(vector<�ܳ��ճ�_>& �ճ�);
	static int �ܳ�����״̬(int dQuestId);
	static int �ճ�����״̬(int dQuestId);
	static int �ܳ�����();

	static void ��ȡ����();

};

void gei_guild(vector<����_>& �ճ�);
void ��������(CString name);
void ���빤������call(INT64 ID, CString ����);
bool �򿪹���ǩ������();
void �������(DWORD ���);
void �뿪����();
bool �����Ƿ����();
void ��������();



CString ����Ĺ�������();