#pragma once

#include "common.h"
#include <libvu0.h>

class mgCMemory;

enum VLGR_MOTION {
    VLGR_MOTION_NONE       = -1,
    VLGR_MOTION_STAND      = 0,
    VLGR_MOTION_WALK       = 1,
    VLGR_MOTION_RUN        = 2,
    VLGR_MOTION_TALK       = 3,
    VLGR_MOTION_SIT        = 4,
    VLGR_MOTION_CAMERA_IN  = 5,
    VLGR_MOTION_CAMERA     = 6,
    VLGR_MOTION_CAMERA_OUT = 7,
    VLGR_MOTION_SPECIAL    = 8
};

enum VLGR_TIME {
    VLGR_TIME_NOON  = 0,
    VLGR_TIME_NIGHT = 1
};

enum VLGR_ROUTE_TYPE {
    VLGR_ROUTE_MOVE = 1,
    VLGR_ROUTE_WAIT = 2
};

enum VLGR_EX_STEP {
    VLGR_EX_STEP_START    = 1,
    VLGR_EX_STEP_IN       = 2,
    VLGR_EX_STEP_HOLD     = 3,
    VLGR_EX_STEP_OUT      = 4,
    VLGR_EX_STEP_RESTORE  = 5,
    VLGR_EX_STEP_END      = 6
};

class CVillagerPlaceInfo {
public:
    struct Node {
        Node *next;
        s32   type;
        s32   unk_8;
        s32   unk_c;
        union {
            sceVu0FVECTOR pos;
            struct {
                s32 motion_end;
                s32 time;
                s32 motion;
            } wait;
        };
    };

    sceVu0FVECTOR pos;
    sceVu0FVECTOR talk_offset;
    s32           map_no;
    s32           motion;
    s32           move_motion;
    float         move_speed;
    s32           no_shadow;
    Node         *route;
    s32           unk_38;
    s32           unk_3c;

    CVillagerPlaceInfo();

    Node *Add(mgCMemory *stack);
};
STATIC_ASSERT(sizeof(CVillagerPlaceInfo::Node) == 0x20);
STATIC_ASSERT(sizeof(CVillagerPlaceInfo) == 0x40);

class CVillagerPlace {
public:
    struct ProgressInfo {
        s32                 progress;
        s32                 after;
        CVillagerPlaceInfo *place[4][2];

        void Init();
    };

    s32           prog_num;
    ProgressInfo *prog_info;

    CVillagerPlace();
};
STATIC_ASSERT(sizeof(CVillagerPlace::ProgressInfo) == 0x28);
STATIC_ASSERT(sizeof(CVillagerPlace) == 0x8);

class CVillagerData {
public:
    s32                       chara_id;
    s32                       vlgr_id;
    s32                       unk_8;
    s32                       unk_c;
    s32                       unk_10;
    CVillagerPlaceInfo       *place;
    CVillagerPlaceInfo::Node *route;
    s32                       route_time;
    s32                       ex_mode;
    s32                       ex_step;
    s32                       ex_time;
    s32                       stay;
    s32                       req_motion;
    s32                       now_motion;
    s32                       motion_flag;
    s32                       motion_end;
    s32                       parts_mode;
    s32                       unk_44;
    s32                       unk_48;
    s32                       unk_4c;
    sceVu0FVECTOR             pos;
    sceVu0FVECTOR             rot;

    CVillagerData() {
        Initialize();
    }

    void Initialize();
};
STATIC_ASSERT(sizeof(CVillagerData) == 0x70);

class CVillagerMngr {
public:
    s32           stop;
    s32           data_num;
    s32           unk_8;
    s32           unk_c;
    CVillagerData data[32];

    CVillagerMngr() {
        Initialize();
    }

    void Initialize();

    CVillagerData *GetData(int no);

    void Stay(int no);

    void CancelStay(int no);

    void ExMode(int no);

    int SearchDataIDatCharaID(int chara_id);

    int Register(int vlgr_id, int chara_id, CVillagerPlaceInfo *place);

    void DeleteCharaID(int chara_id);

    CVillagerData *NewData();

    int CheckStay(int no);

    void Step();

    int GetAppearVlgr(int progress, int time, int map_no, int *vlgr_id, CVillagerPlaceInfo **place);

    int GetTalkRect(int chara_id, float *rect);
};
STATIC_ASSERT(sizeof(CVillagerMngr) == 0xE10);
