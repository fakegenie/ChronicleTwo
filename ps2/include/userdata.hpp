#pragma once

#include "common.h"
#include "gamedata.hpp"

class CBattleCharaInfo;
class CFishingTournament;
class CUserDataManager;
struct BASE_MONSTER_TBL;

enum USER_CHARA {
    USER_CHARA_MAX     = 0,
    USER_CHARA_MONICA  = 1,
    USER_CHARA_ROBO    = 2,
    USER_CHARA_MONSTER = 3,
    USER_CHARA_NUM     = 4,
};

enum BATTLE_CHARA_TYPE {
    BATTLE_CHARA_HUMAN   = 0,
    BATTLE_CHARA_ROBO    = 1,
    BATTLE_CHARA_MONSTER = 2,
};

enum CHARA_STATUS_ATTR {
    CHARA_STATUS_POISON = 0x01,
    CHARA_STATUS_UNK_2  = 0x02,
    CHARA_STATUS_UNK_4  = 0x04,
    CHARA_STATUS_UNK_8  = 0x08,
    CHARA_STATUS_POWER  = 0x10,
    CHARA_STATUS_UNK_20 = 0x20,
    CHARA_STATUS_UNK_40 = 0x40,
    CHARA_STATUS_ALL    = 0x7F,
};

enum BREEDFISH_FLAGS {
    BREEDFISH_FLAG_ELECTRIC = 0x2,
};

enum SPECTOL_TYPE {
    SPECTOL_TYPE_NONE         = 0,
    SPECTOL_TYPE_WEAPON       = 1,
    SPECTOL_TYPE_ATTACH       = 2,
    SPECTOL_TYPE_WEAPON_LOW   = 3,
    SPECTOL_TYPE_ITEM         = 4,
};

class COMMON_GAGE {
public:
    float max;
    float now;

    int CheckFill();

    float GetRate();

    void SetFillRate(float rate);

    void AddPoint(float point);

    void AddRate(float rate);
};
STATIC_ASSERT(sizeof(COMMON_GAGE) == 0x8);

struct ITEM_USED {
    s16 num;
    s16 unk_2;
    u8  unk_4[0x58];
};

struct ATTACH_USED {
    u8   spectol_type;
    u8   spectol_value;
    s16  status[2];
    s16  attribute[8];
    s16  spectol_item_no;
    s16  level;
    u8   unk_1a[2];
    u32  special;
    char name[0x1A];
    s16  num;
    u8   unk_3c[0x20];
};

struct WEAPON_USED {
    COMMON_GAGE whp;
    COMMON_GAGE abs;
    s16         level;
    s16         status[2];
    s16         attribute[8];
    s16         unk_26;
    u32         special;
    s16         fusion_point;
    s16         unk_2e;
    s16         unk_30;
    u8          unk_32;
    char        name[0x20];
    u8          unk_53[9];
};

struct ROBOPART_USED {
    COMMON_GAGE gage0;
    COMMON_GAGE gage1;
    s16         status[10];
    s16         defence;
    s16         unk_26;
    u8          unk_28[4];
    char        name[0x20];
    u8          unk_4c[0x10];
};

struct BREEDFISH_USED {
    char  name[0x15];
    u8    sex;
    u8    unk_16;
    u8    unk_17;
    u16   size;
    u16   weight;
    int   unk_1c;
    int   hp;
    s16   fatigue;
    u16   param[5];
    u16   timer;
    u8    unk_32[3];
    s8    unk_35;
    u16   unk_36;
    u16   flags;
    u8    unk_3a;
    s8    grow_count;
    u8    unk_3c;
    u8    unk_3d;
    u8    unk_3e[2];
    int   tank_day;
    float tank_hour;
    u8    unk_48[0x14];
};

struct GIFTBOX_USED {
    s16 item_no[3];
    u8  unk_6[0x56];
};

struct BOILED_USED {
    s16  base_item_no;
    char name[0x16];
    u16  value;
    u8   unk_1a[0x42];
};

class CGameDataUsed {
public:
    s16 used_type;
    s16 item_no;
    s8  item_type;
    u8  rename_flag;
    u8  unk_6[0xA];
    union {
        ITEM_USED      item;
        ATTACH_USED    attach;
        WEAPON_USED    weapon;
        ROBOPART_USED  robopart;
        BREEDFISH_USED fish;
        GIFTBOX_USED   giftbox;
        BOILED_USED    boiled;
    } data;

