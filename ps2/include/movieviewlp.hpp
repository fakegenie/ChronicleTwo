#pragma once

#include "common.h"
#include "mainloop.hpp"

struct MOVIE_LIST_ENTRY {
    char *name;
    char *file_name;
    int   bgm_no;
};
STATIC_ASSERT(sizeof(MOVIE_LIST_ENTRY) == 0xC);

enum MOVIE_VIEW_MODE {
    MOVIE_VIEW_MODE_SELECT = 0,
    MOVIE_VIEW_MODE_PLAY   = 1,
};

enum MOVIE_SPECIAL_MODE {
    MOVIE_SPECIAL_MODE_NONE     = 0,
    MOVIE_SPECIAL_MODE_PROMO    = 1,
    MOVIE_SPECIAL_MODE_PROMO_TV = 2,
};

void MovieViewInit(INIT_LOOP_ARG arg);

void MovieViewExit();

int MovieViewLoop();
