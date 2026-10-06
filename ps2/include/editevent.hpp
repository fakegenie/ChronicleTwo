#pragma once

#include "common.h"

#include <libvu0.h>

#include "sceneevent.hpp"

class CScene;
struct RS_STACKDATA;

enum EditEventState {
    EDIT_EVENT_STATE_IDLE = 0,
    EDIT_EVENT_STATE_RUNNING = 1,
    EDIT_EVENT_STATE_UNK_2 = 2,
    EDIT_EVENT_STATE_END = 3,
};

enum EditEventType {
    EDIT_EVENT_TYPE_NONE = -1,
    EDIT_EVENT_TYPE_HOUSE_DOOR = 0,
    EDIT_EVENT_TYPE_DOOR = 1,
    EDIT_EVENT_TYPE_TREASURE_BOX = 2,
    EDIT_EVENT_TYPE_BOOK = 3,
};

enum EditEventResult {
    EDIT_EVENT_RESULT_IDLE = -1,
    EDIT_EVENT_RESULT_CONTINUE = 0,
    EDIT_EVENT_RESULT_END = 1,
    EDIT_EVENT_RESULT_ENTER = 2,
    EDIT_EVENT_RESULT_EXIT = 3,
    EDIT_EVENT_RESULT_ENTER_HOUSE = 4,
    EDIT_EVENT_RESULT_MENU = 5,
};

enum EditHouseDoorStep {
    EDIT_HOUSE_DOOR_STEP_OPEN_MENU = 0,
    EDIT_HOUSE_DOOR_STEP_MENU_END = 1,
    EDIT_HOUSE_DOOR_STEP_WAIT = 2,
};

enum EditDoorStep {
    EDIT_DOOR_STEP_START = 0,
    EDIT_DOOR_STEP_APPROACH = 1,
    EDIT_DOOR_STEP_OPEN = 2,
    EDIT_DOOR_STEP_LEAVE = 3,
    EDIT_DOOR_STEP_RETURN = 4,
    EDIT_DOOR_STEP_WAIT = 5,
};

enum EditTreasureBoxStep {
    EDIT_TREASURE_BOX_STEP_START = 0,
    EDIT_TREASURE_BOX_STEP_OPEN = 1,
    EDIT_TREASURE_BOX_STEP_LIFT = 2,
    EDIT_TREASURE_BOX_STEP_WAIT = 3,
    EDIT_TREASURE_BOX_STEP_MESSAGE = 4,
    EDIT_TREASURE_BOX_STEP_DELETE = 5,
    EDIT_TREASURE_BOX_STEP_FULL_MESSAGE = 6,
    EDIT_TREASURE_BOX_STEP_END = 7,
};

enum EditBookStep {
    EDIT_BOOK_STEP_START = 0,
    EDIT_BOOK_STEP_READ = 1,
    EDIT_BOOK_STEP_DONE = 2,
    EDIT_BOOK_STEP_CLOSE = 3,
};

class CEditEvent {
public:
    s32             count;
    s32             state;
    s32             step;
    s32             unk_c;
    s32             type;
    s32             unk_14;
    s32             unk_18;
    s32             unk_1c;
    CSceneEventData data;
    float           projection;
    s32             unk_f4;
    s32             unk_f8;
    s32             unk_fc;
    sceVu0FVECTOR   return_pos;
    sceVu0FVECTOR   return_rot;
    s32             reload_geo_npc;
    s32             unk_124;
    char            map_name[0x20];
    s32             door_se;
    s32             unk_14c;

    CEditEvent() {
        Reset();
    }

    void Reset();

    int StartEvent(CSceneEventData *event_data);

    int Step(CScene *scene);

    int Draw(CScene *scene);
};

STATIC_ASSERT(sizeof(CEditEvent) == 0x150);

enum GeoramaFuncCommand {
    GEORAMA_FUNC_LOAD_INT_NPC = 1,
    GEORAMA_FUNC_LOAD_GEO_NPC = 2,
    GEORAMA_FUNC_CHECK_PLACE_BURN = 3,
    GEORAMA_FUNC_TEST = 999,
};

struct GeoFuncParam {
    CScene *scene;
};

STATIC_ASSERT(sizeof(GeoFuncParam) == 0x4);

int GeoramaFunc(GeoFuncParam *param, RS_STACKDATA *args, int argc);

void GeoUpdateNpcPos(CScene *scene);