    CGameDataUsed();

    void Init();

    int CheckTypeEnableStack();

    char *GetDataPath();

    int IsWhoEquip();

int GetLevel();

int GetPalletColor();

int GetSpectolNo();

    int CheckStackRemain();

int GetNum();

    int GetActiveSetNum();

    int AddNum(int num, int clear_empty);

int GetUseCapacity();

    int AddFishHp(int hp);

    int Boiled();

    int IsActiveSet();

    void SetName(char *name);

    char *GetName(int mode);

    void TransToPassword(char *password, int length);

    void TransToData(char *password, int length);

    int DeleteNum(int num);

int RemainFusion();

int AddFusionPoint(int point);

    int GetEffectReadType(char **effect, char **sound, int *power);

    void GetMsgAddInfo(char **name, char **sub_name, int *value);

    float GetWHp(int *whp);

    int IsRepair();

    int Repair(int point);

    int GetEnableRepairItemNo();

    int IsEnableUseRepair(int item_no);

int GetRoboInfoType();

    void GetRoboJointName(char *name);

    void GetRoboSoundFileName(char *name);

    int IsBroken();

    int IsLevelUp();

    void LevelUp();

    int IsTrush();

    int IsSpectolTrans();

    void ToSpectolTrans(CGameDataUsed *attach, int num);

    void GetStatusParam(short *status);

    void GetStatusParam(short *status, float time);

    int IsBuildUp(int *num, int *weapon_no, int *enable);

    int IsFishingRod();

    int GetActiveElem();

int GetAttackType();

    int GetModelNo();

    void CheckParamLimmit();

    void TimeCheck(int time);

    int GetGiftBoxItemNum();

    int SetGiftBoxItem(int item_no, int index);

    int GetGiftBoxItemNo(int index);

    int GetGiftBoxSameItemNum(int item_no);

    void CopyGameData(CGameDataUsed *src);

    int CopyDataWeapon(int item_no);

    int CopyDataAttach(int item_no);

    int CopyDataItem(int item_no);

    int CopyDataFish(int item_no);

    int CopyDataGiftBox(int item_no);

    int CopyDataItem(CGameDataUsed *src);

    int CopyDataRoboPart(int item_no);
};
STATIC_ASSERT(sizeof(CGameDataUsed) == 0x6C);

struct CHARA_DATA {
    COMMON_GAGE   hp;
    u16           status_attr;
    s16           defence;
    s16           status_time[4];
    u8            unk_14[0x17];
    u8            unk_2b;
    CGameDataUsed active_item[3];
    CGameDataUsed equip[5];
};
STATIC_ASSERT(sizeof(CHARA_DATA) == 0x38C);

struct ROBO_DATA {
    u8            unk_0[2];
    char          name[0x1A];
    s8            voice_unit;
    s8            voice_flag;
    u8            unk_1e[2];
    COMMON_GAGE   hp;
    COMMON_GAGE   abs;
    CGameDataUsed parts[4];
    s16           status_time[3];
    u8            unk_1e6[2];
    u16           shield_kit_num;
    u8            unk_1ea[0x36];

    float AddPoint(float point);

    int GetDefenceVol();
};
STATIC_ASSERT(sizeof(ROBO_DATA) == 0x220);

struct MOS_HENGE_PARAM {
    s16 monster_id;
    s16 attack;
    s16 defence;
    u8  unk_6[0x16];
};
STATIC_ASSERT(sizeof(MOS_HENGE_PARAM) == 0x1C);

class MOS_CHANGE_PARAM {
public:
    s16         no;
    s16         level;
    s16         class_level;
    s16         progress;
    s16         monster_id;
    u8          enable;
    u8          unk_b;
    COMMON_GAGE hp;
    COMMON_GAGE abs;
    u8          unk_1c[0x20];
    s16         status_time_1;
    s16         status_time_10;
    u8          unk_40[0x7C];

    int GetAttackVol(int monster_id);

    int GetDefenceVol(int monster_id);

    int CheckClassChange();

    int GetDegreeLevel();

    int LevelUp();
};
STATIC_ASSERT(sizeof(MOS_CHANGE_PARAM) == 0xBC);

