#pragma once

#include "common.h"

class ClsMes;
class mgCMemory;

struct INIT_LOOP_ARG;

enum EditLoopMode {
    EDIT_LOOP_WALK = 1,
    EDIT_LOOP_EDIT = 2,
    EDIT_LOOP_WALK_MENU = 3,
    EDIT_LOOP_EDIT_PRE_MENU = 4,
    EDIT_LOOP_EDIT_MENU = 5,
    EDIT_LOOP_WAIT_READ = 6,
};

enum EditControlMode {
    EDIT_CONTROL_PLAYER = 1,
    EDIT_CONTROL_EVENT = 2,
    EDIT_CONTROL_EVENT_EDIT = 3,
    EDIT_CONTROL_DEBUG = 4,
};

int IsEditMode();

void SetDataPacket(int mode);

void EditInit(INIT_LOOP_ARG arg);

void EditExit();

int EditLoop();

int EditStep();

int EditDraw();

int BurnEditParts();

int EditMapJump(int map_no);

int EditGotoInterior(int map_no, int delete_villager);

int EditExitInterior(int arg);

void EditDataSave();

void EditDataLoad();

void KeepEditAnalyze();

int EditAnalyzeChanged();

extern u_long128 *read_buffer_end;

extern ClsMes EventMes1;

extern mgCMemory ScriptBuffer;

extern mgCMemory ScriptBuffer__2;
