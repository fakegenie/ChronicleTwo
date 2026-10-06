#pragma once

#include "common.h"

struct ATTACH_USED;
class CGameDataUsed;

enum USED_ITEM_TYPE {
    USED_ITEM_TYPE_NONE = 0,
    USED_ITEM_TYPE_ITEM = 1,
    USED_ITEM_TYPE_ATTACH = 2,
    USED_ITEM_TYPE_WEAPON = 3,
    USED_ITEM_TYPE_UNK_4 = 4,
    USED_ITEM_TYPE_ROBO_PART = 5,
    USED_ITEM_TYPE_FISH = 6,
    USED_ITEM_TYPE_GIFT_BOX = 7,
    USED_ITEM_TYPE_BOILED = 8,
};

enum ITEM_ATTRIBUTE {
    ITEM_ATTRIBUTE_TRUSH = 0x1,
    ITEM_ATTRIBUTE_SPECTOL_TRANS = 0x2,
};

enum ITEM_USE_FLAG {
    ITEM_USE_FLAG_ADD_STATUS_UNK_8 = 0x4000,
    ITEM_USE_FLAG_CURE_STATUS_UNK_8 = 0x8000,
    ITEM_USE_FLAG_ADD_POISON = 0x10000,
    ITEM_USE_FLAG_CURE_POISON = 0x20000,
    ITEM_USE_FLAG_ADD_STATUS_UNK_4 = 0x40000,
    ITEM_USE_FLAG_CURE_STATUS_UNK_4 = 0x80000,
    ITEM_USE_FLAG_ADD_STATUS_UNK_2 = 0x100000,
    ITEM_USE_FLAG_CURE_STATUS_UNK_2 = 0x200000,
    ITEM_USE_FLAG_ADD_POWER = 0x400000,
    ITEM_USE_FLAG_CURE_ALL = 0x800000,
    ITEM_USE_FLAG_ADD_STATUS_UNK_20 = 0x02000000,
    ITEM_USE_FLAG_CURE_STATUS_UNK_20 = 0x04000000,
    ITEM_USE_FLAG_ADD_STATUS_UNK_40 = 0x08000000,
    ITEM_USE_FLAG_CURE_STATUS_UNK_40 = 0x10000000,
};

enum ITEM_USE_TARGET_TYPE {
    ITEM_USE_TARGET_CHARA = 0,
    ITEM_USE_TARGET_ITEM = 1,
    ITEM_USE_TARGET_ROBO = 2,
    ITEM_USE_TARGET_MONSTER = 3,
    ITEM_USE_TARGET_NONE = -1,
};

struct CDataCommon {
    u8    type;
    u8    unk_1;
    s16   item_no;
    s16   list_no;
    s16   icon_no;
    s16   message_no;
    u16   max_num;
    char  file_name[16];
    u8    active_set;
    u8    unk_1d;
    s16   stack_num;
    u8    unk_20;
    u8    unk_21[3];
    u32   attribute;
    char *name;
};
STATIC_ASSERT(sizeof(CDataCommon) == 0x2C);

class CDataItem {
public:
    u32 status_flags;
    u32 use_flags;
    u16 target_flags;
    s16 value[3];

    CDataItem();
};
STATIC_ASSERT(sizeof(CDataItem) == 0x10);

class CDataAttach {
public:
    s16 status[2];
    s16 attribute[8];
    u32 special;

    CDataAttach();
};
STATIC_ASSERT(sizeof(CDataAttach) == 0x18);

class CDataWeapon {
public:
    s16 durability;
    s16 levelup_exp;
    s16 status[2];
    s16 status_max[2];
    s16 attribute[8];
    s16 attribute_max[8];
    u32 special;
    u8  unk_30[8];
    u8  unk_38;
    u8  fusion_point;
    s16 buildup_weapon[3];
    s16 buildup_monster[3];
    u8  pallet_color;
    u8  unk_47;
    u8  attack_type;
    u8  model_no;
    u8  unk_4a[2];

