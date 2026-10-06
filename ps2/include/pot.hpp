#pragma once

#include "common.h"

#include <libvu0.h>

struct CCPoly;
class CMapParts;
class CMapPiece;
class mgCFrame;

enum {
    BPOT_FRAGMENT_MAX = 32,
    BPOT_BREAK_TIME = 60,
    BPOT_FADE_TIME = 30,
    POT_FLY_TIME_MAX = 150,
};

enum POT_STATE {
    POT_STATE_NONE = 0,
    POT_STATE_HOLD = 1,
    POT_STATE_FLY = 2,
};

enum POT_STEP_RESULT {
    POT_STEP_NONE = 0,
    POT_STEP_BREAK = 1,
    POT_STEP_TIMEOUT = 2,
};

enum BPOT_TYPE {
    BPOT_TYPE_NONE = 0,
    BPOT_TYPE_BOX = 1,
    BPOT_TYPE_ROCK0 = 2,
    BPOT_TYPE_ROCK1 = 3,
};

class CFragment {
public:
    int           no;
    int           active;
    sceVu0FVECTOR position;
    sceVu0FVECTOR velocity;
    sceVu0FVECTOR gravity;
    sceVu0FVECTOR rotation;
    mgCFrame     *frame;

    CFragment() { Init(); }

    void Draw(float *origin, float alpha);

    void Step(CCPoly *polys, int poly_num);

    void Set(float *position, float *velocity);

    void Init();
};

STATIC_ASSERT(sizeof(CFragment) == 0x60);

class CBPot {
public:
    int           timer;
    int           type;
    CMapParts    *parts;
    CMapPiece    *piece;
    mgCFrame     *frame;
    sceVu0FVECTOR position;
    int           fragment_num;
    CFragment     fragment[BPOT_FRAGMENT_MAX];
    float       (*offset)[4];

    CBPot() { Init(); }

    void Clash(float *position, float *normal, float *velocity);

    void Step();

    int SetObject2(int kind, CMapParts *parts);

    void Init();
};

STATIC_ASSERT(sizeof(CBPot) == 0xC50);

class CPot {
public:
    int           state;
    CMapParts    *parts;
    sceVu0FVECTOR position;
    sceVu0FVECTOR velocity;
    sceVu0FVECTOR gravity;
    sceVu0FVECTOR hold_pos;
    sceVu0FVECTOR prev_hold_pos;
    sceVu0FVECTOR break_pos;
    int           fly_time;

    CPot() { Init(0); }

    void HoldStep();

    int FlyStep();

    void Clear();

    void Bakuhatsu(float *normal, float *velocity);

    int Step();

    void Throw();

    void Hold(CMapParts *parts);

    void Init(int keep);
};

STATIC_ASSERT(sizeof(CPot) == 0x80);

void CalcReflectionVector(float *direction, float *normal, float *out_reflection);

extern float box_offset[12][4];

extern float iwa0_offset[10][4];

extern float iwa1_offset[9][4];

extern CPot BTsubo;

extern CBPot BTsubo2;
