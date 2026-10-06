#pragma once

#include "common.h"

enum grRACE_STATE {
    GR_RACE_STATE_NONE = 0,
    GR_RACE_STATE_SWIM = 1,
    GR_RACE_STATE_BATTLE = 2,
    GR_RACE_STATE_GOAL = 3,
};

enum grCHARA_BONUS_TYPE {
    GR_CHARA_BONUS_FRONT = 0,
    GR_CHARA_BONUS_BACK = 1,
    GR_CHARA_BONUS_NONE = 2,
    GR_CHARA_BONUS_RANDOM = 3,
};

struct grFISH_PARAM {
    char name[0x18];
    int  fish_no;
    int  affinity;
    int  bonus_type;
    int  power;
    int  stamina;
    int  speed[3];
    int  tactics;
    int  lane;
};
STATIC_ASSERT(sizeof(grFISH_PARAM) == 0x40);

struct grRACE_PROGRESS {
    float pos;
    int   lane;
    float lane_pos;
    s8    state;
    s8    battle;
    u_char    unk_e[2];
    int   battle_target;
    int   battle_hits;
};
STATIC_ASSERT(sizeof(grRACE_PROGRESS) == 0x18);

struct grRACE_INFO {
    u_int              seed;
    int              unk_4;
    int              fish_num;
    grFISH_PARAM     fish[6];
    int              step_max;
    grRACE_PROGRESS *progress[6];
    int              after_goal_step;
    int              rank[6];
    float            goal_time[6];
};
STATIC_ASSERT(sizeof(grRACE_INFO) == 0x1DC);

struct RACE_FISH_PARAM {
    float            speed[5];
    float            accel[5];
    u_char               unk_28[0x28];
    float            velocity;
    float            pos;
    int              lane;
    s8               state;
    s8               battle;
    u_char               unk_5e[2];
    int              battle_target;
    int              battle_hits;
    float            power;
    float            aggression;
    float            battle_urge;
    float            battle_time;
    float            boost;
    int              rank;
    float            rank_ratio[6];
    int              progress_num;
    grRACE_PROGRESS *progress;
};
STATIC_ASSERT(sizeof(RACE_FISH_PARAM) == 0xA0);

struct grFISH_DATA {
    int   fish_no;
    float power;
    float stamina;
    float speed[3];
    int   affinity;
};
STATIC_ASSERT(sizeof(grFISH_DATA) == 0x1C);

int grGyoRaceSimulate(grRACE_INFO *info);

int grGetFishProgress(grRACE_INFO *info, int fish, float time, grRACE_PROGRESS *progress);

int rand_prob(int percent);
