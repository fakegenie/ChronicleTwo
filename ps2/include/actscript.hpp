#pragma once

#include "common.h"

class CActionChara;
class CRunScript;
class CScene;
class mgCCameraFollow;
class mgCMemory;
struct RUN_SCRIPT_ENV;

struct ACTION_INFO {
    CActionChara    *chara;
    mgCCameraFollow *camera;
    RUN_SCRIPT_ENV  *env;
    u8               unk_c[4];
};

STATIC_ASSERT(sizeof(ACTION_INFO) == 0x10);

extern CScene *nowScene__2;

extern CScene *nowScene__2;

extern ACTION_INFO action_info;

int SetActionScript(CRunScript *script, char *program, mgCMemory *memory);

void SetActionExtendTable();
