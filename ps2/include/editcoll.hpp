#pragma once

#include "common.h"

#include "collision.hpp"

class mgCMemory;
struct mgVu0FBOX;

class CEditCollision : public CCollisionMDT {
public:
    void Copy(CEditCollision &dest, int area_kind, mgCMemory *memory);

    float AreaXZ();

    int OverlapPoly3XZ(float (*triangle)[4], float *area, mgVu0FBOX *box);

    float OverlapXZ(CEditCollision &other, float (*matrix)[4], mgVu0FBOX *box);

    int OverlapPoly3XZ(float (*triangle)[4], float (*matrix)[4], float *area);

    void ApplyMatrix(float (*matrix)[4]);

    void DeleteVerticalPoly();

    int PickupVerticalPoly();
};

STATIC_ASSERT(sizeof(CEditCollision) == 0x50);

int ClipBoxXZ(float *max_a, float *min_a, float *max_b, float *min_b);

float OverlapPoly3AreaXZ(float (*clipped)[4], float (*clipper)[4], mgVu0FBOX *box);
