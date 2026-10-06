#pragma once

#include "common.h"

#include <libvu0.h>

#include "mg_frame.hpp"
#include "mg_tanime.hpp"
#include "prespr.hpp"

class mgCCamera;
class mgCMemory;
class CCharacter2;

#define CHILL_AFTER_HIT_PIECE_MAX 24

#define FIRE_AFTER_HIT_FLAME_MAX 14

#define FIRE_AFTER_HIT_TRAIL_MAX 6

#define TORNADO_PIECE_MAX 18

#define THUNDER_SPARK_MAX 48

#define MINI_EFF_PRIM_MAX 64

#define HEALING_LIGHT_MAX 16

#define AFTER_WIRE_POINT_MAX 16

#define WEAPON_ELEMENT_SPARK_MAX 32

#define WEAPON_ELEMENT_BOLT_MAX 16

enum WEAPON_ELEMENT_KIND {
    WEAPON_ELEMENT_FIRE = 0,
    WEAPON_ELEMENT_COLD = 1,
    WEAPON_ELEMENT_THUNDER = 2,
    WEAPON_ELEMENT_WIND = 3,
};

enum BATTLE_EFFECT_KIND {
    BATTLE_EFFECT_HIT = 0,
    BATTLE_EFFECT_FLUSH = 1,
    BATTLE_EFFECT_POWER_LINE = 2,
    BATTLE_EFFECT_DEAD = 3,
    BATTLE_EFFECT_CHARA = 4,
};

enum HIT_EFFECT_KIND {
    HIT_EFFECT_BOARD = 0,
    HIT_EFFECT_SPARK_SHORT = 1,
    HIT_EFFECT_SPARK_LONG = 2,
};

enum HEALING_EFFECT_MODE {
    HEALING_EFFECT_IDLE = 0,
    HEALING_EFFECT_SPENT = 1,
    HEALING_EFFECT_RECHARGE = 2,
    HEALING_EFFECT_OFF = 3,
};

enum SWORD_LUMINOUS_MODE {
    SWORD_LUMINOUS_OFF = 0,
    SWORD_LUMINOUS_FADE_IN = 1,
    SWORD_LUMINOUS_ON = 2,
    SWORD_LUMINOUS_FADE_OUT = 3,
};

enum MINI_EFF_PRIM_STATE {
    MINI_EFF_PRIM_FREE = 0,
    MINI_EFF_PRIM_RISING = 2,
};

enum SPARC_EFFECT_STATE {
    SPARC_EFFECT_OFF = 0,
    SPARC_EFFECT_FADE_IN = 1,
    SPARC_EFFECT_FADE_OUT = 2,
};

enum MAP_EFFECT_TYPE {
    MAP_EFFECT_NONE = -1,
    MAP_EFFECT_D01 = 0,
    MAP_EFFECT_D02 = 1,
    MAP_EFFECT_D03 = 2,
};

struct BattleEffectPrim {
    s32           kind;
    sceVu0FVECTOR pos;
    sceVu0FVECTOR velocity;
    float         size;
    float         speed;
    float         rate;
    s32           life;
    s32           life_max;
    float         alpha;
    float         alpha_step;
};

STATIC_ASSERT(sizeof(BattleEffectPrim) == 0x50);

struct BattleEffectChara {
    s32          unk_0;
    s32          unk_4;
    s8           unk_8;
    u8           unk_9[3];
    u8           unk_c[0xC];
    CCharacter2 *chara;
};

STATIC_ASSERT(sizeof(BattleEffectChara) == 0x1C);

struct CHILL_AFTER_HIT_PIECE {
    sceVu0FVECTOR pos;
    sceVu0FVECTOR velocity;
    float         size;
    float         damping;
    float         angle;
    float         spin;
    s8            rect;
    s8            move_time;
    s8            trail_num;
    s8            fade_speed;
    s16           alpha;
    float         trail[2][3];
};

STATIC_ASSERT(sizeof(CHILL_AFTER_HIT_PIECE) == 0x50);

class CChillAfterHit {
public:
    s32                   active;
    s32                   piece_num;
    float                 rate;
    sceVu0FVECTOR         center;
    CHILL_AFTER_HIT_PIECE piece[CHILL_AFTER_HIT_PIECE_MAX];

    CChillAfterHit() { Initialize(); }

    void Initialize();

    void SetPos(float *pos, float size, int strength);

    void Step();

