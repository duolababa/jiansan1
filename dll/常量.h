#pragma once

#define ȡ����ʱ��() GetCurrentTime()	


#define DATA_OF_OBJCT_OF2 0x38
#define DATA_OF_BOJCT_OF3 0x8

#define DATA_OF_OBJECT_TREE_FLAG 0x19
#define DATA_OF_OBJECT_TREE_PDATA 0x28
#define DATA_OF_OBJECT_TREE_ID 0x20
#define  DATA_OF_OBJECT_TREE_NAME 0x88
#define  DATA_OF_OBJECT_TREE_X 0x10
#define  DATA_OF_OBJECT_TREE_Y 0x14
#define  DATA_OF_OBJECT_TREE_Z 0x18
//#define  DATA_OF_OBJECT_TREE_����״̬ 0xE0C    //41 B9 ?? ?? ?? ?? 44 0F 49 C8 45 85 C9 44 0F 4F CB 33 C9 + 0x13
#define  DATA_OF_OBJECT_TREE_�Ƿ����� 0x130
//#define  DATA_OF_OBJECT_TREE_HP 0x3E8    //49 0F AF D1 4C 63 C0 4D 0F AF C1 48 03 D1 4D 85 C0   -0x1C
//#define  DATA_OF_OBJECT_TREE_MaxHP 0x3F0    //49 0F AF D1 4C 63 C0 4D 0F AF C1 48 03 D1 4D 85 C0  -0x2a
//#define  DATA_OF_OBJECT_TREE_LV 0x10C   //F7 42 ?? ?? ?? ?? ?? 48 8B DA 8B 71 ?? 48 8B F9 75 ?? 48 8B 0D ?? ?? ?? ?? +0x19  
//#define  DATA_OF_OBJECT_TREE_Money 0xdc80  //48 8B DA 89 44 24 ?? E8 ?? ?? ?? ?? 85 C0 74 ?? 41 B9 ?? ?? ?? ?? 4C 8D 05 ?? ?? ?? ?? EB ?? + 1f  0xdca0-CEC0



#define  DATA_OF_OBJECT_TREE_Money1 0xDF8

//8B 81 ?? ?? ?? ?? C3 CC CC CC CC CC CC CC CC CC 8B 81 ?? ?? ?? ?? C3 CC CC CC CC CC CC CC CC CC 8B 81 ?? ?? ?? ?? C3 CC CC CC CC CC CC CC CC CC 89 91 ?? ?? ?? ?? C3 CC CC CC CC CC CC CC CC CC 8B 81 ?? ?? ?? ?? C3 CC CC CC CC CC CC CC CC CC 8B 81 ?? ?? ?? ?? C3 CC CC CC CC CC CC CC CC CC 89 91 ?? ?? ?? ?? C3 CC CC CC CC CC CC CC CC CC 8B 81 ?? ?? ?? ?? C3 CC CC CC CC CC CC CC CC CC 8B 81 ?? ?? ?? ?? C3 CC CC CC CC CC CC CC CC CC 8B 81 ?? ?? ?? ?? C3 
//�ڶ���+20


//#define DATA_OF_OBJBA_OF1 0xb808   //E8 ?? ?? ?? ?? 48 8B D8 48 85 C0 0F 84 ?? ?? ?? ?? 48 8B 10 48 8B C8 48 89 74 24 ?? FF 52 ?? 48 8B 13 -0x18
//#define DATA_OF_OBJBA_OF2 0x20//48 8D 0C C0 48 C1 E1 ?? 49 03 C9 E8 ?? ?? ?? ?? 48 83 C4 ??   -7
#define DATA_OF_OBJBA_SIZE 0x120
#define  DATA_OF_OBJBA_TREE_NUM 0x70
#define  DATA_OF_OBJBA_TREE_ID 0x8
#define  DATA_OF_OBJBA_TREE_type 0xC
#define  DATA_OF_OBJBA_TREE_NAME 0x48


