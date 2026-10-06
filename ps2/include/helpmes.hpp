#pragma once

#include "common.h"

struct HELP_MES_INFO {
    s32 show;
    s32 created;
    s32 time;
    s32 mes_no;
    s32 x;
    s32 y;
    s32 fukidashi_pos;
};

STATIC_ASSERT(sizeof(HELP_MES_INFO) == 0x1C);

void LoadHelpMes(u_long128 *buffer);

void CreateHelpMes(int tex_no);

void StepHelpMes();

void ShowOffOnceHelpMes();

void DrawHelpMes();

void ShowHelpMes(int mes_no, int time);

void ShowErrorHelpMes(int mes_no, int time);
