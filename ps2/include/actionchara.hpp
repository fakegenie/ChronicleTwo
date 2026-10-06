#pragma once

#include "common.h"
#include <cstring>

#include <libvu0.h>

#include "character.hpp"
#include "dng_effect.hpp"
#include "dng_main.hpp"
#include "runscript.hpp"

class mgCFrame;
class mgCMemory;
class CScene;
class CMapParts;
class CColPrim;
class CEffectScriptMan;
class CActionChara;

enum ACTION_CHARA_TYPE {
    ACTION_CHARA_MAX     = 0,
    ACTION_CHARA_MONICA  = 1,
    ACTION_CHARA_ROBO    = 2,
    ACTION_CHARA_MONSTER = 3,
};

enum ACTION_MOVE_TYPE {
    ACTION_MOVE_HUMAN      = 0,
    ACTION_MOVE_ROBO_WALK  = 1,
    ACTION_MOVE_ROBO_TANK  = 2,
    ACTION_MOVE_ROBO_BIKE  = 3,
    ACTION_MOVE_MONSTER    = 3,
    ACTION_MOVE_ROBO_WALK2 = 4,
    ACTION_MOVE_ROBO_TANK2 = 5,
    ACTION_MOVE_ROBO_AIR   = 6,
    ACTION_MOVE_ROBO_AIR2  = 7,
};

enum ACTION_CHARA_KIND {
    ACTION_KIND_NONE   = 0,
    ACTION_KIND_PART   = 1,
    ACTION_KIND_SCRIPT = 2,
};

enum ACTION_HOLD_TYPE {
    ACTION_HOLD_NONE  = 0,
    ACTION_HOLD_ITEM  = 1,
    ACTION_HOLD_ENEMY = 3,
    ACTION_HOLD_STONE = 4,
};

enum ACTION_DAMAGE_REQ {
    ACTION_DAMAGE_REQ_NONE  = 0,
    ACTION_DAMAGE_REQ_SMALL = 1,
    ACTION_DAMAGE_REQ_LARGE = 2,
    ACTION_DAMAGE_REQ_DEAD  = 4,
    ACTION_DAMAGE_REQ_HOLD  = 7,
};

enum ACTION_PROG {
    ACTION_PROG_RUNNING      = -1,
    ACTION_PROG_INIT         = 100,
    ACTION_PROG_RESET        = 150,
    ACTION_PROG_MAIN         = 200,
    ACTION_PROG_DAMAGE_SMALL = 500,
    ACTION_PROG_HOLD         = 550,
    ACTION_PROG_DAMAGE_LARGE = 600,
    ACTION_PROG_DEAD         = 1400,
    ACTION_PROG_LAND         = 1500,
};

struct RUN_SCRIPT_ENV {
    CCharacter2 *item_chara;
    s32          texb;
};

STATIC_ASSERT(sizeof(RUN_SCRIPT_ENV) == 0x8);

struct ACTION_SW_EFFECT {
    s16   sword_no;
    char *chara;
    char *motion;
    float start;
    float end;
    char *frame0;
    char *frame1;
    s8    length;
    s8    hold_time;
    s8    fade_time;
    s8    wait;
};

STATIC_ASSERT(sizeof(ACTION_SW_EFFECT) == 0x20);

struct ACTION_DAMAGE {
    s8        use;
    char     *chara;
    mgCFrame *frame0;
    mgCFrame *frame1;
    float     radius;
    float     power_rate;
    float     start_frame;
    float     end_frame;
    char     *damage;
    CColPrim *prim;
};

STATIC_ASSERT(sizeof(ACTION_DAMAGE) == 0x28);

struct ACTION_OBJECT {
    mgCFrame     *frame;
    s32           unk_4[3];
    sceVu0FVECTOR pos;
};

STATIC_ASSERT(sizeof(ACTION_OBJECT) == 0x20);

struct ACTION_BODY_COL {
    s32   type;
    s32   object;
    float radius;
    s32   unk_c[5];
    s32   unk_20;
};

STATIC_ASSERT(sizeof(ACTION_BODY_COL) == 0x24);

struct ACTION_SOUND {
    s32   se_no;
    float start_frame;
    float end_frame;
    s32   unk_c;
    char *chara;
};

STATIC_ASSERT(sizeof(ACTION_SOUND) == 0x14);

struct ACTION_ACCELE {
    sceVu0FVECTOR accele;
    float         speed;
    float         move_speed;
    s32           unk_18;
    s32           unk_1c;
};

STATIC_ASSERT(sizeof(ACTION_ACCELE) == 0x20);

struct ACTION_ACCUME {
    mgCFrame *frame;
    s16       unk_4;
    s16       active;
};

STATIC_ASSERT(sizeof(ACTION_ACCUME) == 0x8);

struct ACTION_SHAKE {
    s16   time;
    float offset;
};

STATIC_ASSERT(sizeof(ACTION_SHAKE) == 0x8);

