#pragma once

#include "common.h"
#include "villagermngr.hpp"

class mgCMemory;

enum {
    VLGR_PLACE_MAX    = 0x200,
    GAME_PROGRESS_MAX = 0x100
};

enum VLGR_HOUSE_TYPE {
    VLGR_HOUSE_NONE = -1,
    VLGR_HOUSE_A    = 0,
    VLGR_HOUSE_B    = 1,
    VLGR_HOUSE_C    = 2,
    VLGR_HOUSE_D    = 3
};

struct GAME_PROGRESS_INFO {
    s16   chapter;
    s16   section;
    s32   order;
    char *name;
};
STATIC_ASSERT(sizeof(GAME_PROGRESS_INFO) == 0xC);

class CVillagerInfo {
public:
    s32   vlgr_id;
    char *model_name;
    s32   house_type;
    char *show_frames;
    char *hide_frames;
    s32   unk_14;
    s32   unk_18;

    CVillagerInfo();
};
STATIC_ASSERT(sizeof(CVillagerInfo) == 0x1C);

int vpiGetMotionID(char *name);

CVillagerPlaceInfo *GetVlgrPlaceInfo(int place_no);

CVillagerPlace *GetVlgrPlaceTable(int *num);

CVillagerInfo *GetVillagerInfo(int vlgr_id);

int GetVillagerModelName(int vlgr_id, char *name);

void LoadNPCInfo(char *script, int size, mgCMemory *stack);

void LoadPlaceInfo(char *script, int size, mgCMemory *stack);

void LoadGameInfo(mgCMemory *stack);

GAME_PROGRESS_INFO *GetGameProgressInfo(int progress);

int GetGameChapter(int progress);

int GetGameProgressNum();
