#pragma once

#include "common.h"

#include <libvu0.h>
#include <cstring>

class COcclusion {
public:
    COcclusion() { memset(this, 0, sizeof(COcclusion)); }

    int enable;
    u8 unk_4[0xC];
    sceVu0FVECTOR vertex[4];
    int setup;
    u8 unk_54[0xC];
    sceVu0FVECTOR plane;
    sceVu0FVECTOR side_plane[4];
    sceVu0FVECTOR view_min;

    void Setup(sceVu0FMATRIX view_matrix);

    int CheckSphere(sceVu0FVECTOR sphere);
};
STATIC_ASSERT(sizeof(COcclusion) == 0xC0);
