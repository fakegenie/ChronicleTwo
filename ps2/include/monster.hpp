#pragma once

#include "common.h"

#include <libvu0.h>

#include "actionchara.hpp"
#include "dng_hud.hpp"
#include "dng_main.hpp"
#include "mg_memory.hpp"
#include "runscript.hpp"
#include "scenesnd.hpp"

class CActiveMonster;
class CColPrim;
class CEffectScriptMan;
class CMapParts;
class CMapPiece;
class CMiniMapSymbol;
class CScene;
class mgCFrame;

enum MONSTER_MAN_SIZE {
    MONSTER_ACTIVE_MAX = 24,
    MONSTER_REFER_MAX  = 12,
    MONSTER_LOCATE_MAX = 32,
    MONSTER_VAR_MAX    = 8,
    MONSTER_VAR2_MAX   = 32,
    MONSTER_SHARE_MAX  = 128
};

enum ACTIVE_MONSTER_STATE {
    ACTIVE_MONSTER_NONE = 0,
    ACTIVE_MONSTER_LIVE = 1,
    ACTIVE_MONSTER_DEAD = 3
};

enum MONSTER_VIEW {
    MONSTER_VIEW_INIT     = 0,
    MONSTER_VIEW_OUT      = 1,
    MONSTER_VIEW_IN       = 2,
    MONSTER_VIEW_FADE_IN  = 3,
    MONSTER_VIEW_FADE_OUT = 4
};

enum MONSTER_ATTRIB {
    MONSTER_ATTRIB_NO_LOCK_ON   = 0x1,
    MONSTER_ATTRIB_UNK_2        = 0x2,
    MONSTER_ATTRIB_SET_VELOCITY = 0x4,
    MONSTER_ATTRIB_NO_MAP_HIT   = 0x8,
    MONSTER_ATTRIB_NO_BODY_HIT  = 0x10,
    MONSTER_ATTRIB_NO_DAMAGE    = 0x20,
    MONSTER_ATTRIB_QUICK_DEAD   = 0x40,
    MONSTER_ATTRIB_UNK_80       = 0x80,
    MONSTER_ATTRIB_SKIP_GROUND  = 0x100,
    MONSTER_ATTRIB_ALWAYS_VIEW  = 0x200
};

enum MONSTER_STATUS_ATTR {
    MONSTER_STATUS_POISON = 0x1,
    MONSTER_STATUS_SLOW   = 0x2,
    MONSTER_STATUS_UNK_8  = 0x8,
    MONSTER_STATUS_UNK_20 = 0x20
};

enum MONSTER_PROG {
    MONSTER_PROG_RUNNING  = -1,
    MONSTER_PROG_INIT     = 100,
    MONSTER_PROG_MAIN     = 200,
    MONSTER_PROG_STATUS   = 400,
    MONSTER_PROG_DAMAGE   = 500,
    MONSTER_PROG_KNOCK    = 600,
    MONSTER_PROG_GUARD    = 700,
    MONSTER_PROG_ESCAPE_0 = 800,
    MONSTER_PROG_ESCAPE_1 = 900,
    MONSTER_PROG_DEAD     = 1000,
    MONSTER_PROG_LAND     = 1200,
    MONSTER_PROG_PIYORI   = 1400
};

enum MONSTER_LINK {
    MONSTER_LINK_NONE  = 0,
    MONSTER_LINK_PARTS = 1,
    MONSTER_LINK_PIECE = 2
};

enum MONSTER_SCOOP_TYPE {
    MONSTER_SCOOP_MOTION = 0x1,
    MONSTER_SCOOP_ALWAYS = 0x2
};

struct BASE_MONSTER_TBL {
    s16   id;
    s16   grade;
    char  name[32];
    char  model[16];
    char  script[16];
    s16   gift_type;
    s32   sound_no;
    s32   unk_4c;
    s32   life;
    s8    user_mons_id;
    u16   reward_exp;
    u16   reward_money;
    u16   unk_5a;
    float whp;
    u16   gekirin_num;
    s8    guard_rate;
    s8    escape_rate0;
    s8    escape_rate1;
    u16   attack;
    u8    defense;
    s8    stagger;
    s8    boss;
    s8    sw_effect_num;
    s16   element_resist[8];
    s16   ext_param[12];
    u32   flags;
    u32   unk_98;
    s32   next_id;
    union {
        s16 drop_item[3];
        s16 drop_items[3];
    };
    u32   resist_attr;
    s16   status_chance;
    s16   ratio_damage_rate;
    s8    area_no;
    s16   memo_index;
    s16   unk_b4;
};

STATIC_ASSERT(sizeof(BASE_MONSTER_TBL) == 0xB8);

struct MONSTER_SCOOP {
    s32   type;
    char *motion;
    float start;
    float end;
    s32   no;
    s32   ok;
};

STATIC_ASSERT(sizeof(MONSTER_SCOOP) == 0x18);

struct MONSTER_STATUS {
    u32 attr;
    s16 poison_count;
    s16 grey_time;
    s16 slow_time;
};

STATIC_ASSERT(sizeof(MONSTER_STATUS) == 0xC);

struct MONSTER_REACT {
    s16 kind;
    s16 flag;
    s16 blow;
    s16 pad;
};

STATIC_ASSERT(sizeof(MONSTER_REACT) == 0x8);

union ScriptVariable {
    int i;
    float f;
};

