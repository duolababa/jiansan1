#pragma once
#define 取启动时间() GetCurrentTime()	


















#define 基址_个人_遍历 0x4BF6D00
#define 基址_个人_判断虚表 0x288AF20
#define 基址_个人_坐标 0x4C56FD8
#define 基址_地图_寻路call 0x2465780
#define 基址_背包_遍历 0x4C02E58
#define 基址_背包_获取名字call 0x6227A0
#define 基址_背包_获取名字rcx 0x4BF4C50
#define 基址_背包_使用物品call_rcx 0xAED2A0
#define 基址_背包_使用物品call 0x27D45E0
#define 基址_背包_使用物品call2 0x27D2A40
#define 基址_技能_快捷栏 0x4C02E60
#define 基址_技能_获取名字call 0x116A050
#define 基址_技能_获取名字rcx 0x4BF6CE0
#define 基址_环境_打开npc 0x2624870
#define 基址_环境_npc对话标志 0x4C58830
#define 基址_环境_是否处于加载界面 0x4C20650
#define 基址_任务_快捷栏 0x4C02F18
#define 基址_任务_获取任务对象 0x24AD420
#define 基址_任务_获取任务目标信息 0x106BAC0
#define 基址_坐骑_使用坐骑call 0x2491550
#define 基址_个人_速度校验地址 0x2550674
#define 基址_环境_地图ID 0x4C03698
#define 基址_技能_使用技能call 0x2465780
#define 基址_任务_接任务call 0x10FF6D0
#define 基址_环境_退出npc对话 0x4BF6CE8
#define 基址_任务_获取任务坐标 0x15823C0
#define 基址_地图_环境 0x4C5AAB0
#define 基址_地图_获取环境名字call 0xD0BF90
#define 基址_副本_入场HOOK地址 0x19022B3
#define 基址_副本_入场CALL 0x1C96330
#define 基址_环境_判断动画 0x4C5D6A8
#define 基址_鼠标_鼠标写入地址 0x265A796
#define 基址_鼠标_鼠标写入地址2 0x2553BF0
#define 基址_鼠标_坐标 0x4C56FD8
#define 基址_鼠标_游戏坐标转鼠标call 0x235E8E0
#define 基址_鼠标_游戏坐标转鼠标rcx 0x4C8BAE4
#define 基址_新手_选择职业call 0x2098920
#define 基址_新手_退出体验call 0x2024AE0
#define 基址_新手_获取序幕对象call 0x1F90220
#define 基址_新手_获取序幕对象rcx 0x4BF6D00
#define 基址_新手_跳过序幕call 0x2841230
#define 基址_环境_传送call 0x12E5AA0
#define 基址_环境_传送rcx 0x4BF6CF8
#define 基址_环境_传送点遍历 0x4C16958
#define 基址_环境_怪物是否死亡 0x2530670
#define 基址_环境_npc对话分支call 0x130A890
#define 基址_封包_发包call 0x26A1610
#define 基址_封包_发包rcx 0x4BF6D08
#define 基址_技能_升级技能包头 0xFFFFFFFF8E876FE6
#define 基址_个人_社交动作call 0x114EAE0
#define 基址_个人_社交动作rcx 0x4C56208
#define 基址_背包_修理call 0x13F5810
#define 基址_背包_修理rcx 0x4C6A208
#define 基址_副本_进入其他副本call 0x1C96070
#define 基址_个人_复活包头 0x3BDC930
#define 基址_环境_拾物call 0x2659D10
#define 基址_地图_获取大地图名 0x259630
#define 基址_拍卖_获取剩余时间call 0x299E490
#define 基址_UI_按键参数 0x1E7B768
#define 基址_个人_乐谱遍历rcx 0x4BF4C50
#define 基址_个人_乐谱遍历rdx 0x4BC61EC
#define 基址_个人_乐谱遍历call 0x25ADC0
#define 基址_个人_演奏乐谱call 0xFC2AA0
#define 基址_个人_演奏乐谱rcx 0x4C5AAE0
#define 基址_UI_航海出港call 0xC97560
#define 基址_UI_航海出港rcx 0x4C02F30
#define 基址_UI_航海入港call 0xCA1220
#define 基址_本人_修理船只call 0xC86D90
#define 基址_地图_获取港口传送点ID 0x79B930
#define 基址_UI_准备出航call 0x2CCD4A0
#define 基址_登录_选择服务器call 0x245F3A0
#define 基址_登录_选择服务器rcx 0x4C5C428
#define 基址_登录_确认协议call 0x283EFB0
#define 基址_登录_选择职业call 0x244E578
#define 基址_登录_选择职业rcx 0x4C828B8
#define 基址_登录_创建角色 0x1271B90
#define 基址_登录_打开创建角色call 0x28457B0
#define 基址_登录_进入游戏call 0x2454A60
#define 基址_登录_进入游戏rcx 0x4C5A0C0
#define 基址_任务_获取任务地图ID 0x151DEA0
#define 基址_地图_目的地址是否可达Call 0x169BC50
#define 基址_地图_目的地址是否可达_rax获取偏移 0x330
#define 基址_组队_遍历 0x4C02F00
#define 基址_组队_离开队伍call 0x26A2890
#define 基址_组队_离开队伍rcx 0x4BF6D08
#define 基址_组队_离开队伍rdx 0x49597976
#define 基址_组队_踢出队伍call 0x26A2890
#define 基址_组队_踢出队伍rdx 0x3A62090
#define 基址_组队_邀请队伍call 0x26A2890
#define 基址_组队_邀请队伍rdx 0x3A62020
#define 基址_组队_同意邀请call 0x22A8000
#define 基址_个人_分解call 0xF26840
#define 基址_个人_分解rcx 0x4C5D7F8
#define 基址_个人_打开分解call 0x1FEF440
#define 基址_个人_打开分解rcx 0x4BF6D00
#define 基址_个人_召唤宠物call 0x107A020
#define 基址_个人_召唤宠物rcx 0x4C56228
#define 基址_任务_阶段任务完成call 0x136C860
#define 基址_拍卖_获取遍历对象rcx 0x4C6BCE8
#define 基址_拍卖_登记物品遍历call 0x17F2130
#define 基址_拍卖_即使购买call 0xC9E9E0
#define 基址_拍卖_即使购买rcx 0x4C5A078
#define 基址_拍卖_登记封包头 0x395EA58
#define gc_SkillShortKeySet 0x10FF7D0
#define gb_voyageLinerList 0x4C69240
#define gb_ActorList 0x4BF6CF0
#define go_hj_HideState 0xB4
#define gb_AttrList 0x4C02E58
#define go_hj_myRole 0x49C
#define gb_UiList 0x4BF6D00
#define gb_ShortKey 0x4C02E58
#define go_AttrList_off1 0xE4
#define go_bag_dSize 0x6C8
#define go_bag_offset2 0x553F0
#define gb_ResBase 0x4BF4C50
#define go_Res_dtotal 0xD8
#define gb_QuestCur 0x4C02F18
#define gb_QuestRes 0x4BF4C58
#define go_QuestStepCompStart 0x156C
#define gb_Str 0x4C86370
#define go_sk_offset 0x4AD0
#define go_SkillCurPreset 0x1689E4
#define go_ShortKey_CurPage 0x164EB8
#define go_ShortKey_Life 0x71
#define go_ShortKey_Fight 0x71
#define gb_MouseInfo 0x4C56FD8
#define gb_SceneMovie 0x4BF6DF8
#define gb_EntranceInfo 0x4C577F0
#define go_DungeonMoviePass 0x108
#define gb_CurTeleportList 0x4C16958
#define go_RecomEquip 0x610
#define gc_WearEquip 0x24C9850
#define gc_UnWearEquip 0x22BF320
#define gb_ActorTakeStatus 0x4C561F0
#define go_UiMsgStart 0x144
#define gc_CheckGuildQuest 0x2816940
#define gb_GuildQuestList 0x4C5F370
#define gc_ShopBuyAddItem 0x139BD10
#define go_ShopBuyItemState 0x1E0
#define go_ShopBuyItemListStart 0x160
#define gc_ShopBuyItem 0x22AE5D0
#define go_ShopListStart 0x94
#define gb_ShopBase 0x4C6A208
#define gc_GameListFree 0xC0A070
#define gc_GetNpcQuestTalkCurList 0x24A0390
#define gc_GetNpcQuestTalkResList 0x604170
#define gc_ExpressMailDel 0x1F9EF80
#define gc_ExpressMailGetItemAll 0x1F9F660
#define gc_ExpressMailSelectByIndex 0x1E51360
#define gc_ExpressMailWndShowClick 0x1E51060
#define go_ExpressMailOpened 0x3554
#define go_ExpressMailMoney1 0x118
#define go_ExpressMailMoney2 0xA
#define go_ExpressMailSize 0x104
#define go_ExpressMailCurSel 0x160
#define gb_ExpressMailList 0x4C57708
#define go_ExpressMailType 0xCC
#define go_ExpressMailState 0xFF
#define go_ExpressMailSenderName 0xCD
#define go_ExpressMailTitle 0x9
#define go_bag_Vehicle 0x168A00
#define gb_CommonAction 0x4BF6CF8
#define gc_ItemJobCheck 0xAA83A0
#define go_BS_RandomItemOpenAll 0x34
#define go_BSItem_ItemInfo 0x42C
#define go_BSItem_WndInfo 0x420
#define gc_UseItem 0x24EF720
#define gb_Attendance 0x4C5BA30
#define go_AttendanceListStart 0xCC
#define gc_AttendanceTake 0x10FF190
#define go_MousePoint 0x3EC
#define go_Role_FishObj 0x5A90
#define go_Role_FishObj_State 0xED8
#define go_QuickSlotType 0x4BC
#define gc_MsgBoxConfirm 0x1BFEFF0
#define go_PortalMapId 0x2C4
#define go_MarketUiSerchCheck 0x38C
#define gc_AuctionSearchStart 0xC9F550
#define go_AuctionDataSet 0x1FC
#define go_AuctionSearchState 0x664
#define gc_DataCopy 0xC4A3E0
#define gb_AuctionInfo 0x4C5A078
#define go_ExchangeShopWndTabVauleCtrl 0x418
#define go_ExchangeShopWndTabCurVaule 0x55C
#define gc_UIShowCtrl 0x1FF5400
#define gc_WelcomeChallengeLockCheck 0x1512B80
#define gb_WelcomeChallenge 0x4C5FFF0
#define go_WelcomeChallengeMissionId 0x98
#define gc_WelcomeChallengeRewardTake 0x1575B70
#define gc_WelcomeChallengeTypeNewIndex 0x1513230
#define go_ShopListSize 0x128
#define gc_BarterShopEquipLevCheck 0x13A69C0
#define gc_BarterShopExchange 0x139E730
#define gc_GetMoneyValue 0x24A8CB0
#define go_RoleMoneyListStart 0x120
#define go_PacketSocketObj 0x174
#define go_GameStageValue 0xE4
#define gb_PacketInfo 0x4BF6D08
#define go_CharacterSrvId 0x16F0
#define go_CharacterLev 0x1A9A
#define go_CharacterName 0x1A68
#define go_CharacterIndex 0x1AE0
#define go_CharacterJob 0x2
#define gb_CharacterList 0x4C5A0C0
#define go_CharacterListStart 0xA4
#define go_CharacterListSize 0x1B44
#define gc_hottimeEventRewardTake 0x14B7900
#define gc_hottimeEventRewardCheck 0x14A96B0
#define gb_hottimeEvent 0x4C6BCC8
#define go_PortalOpen 0xED8
#define gc_VoyageShipSelectShip 0x1A4ACB0
#define go_VoyageCurShipId 0x100
#define gb_VoyageData 0x4C02F30
#define gc_VoyageShipDelCrew 0xC5E0F0
#define gc_VoyageShipAddCrew 0xCB3AB0
#define go_VoyageCrewTotal 0x168A34
#define go_GetInteractPropState 0xB94
#define go_hj_VehicleId 0x49D8
#define go_ActionTimingData 0x124
#define go_ActionTimingMaxTime 0x2D4
#define gb_ExpeditionRecdList 0x4BF6DE8
#define go_ExpeditionRecdStart 0x364
#define gb_ExpeditionLev 0x4C20EB6
#define gc_MemAlloc 0x36BA7C8
#define gc_ExpeditionInRecv 0xC2DE40
#define gc_DungeonEntranceEnter 0xE8E400
#define go_DungeonEntranceInfoArg 0x17A
#define gc_ItemShortKeySet 0x26A2BA0
#define gc_EngraveDrag 0x24DCB90
#define gb_EngraveList 0x4C5A090
#define go_EngraveListStart 0x9C
#define gc_getAbilityResAddr 0x6048B0
#define go_BookCurInfoStart 0x94
#define go_BookTakeedItemNum 0x98
#define go_BookRewardItemNum 0xE0
#define gb_BookCurInfo 0x4C5A060
#define go_BookCurPorcess 0xE4
#define gb_getBookReward包头 0x3BA22D0
#define go_getBookRewardSendArg 0x53
#define go_quickSlotFramePageArray 0x3E0
#define go_ActorShow 0x7E8
#define gc_ActorShow 0x15FB620
#define gb_ChaosDungeonInfo 0x4C58968
#define go_ChaosDungeonState 0xAD
#define go_BattleState 0xF08
#define go_ItemAbilityTotal 0x653
#define go_ItemAbilityStartAddr 0x661
#define go_ItemAbilityStartOffset -0xC   //需要每次检查
#define go_ItemAbilityId -0xA  //需要每次检查
#define go_marbleWndItemListTotal 0x458
#define go_marbleWndItemCurSel 0x448
#define gc_marbleWndItemSelect 0x2187370
#define gc_marbleWndItemStartBtn 0x2147B60
#define go_marbleWndItemListSize 0x6F8
#define go_marbleWndItemCntrType 0x6CC
#define go_marbleWndItemSrvId 0xB0
#define go_ItemGradeLev 0x10
#define go_ItemBuildListStart 0xD10
#define go_ItemBuildListSize 0x72C
#define gc_ItemBuildUpListSelectIndex 0x21E3F40
#define go_ItemBuildUpSelect 0x4E8
#define go_ItemBuildCurItemSrvId 0x5C8
#define gc_ItemBuildLevUpSucess 0x21C8150
#define gc_ItemBuildLevUpResult 0x21D0C00
#define gc_ItemBuildUpChildLevelUpGradeBtn 0x21EEF60
#define gc_ItemBuildUpLevelUpGrade 0x2B56790
#define gc_ItemBuildUpChildLevelUpBtn 0x21EDDB0
#define go_ItemBuildUpCurExp 0xA8
#define gc_ItemBuildUpMaxBtn 0x2212340
#define gc_ItemBuildUpLevelUp 0x238F8E0
#define gc_CheckAbilityStone 0x1D1FA90
#define gc_CharacterGetJumpState 0x2431C60
#define gb_CurSeverIndex 0x4C03678
#define gb_AccountSpecInfo 0x4BF6D38
#define gc_AccountSpecCheck 0x2A3DA0
#define gc_UesJumpByIndex 0x245B5A0
#define go_DeadSceneChildList 0x17C	
#define go_deadSceneTotal 0x470
#define go_deadSceneStart 0x3FC
#define gc_deadSceneWndBtn 0x1BCCEC0
#define go_UseSkillOffset 0x110
#define go_ManPoBaseOffset 0x98
#define gc_UseSkillCall 0x024602D0 	//lostark.exe:$0x27DFFF0 0x98
#define gb_判断加载基址 0x4C577B8
#define go_加载偏移1 0xC0
#define go_加载偏移2 0x18
#define 偏移_本人_最大血 0x518
#define 偏移_本人_骑马状态 0x81C
#define 偏移_本人_走路状态 0x49E8
#define 偏移_个人_当前动作 0x110
#define 偏移_个人_当前怒气值 0x5A80
#define 偏移_怪物_不可攻击偏移 0x5A82
#define 偏移_背包_数组大小 0x6C8
#define 偏移_背包_装备遍历数组头 0x990F0
#define 偏移_背包_物品遍历数组头 0x553F0
#define 偏移_背包_生活装备遍历数组头 0x165350
#define 偏移_背包_未知2遍历数组头 0xFFFFFFFFE8810348
#define 偏移_背包_最大耐久度 0x390
#define 偏移_背包_当前耐久度 0x4
#define 偏移_鼠标_坐标 0x2C8
#define 偏移_技能_冷却 0x4AD0
#define 偏移_技能_技能点数 0x1689D4
#define 偏移_环境_对象虚表 0x728
#define 偏移_环境_怪物血量1 0x5A8
#define 偏移_环境_怪物血量2 0x510
#define 偏移_类型_击打道具 0xED0
#define 偏移_环境_击打道具是否死亡 0xF10
#define 偏移_环境_击打道具是否死亡_类型11 0xE90
#define 偏移_环境_击打道具是否死亡_类型7 0x11C8
#define 偏移_UI_按键参数 0x79C
#define 偏移_UI_按键虚表 0x270
#define 偏移_UI_读条1 0x49E8
#define 偏移_UI_读条2 0x2C
#define 偏移_本人_移速1 0xE10
#define 偏移_本人_移速2 0x35C
#define 偏移_UI_进入副本按钮 0x420
#define 偏移_任务_获取任务地图ID偏移 0x11C
#define 偏移_任务_已完成任务 0x180
#define 偏移_其他_面向角度 0x4B8
#define 偏移_背包_物品id 0x6B0
#define 偏移_背包_物品resid 0x6B8
#define 偏移_背包_物品数量 0x6BC
#define 偏移_背包_物品等级 0x11C
#define 偏移_环境_升降机标志 0x4C036D0
#define 偏移_拍卖_数组头 0x94
#define 偏移_拍卖_数组大小 0x788
#define 偏移_拍卖_物品id 0x700
#define 偏移_拍卖_物品等级 0x11E
#define 偏移_拍卖_立即购买 0x4A
#define 偏移_拍卖_最低出价 0x38



