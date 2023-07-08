#pragma once
#include "pch.h"
class 本人
{
public:
	static INT64 取真实对象();
	static INT64 取对象();
	static void CALL_发包复活(DWORD 复活类型);
	static void 改移动速度(bool 开关, float 修改值);
	static bool 乐谱遍历(vector<乐谱信息_>& vsk);
	static DWORD 取当前船只ID();
	static DWORD 获取InteractPropState状态();
	static ActorInfo_ 取角色信息();
	static bool 是否在骑马();
	static bool 是否在走路();
	static bool 是否在走路2();
	static DWORD 举起东西状态();
	static void CALL_做社交动作(DWORD 动作值);
	static void CALL_使用坐骑(DWORD 坐骑ID);
	static void CALL_修理船只(DWORD 船只ID);
	static void CALL_演奏乐谱(DWORD 乐谱序号);
	static void CALL_打开分解();
	static void CALL_全部分解();
	static 坐标_ 取坐标();
	static INT64 取坐标基址();
	static bool 是否已召唤宠物();
	static void 遍历宠物(vector<INT64>& 宠物ID);
	static bool CALL_召唤宠物(INT64 宠物ID);
	static bool 召唤宠物();
	static bool get_ActionTimingTime();
	//static bool 使用表情CALL(DWORD 表情id);
	static INT64 最近怪物(DWORD 距离);
	static INT64 最近怪物1(DWORD 距离);
	static INT64 最近怪物2(DWORD 距离, CString id);
	static bool 是否战斗中();
	static void 设置宝石自动合成();

};

