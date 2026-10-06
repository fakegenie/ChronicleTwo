#pragma once

#include "common.h"

#include "menusys.hpp"
#include "mg_memory.hpp"
#include "savedata.hpp"
#include "scenesnd.hpp"
#include "memcard.hpp"

struct SaveIconSet {
    MC_ICON_DATA file[3];
};

STATIC_ASSERT(sizeof(SaveIconSet) == 0x78);

class CMenuPosDataForm;
class mgCTexture;
struct MENUFORMPARTS_TYPE;

#define OPTION_ITEM_MAX 20

#define OPTION_BUTTON_NUM 3

enum ManualMenuStep {
    MANUAL_STEP_SELECT   = 0,
    MANUAL_STEP_FADE_OUT = 1,
    MANUAL_STEP_PLAY     = 2,
    MANUAL_STEP_CLOSE    = 3,
    MANUAL_STEP_END      = 4,
};

enum SaveListPhase {
    SAVE_LIST_PHASE_SELECT       = 0,
    SAVE_LIST_PHASE_CONFIRM_SAVE = 1,
    SAVE_LIST_PHASE_SAVING       = 2,
    SAVE_LIST_PHASE_SAVE_DONE    = 3,
    SAVE_LIST_PHASE_NOTICE       = 6,
    SAVE_LIST_PHASE_MAKING_DIR   = 10,
    SAVE_LIST_PHASE_CONFIRM_LOAD = 50,
    SAVE_LIST_PHASE_LOADING      = 51,
    SAVE_LIST_PHASE_LOAD_DONE    = 52,
    SAVE_LIST_PHASE_LOAD_NOTICE  = 60,
};

enum SaveFormatPhase {
    SAVE_FORMAT_PHASE_ASK        = 0,
    SAVE_FORMAT_PHASE_FORMATTING = 10,
    SAVE_FORMAT_PHASE_DONE       = 20,
};

enum SaveMenuMode {
    SAVE_MENU_MODE_SAVE         = 0,
    SAVE_MENU_MODE_LOAD         = 1,
    SAVE_MENU_MODE_GYORACE_LOAD = 2,
};

enum SaveMenuPage {
    SAVE_MENU_PAGE_SLOT_SELECT = 0,
    SAVE_MENU_PAGE_FILE_LIST   = 1,
    SAVE_MENU_PAGE_CARD_INFO   = 2,
    SAVE_MENU_PAGE_FILE_READ   = 3,
    SAVE_MENU_PAGE_FORMAT      = 4,
    SAVE_MENU_PAGE_UNK_5       = 5,
    SAVE_MENU_PAGE_ERROR       = 6,
};

enum SubGameSavePhase {
    SUB_SAVE_SLOT_SELECT       = 0,
    SUB_SAVE_CARD_CHECK        = 1,
    SUB_SAVE_CARD_READY        = 2,
    SUB_SAVE_QUIT_ASK          = 10,
    SUB_SAVE_QUIT_ASK_LOAD     = 11,
    SUB_SAVE_OVERWRITE_ASK     = 100,
    SUB_SAVE_WRITING           = 101,
    SUB_SAVE_WRITE_DONE        = 102,
    SUB_SAVE_WRITE_FAILED      = 110,
    SUB_SAVE_WRITE_FAILED_FULL = 111,
    SUB_SAVE_SPACE_ASK         = 150,
    SUB_SAVE_DIR_MAKING        = 151,
    SUB_SAVE_FORMAT_ASK        = 160,
    SUB_SAVE_FORMATTING        = 161,
    SUB_SAVE_NO_DATA           = 165,
    SUB_SAVE_LOAD_ASK          = 200,
    SUB_SAVE_LOADING           = 201,
    SUB_SAVE_LOAD_DONE         = 202,
    SUB_SAVE_LOAD_MISSING      = 250,
    SUB_SAVE_CARD_ERROR        = 1000,
};

class CManualMenu : public CBaseMenuClass {
public:
    s32                select;
    s32                top;
    CScene::BGM_STATUS bgm_status;
    s32                pict_mode;
    s32                pict_num;
    s32                pict_page;
    mgCMemory          movie_stack;
    float              list_y;
    s32                cursor_jump;

    int KeyStep();

    void CalcTex();

    void CalcCursorPosition();
};

STATIC_ASSERT(sizeof(CManualMenu) == 0x178);

class CMenuOption : public CBaseMenuClass {
public:
    float               list_y;
    s32                 choice_num[OPTION_ITEM_MAX];
    MENUFORMPARTS_TYPE *button[OPTION_ITEM_MAX][OPTION_BUTTON_NUM];
    s32                *value[OPTION_ITEM_MAX];
    s32                 unk_2A4[OPTION_ITEM_MAX];
    SV_CONFIG_OPTION    config;
    SV_CONFIG_OPTION    config_backup;
    s32                 select;
    s32                 top;
    s32                 choice;
    s32                 cursor_jump;

    int KeyStep();

    void CalcTex();

    void DefaultButton(MENUFORMPARTS_TYPE **buttons);

    void EnableButton(MENUFORMPARTS_TYPE *button);

    void UpdateOptionForm();
};

STATIC_ASSERT(sizeof(CMenuOption) == 0x384);

class CSaveMenuClass : public CBaseMenuClass {
public:
    u8                  first_step;
    s32                 select;
    s32                 top;
    u8                  list_jump;
    s32                 slot;
    s32                 mode;
    s32                 page;
    s32                 phase;
    s32                 save_kind;
    s32                 dl_base;
    s32                 need_kb;
    s32                 save_kb;
    s32                 check_kb;
    s32                 card_ok;
    s32                 card_changed;
    s32                 chapter8_start;
    s32                 save_count;
    s32                 unk_154;
    CScene::BGM_STATUS  bgm_status;
    mgCTexture         *dl_tex;
    CMenuPosDataForm   *title_form;
    CMenuPosDataForm   *slot_form[2];
    CMenuPosDataForm   *cursor_form;
    CMenuPosDataForm   *list_form;
    CMenuPosDataForm   *scrlbar_form;
    MENUFORMPARTS_TYPE *scrlbar_parts[3];
    s32                 scrlbar_pos[2];

    void SetDlInfoMsg(int load, int show);

    void EnvSetSave(int kind);

    int KeyStep();
};

STATIC_ASSERT(sizeof(CSaveMenuClass) == 0x1A4);

void InitMenuReturnMsg(mgCMemory *stack);

void SetMenuReturnMsgCtrl(int on);

void DrawMenuReturnMsg();

int CheckOmakeVtuto(int no);

void MenuManualInit(mgCMemory *stack, int *tex_block, int open_type);

int MenuManualKey();

void MenuManualDraw();

void MenuOptionInit(mgCMemory *stack, int *tex_block, int open_type);

int MenuOptionKey();

void MenuOptionDraw();

void LocalFunc_AdjustScrlBar(MENUFORMPARTS_TYPE **parts, int *pos, int *size, int top, float line_num, float show_num, int jump);

void SaveFileListDraw(int &tex_block, float *pos, int alpha);

int GetDngMapNo(int dng_no);

void SaveMapInfo(int dng_no);

void ResetMapInfo();

void MenuSaveInit(mgCMemory *stack, int *tex_block, int open_type);

int MenuSaveKey();

void MenuSaveDraw();

void SubGameSaveInit(mgCMemory *stack, int *tex_block, int open_type);

int SubGameSaveKey();

void SubGameSaveDraw();

extern u8 MenuMapInfoSave[0xC];
