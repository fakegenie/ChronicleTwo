#pragma once

#include "common.h"

#include <libvu0.h>

class mgCFrame;
class mgCTexture;
class mgCMemory;

extern mgCMemory BuffWorkData__2;

enum SHOT_STATE {
    SHOT_STATE_FREE = 0,
    SHOT_STATE_FIRED = 1,
    SHOT_STATE_FLYING = 2,
    SHOT_STATE_BURST = 3,
};

enum SHOT_DRAW_FLAG {
    SHOT_DRAW_MODEL = 1 << 0,
    SHOT_DRAW_TRAIL = 1 << 1,
};

class CRocketLauncher {
public:
    int           target_chara;
    u32           unk_04;
    u32           unk_08;
    u32           unk_0c;
    sceVu0FVECTOR pos;
    sceVu0FVECTOR start_pos;
    sceVu0FVECTOR target_pos;
    sceVu0FVECTOR dir;
    sceVu0FVECTOR trail[16];
    int           trail_len;
    int           trail_index;
    int           trail_timer;
    float         speed;
    int           col_prim_id;
    u32           draw_flags;
    int           homing_delay;
    int           homing_time;
    int           life;
    SHOT_STATE    state;
    mgCTexture   *trail_texture;
    mgCFrame     *model;
    int           tex_block;
    u32           unk_184;
    u32           unk_188;
    u32           unk_18c;

    void SetPos(float *start, float *target, float *direction);

    void Step();

    void Draw();

    void Initialize();
};
STATIC_ASSERT(sizeof(CRocketLauncher) == 0x190);

class CRocketLauncherMan {
public:
    CRocketLauncher rocket[24];

    CRocketLauncher *Get();

    void Draw();

    void Step();

    void Clear();

    void Initialize(mgCFrame *model, int tex_block, mgCTexture *trail_texture);
};
STATIC_ASSERT(sizeof(CRocketLauncherMan) == 0x2580);

class CMachineGun {
public:
    sceVu0FVECTOR start_pos[16];
    sceVu0FVECTOR velocity[16];
    sceVu0FVECTOR pos[16];
    s16           active[16];
    s16           col_prim_id[16];
    int           life[16];
    s16           index;
    u8            unk_382[0xE];

    void Set(float *start, float *direction);

    void Step();
};
STATIC_ASSERT(sizeof(CMachineGun) == 0x390);

class CLaserGun {
public:
    int           target_chara;
    u32           unk_04;
    u32           unk_08;
    u32           unk_0c;
    sceVu0FVECTOR pos;
    sceVu0FVECTOR start_pos;
    sceVu0FVECTOR target_pos;
    sceVu0FVECTOR dir;
    sceVu0FVECTOR trail[8];
    int           trail_len;
    int           trail_index;
    int           trail_timer;
    float         speed;
    float         speed_add;
    float         speed_max;
    int           col_prim_id;
    u32           draw_flags;
    int           homing_delay;
    int           homing_time;
    int           life;
    float         scale;
    float         scale_add;
    float         scale_max;
    s16           visual_code;
    s16           unk_10a;
    u32           unk_10c;
    sceVu0FVECTOR color;
    SHOT_STATE    state;
    mgCTexture   *trail_texture;
    mgCFrame     *model;
    int           tex_block;

    void SetPos(float *start, float *target, float *direction);

    void SetVisualCode(int code);

    void Step();

    void Draw();

    void Initialize();
};
STATIC_ASSERT(sizeof(CLaserGun) == 0x130);

class CLaserGunMan {
public:
    CLaserGun laser[16];

    CLaserGun *Get();

    void Draw();

    void Step();

    void Clear();

    void Initialize(mgCFrame *model, int tex_block, mgCTexture *trail_texture);
};
STATIC_ASSERT(sizeof(CLaserGunMan) == 0x1300);

enum PULL_ITEM_TYPE {
    PULL_ITEM_MONEY = 0,
    PULL_ITEM_WEAPON_EXP = 1,
    PULL_ITEM_GATE_KEY = 2,
    PULL_ITEM_MONEY_LARGE = 3,
    PULL_ITEM_ITEM = 4,
    PULL_ITEM_ITEM2 = 5,
    PULL_ITEM_BADGE = 6,
    PULL_ITEM_STOLEN = 7,
};

enum PULL_ITEM_STATE {
    PULL_ITEM_STATE_FREE = 0,
    PULL_ITEM_STATE_FALL = 1,
    PULL_ITEM_STATE_FLOAT = 2,
    PULL_ITEM_STATE_LAND = 3,
    PULL_ITEM_STATE_COLLECT = 4,
    PULL_ITEM_STATE_FADE = 5,
    PULL_ITEM_STATE_GOT = 6,
};

class CPullItem {
public:
    sceVu0FVECTOR   pos;
    sceVu0FVECTOR   velocity;
    sceVu0FVECTOR   draw_pos;
    s16             tex_u;
    s16             tex_v;
    s16             tex_w;
    s16             tex_h;
    float           width;
    float           height;
    s16             fall_time;
    s16             wait_time;
    s16             anim_frame;
    s16             unk_46;
    float           angle;
    float           bob_height;
    s16             can_get;
    s16             get_delay;
    float           pull_speed;
    float           pull_accel;
    float           get_range;
    s8              type;
    s8              glow;
    u8              unk_62[2];
    float           exp;
    s16             num;
    s16             exp_param;
    s16             item_no;
    s16             unk_6e;
    float           alpha;
    s8              wire_index;
    u8              unk_75[7];
    PULL_ITEM_STATE state;

    void Draw(mgCTexture *texture);

    void Step();

    void IsGet(float *player_pos);

    void SetItem(float *position, float *velo, int item_type);

    void Clear();

    void Initialize();
};
STATIC_ASSERT(sizeof(CPullItem) == 0x80);

class CPullItemManager {
public:
    CPullItem *list;
    int        num;

    CPullItem *GetList(int start);

    void Clear();
};
STATIC_ASSERT(sizeof(CPullItemManager) == 0x8);

enum ROBO_VOICE_STATUS {
    ROBO_VOICE_OFF = 0,
    ROBO_VOICE_OPEN = 1,
    ROBO_VOICE_OPENING = 2,
    ROBO_VOICE_STANDBY = 3,
    ROBO_VOICE_PLAY = 4,
    ROBO_VOICE_WAIT = 5,
};

class CRoboVoiceSystem {
public:
    s16 status;
    s16 unk_02;
    int stream_open;
    u32 unk_08;
    int voice_no;
    s16 unk_10;
    s16 wait_time;
    s16 play_time;
    s16 pause_time;

    void SetStatus(int voice, int value);

    void StartVoiceSystem();

    void StopVoice(int pause);

    void Step();
};
STATIC_ASSERT(sizeof(CRoboVoiceSystem) == 0x18);
