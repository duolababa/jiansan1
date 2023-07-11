#pragma once
#define 取启动时间() GetCurrentTime()	







#define g_行走状态 0x754
#define 基址_小退call 0x279E160
#define g_公共仓库索引 0x1246b0
#define g_背包仓库头 0x6CC
#define en鼠标call 0xE31AF0
#define en鼠标基址 0x36D1D00
#define 基址_坐船rcx 0x4C836C0
#define 基址_坐船call 0x1475020
#define 采集数量call 0x1329200
#define 采集物品数量 0x4C75ED0
#define 丢弃写入基址 0x1364CA0




#define 基址_个人_遍历 0x4C10FE0
#define 基址_个人_判断虚表 0x2897A40
#define 基址_个人_坐标 0x4C71448
#define 基址_地图_寻路call 0x2471E00
#define 基址_背包_遍历 0x4C1D1B0
#define 基址_背包_获取名字call 0x624310
#define 基址_背包_获取名字rcx 0x4C0EF30
#define 基址_背包_使用物品call_rcx 0xAF12B0
#define 基址_背包_使用物品call 0x27E0610
#define 基址_背包_使用物品call2 0x27DEA80
#define 基址_技能_快捷栏 0x4C1D1B8
#define 基址_技能_获取名字call 0x1170060
#define 基址_技能_获取名字rcx 0x4C10FC0
#define 基址_环境_打开npc 0x2630F60
#define 基址_环境_npc对话标志 0x4C72CB0
#define 基址_环境_是否处于加载界面 0x4C3A9C4
#define 基址_任务_快捷栏 0x4C1D270
#define 基址_任务_获取任务对象 0x24B9B10
#define 基址_任务_获取任务目标信息 0x1072880
#define 基址_坐骑_使用坐骑call 0x249DD60
#define 基址_个人_速度校验地址 0x255CE24
#define 基址_环境_地图ID 0x4C1D9E8
#define 基址_技能_使用技能call 0x2471E00
#define 基址_任务_接任务call 0x1106410
#define 基址_环境_退出npc对话 0x4C10FC8
#define 基址_任务_获取任务坐标 0x1589AA0
#define 基址_地图_环境 0x4C74F30
#define 基址_地图_获取环境名字call 0xD11FF0
#define 基址_副本_入场HOOK地址 0x190A143
#define 基址_副本_入场CALL 0x1C9F300
#define 基址_环境_判断动画 0x4C77B28
#define 基址_鼠标_鼠标写入地址 0x2666716
#define 基址_鼠标_鼠标写入地址2 0x25603A0
#define 基址_鼠标_坐标 0x4C71448
#define 基址_鼠标_游戏坐标转鼠标call 0x236A070
#define 基址_鼠标_游戏坐标转鼠标rcx 0x4CA600C
#define 基址_新手_选择职业call 0x20A35D0
#define 基址_新手_退出体验call 0x202F830
#define 基址_新手_获取序幕对象call 0x1F9B100
#define 基址_新手_获取序幕对象rcx 0x4C10FE0
#define 基址_新手_跳过序幕call 0x284DC90
#define 基址_环境_传送call 0x12EDB50
#define 基址_环境_传送rcx 0x4C10FD8
#define 基址_环境_传送点遍历 0x4C30CCC
#define 基址_环境_怪物是否死亡 0x253CA20
#define 基址_环境_npc对话分支call 0x1312920
#define 基址_封包_发包call 0x26ACD50
#define 基址_封包_发包rcx 0x4C10FE8
#define 基址_技能_升级技能包头 0x6CD2E96
#define 基址_个人_社交动作call 0x1154CD0
#define 基址_个人_社交动作rcx 0x4C70618
#define 基址_背包_修理call 0x13FCEC0
#define 基址_背包_修理rcx 0x4C84688
#define 基址_副本_进入其他副本call 0x1C9F040
#define 基址_个人_复活包头 0x3BF1240
#define 基址_环境_拾物call 0x2665C90
#define 基址_地图_获取大地图名 0x25A410
#define 基址_拍卖_获取剩余时间call 0x21CC400
#define 基址_UI_按键参数 0x1E7B768
#define 基址_个人_乐谱遍历rcx 0x4C0EF30
#define 基址_个人_乐谱遍历rdx 0x4BE04DC
#define 基址_个人_乐谱遍历call 0x25BBA0
#define 基址_个人_演奏乐谱call 0xFCA440
#define 基址_个人_演奏乐谱rcx 0x4C74F60
#define 基址_UI_航海出港call 0xC9DE70
#define 基址_UI_航海出港rcx 0x4C1D288
#define 基址_UI_航海入港call 0xCA7BE0
#define 基址_本人_修理船只call 0xC8D710
#define 基址_地图_获取港口传送点ID 0x79E2D0
#define 基址_UI_准备出航call 0x2CDD860
#define 基址_登录_选择服务器call 0x246BA20
#define 基址_登录_选择服务器rcx 0x4C768A8
#define 基址_登录_确认协议call 0x284BA20
#define 基址_登录_选择职业call 0x245A7B8
#define 基址_登录_选择职业rcx 0x4C9CDC8
#define 基址_登录_创建角色 0x1279520
#define 基址_登录_打开创建角色call 0x28521F0
#define 基址_登录_进入游戏call 0x2460CC0
#define 基址_登录_进入游戏rcx 0x4C74540
#define 基址_任务_获取任务地图ID 0x15255F0
#define 基址_地图_目的地址是否可达Call 0x16A3300
#define 基址_地图_目的地址是否可达_rax获取偏移 0x330
#define 基址_组队_遍历 0x4C1D258
#define 基址_组队_离开队伍call 0x26AE710
#define 基址_组队_离开队伍rcx 0x4C10FE8
#define 基址_组队_离开队伍rdx 0x399A780
#define 基址_组队_踢出队伍call 0x26AE710
#define 基址_组队_踢出队伍rdx 0x3A76AD0
#define 基址_组队_邀请队伍call 0x26AE710
#define 基址_组队_邀请队伍rdx 0x3A76A60
#define 基址_组队_同意邀请call 0x22B2F30
#define 基址_个人_分解call 0xF2DDC0
#define 基址_个人_分解rcx 0x4C77C78
#define 基址_个人_打开分解call 0x1FFA300
#define 基址_个人_打开分解rcx 0x4C10FE0
#define 基址_个人_召唤宠物call 0x1080DE0
#define 基址_个人_召唤宠物rcx 0x4C70638
#define 基址_任务_阶段任务完成call 0x1373F40
#define 基址_拍卖_获取遍历对象rcx 0x4C86178
#define 基址_拍卖_登记物品遍历call 0x17FA130
#define 基址_拍卖_即使购买call 0xCA5210
#define 基址_拍卖_即使购买rcx 0x4C744F8
#define 基址_拍卖_登记封包头 0x39736C0
#define 基址_战斗_是否战斗call偏移 0x348
#define gc_SkillShortKeySet 0x1106510
#define gb_voyageLinerList 0x4C836C0
#define gb_ActorList 0x4C10FD0
#define go_hj_HideState 0xB4
#define gb_AttrList 0x4C1D1B0
#define go_hj_myRole 0x49C
#define gb_UiList 0x4C10FE0
#define gb_ShortKey 0x4C1D1B0
#define go_AttrList_off1 0xE4
#define go_bag_dSize 0x6C0
#define go_bag_offset2 0x54DB0
#define gb_ResBase 0x4C0EF30
#define go_Res_dtotal 0xD8
#define gb_QuestCur 0x4C1D270
#define gb_QuestRes 0x4C0EF38
#define go_QuestStepCompStart 0x156C
#define gb_Str 0x4CA0888
#define go_sk_offset 0x4AD0
#define go_SkillCurPreset 0x166F5C
#define go_ShortKey_CurPage 0x163470
#define go_ShortKey_Life 0x70
#define go_ShortKey_Fight 0x70
#define gb_MouseInfo 0x4C71448
#define gb_SceneMovie 0x4C110E8
#define gb_EntranceInfo 0x4C71C68
#define go_DungeonMoviePass 0x108
#define gb_CurTeleportList 0x4C30CCC
#define go_RecomEquip 0x610
#define gc_WearEquip 0x24D5F20
#define gc_UnWearEquip 0x1A89160
#define gb_ActorTakeStatus 0x4C70600
#define go_UiMsgStart 0x144
#define gc_CheckGuildQuest 0x2823300
#define gb_GuildQuestList 0x4C797F0
#define gc_ShopBuyAddItem 0x13A3740
#define go_ShopBuyItemState 0x1E0
#define go_ShopBuyItemListStart 0x160
#define gc_ShopBuyItem 0x22B9630
#define go_ShopListStart 0x94
#define gb_ShopBase 0x4C84688
#define gc_GameListFree 0x10C7900
#define gc_GetNpcQuestTalkCurList 0x24ACAA0
#define gc_GetNpcQuestTalkResList 0x605CE0
#define gc_ExpressMailDel 0x1FA9EF0
#define gc_ExpressMailGetItemAll 0x1FAA5E0
#define gc_ExpressMailSelectByIndex 0x1E5B020
#define gc_ExpressMailWndShowClick 0x1E5AD20
#define go_ExpressMailOpened 0x120
#define go_ExpressMailMoney1 0x120
#define go_ExpressMailMoney2 0x3404
#define go_ExpressMailSize 0x3560
#define go_ExpressMailCurSel 0x160
#define gb_ExpressMailList 0x4C71B70
#define go_ExpressMailType 0x104
#define go_ExpressMailState 0x10B
#define go_ExpressMailSenderName 0x20
#define go_ExpressMailTitle 0x58
#define go_bag_Vehicle 0x166F78
#define gb_CommonAction 0x4C10FD8
#define gc_ItemJobCheck 0xAAC430
#define go_BS_RandomItemOpenAll 0x34
#define go_BSItem_ItemInfo 0x42C
#define go_BSItem_WndInfo 0x420
#define gc_UseItem 0x24FBAB0
#define gb_Attendance 0x4C75EB0
#define go_AttendanceListStart 0xCC
#define gc_AttendanceTake 0x1105ED0
#define go_MousePoint 0x3EC
#define go_Role_FishObj 0x5A90
#define go_Role_FishObj_State 0xED8
#define go_QuickSlotType 0x4BC
#define gc_MsgBoxConfirm 0x1C07920
#define go_PortalMapId 0x2C4
#define go_MarketUiSerchCheck 0x38C
#define gc_AuctionSearchStart 0xCA5D80
#define go_AuctionDataSet 0x1FC
#define go_AuctionSearchState 0x664
#define gc_DataCopy 0xC512B0
#define gb_AuctionInfo 0x4C744F8
#define go_ExchangeShopWndTabVauleCtrl 0x418
#define go_ExchangeShopWndTabCurVaule 0x55C
#define gc_UIShowCtrl 0x20002D0
#define gc_WelcomeChallengeLockCheck 0x151A260
#define gb_WelcomeChallenge 0x4C7A470
#define go_WelcomeChallengeMissionId 0x98
#define gc_WelcomeChallengeRewardTake 0x157D270
#define gc_WelcomeChallengeTypeNewIndex 0x151A910
#define go_ShopListSize 0x128
#define gc_BarterShopEquipLevCheck 0x13AE3A0
#define gc_BarterShopExchange 0x13A6110
#define gc_GetMoneyValue 0x24B53B0
#define go_RoleMoneyListStart 0x120
#define go_PacketSocketObj 0x174
#define go_GameStageValue 0xE4
#define gb_PacketInfo 0x4C10FE8
#define go_CharacterSrvId 0x1720
#define go_CharacterLev 0x189C
#define go_CharacterName 0x1872
#define go_CharacterIndex 0x1B18
#define go_CharacterJob 0x1AC2
#define gb_CharacterList 0x4C74540
#define go_CharacterListStart 0xA4
#define go_CharacterListSize 0x1B3C
#define gc_hottimeEventRewardTake 0x14BF440
#define gc_hottimeEventRewardCheck 0x14B1260
#define gb_hottimeEvent 0x4C86158
#define go_PortalOpen 0xED8
#define gc_VoyageShipSelectShip 0x1A53420
#define go_VoyageCurShipId 0x100
#define gb_VoyageData 0x4C1D288
#define gc_VoyageShipDelCrew 0xC64C90
#define gc_VoyageShipAddCrew 0xCBA450
#define go_VoyageCrewTotal 0x166FAC
#define go_GetInteractPropState 0xB94
#define go_hj_VehicleId 0x49D8
#define go_ActionTimingData 0x124
#define go_ActionTimingMaxTime 0x2D4
#define gb_ExpeditionRecdList 0x4C110D8
#define go_ExpeditionRecdStart 0x364
#define gb_ExpeditionLev 0x4C3B216
#define gc_MemAlloc 0x36CD7C8
#define gc_ExpeditionInRecv 0xC34FF0
#define gc_DungeonEntranceEnter 0xE954D0
#define go_DungeonEntranceInfoArg 0x110
#define gc_ItemShortKeySet 0x26AEA20
#define gc_EngraveDrag 0x24E8EC0
#define gb_EngraveList 0x4C74510
#define go_EngraveListStart 0x9C
#define gc_getAbilityResAddr 0x606420
#define go_BookCurInfoStart 0x94
#define go_BookTakeedItemNum 0x98
#define go_BookRewardItemNum 0xE0
#define gb_BookCurInfo 0x4C744E0
#define go_BookCurPorcess 0xE4
#define gb_getBookReward包头 0x3BB6C70
#define go_getBookRewardSendArg 0x52
#define go_quickSlotFramePageArray 0x3E0
#define go_ActorShow 0x7E8
#define gc_ActorShow 0x1602D00
#define gb_ChaosDungeonInfo 0x4C72DE8
#define go_ChaosDungeonState 0xA5
#define go_BattleState 0xF08
#define go_ItemAbilityTotal 0x65E
#define go_ItemAbilityStartAddr 0x66C
#define go_ItemAbilityStartOffset -0xC   //需要每次检查
#define go_ItemAbilityId -0xA   //需要每次检查
#define go_marbleWndItemListTotal 0x458
#define go_marbleWndItemCurSel 0x448
#define gc_marbleWndItemSelect 0x2191DD0
#define gc_marbleWndItemStartBtn 0x21526F0
#define go_marbleWndItemListSize 0x6F0
#define go_marbleWndItemCntrType 0x6C4
#define go_marbleWndItemSrvId 0xB8
#define go_ItemGradeLev 0x20
#define go_ItemBuildListStart 0xD08
#define go_ItemBuildListSize 0x724
#define gc_ItemBuildUpListSelectIndex 0x21EEB30
#define go_ItemBuildUpSelect 0x4E8
#define go_ItemBuildCurItemSrvId 0x5C8
#define gc_ItemBuildLevUpSucess 0x21D2D10
#define gc_ItemBuildLevUpResult 0x21DB7C0
#define gc_ItemBuildUpChildLevelUpGradeBtn 0x21F9B00
#define gc_ItemBuildUpLevelUpGrade 0x21ECCB0
#define gc_ItemBuildUpChildLevelUpBtn 0x21F8960
#define go_ItemBuildUpCurExp 0xA8
#define gc_ItemBuildUpMaxBtn 0x221CF40
#define gc_ItemBuildUpLevelUp 0x1814710
#define gc_CheckAbilityStone 0x1D28B10
#define gc_CharacterGetJumpState 0x243DAE0
#define gb_CurSeverIndex 0x4C1D9C8
#define gb_AccountSpecInfo 0x4C11018
#define gc_AccountSpecCheck 0x2A4DC0
#define gc_UesJumpByIndex 0x2467BB0
#define go_deadSceneTotal 0x470
#define go_deadSceneStart 0x3FC
#define go_DeadSceneChildList 0x17C
#define gc_deadSceneWndBtn 0x1BD5420
#define gb_UnasTask 0x4C72DE0
#define go_UnasWeeklyQuestStart 0xD4
#define go_UnasWeeklyQuestState 0x1514
#define go_UnasWeeklyQuestType 0x150C
#define go_UnasTaskWeekPoint 0x3A897
#define go_UnasTaskDayPoint 0x3C0
#define gc_CheckUnasWeeklyQuestCon 0x24CE350
#define go_UseSkillOffset 0x110
#define go_ManPoBaseOffset 0x98
#define gc_UseSkillCall 0x246C950
#define go_ItemGemCombineConfigValue 0x5C
#define gb_ItemGemCombineConfigSet 0x4C74520
#define gc_ItemGemCombineConfigSet 0xF310D0
#define gb_判断加载基址 0x4C71C30
#define go_加载偏移1 0xC0
#define go_加载偏移2 0x18
#define 偏移_本人_最大血 0x518
#define 偏移_本人_骑马状态 0x81C
#define 偏移_本人_走路状态 0x49E8
#define 偏移_个人_当前动作 0x110
#define 偏移_个人_当前怒气值 0x5A80
#define 偏移_怪物_不可攻击偏移 0x5A82
#define 偏移_背包_数组大小 0x6C0
#define 偏移_背包_装备遍历数组头 0x985B0
#define 偏移_背包_物品遍历数组头 0x54DB0
#define 偏移_背包_生活装备遍历数组头 0x163908
#define 偏移_背包_未知2遍历数组头 0x60810348
#define 偏移_背包_最大耐久度 0x390
#define 偏移_背包_当前耐久度 0x69C
#define 偏移_鼠标_坐标 0x2C8
#define 偏移_技能_冷却 0x4AD0
#define 偏移_技能_技能点数 0x166F4C
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
#define 偏移_背包_物品id 0x6B8
#define 偏移_背包_物品resid 0x24
#define 偏移_背包_物品数量 0x6B0
#define 偏移_背包_物品等级 0x11C
#define 偏移_环境_升降机标志 0x4C1DA20
#define 偏移_拍卖_数组头 0x94
#define 偏移_拍卖_数组大小 0x780
#define 偏移_拍卖_物品id 0x2C
#define 偏移_拍卖_物品等级 0x11E
#define 偏移_拍卖_立即购买 0x48
#define 偏移_拍卖_最低出价 0x6E8

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

