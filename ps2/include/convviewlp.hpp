#pragma once

#include "common.h"
#include "mainloop.hpp"
#include "savedata.hpp"
#include "memcard.hpp"

enum SV_CONV_MODE {
    SV_CONV_MODE_SELECT  = 0,
    SV_CONV_MODE_CONVERT = 2,
    SV_CONV_MODE_RESULT  = 3,
};

enum SAVEDATA_CONVERT_PHASE {
    SAVEDATA_CONVERT_PHASE_CHECK_CARD = 0,
    SAVEDATA_CONVERT_PHASE_READ_DIR   = 1,
    SAVEDATA_CONVERT_PHASE_CONVERT    = 2,
    SAVEDATA_CONVERT_PHASE_END        = 3,
};

enum SAVEDATA_CONVERT_RESULT {
    SAVEDATA_CONVERT_RESULT_NONE       = 0,
    SAVEDATA_CONVERT_RESULT_DONE       = 1,
    SAVEDATA_CONVERT_RESULT_CARD_ERROR = 100,
    SAVEDATA_CONVERT_RESULT_NO_FILES   = 101,
};

enum SAVEDATA_CONVERT_TYPE {
    SAVEDATA_CONVERT_TYPE_NONE  = -1,
    SAVEDATA_CONVERT_TYPE_GAME  = 0,
    SAVEDATA_CONVERT_TYPE_ALBUM = 1,
    SAVEDATA_CONVERT_TYPE_OMAKE = 2,
};

struct SAVE_CONVERT_WORK {
    u8 unk_0[0x80];
    CSaveData save_data;
    u8 unk_659b0[0x10];
};
STATIC_ASSERT(sizeof(SAVE_CONVERT_WORK) == 0x659C0);

void SVConvViewInit(INIT_LOOP_ARG arg);

void SVConvViewExit();

int SVConvViewLoop();

int SaveDataConvertLoop();
