#pragma once

#include "common.h"

union DngEventVector {
    float f[4];
    u_long128 qw;
};

#include <libvu0.h>

#include "character.hpp"
#include "mg_drawenv.hpp"
#include "mg_frame.hpp"
#include "object.hpp"

class CAutoMapGen;
class CColFrame;
class CMapParts;
class CMiniMapSymbol;
class ClsMes;
class mgCFrame;
class mgCMemory;
struct CCPoly;

enum EpisodeTitleState {
    EPISODE_TITLE_OFF = 0,
    EPISODE_TITLE_FADE_IN = 1,
    EPISODE_TITLE_HOLD = 2,
    EPISODE_TITLE_FADE_OUT = 3,
};

enum TreasureBoxState {
    TREASURE_BOX_STATE_NONE = 0,
    TREASURE_BOX_STATE_UNOPENED = 1,
    TREASURE_BOX_MAX = 24,
};

enum TreasureBoxFlag {
    TREASURE_BOX_FLAG_TWO_ITEMS = 0x80,
    TREASURE_BOX_FLAG_MIMIC = 0x100,
};

enum DungeonEventPointKind {
    DUNGEON_EVENT_POINT_PLAYER = 0,
    DUNGEON_EVENT_POINT_TREASURE_BOX = 1,
    DUNGEON_EVENT_POINT_WAY_20 = 2,
    DUNGEON_EVENT_POINT_WAY_24 = 3,
};

struct TRESURE_BOX_ITEM {
    s32 item_no;
    s32 rank;
    s32 num;
};

STATIC_ASSERT(sizeof(TRESURE_BOX_ITEM) == 0xC);

struct TRESURE_BOX_GROUP {
    s32 group_id;
    s32 item_num;
    TRESURE_BOX_ITEM item[96];
};

STATIC_ASSERT(sizeof(TRESURE_BOX_GROUP) == 0x488);

struct TRESURE_BOX_FLOOR {
    s32 group_num;
    s32 group_id[64];
};

STATIC_ASSERT(sizeof(TRESURE_BOX_FLOOR) == 0x104);

struct TRESURE_BOX_FLOOR_INFO {
    s16 rank_max;
    s16 rank_min;
    TRESURE_BOX_GROUP group[64];
    s32 group_num;
    TRESURE_BOX_FLOOR floor[128];
    s32 floor_start;
};

STATIC_ASSERT(sizeof(TRESURE_BOX_FLOOR_INFO) == 0x1A40C);

class CStartupEpisodeTitle {
public:
    s16 state;
    s16 wait;
    float alpha;
    float reveal;
    float slide;
    s16 width;
    ClsMes *mes;

    void DrawEpisode(int mes_tex_block, int frame_tex_block);

    void Switch(int state);

    void Step();

    void Initialize();
};

STATIC_ASSERT(sizeof(CStartupEpisodeTitle) == 0x18);

struct MESSAGE_TASK {
    char *message;
    char text[128];
    s8 priority;
    s16 time;
    s16 count;
    s16 slot;
    MESSAGE_TASK *next;
};

STATIC_ASSERT(sizeof(MESSAGE_TASK) == 0x90);

class MessageTaskManager {
public:
    u32 flag;
    ClsMes *mes;
    MESSAGE_TASK task[6];
    MESSAGE_TASK *top;

    void Draw();

    void Step();

    void Print(char *message, int time, int slot, int priority);

    void Clear();

    void Initialize();
};

STATIC_ASSERT(sizeof(MessageTaskManager) == 0x36C);

class CRedMarkModel : public CObjectFrame {
public:
    s32 draw_request;
    float angle;

    virtual void Initialize();

    virtual void Draw();

    virtual void Step();
};

STATIC_ASSERT(sizeof(CRedMarkModel) == 0x90);

class CGeoStone : public CCharacter2 {
public:
    s32 flag;
    float angle;
    s32 anime;

    void GeoDraw(float *player_pos);

    void DrawMiniMapSymbol(CMiniMapSymbol *mini_map);

    void SetFlag(int flag);

    void GeoStep();

    int CheckEvent(float *pos);

    virtual void Initialize();
};

