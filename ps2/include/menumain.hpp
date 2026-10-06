#pragma once

#include "common.h"

#include <libvu0.h>

#include "mg_camera.hpp"
#include "mg_memory.hpp"

class CDC2Mes;
class CFishAquarium;
class CMenuItemUse;
class CMenuKeyFunc;
class CMenuMoveItem;
class CMenuPosDataForm;
class CMenuSystemData;
class CSaveData;
class CSaveDataDungeon;
class CScene;
class CUserDataManager;
class ClsMes;
class mgCDrawPrim;
class mgCTexture;
struct SV_CONFIG_OPTION;

enum MenuModeID {
    MENU_MODE_MAIN_TOWN         = 0,
    MENU_MODE_MAIN_DUNGEON      = 1,
    MENU_MODE_ITEM              = 2,
    MENU_MODE_GEORAMA           = 3,
    MENU_MODE_CHARA_CHANGE      = 4,
    MENU_MODE_INVENT            = 5,
    MENU_MODE_WORLD_MOVE        = 6,
    MENU_MODE_OPTION            = 7,
    MENU_MODE_MANUAL            = 8,
    MENU_MODE_MONSTER_BOX       = 10,
    MENU_MODE_DNG_TREE_MAP      = 11,
    MENU_MODE_SHOP              = 12,
    MENU_MODE_SAVE              = 13,
    MENU_MODE_TITLE_SAVE        = 14,
    MENU_MODE_ITEM_SELECT       = 15,
    MENU_MODE_INVENT_DIRECT     = 16,
    MENU_MODE_CHAPTER           = 17,
    MENU_MODE_AQUA              = 18,
    MENU_MODE_REMOVAL           = 19,
    MENU_MODE_NAME_REGIST       = 20,
    MENU_MODE_GYORACE_FISH_SEL  = 21,
    MENU_MODE_NPC_QUEST_VIEW    = 22,
    MENU_MODE_COSTUME           = 23,
    MENU_MODE_MAIN_CHARA_BG     = 24,
    MENU_MODE_GYORACE           = 25,
    MENU_MODE_SPHIDA            = 26,
    MENU_MODE_MONSTER_BOOK      = 27,
    MENU_MODE_SUBGAME_SAVE      = 28,
    MENU_MODE_SPHIDA_SCORE_VIEW = 29,
    MENU_MODE_NUM               = 30,
};

enum MenuOpenType {
    MENU_OPEN_MAIN_TOWN               = 0,
    MENU_OPEN_MAIN_DUNGEON            = 1,
    MENU_OPEN_GEORAMA                 = 2,
    MENU_OPEN_DNG_TREE_MAP            = 3,
    MENU_OPEN_CHARA_CHANGE            = 4,
    MENU_OPEN_NAME_REGIST             = 5,
    MENU_OPEN_SHOP                    = 6,
    MENU_OPEN_SAVE                    = 7,
    MENU_OPEN_TITLE_SAVE              = 8,
    MENU_OPEN_USE_ITEM                = 9,
    MENU_OPEN_INVENT                  = 10,
    MENU_OPEN_CHAPTER                 = 11,
    MENU_OPEN_REMOVAL                 = 12,
    MENU_OPEN_WORLD_MOVE              = 13,
    MENU_OPEN_CHARA_CHANGE_DUNGEON    = 14,
    MENU_OPEN_GYORACE_FISH_SEL        = 15,
    MENU_OPEN_MAIN_TOWN_ITEM_OVER     = 16,
    MENU_OPEN_MAIN_DUNGEON_ITEM_OVER  = 17,
    MENU_OPEN_OPTION                  = 18,
    MENU_OPEN_WORLD_MOVE_B            = 19,
    MENU_OPEN_COSTUME                 = 20,
    MENU_OPEN_MAIN_CHARA_BG_DUNGEON   = 21,
    MENU_OPEN_USE_ITEM_B              = 22,
    MENU_OPEN_GYORACE                 = 23,
    MENU_OPEN_SPHIDA                  = 24,
    MENU_OPEN_MONSTER_BOOK            = 25,
    MENU_OPEN_SUBGAME_SAVE            = 26,
    MENU_OPEN_TITLE_SUBGAME_SAVE      = 27,
    MENU_OPEN_SPHIDA_SCORE_VIEW       = 28,
    MENU_OPEN_MAIN_CHARA_BG           = 29,
    MENU_OPEN_NUM                     = 30,
    MENU_OPEN_ITEM_OVER               = 16,
};

enum MenuLoopType {
    MENU_LOOP_TOWN    = 0,
    MENU_LOOP_DUNGEON = 1,
};

enum MenuInterStep {
    MENU_INTER_STEP_SELECT  = 0,
    MENU_INTER_STEP_OPEN    = 1,
    MENU_INTER_STEP_CLOSE   = 2,
    MENU_INTER_STEP_MESSAGE = 13,
};