#define jieshiqircx 0x5AE7A8
#define qLuaLoadString 0x244130
#define qLuaPCALL 0x245890
#define qLuaTostringCall 0x246480
#define qLUApop 0x246270
#define DATA_BASE_BOJECT 0x897AA0
#define DATA_OF_OBJCT_0F1 0x659B28
#define DATA_BASE_BACK 0x897C30
#define hookyouhua 0xB3077
#define mingwenrcx 0x897C50
#define ��Ϣ�� 0x5AE7A8
#define ������ 0xD450
#define ����1 0x4AF0
#define ����2 0x1620
#define �Ƿ��ͼ 0x897BF0
#define OBJ_user_suo 0x131E0
#define DATA_OF_OBJBA_jineng 0xB88
#define wabao 0x2F6AD0
#define anjianr8 0x1598
#define anjianrcx 0x5AE7A8
#define anjiancall 0x10BE50
#define DATA_OF_OBJECT_TREE_����״̬ 0xE74
#define DATA_OF_OBJECT_TREE_HP 0x3E8
#define DATA_OF_OBJECT_TREE_MaxHP 0x3F0
#define DATA_OF_OBJECT_TREE_Money 0xDCB8
#define DATA_OF_OBJECT_TREE_LV 0x10C
#define DATA_OF_OBJBA_ս��״̬ 0x4BC
#define DATA_OF_OBJBA_OF1 0xB840
#define DATA_OF_OBJBA_OF2 0x20
#define jieshiqi 0x1030





#define ��Ϣ���� 0x5A19B8

//KGUIX64.dll + 5A19B8



#define ��Ϣ��_1 0x20001
#define ��Ϣ��_2 0x30001
#define ��Ϣ��_3 0x40001
#define ��Ϣ��_4 0x50001
#define ��Ϣ��_5 0x60001
#define ��Ϣ��_6 0x70001
#define ��Ϣ��_7 0x80001
#define ��Ϣ��_8 0x90001
#define ��Ϣ��_9 0xA0001
#define ��Ϣ��_0 0xB0001
#define ��Ϣ��_F1 0x3B0001
#define ��Ϣ��_F2 0x3C0001
#define ��Ϣ��_F3 0x3D0001
#define ��Ϣ��_F4 0x3E0001
#define ��Ϣ��_F5 0x3F0001
#define ��Ϣ��_F6 0x400001
#define ��Ϣ��_F7 0x410001
#define ��Ϣ��_F8 0x420001
#define ��Ϣ��_F9 0x430001
#define ��Ϣ��_F10 0x440001
#define ��Ϣ��_F11 0x570001
#define ��Ϣ��_F12 0x580001
#define ��Ϣ��_A 0x1E0001
#define ��Ϣ��_S 0x1F0001
#define ��Ϣ��_D 0x200001
#define ��Ϣ��_W 0x110001
#define ��Ϣ��_X 0x2D0001
#define ��Ϣ��_CTRL 0x1D0001
#define ��Ϣ��_Spac 0x390001
#define ��Ϣ��_Ait 0x20380001
#define ��Ϣ��_�س� 0x1C0001
#define ��Ϣ��_Q 0x100001
#define ��Ϣ��_E 0x120001
#define ��Ϣ��_Tab 0xF0001
#define ��Ϣ��_F 0x210001
#define ��Ϣ��_Shift 0x2A0001


//#define DATA_OF_OBJBA_jineng 0xB58   //488BD985C00F84????????FFC8
//#define DATA_OF_OBJBA_ս��״̬ 0x4bc   //488B46??4885C00F85????????41B9????????  -d


//48 89 5C 24 ?? 48 89 6C 24 ?? 48 89 74 24 ?? 48 89 7C 24 ?? 41 56 48 83 EC ?? 48 8B 05 ?? ?? ?? ?? 33 FF 8B DF 49 8B E8 4C 8B F2 48 8B F1 44 8B 48 ?? 
//$+461B3      hookyouhua  �ַ���     | 48 8D 05 85 12 47  | lea rax,qword ptr ds:[7FF629F9D078]      | 7FF629F9D078:"KPlayerClient::Send"

//4C 8B 40 ?? 49 8B C8 49 8B 40 ?? 80 78 ?? ?? 75 ??    ��Χ����

//48 8B D3 E8 ?? ?? ?? ?? EB ?? 44 0F B6 47 ??  -7