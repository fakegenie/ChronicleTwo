#pragma once

#include "common.h"

#include "font.hpp"

class mgCDrawPrim;

enum VersatileWinPart {
    VWIN_TOP_L          = 0,
    VWIN_TOP_C          = 1,
    VWIN_TOP_R          = 2,
    VWIN_SIDE_L         = 3,
    VWIN_SIDE_C         = 4,
    VWIN_SIDE_R         = 5,
    VWIN_BAND_L         = 6,
    VWIN_BAND_C         = 7,
    VWIN_BAND_R         = 8,
    VWIN_LOWER_SIDE_L   = 9,
    VWIN_LOWER_SIDE_C   = 10,
    VWIN_LOWER_SIDE_R   = 11,
    VWIN_LOWER_BOTTOM_L = 12,
    VWIN_LOWER_BOTTOM_C = 13,
    VWIN_LOWER_BOTTOM_R = 14,
    VWIN_BOTTOM_L       = 15,
    VWIN_BOTTOM_C       = 16,
    VWIN_BOTTOM_R       = 17,
    VWIN_TOP4_L         = 18,
    VWIN_TOP4_C         = 19,
    VWIN_TOP4_R         = 20,
    VWIN_PART_MAX       = 21,
};

void CalcSelectCursorPos(RECT win, int *cursor_pos);

void OffsetYesNoWin(RECT *win, RECT *shadow);

void DrawVersatileWin_yesno(mgCDrawPrim *prim, RECT win, RGBAQ_TYPE *color, int alpha, int opaque);

void MyMenuHelpWinDraw(mgCDrawPrim *prim, RECT win, int alpha);

void MyMenuFloatingWinDraw(mgCDrawPrim *prim, RECT win, int point_x, int point_y, RGBAQ_TYPE *frame_color,
                           RGBAQ_TYPE *fill_color);

void DrawVersatileWin_1(mgCDrawPrim *prim, RECT win, RGBAQ_TYPE *color, int alpha, int opaque);

void DrawVersatileWin_1(mgCDrawPrim *prim, RECT win, RGBAQ_TYPE *color, int alpha);

void DrawVersatileWin_3(mgCDrawPrim *prim, RECT win, int select_y, RGBAQ_TYPE *color, int alpha, int opaque);

void DrawVersatileWin_4(mgCDrawPrim *prim, RECT win, RGBAQ_TYPE *color, int alpha, int opaque);

void DrawVersatileWin_4(mgCDrawPrim *prim, RECT win, RGBAQ_TYPE *color, int alpha);

void DrawDQFukidashi(mgCDrawPrim *prim, RECT win, int tail_x, int tail_y, RGBAQ_TYPE *color, int tail_on,
                     int mode);

extern s32 data[VWIN_PART_MAX][4];
