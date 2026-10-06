#pragma once

#include "common.h"

#include <libvu0.h>

#include "character.hpp"
#include "mg_memory.hpp"

class CDC2Mes;
class CGameDataUsed;
class CGyoRaceData;
class CUserDataManager;
class CWaterFrame;
class ClsMes;
class mgCFrame;
class mgCTexture;
struct BREEDFISH_USED;

class CAquaFish;
class CAquaFishEff;

enum AQUA_FISH_THINK {
    AQUA_FISH_THINK_REST         = 0,
    AQUA_FISH_THINK_SWIM         = 1,
    AQUA_FISH_THINK_FOOD_LOOK    = 3,
    AQUA_FISH_THINK_FOOD_EAT     = 4,
    AQUA_FISH_THINK_BATTLE       = 5,
    AQUA_FISH_THINK_BATTLE_REST  = 6,
    AQUA_FISH_THINK_LOVE_SEARCH  = 7,
    AQUA_FISH_THINK_LOVE_CHASE   = 8,
};

enum AQUA_FISH_SWIM {
    AQUA_FISH_SWIM_POINT = 0,
    AQUA_FISH_SWIM_ROUTE = 1,
    AQUA_FISH_SWIM_ROUND = 2,
};

enum AQUA_FISH_COL {
    AQUA_FISH_COL_WALL   = 0x1,
    AQUA_FISH_COL_OBJECT = 0x2,
    AQUA_FISH_COL_FOOD   = 0x4,
    AQUA_FISH_COL_FISH   = 0x8,
    AQUA_FISH_COL_TARGET = 0x10,
};

enum AQUA_BUBBLE_STATE {
    AQUA_BUBBLE_RISE = 0,
    AQUA_BUBBLE_POP  = 1,
    AQUA_BUBBLE_END  = 2,
};

enum FISH_FOOD_STATE {
    FISH_FOOD_HOLD  = 0,
    FISH_FOOD_DROP  = 1,
    FISH_FOOD_ENTER = 2,
    FISH_FOOD_SINK  = 3,
};

struct AQUA_BUBBLE {
    u8            pattern;
    u8            state;
    float         phase;
    float         drift_x;
    float         drift_z;
    sceVu0FVECTOR pos;
    float         alpha;
    u8            unk_24[0xC];
};

STATIC_ASSERT(sizeof(AQUA_BUBBLE) == 0x30);

class CBubble {
public:
    s8            one_shot;
    s8            active;
    u32           generated;
    u8            unk_08[0x8];
    sceVu0FVECTOR origin;
    float         surface_y;
    float         height;
    mgCTexture   *texture;
    s16           tex_u;
    s16           tex_v;
    u32           bubble_num;
    AQUA_BUBBLE  *bubble;
    u8            unk_38[0x8];

    void Generate(int no);

    int Generate(float *pos);

    void SetTexture(mgCTexture *tex, int u, int v);

    void Step();

    void Draw();

    void Initialize(mgCMemory *memory, float *origin, int num, float surface);

    void RunOff();
};

STATIC_ASSERT(sizeof(CBubble) == 0x40);

class CAquaFishActionParam {
public:
    s16        phase;
    s32        timer;
    s16        target_no;
    CAquaFish *target;
    float      speed;
    float      max_speed;
    u8         unk_18[0x18];
    float      decel;
    s32        hit_count;
    u8         unk_38[0x8];

    void Initialize();
};

STATIC_ASSERT(sizeof(CAquaFishActionParam) == 0x40);

struct AQUA_FISH_ROUND {
    s16   dir;
    float width;
    float depth;
    float wave;
};

STATIC_ASSERT(sizeof(AQUA_FISH_ROUND) == 0x10);

struct NEXT_THINK_PARAM {
    sceVu0FVECTOR pos;
    CAquaFishEff *effect;
    CAquaFish    *target;
    s16           target_no;
};

STATIC_ASSERT(sizeof(NEXT_THINK_PARAM) == 0x20);

