#pragma once
#include "pch.h"
#include <vector>
using namespace std;

struct 坐标_
{
	float x=0;
	float y=0;
	float z=0;
	int 大陆ID=0;
	int 地图ID=0;
	int 是否可达 = 0;
	int 数组位置 = 0;
	float fDis = 0;
};
struct ActorInfo_
{
	INT64 真实对象指针;
	INT64 对象指针;
	DWORD 当前血;
	DWORD 最大血;
	DWORD 当前蓝;
	DWORD 最大蓝;
	坐标_ 坐标;
	DWORD 当前地图ID;
	DWORD 装备评分;
	CString 名称;
	DWORD 等级;
	DWORD 航海当前耐久;
	DWORD 航海最大耐久;
	DWORD 怒气值;
	DWORD 当前动作;
	DWORD InteractPropState=0;
	DWORD 举起状态 = 0; //==4已举起 ==1 未举起

	DWORD 骑行状态;
	DWORD G按标识 = 0;
	DWORD 行走状态;
	DWORD 职业;
	DWORD ID1=0;
	//int 课题状态;
};
struct UIinfo_
{
	DWORD dIndex;
	DWORD dId;
	INT64 UIObj;
	bool bShow;
	CString CName;
	//int 课题状态;
};
struct 耐久度_
{
	DWORD 当前耐久度=0;
	DWORD 最大耐久度=0;
	//int 课题状态;
};
struct Inventoryinfo_
{
	INT64 ItemObj;
	INT64 ItemId;
	CString ItemName;
	DWORD dNum;
	DWORD dindex = -1;
	DWORD WearId;
	DWORD BoxType;
	INT64 dItemResAddr;
	DWORD ItemResId = 0;
	耐久度_ 耐久度;
	DWORD 颜色;
	DWORD dPriceType = 0;
	DWORD dPrice = 0;
	DWORD dSlotIndex = 0;
	DWORD dLev = 0;
	DWORD dUpgradeLev = 0;
	//int 课题状态;
};

