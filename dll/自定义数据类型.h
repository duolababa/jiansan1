#pragma once
#include "pch.h"
#include <vector>
using namespace std;

struct ����_
{
	float x=0;
	float y=0;
	float z=0;
	int ��½ID=0;
	int ��ͼID=0;
	int �Ƿ�ɴ� = 0;
	int ����λ�� = 0;
	float fDis = 0;
};
struct ActorInfo_
{
	INT64 ��ʵ����ָ��;
	INT64 ����ָ��;
	DWORD ��ǰѪ;
	DWORD ���Ѫ;
	DWORD ��ǰ��;
	DWORD �����;
	����_ ����;
	DWORD ��ǰ��ͼID;
	DWORD װ������;
	CString ����;
	DWORD �ȼ�;
	DWORD ������ǰ�;�;
	DWORD ��������;�;
	DWORD ŭ��ֵ;
	DWORD ��ǰ����;
	DWORD InteractPropState=0;
	DWORD ����״̬ = 0; //==4�Ѿ��� ==1 δ����

	DWORD ����״̬;
	DWORD G����ʶ = 0;
	DWORD ����״̬;
	DWORD ְҵ;
	DWORD ID1=0;
	//int ����״̬;
};
struct UIinfo_
{
	DWORD dIndex;
	DWORD dId;
	INT64 UIObj;
	bool bShow;
	CString CName;
	//int ����״̬;
};
struct �;ö�_
{
	DWORD ��ǰ�;ö�=0;
	DWORD ����;ö�=0;
	//int ����״̬;
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
	�;ö�_ �;ö�;
	DWORD ��ɫ;
	DWORD dPriceType = 0;
	DWORD dPrice = 0;
	DWORD dSlotIndex = 0;
	DWORD dLev = 0;
	DWORD dUpgradeLev = 0;
	//int ����״̬;
};

struct Equipinfo_
{
	INT64 ItemObj;
	INT64 ItemId=0;
	CString ItemName;
	DWORD Type;
	INT64 dItemResAddr;
	�;ö�_ �;ö�;
	DWORD ��Ʒ�ȼ�=0;
	DWORD WearId = 0;
	DWORD ��ɫ=0;
	DWORD dLev=0;
	DWORD dUpgradeLev = 0;
	//int ����״̬;
};
struct ������Ϣ_
{
	INT64 Obj;
	DWORD ���;
	CString ����;
	//int ����״̬;
};
struct ���͵���Ϣ_
{
	DWORD dTeleportId;
	CString cTeleportName;
	DWORD Mapid =0;
	//int ����״̬;
};
struct ��½��ɫ��Ϣ_
{
	INT64 ����ָ�� = 0;
	CString ���� = L"";
	DWORD �ȼ� = 0;
	int dIndex = -1;
	DWORD dJob = 0;
	INT64 SrvId = 0;
	DWORD ֱ��״̬ = 0;
	bool �����Ƿ���� = false;
	//int ����״̬;
};
struct temp����ָ��
{
	INT64 ����obj;
	INT64 ����;;
	//int ����״̬;
};

class MyPlayerclass  //�Լ��ĺŽṹ
{
public:
	DWORD Mapid;
	int zy;
	int Lev;
	int AtQF;
	int type;//����,0���ڿ�,1��ɱ��
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
	INT64 objBase = 0;//�����ַ+ 8ΪX + 18ΪY
	INT64 dResAddr = 0;
	DWORD dObjId = 0;
	DWORD dResId = 0;
	DWORD ModId = 0; //����Ѱ·��
	CString wName = L"";
	CString wTips = L"";
	float fDis = 0;
	����_ ����;
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
	float ����;
	BYTE �Ƿ���Թ���;
	DWORD ID1 = 0;
};

struct SubQuestNeed_
{
	CString ��������;
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
	std::vector<SubQuestNeed_>���������;
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
	CString ����;
	DWORD ��λ=0;
	DWORD �츳1=0;
	DWORD �츳2=0;
	DWORD �츳3=0;
	bool �Ƿ���ȴ = 0;
	DWORD ����״̬ = 0;
};

struct ShortCutInfo_
{
	DWORD dPage;
	INT64 objBase;
	DWORD dId;
	CString ����;
	DWORD type; //���=1 ����=2 ����=3;
	DWORD ��λ;
	DWORD �Ƿ���ȴ = false;
	DWORD ����״̬ = 0;
};