enum MenuInterBGReadStep {
    MENU_INTER_BG_READ_WAIT = 0,
    MENU_INTER_BG_READ_BUSY = 1,
    MENU_INTER_BG_READ_DONE = 2,
};

struct MENU_INIT_ARG {
    mgCMemory *stack;
    mgCMemory *chara_stack;
    mgCMemory *base_chara_stack;
    s16 chara_tex_block;
    s16 unk_0E;
    s32 unk_10;
    s32 unk_14;
    CScene *scene;
    CUserDataManager *user_data;
    u_int *pack;
    int pack_size;
    int open_type;
    int tex_block_top;
    int tex_block_num;
    int mes_tex_block;
    int active_chara_no;
    int end_code;
    int result[5];
    s32 unk_54;
    int param[16];
};

STATIC_ASSERT(sizeof(MENU_INIT_ARG) == 0x98);

struct MENU_DRAW_ENV {
    mgCCamera camera;
    u8 unk_70[0x10];
    sceVu0FVECTOR ref;
    sceVu0FVECTOR pos;
    float speed;
    float projection;
    float old_projection;
    s32 unk_AC;
    sceVu0FVECTOR old_ambient;
    sceVu0FVECTOR ambient;
};

STATIC_ASSERT(sizeof(MENU_DRAW_ENV) == 0xD0);

struct MENU_ETC_INFO {
    int tex_block;
    mgCTexture *tex;
};

STATIC_ASSERT(sizeof(MENU_ETC_INFO) == 0x8);

class CMenuInter {
public:
    int select_no;
    int select_num;
    int next_mode;
    int *mode_list;
    s16 step;
    s8 bg_read_step;
    s8 bg_read_wait;
    s8 cursor_jump;
    u8 help_update;

    void Initialize(int unused);

    void InitEnd();

    void PushOk();

    int ReadBGTexture(int mode, int restart);
};

STATIC_ASSERT(sizeof(CMenuInter) == 0x18);

void MenuScreenBlackBeltSet(int flag);

int GetMenuLoopType();

int CheckTrushMenu();

CSaveDataDungeon *menu_GetSaveDataDungeon();

void *menu_GetBattleAreaScene();

CMenuSystemData *GetMenuSysData();

int CheckBitFlagMenu(int flag_no);

int CheckShortFlagMenu(int flag_no);

int CheckStartChapter8(CSaveData *save);

void InitMenuEtcSpecialFlag();

int SetMenuEtcFlag(int flag);

int GetMenuEtcFlag();

mgCDrawPrim *GetMenuPrim();

void MenuMainImageDataEnter(int tex_block);

void SetMenuFrameRate(int rate);

void SetMenuKeyCtrlEnv(int env);

int MenuMainInit(MENU_INIT_ARG *arg);

int MenuMainExit();

int MenuMainLoop();

int MenuMainKey();

void MenuMainDraw();

int NextMenuInit(int mode, mgCMemory *stack, int *tex_blocks);

void MenuCamInit(float speed);

char *GetMenuCfgFileName(int cfg_no, int unused);

short *GetMenuMainMessageBuffer();

u_int *GetMenuMainIMGPtr();

u_int *GetMenuMainPosCfgBuffer(int *size);

void SetCommonMenuModeID();

int *GetCommonMenuModeID();

int CursorSaveOptionState();

void ReturnMenuIntern(int out);

void MenuAreaBoardNameStep();

void MenuCommonBaseDataEnter(mgCMemory *stack, u_int *pack, int pack_size, int tex_block);

void MenuBaseTextureReEnter();

void CopyActiveItemAndWeapon(int chara_no, int unused);

int CopyActiveIconTexture(mgCTexture **tex, int chara_no, u_int *unused);

void BookshelfMessageMake(ClsMes *mes, int mes_offset, int item_no, int monster_no);

extern CScene *MenuMainScene;

extern CSaveData *MenuActiveSaveData;

extern CUserDataManager *MenuUserDataManPtr;

extern CMenuSystemData *MenuSystemDataPtr;

extern SV_CONFIG_OPTION *MenuConfigPtr;

extern CSaveDataDungeon *MenuSaveDataDungeonPtr;

extern CFishAquarium *MenuFishAquarium;

extern s16 MenuNowMapNo;

extern s16 MenuNowMapType;

extern float MenuNowTime;

extern s8 ItemOverFlowCheckFlag;

extern MENU_DRAW_ENV *MenuDrawEnv;

extern CMenuKeyFunc *MenuCommonInfo;

extern MENU_ETC_INFO MenuEtcInfo;

extern CMenuMoveItem *MenuMoveItemPtr;

extern CMenuPosDataForm *MenuFormMI2;

extern int MenuItemCommandCounter;

extern int menu_debug_flag;

extern int MenuPrevEndCode;

extern int MenuBGTextureBlock;

extern int MenuItemIconTextureBlock;

extern CMenuItemUse MenuItemUse;

extern mgCMemory MenuMainTextureReadBuf;

extern mgCMemory MenuSoundBuffer;

extern MENU_INIT_ARG MenuArg;
