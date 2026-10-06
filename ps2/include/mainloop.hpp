#pragma once

#include "common.h"
#include "gamepad.hpp"
#include "sound.hpp"
#include <cstring>

class CFont;
class CScene;
class CSaveData;
class CSubGameData;
class CPadControl;
class mgCMemory;
class mgCTexture;

enum MainLoopMode {
    LOOP_MENU          = 0,
    LOOP_EDIT          = 1,
    LOOP_DUNGEON       = 2,
    LOOP_TITLE         = 3,
    LOOP_CHARA_VIEWER  = 4,
    LOOP_TEX_VIEWER    = 5,
    LOOP_MAP_VIEW      = 6,
    LOOP_SOUND_VIEWER  = 7,
    LOOP_MOVIE_VIEW    = 8,
    LOOP_SV_CONV_VIEW  = 9,
    LOOP_MODE_NUM      = 10,
};

enum LanguageCodeNo {
    LANG_JAPANESE = 0,
    LANG_ENGLISH  = 1,
    LANG_FRENCH   = 2,
    LANG_GERMAN   = 3,
    LANG_ITALIAN  = 4,
    LANG_SPANISH  = 5,
    LANG_CHINESE  = 6,
    LANG_KOREAN   = 7,
};

enum MainCaptureMode {
    CAPTURE_OFF         = 0,
    CAPTURE_RECORD      = 1,
    CAPTURE_PLAY        = 2,
    CAPTURE_PLAY_SCREEN = 3,
    CAPTURE_MODE_NUM    = 4,
};

enum DebugMenuMode {
    DEBUG_MENU_TOP            = 0,
    DEBUG_MENU_MAP_SELECT     = 1,
    DEBUG_MENU_EVENT_SELECT   = 2,
    DEBUG_MENU_SAVE_DATA_EDIT = 3,
};

enum DebugMenuRow {
    DEBUG_ROW_EVENT_SELECT = 0,
    DEBUG_ROW_LANGUAGE     = 9,
    DEBUG_ROW_ITEM_SET     = 10,
    DEBUG_ROW_SAVE_DATA    = 11,
    DEBUG_ROW_LOAD_CFG     = 12,
    DEBUG_ROW_CONVERT_SAVE = 13,
    DEBUG_ROW_NUM          = 14,
};

enum PauseMenuStep {
    PAUSE_MENU_OPEN     = 0,
    PAUSE_MENU_SELECT   = 1,
    PAUSE_MENU_FADE_OUT = 2,
    PAUSE_MENU_END      = 3,
};

enum PauseMenuResult {
    PAUSE_MENU_STAY   = 0,
    PAUSE_MENU_RESUME = 1,
    PAUSE_MENU_QUIT   = 2,
};

enum MasterDebugCodeValue {
    MASTER_DEBUG_CODE = 0x5D44,
};

struct INIT_LOOP_ARG {
    INIT_LOOP_ARG() { memset(this, 0, sizeof(*this)); }
    int map_no;
    s8 unk_4[0x40];
    int floor_no;
    int event_no;
    int unk_4c;
};
STATIC_ASSERT(sizeof(INIT_LOOP_ARG) == 0x50);

struct DEBUG_INFO {
    DEBUG_INFO() { memset(this, 0, sizeof(*this)); }
    int debug_camera;
    int chara_move;
    int georama_debug;
    int param_off;
    int invent_debug;
};
STATIC_ASSERT(sizeof(DEBUG_INFO) == 0x14);

struct PAD_TABLE_ENTRY {
    int no;
    int trigger;
    int button;
};
STATIC_ASSERT(sizeof(PAD_TABLE_ENTRY) == 0xC);

struct ANALOG_TABLE_ENTRY {
    int no;
    int axis;
};
STATIC_ASSERT(sizeof(ANALOG_TABLE_ENTRY) == 0x8);

typedef void (*LOOP_INIT_FUNC)(INIT_LOOP_ARG arg);

typedef int (*LOOP_MAIN_FUNC)();

typedef void (*LOOP_EXIT_FUNC)();

extern LOOP_INIT_FUNC LoopInit[LOOP_MODE_NUM];

extern LOOP_MAIN_FUNC LoopMain[LOOP_MODE_NUM];

extern LOOP_EXIT_FUNC LoopExit[LOOP_MODE_NUM];

extern int MainThreadPriority;

extern u_long128 *read_buffer;

extern u32 SystemSND_ID;

extern CSound CSnd;

extern int DebugFlag;

extern int DefStartEventNo;

extern int LanguageCode;

extern int OmakeFlag;

extern int MasterDebugCode;

extern CGamePad GamePad;

extern CGamePad GamePad__2;

extern CPadControl PadCtrl;

extern DEBUG_INFO DebugInfo;

CFont *GetDebugFont();

int GetCaptureMode();

int GetSystemSndID();

CScene *GetMainScene();

CSaveData *GetSaveData();

CSubGameData *GetSubGameSaveData();

void InitSaveData();

int GetVramTopAddress();

mgCMemory *GetMainStack();

void NextLoop(int loop_no, INIT_LOOP_ARG arg);

int GetNowLoopNo();

INIT_LOOP_ARG *GetNowInitArg();

void cat_start();

void cat_end();

void SetTextureTable(int block_max, int texture_max, mgCMemory *memory);

void PlayTimeCount(int enable);

int GetPlayTimeCountFlag();

void LanguageChange(int language, u_long128 *buffer);

void MainLoop();

mgCTexture *GetFontTexture(int index);

void LoadFontTexture();

void ReLoadFontTexture(int block);

void demQuit();

void demoQuitTimeOut();

void demoAttractInterrupted();

void demoAttractComplete();

void FadeOutForE3();

int TimeLimitCheck();

void InitPauseMenu(int value);

int PauseMenu();

void LoadGameConfig(char *file_name);