STATIC_ASSERT(sizeof(CGeoStone) == 0x670);

class CRandomCircle {
public:
    sceVu0FVECTOR pos[3];
    s32 active[3];
    s32 hit;
    CCharacter2 model;

    void Draw(float *player_pos);

    void Step();

    void DrawSymbol(CMiniMapSymbol *mini_map);

    int CheckArea(float *pos, float dist);

    int GetPosition(float *out_pos, int index);

    int CheckEvent(float *pos);

    int SetCircle(float *pos);

    void Clear();

    void Initialize();
};

STATIC_ASSERT(sizeof(CRandomCircle) == 0x6A0);

class CTreasureBox : public mgCObject {
public:
    float lid_open;
    s8 state;
    s32 flags;
    s16 item[2];
    s16 num[2];
    mgCFrame *lid_frame;
    mgCFrame *frame;
    CCharacter2 *model;

    virtual void Initialize()
#ifndef DNG_DEBUG_SOURCE
    {
        state = TREASURE_BOX_STATE_NONE;
        lid_open = 0.0f;
        flags = 1;
    }
#else
    ;
#endif

    void Draw(float *camera_pos);

    void DrawShadow(float *camera_pos, float *light_dir);
};

STATIC_ASSERT(sizeof(CTreasureBox) == 0x70);

class CTreasureBoxManager {
public:
    s32 tex_block;
    CTreasureBox box[TREASURE_BOX_MAX];
    s32 unk_A90;
    CCharacter2 *model;
    CColFrame *col_frame;
    s32 near_box;

    void Initialize() {
        for (int i = 0; i < TREASURE_BOX_MAX; i++) {
            box[i].Initialize();
        }
        unk_A90 = 0;
        model = NULL;
        col_frame = NULL;
        near_box = -1;
    }

    void SetLargeModel(CCharacter2 *model, int tex_block);

    void SetCollisionModel(unsigned int *pack, mgCMemory *memory);

    void PutTreasureBox(int index, float *pos, float rot_y, int flags, int item0, int num0, int item1, int num1);

    int CheckArea(float *pos, float dist);

    void DrawMiniMapSymbol(CMiniMapSymbol *mini_map);

    void Draw(float *camera_pos);

    void DrawShadow(float *camera_pos);

    int PickupCollision(float *pos, CCPoly *poly, mgVu0FBOX box, int max);

    int MimicCount();

    int CheckEvent(float *pos, float dist);
};

STATIC_ASSERT(sizeof(CTreasureBoxManager) == 0xAA0);

int GetGateKeyIndex(int dungeon, int floor);

int GetKeyDoorIndex(int dungeon, int floor);

int Lamb2WolfManager();

void LoopSoundManager(int mode);

void BattleSoundManager();

void ScriptDebugCommand(int command);

void XChgMapLighting();

float XChgMapRotation(int rotation);

int SearchMapEventParts(int kind, CMapParts **out_parts, float *out_rot, int max);

int SearchMapFlatPosition(float *out_pos, CAutoMapGen *map_gen);

int GetDungeonEventPoint(float *out_pos, float *out_rot, int kind);

void CreatTresuarBoxInfo(TRESURE_BOX_FLOOR_INFO *info, char *script, int size);

float ScanEyePoint(float *pos);

void AutoSetTreasureBox(int item_no, float *pos, float rot_y);

void AutoSetTreasureBox();

void AutoSetMonster();

void AutoSetMonster(int monster_no, float *pos, float *rot, int param);

void DungeonFloorInit();

void DungeonFloorFinish();

void LoadDungeonMapFile(char *map_name, char *cfg_name, int gen_flag);

void MinimapDoorEnable(float *pos);

void LoadMonsterFile();

void LoadMonsterFile(int monster_no, int reset);

void StatusWarningSnd();

void BattleAreaBGMCtrl();

void PickupRandomItemCheckMax(TRESURE_BOX_FLOOR_INFO *table, int floor_index);

TRESURE_BOX_ITEM *PickupRandomItem(TRESURE_BOX_FLOOR_INFO *table, int floor_index, int rank);

int CheckObjectPutArea(float *pos);

void CreatMonsterFloorInfo(char *script, int size);
