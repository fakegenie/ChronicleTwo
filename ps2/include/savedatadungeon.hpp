#pragma once

#include "common.h"

enum {
    SAVE_DUNGEON_NUM = 7,
    SAVE_DUNGEON_FLOOR_NUM = 162
};

enum DNG_FLOOR_FLAG {
    DNG_FLOOR_FLAG_OPEN = 0x1,
    DNG_FLOOR_FLAG_UNK_2 = 0x2,
    DNG_FLOOR_FLAG_PRACTICE_CLEAR = 0x8,
    DNG_FLOOR_FLAG_FAST_DESTROY_CLEAR = 0x10,
    DNG_FLOOR_FLAG_FISHING_CLEAR = 0x20,
    DNG_FLOOR_FLAG_SPHEDA_CLEAR = 0x80,
    DNG_FLOOR_FLAG_GEOSTONE_FOUND = 0x100,
    DNG_FLOOR_FLAG_GEOSTONE_READ = 0x200,
    DNG_FLOOR_FLAG_SEAL_CLEAR = 0x400
};

struct DNG_FLOOR_SAVE {
    s32 unk_0;
    s32 fast_destroy_time;
    u16 unk_8;
    u8  unk_a;
    u8  unk_b;
    u16 spheda_clear;
    u16 flag;
    u16 kill_count;
    u16 visit_count;
};

STATIC_ASSERT(sizeof(DNG_FLOOR_SAVE) == 0x14);

class CSaveDataDungeon {
public:
    s32 stage_id;
    s32 floor_id[SAVE_DUNGEON_NUM];
    s32 prev_floor_id[SAVE_DUNGEON_NUM];
    DNG_FLOOR_SAVE floor_info[SAVE_DUNGEON_FLOOR_NUM];

    DNG_FLOOR_SAVE *GetFloorInfoPtr(int stage, int floor);

    void Initialize();

    void SetFloorID(int floor);
};

STATIC_ASSERT(sizeof(CSaveDataDungeon) == 0xCE4);
