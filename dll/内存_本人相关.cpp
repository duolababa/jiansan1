#include "�ڴ�_�������.h"

INT64 ����::ȡ��ʵ����()
{
	return R_QW(R_QW(��Ϸģ�� + ��ַ_����_����) + 160);
}
INT64 ����::ȡ����()
{
	INT64 ��_������ַ = ��Ϸģ�� + ��ַ_����_����;
	INT64 ��_����жϵ�ַ = ��Ϸģ�� + ��ַ_����_�ж����;
	INT64 ��_rcx = R_QW(R_QW(��_������ַ) + 0xA4) + 0x2F8;
	INT64 ��_����ͷ = R_QW(��_rcx);
	DWORD ��_���� = R_DW(��_rcx + 0x28);
	for (size_t i = 0; i < ��_����; i++)
	{
		INT64 ��_���� = R_QW(��_����ͷ + i * 5 * 4 + 4);
		if (��_���� != 0)
		{
			INT64 ��_��ʱ����ַ = R_QW(R_QW(��_����) + 0x58);
			if (��_��ʱ����ַ == ��_����жϵ�ַ)
			{
				return ��_����;
			}
		}
	}
	return 0;
}
void ����::CALL_��������(DWORD ��������)
{
	INT64 ��_rcx = R_QW(��Ϸģ�� + ��ַ_���_����rcx);
	INT64 ��_call = ��Ϸģ�� + ��ַ_���_����call;
	INT64 ��_�����ͷ = ��Ϸģ�� + ��ַ_����_�����ͷ;
	UCHAR pBuff[0x24] = { 0 };
	W_QW((ULONG64)&pBuff[0x0], ��_�����ͷ);
	W_QW((ULONG64)&pBuff[0x8], 0);
	W_QW((ULONG64)&pBuff[0x10], 0);
	W_Word((ULONG64)&pBuff[0x16], 0x230);
	W_BYTE((ULONG64)&pBuff[0x17], ��������);
	MainUniversalCALL2(��_rcx, (ULONG_PTR)pBuff, ��_call);
	//*(DWORD*)&pBuff[0x0]
}

void ����::���ƶ��ٶ�(bool ����, float �޸�ֵ)
{
	INT64 ��_�ٶ�У���ַ = ��Ϸģ�� + ��ַ_����_�ٶ�У���ַ;
	INT64 ��_�ٶȵ�ַ = R_QW(����::ȡ��ʵ����() + ƫ��_����_����1) + ƫ��_����_����2;
	if (����)
	{
		BYTE �޸�[2] = { 235,33 };
		DWORD old_protect;
		VirtualProtect((LPVOID)��_�ٶ�У���ַ, 2, 64, &old_protect);
		memcpy((LPVOID)��_�ٶ�У���ַ, (void*)&�޸�, 2);
		VirtualProtect((LPVOID)��_�ٶ�У���ַ, 2, old_protect, &old_protect);
		W_Float(��_�ٶȵ�ַ, �޸�ֵ);
	}
	else
	{
		BYTE �޸�[2] = { 117,33 };
		DWORD old_protect;
		VirtualProtect((LPVOID)��_�ٶ�У���ַ, 2, 64, &old_protect);
		memcpy((LPVOID)��_�ٶ�У���ַ, (void*)&�޸�, 2);
		VirtualProtect((LPVOID)��_�ٶ�У���ַ, 2, old_protect, &old_protect);
	}
}
bool ����::���ױ���(vector<������Ϣ_>& vsk)
{
	vsk.clear();
	������Ϣ_ temp;
	INT64 ��_rcx = R_QW(��Ϸģ�� + ��ַ_����_���ױ���rcx);
	if (!��_rcx)
	{
		return false;
	}
	INT64 ��_rdx = R_QW(��Ϸģ�� + ��ַ_����_���ױ���rdx);
	if (!��_rdx)
	{
		return false;
	}
	INT64 ��_CALL = ��Ϸģ�� + ��ַ_����_���ױ���call;
	for (size_t i = 1; i <= 22; i++)
	{
		if (i == 20)
		{
			continue;
		}
		INT64 ret = CALL4(��_rcx, ��_rdx, i, 0, ��_CALL);
		if (ret)
		{
			temp.Obj = R_QW(R_QW(ret) + 12);
			temp.��� = i;
			temp.���� = CString(UnicodeToAnsi(R_CString(R_QW(temp.Obj + 0x20))));
			MyTrace(L"0x%I64X ���:%d ���ƣ�%s", temp.Obj, temp.���, temp.����);
			vsk.push_back(temp);
		}

	}
	return true;
}

