#pragma once

#include "common.h"

enum FutureMapSelectResult {
    FUTURE_MAP_SELECT_CONTINUE = 0,
    FUTURE_MAP_SELECT_CHOSEN   = 1,
    FUTURE_MAP_SELECT_CLOSED   = 2,
};

enum HDDMenuResult {
    HDD_MENU_CONTINUE = 0,
    HDD_MENU_CLOSED   = 1,
};

enum HDDMenuItem {
    HDD_MENU_UNINSTALL = 0,
    HDD_MENU_INSTALL   = 1,
    HDD_MENU_MOUNT     = 2,
};

int FutureMapSelect();

void InitHDDMenu(u_long128 *work);

int HDDMenuLoop();

int EmergencyMessage(int error);
