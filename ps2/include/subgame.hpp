#pragma once

#include "common.h"

class CScene;
class mgCMemory;

enum SUBGAME_TYPE {
    SUBGAME_NONE = 0,
    SUBGAME_FISHING = 1,
    SUBGAME_GYORACE = 2,
    SUBGAME_BUGGY = 3,
    SUBGAME_UNUSED = 4,
    SUBGAME_MAX = 5,
};

enum SG_PLAY_VOICE_STEP {
    SG_PLAY_VOICE_IDLE = 0,
    SG_PLAY_VOICE_OPEN = 1,
    SG_PLAY_VOICE_OPENING = 2,
    SG_PLAY_VOICE_STANDBY = 3,
    SG_PLAY_VOICE_READY = 4,
    SG_PLAY_VOICE_PLAYING = 5,
};

enum SUBGAME_CLEAR {
    SUBGAME_CHARA_BASE = 0x40,
    SUBGAME_CHARA_NUM = 0x28,
    SUBGAME_EFFECT_SLOT = 7,
};

struct SubGameInfo {
    CScene *scene;
    int texb;
    int texb_num;
    int unk_c;
    mgCMemory *menu_buff;
    int dungeon;
    int no_map_event;
    int record_check;
    int rod_no;
    int esa_no;
    int keep_bgm;
    mgCMemory *load_buff;

    SubGameInfo() {
        keep_bgm = 0;
        dungeon = 0;
        scene = 0;
        menu_buff = 0;
        load_buff = 0;
        no_map_event = 0;
        record_check = 0;
    }
};

STATIC_ASSERT(sizeof(SubGameInfo) == 0x30);

class sgCPlayVoice {
public:
    int step;
    int file_no;
    int play;
    float vol_r;
    float vol_l;

    sgCPlayVoice() {
        step = SG_PLAY_VOICE_IDLE;
        play = 0;
        vol_l = 1.0f;
        vol_r = 1.0f;
    }

    void Open(int file_no);

    void SetVol(float left, float right);

    void Play();

    int Step();

    void Close();
};

STATIC_ASSERT(sizeof(sgCPlayVoice) == 0x14);

void InitSubGame(CScene *scene);

int SubGameRunning();

int GetSubGameNo();

SubGameInfo *GetNowSubGameInfo();

int sgMenuOpenEnable();

void sgSetMenuOpenEnableFlag(int enable);

int sgGetItemOver();

void sgGetItemOverReset();

void sgGetItemOverFlagOn();

int sgInitSubGame(int type, SubGameInfo *info);

int sgLoopSubGame();

int sgLoopSubGame2();

int sgExitSubGame();

int sgRestartSubGame(SubGameInfo *info);

int sgBreakSubGame();

int sgDrawSubGameMap();

int sgDrawSubGameCharaShadow();

int sgDrawSubGameChara();

int sgDrawSubGameEffect();

int sgDrawSubGameSystem();
