#pragma once

#include "common.h"

#include "editdata.hpp"
#include "map.hpp"
#include "menusystemdata.hpp"
#include "quest.hpp"
#include "savedatadungeon.hpp"
#include "userdata.hpp"

#define SAVE_BIT_FLAG_MAX 0x800

enum SAVE_BIT_FLAG {
    SAVE_FLAG_ROBO_BIKE_EVENT_SEEN = 0x35,
    SAVE_FLAG_ITEM_BOARD_EXPANDED  = 254,
    SAVE_FLAG_TOURNAMENT_STARTED   = 0x158,
    SAVE_FLAG_TOURNAMENT_CYCLE     = 0x1A8,
    SAVE_FLAG_EDIT_BLOCKED         = 0x208,
    SAVE_FLAG_COSTUME_UNLOCK       = 0x31F,
};

#define SAVE_SHORT_FLAG_MAX 0x80

#define SAVE_MAP_FLAG_MAX 0x100

#define SAVE_BUILD_PARTS_MAX 0x100

#define SAVE_BUILD_PARTS_NUM_MAX 9999

#define SAVE_EDIT_DATA_MAX 5

#define SAVE_TOUR_DAYS 3

#define SAVE_TOUR_CYCLE 10

#define SAVE_TOUR_COUNT_MAX 100

#define SPHIDA_PLAYER_MAX 64

#define SPHIDA_HOLE_MAX 9

#define GYORACE_DATA_MAX 64

struct SV_CONFIG_OPTION {
    s32 cursor_save;
    s32 vibration;
    s32 message_speed;
    s32 sound_mode;
    s32 fast_time;
    s32 map;
    u8  unk_18[4];
    s32 enemy_hp;
    s32 damage_off;
    s32 unk_24;
    s32 monster_name;
    s32 anger_counter;
    s32 dof_off;
    u8  caption_off;
    u8  unk_35;
    s8  eye_reverse;
    s8  unk_37;
    u8  unk_38[8];
};

STATIC_ASSERT(sizeof(SV_CONFIG_OPTION) == 0x40);

struct SAVE_TOUR_INFO {
    s32 start_day;
    s32 finish_day;
    s16 now_event;
    s8  type;
    s8  count;
    s32 base_day;
    u8  unk_10[0xC];
};

STATIC_ASSERT(sizeof(SAVE_TOUR_INFO) == 0x1C);

class CSaveData {
public:
    u32              bit_flag[SAVE_BIT_FLAG_MAX / 32];
    s16              short_flag[SAVE_SHORT_FLAG_MAX];
    CMapFlagData     map_flag[SAVE_MAP_FLAG_MAX];
    u8               unk_1200[0x800];
    s64              play_time;
    s32              game_progress;
    s32              time_stop;
    float            now_time;
    s32              day;
    s16              map_no;
    s16              sub_map_no;
    s16              prev_map_no;
    s16              prev_sub_map_no;
    s32              area_no;
    s16              build_parts_num[SAVE_BUILD_PARTS_MAX];
    CEditData        edit_data[SAVE_EDIT_DATA_MAX];
    SV_CONFIG_OPTION config;
    CSaveDataDungeon save_dungeon;
    u8               unk_1D298[8];
    CUserDataManager user_data;
    CQuestData       quest_data;
    CMonsterBook     monster_book;
    CMenuSystemData  menu_system_data;
    u8               bit_ctrl;
    u8               unk_643C9;
    u8               unk_643CA[6];
    SAVE_TOUR_INFO   tour;
    u8               unk_643EC[0x1544];

    void Initialize();

    int CheckBitFlagNo(int no);

    int SetBitFlag(int no, int on);

    int GetBitFlag(int no);

    s16 SetShortFlag(int no, s16 value);

    s16 GetShortFlag(int no);

    void SetBuildPartsNum(int parts_no, int num);

    s16 GetBuildPartsNum(int parts_no);

    s16 AddBuildPartsNum(int parts_no, int add);

    CEditData *GetEditData(int town_no);

    int GetPlaceEditPartsNum(int parts_id);

    CMapFlagData *GetMapFlag(int map_no);

    void InitBitCtrl();

    u8 SetBitCtrl(int bits);

    void ResetBitCtrl(int bits);

    int GetBitCtrl();

    int GetItem(int item_no, int num);

    void ForceBootTour(int day, int type);

    int CheckEventDay(int day);

    void CheckTourBoot(int day);

    int CheckNowTourEvent();

    int CheckNowTourType();

    s8 AddTourCountEtc(int add);

    int GetTourCountEtc();

    void FinishTour();

    SV_CONFIG_OPTION *GetConfig() {
        return &config;
    }

    CUserDataManager *GetUserDataManager() {
        return &user_data;
    }
};

STATIC_ASSERT(sizeof(CSaveData) == 0x65930);

struct SPHIDA_PLAYER_DATA {
    char name[0x14];
    u8   unk_14[4];
    s32  password_key;
    u8   unk_1C[4];
    s32  total_score;
    u8   hole_score[SPHIDA_HOLE_MAX];
    u8   unk_2D[0xB];
    s32  unk_38;
    u8   unk_3C[0x14];
};

STATIC_ASSERT(sizeof(SPHIDA_PLAYER_DATA) == 0x50);

class CSphidaData {
public:
    u8                 unk_0[0x48];
    SPHIDA_PLAYER_DATA player[SPHIDA_PLAYER_MAX];
    u16                hole_score[SPHIDA_HOLE_MAX];
    u8                 unk_145A[0x1E];
    s16                now_hole;
    u8                 unk_147A[2];
    char               player_name[0x1C];
    u8                 unk_1498[0x3B0];

    CSphidaData() {
        Initialize();
    }

    void Initialize();

    void SetHorl(int hole);

    void SetHorlScore(int score, int hole);

    int GetNowHorl();

    int GetHorlScore(int hole);

    void ClearPlayerScore(int no);

    int EnterScore();

    SPHIDA_PLAYER_DATA *GetPlayerData(int no);

    void InitPlay();
};

STATIC_ASSERT(sizeof(CSphidaData) == 0x1848);

struct GYORACE_DATA {
    CGameDataUsed fish;
    u8            unk_6C[0x34];

    int IsUsed();

    void Init();
};

STATIC_ASSERT(sizeof(GYORACE_DATA) == 0xA0);

class CGyoRaceData {
public:
    u8           unk_0[0x28];
    GYORACE_DATA data[GYORACE_DATA_MAX];
    u8           unk_2828[0x400];

    CGyoRaceData() {
        Initialize();
    }

    void Initialize();

    int SearchSpace();

    GYORACE_DATA *SearchSpaceData(int *no);

    GYORACE_DATA *GetData(int no);
};

STATIC_ASSERT(sizeof(CGyoRaceData) == 0x2C28);

class CSubGameData {
public:
    u8           incomplete;
    u8           unk_1[7];
    u32          play_enable;
    u8           unk_C[0xF4];
    CSphidaData  sphida;
    CGyoRaceData gyorace;
    u8           unk_4570[0xF00];

    CSubGameData();

    void Initialize();

    void PlayEnable(int bits, int enable);

    CSphidaData *GetSphidaData();

    CGyoRaceData *GetGyoRaceData();
};

STATIC_ASSERT(sizeof(CSubGameData) == 0x5470);

void InitSV_CONFIG_OPTION(SV_CONFIG_OPTION *option);
