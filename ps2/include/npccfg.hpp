#pragma once

#include "common.h"

enum NpcModelPathType {
    NPC_MODEL_PATH_CHARA       = 0,
    NPC_MODEL_PATH_INFO        = 1,
    NPC_MODEL_PATH_EVENT_TRAIN = 2,
    NPC_MODEL_PATH_MENU        = 3,
};

struct NPC_BASE_DATA {
    s16  chara_no;
    s8   debug_flag;
    char name[0x1C];
    char model[0x10];
    s8   max_npc_point;
    s8   ability_num;
    s8   unk_31;
    u8   ability_cost[4];
};
STATIC_ASSERT(sizeof(NPC_BASE_DATA) == 0x36);

void LoadNPCCfg();

int GetPartyCharaMessage(int chara_no, int type, int event);

char *GetNPCModelName(int chara_no);

char *GetNPCName(int chara_no);

char *GetPartyCharaModelName(int chara_no, int type);

NPC_BASE_DATA *GetPartyNPCData(int chara_no);