    void Draw();
};

STATIC_ASSERT(sizeof(CChillAfterHit) == 0x7A0);

struct FIRE_AFTER_HIT_FLAME {
    sceVu0FVECTOR pos;
    float         velocity[3];
    float         size;
    s16           alpha;
    s16           age;
    s16           fade_speed;
    s8            trail_head;
    s8            delay;
};

STATIC_ASSERT(sizeof(FIRE_AFTER_HIT_FLAME) == 0x30);

struct FIRE_AFTER_HIT_TRAIL {
    float pos[3];
    float size;
    s16   alpha;
};

STATIC_ASSERT(sizeof(FIRE_AFTER_HIT_TRAIL) == 0x14);

class CFireAfterHit {
public:
    s32                  active;
    s32                  flame_num;
    s32                  time;
    float                rate;
    FIRE_AFTER_HIT_FLAME flame[FIRE_AFTER_HIT_FLAME_MAX];
    FIRE_AFTER_HIT_TRAIL trail[FIRE_AFTER_HIT_FLAME_MAX][FIRE_AFTER_HIT_TRAIL_MAX];

    CFireAfterHit() { Initialize(); }

    void Initialize();

    void SetPos(float *pos, float size, int strength);

    void Step();

    void Draw();
};

STATIC_ASSERT(sizeof(CFireAfterHit) == 0x940);

struct TORNADO_PIECE {
    sceVu0FVECTOR pos;
    float         scale;
    float         angle;
    float         alpha;
    float         rise;
    s8            life;
};

STATIC_ASSERT(sizeof(TORNADO_PIECE) == 0x30);

class CTornado {
public:
    mgCFrame     *model;
    s32           live_num;
    s32           active;
    float         rate;
    sceVu0FVECTOR center;
    TORNADO_PIECE piece[TORNADO_PIECE_MAX];

    void SetPos(float *pos, float size, float strength);

    void Draw();

    void Step();

    void Initialize();
};

STATIC_ASSERT(sizeof(CTornado) == 0x380);

struct THUNDER_SPARK {
    sceVu0FVECTOR pos;
    sceVu0FVECTOR velocity;
    float         angle;
    float         spin;
    float         life;
    float         scale;
    s8            frame;
};

STATIC_ASSERT(sizeof(THUNDER_SPARK) == 0x40);

class CThunder {
public:
    mgCFrame      frame;
    mgCFrameAttr  attr;
    u8            unk_1a0[0x10];
    THUNDER_SPARK spark[THUNDER_SPARK_MAX];
    s8            active;
    s8            live_num;
    float         rate;

    void SetPos(float *pos, float size, float strength);

    void Draw();

    void Step();

    void Initialize();
};

STATIC_ASSERT(sizeof(CThunder) == 0xDC0);

class CSparcEffect {
public:
    mgCFrame     *model[3];
    sceVu0FVECTOR pos;
    u8            unk_20[0x80];
    float         alpha_max;
    float         alpha;
    s8            pattern;
    s8            state;
    s8            color;

    void Draw();

    void Step();

    void Initialize();
};

STATIC_ASSERT(sizeof(CSparcEffect) == 0xB0);

class CMiniEffPrim {
public:
    sceVu0FVECTOR pos;
    s8            state;
    s8            color;
    float         alpha;
    float         size;

    void SetPrim(float *pos, int color);

    void Draw(CPreSprite *prim);

    int Step();

    void Initialize();
};

STATIC_ASSERT(sizeof(CMiniEffPrim) == 0x20);

class CMiniEffPrimMan {
public:
    CMiniEffPrim prim[MINI_EFF_PRIM_MAX];
    s32          active_num;
    u8           unk_804[0xC];
    CPreSprite   draw_prim;

    void CreatPrim(float *pos, int color);

    void Draw();

    void Step();

    void Initialize();
};

STATIC_ASSERT(sizeof(CMiniEffPrimMan) == 0x940);

struct CPalletAnime {
    s16 red;
    s16 green;
    s16 blue;
    s16 pulse_num;
    s16 elapsed;
    s16 duration;
    s16 repeats;

    void SetAnim(short red, short green, short blue, short pulse_num, short duration, short repeats);

    int CreatPallet(float *out, float *base);

    void Step();

    void Initialize();
};

STATIC_ASSERT(sizeof(CPalletAnime) == 0xE);