DWORD ����::ȡ��ǰ��ֻID()
{
	return R_DW(R_QW(��Ϸģ�� + ��ַ_UI_��������rcx) + 256);
}
DWORD ����::��ȡInteractPropState״̬()
{
	INT64 ��_������ʵ���� = ����::ȡ��ʵ����();
	DWORD InteractPropState = R_DW(��_������ʵ���� + go_GetInteractPropState);
	return InteractPropState;
}
ActorInfo_ ����::ȡ��ɫ��Ϣ()
{
	ActorInfo_ ��ʱ��ɫ��Ϣ;
	INT64 ��_������ʵ���� = ����::ȡ��ʵ����();
	INT64 ��_���˶��� = ����::ȡ����();
	��ʱ��ɫ��Ϣ.���� = R_CString(R_QW(��_������ʵ���� + 0x1C));
	��ʱ��ɫ��Ϣ.�ȼ� = R_W(R_QW(R_QW(��Ϸģ�� + gb_AttrList) + 0xE4) + 30);
	INT64 ���Զ��� = getAttrAddr(R_DW(��_������ʵ���� + 0x14));
	//MyTrace(L"ȡ��ɫ��Ϣ %s %d 0x%I64X",��ʱ��ɫ��Ϣ.����, ��ʱ��ɫ��Ϣ.�ȼ�, ���Զ���);
	��ʱ��ɫ��Ϣ.װ������ = R_Float(���Զ��� + ƫ��_����_װ������);
	/*��ʱ��ɫ��Ϣ.��ǰѪ = getEncryValue(���Զ���, 1);
	��ʱ��ɫ��Ϣ.��ǰ�� = getEncryValue(���Զ���, 2);
	��ʱ��ɫ��Ϣ.���Ѫ = getEncryValue(���Զ���, 0x1B);
	��ʱ��ɫ��Ϣ.����� = getEncryValue(���Զ���, 0x1C);*/
	��ʱ��ɫ��Ϣ.��ǰѪ = R_DW(��_���˶��� + ƫ��_����_���Ѫ + 4);
	��ʱ��ɫ��Ϣ.��ǰ�� = R_DW(��_���˶��� + ƫ��_����_���Ѫ + 12);
	��ʱ��ɫ��Ϣ.���Ѫ = R_DW(��_���˶��� + ƫ��_����_���Ѫ);
	��ʱ��ɫ��Ϣ.����� = R_DW(��_���˶��� + ƫ��_����_���Ѫ + 8);
	��ʱ��ɫ��Ϣ.������ǰ�;� = R_DW(���Զ��� + ƫ��_����_�����;�);
	��ʱ��ɫ��Ϣ.��������;� = R_DW(���Զ��� + ƫ��_����_�����;� + 4);
	INT64 addr2 = R_QW(��_������ʵ���� + ƫ��_����_��ǰŭ��ֵ);
	DWORD ��ǰŭ��ֵ = R_DW(addr2 + 0x14);
	��ʱ��ɫ��Ϣ.ŭ��ֵ = ��ǰŭ��ֵ;
	��ʱ��ɫ��Ϣ.InteractPropState = R_DW(��_������ʵ���� + go_GetInteractPropState);
	INT64 addr3 = R_QW(R_QW(��_������ʵ���� + ƫ��_����_��ǰ���� + 0x30));
	DWORD ��ǰ����ֵ = R_DW(addr3 + 0x30);
	//DWORD ����״̬ = R_DW(��_������ʵ���� + 0x234);
	��ʱ��ɫ��Ϣ.��ǰ���� = ��ǰ����ֵ;
	��ʱ��ɫ��Ϣ.����״̬ = ������״̬();
	//MyTrace(L"ȡ��ɫ��Ϣ2 %d %d/%d  %d %d %d ���� %d", ��ʱ��ɫ��Ϣ.װ������, ��ʱ��ɫ��Ϣ.��ǰѪ, ��ʱ��ɫ��Ϣ.���Ѫ, ��ʱ��ɫ��Ϣ.������ǰ�;�, ��ʱ��ɫ��Ϣ.ŭ��ֵ, ��ʱ��ɫ��Ϣ.InteractPropState, ��ʱ��ɫ��Ϣ.����״̬);
	/// <summary>
	/// /////////////////////
	/// </summary>
	/// <returns></returns>
	INT64 ��_v1 = R_QW(R_QW(R_QW(R_QW(��Ϸģ�� + ��ַ_����_����) + 0x94) + 0x10) + 0x27C);
	//INT64 ��_v1 = R_QW(R_QW(��Ϸģ�� + ��ַ_����_����) + 0x94);
	��ʱ��ɫ��Ϣ.����.x = R_Float(��_v1 + ƫ��_����);
	��ʱ��ɫ��Ϣ.����.y = R_Float(��_v1 + ƫ��_���� + 4);
	��ʱ��ɫ��Ϣ.����.z = R_Float(��_v1 + ƫ��_���� + 8);
	//MyTrace(L"ȡ��ɫ��Ϣ3");
	//MyTrace(L"װ������ %0.3f", R_Float(���Զ��� + ƫ��_����_װ������));
	return ��ʱ��ɫ��Ϣ;
}

