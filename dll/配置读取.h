#pragma once
#include "pch.h"
class 配置
{
public:
	static void 取录制坐标(int 地图标识, vector<录制坐标_>& 录制坐标组);
	static void 获取辅助位置();
	static CString 获取指定设置文本(CString 配置文件名称, CString 配置节点, CString 配置项名称);
	static void 读取脚本配置();
};

void 文本分割(CString strSource, char ch, CArray<CString, CString>* 返回文本组);
//void 获取辅助位置();