class CAquaFish : public CCharacter2 {
public:
    sceVu0FVECTOR        target_pos;
    sceVu0FVECTOR        move;
    sceVu0FVECTOR        target_rot;
    sceVu0FVECTOR        turn;
    s16                  aqua_no;
    float                radius;
    s32                  think_timer;
    s16                  pair_no;
    s16                  think_mode;
    s16                  swim_mode;
    u8                   unk_6b2[0xE];
    CAquaFishActionParam action;
    union {
        AQUA_FISH_ROUND  round;
        float            charge_angle;
    };
    sceVu0FVECTOR        route[32];
    s16                  route_num;
    s16                  route_no;
    s32                  route_time;
    u8                   unk_918[0x8];
    s16                  eat_item;
    s8                   swim_variant;
    u32                  col_flags;
    s32                  wall_time;
    s32                  fatigue;
    s32                  fatigue_max;
    s32                  flash_count;
    CGameDataUsed       *data;

    CAquaFish();

    virtual void Initialize();

    void SetLiveParam(CGameDataUsed *data);

    void SetAdjustScale();

    int AddFatigue(int add);

    void GetPosition2D(int *pos);

    void GetDirVect(float *dir);

    void NormalGetNextVelo(float speed);

    void NormalGetNextRotY();

    void NormalGetNextRot();

    float CalcMoveSpeed(float speed);

    void NextRootNormal();

    void MoveActionRound();

    void MoveActionBattle();

    void NextThink(int think, NEXT_THINK_PARAM *param);

    int ParamStep();

    void FishDraw();
};

STATIC_ASSERT(sizeof(CAquaFish) == 0x940);

class CAquaFishEff {
public:
    CAquaFish  *fish;
    mgCTexture *texture;
    u16         type;
    s32         timer;

    void Initialize();

    void StartFishEffect(int type);

    void Step();

    void Draw();
};

STATIC_ASSERT(sizeof(CAquaFishEff) == 0x10);

class CFishFood : public CCharacter2 {
public:
    sceVu0FVECTOR spin;
    sceVu0FVECTOR pos;
    s16           item_no;
    s32           fall_time;
    float         sway;
    float         sway_phase;
    u8            state;

    CFishFood();

    void SetDropPosition(float *pos);

    void Drop();

    virtual void Step();
};

STATIC_ASSERT(sizeof(CFishFood) == 0x6A0);

class CAquaMes {
public:
    mgCMemory *memory;
    ClsMes    *title_mes;
    s32        title_id;
    u8         title_draw;
    ClsMes    *menu_mes;
    s32        menu_cursor;
    u8         menu_draw;
    u8         cursor_snap;
    u8         cursor_draw;
    float      cursor_target[2];
    float      cursor_pos[2];
    ClsMes    *question_mes;
    s32        question_cursor;
    u8         question_draw;
    s16        question_num;
    ClsMes    *guide_mes;
    s32        guide_id;
    u8         guide_draw;
    ClsMes    *help_mes;
    u8         help_draw;
    ClsMes    *info_mes;
    u8         info_draw;
    ClsMes    *fish_mes;
    s32        fish_mes_time;
    s32        unk_5c;
    s32        unk_60;

    CAquaMes();

    void Initialize(mgCMemory *memory);

    void SettingAquaMes(int aqua_no);

    void SetTitleId(int id);

    int AddMenuCursor(int add, int num);

    void SetQuestionId(int id, int top, int num);

    int AddQuestionCursor();

    void SetCtrlHelpId(int id);

    void SetInfoMsgID(int id);

    void EatMessage(int id, CAquaFish *fish);

    void ChangeManMessage(CAquaFish *fish);

    void DeadMessage(CAquaFish *fish);

    void Step();

    void Draw();

    void DrawTitleMes();
};

STATIC_ASSERT(sizeof(CAquaMes) == 0x64);

class CAquarium {
public:
    s32               mode;
    u_long128        *load_buf;
    mgCMemory         load_stack;
    s32               tex_block[13];
    CUserDataManager *user_data;
    mgCMemory         aqua_stack;
    mgCFrame         *ground_frame;
    mgCFrame         *glass_frame;
    mgCFrame         *aqua_frame;
    mgCFrame         *mizu_frame;
    s16               ground_tex_block;
    s16               glass_tex_block;
    s16               aqua_tex_block;
    CWaterFrame      *water;
    s16               water_tex_block;
    mgCFrame         *suimen_frame;
    float             ripple;
    mgCMemory         naka_stack;
    mgCFrame         *naka_frame;
    CAquaMes          mes;
    mgCMemory         mes_stack;
    s16               menu_tex_block;
    mgCMemory         fish_stack[6];
    CAquaFish        *fish[6];
    s16               fish_tex_block[6];
    s16               sel_fish;
    char              target_name[0x20];
    char              partner_name[0x20];
    s16               target_fish;
    s16               partner_fish;
    u8                fish_info_draw;
    CFishFood        *food;
    s16               food_tex_block;
    s16               unk_326;
    sceVu0FVECTOR     drop_pos;
    s32               food_time;
    u8                unk_344[0x40];
    u8                drop_root_draw;
    s16               unk_386;
    s16               love_phase;
    s16               love_time;
    s16               love_tex_block;
    CCharacter2      *love_chara;
    mgCMemory         food_stack;

