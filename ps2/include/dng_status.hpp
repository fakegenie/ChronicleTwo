#pragma once

#include "common.h"
#include "mg_tanime.hpp"

class mgCTexture;

struct SP_RGBA {
    int r;
    int g;
    int b;
    int a;
};
STATIC_ASSERT(sizeof(SP_RGBA) == 0x10);

void PrintV(int x, int y, int value, mgCTexture *texture, mgRect<int> glyph, int digits, int align_right,
            int pitch, SP_RGBA *color);

void DrawDrumCounter(int x, int y, int value);

void DrawMainUnitStatusBord(float rate);

void DrawRoboUnitStatusBord(float rate);

void DrawMonsterUnitStatusBord(float rate);

void DrawStatusBord();
