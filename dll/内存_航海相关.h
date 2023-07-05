#pragma once
#include "pch.h"
class 航海
{
public:
	static DWORD getRoleCrewList(vector<CrewInfo_>& vsk);
	static void VoyageShipAddCrew(int dResId);
	static void VoyageShipDelCrew(int dIndex);
	static DWORD getCurVoyageShipResId();
	static bool 指定船员是否上船(DWORD dResId);
	static bool 指定船员是否上了已装备的船(DWORD dResId);
	static void 删除所有船员();
	static void 设置所有船员();
	static bool 自动选择最优战船();
};

