#pragma once

#include "common.h"

#include <libvu0.h>

#include "dng_event.hpp"
#include "mg_drawenv.hpp"

class CColFrame;
class CMiniMapSymbol;
class mgCDrawPrim;
class mgCMemory;
class mgCTexture;
struct CCPoly;
struct MDS_HEADER;

enum PowGageState {
    POWGAGE_STATE_IDLE = -1,
    POWGAGE_STATE_START = 0,
    POWGAGE_STATE_CHARGE = 1,
    POWGAGE_STATE_CHARGE_SET = 2,
    POWGAGE_STATE_IMPACT = 3,
    POWGAGE_STATE_JUDGE = 4,
};

enum PowGageCode {
    POWGAGE_CODE_NONE = -10,
    POWGAGE_CODE_JUST = 0,
    POWGAGE_CODE_LATE = 4,
    POWGAGE_CODE_NO_POWER = 5,
};

enum SphidaEvent {
    SPHIDA_EVENT_SHOT = 3000,
    SPHIDA_EVENT_NEAR_BALL = 3001,
    SPHIDA_EVENT_NEAR_BALL_LAST = 3002,
    SPHIDA_EVENT_OMAKE_AWAY = 3003,
};

struct GOLF_CLUB_DEF {
    float power;
    float unk_4;
    int   unk_8;
};
STATIC_ASSERT(sizeof(GOLF_CLUB_DEF) == 0xC);

class CPowGage {
public:
    float       pos_x;
    float       pos_y;
    mgCTexture *texture;
    float       power;
    int         safe_level;
    int         code;
    int         count;
    int         state;
    int         reverse;

    CPowGage() {
        Initialize();
    }

    void Initialize();

    void Step();

    void Draw();
};
STATIC_ASSERT(sizeof(CPowGage) == 0x24);

class CSphida {
public:
    CPowGage        pow_gage;
    int             tex_bank;
    int             play_flag;
    int             minimap_flag;
    int             mm_line_flag;
    int             status_flag;
    u_char              unk_38[0x8];
    sceVu0FVECTOR   mm_line_pos[5];
    sceVu0FVECTOR   pin_pos;
    sceVu0FVECTOR   ball_pos;
    int             pin_col;
    int             ball_col;
    int             par_count;
    u_char              unk_bc[0x4];
    CRedMarkModel   red_mark;
    u_char              unk_150[0x48];
    u_char              unk_198[6];
    u_char              unk_19e[0x42];
    sceVu0FVECTOR   map_view_pos;
    int             mini_level;
    float           spin_mark_pos_x;
    float           spin_mark_pos_y;
    int             club_no;
    float           carry;
    int             last_challenge;
    CColFrame      *col_model;
    int             omake_mode;
    int             unk_210[9];
    u_char              unk_234[0xC];

    CSphida();

    void Initialize();

    void SetUp(int tex_bank);

    void s17_SetUp(int tex_bank);

    void Omake_SetUp(int course, int tex_bank);

    int Step();

    void InitStatusSprite();

    void DrawStatusSprite();

    void DrawParCounter();

    void Draw();

    int SetCollisionModel(MDS_HEADER *model, mgCMemory *memory);

    int PickupCollision(float *pos, CCPoly *poly, mgVu0FBOX box, int max);

    void DrawMiniMapSymbol(CMiniMapSymbol *symbol);
};
STATIC_ASSERT(sizeof(CSphida) == 0x240);

extern GOLF_CLUB_DEF GolfClubDef[7];

extern CSphida *Sphida;

GOLF_CLUB_DEF *GetSphidaClubDef(int club_no);

void DPrimEnterSprite(mgCDrawPrim *prim, int u, int v, int tex_w, int tex_h, float x, float y, float w, float h);

void InitSphida();

CSphida *GetSphidaPtr();
