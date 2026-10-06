#pragma once

#include "common.h"

class mgCMemory;

enum GLID_TYPE {
    GLID_TYPE_ROOT = 0,
    GLID_TYPE_ROOM = 1,
};

enum GLID_DIR {
    GLID_DIR_UP = 0,
    GLID_DIR_DOWN = 1,
    GLID_DIR_LEFT = 2,
    GLID_DIR_RIGHT = 3,
    GLID_DIR_NUM = 4,
};

enum DNGMAP_ROOM_FLAG {
    DNGMAP_ROOM_FLAG_ROOM = 0x1,
    DNGMAP_ROOM_FLAG_START = 0x2,
    DNGMAP_ROOM_FLAG_EXIT = 0x4,
    DNGMAP_ROOM_FLAG_BOSS = 0x8,
    DNGMAP_ROOM_FLAG_SUB = 0x10,
};

enum DNGMAP_SEAL {
    DNGMAP_SEAL_NONE = 0,
    DNGMAP_SEAL_MONICA = 1,
    DNGMAP_SEAL_MAX = 2,
};

enum DNGMAP_SUB_GAME {
    DNGMAP_SUB_GAME_SPHEDA = 0x1,
    DNGMAP_SUB_GAME_FISHING = 0x2,
};

enum DNGMAP_FAST_DESTROY_RESULT {
    DNGMAP_FAST_DESTROY_NONE = 0,
    DNGMAP_FAST_DESTROY_FIRST = 1,
    DNGMAP_FAST_DESTROY_RECORD = 2,
};

enum DNGMAP_PRACTICE_RESULT {
    DNGMAP_PRACTICE_NONE = 0,
    DNGMAP_PRACTICE_FAILED = 1,
    DNGMAP_PRACTICE_CLEAR = 2,
    DNGMAP_PRACTICE_CLEAR_AGAIN = 3,
};

enum {
    DNGMAP_DUNGEON_MAX = 6,
    DNGMAP_FLOOR_SPECIAL = 100,
    DNGMAP_SPHEDA_PRIZE_NUM = 3,
};

struct DNGMAP_ROOT_INFO {
    u8 type;
    u8 shape;
    u8 show_mark;
    u8 open;
    s8 opened;
};

STATIC_ASSERT(sizeof(DNGMAP_ROOT_INFO) == 0x5);

struct DNGMAP_ROOM_INFO {
    char *unk_0;
    char *title;
    s8    floor_id;
    s8    order;
    u8    unk_a[0x2];
    u32   flag;
    s32   fast_destroy_time;
    s8    seal;
    s8    spheda;
    s8    geostone;
    s8    fishing;
    s16   fishing_record;
    s8    practice_type;
    u8    unk_1b;
    s32   practice_param;
    u8    unk_20[0x4];
    s16   spheda_prize_item[DNGMAP_SPHEDA_PRIZE_NUM];
    s8    spheda_prize_num[DNGMAP_SPHEDA_PRIZE_NUM];
    u8    unk_2d;
    s16   link[GLID_DIR_NUM];
    s16   key_room[GLID_DIR_NUM];
    s16   offset_x;
    s16   offset_y;
    s8    tex_no;
    u8    unk_43;
    u8    unk_44;
    u8    visited;
    u8    mark;
    u8    unk_47;
    float mark_phase;
    s32   unk_4c;
};

STATIC_ASSERT(sizeof(DNGMAP_ROOM_INFO) == 0x50);

struct GLID_INFO {
    s16        type;
    s16        x;
    s16        y;
    s16        unk_6;
    s16        unk_8;
    u8         unk_a[0x2];
    GLID_INFO *link_glid[GLID_DIR_NUM];
    u8         blink;
    u8         unk_1d[0x3];
    union {
        DNGMAP_ROOM_INFO room;
        DNGMAP_ROOT_INFO root;
    };
};

STATIC_ASSERT(sizeof(GLID_INFO) == 0x70);

class CDngFloorManager {
public:
    s8         dng_no;
    u8         unk_1[0x3];
    GLID_INFO *glid_info;
    s32        glid_num;
    s16        glid_w;
    s16        glid_h;

    void Initialize();

    void AnalyzeFile(char *script, int size, mgCMemory *stack);

    void LoadDataTable(int dng_no, mgCMemory *stack);

    GLID_INFO *GetDngMapFloorGlidInfo(int floor_id);

    int IsGeoStone(int floor_id);

    int GetSphedaPrize(int floor_id, int rank, int *item, int *num);

    int GetSphedaPrize(int rank, int *item, int *num);

    int IsPlaySubGame();

    int IsSealFloor(int floor_id);

    int IsClearMostFastDestroy();

    int IsClearPractice(int check_type);

    DNGMAP_ROOM_INFO *GetDngMapFloorInfo(int floor_id);

    DNGMAP_ROOM_INFO *GetActiveFloorInfo();

    void RelationGlid();

    void CheckDrawGlidInfo();

    GLID_INFO *GetNextGlid(GLID_INFO *glid, int *dir);

    GLID_INFO *GetNextRoom(int floor_id, int dir, GLID_INFO *glid, int unused, int *found_dir);

    GLID_INFO *GetKeyNextRoom(int floor_id, int dir, GLID_INFO *glid);

    int GetDngMapNextFloorID(int floor_id, int root_type);

    char *GetFloorTitle(int floor_id);

    int GetDngMapNextRoot(int floor_id);
};

STATIC_ASSERT(sizeof(CDngFloorManager) == 0x10);

int GetCountSphedaClear();

int CheckFishingRecord(float size);
