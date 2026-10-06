#pragma once

#include "common.h"

enum EzBgmCommand {
    EZBGM_CHANNEL_MASK    = 0x000F,
    EZBGM_COMMAND_MASK    = 0xFFF0,
    EZBGM_PRELOAD         = 0x0040,
    EZBGM_OPEN            = 0x8020,
    EZBGM_OPEN_FROM_PACK  = 0x80F0,
    EZBGM_UNK_8A00        = 0x8A00,
};

int ezBgmInit();

int ezBgm(int command, int argument);
