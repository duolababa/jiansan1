#pragma once
#include "pch.h"
#include <vector>
using namespace std;

struct 坐标_
{
	float x = 0;
	float y = 0;
	float z = 0;
	int 大陆ID = 0;
	int 地图ID = 0;
	int 是否可达 = 0;
	int 数组位置 = 0;
	float fDis = 0;
};

struct 坐标_1
{
	DWORD x = 0;
	DWORD y = 0;
	DWORD z = 0;
	float fDis = 0;
};

struct temp名称指针
{
	INT64 名称obj;
	INT64 长度;;
	//int 课题状态;
};

class MyPlayerclass  //自己的号结构
{
public:
	DWORD Mapid;
	int zy;
	int Lev;
	int AtQF;
	int type;//类型,0是挖矿,1是杀手
	char Name[100];
	DWORD64 PleryID;
	MyPlayerclass()
	{
		Lev = 0;
		type = 0;
		zy = -1;
		Mapid = 0;
		memset(Name, 0, 100);
		PleryID = 0;
		AtQF = -1;
	};
	void copy(MyPlayerclass b)
	{
		Lev = b.Lev;
		zy = b.zy;
		type = b.type;
		Mapid = b.Mapid;
		strcpy(Name, b.Name);
		PleryID = b.PleryID;
		AtQF = b.AtQF;
	};
};


struct _stu数值
{
	_stu数值()
	{
		m_Min = -1;
		m_Max = -1;

	}
	int m_Min;
	int m_Max;
public:
	int _取血量百分比()
	{
		if (m_Max == 0 || m_Max== -1)return 0;
		return m_Min * 100 / m_Max;
		
	}

	void _设置(int Min, int Max)
	{
		m_Min = Min;
		m_Max = Max;

	}



};

struct _stu物品
{
	INT64 m_物品结构地址 = 0;
	INT64 m_ID = 0;
	CString name;
	_stu数值 m数量;
	DWORD 物品类型;

};

struct _stu行囊
{
	vector<_stu物品> m_数据;
	int m_位置;
	int m_最大存放数量;

};


struct _stu背包
{
	vector<_stu行囊> m_数据;
	int m_行囊数量;
	DWORD 背包总数;
};


struct _stu对象
{
	INT64 m_结构地址 = 0;
	INT64 ID = 0;
	坐标_1 游戏坐标;
	DWORD 血量 = 0;
	DWORD 最大血 = 0;
	DWORD 等级 = 0;
	_stu数值 m_血量;
	_stu数值 m_蓝量;
	_stu数值 m_力气;
	DWORD 行走状态;
	DWORD 骑行状态; 
	CString name;
	DWORD 金币;
	CString 地图;
	DWORD 通宝;
	DWORD 玲珑锁=0;
	DWORD 冷却 = 0;
	DWORD 战斗 = 0;
	DWORD 过图 = 0;
	DWORD64 距离 = 0;

};


struct _stu对象列表
{
	vector<_stu对象> m_数据;

};


struct mypid
{
	int 序号 = 0;
	int mapid = 0;
	int Lev = 0;
	int 延迟;
	char 账户[100];
	char 密码[100];
	char 区[100];
	char 服[100];
	char 角色[100];
	char 仓库密码[100];
	char 流程[100];
	char 执行[100];
	char 备注[100];
	char 运行目录[500];
	char 反馈中控[1024];
};


