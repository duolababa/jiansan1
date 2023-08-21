#pragma once
#define 取启动时间() GetCurrentTime()	



#define 基址_个人_遍历 0x5017740
#define 基址_个人_坐标 0x507C978
#define 基址_地图_寻路call 0x2721D10
#define 基址_背包_遍历 0x5025D70
#define 基址_背包_获取名字call 0x666AF0
#define 基址_背包_获取名字rcx 0x5017738
#define 基址_背包_使用物品call_rcx 0x21BAC80
#define 基址_背包_使用物品call 0x2B0B170
#define 基址_背包_使用物品call2 0x2B09340
#define 基址_技能_快捷栏 0x5025D78
#define 基址_技能_获取名字call 0x129DC90
#define 基址_技能_获取名字rcx 0x5019750
#define 基址_环境_打开npc 0x28C55A0
#define 基址_环境_npc对话标志 0x507EBE8
#define 基址_环境_是否处于加载界面 0x5044084
#define 基址_任务_快捷栏 0x5025E30
#define 基址_任务_获取任务对象 0xCE2410
#define 基址_坐骑_使用坐骑call 0x274A160
#define 基址_个人_速度校验地址 0x28019D4
#define 基址_环境_地图ID 0x50265E4
#define 基址_技能_使用技能call 0x2721D10
#define 基址_任务_接任务call 0x12322B0
#define 基址_环境_退出npc对话 0x507BB98
#define 基址_任务_获取任务坐标判断 0x4682A0
#define 基址_任务_获取任务坐标 0x176A4B0
#define 基址_地图_环境 0x5081028
#define 基址_地图_获取环境名字call 0xE1E5E0
#define 基址_副本_入场HOOK地址 0x1A372D3
#define 基址_环境_判断动画 0x507DAE8
#define 基址_鼠标_鼠标写入地址 0x28E93A6
#define 基址_鼠标_鼠标写入地址2 0x2899B20
#define 基址_鼠标_坐标 0x507C978
#define 基址_鼠标_游戏坐标转鼠标call 0x2655230
#define 基址_鼠标_游戏坐标转鼠标rcx 0x50B59A0
#define 基址_新手_选择职业call 0x22CE3D0
#define 基址_新手_退出体验call 0x2263F80
#define 基址_新手_获取序幕对象rcx 0x5017740
#define 基址_直升_跳过序幕rcx 0x5080530
#define 基址_直升_跳过序幕call 0x1051D90
#define 基址_新手_跳过序幕call 0x2AF5745
#define 基址_环境_传送call 0x14CE2A0
#define 基址_环境_传送rcx 0x5019768
#define 基址_环境_传送点遍历 0x503A290
#define 基址_环境_怪物是否死亡 0x27DBEC0
#define 基址_环境_npc对话分支call 0x1465440
#define 基址_封包_发包call 0x29D9F40
#define 基址_封包_发包rcx 0x5017748
#define 基址_个人_社交动作call 0x1284000
#define 基址_个人_社交动作rcx 0x507BB90
#define 基址_背包_修理call 0x156A550
#define 基址_背包_修理rcx 0x507BBB8
#define 基址_环境_拾物call 0x28E8900
#define 基址_拍卖_获取剩余时间call 0x2404C10
#define 基址_个人_乐谱遍历rcx 0x5017738
#define 基址_个人_演奏乐谱call 0x1173730
#define 基址_个人_演奏乐谱rcx 0x5081048
#define 基址_UI_航海出港call 0xDAB4C0
#define 基址_UI_航海出港rcx 0x5025E48
#define 基址_UI_航海入港call 0xDB57B0
#define 基址_地图_获取港口传送点ID 0x7F5C60
#define 基址_UI_准备出航call 0x3058270
#define 基址_登录_选择服务器call 0x271B110
#define 基址_登录_选择服务器rcx 0x5082A78
#define 基址_登录_确认协议call 0x2AF5C80
#define 基址_登录_选择职业call 0x27093A0
#define 基址_登录_选择职业rcx 0x50ABDC0
#define 基址_登录_创建角色 0x13BB9F0
#define 基址_登录_打开创建角色call 0x2AFA530
#define 基址_登录_进入游戏call 0x27101F0
#define 基址_登录_进入游戏rcx 0x5080568
#define 基址_任务_获取任务地图ID 0x1698030
#define 基址_地图_目的地址是否可达Call新 0x186CCA0
#define 基址_地图_目的地址是否可达RCX新 0x5094F30
#define 基址_地图_目的地址是否可达Call 0x18966C0
#define 基址_组队_遍历 0x5025E18
#define 基址_组队_离开队伍call 0x29DB950
#define 基址_组队_离开队伍rcx 0x5017748
#define 基址_组队_离开队伍rdx 0x3C98520
#define 基址_组队_踢出队伍call 0x29DB950
#define 基址_组队_踢出队伍rdx 0x3DAAD18
#define 基址_组队_邀请队伍call 0x29DB950
#define 基址_组队_邀请队伍rdx 0x148F6C7
#define 入包call 0x14B1570
#define 基址_个人_分解call 0x104B370
#define 基址_个人_分解rcx 0x5083E80
#define 基址_个人_打开分解call 0x2234F60
#define 基址_个人_打开分解rcx 0x5017740
#define 基址_个人_召唤宠物call 0x1191900
#define 基址_个人_召唤宠物rcx 0x507BBB8
#define 基址_任务_阶段任务完成call 0x14BC3A0
#define 基址_拍卖_获取遍历对象rcx 0x50937D8
#define 基址_拍卖_登记物品遍历call 0x19E4070
#define 基址_拍卖_即使购买call 0xDB2B80
#define 基址_拍卖_即使购买rcx 0x5080520
#define 基址_背包_丢弃Rcx 0x507C9E0
#define 基址_背包_丢弃CALL 0x14ADDC0
#define gc_SkillShortKeySet 0x12323B0
#define gb_ActorList 0x5019760
#define gb_AttrList 0x5025D70
#define gb_UiList 0x5017740
#define gb_ShortKey 0x5025D70
#define gb_ResBase 0x5017738
#define gb_QuestCur 0x5025E30
#define gb_QuestRes 0x50178E0
#define gb_MouseInfo 0x507C978
#define gb_SceneMovie 0x5019848
#define gb_EntranceInfo 0x507DAF0
#define gb_CurTeleportList 0x503A290
#define gc_WearEquip 0x2782FB0
#define gc_UnWearEquip 0x1C63400
#define gb_ActorTakeStatus 0x507BB78
#define gc_CheckGuildQuest 0x2AC8720
#define gb_GuildQuestList 0x5085C48
#define gc_ShopBuyAddItem 0x14F2280
#define gc_ShopBuyItem 0x24FA5B0
#define gb_ShopBase 0x5090318
#define gc_GameListFree 0xE17D80
#define gc_GetNpcQuestTalkCurList 0x2758910
#define gc_GetNpcQuestTalkResList 0x647A70
#define gc_ExpressMailDel 0x21CD0A0
#define gc_ExpressMailGetItemAll 0x21CD830
#define gc_ExpressMailWndShowClick 0x2053000
#define gb_ExpressMailList 0x507CD40
#define gb_CommonAction 0x5019768
#define gb_Attendance 0x5082010
#define gc_AttendanceTake 0x1231A10
#define gc_MsgBoxConfirm 0x1EA5390
#define gc_UIShowCtrl 0x223B3F0
#define gc_WelcomeChallengeLockCheck 0x1717340
#define gb_WelcomeChallenge 0x50868E8
#define gc_WelcomeChallengeRewardTake 0x175B2F0
#define gc_WelcomeChallengeTypeNewIndex 0x1717890
#define gc_BarterShopEquipLevCheck 0x14FCF30
#define gc_GetMoneyValue 0x27615D0
#define gb_PacketInfo 0x5017748
#define gc_AuctionSearchStart 0xDB39A0
#define gc_ItemJobCheck 0xB09310
#define gc_DataCopy 0xD5BE20
#define gc_BarterShopExchange 0x14F4720
#define gc_hottimeEventRewardTake 0x169E170
#define gc_hottimeEventRewardCheck 0x168BCE0
#define gb_hottimeEvent 0x5093770
#define gc_VoyageShipSelectShip 0x1C29500
#define gb_VoyageData 0x5025E48
#define gc_VoyageShipDelCrew 0xD70CA0
#define gc_VoyageShipAddCrew 0xDC7DC0
#define gb_AuctionInfo 0x5080520
#define gb_CharacterList 0x5080568
#define gb_ExpeditionRecdList 0x5019838
#define gb_ExpeditionLev 0x50448F2
#define gc_MemAlloc 0x399C868
#define gc_ExpeditionInRecv 0xD3E850
#define gc_DungeonEntranceEnter 0xFB8F90
#define gc_ItemShortKeySet 0x29DC3B0
#define gc_EngraveDrag 0x2795A00
#define gb_EngraveList 0x5080538
#define gc_getAbilityResAddr 0x6481B0
#define gb_getBookReward包头 0x3F1CAA8
#define gc_ActorShow 0x17856A0
#define gb_ChaosDungeonInfo 0x507ED40
#define gc_marbleWndItemSelect 0x23C8450
#define gc_marbleWndItemStartBtn 0x239C870
#define gc_MarbleNeedMake 0x239C870
#define gc_ItemBuildUpListSelectIndex 0x24F8690
#define gc_ItemBuildLevUpSucess 0x240D6E0
#define gc_ItemBuildLevUpResult 0x2414480
#define gc_ItemBuildUpChildLevelUpGradeBtn 0x2439520
#define gc_ItemBuildUpLevelUpGrade 0x2C5ABC0
#define gc_ItemBuildUpChildLevelUpBtn 0x24382B0
#define gc_ItemBuildUpMaxBtn 0x2464E40
#define gc_ItemBuildUpLevelUp 0x1DD0AB0
#define gc_CheckAbilityStone 0x1FE78B0
#define gc_CharacterGetJumpState 0x26EA4C0
#define gb_CurSeverIndex 0x50265C4
#define gb_AccountSpecInfo 0x5017758
#define gc_AccountSpecCheck 0x25F870
#define gc_UesJumpByIndex 0x2717190
#define gc_CheckUnasWeeklyQuestCon 0x277B0A0
#define gb_ItemGemCombineConfigSet 0x5080548
#define gc_ItemGemCombineConfigSet 0x104F070
#define gb_判断加载基址 0x507DAB8
#define 是否可以骑马写入基址 0x1733220
#define 基址_小退call 0x2ACA930
#define gb_Str 0x50AFA38
#define 偏移_环境_升降机标志 0x502661C
#define gc_UseItem 0x27A8620
#define gb_BookCurInfo 0x5080508
#define gc_deadSceneWndBtn 0x1DA93A0
#define gc_UseSkillCall 0x271C4B0
#define gb_UnasTask 0x507ED38
#define 采集数量call 0x1485130
#define 分解颜色call 0x21973B0
#define 基址_坐船call 0x3058F70
#define 徽章领取call 0x1180110
#define 混沌选项卡call 0x2BA3F70
#define 副本进入写入基址 0x2BA19C0
#define 拍卖写入基址 0x10E6460
#define 基址_工会_输入密码rdx 0x3DEE938
#define 基址_工会_捐赠rdx 0x3F9ACD8
#define 基址_工会_离开call 0x1F80350
#define 交易金额call 0x1714160