struct HEALING_LIGHT {
    sceVu0FVECTOR pos;
    float         radius;
    float         angle;
    float         bob_height;
    float         bob_phase;
    float         bob_speed;
    float         spin;
};

STATIC_ASSERT(sizeof(HEALING_LIGHT) == 0x30);

class CHealingEffectMan {
public:
    s16           active;
    HEALING_LIGHT light[HEALING_LIGHT_MAX];
    float         brightness;
    s16           mode;
    sceVu0FVECTOR center;

    void Draw(mgCCamera *camera);

    void Step();

    void SetMode(int mode);

    void Set(float *pos);

    void Initialize();
};

STATIC_ASSERT(sizeof(CHealingEffectMan) == 0x330);

class CSwordLuminous {
public:
    s8        mode;
    mgCFrame *tip_frame;
    mgCFrame *root_frame;
    u8        unk_c[4];
    float     fade;
    float     pulse;

    void Draw();

    void Step();
};

STATIC_ASSERT(sizeof(CSwordLuminous) == 0x18);

class CSWordAfterImage {
public:
    sceVu0FVECTOR *edge_point;
    sceVu0FVECTOR *back_point;
    float         *life;
    sceVu0FVECTOR *smooth_edge;
    sceVu0FVECTOR *smooth_back;
    float         *smooth_life;
    u8             unk_18[8];
    s32            edge_color[4];
    s32            back_color[4];
    s32            division;
    s32            smooth_num;
    s32            point_max;
    s32            point_num;
    s32            write_index;
    s32            head_index;
    s32            active;
    u8             unk_5c[4];

    void Draw();

    void CreatPointList();

    void AddPoint(float *edge, float *back, float life);

    void Step();

    void Initialize(mgCMemory *memory, int point_max, int division);
};

STATIC_ASSERT(sizeof(CSWordAfterImage) == 0x60);

class CAfterWire {
public:
    s32           mode;
    sceVu0FVECTOR point[AFTER_WIRE_POINT_MAX];
    s16           smooth_num;
    s16           point_num;
    s16           oldest;
    s16           write_index;
    s16           newest;

    CAfterWire() { mode = 0; }

    void SetMode(int mode);

    void SetPos(float *pos);

    void DrawWire(sceVu0FVECTOR *work);

    void StepWire();
};

STATIC_ASSERT(sizeof(CAfterWire) == 0x120);

extern CAfterWire afterWire[16];

class CHitEffectImage {
public:
    sceVu0FVECTOR     origin;
    sceVu0FVECTOR     direction;
    BattleEffectPrim *spark;
    s32               spark_num;
    s32               live_num;
    s32               spark_max;
    float             spread;
    float             slow;
    float             distance;
    float             gravity;
    float             sprite_size;
    s32               kind;
    u8                unk_48[8];
    mgRect<int>       tex_rect;

    CHitEffectImage();

    void SethitEffect(float *pos, float *direction, float spread, float distance, float slow, float gravity,
                      int life, int spark_num);

    void Step();

    void Draw();

    void DrawBord();

    void DrawSpark(float length);
};

STATIC_ASSERT(sizeof(CHitEffectImage) == 0x60);

class CFlushEffect {
public:
    mgCFrame     *follow;
    sceVu0FVECTOR pos;
    float         fade_speed;
    s16           alpha;
    float         size;
    float         grow;
    s16           active;
    s16           tex_u;
    s16           tex_v;
    s16           tex_size;
    void Draw();

    void Step();
};

STATIC_ASSERT(sizeof(CFlushEffect) == 0x40);

class CPowerLine {
public:
    mgCFrame         *source;
    sceVu0FVECTOR     pos;
    float             radius;
    float             prim_size;
    float             rise;
    u8                unk_2c[8];
    s32               duration;
    s32               elapsed;
    s32               prim_life;
    float             height;
    u8                unk_44[0xC];
    mgRect<int>       tex_rect;
    s32               color[4];
    BattleEffectPrim *prim;
    s32               prim_max;
    s32               live_num;
    s32               next;

    CPowerLine();

    void CreatPrim();

    void Step();

    void Draw();
};

STATIC_ASSERT(sizeof(CPowerLine) == 0x80);

class CDeadEffect {
public:
    sceVu0FVECTOR     pos;
    float             height;
    float             radius;
    float             size;
    s32               duration;
    s32               elapsed;
    BattleEffectPrim *prim;
    s32               prim_max;
    s32               live_num;
    s32               next;

