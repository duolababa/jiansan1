#pragma once
#include "pch.h"
#include <vector>
using namespace std;

struct ����_
{
	float x = 0;
	float y = 0;
	float z = 0;
	int ��½ID = 0;
	int ��ͼID = 0;
	int �Ƿ�ɴ� = 0;
	int ����λ�� = 0;
	float fDis = 0;
};

struct ����_1
{
	DWORD x = 0;
	DWORD y = 0;
	DWORD z = 0;
	float fDis = 0;
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


struct _stu��ֵ
{
	_stu��ֵ()
	{
		m_Min = -1;
		m_Max = -1;

	}
	int m_Min;
	int m_Max;
public:
	int _ȡѪ���ٷֱ�()
	{
		if (m_Max == 0 || m_Max== -1)return 0;
		return m_Min * 100 / m_Max;
		
	}

	void _����(int Min, int Max)
	{
		m_Min = Min;
		m_Max = Max;

	}



};

struct _stu��Ʒ
{
	INT64 m_��Ʒ�ṹ��ַ = 0;
	INT64 m_ID = 0;
	CString name;
	_stu��ֵ m����;
	DWORD ��Ʒ����;

};

struct _stu����
{
	vector<_stu��Ʒ> m_����;
	int m_λ��;
	int m_���������;

};


struct _stu����
{
	vector<_stu����> m_����;
	int m_��������;
	DWORD ��������;
};


struct _stu����
{
	INT64 m_�ṹ��ַ = 0;
	INT64 ID = 0;
	����_1 ��Ϸ����;
	DWORD Ѫ�� = 0;
	DWORD ���Ѫ = 0;
	DWORD �ȼ� = 0;
	_stu��ֵ m_Ѫ��;
	_stu��ֵ m_����;
	_stu��ֵ m_����;
	DWORD ����״̬;
	DWORD ����״̬; 
	CString name;
	DWORD ���;
	CString ��ͼ;
	DWORD ͨ��;
	DWORD ������=0;
	DWORD ��ȴ = 0;
	DWORD ս�� = 0;
	DWORD ��ͼ = 0;
	DWORD64 ���� = 0;

};


struct _stu�����б�
{
	vector<_stu����> m_����;

};


struct mypid
{
	int ��� = 0;
	int mapid = 0;
	int Lev = 0;
	int �ӳ�;
	char �˻�[100];
	char ����[100];
	char ��[100];
	char ��[100];
	char ��ɫ[100];
	char �ֿ�����[100];
	char ����[100];
	char ִ��[100];
	char ��ע[100];
	char ����Ŀ¼[500];
	char �����п�[1024];
};