#define 基址_地图_获取大地图名 0x50B72F0
#define gc_ExpressMailSelectByIndex 0x2053300
#define 基址_本人_修理船只call 0xDB5C70
#define 基址_个人_乐谱遍历rdx 0x4FF69A0
#define 基址_个人_乐谱遍历call 0x6CD140
#define 基址_副本_入场CALL 0x1E803B0
#define 基址_技能_升级技能包头 0x3DAAB58
#define 基址_副本_进入其他副本call 0x1E80470

#define g_市场拍卖rdx 0x3D0
#define 基址_个人_遍历偏移 0x190
#define 基址_个人_虚表数组偏移 0x7B8
#define go_marbleWndItemCntrType 0x334
#define go_hj_HideState 0xB4
#define go_hj_myRole 0x4E4
#define go_AttrList_off1 0xE4
#define go_bag_dSize 0x330
#define go_bag_offset2 0x28530
#define go_Res_dtotal 0xD8
#define go_QuestStepCompStart 0x1578
#define go_sk_offset 0x4FA4
#define go_SkillCurPreset 0xA9F08
#define go_RecomEquip 0x614
#define go_ShopBuyItemState 0x1E0
#define go_ShopBuyItemListStart 0x160
#define go_ShopListStart 0x94
#define go_ExpressMailOpened 0x1F75
#define go_ExpressMailMoney1 0x148
#define go_ExpressMailMoney2 0x1E24
#define go_ExpressMailCurSel 0x16C
#define go_ExpressMailType 0x13B
#define go_ExpressMailState 0x68
#define go_ExpressMailSenderName 0x8
#define go_ExpressMailTitle 0x68
#define go_BS_RandomItemOpenAll 0x34
#define go_AttendanceListStart 0xC0
#define go_MousePoint 0x3EC
#define go_Role_FishObj 0x5F7C
#define go_Role_FishObj_State 0xEFC
#define go_QuickSlotType 0x4C0
#define go_PortalMapId 0x1FC
#define 基址_地图_目的地址是否可达_rax获取偏移 0x338
#define 基址_地图_目的地址是否可达_r12偏移 0xD8
#define 基址_地图_目的地址是否可达_r12获取偏移 0x1B8
#define 基址_地图_目的地址是否可达_rax偏移 0xF3C
#define go_ShopListSize 0x12C
#define go_RoleMoneyListStart 0x120
#define go_PacketSocketObj 0x174
#define go_GameStageValue 0xE4
#define go_CharacterSrvId 0x8
#define go_CharacterLev 0x1A34
#define go_CharacterName 0x948
#define go_CharacterIndex 0xBA8
#define go_CharacterListStart 0xA4
#define go_CharacterListSize 0x1ADC
#define go_PortalOpen 0xEFC
#define go_VoyageCurShipId 0x100
#define go_VoyageCrewTotal 0xA9F58
#define go_GetInteractPropState 0xBB8
#define go_hj_VehicleId 0x4EAC
#define go_ActionTimingData 0x124
#define go_ActionTimingMaxTime 0x2DC
#define go_ExpeditionRecdStart 0x364
#define go_DungeonEntranceInfoArg 0x110
#define go_EngraveListStart 0x9C
#define go_BookCurInfoStart 0x94
#define go_BookTakeedItemNum 0x98
#define go_BookRewardItemNum 0xE0
#define go_BookCurPorcess 0xE4
#define go_quickSlotFramePageArray 0x3E4
#define go_ActorShow 0x7F8
#define go_ChaosDungeonState 0xA8
#define go_marbleWndItemListTotal 0x45C
#define go_marbleWndItemCurSel 0x44C
#define go_marbleWndItemListSize 0x360
#define go_marbleWndItemSrvId 0x300
#define go_ItemBuildCurItemSrvId 0x5CC
#define go_ItemBuildUpCurExp 0xB0
#define go_deadSceneTotal 0x48C
#define go_deadSceneStart 0x400
#define go_DeadSceneChildList 0x17C
#define go_UnasWeeklyQuestState 0x1514
#define go_UnasTaskWeekPoint 0x378
#define go_UnasTaskDayPoint 0x358
#define go_UseSkillOffset 0x110
#define go_ManPoBaseOffset 0x98
#define go_加载偏移1 0xC0
#define go_加载偏移2 0x18
#define 偏移_本人_最大血 0x554
#define 偏移_本人_骑马状态 0x858
#define 偏移_本人_走路状态 0x4EBC
#define 偏移_个人_当前动作 0x110
#define 偏移_个人_当前怒气值 0x5F6C
#define 偏移_怪物_不可攻击偏移 0x5F6E
#define 偏移_背包_装备遍历数组头 0x48330
#define 偏移_背包_最大耐久度 0x258
#define 偏移_背包_当前耐久度 0x308
#define 偏移_鼠标_坐标 0x2C8
#define go_Character装等评分 0x930
#define 偏移_环境_击打道具是否死亡 0xF34
#define 偏移_环境_击打道具是否死亡_类型11 0xEB4
#define 偏移_环境_击打道具是否死亡_类型7 0x11EC
#define 偏移_UI_读条1 0x4EBC
#define 偏移_UI_读条2 0x2C
#define 偏移_本人_移速1 0xE34
#define 偏移_本人_移速2 0x35C
#define 偏移_UI_进入副本按钮 0x424
#define 偏移_任务_获取任务地图ID偏移 0x12C
#define 偏移_任务_获取任务地图ID偏移2 0x124
#define 偏移_任务_已完成任务 0x180
#define 偏移_其他_面向角度 0x4B8
#define 偏移_背包_物品resid 0x2E8
#define dtotalUI 0x230
#define 寻找打开窗口UI 0x2E0
#define getUiObjByIdUI 0x80C
#define go_ShortKey_CurPage 0xA8060
#define g_坐骑 0xA9F24
#define g_坐骑_index单 0x8
#define g_坐骑_叠加单 0x23
#define 偏移_背包_物品数量 0x314
#define 偏移_背包_物品id 0x300
#define 偏移_背包_物品等级 0x94
#define go_ItemGradeLev 0x310
#define go_ItemBuildListStart 0x304
#define go_ItemBuildListSize 0x394
#define go_ItemBuildUpSelect 0x444
#define 物品颜色 0x90
#define 物品分类 0x8C
#define 偏移_怪物_目标ID 0x5F80
#define go_ExpressMailSize 0x1FBC
#define go_ItemAbilityStartOffset 0x4 
#define go_ItemAbilityId 0x6
#define go_BSItem_WndInfo 0x424
#define go_CharacterJob 0xB7C
#define go_ItemAbilityTotal 0xA
#define go_ItemAbilityStartAddr 0xC
#define go_UnasWeeklyQuestStart 0x11C
#define 偏移_背包_物品遍历数组头 0x28530
#define 偏移_背包_生活装备遍历数组头 0xA8534
#define 偏移_UI_按键参数 0x7B4
#define 偏移_UI_按键虚表 0x270
#define 基址_UI_按键参数 0x1EA3598
#define g_背包仓库头 0x6CC
#define g_公共仓库索引 0x8a570
#define en鼠标call 0xE49920
#define en鼠标基址 0x1EB77D8
#define 新坐标寻路call 0x186CCA0
#define 行会rcx 0x5081038
#define 搜索行会call 0x16980B0
#define 登记call 0x2468400
#define 登记rcx 0x5080528
#define 采集数量call 0x1485130
#define 分解颜色call 0x21973B0
#define 基址_坐船call 0x3058F70
#define 徽章领取call 0x1180110
#define g_商城遍历x 0x5BC
#define 商城箱子rcx 0x5017760
#define 钻石rcx 0x5026218
#define g_商城循环 0x210
#define g_商城遍历 0x4E4
#define g_ShipsetID 0x450
#define g_登记物品 0x654
#define g_钻石 0x21226
#define 是否加入工会 0xA7E8
#define 当前工会名称 0xA488
#define 当前工会名称1 0x214
#define g_挑战 0x94
#define g_挑战1 0x3DC
#define g_挑战2 0x2


