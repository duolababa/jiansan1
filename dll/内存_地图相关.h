#pragma once
#include "pch.h"
class ��ͼ
{
public:
	static int ȡ��ͼID();
	static int ȡ��ǰ��½ID();
	static void ����(DWORD ����ID);
	static void �����Ѽ���͵�(vector<���͵���Ϣ_>& vsk);
	static bool ���͵��Ƿ񼤻�(DWORD ���͵�ID);
	static void ȡĿ���ͼ���͵�(DWORD ��ͼID, vector<���͵���Ϣ_>& vsk);
	static DWORD ��ȡ�ۿڴ��͵�ID();
	static INT64 ȡ��������();
	static CString ȡ���ͼ��();
	static CString ȡָ����ͼ��(DWORD ��_��ͼID);
	static CString ȡС��ͼ��();
	static void Ѱ·(float x, float y, float z, DWORD modid);
	static bool ����ͼѰ·(float x, float y, float z, DWORD modid);
	static bool ָ���ص��Ƿ�ɵ���(float x, float y, float z);
	static bool ָ���ص��Ƿ�ɵ���_M(float x, float y, float z);
};