struct Equipinfo_
{
	INT64 ItemObj;
	INT64 ItemId=0;
	CString ItemName;
	DWORD Type;
	INT64 dItemResAddr;
	耐久度_ 耐久度;
	DWORD 物品等级=0;
	DWORD WearId = 0;
	DWORD 颜色=0;
	DWORD dLev=0;
	DWORD dUpgradeLev = 0;
	//int 课题状态;
};
struct 乐谱信息_
{
	INT64 Obj;
	DWORD 序号;
	CString 名称;
	//int 课题状态;
};
struct 传送点信息_
{
	DWORD dTeleportId;
	CString cTeleportName;
	DWORD Mapid =0;
	//int 课题状态;
};
struct 登陆角色信息_
{
	INT64 对象指针 = 0;
	CString 名称 = L"";
	DWORD 等级 = 0;
	int dIndex = -1;
	DWORD dJob = 0;
	INT64 SrvId = 0;
	DWORD 直升状态 = 0;
	bool 任务是否完成 = false;
	//int 课题状态;
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

struct objInfo_
{
	INT64 objBase = 0;//对象地址+ 8为X + 18为Y
	INT64 dResAddr = 0;
	DWORD dObjId = 0;
	DWORD dResId = 0;
	DWORD ModId = 0; //电梯寻路用
	CString wName = L"";
	CString wTips = L"";
	float fDis = 0;
	坐标_ 坐标;
	DWORD dType = 0;
	BYTE dResType = 0;
	BYTE dResShow = 0;
	BYTE dResOpen = 0;
	BYTE dPortalOpen = 0;
	BOOL IsHide = false;
	BOOL IsEnemy = false;
	DWORD dCurHp = 0;
	DWORD dMaxHp = 0;
	BYTE dCanAttack = 0;
	int dIsDead = 0;
	int dMonsterSkillNum = 0;
	float 距离;
	BYTE 是否可以攻击;
	DWORD ID1 = 0;
};

struct SubQuestNeed_
{
	CString 任务描述;
	DWORD TargetID;
	DWORD dCur;
	DWORD dNeed;
};
struct QuestInfo_
{
	INT64 objBase=0;
	INT64 dResAddr=0;
	DWORD dQuestId = 0;
	DWORD dStep=0;
	DWORD dState=0;
	CString QuestName;
	CString DescribeName;
	CString QuestOption;
	DWORD dType=0;
	DWORD IsFinish = 0;
	DWORD TargetId=0;
	DWORD NeedNum=0;
	DWORD CurNum=0;
	DWORD TargetNum=0;
	std::vector<SubQuestNeed_>子任务进度;
};

struct SkillInfo_
{
	INT64 objBase=0;
	INT64 InfoObj=0;
	DWORD dSkillId=0;
	DWORD dSkillLev=0;
	DWORD dSkillType;
	DWORD dRange;
	DWORD dUpGradeNeedPoint;
	bool dCanUpGrade;
	CString 名称;
	DWORD 键位=0;
	DWORD 天赋1=0;
	DWORD 天赋2=0;
	DWORD 天赋3=0;
	bool 是否冷却 = 0;
	DWORD 技能状态 = 0;
};

struct ShortCutInfo_
{
	DWORD dPage;
	INT64 objBase;
	DWORD dId;
	CString 名称;
	DWORD type; //左侧=1 右上=2 右下=3;
	DWORD 键位;
	DWORD 是否冷却 = false;
	DWORD 技能状态 = 0;
};

struct 分段处理信息_
{
	坐标_ 坐标;
	DWORD 处理方式;//1=过传送门 2=G 3=电梯;
	DWORD 属于分段=0;
};
struct 小地图信息_
{
	DWORD 标记;
	坐标_ 进入坐标;
	DWORD 属于分段;
	坐标_ 返回坐标;
};
struct 记录传送点信息_
{
	DWORD ResId;
	坐标_ 坐标;
	DWORD 属于分段;
	CString 名称;
};
typedef struct 节点处理_
{
	DWORD 地图ID;
	分段处理信息_ 前往上一张地图传送门;
	分段处理信息_ 前往下一张地图传送门;
	CArray<分段处理信息_, 分段处理信息_>前往下一个分段组;
	CArray<分段处理信息_, 分段处理信息_>返回上一个分段组;
	CArray<小地图信息_, 小地图信息_>小地图组;
	CArray<记录传送点信息_, 记录传送点信息_>传送点组;
	节点处理_()
	{

	}
	节点处理_(const 节点处理_& ca)
	{
		地图ID = ca.地图ID;
		前往上一张地图传送门 = ca.前往上一张地图传送门;
		前往下一张地图传送门 = ca.前往下一张地图传送门;
		for (int i = 0; i < ca.前往下一个分段组.GetCount(); ++i)
		{
			前往下一个分段组.Add(ca.前往下一个分段组[i]);
		}
		for (int i = 0; i < ca.返回上一个分段组.GetCount(); ++i)
		{
			返回上一个分段组.Add(ca.返回上一个分段组[i]);
		}
		for (int i = 0; i < ca.小地图组.GetCount(); ++i)
		{
			小地图组.Add(ca.小地图组[i]);
		}
		for (int i = 0; i < ca.传送点组.GetCount(); ++i)
		{
			传送点组.Add(ca.传送点组[i]);
		}

	}
	节点处理_& operator=(const 节点处理_& ca)
	{
		if (&ca == this)
		{
			return *this;
		}
		地图ID = ca.地图ID;
		前往上一张地图传送门 = ca.前往上一张地图传送门;
		前往下一张地图传送门 = ca.前往下一张地图传送门;
		前往下一个分段组.RemoveAll();
		返回上一个分段组.RemoveAll();
		小地图组.RemoveAll();
		传送点组.RemoveAll();
		for (int i = 0; i < ca.前往下一个分段组.GetCount(); ++i)
		{
			前往下一个分段组.Add(ca.前往下一个分段组[i]);
		}
		for (int i = 0; i < ca.返回上一个分段组.GetCount(); ++i)
		{
			返回上一个分段组.Add(ca.返回上一个分段组[i]);
		}
		for (int i = 0; i < ca.小地图组.GetCount(); ++i)
		{
			小地图组.Add(ca.小地图组[i]);
		}
		for (int i = 0; i < ca.传送点组.GetCount(); ++i)
		{
			传送点组.Add(ca.传送点组[i]);
		}
		return *this;
	}
};

struct 录制坐标_
{
	float x1=0;
	float y1=0;
	float z1=0;
	float x2=0;
	float y2=0;
	float z2=0;
	int 操作=-1;
	DWORD 线路;
	DWORD 线路分段;
	DWORD 未知1;
	DWORD 未知2;
	DWORD 地图ID;
	DWORD dis;
	bool 已分配=false;
};

struct _QuestTalkInfo
{
	INT64 dResAddr;
	int dTalkId;
	int dParentId;
	wchar_t wName[MAX_PATH];
};

struct MailInfo_
{
	DWORD dIndex;
	INT64 dObjAddr;
	INT64 dMailId;
	DWORD dType;
	DWORD dState;
	DWORD dNeedOpen;
	INT64 dMoneyNum;
	CString 发件人;
	CString Ctitle;
};
struct CrewInfo_
{
	DWORD dShipId = 0;
	DWORD dIndex = -1;
	DWORD dResId = 0;
	INT64 dResAddr = 0;
	CString wName = L"";
};
struct ShipInfo_
{
	INT64 dObj = 0;
	WORD dLev = 0;
	DWORD dIndex = -1;
	DWORD dResId = 0;
	INT64 dResAddr = 0;
	CString wName = L"";
};

struct 诞生石能力强化信息_
{
	INT64 dObj = 0;
	DWORD dAbilityId = 0;
	DWORD dAbilityName = 0;
	DWORD dState = 0;
};

struct 诞生石信息_
{
	INT64 dObj = 0;
	DWORD type = 0;
	DWORD 总强化成功次数 = 0;
	vector<诞生石能力强化信息_>能力1数组;
	vector<诞生石能力强化信息_>能力2数组;
	vector<诞生石能力强化信息_>能力3数组;
};

struct 副本信息_
{
	DWORD ID;
	CString csName = L"空";

};


struct 周长日常_
{
	DWORD ID;
	CString csName = L"空";
	DWORD 状态 = 0;

};

