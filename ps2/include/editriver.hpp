#pragma once

#include "common.h"

#include <libvu0.h>

class mgCMemory;
struct CCPoly;
struct mgVu0FBOX;

enum {
    EDIT_GRID_CORNER_MAX = 4,
    EDIT_GRID_ROT_MAX = 4,
};

enum EditRiverPiece {
    EDIT_RIVER_PIECE_OUTER = 0,
    EDIT_RIVER_PIECE_EDGE = 1,
    EDIT_RIVER_PIECE_INNER = 2,
    EDIT_RIVER_PIECE_FULL = 3,
    EDIT_RIVER_PIECE_VARIANT = 4,
};

class CGridData {
public:
    s32 river;
    s16 piece[EDIT_GRID_CORNER_MAX];
    s16 rot[EDIT_GRID_CORNER_MAX];

    CGridData();
};

STATIC_ASSERT(sizeof(CGridData) == 0x14);

class CEditGrid {
public:
    s32 num_x;
    s32 num_z;
    CGridData *data;
    float step_x;
    float step_z;
    u8 unk_14[0xC];
    sceVu0FVECTOR origin;
    sceVu0FMATRIX rot[EDIT_GRID_ROT_MAX];

    void Create(int num_x, int num_z, mgCMemory *stack);

    void Clear();

    void Initialize();

    int Check(int x, int z);

    CGridData *Get(int x, int z);

    CGridData *GetFast(int x, int z);

    int GetLPos(int *lpos, float x, float z);

    void GetWPos(float *pos, int x, int z);

    int SetRiver(float x, float z);

    int ResetRiver(float x, float z);

    int SetRiver(int x, int z);

    int ResetRiver(int x, int z);

    int UpdateRiver(int x, int z);

    int River(int x, int z);

    void GetRiverPos(int x, int z, float (*pos)[4]);

    void GetRiverPos(int x, int z, float *pos);

    int GetRiverPoly(CCPoly *poly, const mgVu0FBOX &box, int poly_max, float margin);

    void GetGridBox(mgVu0FBOX *box, float *pos);
};

STATIC_ASSERT(sizeof(CEditGrid) == 0x130);