    CDataWeapon();
};
STATIC_ASSERT(sizeof(CDataWeapon) == 0x4C);

class CDataRoboPart {
public:
    s16 use_capacity;
    s16 unk_2;
    s16 unk_4;
    s16 unk_6;
    s16 unk_8;
    s16 unk_a;
    s16 unk_c[8];
    s16 unk_1c;
    s16 info_type_d;
    s16 info_type_e;
    u8  offset_no;
    u8  unk_23;

    int GetOffsetNo();
};
STATIC_ASSERT(sizeof(CDataRoboPart) == 0x24);

class CDataBreedFish {
public:
    float size;
    s16   unk_4;
    s16   unk_6;
    s16   unk_8;
    s16   unk_a;
    s16   unk_c;
    s16   unk_e;
    s16   unk_10;
    s16   unk_12;

    CDataBreedFish();
};
STATIC_ASSERT(sizeof(CDataBreedFish) == 0x14);

struct USEITEM_EFFECT {
    u32 use_flags;
    u32 status_flags;
    u16 target_flags;
    u8  unk_a[2];
    int value[4];
};

class CItemUseTarget {
public:
    int type;
    union {
        void          *data;
        CGameDataUsed *item;
    } target;

    CItemUseTarget() { type = ITEM_USE_TARGET_NONE; }

    void SetPtr(int type, void *target);
};
STATIC_ASSERT(sizeof(CItemUseTarget) == 0x8);

class CGameData {
public:
    int             unk_0;
    CDataCommon    *common_data;
    CDataItem      *item_data;
    CDataWeapon    *weapon_data;
    s16            *guard_data;
    CDataAttach    *attach_data;
    CDataRoboPart  *robo_data;
    CDataBreedFish *fish_data;
    u16             max_item_no;
    u16             common_num;
    u16             item_num;
    u16             weapon_num;
    u16             guard_num;
    u16             attach_num;
    u16             robo_num;
    u16             fish_num;

    void Initialize();

    int LoadData();

    int LoadItemSystemMes(int language);

    void InitItemMes(int clear_name, int unused);

    CDataCommon *GetCommonData(int item_no);

    CDataWeapon *GetWeaponData(int item_no);

    CDataItem *GetItemData(int item_no);

    CDataAttach *GetAttachData(int item_no);

    CDataRoboPart *GetRoboData(int item_no);

    CDataBreedFish *GetFishData(int item_no);

    s16 *GetGuardData(int item_no);

    int GetDataType(int item_no);

    s16 GetDataTypeStartListNo(int type);
};
STATIC_ASSERT(sizeof(CGameData) == 0x30);

extern s8 etcitem_spectol_table[0x352];

extern CDataWeapon *SpiWeaponPt;

extern CDataItem *SpiItemPt;

extern CDataAttach *SpiAttach;

extern CDataRoboPart *SpiRoboPart;

extern CDataBreedFish *SpiFish;

extern CGameData GameItemDataManage;

CGameData *GetGameDataPt();

CDataCommon *GetCommonItemData(int item_no);

CDataItem *GetItemInfoData(int item_no);

CDataWeapon *GetWeaponInfoData(int item_no);

CDataRoboPart *GetRoboPartInfoData(int item_no);

CDataBreedFish *GetBreedFishInfoData(int item_no);

char *GetItemFileName(int item_no, int with_extension);

char *GetItemFilePath(int item_no, int alternate);

int GetItemDataType(int item_no);

u32 GetItemDataAttribute(int item_no);

int ConvertUsedItemType(int type);

int GetItemMessageNo(int item_no, int message);

char *GetItemMessage(int item_no);

int GetItemIconNo(int item_no);

void SetItemSpectolPoint(int item_no, ATTACH_USED *attach, int num);

int GetMenuCommandMsg(int item_no, int *message_list);

int CheckItemEquip(int chara, int item_no);

int SearchItemByName(char *name);

int GetRidePodCore(int index);

int GetUsedItemAfterEffect(int item_no, USEITEM_EFFECT *effect);

int ItemCmdMsgSet(int item_no, int *messages);
