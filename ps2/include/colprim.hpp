#pragma once

#include "common.h"

#include <libvu0.h>

class CScene;
class mgCFrame;

#define COLPRIM_MAX 64

#define DAMAGE_PARAM_MAX 115

#define DAMAGE_ELEMENT_MAX 8

enum DamageShape {
    DAMAGE_SHAPE_POINT = 1 << 0,
    DAMAGE_SHAPE_LINE  = 1 << 1,
    DAMAGE_SHAPE_TRAIL = 1 << 2,
};

enum DamageTarget {
    DAMAGE_TARGET_BY_OWNER = 1 << 0,
    DAMAGE_TARGET_PLAYER   = 1 << 1,
    DAMAGE_TARGET_MONSTER  = 1 << 2,
};

enum DamageKind {
    DAMAGE_KIND_MAX_MELEE      = 0x00,
    DAMAGE_KIND_MAX_GUN        = 0x01,
    DAMAGE_KIND_LASER_GUN      = 0x02,
    DAMAGE_KIND_GRENADE        = 0x03,
    DAMAGE_KIND_MONICA_MELEE   = 0x04,
    DAMAGE_KIND_MONICA_MAGIC   = 0x05,
    DAMAGE_KIND_CHECK          = 0x0A,
    DAMAGE_KIND_RIDEPOD_PUNCH  = 0x0B,
    DAMAGE_KIND_RIDEPOD_SWORD  = 0x0C,
    DAMAGE_KIND_RIDEPOD_GUN    = 0x0D,
    DAMAGE_KIND_MONSTER        = 0x14,
    DAMAGE_KIND_ITEM           = 0x19,
};

enum ColPrimCoordType {
    COLPRIM_COORD_VECTOR = 1,
    COLPRIM_COORD_FRAME  = 2,
};

struct DAMAGE_PARAM {
    char name[0x10];
    s8 shape;
    u8 unk_11[3];
    u_int  target;
    signed char   kind;
    u_char   unk_19[0x3];
    int  damage;
    signed char   multi_hit;
    u_char   unk_21;
    signed char   stagger;
    u_char   unk_23;
    short  critical_rate;
    u_short  hit_flags;
    int  unk_28;
    short  element[DAMAGE_ELEMENT_MAX];
    int  source_type;
    u_int  status;
    short  stun_time;
    short  hit_count;
};
STATIC_ASSERT(sizeof(DAMAGE_PARAM) == 0x48);

class CColPrim {
public:
    int           id;
    int           param_no;
    DAMAGE_PARAM *param;
    int           active;
    int           owner;
    int           unk_14;
    u_long           hit_mask;
    int           step_count;
    int           life;
    int           hit_num;
    int           attacker;
    u_int           coord_type;
    int           unk_34;
    mgCFrame     *frame[2];
    sceVu0FVECTOR pos[2];
    sceVu0FVECTOR old_pos[2];
    u_int           target;
    float         radius;
    int           damage;
    int           unk_8c;
    short           element[DAMAGE_ELEMENT_MAX];
    u_int           status;
    float         range;
    u_char            unk_a8[0x8];
    sceVu0FVECTOR origin;
    signed char            reversed;
    u_char            unk_c1[0xF];
    sceVu0FVECTOR revers_vec;
    short           gift[3];
    signed char            has_gift;
    u_char            unk_e7[0x9];
    sceVu0FVECTOR hit_vec;
    sceVu0FVECTOR hit_pos;

    int SetDamage(char *name, int owner);

    void SetCoord(float *pos, float radius);

    void SetCoord(float *start, float *end, float radius);

    void SetCoord(mgCFrame *frame, float radius);

    void SetCoord(mgCFrame *start, mgCFrame *end, float radius);

    int IsHit(CScene *scene, int chara_id);

    int IsReversVec(CColPrim *attack);

    void GetReversVec(float *vec);

    void DebugDraw();

    int Step();

    void Delete(int owner);

    void Initialize();
};
STATIC_ASSERT(sizeof(CColPrim) == 0x110);

class CColPrimMan {
public:
    CScene  *scene;
    CColPrim prim[COLPRIM_MAX];

    CColPrim *GetPrim();

    CColPrim *GetID2Prim(int id);

    int ActivePrimNum();

    void Delete(int owner);

    CColPrim *CheckHit(int chara_id);

    CColPrim *IsReversVec(CColPrim *attack);

    void Step();

    void Initialize(CScene *scene);
};
STATIC_ASSERT(sizeof(CColPrimMan) == 0x4410);

extern DAMAGE_PARAM Damage_Param_Table[DAMAGE_PARAM_MAX];
