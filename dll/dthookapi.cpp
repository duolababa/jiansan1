#include"pch.h"
#include"detours.h"

BOOL hookapi(PVOID *oldApi/*ҪHOOK�ĵ�ַ ����*/, PVOID newApi/*�µĺ�����ַ*/)
{
	BOOL br = FALSE;
	DetourRestoreAfterWith();//�ָ�ԭ��״̬
	DetourTransactionBegin();//���ؿ�ʼ
	DetourUpdateThread(GetCurrentThread());//ˢ�µ�ǰ�߳�

	//�������������ε���DetourAttach������HOOK�������
	//DetourAttach(&(PVOID&)OldCreateMutexA,NewCreateMutexA);
	DetourAttach(oldApi, newApi);
	//br����NO_ERROR��ʾ�ɹ�
	br = DetourTransactionCommit();//��������Ч
	if (br == NO_ERROR)
	{
		br = TRUE;
	}
	else
	{
		br = FALSE;
	}
	return br;
}

BOOL unhookapi(PVOID *oldApi, PVOID newApi)
{
	BOOL br = FALSE;
	DetourTransactionBegin();//HOOK��ʼ
	DetourUpdateThread(GetCurrentThread());;//ˢ�µ�ǰ�߳�
	//�������������ε���DetourDetach,���������������HOOK
	DetourDetach(oldApi, newApi);//ж��HOOK
	br = DetourTransactionCommit();//HOOK��Ч
	if (br == NO_ERROR)
	{
		br = TRUE;
	}
	else
	{
		br = FALSE;
	}
	return br;
}


