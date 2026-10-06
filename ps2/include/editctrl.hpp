#pragma once

#include "common.h"

#include "dng_main.hpp"

class CPadControl;
class CScene;
struct CCPoly;

enum EditViewMode {
    EDIT_VIEW_MODE_WALK  = 0,
    EDIT_VIEW_MODE_EYE   = 1,
    EDIT_VIEW_MODE_PHOTO = 2,
};

enum EditLadderMode {
    EDIT_LADDER_MODE_NONE   = 0,
    EDIT_LADDER_MODE_BOTTOM = 1,
    EDIT_LADDER_MODE_TOP    = 2,
};

enum EditCharaMotionMode {
    EDIT_CHARA_MOTION_FREE    = 0,
    EDIT_CHARA_MOTION_LANDING = 1,
};

struct EditMoveCharaInfo {
    int           poly_num;
    CCPoly       *polys;
    u8            unk_8[8];
    MoveCheckInfo move_info;
    int           hard_landing;
    u8            unk_124[0xC];
};

STATIC_ASSERT(sizeof(EditMoveCharaInfo) == 0x130);

int EditOnGround();

int IsWalkMode();

void EditControlInit(CScene *scene);

void EditControlStatusInit(CScene *scene);

int EditControl(CScene *scene, CPadControl *pad);

char *GetFootEffName(int ground_kind);

void EditMoveChara(CScene *scene, float *velocity, EditMoveCharaInfo *info);

void EditCameraControl(CScene *scene, CPadControl *pad, float (*look_at)[4]);

void CancelEyeViewMode();

void ResetViewMode(CScene *scene);

void EditStepChara(CScene *scene);

void EditDrawShadowChara(CScene *scene);

void EditDrawChara(CScene *scene);

void EditDrawEffectChara(CScene *scene);
