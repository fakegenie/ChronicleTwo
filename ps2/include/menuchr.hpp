#pragma once

#include "common.h"

#include <libvu0.h>

#include "actionchara.hpp"
#include "menucls1.hpp"
#include "menudraw.hpp"
#include "menusys.hpp"
#include "mg_camera.hpp"
#include "mg_memory.hpp"
#include "mg_tanime.hpp"
#include "nd_meswin.hpp"
#include "userdata.hpp"

class CCharacter2;
class CDC2Mes;
class CMenuPosDataForm;
class CScene;
class mgCFrame;
class mgCTexture;
struct BASE_MONSTER_TBL;
struct NPC_BASE_DATA;

enum {
    MENU_CHARA_LOAD_MAX = 7,
    MENU_LOAD_ITEM_MAX = 12,
    MONSTER_PROGRESS_NUM = 19,
    MONSTER_PROGRESS_LEVEL_NUM = 4,
    CHR_CNG_STAR_NUM = 256,
    CHR_CNG_CLUT_NUM = 256,
    MOS_SELECT_BADGE_NUM = 12,
    MOS_SELECT_LEVEL_MAX = 16,
    COSTUME_LIST_NUM = 3,
    COSTUME_LIST_MAX = 8,
    MOS_BOOK_LIST_MAX = 0x180,
    MOS_BOOK_DROP_ITEM_NUM = 3,
};

enum CHR_CNG_PHASE {
    CHR_CNG_PHASE_NONE = 0,
    CHR_CNG_PHASE_LOAD = 1,
    CHR_CNG_PHASE_ENTER = 2,
    CHR_CNG_PHASE_DONE = 3,
};

enum CHR_CNG_SUB_MENU {
    CHR_CNG_SUB_MENU_NONE = -1,
    CHR_CNG_SUB_MENU_MONSTER_BOX = 1,
};

enum MOS_SELECT_RESULT {
    MOS_SELECT_RESULT_CLOSE = 1,
    MOS_SELECT_RESULT_CHANGE = 2,
};

struct MENU_BGREAD_INFO2 {
    char name[0x20];
    char path[0x50];
    s8 reading;
    CActionChara *chara;
};

struct CHR_CNG_STAR {
    float life;
    float alpha;
    float x;
    float y;
    float unk_10;
    float unk_14;
};
STATIC_ASSERT(sizeof(CHR_CNG_STAR) == 0x18);

class CMenuChrCngMenu : public CBaseMenuClass {
public:
    int select;
    int last_select;
    s32 unk_118;
    s16 open_wait;
    u8 set_cursor;
    u8 change_ready;
    s16 change_phase;
    s16 change_chara;
    u32 enable_change;
    u32 party_member;
    u8 close_on_end;
    u8 got_item;
    int gift_item;
    int gift_num;
    int item_brd_select;
    int item_brd_pos;
    CMenuPosDataForm *form;
    MENUFORMPARTS_TYPE *gauge_part[3];
    COMMON_GAGE *gauge[3];
    MENU_ETCINFO *chara_pos[5];
    CMenuPosDataForm *npc_mes_form;
    CMenuPosDataForm *npc_sub_form;
    CMenuPosDataForm *npc_chara_form;
    CMenuPosDataForm *npc_sub_form2;
    MENUFORMPARTS_TYPE *cmd_part[4];
    MENUFORMPARTS_TYPE *point_gauge_part;
    mgCMemory npc_model_stack;
    mgCMemory npc_build_stack;
    PARTY_CHARA_INFO *party_info;
    NPC_BASE_DATA *npc_data;
    int item_brd_arrived;
    s8 face_state;
    u8 face_loaded;
    s16 face_chara;
    u8 *face_img;
    u8 npc_loading;
    u8 npc_loaded;
    CActionChara *npc_chara;
    int npc_wait;
    int npc_show;
    float npc_y;
    int npc_no;
    int npc_mes_talk;
    int npc_mes_cmd;
    int npc_mes_cancel;
    int npc_cmd_mes[4];
    s32 unk_23C;
    float cursor_wave;
    s16 *sys_mes;
    s16 *mes_data;
    s16 sub_menu;
    s16 sub_menu_next;
    int star_stop_wait;
    s16 star_spawn;
    s16 star_fade;
    float star_x;
    float star_y;
    float unk_260;
    float star_size;
    float star_angle;
    float star_alpha;
    int star_fade_out;
    float star_wave;
    float star_pulse;
    s32 unk_27C;
    CHR_CNG_STAR star[CHR_CNG_STAR_NUM];
    u32 clut[CHR_CNG_CLUT_NUM];
    u8 unk_1E80[0x100];

    void AttachForm();

    void EnterDataMenu(u8 *pack);

    void LoadNPCFaceData(mgCMemory *stack, int load_now);

    void EnterNPCFaceData();

    int LoadBGNPCModel(int restart_read);

    int CheckBGNPCModel();

    int KeyChangeMain();

    void CalcTex();

    int CheckChrChange();