bool ����::�Ƿ�������()
{
	INT64 ��_������� = ����::ȡ����();
	bool ��_����״̬ = R_BYTE(��_������� + ƫ��_����_����״̬);
	return ��_����״̬;
}

bool ����::�Ƿ�����·()
{
	INT64 ��_������� = ����::ȡ��ʵ����();
	bool ��_״ֵ̬ = R_BYTE(R_QW(��_������� + ƫ��_����_��·״̬) + 0x2C);
	return ��_״ֵ̬;
}
bool ����::�Ƿ�����·2()
{
	INT64 ��_������ʵ���� = ����::ȡ��ʵ����();
	INT64 addr3 = R_QW(R_QW(��_������ʵ���� + ƫ��_����_��ǰ���� + 0x30));
	DWORD ��ǰ����ֵ = R_DW(addr3 + 0x30);
	if (��ǰ����ֵ == 1)
	{
		return true;
	}
	return false;
}

DWORD ����::������״̬()
{
	INT64 ��_״̬���� = R_QW(��Ϸģ�� + gb_ActorTakeStatus);
	DWORD ��_״ֵ̬ = R_DW(��_״̬���� + 8);
	return ��_״ֵ̬;
}

void ����::CALL_���罻����(DWORD ����ֵ)//62014
{
	INT64 ��_rcx = R_QW(��Ϸģ�� + ��ַ_����_�罻����rcx);
	INT64 dCALL = ��Ϸģ�� + ��ַ_����_�罻����call;
	MainUniversalCALL2(��_rcx, ����ֵ, dCALL);
}

void ����::CALL_ʹ������(DWORD ����ID)//62014
{
	INT64 ��_rcx = R_QW(��Ϸģ�� + ��ַ_����_����);
	INT64 dCALL = ��Ϸģ�� + ��ַ_����_ʹ������call;
	MainUniversalCALL2(��_rcx, ����ID, dCALL);
}

void ����::CALL_����ֻ(DWORD ��ֻID)//62014
{
	INT64 ��_rcx = R_QW(��Ϸģ�� + ��ַ_UI_��������rcx);
	INT64 dCALL = ��Ϸģ�� + ��ַ_����_����ֻcall;
	MainUniversalCALL2(��_rcx, ��ֻID, dCALL);
}
void ����::CALL_��������(DWORD �������)//62014
{


	INT64 ��_rcx = R_QW(��Ϸģ�� + ��ַ_����_��������rcx);
	INT64 dCALL = ��Ϸģ�� + ��ַ_����_��������call;
	MainUniversalCALL4(��_rcx, �������, 0, 0, dCALL);
	/*��ţ�1 ����000001ED650B36C0 ���֣�����֮��
		��ţ�2 ����000001ED650B31C0 ���֣�����֮��
		��ţ�3 ����000001ED650B3080 ���֣�����֮��
		��ţ�4 ����000001ED650B2F40 ���֣�����ϣ��֮��
		��ţ�5 ����000001ED650B2E00 ���֣��ĳ����
		��ţ�6 ����000001ED650B2CC0 ���֣��ջ�֮��
		��ţ�7 ����000001ED650B2B80 ���֣�����֮��
		��ţ�8 ����000001ED650B2A40 ���֣�����Сҹ��
		��ţ�9 ����000001ED650B7900 ���֣�ɭ��С������
		��ţ�10 ����000001ED650B77C0 ���֣�ĺ�ⰲ����
		��ţ�11 ����000001ED650B7680 ���֣�����֮��
		��ţ�12 ����000001ED65074340 ���֣��ǹ�֮��
		��ţ�13 ����000001ED65074480 ���֣�������
		��ţ�14 ����000001ED650740C0 ���֣��ž��İ�����
		��ţ�15 ����000001ED65074200 ���֣����������֮��
		��ţ�16 ����000001EC512A4840 ���֣����֮��
		��ţ�17 ����000001EC512A0D80 ���֣�����֮��
		��ţ�18 ����000001ECE4A18A80 ���֣��ع�֮��
		��ţ�19 ����000001ECE4A18BC0 ���֣���������
		��ţ�21 ����000001ECE4A190C0 ���֣����񰲻���
		��ţ�22 ����000001ECE4A17180 ���֣���г֮��*/
}
void ����::CALL_�򿪷ֽ�()//62014
{
	INT64 ��_rcx = R_QW(��Ϸģ�� + ��ַ_����_�򿪷ֽ�rcx);
	INT64 dCALL = ��Ϸģ�� + ��ַ_����_�򿪷ֽ�call;
	MainUniversalCALL4(��_rcx, 0x25, 0, 0, dCALL);
}

