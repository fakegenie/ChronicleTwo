#pragma once

#include "common.h"

#include "mg_drawprim.hpp"

class CPreSprite : public mgCDrawPrim {
public:
    u8 unk_120[0x10];

    void Preset2D();

    void SetIRect(int x, int y, int w, int h, int u, int v);

    void SetIStretch(int x, int y, int w, int h, int u, int v, int tw, int th);

    void SetScirror(int x, int y, int w, int h);

    void SetAlphaBlend(int mode);
};
STATIC_ASSERT(sizeof(CPreSprite) == 0x130);