    int MenuLocalLoop();

    void InitStarInfo();

    void UpdataLife();
};
STATIC_ASSERT(sizeof(CMenuChrCngMenu) == 0x1F80);

class CMenuMosSelect : public CBaseMenuClass {
public:
    sceVu0FVECTOR camera_pos;
    sceVu0FVECTOR camera_ref;
    int result;
    s16 *mes_data;
    int select;
    int top;
    MOS_CHANGE_PARAM *badge;
    MOS_CHANGE_PARAM *select_badge;
    u8 unk_148[8];
    CDC2Mes mes;
    int mes_show;
    s32 unk_2BA4;
    ClsMes info_win;
    int info_win_show;
    s32 unk_5504;
    int set_cursor;
    int level_num;
    int level_monster[MOS_SELECT_LEVEL_MAX];
    int change_wait;
    int view_monster;
    int pick_monster;
    int load_monster;
    int level_max;
    s8 skip_draw;
    CMenuPosDataForm *badge_form;
    CMenuPosDataForm *info_form;
    CMenuPosDataForm *model_form;
    u8 model_side;
    sceVu0FVECTOR model_pos;
    CActionChara monster[1];
    CActionChara effect;
    mgCMemory effect_stack;
    mgCMemory unk_7620;
    u_long128 *effect_data;
    u32 *effect_sound;
    s16 effect_show;
    s16 effect_frame;
    s32 unk_765C;
    s16 load_wait;
    s16 load_phase;

    void AttachForm();

    int CheckLoadBGMonster();

    void CalcCursorPosition();

    void CalcTex();

    int KeyNormalMode(int select_key, int lr_key, int push_button);

    int KeyStep();
};
STATIC_ASSERT(sizeof(CMenuMosSelect) == 0x7670);

class CMenuCostumeSel : public CBaseMenuClass {
public:
    mgCCameraFollow camera;
    int select;
    s32 unk_1D4;
    s16 costume_num[COSTUME_LIST_NUM];
    s16 costume_select[COSTUME_LIST_NUM];
    s16 costume_list[COSTUME_LIST_NUM][COSTUME_LIST_MAX];
    s16 *list[COSTUME_LIST_NUM];
    s32 unk_220;
    float tile_scroll;
    mgCMemory stack;
    s16 chara;
    int monica_enabled;
    sceVu0FVECTOR chara_pos;
    float costume_rotation[4];
    s32 unk_280;
    int cursor_show;
    int change_chara;
    float line_wave[3];
    int load_wait;
    int loading;
    int wait_load;
    int show_help;
    s32 unk_2A8;
    s32 unk_2AC;
    float cursor_x;
    float cursor_y;
    float cursor_wave;
    float cursor_wave_y;
    CHARA_DATA *chara_data;
    mgCTexture *tile_tex;
    mgCTexture *cursor_tex;

    void UpdateCostumeList(int chara_no, unsigned long attr);

    void LoadMenuData(mgCMemory *stack, int *tex_block);

    int KeyStep();

    void Draw();
};
STATIC_ASSERT(sizeof(CMenuCostumeSel) == 0x2D0);

class CMosBookMenu : public CBaseMenuClass {
public:
    mgCCamera camera;
    float bg_scroll;
    mgCMemory stack;
    int tex_block_no;
    CActionChara *monster;
    s32 unk_1BC;
    s32 unk_1C0;
    s32 unk_1C4;
    s32 unk_1C8;
    s32 unk_1CC;
    int load_phase;
    int load_wait;
    int show_wait;
    s8 skip_draw;
    int select;
    BASE_MONSTER_TBL *monster_info;
    int list[MOS_BOOK_LIST_MAX];
    int list_num;
    char area_name[0x40];
    char name[0x40];
    char type_name[0x40];
    char weak_name[0x58];
    u32 hp;
    u32 abs;
    int kill_num;
    u32 strong_bit;
    u32 weak_bit;
    char drop_item[MOS_BOOK_DROP_ITEM_NUM][0x21];

    void InitMonsterInfo();

    void SetMonsterInfo(BASE_MONSTER_TBL *info);

    virtual void InitEnd();

    void Draw();

    int KeyStep();
};
STATIC_ASSERT(sizeof(CMosBookMenu) == 0x980);

STATIC_ASSERT(sizeof(mgRect<short>) == 0x8);

extern s16 monster_progress_tbl[MONSTER_PROGRESS_NUM * (1 + MONSTER_PROGRESS_LEVEL_NUM)];

extern mgCMemory *MorattaStack;

extern mgCTexture *MenuCharaChangeBase_Tex;

extern mgCTexture *MenuCharaChangeCLUT_Tex;

extern mgCTexture *MenuCharaChangeStar_Tex;

extern u32 *CharaSndBuffer;

extern MENU_BGREAD_INFO2 *MenuCharaBuild2[MENU_CHARA_LOAD_MAX];

extern CActionChara *MenuActionChara[MENU_CHARA_LOAD_MAX];

