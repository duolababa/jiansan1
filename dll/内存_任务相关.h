#pragma once
#include "pch.h"
void ���÷ֶ������ѵ���();
class ����
{
public:



	static bool CALL_������(DWORD ����ID, DWORD �������);

	static bool CALL_������(DWORD ����ID);

	static ����_ CALL_ȡ��������(DWORD ����ID, INT64 objbase, INT64 dResAddr);

	//static ����_ CALL_ȡ��������(QuestInfo_ ����);

	static void getQuestCurStepInfo(INT64 dObj, QuestInfo_& bi, vector<SubQuestNeed_>& �����������);

	static void get_CurQuestList(vector<QuestInfo_>& vsk);

	static BOOL bCheckGuildQuestState(DWORD dQuestId);

	static void get_GuideList(vector<QuestInfo_>& vsk);

	static QuestInfo_ ȡ���ɽ�ָ������();

	//static QuestInfo_ ȡ���ɽ�ָ������(DWORD dQuestId);

	static QuestInfo_ ȡ����������();//5

	static QuestInfo_ ȡ����������();//2

	static QuestInfo_ ȡ������������();//2

	static QuestInfo_ ȡ����������();//!=2 !=0

	static QuestInfo_ ȡ��ָ����������(DWORD ����ID);

	static QuestInfo_ ȡ��ָ����������(DWORD ����ID);

	static QuestInfo_ ȡ��ָ��֧������(DWORD ����ID);

	static QuestInfo_ ȡ����������();//4

	static QuestInfo_ ȡ����������();//2

	static QuestInfo_ ȡ��Ѱ�ҷ�������();

	static bool �Ƿ��ѽ�����(DWORD ����ID);

	static void get_FinishQuestList(vector<DWORD>& vsk);

	static  bool �����Ƿ������(DWORD ����ID, vector<DWORD>& vsk);

	static int getNpcTaklEndSendArg(int dNpcResId, int dQuestId, int dStep);
	static int getNpcTaklEndSendArg1(int dNpcResId, int dQuestId, int dStep);
	static int bCheckQuestStepIsEndNpcTalk(INT64 dResAddr, DWORD dStep);

	static void Fun_�׶��������CALL(DWORD SendArg);

};

 INT64 getQuestResAddrById(DWORD dResId);