class CActionChara : public CCharacter2 {
public:
    sceVu0FVECTOR    old_pos;
    s32              chara_type;
    CActionChara    *parent;
    CActionChara    *next;
    CPalletAnime     script_pallet;
    s16              chara_kind;
    sceVu0FVECTOR    front_vec;
    s32              mask_flag;
    s32              attack_type;
    s32              move_type;
    float            max_speed;
    s32              unk_6b0;
    s16              unk_6b4;
    char            *script_buf;
    CRunScript       script;
    s16              prog_no;
    s16              prog;
    u32              pad_history;
    char            *default_motion;
    s16              hold_type;
    CMapParts       *hold_parts;
    mgCFrame        *hold_frame;
    s16              release_timing;
    s16              unk_72a;
    mgCFrame        *catch_frame;
    s16              catch_state;
    s16              no_hit_time;
    CPalletAnime     pallet[3];
    s16              battle_stance;
    float            battle_stance_rate;
    s16              shot_wait;
    s32              muteki_time;
    s8               menu_flag;
    s8               stand_flag;
    s8               dir_gun;
    s16              target_no;
    s16              lock_on;
    s32              murderous_time;
    s32              murderous;
    s32              now_status;
    ACTION_ACCELE    accele;
    sceVu0FVECTOR    add_vec;
    float            add_speed;
    float            add_decel;
    s32              add_time;
    float            stick_angle;
    s32              stick_time;
    float            target_dot;
    s32              unk_7c8;
    void            *accume_effect;
    ACTION_ACCUME    accume;
    s32              acumu_pad;
    CEffectScriptMan *effect_man;
    s8               throw_effect;
    ACTION_SW_EFFECT sw_effect[9];
    s8               sw_effect_num;
    MoveCheckInfo    move_check;
    ACTION_DAMAGE    damage[11];
    s8               damage_num;
    s32              damage_req;
    s32              unk_be0;
    s32              unk_be4;
    s32              damage_time;
    s32              melee_hit;
    s32              guard_flag;
    s8               stagger;
    s8               stagger_time;
    ACTION_SHAKE     shake;
    ACTION_OBJECT    object[8];
    ACTION_BODY_COL  body_col[16];
    sceVu0FVECTOR    blow_vec;
    float            blow_rate;
    float            blow_speed;
    float            blow_decel;
    s32              blow_time;
    ACTION_SOUND     sound[10];

    CActionChara() {
        memset(&move_check, 0, sizeof(move_check));
    }

    void ResetAccele();

    void ResetAction();

    void ResetScript();

    int CheckRunEvent();

    void SetMaskFlag(int flag, int on);

    ACTION_OBJECT *EntryObject(char *name, int no);

    void CalcCollision();

    ACTION_BODY_COL *EntryBodyCol(int object, float radius);

    ACTION_DAMAGE *EntryDamage2(char *frame0, char *frame1, char *damage, float radius, char *motion, float start, float end, char *chara);

    ACTION_DAMAGE *EntryDamage2(mgCFrame *frame0, mgCFrame *frame1, char *damage, float radius, char *motion, float start, float end, char *chara);

    void AllDeleteDamage();

    ACTION_SW_EFFECT *GetSwEffectPtr();

    void SetSoundInfoCopy();

    virtual void SetFadeFlag(int flag);

    virtual void SetFarDist(float dist);

    virtual void SetNearDist(float dist);

    virtual float GetCameraDist();

    virtual void Show(int show, int all);

    virtual int GetShow(char *chara);

    int CheckKeri(char *name, int kick);

    int CheckEnemyCatch(char *name);

    void ThrowItemObject();

    int UsedItemAction();

    void EntryThrowItem();

    void RemoveThrowItem();

    virtual void SetMotion(int no, int flags);

    virtual void SetMotion(char *name, int flags, int all);

    virtual void ResetMotion();

    virtual float GetNowFrameWait(char *chara);

    virtual float GetNowFrame(char *chara);

    virtual int CheckMotionEnd(char *chara);

    virtual int GetMotionStatus(char *chara);

    float GetWaitToFrame(char *motion, float rate, char *chara);

    virtual int Draw();

    virtual int DrawDirect();

    virtual int DrawShadowDirect();

    virtual void DrawEffect();

    virtual void StepEffect();

    CActionChara *SearchChara(char *name);

    mgCFrame *SearchObject(char *name);

    void ResetParent();

    int SetRef(CActionChara *part, char *name);

    float GetTargetDist(CScene *scene);

    void CollisionCheck(float *pos, float *velocity, float *out_velocity);

    void RockOn();

    int HumanMoveIF();

    int HumanShrowMoveIF();

    int HumanTameMoveIF();

    int HumanGunMoveIF(char *stand_motion, char *move_motion);

    int RoboWalkMoveIF(int mode);

    int RoboTankMoveIF(int mode);

    int RoboBikeMoveIF(int mode);

    int RoboAirMoveIF(int unk, int mode);

    int MonsterMoveIF();

    int CheckDamage();

    int LoadActionFile(char *data, int size, mgCMemory *memory);

    void InitScript();

    void SetHold();

    void RunScript(CScene *scene, RUN_SCRIPT_ENV *env);

    int CheckReleaseTimming(int hold_type);

    void StepParam();

    virtual void Step();

    virtual void ShadowStep();

    virtual void Initialize(mgCMemory *memory);

    virtual void Copy(CActionChara &dest, mgCMemory *memory);
};

STATIC_ASSERT(sizeof(CActionChara) == 0x1030);
