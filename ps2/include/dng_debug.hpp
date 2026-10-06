#pragma once

#include "common.h"

enum DNG_DEBUG_COMMAND {
    DNG_DEBUG_CMD_RUN_EVENT    = 0,
    DNG_DEBUG_CMD_ENEMY_LOADER = 1,
    DNG_DEBUG_CMD_DEBUG_CAMERA = 2,
    DNG_DEBUG_CMD_CHARA_MOVE   = 3,
    DNG_DEBUG_CMD_ENEMY_RESET  = 4,
    DNG_DEBUG_CMD_LOCK_ON_MODE = 5,
    DNG_DEBUG_CMD_INFORMATION  = 6,
    DNG_DEBUG_CMD_SKIP_FLOOR   = 7,
    DNG_DEBUG_CMD_SOUND_FLAG   = 8,
    DNG_DEBUG_CMD_MONSTER_TALK = 9,
    DNG_DEBUG_CMD_EFFECT_ID    = 10,
    DNG_DEBUG_CMD_EFFECT_VOL   = 11,
    DNG_DEBUG_CMD_NUM          = 12
};

struct DNG_DEBUG_INFO {
    s16   active;
    s16   cursor;
    s16   command;
    s16   event_no;
    s32   saved_pause_flag;
    s32   first_enemy_load;
    s32   sound_flag;
    s32   monster_talk;
    s32   effect_id;
    float effect_vol;
};
STATIC_ASSERT(sizeof(DNG_DEBUG_INFO) == 0x20);

extern DNG_DEBUG_INFO dbinfo;

DNG_DEBUG_INFO *dngGetDebugInfo();

void dngDebugInit();

void dngDebugStart();

void dngDebugDraw();

int dngDebugKey();

void DrawDebugWindow();

void DBGCMD_ReloadEnemy(int monster_id, int reset);
