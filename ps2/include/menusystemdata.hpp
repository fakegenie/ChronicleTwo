#pragma once

#include "common.h"

struct MENU_SYSTEM_LIST_CURSOR {
    s16 select;
    s16 top;
};

STATIC_ASSERT(sizeof(MENU_SYSTEM_LIST_CURSOR) == 0x4);

struct MENU_SYSTEM_GHOBI {
    s16 item_no;
    s16 unk_2;
};

STATIC_ASSERT(sizeof(MENU_SYSTEM_GHOBI) == 0x4);

#define MENU_SYSTEM_GHOBI_NUM 32

#define MENU_SYSTEM_GEORAMA_LIST_NUM 7

class CMenuSystemData {
public:
    s16 item_board_select;
    s16 item_board_top;
    s16 unk_4;
    s16 unk_6;
    s16 item_key_arg_no;
    s16 item_cursor;
    u8 unk_c[0x14];
    MENU_SYSTEM_LIST_CURSOR invent_item;
    u8 unk_24[0xA];
    s16 invent_unk_2e;
    MENU_SYSTEM_LIST_CURSOR invent_card;
    MENU_SYSTEM_LIST_CURSOR invent_photo;
    MENU_SYSTEM_LIST_CURSOR invent_album;
    MENU_SYSTEM_LIST_CURSOR invent_memo;
    u8 unk_40[0x10];
    MENU_SYSTEM_LIST_CURSOR georama_list[MENU_SYSTEM_GEORAMA_LIST_NUM];
    u8 unk_6c[0x21C];
    MENU_SYSTEM_GHOBI ghobi[MENU_SYSTEM_GHOBI_NUM];

    CMenuSystemData();

    void MenuSystemDataInit();

    int CheckGetAlready(int item_no);

    void GetGhobi(int item_no);
};

STATIC_ASSERT(sizeof(CMenuSystemData) == 0x308);
