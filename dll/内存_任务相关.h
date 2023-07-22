#pragma once
#include "pch.h"
void 设置分段坐标已到达();
class 任务
{
public:



	static bool CALL_交任务(DWORD 任务ID, DWORD 奖励序号);

	static bool CALL_接任务(DWORD 任务ID);

	static 坐标_ CALL_取任务坐标(DWORD 任务ID, INT64 objbase, INT64 dResAddr);

	//static 坐标_ CALL_取任务坐标(QuestInfo_ 任务);

	static void getQuestCurStepInfo(INT64 dObj, QuestInfo_& bi, vector<SubQuestNeed_>& 子任务进度组);

	static void get_CurQuestList(vector<QuestInfo_>& vsk);

	static BOOL bCheckGuildQuestState(DWORD dQuestId);

	static void get_GuideList(vector<QuestInfo_>& vsk);

	static QuestInfo_ 取出可接指引任务();

	//static QuestInfo_ 取出可接指引任务(DWORD dQuestId);

	static QuestInfo_ 取出世界任务();//5

	static QuestInfo_ 取出主线任务();//2

	static QuestInfo_ 取出主线子任务();//2

	static QuestInfo_ 取出其他任务();//!=2 !=0

	static QuestInfo_ 取出指定主线任务(DWORD 任务ID);

	static QuestInfo_ 取出指定世界任务(DWORD 任务ID);

	static QuestInfo_ 取出指定支线任务(DWORD 任务ID);

	static QuestInfo_ 取出触发任务();//4

	static QuestInfo_ 取出副本任务();//2

	static QuestInfo_ 取出寻找方舟任务();

	static bool 是否已接任务(DWORD 任务ID);

	static void get_FinishQuestList(vector<DWORD>& vsk);

	static  bool 任务是否已完成(DWORD 任务ID, vector<DWORD>& vsk);

	static int getNpcTaklEndSendArg(int dNpcResId, int dQuestId, int dStep);
	static int getNpcTaklEndSendArg1(int dNpcResId, int dQuestId, int dStep);
	static int bCheckQuestStepIsEndNpcTalk(INT64 dResAddr, DWORD dStep);

	static void Fun_阶段任务完成CALL(DWORD SendArg);

};

 INT64 getQuestResAddrById(DWORD dResId);

