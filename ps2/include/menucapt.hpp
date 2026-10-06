#pragma once

#include "common.h"

class mgCMemory;

enum MenuChapterModeID {
    MENU_CHAPTER_MODE_FADE_IN  = 0,
    MENU_CHAPTER_MODE_SHOW     = 1,
    MENU_CHAPTER_MODE_FADE_OUT = 2,
};

struct MENU_CHAPTER_INFO {
    int   tex_block[2];
    u8    unk_8[0x10];
    int   show_cnt;
    float logo_alpha;
};
STATIC_ASSERT(sizeof(MENU_CHAPTER_INFO) == 0x20);

void MenuChapterInit(mgCMemory *stack, int *tex_block, int open_type, int chapter);

int MenuChapterKey();

void MenuChapterDraw();