struct �ֶδ�����Ϣ_
{
	����_ ����;
	DWORD ����ʽ;//1=�������� 2=G 3=����;
	DWORD ���ڷֶ�=0;
};
struct С��ͼ��Ϣ_
{
	DWORD ���;
	����_ ��������;
	DWORD ���ڷֶ�;
	����_ ��������;
};
struct ��¼���͵���Ϣ_
{
	DWORD ResId;
	����_ ����;
	DWORD ���ڷֶ�;
	CString ����;
};
typedef struct �ڵ㴦��_
{
	DWORD ��ͼID;
	�ֶδ�����Ϣ_ ǰ����һ�ŵ�ͼ������;
	�ֶδ�����Ϣ_ ǰ����һ�ŵ�ͼ������;
	CArray<�ֶδ�����Ϣ_, �ֶδ�����Ϣ_>ǰ����һ���ֶ���;
	CArray<�ֶδ�����Ϣ_, �ֶδ�����Ϣ_>������һ���ֶ���;
	CArray<С��ͼ��Ϣ_, С��ͼ��Ϣ_>С��ͼ��;
	CArray<��¼���͵���Ϣ_, ��¼���͵���Ϣ_>���͵���;
	�ڵ㴦��_()
	{

	}
	�ڵ㴦��_(const �ڵ㴦��_& ca)
	{
		��ͼID = ca.��ͼID;
		ǰ����һ�ŵ�ͼ������ = ca.ǰ����һ�ŵ�ͼ������;
		ǰ����һ�ŵ�ͼ������ = ca.ǰ����һ�ŵ�ͼ������;
		for (int i = 0; i < ca.ǰ����һ���ֶ���.GetCount(); ++i)
		{
			ǰ����һ���ֶ���.Add(ca.ǰ����һ���ֶ���[i]);
		}
		for (int i = 0; i < ca.������һ���ֶ���.GetCount(); ++i)
		{
			������һ���ֶ���.Add(ca.������һ���ֶ���[i]);
		}
		for (int i = 0; i < ca.С��ͼ��.GetCount(); ++i)
		{
			С��ͼ��.Add(ca.С��ͼ��[i]);
		}
		for (int i = 0; i < ca.���͵���.GetCount(); ++i)
		{
			���͵���.Add(ca.���͵���[i]);
		}

	}
	�ڵ㴦��_& operator=(const �ڵ㴦��_& ca)
	{
		if (&ca == this)
		{
			return *this;
		}
		��ͼID = ca.��ͼID;
		ǰ����һ�ŵ�ͼ������ = ca.ǰ����һ�ŵ�ͼ������;
		ǰ����һ�ŵ�ͼ������ = ca.ǰ����һ�ŵ�ͼ������;
		ǰ����һ���ֶ���.RemoveAll();
		������һ���ֶ���.RemoveAll();
		С��ͼ��.RemoveAll();
		���͵���.RemoveAll();
		for (int i = 0; i < ca.ǰ����һ���ֶ���.GetCount(); ++i)
		{
			ǰ����һ���ֶ���.Add(ca.ǰ����һ���ֶ���[i]);
		}
		for (int i = 0; i < ca.������һ���ֶ���.GetCount(); ++i)
		{
			������һ���ֶ���.Add(ca.������һ���ֶ���[i]);
		}
		for (int i = 0; i < ca.С��ͼ��.GetCount(); ++i)
		{
			С��ͼ��.Add(ca.С��ͼ��[i]);
		}
		for (int i = 0; i < ca.���͵���.GetCount(); ++i)
		{
			���͵���.Add(ca.���͵���[i]);
		}
		return *this;
	}
};

struct ¼������_
{
	float x1=0;
	float y1=0;
	float z1=0;
	float x2=0;
	float y2=0;
	float z2=0;
	int ����=-1;
	DWORD ��·;
	DWORD ��·�ֶ�;
	DWORD δ֪1;
	DWORD δ֪2;
	DWORD ��ͼID;
	DWORD dis;
	bool �ѷ���=false;
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
	CString ������;
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

struct ����ʯ����ǿ����Ϣ_
{
	INT64 dObj = 0;
	DWORD dAbilityId = 0;
	DWORD dAbilityName = 0;
	DWORD dState = 0;
};

struct ����ʯ��Ϣ_
{
	INT64 dObj = 0;
	DWORD type = 0;
	DWORD ��ǿ���ɹ����� = 0;
	vector<����ʯ����ǿ����Ϣ_>����1����;
	vector<����ʯ����ǿ����Ϣ_>����2����;
	vector<����ʯ����ǿ����Ϣ_>����3����;
};

struct ������Ϣ_
{
	DWORD ID;
	CString csName = L"��";

};


struct �ܳ��ճ�_
{
	DWORD ID;
	CString csName = L"��";
	DWORD ״̬ = 0;

};

