#include "pch.h"
#include "ImGuiWin.h"
#include "luaFunc.h"

//IMGUIʹ�ñ�����ʼ��

char InputText[1024 * 20] = u8"";

// ȫ�ֱ��������ʼ��
//ClipboardExample ������ = ClipboardExample();//�������������
UINT64 ȫ��ģ���� = (UINT64)GetModuleHandleA("LOSTARK.exe");

bool b�����ϢӰ����Ϸ;

void MainLuaCall()
{
    ::SendMessageA(g_hWnd, ע����Ϣֵ, Msgid::CallLua, 0);
}


// �ҵ�IMGUI���ڿ�ʼ��
void ��ʾ��ϷIMGUI����(bool* mainBeginSate)
{
	IM_���ó�ʼ��������;
	IM_���ô���_���̶��ߴ�(600, 400);
	IM_��ʼ(u8"LOSTARK - ���� - SCRIPT");
	/*------------------------------*/ 


    //if (IM_������_����(u8"�ؼ�����")) ������5();


    IM_����;
}