class CMonsterBox {
public:
    MOS_CHANGE_PARAM monster[64];

    void Initialize();

    MOS_CHANGE_PARAM *GetMonsterBajjiData(int no);

    MOS_CHANGE_PARAM *GetMonsterBajjiDataByMonsterID(int monster_id);

    void EnableChange(int no);

    int IsChange(int no);

    void AllCure();
};
STATIC_ASSERT(sizeof(CMonsterBox) == 0x2F00);

class CFishAquarium {
public:
    u16           unk_0;
    s16           unk_2;
    CGameDataUsed fish_tank[6];
    CGameDataUsed sub_tank[4];
    CGameDataUsed breed_tank[2];
    u8            unk_514[4];
    u64           unk_518;
    s64           last_time;
    int           last_day;
    float         last_hour;

    CFishAquarium() { Initialize(); }

    void Initialize();

    CGameDataUsed *GetAquariumFishTop(int tank);

    int SearchAqua1NotUsed(int tank);

    void FishIntoAquarium(int tank, int index, CGameDataUsed *fish);

    int GetAquariumFishNum(int tank);

    int CheckHaigouTankSex(CGameDataUsed *fish);

    void RefreshParam();
};
STATIC_ASSERT(sizeof(CFishAquarium) == 0x530);

struct FISH_RECORD {
    float size;
    float prev_size;
    float weight;
    float prev_weight;
    int   num;
    u8    unk_14[0xC];
};
STATIC_ASSERT(sizeof(FISH_RECORD) == 0x20);

class CFishingRecord {
public:
    u8          unk_0[0x40];
    FISH_RECORD record[24];

    CFishingRecord();

    FISH_RECORD *GetFishRecord(int item_no);

    int CheckRecordFish(int item_no, float size, float weight);
};
STATIC_ASSERT(sizeof(CFishingRecord) == 0x340);

struct FISH_TOURNAMENT_ENTRY {
    s16 item_no;
    s16 size;
    s16 weight;
    s16 unk_6;
};
STATIC_ASSERT(sizeof(FISH_TOURNAMENT_ENTRY) == 0x8);

class CFishingTournament {
public:
    u8                    unk_0[4];
    s16                   rank;
    u8                    unk_6[0x1A];
    FISH_TOURNAMENT_ENTRY entry[10];

    CFishingTournament() { Initialize(); }

    void Initialize();

    void ResetRecord();

    int EntryFish(int item_no, int size, int weight);

    int EntryRemain();

    FISH_TOURNAMENT_ENTRY *GetRecord(int index);

    void SetRank(int rank);

    void SortRecord();

    int CalcTopWeight();
};
STATIC_ASSERT(sizeof(CFishingTournament) == 0x70);

struct PARTY_CHARA_INFO {
    s16 chara_no;
    u16 status;
    s16 point;
    u8  unk_6[6];
};
STATIC_ASSERT(sizeof(PARTY_CHARA_INFO) == 0xC);

struct USER_PICTURE_INFO {
    u8    used;
    u8    is_new;
    short map_no;
    short npc_no;
    short monster_no;
    short unk_8;
    short neta_id;
    u8    unk_c[8];
    char *image;
};
STATIC_ASSERT(sizeof(USER_PICTURE_INFO) == 0x18);

struct INVENT_CREATED_ITEM {
    short item_id;
    short unk_2;
};
STATIC_ASSERT(sizeof(INVENT_CREATED_ITEM) == 0x4);

struct SCOOP_INFO {
    s8 known;
    s8 obtained;
    u8 unk_2[2];
};
STATIC_ASSERT(sizeof(SCOOP_INFO) == 0x4);

class CScoopDataManager {
public:
    SCOOP_INFO info[0x80];

    SCOOP_INFO *GetScoopInfo(int scoop_id);

    void SetViewFlag(int scoop_id, int flag);

    int KnowScoop();

    int CheckScoop();

    int GetScoopTotal(int *total);
};

class CInventUserData {
public:
    int                 shutter_num;
    int                 level;
    short               neta_id[0x200];
    USER_PICTURE_INFO   photo[30];
    INVENT_CREATED_ITEM created_item[0x100];
    CScoopDataManager   scoop;
    u8                  unk_cd8[0x88];
    char                photo_work[30][0x2000];
    u8                  unk_3cd60[0x100];