#define 邮寄添加物品call 0x1462690



#define 邮寄输入昵称call 0x14B24D0
#define send邮寄call 0x21CE3F0
#define 光标是否激活 0x50BF23E
#define 邮寄选项 0x1DC

#define  打开商品call 0x21ABE40
#define  打开商品rdx 0x5081BB8
//#define 邮寄选项卡call 0x14BFE70



#define g_行走状态 0x76C
#define g_是否骑马 0x4FC0

#define 购买商品箱子写入基址 0x1C2B5E0
#define 打开箱子写入基址 0xF25F90



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
#define 偏移_UI_显示 0xB8
#define 偏移_坐标 0x7C//124
#define 偏移_其他_采集标识 0x400
//#define 偏移_任务_已完成任务 0x180 //?? 8D ?? ?? ?? ?? ?? ?? 33 ?? ?? 8D ?? ?? ?? 8B ?? ?? ?? ?? ?? E8 ?? ?? ?? ?? ?? 63 ?? ?? ?? ?? 8B ?? ?? ?? ?? 8D +3
//#define 偏移_NPC头上任务 0xD90 //83 ?? ?? ?? ?? ?? ?? 74 ?? 83 ?? ?? ?? ?? ?? ?? 74 ?? 33 ?? C3 ?? ?? ?? ?? ?? C3 +9+2 
//
//
//#define 偏移_怪物_不可攻击偏移  1 //0F ?? ?? ?? ?? ?? ?? 3C ?? 73 ?? 0F ?? ?? 85 ?? 78 ?? 3B ?? ?? 7D ?? 0F ?? ?? ?? 8B ?? 8B +3
//#define 偏移_个人_当前怒气值  2 //FF ?? ?? ?? ?? ?? 83 ?? ?? 0F ?? ?? ?? ?? ?? ?? 8B ?? ?? ?? ?? ?? ?? 85 ?? 74 ?? ?? 8B ?? FF ?? ?? ?? ?? ?? 85 ?? 0F  +0F+3
//#define 偏移_个人_当前动作 3 //E8 ?? ?? ?? ?? ?? 83 ?? ?? ?? ?? ?? ?? 0F ?? ?? ?? ?? ?? ?? 8D ?? ?? ?? ?? ?? 0F ?? ?? E8 ?? ?? ?? ?? ?? 8D  +0x13+3 [[2157DE00020+104+30]]+30  读4字节

