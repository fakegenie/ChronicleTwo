#pragma once

#include "common.h"
#include "subgame.hpp"

class CScene;
class CEditData;
class mgCMemory;

enum EDIT_DEBUG_PAGE {
    EDIT_DEBUG_PAGE_GENERAL = 0,
    EDIT_DEBUG_PAGE_EDIT_DATA = 1,
    EDIT_DEBUG_PAGE_MAP = 2,
    EDIT_DEBUG_PAGE_COUNT = 3,
};

enum EDIT_DEBUG_GENERAL_ITEM {
    EDIT_DEBUG_GENERAL_DEBUG_CAMERA = 0,
    EDIT_DEBUG_GENERAL_RUN_EVENT = 1,
    EDIT_DEBUG_GENERAL_GEORAMA_DEBUG = 2,
    EDIT_DEBUG_GENERAL_CHARA_MOVE = 3,
    EDIT_DEBUG_GENERAL_SUB_GAME = 4,
    EDIT_DEBUG_GENERAL_PARAM_OFF = 5,
    EDIT_DEBUG_GENERAL_INVENT_DEBUG = 6,
    EDIT_DEBUG_GENERAL_COUNT = 7,
};

enum EDIT_DEBUG_EDIT_DATA_ITEM {
    EDIT_DEBUG_EDIT_DATA_ALL_CLEAR = 0,
    EDIT_DEBUG_EDIT_DATA_SAVE_FILE = 1,
    EDIT_DEBUG_EDIT_DATA_LOAD_FILE = 2,
    EDIT_DEBUG_EDIT_DATA_CONDITION = 3,
    EDIT_DEBUG_EDIT_DATA_MAP_FLAG = 4,
    EDIT_DEBUG_EDIT_DATA_COUNT = 5,
};

enum EDIT_DEBUG_MAP_ITEM {
    EDIT_DEBUG_MAP_MAP_JUMP = 0,
    EDIT_DEBUG_MAP_LOAD_GYORACE = 1,
    EDIT_DEBUG_MAP_COUNT = 2,
};

enum LIGHTING_EDIT_PAGE {
    LIGHTING_EDIT_PAGE_BG_AMBIENT = 0,
    LIGHTING_EDIT_PAGE_DIR_LIGHT = 1,
    LIGHTING_EDIT_PAGE_FOG = 2,
    LIGHTING_EDIT_PAGE_FILE = 3,
    LIGHTING_EDIT_PAGE_COUNT = 4,
};

struct EditDebugInfo : public SubGameInfo {
    CEditData *edit_data;
    int edit_data_no;
    int jump_map_no;
};
STATIC_ASSERT(sizeof(EditDebugInfo) == 0x3C);

void EditDebugInit();

int EditDebugMode();

void EditDebugStart(int texb, mgCMemory *buffer);

int EditDebugLoop(CScene *scene, EditDebugInfo *info);

void EditDebugEnd();

void InitLightingEdit();

void EndLightingEdit();

int IsLightingEditMode();

void LightingEdit(CScene *scene);
