#pragma once

#include "common.h"

class mgCMemory;
class CCharacter2;

enum MapSelType {
    MAP_SEL_NEW         = 0,
    MAP_SEL_GEORAMA     = 1,
    MAP_SEL_PALM_BLINKS = 2,
    MAP_SEL_SUBMAP      = 3,
    MAP_SEL_FUTURE      = 4,
    MAP_SEL_DUNGEON     = 5,
    MAP_SEL_EVENT       = 6,
    MAP_SEL_SPECIAL     = 7,
    MAP_SEL_TYPE_NUM    = 8,
};

enum MapSelectMode {
    MAP_SELECT_MODE_CANCEL = -1,
    MAP_SELECT_MODE_TYPE   = 0,
    MAP_SELECT_MODE_MAP    = 1,
    MAP_SELECT_MODE_DECIDE = 2,
};

enum MapSelectResult {
    MAP_SELECT_CONTINUE = 0,
    MAP_SELECT_CANCEL   = 1,
    MAP_SELECT_DECIDE   = 2,
};

enum SaveDataEditItem {
    SED_PROGRESS  = 0,
    SED_TIME      = 1,
    SED_FLAG      = 2,
    SED_GEO_COMP  = 3,
    SED_PLAY_TIME = 4,
    SED_CONFIG    = 5,
    SED_ITEM_NUM  = 6,
};

enum EventViewResult {
    EVENT_VIEW_CONTINUE = 0,
    EVENT_VIEW_START    = 1,
    EVENT_VIEW_CANCEL   = 2,
};

enum {
    MAP_NAME_BUFF_SIZE = 0x800,
    SELECT_MAP_MAX     = 0x80,
    EVENT_VIEW_MAX     = 0x200,
};

struct MAP_NAME_INFO {
    char *name;
    char *title;
    char *add_path;
    int   type;
    int   sel_type;
    int   snd_data_id;
    int   area_no;
};
STATIC_ASSERT(sizeof(MAP_NAME_INFO) == 0x1C);

struct EVENT_VIEW_INFO {
    char *name;
    char *detail;
    int   unk_8;
    int   event_no;
    int   map_no;
    int   floor_no;
    int   dungeon;
};
STATIC_ASSERT(sizeof(EVENT_VIEW_INFO) == 0x1C);

extern EVENT_VIEW_INFO *EventInfo;

extern int BossBattleSelFlag;

void LoadMapName(int language, u_long128 *buffer);

void GetMapPath(char *path, char *name);

int GetMapType(int map_no);

int GetMapAreaNo(int map_no);

int GetMapSelType(int map_no);

int GetMapSndDataID(int map_no);

char *GetMapName(int map_no, char **title);

int SearchMapNo(char *name);

char *GetMapTitle(int map_no);

char *GetAddMapPath(int map_no);

void InitMapSelect(mgCMemory *stack);

int MapSelectLoop();

void InitSaveDataEdit(mgCMemory *stack);

int SaveDataEditLoop();

int EventViewLoop();

void LoadEventViewData(u_long128 *buffer, mgCMemory *stack);

void AtraMiriaOnOff(int type, CCharacter2 *chara, int on);
