#pragma once
#include "pch.h"
class ����
{
public:
    static DWORD getRoleCurSkillPoints();
    static void get_SkillList(vector<SkillInfo_>& vsk);
    static void get_SkillShortList(vector<ShortCutInfo_>& vsk);
    static void get_RightShortList(vector<ShortCutInfo_>& vsk);

    static bool ��ȴ�ж�(INT64 ���ܶ���ָ��);

    static bool д�������굽���(����_ ��������);

    static bool д�������굽���2(float fx, float fy, float fz);


    static DWORD ���ܼ���ת��(int ��λ);

    static DWORD �Ҳ��ݼ�����ת��(int type, int ��λ);

    static void �����ͷ�(����_ ��������);

    static void �������();

    static void ����������();

    static void �����ͷ�2(����_ ��������);

    static SkillInfo_ ����::ȡ��ָ��������Ϣ(DWORD SkillID, vector<SkillInfo_>&vsk);

    static bool CALL_���������츳(DWORD ����ID, DWORD �ȼ�, DWORD ����1, DWORD ����2, DWORD ����3);

    static bool �Զ���������(DWORD ����ID, DWORD �ȼ�, DWORD ����1, DWORD ����2, DWORD ����3,DWORD ���ȵȼ�=4);

    static void �Զ�����Ů�׼���();

    static void CALL_��ݼ����ܰڷ�(DWORD ����ID, DWORD λ��);
    static DWORD �жϼ��ܵȼ�(DWORD ����ID);
    static void �ڷ���ѧϰ����();
    static DWORD get_SkillShortCurPage();
    //static void �Զ���������();

};

DWORD ͨ������ID��ȡ����(DWORD SKILLID);
void ���Դ��(INT64 ����obj);