    CScoopDataManager *GetScoopData() {
        return &scoop;
    }

    CInventUserData() { Initialize(); }

    void Initialize();

    void ResetAddress();

    void PhotoCheckEnd();

    USER_PICTURE_INFO *GetPhotoInfo(int index);

    char *GetPhototWorkAdr();

    USER_PICTURE_INFO *IsPhotoSpace(int *index);

    void DeletePhotoData(int index);

    int CheckNetaFlag(int neta_id);

    int GetNetaID(int index);

    void SetNetaFlag(int neta_id);

    int CheckNetaFlagHavePhoto(int neta_id);

    int CountNeta();

    int CountScoop();

    int AddShutterNum(int add);

    int GetNowHavePictureNum();

    int GetPictureNum(int *num);

    int CalcPhotoExp();

    int LevelCheck(USER_PICTURE_INFO *photo);

    int GetLevel();

    void SetCreateItemFlag(int index, int item_id);

    int GetCreateItemID(int index);

    int IsAlreadyCreatedItem(int item_id);

    int GetHatsumeiNum();
};
STATIC_ASSERT(sizeof(CInventUserData) == 0x3CE60);

class CUserDataManager {
public:
    CGameDataUsed      used_data[150];
    CHARA_DATA         chara_data[2];
    ROBO_DATA          robo_data;
    CGameDataUsed      esa[2];
    CFishAquarium      aquarium;
    u8                 unk_4e88[0x28];
    CMonsterBox        monster_box;
    PARTY_CHARA_INFO   party_chara[32];
    CInventUserData    invent_data;
    u16                party_member;
    u16                chara_change;
    u8                 chara_change_mask;
    u8                 unk_44d95;
    s16                active_chr_no;
    s16                monster_id;
    u8                 unk_44d9a[2];
    int                money;
    s16                yarikomi_medal;
    u8                 unk_44da2[0x1E];
    s16                special_item_bought;
    u8                 unk_44dc2[6];
    u64                unk_44dc8;
    s16                photo_subject[0x200];
    u64                unk_451d0;
    s64                last_refresh_time;
    int                npc_refresh_day;
    float              npc_refresh_hour;
    CFishingTournament fish_tournament;
    CFishingRecord     fish_record;
    unsigned long      costume_bit;
    u8                 unk_455a0[0x200];

    CInventUserData *GetInventUserData() {
        return &invent_data;
    }

    CUserDataManager();

    void Initialize();

    void RefreshParam();

    CGameDataUsed *GetUsedDataPtr(int index);

    CHARA_DATA *GetCharaDataPtr(int chara);

    COMMON_GAGE *GetCharaHpGage(int chara);

    int AddHp(int chara, int hp);

    float GetHp(int chara);

    float AddHp_Rate(int chara, float rate);

    COMMON_GAGE *GetWHpGage(int chara, int weapon);

    COMMON_GAGE *GetAbsGage(int chara, int weapon);

    int AddWhp(int chara, int weapon, int whp);

    int GetWhp(int chara, int weapon, int *max);

    int AddAbs(int chara, int weapon, int abs);

    int GetAbs(int chara, int weapon, int *max);

    void JoinPartyMember(int chara);

    void LeavePartyMember(int chara);

    int GetNowPartyMember();

    void EnableCharaChange(int chara);

    void DisableCharaChange(int chara);

    int CheckEnableCharaChange(int chara, int *reason);

    int CheckQuickChange(int chara, int *reason);

    void EnableCharaChangeMask(int chara);

    void DisableCharaChangeMask(int chara);

    void InitCharaChangeMask();

    u32 GetEnableCharaChangeFlag();

    u16 *GetCharaStatusAttirbutePtr(int chara);

    int SetCharaStatusAttirbute(int chara, unsigned int attr, int clear);

    int SetCharaStatusAttirbuteVol(int chara, unsigned int attr, int time);

    int GetCharaStatusAttirbute(int chara);

    MOS_CHANGE_PARAM *GetMonsterBajjiDataPtr(int no);

    MOS_CHANGE_PARAM *GetMonsterBajjiDataPtrMosId(int monster_id);

    int GetItemBoardOverNum();

