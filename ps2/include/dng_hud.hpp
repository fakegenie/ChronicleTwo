#pragma once

#include "common.h"

#include <cstring>
#include <libvu0.h>

#include "object.hpp"

class CCharacter2;
class CPreSprite;
class CScene;
class ClsMes;
class mgCObject;

enum LevelupInfoPhase {
    LEVELUP_INFO_PHASE_NONE = 0,
    LEVELUP_INFO_PHASE_APPEAR = 1,
    LEVELUP_INFO_PHASE_FLASH = 2,
    LEVELUP_INFO_PHASE_HOLD = 3,
    LEVELUP_INFO_PHASE_FADE = 4,
};

enum GekirinState {
    GEKIRIN_STATE_SHOW = 0,
    GEKIRIN_STATE_BREAK = 1,
    GEKIRIN_STATE_NONE = 2,
};

enum {
    ENEMY_LIFE_GAGE_GEKIRIN_MAX = 16,
};

enum DamageScorePhase {
    DAMAGE_SCORE_PHASE_APPEAR = 0,
    DAMAGE_SCORE_PHASE_FADE = 1,
};

enum DamageScore2Phase {
    DAMAGE_SCORE2_PHASE_NONE = 0,
    DAMAGE_SCORE2_PHASE_JUMP = 1,
    DAMAGE_SCORE2_PHASE_HOLD = 2,
    DAMAGE_SCORE2_PHASE_FADE = 3,
};

enum WarningGageLayout {
    WARNING_GAGE_LAYOUT_NONE = -1,
    WARNING_GAGE_LAYOUT_MAIN = 0,
    WARNING_GAGE_LAYOUT_ROBO = 1,
};

class CLevelupInfo {
public:
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
    s32 unk_0c;
    s32 unk_10;
    s32 unk_14;
    s32 unk_18;
    s32 unk_1c;
    float progress;
    s32 phase;
    s32 x;
    s32 y;
    s32 unk_30;
    s32 unk_34;

    void SetLevelUpInfo(int x, int y, int unk_30, int unk_34);

    void Draw();

    void Step();
};

STATIC_ASSERT(sizeof(CLevelupInfo) == 0x38);

class CPiyori {
public:
    mgCObject *target;
    float star_angle[3];
    float circle_angle;
    float height;
    float radius;
    s16 time;
    s16 se_wait;

    void Initialize();

    void Reset();

    void Set(mgCObject *target, float height, float radius, short time);

    void Set(mgCObject *target, short time);

    void Draw();

    void Step();
};

STATIC_ASSERT(sizeof(CPiyori) == 0x20);

class CGiftMark {
public:
    CCharacter2 *chara;
    float height;
    float angle;
    s32 active;
    s16 time;

    void Set(CCharacter2 *chara, float height);

    void Draw();

    void Step();

    void Initialize();
};

STATIC_ASSERT(sizeof(CGiftMark) == 0x14);

class CEnemyGekirin {
public:
    s8 state;
    s8 frame;

    void Draw(CPreSprite *sprite, int x, int y);

    void Step();
};

STATIC_ASSERT(sizeof(CEnemyGekirin) == 0x2);

class CEnemyLifeGage {
public:
    sceVu0FVECTOR pos;
    s32 max_hp;
    s32 hp;
    s32 screen;
    s32 view;
    float scale;
    CEnemyGekirin gekirin[ENEMY_LIFE_GAGE_GEKIRIN_MAX];

    void SetView(int view);

    void Set(float *pos, int max_hp, int hp, int gekirin_num, int screen);

    void Draw(int hide_gekirin);

    void Step();

    void ResetGekirin(int gekirin_num);

    void Initialize(int gekirin_num);
};

STATIC_ASSERT(sizeof(CEnemyLifeGage) == 0x50);

class CDamageScore {
public:
    s32 unk_00;
    u8 unk_04[0xC];
    sceVu0FVECTOR pos;
    char text[8];
    float bounce[8];
    s16 color[3];
    s16 alpha;
    s16 phase;
    s16 length;
    s32 unk_54;
    s32 unk_58;
    s32 digit_w;
    s32 digit_h;
    s32 digit_u;
    s32 digit_v;
    s32 unk_6c;
    s32 unk_70;
    s32 sprite_w;
    s32 sprite_h;
    s32 sprite_u;
    s32 sprite_v;
    s32 sprite;
    s32 active;

    CDamageScore() { memset(color, 0x80, sizeof(color)); }

    void SetValue(float *pos, int value);

    void SetColor(short r, short g, short b);

    void SetSprite(float *pos, int u, int v, int w, int h);

    void Draw();

    void Step();
};

STATIC_ASSERT(sizeof(CDamageScore) == 0x90);

class CDamageScore2 {
public:
    s32 chara_no;
    float height;
    float offset_y;
    float alpha;
    s32 value;
    char text[8];
    s32 phase;
    s32 length;
    float progress;

    void SetValue(int chara_no, int value, float height);

    void Draw(CScene *scene);

    void Step();
};

STATIC_ASSERT(sizeof(CDamageScore2) == 0x28);

class CLockOnModel : public CObjectFrame {
public:
    CScene *scene;
    ClsMes *mes;
    float angle;
    char *name;
    s32 unk_90;
    u8 unk_94[0xC];
    sceVu0FVECTOR pos;

    virtual void Draw();

    virtual void Step();

    virtual void Initialize(CScene *scene);

    void DrawMess(int tex_block);
};

STATIC_ASSERT(sizeof(CLockOnModel) == 0xB0);

class CWarningGage2 {
public:
    s32 warning[3];
    s32 time;
    float rate[3];
    s32 layout;

    void Step();

    void Draw();
};

STATIC_ASSERT(sizeof(CWarningGage2) == 0x20);
