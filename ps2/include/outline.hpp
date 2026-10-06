#pragma once

#include "common.h"

#include "mg_drawenv.hpp"

class mgCFrame;
class mgCTexture;

class COutLineDraw {
public:
    COutLineDraw *next;
    mgVu0FBOX unk_10;
    mgCTexture *texture;
    mgCFrame *frame;
    float width;
    int depth_from_pos;
    sceVu0FVECTOR pos;
    sceVu0FVECTOR color;
    int enable;
    int hide_edge;

    COutLineDraw() {
        next = NULL;
        Initialize();
    }

    void Initialize();

    void SetFrame(mgCFrame *frame);

    int Draw(float *pos, float scale, float alpha);

    int Draw(float scale, float alpha);
};
STATIC_ASSERT(sizeof(COutLineDraw) == 0x70);
