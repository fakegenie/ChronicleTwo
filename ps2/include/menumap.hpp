#pragma once

#include "common.h"

#include "menusys.hpp"

class CDC2Mes;
class mgCMemory;
class mgCTexture;
struct SPI_STACK;

enum {
    WMAP_AREA_POS_MAX = 8,
    WMAP_AREA_POS_LIST = 6,
    WMAP_NEAR_AREA_MAX = 0x40,
    WMAP_WAVE_LINE_NUM = 0x118,
};

enum WMAP_POS_TYPE {
    WMAP_POS_TYPE_GEORAMA = 4,
};

enum WORLD_MAP_MODE {
    WORLD_MAP_MODE_RUN = 0,
    WORLD_MAP_MODE_OPEN = 1,
    WORLD_MAP_MODE_CLOSE = 2,
};

enum WORLD_MAP_STEP {
    WORLD_MAP_STEP_AREA = 0,
    WORLD_MAP_STEP_POS = 1,
    WORLD_MAP_STEP_ASK = 2,
    WORLD_MAP_STEP_TREE_MAP = 3,
    WORLD_MAP_STEP_WAIT = 10,
};

enum WORLD_MOVE_RESULT {
    WORLD_MOVE_CONTINUE = 0,
    WORLD_MOVE_CLOSE = 1,
    WORLD_MOVE_JUMP = 2,
};

enum SPHIDA_MENU_PHASE {
    SPHIDA_MENU_TOP = 0,
    SPHIDA_MENU_EXIT = 1,
    SPHIDA_MENU_NAME_FADE = 99,
    SPHIDA_MENU_NAME_REGIST = 100,
    SPHIDA_MENU_PASSWORD = 200,
    SPHIDA_MENU_PASSWORD_VIEW = 201,
    SPHIDA_MENU_CLEAR = 300,
    SPHIDA_MENU_CLEAR_ASK = 301,
    SPHIDA_MENU_QUIT_ASK = 400,
};

struct WMAP_POS_DATA {
    char *name;
    s32 map_no;
    s16 loop_no;
    s16 area_no;
    s16 dng_no;
    s8 floor;
    s8 enable;
    s16 flag_no;
    s8 type;
    u8 unk_13;
};
STATIC_ASSERT(sizeof(WMAP_POS_DATA) == 0x14);

struct WMAP_AREA_DATA {
    s32 area_no;
    WMAP_POS_DATA *pos[WMAP_AREA_POS_MAX];
    s16 unk_24;
    u8 unk_26[0x2];
    s32 x;
    s32 y;
    s32 name_x;
    s32 name_y;
    s32 name_side;
    s32 enable;
    char *name;
    float dist;
    float dir_dot;
};
STATIC_ASSERT(sizeof(WMAP_AREA_DATA) == 0x4C);

class CWorldMapMenu : public CBaseMenuClass {
public:
    s32 area_no;
    u8 unk_114[0x4];
    u8 unk_118[0x50];
    u8 unk_168[0x4];
    s32 exit_wait;
    s16 map_type;
    u8 unk_172[0x2];
    s32 here_area;
    s32 view_only;
    mgCTexture *capture_tex;
    float back_alpha;
    u8 capture_view;
    u8 unk_185[0x3];
    mgCTexture *cursor_tex;
    u8 cursor_reset;
    u8 cursor_view;
    u8 unk_18e[0x2];
    float cursor_pos[2];
    mgCTexture *map_tex;
    mgCTexture *mark_tex;
    mgCTexture *anim_tex;
    mgCTexture *pulse_tex;
    float wave_x[WMAP_WAVE_LINE_NUM];
    float wave_y[WMAP_WAVE_LINE_NUM];
    float pulse_angle[2];
    float float_angle;
    s32 blink_cnt;
    short *mes_data;
    short *menu_mes_data;
    WMAP_AREA_DATA *select_area;
    s32 pos_num;
    WMAP_POS_DATA *select_pos;
    s32 near_num;
    WMAP_AREA_DATA *near_area[WMAP_NEAR_AREA_MAX];
    u8 name_view;
    u8 pos_list_view;
    u8 ask_view;
    u8 unk_b93;
    s16 pos_icon[WMAP_AREA_POS_MAX];

    CWorldMapMenu();

    void SetMsgBuffer();

    int KeyStep();

    void Draw();
};
STATIC_ASSERT(sizeof(CWorldMapMenu) == 0xBA4);

int _WMAP_POSNUM(SPI_STACK *stack, int argument_count);

int _WMAP_POS(SPI_STACK *stack, int argument_count);

int _WMAP_AREANUM(SPI_STACK *stack, int argument_count);

int _WMAP_AREA(SPI_STACK *stack, int argument_count);

void worldmap_analyze(mgCMemory *stack, char *script, int size);

int WorldMoveInit(mgCMemory *stack, int *tex_block, int open_type);

int WorldMoveKey();

void WorldMoveDraw();

void SphidaScreListUpdate(CDC2Mes *mes, int update);

void SphidaMenuInit(mgCMemory *stack, int *tex_block, int open_type);

int OmakeSfidaSelect(int key);

int SphidaMenuKey();

void SphidaMenuDraw();

void SphidaScoreViewInit(mgCMemory *stack, int *tex_block, int open_type);

int SphidaScoreViewKey();

void SphidaScoreViewDraw();
