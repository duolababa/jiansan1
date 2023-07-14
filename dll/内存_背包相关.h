#pragma once
#include "pch.h"
class 背包
{
public:
    static void get_InventoryItemList(vector<Inventoryinfo_>& vsk);
    static void get_EquipList(vector<Equipinfo_>& vsk);
    static void get_UpEquipList(vector<Equipinfo_>& vsk);
    static void get_LifeToolList(vector<Equipinfo_>& vsk);
    static void get_feicangkuList(vector<Inventoryinfo_>& vsk);
    static void get_cangkuList(vector<Inventoryinfo_>& vsk);

    static Inventoryinfo_ 取公共仓库(CString name);
    static Inventoryinfo_ 取单独仓库(CString name);

    static bool 取仓call(DWORD 槽位, DWORD 是否公共仓库);
    static bool 指定位置生活工具是否已装备(DWORD 槽位);
    static Equipinfo_ get_EquipInfobyIndex(DWORD type);
    static DWORD 取金币数();
    static DWORD 取银币数();
    static DWORD 取复活币数();
    static INT64 getMoneyNumByType(int dMoneyType);
    static void 维修装备(DWORD 参_修理类型);
    static void 使用物品(DWORD 格子数);
    static void 使用任务物品(DWORD 格子数);
    static void 右键物品(DWORD 格子数);
    static void 丢弃物品call(INT64 ItemId);
    static DWORD 坐骑遍历();
    

    static void 使用物品2(DWORD 格子数);
    static void get_RecommendEquipList(vector<Inventoryinfo_>& vsk);
    static int get_PosbyItemID(DWORD itemId);
    static Inventoryinfo_ get_ItemInfobyItemID(DWORD itemId);
    static void 使用背包指定物品(CString 物品名称);
    static void 使用背包指定物品_ByResId(DWORD ResId);
    static void 装备背包指定物品_ByResId(DWORD ResId);
    static DWORD 返回指定物品数量(DWORD ResId);
    static bool 判断是否为推荐装备(INT64 ItemId);
    static void 自定装备推荐装备();
    static void CALL_穿戴装备(DWORD bagpos, DWORD SendArg);
    static void Fun_UnWearEquip(int dEquipSlot);
    static bool 背包物品处理();
    static void  点击分解颜色call();
    static void  自动入包call();
    static void SetHpItemSlot(DWORD dItemId, DWORD dTargetIndex);
    static void SetBufItemSlot(DWORD dItemId, DWORD dTargetIndex);
    static void 药品拖拽call(DWORD 位置, DWORD dItemId, DWORD dTargetIndex, DWORD 物品类型);
    static DWORD 需研磨装备序号(DWORD lv);
    static DWORD 采集数量(DWORD ID);
    static DWORD 指定类型物品数量(DWORD ID);
};

int getEquipWearArg(int dSlotIndex);