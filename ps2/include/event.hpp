#pragma once

#include "common.h"

class CCharacter2;
class ClsMes;
class CScene;
class mgCCamera;
class mgCMemory;

enum EVENT_REQUEST {
    EVENT_REQUEST_NONE = 0,
    EVENT_REQUEST_END = 1,
    EVENT_REQUEST_SUB_MODE = 2,
    EVENT_REQUEST_GOTO = 3,
    EVENT_REQUEST_INTERIOR = 4,
    EVENT_REQUEST_OUTSIDE = 7,
    EVENT_REQUEST_MAP_JUMP = 8,
    EVENT_REQUEST_LOAD_SCRIPT = 15,
    EVENT_REQUEST_EDIT_MODE = 17,
    EVENT_REQUEST_RESET_EDIT = 18,
    EVENT_REQUEST_RESTART_EDIT = 19,
};

enum EVENT_COMMAND_MODE {
    EVENT_COMMAND_RUN = 0,
    EVENT_COMMAND_UNK_1 = 1,
    EVENT_COMMAND_UNK_2 = 2,
    EVENT_COMMAND_SUB_MODE = 3,
    EVENT_COMMAND_DOOR = 4,
};

enum EVENT_SKIP_STATE {
    EVENT_SKIP_NONE = 0,
    EVENT_SKIP_ENABLED = 1,
    EVENT_SKIP_FADE_OUT = 2,
    EVENT_SKIP_WAIT_SOUND = 3,
};

extern CScene *EventScene;

int LoadNpcTalkMes(mgCMemory *memory);

void ResetNpcTalkMes();

int GetSquareEvent();

void InitEvent(CScene *scene);

void SetEventScript(char *program, char *unused, mgCMemory *memory);

int RunEvent(int entry, CScene *scene);

int EventDoorLoop(int frame, int use_scene_se);

int StartEventSyori();

void SkipEventStart();

void SkipEvent();

bool CheckEventSkip();

int EventLoop();

ClsMes *GetEventMessage(int no);

mgCCamera *GetActiveCamera();

CCharacter2 *GetCharacter(int no);