//#define 偏移_背包_物品数量 0x6B8
//#define 偏移_背包_物品id 0x6A8
//#define 偏移_背包_物品resid 1712 //id+8;
//define go_Character_lev 0X26E
#define 偏移_地图_寻路rcx 0x110
#define 偏移_环境_拾物 0x49C //4883EC??488B89????????4885C974??488B01FF50??4885C074??488B80????????4883C4??C333C04883C4??C3 +4
//00007FF67C3DF9B0 | 48:83EC 28 | sub rsp, 0x28 |
//00007FF67C3DF9B4 | 48 : 8B89 9C040000 | mov rcx, qword ptr ds : [rcx + 0x49C] |
//00007FF67C3DF9BB | 48 : 85C9 | test rcx, rcx |
//00007FF67C3DF9BE | 74 17 | je 0x7FF67C3DF9D7 |
//00007FF67C3DF9C0 | 48 : 8B01 | mov rax, qword ptr ds : [rcx] |
//00007FF67C3DF9C3 | FF50 30 | call qword ptr ds : [rax + 0x30] |
//00007FF67C3DF9C6 | 48 : 85C0 | test rax, rax |
//00007FF67C3DF9C9 | 74 0C | je 0x7FF67C3DF9D7 |
//00007FF67C3DF9CB | 48 : 8B80 7C020000 | mov rax, qword ptr ds : [rax + 0x27C] |
//00007FF67C3DF9D2 | 48 : 83C4 28 | add rsp, 0x28 |
//00007FF67C3DF9D6 | C3 | ret |
//00007FF67C3DF9D7 | 33C0 | xor eax, eax |
//00007FF67C3DF9D9 | 48 : 83C4 28 | add rsp, 0x28 |
//00007FF67C3DF9DD | C3 | ret |
//00007FF67C3DF9DE | CC | int3 |
//00007FF67C3DF9DF | CC | int3 |
//00007FF67C3DF9E0 | 40 : 53 | push rbx |
//00007FF67C3DF9E2 | 48 : 83EC 20 | sub rsp, 0x20 |
//00007FF67C3DF9E6 | 48 : 8B99 9C040000 | mov rbx, qword ptr ds : [rcx + 0x49C] |
//00007FF67C3DF9ED | 48 : 85DB | test rbx, rbx |
//00007FF67C3DF9F0 | 74 3F | je 0x7FF67C3DFA31 |
//00007FF67C3DF9F2 | 48 : 8B5B 18 | mov rbx, qword ptr ds : [rbx + 0x18] |
//00007FF67C3DF9F6 | 48 : 85DB | test rbx, rbx |
//00007FF67C3DF9F9 | 74 36 | je 0x7FF67C3DFA31 |
//00007FF67C3DF9FB | 48 : 8B05 06D85702 | mov rax, qword ptr ds : [0x7FF67E95D208] |
//00007FF67C3DFA02 | 48 : 85C0 | test rax, rax |
//00007FF67C3DFA05 | 75 0C | jne 0x7FF67C3DFA13 |
//00007FF67C3DFA07 | E8 F492DDFE | call 0x7FF67B1B8D00 |
#define 偏移_环境_拾物2 0xD0 //488B81????????C3CCCCCCCCCCCCCCCC488B81????????C3CCCCCCCCCCCCCCCC488B91????????33C0483991????????480F44C2C3
//00007FF67B1B6760 | 48:8B81 D0000000 | mov rax, qword ptr ds : [rcx + 0xD0] |
//00007FF67B1B6767 | C3 | ret |
//00007FF67B1B6768 | CC | int3 |
//00007FF67B1B6769 | CC | int3 |
//00007FF67B1B676A | CC | int3 |
//00007FF67B1B676B | CC | int3 |
//00007FF67B1B676C | CC | int3 |
//00007FF67B1B676D | CC | int3 |
//00007FF67B1B676E | CC | int3 |
//00007FF67B1B676F | CC | int3 |
//00007FF67B1B6770 | 48:8B81 800E0000 | mov rax, qword ptr ds : [rcx + 0xE80] |
//00007FF67B1B6777 | C3 | ret |
//00007FF67B1B6778 | CC | int3 |
//00007FF67B1B6779 | CC | int3 |
//00007FF67B1B677A | CC | int3 |
//00007FF67B1B677B | CC | int3 |
//00007FF67B1B677C | CC | int3 |
//00007FF67B1B677D | CC | int3 |
//00007FF67B1B677E | CC | int3 |
//00007FF67B1B677F | CC | int3 |
//00007FF67B1B6780 | 48:8B91 240E0000 | mov rdx, qword ptr ds : [rcx + 0xE24] |
//00007FF67B1B6787 | 33C0 | xor eax, eax |
//00007FF67B1B6789 | 48 : 3991 98000000 | cmp qword ptr ds : [rcx + 0x98] , rdx |
//00007FF67B1B6790 | 48 : 0F44C2 | cmove rax, rdx |
//00007FF67B1B6794 | C3 | ret |
#define 偏移_本人_航海耐久 1620
#define 偏移_本人_装备评分 1644
#define 偏移_UI_航海界面 636
#define 偏移_UI_显示 184
#define 偏移_坐标 0x7C//124
#define 偏移_其他_采集标识 0x400
//#define 偏移_任务_已完成任务 0x180 //?? 8D ?? ?? ?? ?? ?? ?? 33 ?? ?? 8D ?? ?? ?? 8B ?? ?? ?? ?? ?? E8 ?? ?? ?? ?? ?? 63 ?? ?? ?? ?? 8B ?? ?? ?? ?? 8D +3
//#define 偏移_NPC头上任务 0xD90 //83 ?? ?? ?? ?? ?? ?? 74 ?? 83 ?? ?? ?? ?? ?? ?? 74 ?? 33 ?? C3 ?? ?? ?? ?? ?? C3 +9+2 
//
//
//#define 偏移_怪物_不可攻击偏移  1 //0F ?? ?? ?? ?? ?? ?? 3C ?? 73 ?? 0F ?? ?? 85 ?? 78 ?? 3B ?? ?? 7D ?? 0F ?? ?? ?? 8B ?? 8B +3
//#define 偏移_个人_当前怒气值  2 //FF ?? ?? ?? ?? ?? 83 ?? ?? 0F ?? ?? ?? ?? ?? ?? 8B ?? ?? ?? ?? ?? ?? 85 ?? 74 ?? ?? 8B ?? FF ?? ?? ?? ?? ?? 85 ?? 0F  +0F+3
//#define 偏移_个人_当前动作 3 //E8 ?? ?? ?? ?? ?? 83 ?? ?? ?? ?? ?? ?? 0F ?? ?? ?? ?? ?? ?? 8D ?? ?? ?? ?? ?? 0F ?? ?? E8 ?? ?? ?? ?? ?? 8D  +0x13+3 [[2157DE00020+104+30]]+30  读4字节

