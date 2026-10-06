#pragma once

#include "common.h"

#include <libvu0.h>

#include "mg_camera.hpp"
#include "gyoracesim.hpp"

class ClsMes;
struct SubGameInfo;

enum GYORACE_MODE {
    GYORACE_MODE_READY = 0,
    GYORACE_MODE_GATE_OPEN = 1,
    GYORACE_MODE_RACE = 2,
    GYORACE_MODE_FINISH = 3,
    GYORACE_MODE_GOAL_VIEW = 4,
    GYORACE_MODE_END = 5,
};

struct GYORACE_FISH_INF {
    int lane;
    int chara_no;
    int fish_no;
    int rank;
    u_int lap;
    int unk_14;
    float lap_start;
    int unk_1c;
    float time;
    float lap_time[2];
};
STATIC_ASSERT(sizeof(GYORACE_FISH_INF) == 0x2C);

struct GYORACE_RESULT {
    char name[0x18];
    float time;
    int fish_no;
    int race_class;
};
STATIC_ASSERT(sizeof(GYORACE_RESULT) == 0x24);

int sgInitGyoRace(SubGameInfo *info);

int sgLoopGyoRace(SubGameInfo *info);

void AutoCam(SubGameInfo *info);

int sgMapDrawGyoRace(SubGameInfo *info);

int sgCharaDrawGyoRace(SubGameInfo *info);

int sgEffectDrawGyoRace(SubGameInfo *info);

int sgSysDrawGyoRace(SubGameInfo *info);

int Jikkyou(SubGameInfo *info);

extern char *fish_name[18];

extern sceVu0FVECTOR cam_pos[5];

extern float race_cnt;

extern int race_proc_cnt;

extern int race_mode;

extern int time_max;

extern int camera_id;

extern int race_rank[2];

extern ClsMes *gyo_mes;

extern GYORACE_RESULT fish_game_data[6];

extern grRACE_INFO RaceInfo;

extern grRACE_PROGRESS old_prog[6];

extern mgCCamera camera0;

extern GYORACE_FISH_INF fish_inf[6];