    int GetItemBoardMaxNum(int with_over);

    void SetActiveChrNo(int chara);

    s16 GetActiveChrNo() {
        return active_chr_no;
    }

    void SetRoboName(char *name);

    char *GetRoboName();

    char *GetRoboNameDefault();

    void SetVoiceUnit(int fitted);

    s8 CheckVoiceUnit();

    void SetRoboVoiceFlag(int on);

    int CheckRoboVoiceFlag();

    float AddRoboAbs(float abs);

    float GetRoboAbs();

    int CheckCapacity();

    int CheckRobotCore();

    int GetDefenceVol(int chara);

    void JoinPartyChara(int chara_no, int status, int unused);

    void SetPartyCharaStatus(int chara_no, int status);

    int GetPartyCharaStatus(int chara_no);

    int NowPartyCharaID();

    void LeaveHouse(int chara_no);

    PARTY_CHARA_INFO *GetPartyCharaInfo(int chara_no);

    int UseNpcAbility(int chara_no, int ability, int use);

    void AllWeaponRepair();

    void RefreshNPCStatus(int unused);

    int GetFishingRodNo();

    int NowFishingStyle();

    CGameDataUsed *GetActiveEsa();

    CGameDataUsed *GetActiveEsa(int rod_no);

    int GetFishBait();

    void DeleteBait();

    int GetFishInAquarium(int item_no, float size, float weight);

    int CheckFishRecordUpdate(int item_no, float size, float weight);

    void GetFishRecord(int item_no, float *size, float *weight);

    void GetRodStatus(int *status);

    int AddFp(int point);

    int SetChrEquip(int chara, CGameDataUsed *item);

    int SetChrEquip(int chara, int item_no);

    int SetChrEquipDirect(int chara, int item_no);

    CGameDataUsed *SearchEquip(int chara, int item_no);

    char *GetCharaEquipDataPath(int chara, int slot);

    int AddFusionPoint(int chara, int weapon, int point);

    int SearchSpaceUsedData();

    int SearchSpaceUsedData(int item_no);

    CGameDataUsed *SearchSpaceUsedDataPtr();

    CGameDataUsed *SearchSpaceUsedDataPtr(int item_no);

    int SearchActiveItemTableSpace(int chara, int item_no);

    CGameDataUsed *SearchItemOnItemBrd(int item_no, int with_over);

    int GetNumStackOverBoard();

    CGameDataUsed *SearchAllHaveItem(int item_no);

    int FishInAquarium(CGameDataUsed *fish, int tank);

    int CheckElectricFish();

    int GetNumSameItem(int item_no);

    s16 AddYarikomiMedal(int num);

    int GetYarikomiMedal();

    int GetItem(int item_no, int num);

    int GetItemNotOver(int item_no, int num);

    int GetOverItem(int item_no, int num);

    int CheckItemLimmitOver();

    int DeleteItem(int item_no, int num);

    int CopyGameData(CGameDataUsed *place, int item_no);

    int AddMoney(int money);

    void SetCostumeBit(unsigned long bit);

    unsigned long GetCostumeBit();

    void GetCostume(int item_no);

    int CountFish();
};
STATIC_ASSERT(sizeof(CUserDataManager) == 0x457A0);

struct BATTLE_WEAPON_PARAM {
    s16 status[10];
    u32 special;
    s16 pallet_no;
    u8  unk_1a[2];
};
STATIC_ASSERT(sizeof(BATTLE_WEAPON_PARAM) == 0x1C);

class CBattleCharaInfo {
public:
    s16                 chr_no;
    s16                 unk_2;
    s16                 now_npc;
    s16                 chara_type;
    void               *chara_data;
    float               robo_hp_drain;
    float               monster_hp_drain;
    s16                 regen_count;
    s16                 poison_count;
    s16                 magic_sword_elem;
    s16                 magic_sword_num;
    s16                 magic_sword_pow[7];
    u8                  unk_2a[2];
    CGameDataUsed      *active_item;
    CGameDataUsed      *equip;
    BATTLE_WEAPON_PARAM weapon_param[2];
    s16                 defence;
    u8                  unk_6e[6];
    COMMON_GAGE        *hp;
    float               hp_change_frames;
    float               hp_change_step;
    float               unk_80;
    float               disp_hp;
    float               unk_88;
    float               prev_hp;

