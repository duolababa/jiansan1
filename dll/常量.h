#pragma once
#define 取启动时间() GetCurrentTime()	




//
//#define g_坐骑 0x166f78
//#define g_坐骑_index单 0x17
//#define g_坐骑_叠加单 0x8

#define 是否可以骑马写入基址 0x16C9D30
#define g_坐骑 0xA9F24
#define g_坐骑_index单 0xC
#define g_坐骑_叠加单 0x23
#define g_是否骑马 0x4FC0
#define 怪物目标 0x53F8

#define g_行走状态 0x76C
#define g_背包仓库头 0x6CC
#define g_公共仓库索引 0x8a570
#define 基址_小退call 0x28C47A0


#define en鼠标call 0xE49A80
#define en鼠标基址 0x1EB87D8

#define 基址_坐船rcx 0x4C836C0
#define 基址_坐船call 0x1475020


#define 采集数量call 0x143B360
#define 采集物品数量 0x4EF3140
#define 丢弃写入基址 0x1462A30
#define 分解颜色call 0x21145E0
#define 入包call 0x1466030

#define 上马call地址 0x26AA210
#define 新坐标寻路call 0x17FE990
#define 新坐标寻路rcx 0x4F0B5E0



#define 基址_个人_遍历 0x4E8DEB0
#define 基址_个人_遍历偏移 0x190
#define 基址_个人_虚表数组偏移 0x7B8
#define 基址_个人_虚表数组头 0x328
#define 基址_个人_判断虚表 0x2B4DEB0
#define 基址_个人_坐标 0x4EF30D8
#define 基址_地图_寻路call 0x2682460
#define 基址_背包_遍历 0x4E9C310
#define 基址_背包_获取名字call 0x661FD0
#define 基址_背包_获取名字rcx 0x4E8DEA8
#define 基址_背包_使用物品call_rcx 0x21379F0
#define 基址_背包_使用物品call 0x2A6AEE0
#define 基址_背包_使用物品call2 0x2A69390
#define 基址_技能_快捷栏 0x4E9C318
#define 基址_技能_获取名字call 0x1263D80
#define 基址_技能_获取名字rcx 0x4E8FEC0
#define 基址_环境_打开npc 0x2829480
#define 基址_环境_npc对话标志 0x4EF5368
#define 基址_环境_是否处于加载界面 0x4EBA600
#define 基址_任务_快捷栏 0x4E9C3D0
#define 基址_任务_获取任务对象 0xCD12F0
#define 基址_坐骑_使用坐骑call 0x26AA210
#define 基址_个人_速度校验地址 0x2761614
#define 基址_环境_地图ID 0x4E9CB98
#define 基址_技能_使用技能call 0x2682460
#define 基址_任务_接任务call 0x11FAA00
#define 基址_环境_退出npc对话 0x4EF22F8
#define 基址_任务_获取任务坐标 0x16FD4D0
#define 基址_地图_环境 0x4EF7788
#define 基址_地图_获取环境名字call 0xE06E80
#define 基址_副本_入场HOOK地址 0x19CC033
#define 基址_副本_入场CALL 0x1E16FC0
#define 基址_环境_判断动画 0x4EF4270
#define 基址_鼠标_鼠标写入地址 0x2858676
#define 基址_鼠标_鼠标写入地址2 0x27FCE50
#define 基址_鼠标_坐标 0x4EF30D8
#define 基址_鼠标_游戏坐标转鼠标call 0x25BD630
#define 基址_鼠标_游戏坐标转鼠标rcx 0x4F2BCD8
#define 基址_新手_选择职业call 0x2243B10
#define 基址_新手_退出体验call 0x21DB8D0
//#define 基址_新手_获取序幕对象call 0x未找到
#define 基址_新手_获取序幕对象rcx 0x4E8DEB0
#define 基址_直升_跳过序幕rcx 0x4EF6CA8
#define 基址_直升_跳过序幕call 0x1028900
#define 基址_新手_跳过序幕call 0x2A55530
#define 基址_环境_传送call 0x1481FD0
#define 基址_环境_传送rcx 0x4E8FED8
#define 基址_环境_传送点遍历 0x4EB080C
#define 基址_环境_怪物是否死亡 0x273D110
#define 基址_环境_npc对话分支call 0x141B820
#define 基址_封包_发包call 0x2945C50
#define 基址_封包_发包rcx 0x4E8DEB8
#define 基址_技能_升级技能包头 0x3C87A68
#define 基址_个人_社交动作call 0x124AA80
#define 基址_个人_社交动作rcx 0x4EF22F0
#define 基址_背包_修理call 0x1512E60
#define 基址_背包_修理rcx 0x4EF2318
#define 基址_副本_进入其他副本call 0x1E16E10
#define 基址_个人_复活包头 0x3E0E158
#define 基址_环境_拾物call 0x2857BD0
#define 基址_地图_获取大地图名 0x285310
#define 基址_拍卖_获取剩余时间call 0x2BA6230
#define 基址_UI_按键参数 0x1EA4520
#define 基址_个人_乐谱遍历rcx 0x4E8DEA8
#define 基址_个人_乐谱遍历rdx 0x4E5CC20
#define 基址_个人_乐谱遍历call 0x6C82B0
#define 基址_个人_演奏乐谱call 0x113F270
#define 基址_个人_演奏乐谱rcx 0x4EF77A8
#define 基址_UI_航海出港call 0xD95440
#define 基址_UI_航海出港rcx 0x4E9C3E8
#define 基址_UI_航海入港call 0xD9EED0
#define 基址_本人_修理船只call 0xD84D50
#define 基址_地图_获取港口传送点ID 0x7F02F0
#define 基址_UI_准备出航call 0x2F95E60
#define 基址_登录_选择服务器call 0x267BDA0
#define 基址_登录_选择服务器rcx 0x4EF91D0
#define 基址_登录_确认协议call 0x2A524B0
#define 基址_登录_选择职业call 0x266A5E0
#define 基址_登录_选择职业rcx 0x4F223A0
#define 基址_登录_创建角色 0x13787B0
#define 基址_登录_打开创建角色call 0x2A5A0C0
#define 基址_登录_进入游戏call 0x2670EF0
#define 基址_登录_进入游戏rcx 0x4EF6CD8
#define 基址_任务_获取任务地图ID 0x4D5B70
#define 基址_地图_目的地址是否可达Call 0x1828E60
#define 基址_地图_目的地址是否可达_rax获取偏移 0x338
#define 基址_地图_目的地址是否可达_r12偏移 0xE34
#define 基址_地图_目的地址是否可达_r12获取偏移 0x1B8
#define 基址_地图_目的地址是否可达_rax偏移 0xF3C
#define 基址_组队_遍历 0x4E9C3B8
#define 基址_组队_离开队伍call 0x29474D0
#define 基址_组队_离开队伍rcx 0x4E8DEB8
#define 基址_组队_离开队伍rdx 0x3BA6058
#define 基址_组队_踢出队伍call 0x29474D0
#define 基址_组队_踢出队伍rdx 0x3C87C28
#define 基址_组队_邀请队伍call 0x29474D0
#define 基址_组队_邀请队伍rdx 0x3C87BB8
#define 基址_组队_同意邀请call 0x251D750
#define 基址_个人_分解call 0x1022840
#define 基址_个人_分解rcx 0x4EFA5C0
#define 基址_个人_打开分解call 0x21AD130
#define 基址_个人_打开分解rcx 0x4E8DEB0
#define 基址_个人_召唤宠物call 0x115CFF0
#define 基址_个人_召唤宠物rcx 0x4EF2318
#define 基址_任务_阶段任务完成call 0x1470450
#define 基址_拍卖_获取遍历对象rcx 0x4F09E20
#define 基址_拍卖_登记物品遍历call 0x19784C0
#define 基址_拍卖_即使购买call 0xD9C410
#define 基址_拍卖_即使购买rcx 0x4EF6C98
#define 基址_拍卖_登记封包头 0x3B7F1D0
#define 基址_战斗_是否战斗call偏移 0x350
#define 基址_背包_丢弃Rcx 0x4EF3140
#define 基址_背包_丢弃CALL 0x1462A30
#define gc_SkillShortKeySet 0x11FAB00
#define gb_voyageLinerList 0x1
#define gb_ActorList 0x4E8FED0
#define go_hj_HideState 0xB4
#define gb_AttrList 0x4E9C310
#define go_hj_myRole 0x4E4
#define gb_UiList 0x4E8DEB0
#define gb_ShortKey 0x4E9C310
#define go_AttrList_off1 0xE4
#define go_bag_dSize 0x330
#define go_bag_offset2 0x28530
#define gb_ResBase 0x4E8DEA8
#define go_Res_dtotal 0xD8
#define gb_QuestCur 0x4E9C3D0
#define gb_QuestRes 0x4E8E050
#define go_QuestStepCompStart 0x1578
#define gb_Str 0x4F26128
#define go_sk_offset 0x4FA4
#define go_SkillCurPreset 0xA9F08
#define go_ShortKey_CurPage 0xA8060
#define gb_MouseInfo 0x4EF30D8
#define gb_SceneMovie 0x4E8FFC8
#define gb_EntranceInfo 0x4EF4278
#define go_DungeonMoviePass 0x108
#define gb_CurTeleportList 0x4EB080C
#define go_RecomEquip 0x614
#define gc_WearEquip 0x26E0E80
#define gc_UnWearEquip 0x1BF2400
#define gb_ActorTakeStatus 0x4EF22D8
#define go_UiMsgStart 0x230
#define gc_CheckGuildQuest 0x2A2BD50
#define gb_GuildQuestList 0x4EFC378
#define gc_ShopBuyAddItem 0x14A5A70
#define go_ShopBuyItemState 0x1E0
#define go_ShopBuyItemListStart 0x160
#define gc_ShopBuyItem 0x2464C00
#define go_ShopListStart 0x94
#define gb_ShopBase 0x4F06998
#define gc_GameListFree 0x2AE9950
#define gc_GetNpcQuestTalkCurList 0x26B8820
#define gc_GetNpcQuestTalkResList 0x642F50
#define gc_ExpressMailDel 0x2149530
#define gc_ExpressMailGetItemAll 0x2149CC0
#define gc_ExpressMailSelectByIndex 0x1FED650
#define gc_ExpressMailWndShowClick 0x1FED350
#define go_ExpressMailOpened 0x1772
#define go_ExpressMailMoney1 0x120
#define go_ExpressMailMoney2 0x1B13
#define go_ExpressMailSize 0x4CD8F7C0//需要每次确认检查 
#define go_ExpressMailCurSel 0x160
#define gb_ExpressMailList 0x4EF34A0
#define go_ExpressMailType 0x3A
#define go_ExpressMailState 0x40
#define go_ExpressMailSenderName 0x1
#define go_ExpressMailTitle 0x60
#define go_bag_Vehicle 0xA9F24
#define gb_CommonAction 0x4E8FED8
#define gc_ItemJobCheck 0xB01760
#define go_BS_RandomItemOpenAll 0x34
#define go_BSItem_ItemInfo 0x430
#define go_BSItem_WndInfo 0x424
#define gc_UseItem 0x2705180
#define gb_Attendance 0x4EF8780
#define go_AttendanceListStart 0xC0
#define gc_AttendanceTake 0x11FA480
#define go_MousePoint 0x3EC
#define go_Role_FishObj 0x5F7C
#define go_Role_FishObj_State 0xF04
#define go_QuickSlotType 0x4C0
#define gc_MsgBoxConfirm 0x1D76C40
#define go_PortalMapId 0x1FC
#define go_MarketUiSerchCheck 0x38C
#define gc_AuctionSearchStart 0xD9CF80
#define go_AuctionDataSet 0x200
#define go_AuctionSearchState 0x660
#define gc_DataCopy 0xD482E0
#define gb_AuctionInfo 0x4EF6C98
#define go_ExchangeShopWndTabVauleCtrl 0x41C
#define go_ExchangeShopWndTabCurVaule 0x558
#define gc_UIShowCtrl 0x21B33D0
#define gc_WelcomeChallengeLockCheck 0x16AF200
#define gb_WelcomeChallenge 0x4EFD000
#define go_WelcomeChallengeMissionId 0x94
#define gc_WelcomeChallengeRewardTake 0x16EE9E0
#define gc_WelcomeChallengeTypeNewIndex 0x16AF750
#define go_ShopListSize 0x12C
#define gc_BarterShopEquipLevCheck 0x14AF7A0
#define gc_BarterShopExchange 0x14A7CF0 //检查下是E9还是F9
#define gc_GetMoneyValue 0x26C1470
#define go_RoleMoneyListStart 0x120
#define go_PacketSocketObj 0x174
#define go_GameStageValue 0xE4
#define gb_PacketInfo 0x4E8DEB8
#define go_CharacterSrvId 0xC10
#define go_CharacterLev 0x9BE
#define go_CharacterName 0x888
#define go_CharacterIndex 0xC18
#define go_CharacterJob 0xC0C
#define gb_CharacterList 0x4EF6CD8
#define go_CharacterListStart 0xA4
#define go_CharacterListSize 0x4C54
#define gc_hottimeEventRewardTake 0x163C830
#define gc_hottimeEventRewardCheck 0x162A290
#define gb_hottimeEvent 0x4F09DE0
#define go_PortalOpen 0xF04
#define gc_VoyageShipSelectShip 0x1BBA470
#define go_VoyageCurShipId 0x100
#define gb_VoyageData 0x4E9C3E8
#define gc_VoyageShipDelCrew 0xD5B8D0
#define gc_VoyageShipAddCrew 0xDB0480
#define go_VoyageCrewTotal 0xA9F58
#define go_GetInteractPropState 0xBB8
#define go_hj_VehicleId 0x4EAC
#define go_ActionTimingData 0x124
#define go_ActionTimingMaxTime 0x2DC
#define gb_ExpeditionRecdList 0x4E8FFB8
#define go_ExpeditionRecdStart 0x364
#define gb_ExpeditionLev 0x4EBAE04
#define gc_MemAlloc 0x38BB870
#define gc_ExpeditionInRecv 0xD2B590
#define gc_DungeonEntranceEnter 0xF49EB0
#define go_DungeonEntranceInfoArg 0x110
#define gc_ItemShortKeySet 0x2947B70
#define gc_EngraveDrag 0x26F32B0
#define gb_EngraveList 0x4EF91A0
#define go_EngraveListStart 0x9C
#define gc_getAbilityResAddr 0x643690
#define go_BookCurInfoStart 0x94
#define go_BookTakeedItemNum 0x98
#define go_BookRewardItemNum 0xE0
#define gb_BookCurInfo 0x4EF6C80
#define go_BookCurPorcess 0xE4
#define gb_getBookReward包头 0x3DD3380
#define go_getBookRewardSendArg 0x52
#define go_quickSlotFramePageArray 0x3E4
#define go_ActorShow 0x7F8
#define gc_ActorShow 0x1718710
#define gb_ChaosDungeonInfo 0x4EF54C0
#define go_ChaosDungeonState 0xA4
#define go_BattleState 0xF2C
#define go_ItemAbilityTotal 0x1F
#define go_ItemAbilityStartAddr 0x2D
#define go_ItemAbilityStartOffset -0xC   //需要每次检查
#define go_ItemAbilityId -0xA   //需要每次检查
#define go_marbleWndItemListTotal 0x45C
#define go_marbleWndItemCurSel 0x44C
#define gc_marbleWndItemSelect 0x233A190
#define gc_marbleWndItemStartBtn 0x230F230
#define go_marbleWndItemListSize 0x360
#define go_marbleWndItemCntrType 0x334
#define go_marbleWndItemSrvId 0x10
#define go_ItemGradeLev 0x1C
#define go_ItemBuildListStart 0x97C
#define go_ItemBuildListSize 0x394
#define gc_ItemBuildUpListSelectIndex 0x2462D40
#define go_ItemBuildUpSelect 0x444
#define go_ItemBuildCurItemSrvId 0x480
#define gc_ItemBuildLevUpSucess 0x237C8F0
#define gc_ItemBuildLevUpResult 0x2383260
#define gc_ItemBuildUpChildLevelUpGradeBtn 0x23A6C30
#define gc_ItemBuildUpLevelUpGrade 0x2393AA0
#define gc_ItemBuildUpChildLevelUpBtn 0x23A59D0
#define go_ItemBuildUpCurExp 0xB0
#define gc_ItemBuildUpMaxBtn 0x23D05F0
#define gc_ItemBuildUpLevelUp 0x2D76B40
#define gc_CheckAbilityStone 0x1EA3810
#define gc_CharacterGetJumpState 0x264D050
#define gb_CurSeverIndex 0x4E9CB78
#define gb_AccountSpecInfo 0x4E8DEC8
#define gc_AccountSpecCheck 0x261900
#define gc_UesJumpByIndex 0x2677DE0
#define go_deadSceneTotal 0x48C
#define go_deadSceneStart 0x400
#define go_DeadSceneChildList 0x17C
#define gc_deadSceneWndBtn 0x1D43D50
#define gb_UnasTask 0x4EF54B8
#define go_UnasWeeklyQuestStart 0xD4
#define go_UnasWeeklyQuestState 0x1514
#define go_UnasWeeklyQuestType 0x150C
#define go_UnasTaskWeekPoint 0x372
#define go_UnasTaskDayPoint 0x374
#define gc_CheckUnasWeeklyQuestCon 0x26D9500
#define go_UseSkillOffset 0x110
#define go_ManPoBaseOffset 0x98
#define gc_UseSkillCall 0x267CEE0
#define go_ItemGemCombineConfigValue 0x5C
#define gb_ItemGemCombineConfigSet 0x4EF6CB8
#define gc_ItemGemCombineConfigSet 0x1025EA0
#define gb_判断加载基址 0x4EF4240
#define go_加载偏移1 0xC0
#define go_加载偏移2 0x18
#define 偏移_本人_最大血 0x554
#define 偏移_本人_骑马状态 0x858
#define 偏移_本人_走路状态 0x4EBC
#define 偏移_个人_当前动作 0x110
#define 偏移_个人_当前怒气值 0x5F6C
#define 偏移_怪物_不可攻击偏移 0x5F6E
#define 偏移_背包_数组大小 0x330
#define 偏移_背包_装备遍历数组头 0x48330
#define 偏移_背包_物品遍历数组头 0x28530
#define 偏移_背包_生活装备遍历数组头 0xA8534
#define 偏移_背包_未知2遍历数组头 0xA9F0C
#define 偏移_背包_最大耐久度 0x258
#define 偏移_背包_当前耐久度 0x2E8
#define 偏移_鼠标_坐标 0x2C8
#define 偏移_技能_冷却 0x4FA4
#define 偏移_技能_技能点数 0xA9EF8
#define 偏移_环境_对象虚表 0x738
#define 偏移_环境_怪物血量1 0x5A8
#define 偏移_环境_怪物血量2 0x510
#define 偏移_类型_击打道具 0xEFC
#define 偏移_环境_击打道具是否死亡 0xF3C
#define 偏移_环境_击打道具是否死亡_类型11 0xEB4
#define 偏移_环境_击打道具是否死亡_类型7 0x11F4
#define 偏移_UI_按键参数 0x7B4
#define 偏移_UI_按键虚表 0x270
#define 偏移_UI_读条1 0x4EBC
#define 偏移_UI_读条2 0x2C
#define 偏移_本人_移速1 0xE34
#define 偏移_本人_移速2 0x35C
#define 偏移_UI_进入副本按钮 0x424
#define 偏移_任务_获取任务地图ID偏移 0x12C
#define 偏移_任务_获取任务地图ID偏移2 0x124
#define 偏移_任务_已完成任务 0x180
#define 偏移_其他_面向角度 0x4B8
#define 偏移_背包_物品id 0x310
#define 偏移_背包_物品resid 0x2F8
#define 偏移_背包_物品数量 0x318
#define 偏移_背包_物品等级 0x94
#define 偏移_环境_升降机标志 0x4E9CBD0
#define 偏移_拍卖_数组头 0x48
#define 偏移_拍卖_数组大小 0x388
#define 偏移_拍卖_物品id 0x4A
#define 偏移_拍卖_物品等级 0x96
#define 偏移_拍卖_立即购买 0x48
#define 偏移_拍卖_最低出价 0x1

