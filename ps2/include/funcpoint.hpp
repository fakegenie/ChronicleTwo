#pragma once

#include "common.h"

#include <libvu0.h>

#include "mapload.hpp"
#include "mg_tanime.hpp"

class mgCFrame;
class mgCMemory;
class mgCTexture;
class CFireRaster;
class CMapParts;
class CMapPiece;

enum FUNC_POINT_MNGR_FLAG {
    FUNC_POINT_MNGR_ANY = 0x1,
    FUNC_POINT_MNGR_BURN = 0x2,
    FUNC_POINT_MNGR_FIRE = 0x4,
    FUNC_POINT_MNGR_FLARE = 0x8,
    FUNC_POINT_MNGR_EFFECT = 0x10,
    FUNC_POINT_MNGR_PLIGHT = 0x20,
    FUNC_POINT_MNGR_LIGHT = 0x40,
    FUNC_POINT_MNGR_SOUND = 0x80,
    FUNC_POINT_MNGR_EVENT = 0x100,
};

enum OBJ_ANIME_PARAM {
    OBJ_ANIME_PARAM_POSITION = 1,
    OBJ_ANIME_PARAM_ROTATION = 2,
    OBJ_ANIME_PARAM_SCALE = 3,
    OBJ_ANIME_PARAM_COLOR = 4,
    OBJ_ANIME_PARAM_ALPHA = 5,
};

enum OBJ_ANIME_MODE {
    OBJ_ANIME_MODE_NONE = 0,
    OBJ_ANIME_MODE_LOOP = 1,
    OBJ_ANIME_MODE_STOP = 2,
    OBJ_ANIME_MODE_REPEAT = 3,
    OBJ_ANIME_MODE_PINGPONG = 4,
    OBJ_ANIME_MODE_PINGPONG_ONCE = 5,
    OBJ_ANIME_MODE_LOOK = 6,
    OBJ_ANIME_MODE_RANDOM = 7,
    OBJ_ANIME_MODE_CLOCK_MINUTE = 8,
    OBJ_ANIME_MODE_CLOCK_HOUR = 9,
    OBJ_ANIME_MODE_TIME = 10,
};

class CFuncPointCheck {
public:
    float time;
    s32 anime_frame;

    CFuncPointCheck() { time = 0.0f; }
};

STATIC_ASSERT(sizeof(CFuncPointCheck) == 0x8);

class CObjAnimeEnv {
public:
    sceVu0FVECTOR chara_pos;
    float time;
    u8    unk_14[0x4C];
};

class CObjAnime {
public:
    CFuncPoint *func_point;
    mgCFrame *frame;
    CMapPiece *piece;
    CMapParts *parts;
    s32 stop;
    s32 back;
    s32 unk_18;
    s32 unk_1c;
    sceVu0FVECTOR param;

    CObjAnime();

    void Step(CObjAnimeEnv *env);

    void SetParam(float *value);

    void GetParam(float *out_value);

    int AssignFuncAnime(CFuncPoint *point, CMapParts *parts);
};

STATIC_ASSERT(sizeof(CObjAnime) == 0x30);

template <>
void CList<CFuncPoint>::Initialize();

class CFuncPointMngr {
public:
    u32 flag;
    CList<CFuncPoint> *list[FUNC_POINT_TYPE_NUM];
    CList<CFuncPoint> *now;

    CFuncPointMngr() { Initialize(); }

    CFuncPoint *Add(int type, mgCMemory *stack);

    CFuncPoint *Add(int type, CList<CFuncPoint> *node);

    void Reserve(int num, mgCMemory *stack);

    CList<CFuncPoint> *GetReserve();

    CFuncPoint *AddFromReserve(int type);

    int GetNum(int type);

    int GetEventNum(int event_flag);

    int EnableFuncNum(int type);

    void GetStart(int type);

    CFuncPoint *Get();

    void GetEnd();

    CFuncPoint *Search(char *name);

    int GetLight(float *sphere, CFuncPoint *out_lights, int max, CFuncPointCheck *check, int mode);

    void Step(int type, CFuncPointCheck *check);

    int UpdateFlag(int type, CFuncPointCheck *check);

    void UpdateStatus();

    void Initialize();

    virtual int Copy(CFuncPointMngr &dest, mgCMemory *stack);
};

STATIC_ASSERT(sizeof(CFuncPointMngr) == 0x34);

int CheckTime(float time, float start, float end);

float LimitTime(float time);

float SubTime(float time, float sub);

void DrawFireEffect(float (*lw_matrix)[4], CFuncPointMngr *mngr, CFuncPointCheck *check, float rate, mgCTexture *fire_tex, mgCTexture *light_tex);

void DrawFireRaster(float (*lw_matrix)[4], CFuncPointMngr *mngr, CFuncPointCheck *check, CFireRaster *raster);

int GetSeSrcVolPan(float (*lw_matrix)[4], CFuncPointMngr *mngr, CFuncPointCheck *check, int *out_se_no, float *out_vol, float *out_pan, int max);

float GetLightAnimeWeight(CFuncPoint *point, int frame);