extern mgCMemory MenuActionCharaBuffer[MENU_CHARA_LOAD_MAX];

extern s16 MenuLoadItemNo[MENU_LOAD_ITEM_MAX];

extern mgCMemory MenuChangeNpcMemory;

extern mgCMemory SwordEffectStack;

void InitMenuBGReadInfo2(MENU_BGREAD_INFO2 *info);

int MenuLoadFileCheck(MENU_BGREAD_INFO2 **info);

void MenuBGReadInfo2Malloc(mgCMemory *stack, int *use_tbl);

s16 ConvertCharaLoadDataPhase(int chara_no, int part);

void SetMenuLoadItemNo(int chara_no);

void MenuMemoryAdjust(mgCMemory *src, mgCMemory *rest, mgCMemory *buffer, int mode);

void DeleteMonsterEffect();

void SetMessagePositionNPCForm(CMenuPosDataForm *form, CDC2Mes *mes);

void AdjustNPCTalk(CDC2Mes *mes, CCharacter2 *chara);

void MenuCharaChangeStarDraw();

int MenuCharaChangeInit(mgCMemory *stack, int *tex_block, int mode);

int MenuCharaChangeKey();

void MenuCharaChangeDraw();

char *GetMonsterName(int monster_no);

int get_gajji_id_from_monster_progress_table(int monster_no, int *level);

int GetMonsterProgressTableNo(int level, int monster_no);

int get_monster_tbl_bajjilevel(int *out, int bajji_no, int monster_no, int level);

int get_default_monster_progresstbl(int bajji_no);

int GetMonsterModelFile(int monster_no, int kind, char *path);

void MonsterScaleCheck(CCharacter2 *chara);

int MonsterEffectRead(mgCMemory *stack, int monster_no, int background);

int MonsterEffectEnter(CScene *scene, u_long128 *buffer, int tex_block);
int MonsterEffectEnter(CScene *scene, u_long128 *buffer);

void MenuMonsterBoxInit(mgCMemory *stack, int *tex_block, int mode);

int MenuMonsterBoxKey();

void MenuMonsterBoxDraw();

void MenuTimeStepEnvFunc(CScene *scene, CActionChara *chara, int item_no);

void MenuWeaponRealStepEnvFunc(CActionChara *chara, int item_no);

int MenuItemCharaDataLoad(mgCMemory *stack, int chara_no, MENU_BGREAD_INFO2 **info, int restart_read);

int MenuItemCharaDataLoadEndCheck(MENU_BGREAD_INFO2 **info, mgCMemory *stack, CActionChara **chara, int chara_no,
                                  int tex_block, int scene_tex_block);

u32 MenuCharaSoundLoad(mgCMemory *stack, int chara_no, int background);

void MenuCharaSoundEnter(CScene *scene, CActionChara *chara, int init_port);

u32 MenuItemChrLoad(mgCMemory *stack, int item_no, int kind, MENU_BGREAD_INFO2 *info, int restart_read);

int MenuItemChrLoadEndCheck(MENU_BGREAD_INFO2 *info, CActionChara *chara, mgCMemory *stack, int tex_block);

int MenuItemRoboDataLoad(mgCMemory *stack, MENU_BGREAD_INFO2 **info, int restart_read);

void DeleteOutLineMenu(CActionChara *chara, int sub);

int MenuItemRoboDataLoadEndCheck(MENU_BGREAD_INFO2 **info, mgCMemory *stack, CActionChara **chara, int tex_block,
                                 int scene_tex_block);

void MenuRoboPartsLightOff(mgCFrame *frame);

int MenuMonsterLoadBG(mgCMemory *stack, MENU_BGREAD_INFO2 **info, int monster_no, int restart_read);

int MenuMonsterLoadBGCheck(MENU_BGREAD_INFO2 **info, CActionChara **chara, int tex_block, int scene_tex_block);

void MenuItemCharaDataLoadEndCheckAfter(MENU_BGREAD_INFO2 **info, int chara_no);

void InitMainCharaBG(int chara_no, mgCMemory *stack, int mode);

int ReadMainCharaBG();

int KeyMainCharaBG();

void DrawMainCharaBG();

int MenuNPCModelLoad(mgCMemory *stack, int chara_no, int background);

int MenuNPCLoadCheck(CActionChara *chara, mgCMemory *stack, int tex_block);

void MenuCostumeInit(mgCMemory *stack, int *tex_block, int mode);

int MenuCostumeKey();

void MenuCostumeDraw();

void MonsterBookInit(mgCMemory *stack, int *tex_block, int mode);

int MonsterBookKey();

void MonsterBookDraw();

struct MENU_LOAD_INFO {
    signed char mode;
    signed char unk_1;
    signed char unk_2;
    signed char unk_3;
    signed char unk_4;
    signed char unk_5;
    signed char unk_6[2];
};
STATIC_ASSERT(sizeof(MENU_LOAD_INFO) == 8);

extern MENU_LOAD_INFO MenuLoadInfo;