void ����::CALL_ȫ���ֽ�()//62014
{
	INT64 ��_rcx = R_QW(��Ϸģ�� + ��ַ_����_�ֽ�rcx);
	INT64 dCALL = ��Ϸģ�� + ��ַ_����_�ֽ�call;
	MainUniversalCALL4(��_rcx, 0, 0, 0, dCALL);
}

����_ ����::ȡ����()
{
	����_ ��ʱ����;
	INT64 ��_v1 = R_QW(R_QW(R_QW(R_QW(��Ϸģ�� + ��ַ_����_����) + 0x94) + 0x10) + 0x27C);
	//MyTrace(L"0x%I64x", ��_v1);
	//INT64 ��_v1 =R_QW(R_QW(��Ϸģ�� + ��ַ_����_����) + 0x94);
	��ʱ����.x = R_Float(��_v1 + ƫ��_����);
	��ʱ����.y = R_Float(��_v1 + ƫ��_���� + 4);
	��ʱ����.z = R_Float(��_v1 + ƫ��_���� + 8);
	//MyTrace(L"װ������ %0.3f", R_Float(���Զ��� + ƫ��_����_װ������));
	return ��ʱ����;
}
INT64 ����::ȡ�����ַ()
{
	INT64 ��_v1 = R_QW(R_QW(R_QW(R_QW(��Ϸģ�� + ��ַ_����_����) + 0x94) + 0x10) + 0x27C);

	return ��_v1;
}
bool ����::�Ƿ����ٻ�����()
{
	INT64 ��_RCX = R_QW(��Ϸģ�� + ��ַ_����_�ٻ�����rcx);
	if (R_QW(��_RCX + 0xB4))
	{
		return true;
	}
	return false;
}
void ����::��������(vector<INT64>& ����ID)
{
	����ID.clear();
	INT64 ��_RCX = R_QW(��Ϸģ�� + ��ַ_����_�ٻ�����rcx);
	INT64 ������ = R_QW(��_RCX + 0x9C);
	INT64 ����β = R_QW(��_RCX + 0xA4);
	DWORD total = (����β - ������) / 0x10;
	for (size_t i = 0; i < total; i++)
	{
		INT64 addr = R_QW(������ + i * 0x10);
		INT64 ID = R_QW(addr);
		����ID.push_back(ID);
	}
}
bool ����::CALL_�ٻ�����(INT64 ����ID)
{
	INT64 ��_RCX = R_QW(��Ϸģ�� + ��ַ_����_�ٻ�����rcx);
	if (R_QW(��_RCX + 0xB4))
	{
		return false;
	}
	MainUniversalCALL2(��_RCX, ����ID, ��Ϸģ�� + ��ַ_����_�ٻ�����call);
	return true;
}
bool ����::�ٻ�����()
{
	if (!�Ƿ����ٻ�����())
	{
		vector<INT64>����ID��;
		��������(����ID��);
		if (����ID��.size() != 0)
		{
			CALL_�ٻ�����(����ID��[0]);
		}
		else
		{
			if (!UI����::���������Ƿ���ʾ())
			{
				UI����::Fun_UiShowCtrl(0x1A);
			}
			����::ʹ�ñ���ָ����Ʒ_ByResId(0x24A4A);
			Sleep(1000);
			UI����::�ڴ水��(VK_RETURN);
			if (UI����::���������Ƿ���ʾ())
			{
				UI����::Fun_UiShowCtrl(0x1A);
			}
		}
		return false;
	}
	else
	{
		return true;
	}

}
//bool ����::ʹ�ñ���CALL(DWORD ����id)
//{
//	INT64 ʹ�ñ���rcx = R_QW(��Ϸģ�� + ��ַ_����_ʹ�ñ���rcx);
//	INT64 ʹ�ñ���call = ��Ϸģ�� + ��ַ_����_ʹ�ñ���call;
//	if (ʹ�ñ���rcx == 0)
//	{
//		return false;
//	}
//	MainUniversalCALL2(ʹ�ñ���rcx, ����id, ʹ�ñ���call);
//	return true;
//}
bool ����::get_ActionTimingTime()
{
	INT64 addr_1 = R_QW(��Ϸģ�� + gb_ActorList);
	INT64 addr_2 = R_QW(addr_1 + go_hj_myRole);
	INT64 addr_3 = R_QW(addr_2 + 0x18);
	INT64 addr_4 = R_QW(addr_3 + go_hj_VehicleId + 0x10);//��ʵ��ַ
	INT64 addr_Data = R_QW(addr_4 + go_ActionTimingData);
	if (addr_Data)
	{
		for (int i = 0; i < 9; i++)
		{
			int dState = R_DW(addr_4 + go_ActionTimingData + 0x8 + i * 4);
			if (dState != 0)
			{
				float dCurTime = R_Float(addr_Data);
				float dMaxTime = R_Float(addr_Data + go_ActionTimingMaxTime - 8);
				if (dCurTime < dMaxTime)
				{
					MyTrace(L"ʱ�� %0.f / %0.f", dCurTime, dMaxTime);
					return true;
				}

			}
		}
	}
	return false;
}


