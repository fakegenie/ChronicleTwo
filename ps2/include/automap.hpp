#pragma once

#include "common.h"

#include <libvu0.h>

#include "prespr.hpp"

class CCharacter2;
class CMap;
class CMapParts;
class mgCMemory;
class mgCTexture;

enum AUTOMAP_PARTS_KIND {
    AUTOMAP_KIND_NONE = 0x0,
    AUTOMAP_KIND_ROAD = 0x1,
    AUTOMAP_KIND_ROOM = 0x2,
    AUTOMAP_KIND_ROOM_ALT = 0x4,
    AUTOMAP_KIND_ENTRANCE = 0x8,
    AUTOMAP_KIND_DOOR = 0x10,
    AUTOMAP_KIND_STEP = 0x20,
    AUTOMAP_KIND_PART = 0x100,
    AUTOMAP_KIND_ROAD_END = 0x200,
    AUTOMAP_KIND_HEALING = 0x400,
};

enum AUTOMAP_LINK {
    AUTOMAP_LINK_NEG_Z = 0x1,
    AUTOMAP_LINK_POS_Z = 0x2,
    AUTOMAP_LINK_POS_X = 0x4,
    AUTOMAP_LINK_NEG_X = 0x8,
};

enum AUTOMAP_WALL {
    AUTOMAP_WALL_NEG_X = 0x1,
    AUTOMAP_WALL_NEG_Z = 0x2,
    AUTOMAP_WALL_POS_X = 0x4,
    AUTOMAP_WALL_POS_Z = 0x8,
};

enum AUTOMAP_ATTR {
    AUTOMAP_ATTR_HIDE = 0x1,
};

enum AUTOMAP_GEN_FLAG {
    AUTOMAP_GEN_DUMMY_TREE = 0x1,
    AUTOMAP_GEN_PRESET_FLOOR = 0x2,
    AUTOMAP_GEN_DUMMY_MOUNTAIN = 0x4,
    AUTOMAP_GEN_FIXED_START = 0x8,
    AUTOMAP_GEN_NO_IN_OUT = 0x10,
    AUTOMAP_GEN_NO_HEALING = 0x20,
    AUTOMAP_GEN_FIXED_FLOOR = 0x40,
};

enum MINIMAP_SYMBOL {
    MINIMAP_SYMBOL_MONSTER = 0,
    MINIMAP_SYMBOL_TREASURE_BOX = 1,
    MINIMAP_SYMBOL_RANDOM_CIRCLE = 2,
    MINIMAP_SYMBOL_GEOSTONE = 3,
    MINIMAP_SYMBOL_SPHIDA_4 = 4,
    MINIMAP_SYMBOL_SPHIDA_5 = 5,
    MINIMAP_SYMBOL_SPHIDA_6 = 6,
    MINIMAP_SYMBOL_SPHIDA_7 = 7,
    MINIMAP_SYMBOL_MONSTER_BLINK = 8,
    MINIMAP_SYMBOL_END = -1,
};

struct AUTOMAP_PARTS_INFO {
    char *name;
    s16 kind;
    u8 link;
    u8 entrance;
    s16 unk_8[8];
};
STATIC_ASSERT(sizeof(AUTOMAP_PARTS_INFO) == 0x18);

struct MINIMAP_INFO {
    char name[16];
    s16 tile[320];
};
STATIC_ASSERT(sizeof(MINIMAP_INFO) == 0x290);

struct MINIMAP_SYMBOL_INFO {
    s16 symbol;
    s16 r;
    s16 g;
    s16 b;
    s16 w;
    s16 h;
    s16 blink;
    s16 need_visible;
};
STATIC_ASSERT(sizeof(MINIMAP_SYMBOL_INFO) == 0x10);

struct AUTOMAP_ROOM_INFO {
    s32 id;
    s32 w;
    s32 h;
    s32 fixed;
    s32 rate;
    s16 *table;
};
STATIC_ASSERT(sizeof(AUTOMAP_ROOM_INFO) == 0x18);

