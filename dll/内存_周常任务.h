#pragma once
#include "pch.h"
class 周常任务
{
public:
	static int getUnasTaskPoint();
	static BOOL CheckQuestInProgress(int dQuestId);
	static BOOL Fun_CheckUnasWeeklyQuestCon(int dQuestId);
	static INT64 Fun_getQuestrResAddrById(int dQuestId);
	static void get_UnasDailyQuestList(vector<周长日常_>& 日常);
	static void get_UnasWeeklyQuesList(vector<周长日常_>& 日常);
	static int 周常任务状态(int dQuestId);
	static int 日常任务状态(int dQuestId);
	static int 周长积分();

	static void 领取徽章();

};