    void SetDeadEffect(float *pos, float radius, float height, float size, int duration);

    void CreatPrim(int kind);

    void Step();

    void Draw();
};

STATIC_ASSERT(sizeof(CDeadEffect) == 0x40);

class CMapEffect_Sprite {
public:
    sceVu0FVECTOR pos;
    sceVu0FVECTOR target;
    sceVu0FVECTOR direction;
    float         bob_angle;
    float         bob_height;
    s32           life;
    s32           life_max;
    float         speed;
    s32           type;

    void Set(float *pos);

    void Step(mgCCamera *camera);

    void Draw(mgCCamera *camera, CPreSprite *prim);
};

STATIC_ASSERT(sizeof(CMapEffect_Sprite) == 0x50);

class CMapEffectsManeger {
public:
    s32                spawn_wait;
    s32                live_num;
    s32                sprite_num;
    CMapEffect_Sprite *sprite;
    s32                type;

    void Init_LightBoll(mgCMemory *memory, int sprite_num);

    void Step(mgCCamera *camera);

    void Draw(mgCCamera *camera);
};

STATIC_ASSERT(sizeof(CMapEffectsManeger) == 0x14);

class BattleEffectMan {
public:
    BattleEffectPrim  *hit_prim;
    CHitEffectImage   *hit;
    s32                hit_num;
    s32                hit_next;
    CFlushEffect      *flush;
    s32                flush_num;
    s32                flush_next;
    BattleEffectPrim  *power_prim;
    CPowerLine        *power;
    s32                power_num;
    s32                power_next;
    BattleEffectPrim  *dead_prim;
    CDeadEffect       *dead;
    s32                dead_num;
    s32                dead_next;
    CCharacter2       *chara;
    BattleEffectChara *chara_slot;
    s32                chara_num;

    int AllocEffect(int kind, mgCMemory *memory, int num);

    void Step();

    void Draw();
};

STATIC_ASSERT(sizeof(BattleEffectMan) == 0x48);

class CWeaponElement {
public:
    sceVu0FVECTOR *origin;
    sceVu0FVECTOR  fire_pos;
    sceVu0FVECTOR  offset[WEAPON_ELEMENT_SPARK_MAX];
    sceVu0FVECTOR  velocity[WEAPON_ELEMENT_SPARK_MAX];
    float          size[WEAPON_ELEMENT_SPARK_MAX];
    float          shrink[WEAPON_ELEMENT_SPARK_MAX];
    float          alpha[WEAPON_ELEMENT_SPARK_MAX];
    float          spread;
    s16            kind;
    float          power;
    s16            on;
    s16            count;
    float          scale;
    float          spin[WEAPON_ELEMENT_SPARK_MAX];
    float          spin_speed[WEAPON_ELEMENT_SPARK_MAX];
    s16            spawn_delay_max;
    s16            spawn_delay;
    s16            spawn_budget;
    s16            fading[WEAPON_ELEMENT_SPARK_MAX];
    s16            frame[WEAPON_ELEMENT_SPARK_MAX];
    s16            frame_timer;
    s16            bolt_head[WEAPON_ELEMENT_BOLT_MAX];
    s16            bolt_tail[WEAPON_ELEMENT_BOLT_MAX];
    s16            bolt_timer[WEAPON_ELEMENT_BOLT_MAX];
    s16            bolt_frame[WEAPON_ELEMENT_BOLT_MAX];
    s16            bolt_count;

    void Initialize();

    void Set(sceVu0FVECTOR *origin, float *position, float power, int kind, float spread);

    void Step();

    void Draw();

    void Init_Cold(float *position);

    void Step_Cold();

    void Draw_Cold();

    void Init_Wind(float *position);

    void Step_Wind();

    void Draw_Wind();

    void Init_Fire(float *position);

    void Step_Fire();

    void Draw_Fire();

    void Init_Thunder(float *position);

    void Step_Thunder();

    void Draw_Thunder();
};

STATIC_ASSERT(sizeof(CWeaponElement) == 0x7C0);

int CreatSmoothPass(sceVu0FVECTOR *out, sceVu0FVECTOR *ring, int point_num, int division, int start, int ring_size);

float unitRotation(mgCFrame *frame, float target, float divide);

int iRand(int limit);

float fRand(float limit);

int LocalTransWorldPrimPos(int (*corners)[4], float *pos, float width, float height, float angle);
