#pragma once

#include "common.h"

enum DbgFontSerno {
    DBG_FONT_SERNO_SHEET_1    = 0x1000,
    DBG_FONT_SERNO_HALF_WIDTH = 0x2000,
    DBG_FONT_SERNO_DAKUTEN    = 0x2134,
    DBG_FONT_SERNO_HANDAKUTEN = 0x2135,
    DBG_FONT_SERNO_UNKNOWN    = 0x227E,
    DBG_FONT_SERNO_END        = 0x2285,
};

enum DbgFontSheet {
    DBG_FONT_SHEET_FULL_WIDTH_0 = 0,
    DBG_FONT_SHEET_FULL_WIDTH_1 = 1,
    DBG_FONT_SHEET_HALF_WIDTH   = 2,
    DBG_FONT_SHEET_COUNT        = 3,
};

class dbgCJISFont {
public:
    int           texture_id[DBG_FONT_SHEET_COUNT];
    int           loaded_texture_id;
    char          texture_name[DBG_FONT_SHEET_COUNT][0x20];
    int           x;
    int           y;
    int           char_width;
    int           char_height;
    unsigned long prev_serno;
    char          buffer[0x800];
    int           color[4];
    int           back_enable;
    int           back_color[4];
    int           shadow_enable;

    dbgCJISFont();

    void Initialize();

    void InitTexture(int full0_id, char *full0_name, int full1_id, char *full1_name, int half_id, char *half_name);

    void Clear();

    void __putc(unsigned long serno);

    void PrintDirect(int x, int y, char *format, ...);
};
STATIC_ASSERT(sizeof(dbgCJISFont) == 0x8B0);

extern dbgCJISFont JisFont;