struct AUTOMAP_ROOM {
    s32 unk_0;
    s32 x;
    s32 y;
    s32 w;
    s32 h;
};
STATIC_ASSERT(sizeof(AUTOMAP_ROOM) == 0x14);

class CAutoMapParts {
public:
    u32 kind;
    s16 parts_no;
    s16 attr;
    s16 room_no;
    u8 road_link;
    u8 link;
    s16 visible;
    CMapParts *parts;
    u32 wall;
    s8 navi;

    void Initialize() {
        parts_no = -1;
        attr = 0;
        kind = 0;
        room_no = -1;
        road_link = 0;
        link = 0;
        visible = 0;
        wall = -1;
        parts = NULL;
    }
};
STATIC_ASSERT(sizeof(CAutoMapParts) == 0x1C);

class CMiniMapSymbol {
public:
    CMap *map;
    CMapParts *parts_table;
    s32 parts_num;
    mgCTexture *texture;
    CPreSprite prim;
    CAutoMapParts *grid;
    MINIMAP_INFO *info;
    s16 grid_w;
    s16 grid_h;
    float cell_w;
    float cell_d;
    s32 unk_154[3];
    sceVu0FVECTOR center;
    s16 x;
    s16 y;
    s16 w;
    s16 h;
    s32 blink_cnt;
    s16 large;
    u8  unk_17e[0x2];

    void SetMapInfo(CMap *map, CAutoMapParts *grid, int grid_w, int grid_h, float cell_w, float cell_d);

    void DrawSymbolOpen();

    void DrawSymbolClose();

    void DrawSymbol(float *pos, int symbol);

    void DrawSymbol_Chara(CCharacter2 *chara);

    void Draw(float *pos);
};
STATIC_ASSERT(sizeof(CMiniMapSymbol) == 0x180);

class CHealingPoint {
public:
    s32 enable;
    s32 timer;

    int CheckHealingTime();

    void Step();
};
STATIC_ASSERT(sizeof(CHealingPoint) == 0x8);

class CAutoMapGen {
public:
    CMapParts *gio_parts;
    CMapParts *random_stone[12];
    CMapParts *pot_parts;
    s16 random_map;
    s16 minimap_enable;
    u32 gen_flag;
    CMiniMapSymbol mini_map;
    CHealingPoint healing_point;
    s16 grid_w;
    s16 grid_h;
    float cell_w;
    float cell_d;
    AUTOMAP_ROOM_INFO *room_info;
    s32 room_info_num;
    CAutoMapParts *grid;
    s32 place_parts_num;
    AUTOMAP_ROOM room[8];
    s32 room_num;
    s32 door_room;
    s32 navi_valid;
    s32 navi_depth;
    s32 navi_enable;
    s32 unk_298[2];

    void SetupRoomInfo(char *script, int size, mgCMemory *stack);

    int CreatRoom(int x, int y, int room_no, int info_no);

    int LinkConnectCheck(int x, int y, int kind, int room_no, int exclude);

    void SetRoadLinkMark(int x, int y, int side);

    void RoomLink(int from, int to);

    void CreatDummyRoot(int room_no);

    void CreatTermParts();

    void CreatDoorRoom();

    CMapParts *SearchDoorParts();

    void SetPartsIndex();

    void SetDummyMountain();

    void SetDummyTree();

    void SearchHealingPoint(CMap *map);

    void IndexToPartsPlace();

    void SetInOutPartsIndex(int offset);

    void SetHealingPointIndex();

    void CreatFixedMap(int info_no);

    void RandomMapMainProc();

    void Build();

    void MinimapVisTest(float *pos);

    void MinimapDoorOpen(float *pos);

    CMapParts *SearchRandomStone(float *pos, float range);

    void ClearRandomStone();

    void Step();

    int GetAttrStatus(float *pos);

    void MinimapAllVisible();

    float GetNaviDistance(float *pos);

    void UpdateNaviMap(float *pos, int depth);
};
STATIC_ASSERT(sizeof(CAutoMapGen) == 0x2A0);

extern AUTOMAP_PARTS_INFO PartsInfoData[277];

extern MINIMAP_INFO MiniMapInfoData[18];