//#define 偏移_背包_物品数量 0x6B8
//#define 偏移_背包_物品id 0x6A8
//#define 偏移_背包_物品resid 1712 //id+8;
//define go_Character_lev 0X26E
#define 偏移_地图_寻路rcx 0x110
#define 偏移_环境_拾物 0x4E4 //4883EC??488B89????????4885C974??488B01FF50??4885C074??488B80????????4883C4??C333C04883C4??C3 +4
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
#define 偏移_本人_装备评分 0x670
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

#define g_M 0x491C
#define g_F6 0x492A
#define g_空格 0x4954
#define g_N 0x491D
#define g_C 0x4912
#define g_I 0x4918
#define g_G 0x4916
#define g_Q 0x4920
#define g_W 0x4924
#define g_E 0x4914
#define g_R 0x4921
#define g_Z 0x23A9
#define g_B 0x4911
#define g_V 0x232A
#define g_A 0x4910
#define g_S 0x4922
#define g_D 0x4913
#define g_F 0x4915
#define g_1 0x4932
#define g_2 0x4933
#define g_3 0x4934
#define g_4 0x4935
#define g_5 0x4936
#define g_F1 0x4925
#define g_F2 0x4926
#define g_F3 0x4927
#define g_F4 0x4928
#define g_F5 0x4929
#define g_Y 0x1D29
#define g_X 0x1D28
#define g_ESC 0x4953
#define g_ENTER 0x494B
#define g_Q 0x4920
#define g_N 0x491D
#define g_Y 0x1D29
#define g_J 0x4919
#define g_U 0x2329
#define g_1 0x4932
#define g_2 0x4933
#define g_K 0x491A
#define g_6 0x4937
#define g_7 0x4938
#define g_8 0x4939
#define g_9 0x493A