INT64 ����::�������(DWORD ����)
{
	ActorInfo_ add = ȡ��ɫ��Ϣ();
	objInfo_ temp;
	vector<objInfo_>vsk;
	����::����ȫ����������1(vsk);
	DWORD obj���� = 999999;
	INT64 ����ָ�� = 0;

	for (size_t i = 0; i < vsk.size(); i++)
	{
		if (vsk[i].dType == 2)
		{
			if (vsk[i].dCurHp >= 1 && vsk[i].wName != L"")
			{
				if (vsk[i].���� < ����)
				{
					if (vsk[i].���� < obj����)
					{
						obj���� = vsk[i].����;
						����ָ�� = vsk[i].dObjId;

					}
				}
			}

		}
	}
	return ����ָ��;


}




INT64 ����::�������1(DWORD ����)
{

	objInfo_ temp;
	vector<objInfo_>vsk;
	����::����ȫ����������1(vsk);
	DWORD obj���� = 999999;
	INT64 ����ָ�� = 0;

	for (size_t i = 0; i < vsk.size(); i++)
	{
		if (vsk[i].dType == 2)
		{
			if (vsk[i].dCurHp >= 1 && vsk[i].wName != L"" && vsk[i].IsHide == 0)
			{
				if (vsk[i].���� < ����)
				{


					����ָ�� = vsk[i].objBase;
					break;

				}
			}

		}
	}
	return ����ָ��;


}




INT64 ����::�������2(DWORD ����, CString ID�ı�)
{
	CArray<CString, CString>�����ı���;
	ActorInfo_ add = ȡ��ɫ��Ϣ();
	objInfo_ temp;
	vector<objInfo_>vsk;
	����::����ȫ����������1(vsk);
	DWORD obj���� = 999999;
	INT64 ����ָ�� = 0;

	for (size_t i = 0; i < vsk.size(); i++)
	{
		if (vsk[i].dType == 2)
		{
			if (vsk[i].dCurHp >= 1 && vsk[i].wName != L"" && vsk[i].IsHide == 0 && vsk[i].�Ƿ���Թ��� == 0)
			{
				if (vsk[i].���� < ����)
				{
					if (ID�ı� == L"")
					{
						����ָ�� = vsk[i].objBase;
						break;
					}
					else
					{
						if (ID�ı�.Find(L"|") == -1)
						{
							DWORD ��ʱid = ���ù���::ʮ������תʮ����(CStringA(ID�ı�));
							if (��ʱid == vsk[i].dResId)
							{
								����ָ�� = vsk[i].objBase;
								break;
							}
						}
						else
						{
							�ı��ָ�(ID�ı�, '|', &�����ı���);
							if (�����ı���.GetCount() == 0)
							{
								����ָ�� = 0;
								break;
							}
							else
							{
								for (size_t i = 0; i < �����ı���.GetCount(); i++)
								{
									DWORD ��ʱid = 0;

									��ʱid = ���ù���::ʮ������תʮ����(CStringA(ID�ı�));
									if (��ʱid == vsk[i].dResId)
									{
										����ָ�� = vsk[i].objBase;
										return ����ָ��;

									}


								}


							}


						}
					}
				}
			}

		}
	}
	return ����ָ��;


}