#define go_DungeonMoviePass 0x108
#define go_UiMsgStart 0x230
#define go_bag_Vehicle 0xA9F24
#define go_BSItem_ItemInfo 0x430
#define go_MarketUiSerchCheck 0x38C
#define go_AuctionDataSet 0x200
#define go_AuctionSearchState 0x660
#define go_ExchangeShopWndTabVauleCtrl 0x41C
#define go_ExchangeShopWndTabCurVaule 0x558
#define go_WelcomeChallengeMissionId 0x94
#define go_getBookRewardSendArg 0x51
#define go_BattleState 0xF2C
#define go_UnasWeeklyQuestType 0x150C
#define go_ItemGemCombineConfigValue 0x5C
#define 偏移_背包_数组大小 0x330
#define 偏移_技能_冷却 0x4AF4
#define 偏移_技能_技能点数 0xA9EF8
#define 偏移_环境_对象虚表 0x738
#define 偏移_环境_怪物血量1 0x5A8
#define 偏移_环境_怪物血量2 0x510
#define 偏移_类型_击打道具 0xEFC
#define 基址_拍卖_登记封包头 0x3B7B290
//#define 偏移_背包_数组大小 0x0
#define gb_voyageLinerList 0x1

//#define 偏移_背包_未知2遍历数组头 0xA9F0C
//
//#define 基址_工会_输入密码rdx 0x3DEE938
//
//#define 基址_工会_捐赠rdx 0x3F006D8
//
//#define  基址_工会_离开call 0x1EDF6E0
#define  g_市场最近价格 0x1E   //3B F8 7C ?? 48 83 63 ?? ?? +1A
//
//#define 交易金额call 0x162E340

#define g_M 0x4918
#define g_F6 0x4926
#define g_空格 0x4950
#define g_N 0x4919
#define g_C 0x490E
#define g_I 0x4914
#define g_G 0x4912
#define g_Q 0x491C
#define g_W 0x4920
#define g_E 0x4910
#define g_R 0x491D
#define g_Z 0x23A5
#define g_B 0x490D
#define g_V 0x2326
#define g_A 0x490C
#define g_S 0x491E
#define g_D 0x490F
#define g_F 0x4911
#define g_1 0x492E
#define g_2 0x492F
#define g_3 0x4930
#define g_4 0x4931
#define g_5 0x4932
#define g_6 0x4933
#define g_7 0x4934
#define g_8 0x4935
#define g_9 0x4936
#define g_F1 0x4921
#define g_F2 0x4922
#define g_F3 0x4923
#define g_F4 0x4924
#define g_F5 0x4925
#define g_Y 0x1D25
#define g_X 0x1D24
#define g_ESC 0x494F
#define g_ENTER 0x4947
#define g_Q 0x491C
#define g_N 0x4919
#define g_Y 0x1D25
#define g_J 0x4915
#define g_U 0x2325
#define g_1 0x492E
#define g_2 0x492F
#define g_K 0x4916

