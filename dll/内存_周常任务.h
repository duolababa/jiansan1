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

void gei_guild(vector<工会_>& 日常);
void 搜索工会(CString name);
void 输入工会密码call(INT64 ID, CString 密码);
bool 打开工会签到界面();
void 工会捐赠(DWORD 金币);
void 离开工会();
bool 公会是否加入();
void 创建公会();



CString 加入的公会名称();