    CAquarium();

    void Clear();

    void Initialize(mgCMemory *memory, int *tex_block);

    int LoadFish(int no, CGameDataUsed *data);

    void SettingAqua();

    void CombineFish(int no1, int no2);

    int GetBattleTarget(int no);

    void Thinking(int no);

    int ColCheck(int no);

    int InitSelFish();

    void SelectFish(int force);

    void SelFishSetCursor();

    int Step();

    void Draw();
};

STATIC_ASSERT(sizeof(CAquarium) == 0x3D0);

class CGyoraceFishData {
public:
    s16            fish_num[4];
    CGameDataUsed *fish[4];

    int LoadData(mgCMemory *memory, u_long128 *buffer);

    CGameDataUsed *GetRaceFish(int race_class, int no);
};

struct FISH_PRIZE_INFO {
    s32 unk_0;
    s32 unk_4;
};

STATIC_ASSERT(sizeof(FISH_PRIZE_INFO) == 0x8);

int GetUseableEsaNo(int *item_no);

float SetFishAdjustScale(int size, int fish_no, float scale, float max);

void DrawEsaDropRoot(CFishFood *food, float bottom);

void AquaMesDispAdjustPos(ClsMes *mes, int *pos);

int GetFishImgPath(char *path, int fish_no, BREEDFISH_USED *fish);

int GetFishImageColor(int fish_no, int which);

int FishIMGReplace(u_long128 *buffer, CCharacter2 *chara, int fish_no, BREEDFISH_USED *fish);

void DrawFishParam(int x, int y, mgCTexture *tex, CGameDataUsed *data);

int CalcFishParam(BREEDFISH_USED *fish);

void MenuAquaInit(mgCMemory *memory, int *tex_block, int arg);

int MenuAquaKey();

void MenuAquaDraw();

void MenuGyoraceFishSelInit(mgCMemory *memory, int *tex_block, int arg);

int MenuGyoraceFishSelKey();

void MenuGyoraceFishSelDraw();

CGameDataUsed *GetGyoRaceFish();

void SetGyoRaceAquariumNo(int no);

int GetGyoRaceAquariumNo();

void SetGyoRaceClass(int race_class);

int GetGyoRaceClass();

void SetGyoRaceNo(int no);

int GetGyoRaceNo();

void SetGyoRaceRanking(int rank);

int GetGyoRaceRanking();

void InitFishPrize();

int LoadFishPrize(int type);

int LoadFishPrize(int type, mgCMemory *memory);

int RefreshFishPrize();

int GetFishPrize(int race_class, int rank, FISH_PRIZE_INFO *info);

void TuriTourCount();

int CheckSameRacerFish(int racer_no);

CGameDataUsed *GetOmakeGyoracer2(int no);

int GetOmakeGyoracerTactics(int no);

void SetOmakeGyoracerTactics(int no, int tactics);

void GyoraceSubGameInitData();

void GyoraceMenuInit(mgCMemory *memory, int *tex_block, int arg);

int GyoraceMenuKey();

void GyoraceMenuDraw();

void DrawSubGameTitle(mgCTexture *tex, int size, int x, int y, int w);

void DrawSubGameListFix(mgCTexture *tex, int x, int y, int w, int h);

void DrawSubGameScrlList(mgCTexture *tex, int *rect, int *scroll);

void DrawSubGameUnderLine(mgCTexture *tex, int x, int y, int w);

extern char *Mitouroku[7];

extern int AquaDeadCheck;

extern CGameDataUsed *GyoraceFish;

extern CGyoRaceData *GyoraceData;

extern CDC2Mes *MenuDCMsg[9];
