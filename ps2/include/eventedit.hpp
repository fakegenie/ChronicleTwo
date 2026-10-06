#pragma once

#include "common.h"

#include <libvu0.h>

class mgCMemory;

enum EVENT_EDIT_MODE {
    EVENT_EDIT_MODE_CAMERA_MOVE = 0,
    EVENT_EDIT_MODE_CHARACTER = 1,
    EVENT_EDIT_MODE_CAMERA_PAS = 2,
    EVENT_EDIT_MODE_CHARA_PAS = 3,
    EVENT_EDIT_MODE_COUNT = 4,
};

enum EVENT_EDIT_PAS_OP {
    EVENT_EDIT_PAS_OP_ADDITION = 0,
    EVENT_EDIT_PAS_OP_INSERT = 1,
    EVENT_EDIT_PAS_OP_OVERWRITE = 2,
    EVENT_EDIT_PAS_OP_DELETE = 3,
    EVENT_EDIT_PAS_OP_COUNT = 4,
};

enum EVENT_EDIT_PAS_ITEM {
    EVENT_EDIT_PAS_ITEM_EDIT_MODE = 0,
    EVENT_EDIT_PAS_ITEM_SELECT_NO = 1,
    EVENT_EDIT_PAS_ITEM_FRAME = 2,
    EVENT_EDIT_PAS_ITEM_COUNT = 3,
};

struct EventEditInfo {
    int active;
    int mode;
    int disp;
    mgCMemory *memory;
    int texb;
    int chara_no;
    int collision;
    int unk_1C;
    sceVu0FVECTOR camera_pos;
    sceVu0FVECTOR camera_ref;
};
STATIC_ASSERT(sizeof(EventEditInfo) == 0x40);

void InitEventEdit(int texb, mgCMemory *memory);

int ChkEventEditStart();

int EventEdit(mgCMemory *memory);

void DrawEventEdit();