class CActiveMonster : public CActionChara {
public:
    sceVu0FVECTOR    place_pos;
    CRunScript       mons_script;
    BASE_MONSTER_TBL param;
    BASE_MONSTER_TBL *base_tbl;
    BASE_MONSTER_TBL *tbl;
    s16              refer_no;
    s16              monster_id;
    s16              req_prog;
    s16              now_prog;
    ScriptVariable   var[MONSTER_VAR_MAX];
    ScriptVariable   var2[MONSTER_VAR2_MAX];
    CMapParts        *link_parts;
    CMapPiece        *link_piece;
    s16              link_type;
    s32              last_hit_kind;
    s32              last_hit_chara;
    s32              last_hit_source;
    u32              last_hit_attr;
    CEnemyLifeGage   life_gage;
    CPiyori          piyori;
    CGiftMark        gift_mark;
    s16              att_type;
    MONSTER_SCOOP    scoop;
    void             *reserv_img[2];
    s32              reserv_img_size[2];
    sceVu0FVECTOR    center_pos;
    s16              event_no;
    s16              target_no;
    s16              view_state;
    float            view_alpha;
    float            camera_alpha;
    s16              priority;
    float            target_dist;
    float            camera_dist;
    float            clip_dist;
    float            unk_1300;
    float            unk_1304;
    s16              unk_1308;
    float            height;
    s32              max_life;
    s32              life;
    u16              attack;
    s16              gekirin_num;
    float            gekirin;
    s16              gekirin_time;
    u16              unk_1322;
    u16              whp;
    u16              defense;
    s32              reward_exp;
    s32              reward_money;
    s32              state;
    s32              dead_alpha;
    s16              piyori_mark;
    s16              piyori_time;
    MONSTER_STATUS   status;
    u32              attrib;
    s32              message_no;
    s32              locate_param;
    s16              gate_key;
    s16              no_damage_cnt;
    s8               drop_badge;
    MoveCheckInfo    mons_move_check;
    sceVu0FVECTOR    next_pos;
    float            move_speed;
    float            arrive_dist;
    s32              unk_1488;
    s32              unk_148c;
    float            next_rot;
    float            rot_speed;

    CActiveMonster() {
        mons_move_check.Clear();
    }

    int IsDraw(int alive_only);

    void CheckStatusAttr();

    int CheckView(int priority_limit);

    virtual void Step();

    virtual void Copy(CActiveMonster &dest, mgCMemory *memory);

    virtual void Initialize();
};

STATIC_ASSERT(sizeof(CActiveMonster) == 0x14A0);

struct MONSTER_REFER {
    s32            id;
    CActiveMonster chara;
    char           *script;
};

STATIC_ASSERT(sizeof(MONSTER_REFER) == 0x14C0);

class CMonsterLocateInfo {
public:
    s32 num;
    s32 put_num;
    u32 put_flag;
    s16 monster_id[MONSTER_LOCATE_MAX];
    s16 param[MONSTER_LOCATE_MAX];

    void SetPutFlag(int no, int put);
};

STATIC_ASSERT(sizeof(CMonsterLocateInfo) == 0x8C);

class CMonsterMan {
public:
    CScene             *scene;
    mgCMemory          memory[MONSTER_ACTIVE_MAX];
    CActiveMonster     *active[MONSTER_ACTIVE_MAX];
    MONSTER_REFER      refer[MONSTER_REFER_MAX];
    ScriptVariable     share_var[MONSTER_SHARE_MAX];
    CEffectScriptMan   *effect_man;
    CMonsterLocateInfo locate;
    s16                priority_limit;
    CEnemyLifeGage     boss_life_gage;
    s32                boss_max_life;

    void Initialize(CScene *scene);

    void DrawEffectScript();

    int CheckPhoto(CScene::InScreenCharaInfo *info);

    void StepEffectScript();

    float IsBattleStyleDist();

    int CheckMonsterTolk(float *pos);

    CActiveMonster *CheckThrowTarget(mgCFrame *frame);

    int SearchBaseIndex(int id);

    int GetMonsterNum(float dist);

    BASE_MONSTER_TBL *GetReferPtr2(int id);

    int SearchActiveMonsterBlock();

    int SearchReferBlock();

    int EntryRefer(int id, mgCMemory *memory);

    int LoadReferMonsterFile(int id, BASE_MONSTER_TBL *tbl, mgCMemory *memory);

    CActiveMonster *SetActiveMonster(int refer_no, float *pos, float *rot, int param);

    void DrawMiniMapSymbol(CMiniMapSymbol *symbol);

    void DrawLifeGage(int hide_gekirin, int hide);

    void DrawPiyori();

    void DrawActMonster();

    void DrawInvisibleMonster();

    void DrawShadowActMonster();

    void PriorityLevelCheck();

    CActiveMonster *GetPriorityLevelIndex(int priority, int *chara_no);

    void SetNearAreaPiyori(float dist);

    int IsRunEvent();

    void CollisionCheck(CActiveMonster *monster, float *pos, float *velocity, float *out_velocity);

    void CheckDamage();

    void MoveUnit(CActiveMonster *monster, CCPoly *poly, int poly_num);

    void ThinkHost();

    void RunScript(int no);
};

STATIC_ASSERT(sizeof(CMonsterMan) == 0x100F0);

extern BASE_MONSTER_TBL base_monster_define[344];

BASE_MONSTER_TBL *GetMonsterTable(int id);

float SearchArea(CScene *scene, float *from, float *to, float dist);

void LoadMonsterLanguage(int language);