    CBattleCharaInfo() { Initialize(); }

    void Initialize();

    CGameDataUsed *GetEquipTablePtr(int slot);

    void SetChrNo(int chara);

    int GetMonsterID();

    int GetNowNPC();

    int UseNPCPoint(int unused);

    CGameDataUsed *GetActiveItemInfo(int index);

    int UseActiveItem(CGameDataUsed *item);

    u32 GetSpecialStatus(int weapon);

    s16 GetPalletNo(int weapon);

    void RefreshParamater();

    COMMON_GAGE *GetNowAccessWHp(int weapon);

    COMMON_GAGE *GetNowAccessAbs(int weapon);

    float AddWhp(int weapon, float whp);

    void GetNowWhp(int weapon, int *whp);

    int GetWhpNowVol(int weapon);

    void SetMagicSwordPow(int elem, int pow);

    int GetMagicSwordElem();

    int GetMagicSwordPow();

    int GetMagicSwordCounterNow();

    int GetMagicSwordCounterMax();

    void ClearMagicSwordPow();

    float AddAbs(int weapon, float abs, int *level_up);

    int AddAbsRate(int weapon, float rate, int *level_up);

    void GetNowAbs(int weapon, int *abs);

    int LevelUpWeapon(CGameDataUsed *weapon);

    s16 GetDefenceVol();

    float AddHp_Point(float hp, float frames);

    float AddHp_Rate(float rate, int mode, float frames);

    void SetHpRate(float rate);

    int GetMaxHp_i();

    int GetNowHp_i();

    int SetAttr(int attr, int clear);

    int SetAttrVol(int attr, int time);

    int GetAttr();

    void ForceSet();

    int StatusParamStep(int *damage);

    void Step();
};
STATIC_ASSERT(sizeof(CBattleCharaInfo) == 0x90);

extern s8 aquarium_fish_maxtbl[3];

extern CBattleCharaInfo BattleParamater;

CUserDataManager *GetUserDataMan();

CFishingTournament *GetFishTournament();

CFishAquarium *GetAquariumData();

float GetCommonGageRate(COMMON_GAGE *gage);

int CalcBreedFishParam(BREEDFISH_USED *fish);

void SetFishingGamePreEquip(CGameDataUsed *weapon);

void ReEquipFishingGameWeapon();

int CheckFishingWeapon(CGameDataUsed *weapon);

void GameDataSwap(CGameDataUsed *a, CGameDataUsed *b, int check_fishing);

int CheckNowRoboUseCapacity(ROBO_DATA *robo, int *capacity);

int GetMainCharaModelName(int chara, char *name, int alternate);

int GetShiledKitLimmit(int item_no);

BASE_MONSTER_TBL *GetMonsterBaseInfo(int monster_id);

MOS_HENGE_PARAM *GetMonsterHengeParam(int monster_id);

void SetEnvUserDataMan(int dungeon);

void GetCharaDefaultWeapon(int chara, int *item_no);

void LanguageEquipChange();

void CheckEquipChange(int chara);

CBattleCharaInfo *GetBattleCharaInfo();

void ConvertItemAttrToCharaAttr(int attr, int *add, int *cure);

int CheckBadStatus(int attr);

unsigned int CheckWeaponAttribute(unsigned int weapon_attr, unsigned int attr);

int CheckBuildUpMonsterCondition(CDataWeapon *weapon);

int KillMonsterCount(int monster_id, int mode);

int SearchEquipType(int chara, int slot);

int IsItemtypeWhoisEquip(int item_no, int *slot);

int IsCheckParty(int chara);

char *GetAquariumFish0(int index);

int GetUserItemHaveNum(int item_no);

int CheckItemOver();

int CheckItemLimmitOver();

int CheckGetItemLimmitOver(int item_no, int num);

int CheckGetItemRemainNum(int item_no);

void CheckItemDngKey();

void PlayerPartyCure();

void UserDataRefresh();

void DeleteErekiFish();

int GetNowBagMax(int with_over);

void LeaveMonicaItemCheck();

void AquaFishFatigueClear();

void DebugGetItem(CUserDataManager *user_data, int mode);

int GetRandomCircleTrapID(int kind);

int SetRandamCircleStatus(int trap, float &value);
