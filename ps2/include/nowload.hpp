#pragma once

#include "common.h"

#include "mg_memory.hpp"

class CScene;

enum NowLoadingStep {
    NOW_LOADING_STEP_NONE  = -1,
    NOW_LOADING_STEP_START = 0,
    NOW_LOADING_STEP_DRAW  = 1,
    NOW_LOADING_STEP_END   = 2,
};

struct NowLoadingInfo {
    int       tex_block;
    int       unk_4;
    mgCMemory memory;
    int       step_count;

    NowLoadingInfo();
};

STATIC_ASSERT(sizeof(NowLoadingInfo) == 0x3C);

struct PAUSE_INFO {
    int     event_skip;
    CScene *scene;
};

STATIC_ASSERT(sizeof(PAUSE_INFO) == 0x8);

void SwitchNowLoadingThread();

void CancelNowLoading();

void CreateNowLoading(NowLoadingInfo *info);

void NowLoadingBarStep();

void NowLoadingBarSteEnd();

void DeleteNowLoading();

int InitPauseData();

int InitPause(int tex_block);

int PauseEnable(int enable);

int GetPauseFlag();

int PauseStart(PAUSE_INFO *info);

void PauseCancel();

void PauseEnd();

int PauseLoop();

void PauseCount();

void SCElogoFade(int fade_out, mgCMemory *memory);
