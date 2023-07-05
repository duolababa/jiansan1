#pragma once
#include "pch.h"
class 技能
{
public:
    static DWORD getRoleCurSkillPoints();
    static void get_SkillList(vector<SkillInfo_>& vsk);
    static void get_SkillShortList(vector<ShortCutInfo_>& vsk);
    static void get_RightShortList(vector<ShortCutInfo_>& vsk);

    static bool 冷却判断(INT64 技能对象指针);

    static bool 写怪物坐标到鼠标(坐标_ 怪物坐标);

    static bool 写怪物坐标到鼠标2(float fx, float fy, float fz);


    static DWORD 技能键码转换(int 键位);

    static DWORD 右侧快捷键键码转换(int type, int 键位);

    static void 技能释放(坐标_ 怪物坐标);

    static void 屏蔽鼠标();

    static void 解除屏蔽鼠标();

    static void 技能释放2(坐标_ 怪物坐标);

    static SkillInfo_ 技能::取出指定技能信息(DWORD SkillID, vector<SkillInfo_>&vsk);

    static bool CALL_升级技能天赋(DWORD 技能ID, DWORD 等级, DWORD 特性1, DWORD 特性2, DWORD 特性3);

    static bool 自动升级技能(DWORD 技能ID, DWORD 等级, DWORD 特性1, DWORD 特性2, DWORD 特性3,DWORD 优先等级=4);

    static void 自动升级女巫技能();

    static void CALL_快捷键技能摆放(DWORD 技能ID, DWORD 位置);
    static DWORD 判断技能等级(DWORD 技能ID);
    static void 摆放与学习技能();
    static DWORD get_SkillShortCurPage();
    //static void 自动升级技能();

};

DWORD 通过技能ID获取键码(DWORD SKILLID);
void 测试打怪(INT64 怪物obj);