#pragma once

#include "pch.h"
//void getUiList(vector<UIinfo_>& vsk);
class UI����
{
public:
	static void getUiList(vector<UIinfo_>& vsk);
	static INT64 getUiObjById(DWORD ID);
	static INT64 getUiObjByName(CString name);
	static DWORD getUiIdByName(CString name);
	static INT64 getUiObjById_Old(DWORD ID);
	static bool Ѱ�Ҵ򿪴���(CString name, INT64& rcx);

	static void ������븱��();
	static CString �ڵ�Ψһ��ʶ(INT64 ����, INT64& ���ض���);

	static bool �ڴ水��1(DWORD ���ܰ���, DWORD ���� = 2);
	static bool �ڴ水��(DWORD ���ܰ���, DWORD ����=2);
	static bool ��ͼ�Ƿ��();
	static bool �����ɱ���Ľ����Ƿ��();
	static bool �����������Ƿ���ʾ();
	static bool ���������Ƿ���ʾ();
	static bool ���ͼ�Ƿ���ʾ();
	static bool ����ְҵ�н����Ƿ���ʾ();
	static bool ���������Ƿ��();
	static bool ��������();
	static bool �������();
	static bool ���븱��();
	static bool �Ƿ����G();
	static bool �Ƿ����();
	static bool �Ƿ��ں���׼������();
	static bool �Ƿ��ڽ����������();
	static bool ׼������();
	static bool getMsgBoxTextList();
	static CString getMsgBoxMiddleText2(INT64 dUIObj);
	static CString getMsgBoxText();
	static CString getMsgBoxText_ȫ();
	static void getNpcTalkSelectList(vector<CString>& �Ի���);
	static bool ָ��UI�Ƿ���ʾ(CString UIName);
	static bool �̵��Ƿ��();
	static bool �˳��˵��Ƿ��();
	static bool UI����::��������Ƿ���ʾ();
	static bool ����(CString ���ʽ);
	static int UI����::get_DeadSceneList(CString ���ʽ);
	static CString getUiName(INT64 dObjAddr);
	static bool get_DeadSceneListBtnState();
	static int getGameCurStageValue();
	static bool bCheckItemDisassemleWnd();
	static void Fun_UiShowCtrl(int dUiId);
	static DWORD ��������();
	static CString UI����(INT64 ����);
	static CString UI����1(INT64 ����);
	static void �ؼ����call(INT64 ����);
	static CString ���ڷ����ı�();
	static bool ��ϷIP�쳣();
	static void UI����::�ؼ�����call(INT64 ����, CString name);
	//static void Fun_NarrationAssistance_OnOff(int kaiguan);
	//static void Fun_NarrationAssistance_Continue();
	/*void generateBmp(BYTE* pData, int width, int height, LPCTSTR filename);
	void ����(BYTE* pDATA, int ���, int �߶�, LPCTSTR ·��);*/
private:
};

INT64 getChildUiAddrByStr(INT64 dParentAddr, CString cChildName);
INT64 getUiFirstAddr(INT64 dUiObj);
CString UTF82WCS(const char* szU8);
void Fun_MsgBoxConfirm(INT64 dUIObj);
void ������һ��();
void ����ѡ�();