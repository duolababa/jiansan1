#pragma once
#include "pch.h"
class ��½
{
public:

	static int ����������(vector<CString>& vsk);

	static int ��ѯ���������(CString ����������);

	static bool �Ƿ��ڷ���������();

	static bool CALL_ѡ�������(CString ����������);

	static bool �Ƿ����ȷ��Э��();

	static bool CALL_ȷ��Э��();

	static bool CALL_ѡ��ְҵ(CString ְҵ��);

	static bool �Ƿ���׼������();

	static bool �Ƿ��ڴ�����ɫ����();

	static bool �Ƿ���ѡ��ְҵ����();

	static bool CALL_������ɫ(int ��������);

	static bool CALL_�򿪴�����ɫ(int ���);
	static bool ��¼�����ɫ(int ���);

	//static int  CALL_��ɫ����(vector<��½��ɫ��Ϣ_>& vsk);

	static void get_CharacterList(vector<��½��ɫ��Ϣ_>& vsk);

	static ��½��ɫ��Ϣ_ getCharacterInfoByIndex(int ���);
	static int ȡ��������ɽ�ɫ����();
	static ��½��ɫ��Ϣ_ getCharacterInfoByName(CString Name);

	static bool CALL_������Ϸ(int ��ɫ���);

	static void ��ʼ��ȫ�ֽ�ɫ�б�(vector<��½��ɫ��Ϣ_>& vsk);

	static void ��½::�������������(CString ����);

	static ��½��ɫ��Ϣ_ ȡδ�������Ľ�ɫ();

	static DWORD getJmpMapList();
	static int getJumpMapCheck(int dIndex);
	static void Fun_UseJumpByIndex(__int64 dCharacterSrvId, int dIndex);

};

