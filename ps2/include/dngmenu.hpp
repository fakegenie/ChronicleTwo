#pragma once

#include "common.h"

#include "dng_event.hpp"
#include "menucls1.hpp"
#include "menusys.hpp"
#include "mg_tanime.hpp"

class CDngFloorManager;
class CSaveDataDungeon;
class mgCMemory;
class mgCTexture;
struct DNGMAP_ROOM_INFO;
struct DNGMAP_ROOT_INFO;
struct GLID_INFO;

enum DNGMAP_MODE {
    DNGMAP_MODE_MENU = 0,
    DNGMAP_MODE_EVENT = 1,
};

enum DNGMAP_FADE {
    DNGMAP_FADE_NONE = -1,
    DNGMAP_FADE_IN = 0,
    DNGMAP_FADE_OUT = 1,
};

enum {
    DNGMAP_MARK_MAX = 8,
    DNGMAP_BLINK_CYCLE = 100,
    DNG_TREE_MAP_MES_MAX = 8,
    DNG_TREE_MAP_MATERIA_MAX = 0x103,
};

enum DNG_TREE_MAP_RESULT {
    DNG_TREE_MAP_CONTINUE = 0,
    DNG_TREE_MAP_CLOSE = 1,
    DNG_TREE_MAP_JUMP = 2,
};

enum DNG_TREE_MODE {
    DNG_TREE_MODE_MAP = 0,
    DNG_TREE_MODE_SAVE = 1,
};

struct DNGMAP_KOMA_POS {
    float x;
    float y;
    DNGMAP_KOMA_POS *next;
};

STATIC_ASSERT(sizeof(DNGMAP_KOMA_POS) == 0xC);

class CDngFreeMap {
public:
    CSaveDataDungeon *save_dungeon;
    CDngFloorManager *floor_manager;
    u8 active;
    u8 unk_9;
    s16 dng_no;
    s16 mode;
    u8 unk_e[0x2];
    float back_scroll;
    u8 unk_14[0xC];
    mgRect<float> view_rect;
    s32 mark_num;
    u8 unk_34[0xC];
    mgRect<float> mark_rect[DNGMAP_MARK_MAX];
    s16 user_room_no;
    s16 next_room_no;
    GLID_INFO *user_glid;
    s16 blink_cnt;
    u8 unk_ca[0x2];
    GLID_INFO *select_glid;
    s16 tex_block;
    u8 unk_d2[0x2];
    mgCTexture *name_tex;
    mgCTexture *map_tex;
    mgCTexture *last_tex;
    mgCTexture *koma_tex;
    DNGMAP_KOMA_POS *koma_path;
    DNGMAP_KOMA_POS *koma_now;
    s16 koma_move;
    u8 unk_ee[0x2];
    float alpha;
    s32 fade_time;
    float fade_step;
    s32 fade_mode;
    float pos_x;
    float pos_y;
    float next_pos_x;
    float next_pos_y;

    CDngFreeMap() { Initialize(); }

    void Initialize();

    void InitTexture();

    void SetUserGlid(int room_no);

    void CalcGlidPutPos(GLID_INFO *glid, float &x, float &y, int board);

    void CheckIsViewMove(int x, int y, float &move_x, float &move_y);

    void SetNextRoomPos(GLID_INFO *glid);

    GLID_INFO *GetNextGlid(GLID_INFO *glid, int *direction);

    GLID_INFO *GetRoomGlid(int room_no);

    GLID_INFO *GetEntranceRoomGlid();

    void SetTextureInfo();

    void ResetDngMapPos(int room_no, int at_once);

    void DrawBackPattern(int alpha);

    void DrawDngName(int alpha);

    void DrawLast();

    void DrawRoot(mgRect<float> rect, DNGMAP_ROOT_INFO *root, int shadow, unsigned int glid_check, int alpha);

    unsigned int DrawGlidCheck(GLID_INFO *glid);

    void DrawRoomOne(mgRect<float> rect, DNGMAP_ROOM_INFO *room, unsigned int glid_check, int alpha, float bright);

    void DrawGlid(mgRect<float> rect);

    void DrawTreeMap(int alpha);

    void DrawPlayer(int alpha);

    void Step();

    void Draw();

    void FadeIn(int time);

    void FadeOut(int time);

    void DeleteTexBlock();

    void SetKomaMove(int move);

    int LoadDngInfo(mgCMemory *stack, int tex_block, int dng_no, int user_room_no, int next_room_no);
};

STATIC_ASSERT(sizeof(CDngFreeMap) == 0x110);
STATIC_ASSERT(sizeof(mgRect<float>) == 0x10);

class CMenuTreeMap : public CBaseMenuClass {
public:
    float cursor_pos[2];
    s16 dng_no;
    s16 unk_11a;
    s16 jump_pay;
    u8 unk_11e[0x2];
    GLID_INFO *select_glid;
    u8 unk_124[0xC];
    CDC2Mes mes[DNG_TREE_MAP_MES_MAX];
    short *mes_data;
    s32 cursor_view;
    s32 cursor_reset;
    s32 money_view;
    s32 help_view;
    u8 tresure_loaded;
    u8 unk_153c5[0x3];
    TRESURE_BOX_FLOOR_INFO tresure;
    s32 georama_materia[DNG_TREE_MAP_MATERIA_MAX];

    CMenuTreeMap();

    virtual void InitEnd();

    void MsgInit();

    int Step();

    void Draw();

    int FadeInOutMenu();
};

STATIC_ASSERT(sizeof(CMenuTreeMap) == 0x2FBE0);

int CheckDngTreeMapFuncType();

void MakeDngTreeMapJumpNo(int dng_no, int floor_id, int *loop_no, int *map_no);

void DngTreeMapInit(mgCMemory *stack, int *tex_block, int menu_mode, int dng_no);

int DngTreeMapKey();

void DngTreeMapDraw();

extern u8 TreeMapSaveFlag;

extern s16 TreeMapSaveNum;

extern u8 TreeMapCallDungeonSubMap;

extern u8 TreeMapCalledWorldMap;
