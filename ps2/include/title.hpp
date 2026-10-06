#pragma once

#include "common.h"
#include "mg_memory.hpp"
#include "savedata.hpp"
#include "scenesnd.hpp"
#include <cstring>

struct INIT_LOOP_ARG;

enum TitleMode {
    TITLE_MODE_NONE         = -1,
    TITLE_MODE_RUSH_MOVIE   = 0,
    TITLE_MODE_TITLE        = 1,
    TITLE_MODE_MENU         = 2,
    TITLE_MODE_MC_CHECK     = 3,
    TITLE_MODE_COPYRIGHT    = 4,
    TITLE_MODE_HDD_INSTALL  = 5,
    TITLE_MODE_TITLE_RETURN = 6,
    TITLE_MODE_SUBGAME_MENU = 7,
    TITLE_MODE_LANG_SELECT  = 8,
};

enum TitlePhaseNo {
    TITLE_PHASE_WAIT          = -2,
    TITLE_PHASE_FADE_IN       = -1,
    TITLE_PHASE_PUSH_START    = 0,
    TITLE_PHASE_MENU          = 1,
    TITLE_PHASE_NEW_GAME      = 2,
    TITLE_PHASE_CONTINUE      = 3,
    TITLE_PHASE_OPTION        = 4,
    TITLE_PHASE_HDD_INSTALL   = 5,
    TITLE_PHASE_UNUSED_6      = 6,
    TITLE_PHASE_OMAKE_MENU    = 10,
    TITLE_PHASE_OMAKE         = 11,
    TITLE_PHASE_MC_MESSAGE    = 20,
};

enum TitleMenuItem {
    TITLE_MENU_NEW_GAME    = 0,
    TITLE_MENU_CONTINUE    = 1,
    TITLE_MENU_OMAKE       = 2,
    TITLE_MENU_OPTION      = 3,
    TITLE_MENU_HDD_INSTALL = 4,
};

enum TitleKeyResult {
    TITLE_KEY_NONE          = 0,
    TITLE_KEY_START_GAME    = 1,
    TITLE_KEY_RUSH_MOVIE    = 2,
    TITLE_KEY_CONTINUE      = 3,
    TITLE_KEY_OPTION        = 4,
    TITLE_KEY_NEW_GAME      = 5,
    TITLE_KEY_HDD_INSTALL   = 6,
    TITLE_KEY_DEMO_QUIT     = 10,
    TITLE_KEY_DEMO_TIMEOUT  = 11,
    TITLE_KEY_OMAKE         = 1000,
};

enum RushPhase {
    RUSH_PHASE_INIT     = 0,
    RUSH_PHASE_PLAY     = 1,
    RUSH_PHASE_FADE_OUT = 2,
    RUSH_PHASE_END      = 3,
};

enum CopyRightPhase {
    COPYRIGHT_PHASE_DELAY          = -10,
    COPYRIGHT_PHASE_TRIAL_WAIT     = -3,
    COPYRIGHT_PHASE_TRIAL_SHOW     = -2,
    COPYRIGHT_PHASE_TRIAL_FADE_OUT = -1,
    COPYRIGHT_PHASE_FADE_IN        = 0,
    COPYRIGHT_PHASE_SHOW           = 1,
    COPYRIGHT_PHASE_FADE_OUT       = 2,
    COPYRIGHT_PHASE_MOVIE_LOAD     = 3,
    COPYRIGHT_PHASE_MOVIE          = 4,
    COPYRIGHT_PHASE_MOVIE_END      = 5,
    COPYRIGHT_PHASE_END            = 6,
};

enum HddInstallPhase {
    HDD_PHASE_FADE_IN       = 0,
    HDD_PHASE_EXIT          = 1,
    HDD_PHASE_SELECT        = 2,
    HDD_PHASE_CONFIRM       = 3,
    HDD_PHASE_INSTALL       = 4,
    HDD_PHASE_RESULT        = 5,
    HDD_PHASE_CANCEL_ASK    = 6,
    HDD_PHASE_CANCEL        = 7,
    HDD_PHASE_CANCELLED     = 8,
    HDD_PHASE_IMAGE_FADE    = 9,
    HDD_PHASE_ERROR         = 10,
};

enum HddConfirmType {
    HDD_CONFIRM_INSTALL = 0,
    HDD_CONFIRM_EXIT    = 1,
};

enum TitleMcCheckPhase {
    TITLE_MC_PHASE_CARD_1  = 0,
    TITLE_MC_PHASE_FILES_1 = 1,
    TITLE_MC_PHASE_OMAKE_1 = 2,
    TITLE_MC_PHASE_CARD_2  = 3,
    TITLE_MC_PHASE_FILES_2 = 4,
    TITLE_MC_PHASE_OMAKE_2 = 5,
    TITLE_MC_PHASE_END     = 6,
};

enum TitleCameraPhaseNo {
    TITLE_CAMERA_APPROACH = 0,
    TITLE_CAMERA_HOLD     = 1,
    TITLE_CAMERA_ORBIT    = 2,
};

enum TitleLangPhase {
    TITLE_LANG_FADE_IN  = 0,
    TITLE_LANG_SELECT   = 1,
    TITLE_LANG_FADE_OUT = 2,
};

enum OmakeType {
    OMAKE_TYPE_DUNGEON = 0,
    OMAKE_TYPE_GYORACE = 1,
};

enum OmakePlayEnableBit {
    OMAKE_ENABLE_GYORACE = 0x01,
    OMAKE_ENABLE_DUNGEON = 0x02,
    OMAKE_ENABLE_COSTUME = 0x80,
};

struct TITLE_INFO {
    TITLE_INFO() {
        memset(this, 0, sizeof(TITLE_INFO));
        InitSV_CONFIG_OPTION(&config);
    }
    int mode;
    int next_mode;
    s16 select;
    s16 omake_select;
    s16 omake_dungeon;
    s16 omake_gyorace;
    s16 omake_num;
    s16 unk_12;
    float push_alpha;
    int wait_count;
    float title_alpha;
    float menu_alpha;
    float omake_alpha;
    float cursor_alpha;
    int cursor_count;
    float cursor_x;
    float cursor_y;
    int idle_count;
    u8 unk_3c[0xC];
    SV_CONFIG_OPTION config;
    mgCMemory chara_stack[5];
    CScene::BGM_STATUS bgm_status;
};
STATIC_ASSERT(sizeof(TITLE_INFO) == 0x194);

struct RUSH_INFO {
    int phase;
    s16 count;
    s16 movie_no;
    float push_alpha;
    int unk_c;
    int unk_10;
    s8 skipped;
};
STATIC_ASSERT(sizeof(RUSH_INFO) == 0x18);

struct HDD_INFO {
    HDD_INFO() : connect(0), app_install(0), install_space(0) {}
    int connect;
    int hdd_state;
    int app_install;
    int install_space;
    int unk_10;
    int installing;
    int result;
    int progress;
    void *work;
};
STATIC_ASSERT(sizeof(HDD_INFO) == 0x24);

int CheckOmakeFlag();

void InitOmakeEnv(int type, INIT_LOOP_ARG *arg, int *loop_no);

void TitleInit(INIT_LOOP_ARG arg);

void TitleExit();

int TitleLoop();

void TitleLangSelInit(mgCMemory *stack);

int TitleLangSelKey();

void TitleLangSelDraw();

extern int TitleSelectInit;

extern u8 MasterDebugModeOn;

extern u_long CostumeOptionEnv;
