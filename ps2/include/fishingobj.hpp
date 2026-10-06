#pragma once

#include "common.h"

#include <libvu0.h>

class CScene;
class mgCFrame;
struct CCPoly;

enum FishingMode {
    FISHING_MODE_BAIT = 1,
    FISHING_MODE_LURE = 2,
};

struct FISH_POINT {
    sceVu0FVECTOR pos;
    sceVu0FVECTOR old_pos;
    sceVu0FVECTOR velo;
};

STATIC_ASSERT(sizeof(FISH_POINT) == 0x30);

struct FISH_BIND {
    FISH_POINT *point0;
    FISH_POINT *point1;
    float rate;
    float length;
};

STATIC_ASSERT(sizeof(FISH_BIND) == 0x10);

struct FISH_FLOAT {
    FISH_POINT *point0;
    FISH_POINT *point1;
    int unk_8;
    float buoyancy;
};

STATIC_ASSERT(sizeof(FISH_FLOAT) == 0x10);

struct FISH_ROD_SEGMENT {
    float length;
    float stiffness;
    float damping;
    float unk_c;
};

STATIC_ASSERT(sizeof(FISH_ROD_SEGMENT) == 0x10);

class CFishObj {
public:
    int point_num;
    FISH_POINT point[8];
    int bind_num;
    FISH_BIND bind[18];
    u_char unk_2b4[0xC];
    int float_num;
    FISH_FLOAT float_info[16];

    void MovePoint();

    void FloatPoint(float water_level);

    void BindStep();

    void Correct(CCPoly *poly, int poly_num, float damping);
};

STATIC_ASSERT(sizeof(CFishObj) == 0x3D0);

void SetFishingMode(int mode);

int GetFishingMode();

void SetWaterLevel(float level);

float GetWaterLevel();

int ExtendLine(float length);

float GetNowLineLength();

float GetMinLineLength();

void InitRodPoint(mgCFrame *reference, mgCFrame *rod);

void GetHariPos(float *pos, float *old_pos);

void GetUkiPos(float *pos, float *old_pos);

void PullUki(float power);

void SetShowHari(int show);

int GetShowHari();

int SetLurePose(mgCFrame *lure);

int SetUkiPose(mgCFrame *uki, mgCFrame *hari);

int CastingLure(float *target);

void EndCastingLure();

int CatchLine(float *pos, float max_dist);

void SlowLineVelo(float rate);

void ResetLineVelo();

void ResetLine(float *pos);

int InitFishBattle();

int EndFishBattle();

int CheckRodActionChance(int dir, int *just);

int FishBattle(CScene *scene, CCPoly *poly_buffer, int poly_max);

void GetFishPosVelo(float *pos, float *velo);

void RodStep(CScene *scene, u_long128 *poly_buffer);

void DrawFishingLine();

void DrawFishingActionChance();

void InitLureObj(int lure_no, mgCFrame *lure);

void InitUkiObj(int no, mgCFrame *uki, mgCFrame *hari);
