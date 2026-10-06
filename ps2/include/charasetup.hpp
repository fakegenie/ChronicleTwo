#pragma once

#include "common.h"

class mgCMemory;
class CScene;
class CUserDataManager;

enum ROBO_MODEL_SLOT {
    ROBO_MODEL_LEG   = 0,
    ROBO_MODEL_ARM   = 1,
    ROBO_MODEL_BODY  = 2,
    ROBO_MODEL_MINTS = 3,
    ROBO_MODEL_BPACK = 4,
    ROBO_MODEL_NUM   = 5,
};

struct ROBO_INFO_BODY {
    char body_file[13];
    char arm_name[24];
};

STATIC_ASSERT(sizeof(ROBO_INFO_BODY) == 0x25);

struct ROBO_INFO_DATA {
    char *model_name[ROBO_MODEL_NUM];
    char *hat_file;
    char *arm_name;
    s32   move_type;
    s32   attack_type;
};

STATIC_ASSERT(sizeof(ROBO_INFO_DATA) == 0x24);

extern ROBO_INFO_BODY robo_info_body[11];

extern ROBO_INFO_DATA robo_dat;

void GetCharacterSnd(CUserDataManager *user_data, int chara_no, char *path);

int SetupMainUnit(u_long128 *read_buffer, mgCMemory *memory, mgCMemory *stacks, int image_block, CScene *scene, CUserDataManager *user_data, int chara_type, int edit_mode);

int GetCharaMemAllocSize();

int GetCharaMemAllocPtr(mgCMemory *memory, mgCMemory *stacks, int chara_type, int edit_mode);

void SetupUnitMan(CScene *scene, CUserDataManager *user_data, int chara_type, ROBO_INFO_DATA *robo_info);

ROBO_INFO_DATA *GetRoboPartsInfo(CUserDataManager *user_data);
