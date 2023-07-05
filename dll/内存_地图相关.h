#pragma once
#include "pch.h"
class 地图
{
public:
	static int 取地图ID();
	static int 取当前大陆ID();
	static void 传送(DWORD 传送ID);
	static void 遍历已激活传送点(vector<传送点信息_>& vsk);
	static bool 传送点是否激活(DWORD 传送点ID);
	static void 取目标地图传送点(DWORD 地图ID, vector<传送点信息_>& vsk);
	static DWORD 获取港口传送点ID();
	static INT64 取场景对象();
	static CString 取大地图名();
	static CString 取指定地图名(DWORD 局_地图ID);
	static CString 取小地图名();
	static void 寻路(float x, float y, float z, DWORD modid);
	static bool 本地图寻路(float x, float y, float z, DWORD modid);
	static bool 指定地点是否可到达(float x, float y, float z);
	static bool 指定地点是否可到达_M(float x, float y, float z);
};

