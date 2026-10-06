#pragma once

#include "common.h"

class mgCTexture;

enum {
    WAVE_TABLE_DIM = 24
};

class CWaveTable {
public:
    float height[2][WAVE_TABLE_DIM][WAVE_TABLE_DIM];
    int current;

    CWaveTable();

    virtual ~CWaveTable();

    void CreateTexture(mgCTexture *texture);

    void GetEffect();

    void Effect();
};
STATIC_ASSERT(sizeof(CWaveTable) == 0x1208);
