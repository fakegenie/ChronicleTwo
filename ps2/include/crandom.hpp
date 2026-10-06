#pragma once

#include "common.h"

class CRandom {
public:
    u32 seed;

    float nget();
};
STATIC_ASSERT(sizeof(CRandom) == 0x4);

float abs(float value);
