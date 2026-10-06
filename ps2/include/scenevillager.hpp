#pragma once

#include "common.h"

enum SCENE_CHARA_STATUS {
    SCENE_CHARA_NO_SHADOW   = 1 << 3,
    SCENE_CHARA_HIDE        = 1 << 4,
    SCENE_CHARA_EXCLAMATION = 1 << 5,
    SCENE_CHARA_NO_LIGHTING = 1 << 6,
    SCENE_CHARA_NO_FADE     = 1 << 7,
    SCENE_CHARA_NO_DIST     = 1 << 8,
    SCENE_CHARA_NO_MODEL    = 1 << 9,
};

enum SCENE_VILLAGER_SLOT {
    SCENE_VILLAGER_SLOT_TOP       = 8,
    SCENE_VILLAGER_SLOT_NUM       = 16,
    SCENE_SUB_VILLAGER_SLOT_TOP   = 0x18,
    SCENE_SUB_VILLAGER_SLOT_NUM   = 8,
    SCENE_TALK_SLOT_END           = 0x40,
    SCENE_GAMEOBJ_SLOT_TG         = 0x78,
    SCENE_GAMEOBJ_SLOT_TG_BASE    = 0x79,
    SCENE_GAMEOBJ_SLOT_SAVEPOINT  = 0x7A,
    SCENE_GAMEOBJ_SLOT_BOOK       = 0x7B,
    SCENE_CHARA_SLOT_NUM          = 0x80,
};

enum SCENE_VILLAGER_STACK {
    SCENE_STACK_VILLAGER     = 2,
    SCENE_STACK_SUB_VILLAGER = 4,
};

enum VILLAGER_MOTION {
    VILLAGER_MOTION_NONE       = -1,
    VILLAGER_MOTION_STAND      = 0,
    VILLAGER_MOTION_WALK       = 1,
    VILLAGER_MOTION_RUN        = 2,
    VILLAGER_MOTION_TALK       = 3,
    VILLAGER_MOTION_SIT        = 4,
    VILLAGER_MOTION_CAMERA_IN  = 5,
    VILLAGER_MOTION_CAMERA     = 6,
    VILLAGER_MOTION_CAMERA_OUT = 7,
    VILLAGER_MOTION_SPECIAL    = 8,
    VILLAGER_MOTION_NUM        = 9,
};

enum GAMEOBJ_TYPE {
    GAMEOBJ_TYPE_NONE      = 0,
    GAMEOBJ_TYPE_TG_RED    = 1,
    GAMEOBJ_TYPE_TG_BLUE   = 2,
    GAMEOBJ_TYPE_SAVEPOINT = 3,
};

#define GAMEOBJ_PLACE_MAX 4

struct GAMEOBJ_PLACE {
    float pos[3];
    float rot_y;
};

STATIC_ASSERT(sizeof(GAMEOBJ_PLACE) == 0x10);

struct GAMEOBJ_INFO {
    s32           map_no;
    s32           type;
    s32           place_num;
    s32           unk_c;
    GAMEOBJ_PLACE place[GAMEOBJ_PLACE_MAX];
};

STATIC_ASSERT(sizeof(GAMEOBJ_INFO) == 0x50);

class CCharacter2;
class mgCFrame;

int GetChrFileSize(unsigned int *pack, int file_size);
int GetObjectNameList(char *names, CCharacter2 *chara, mgCFrame **frames, int max);
int GetMotionID(char *name);
void SetCharaMotion(CCharacter2 *chara, int motion_id, int mode);
