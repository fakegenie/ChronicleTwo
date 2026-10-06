#pragma once

#include "common.h"

#include <libvu0.h>

#include "mg_memory.hpp"
#include "mg_tanime.hpp"

class CActionChara;
class CCharacter2;
class CGameDataUsed;
class CItemUseTarget;
class CUserDataManager;
class ClsMes;
class mgCDrawPrim;
class mgCTexture;
class CMenuPosDataForm;
enum MENUFORM_DTYPE {
    MENUFORM_DTYPE_NORMAL    = 0x00,
    MENUFORM_DTYPE_ITEMBRD   = 0x0A,
    MENUFORM_DTYPE_GIFTVIEW  = 0x0C,
    MENUFORM_DTYPE_POLY      = 0x0D,
    MENUFORM_DTYPE_MAPPART   = 0x0F,
    MENUFORM_DTYPE_CREATEBRD = 0x10,
    MENUFORM_DTYPE_MSGFORM   = 0x14,
    MENUFORM_DTYPE_COMBRD    = 0x16,
    MENUFORM_DTYPE_LIST      = 0x17,
    MENUFORM_DTYPE_BG_TILE   = 0x18,
    MENUFORM_DTYPE_DLOAD     = 0x19,
    MENUFORM_DTYPE_MAINFRM   = 0x1E,
    MENUFORM_DTYPE_MAINIMG   = 0x1F,
    MENUFORM_DTYPE_CHRSTAR   = 0x20,
    MENUFORM_DTYPE_INV_CARD  = 0x21,
    MENUFORM_DTYPE_GEOLIST   = 0x23,
    MENUFORM_DTYPE_GEOTITLE  = 0x24,
    MENUFORM_DTYPE_GEOANA    = 0x25,
    MENUFORM_DTYPE_HOUSE     = 0x26,
    MENUFORM_DTYPE_SHOPLIST  = 0x27,
    MENUFORM_DTYPE_BUILDUP   = 0x28,
    MENUFORM_DTYPE_MOSBAJI   = 0x29,
    MENUFORM_DTYPE_SAVELIST  = 0x2A,
    MENUFORM_DTYPE_WMAP      = 0x2B,
    MENUFORM_DTYPE_INFOCUR   = 0x2C,
    MENUFORM_DTYPE_CLIP      = 0x2D,
};

enum MENUFORM_MTYPE {
    MENUFORM_MTYPE_N  = -1,
    MENUFORM_MTYPE_D  = 0,
    MENUFORM_MTYPE_L  = 1,
    MENUFORM_MTYPE_I  = 2,
    MENUFORM_MTYPE_IR = 3,
};

enum MENUFORMPARTS_DTYPE {
    MENUFORMPARTS_DTYPE_NORMAL      = 0x00,
    MENUFORMPARTS_DTYPE_NORMAL2     = 0x01,
    MENUFORMPARTS_DTYPE_CURSOR      = 0x02,
    MENUFORMPARTS_DTYPE_FUNCINFO    = 0x03,
    MENUFORMPARTS_DTYPE_NUMBER1     = 0x05,
    MENUFORMPARTS_DTYPE_NUMBER2     = 0x06,
    MENUFORMPARTS_DTYPE_WAKU_RECT   = 0x0D,
    MENUFORMPARTS_DTYPE_WAKU_CIRCLE = 0x0E,
    MENUFORMPARTS_DTYPE_FORM        = 0x19,
    MENUFORMPARTS_DTYPE_BG          = 0x2D,
    MENUFORMPARTS_DTYPE_BETA        = 0x2E,
    MENUFORMPARTS_DTYPE_FADE_TOP    = 0x2F,
    MENUFORMPARTS_DTYPE_FADE_BOTTOM = 0x30,
    MENUFORMPARTS_DTYPE_FADE_RIGHT  = 0x31,
    MENUFORMPARTS_DTYPE_FADE_LEFT   = 0x32,
    MENUFORMPARTS_DTYPE_TRS         = 0x37,
    MENUFORMPARTS_DTYPE_CHECKMARK   = 0x39,
    MENUFORMPARTS_DTYPE_NETA        = 0x3B,
    MENUFORMPARTS_DTYPE_IDEA_BOARD  = 0x3C,
    MENUFORMPARTS_DTYPE_ALBUM       = 0x3D,
    MENUFORMPARTS_DTYPE_IDEA_MEMO   = 0x3E,
    MENUFORMPARTS_DTYPE_SQ_BETA     = 0x41,
    MENUFORMPARTS_DTYPE_RANDOM_LINE = 0x4C,
    MENUFORMPARTS_DTYPE_FONT        = 0x4E,
    MENUFORMPARTS_DTYPE_CLUT_RELOAD = 0x4F,
};

enum MENU_PARTS_EFFECT_TYPE {
    MENU_PARTS_EFFECT_UNK_1       = 1,
    MENU_PARTS_EFFECT_BLINK       = 2,
    MENU_PARTS_EFFECT_ROT         = 3,
    MENU_PARTS_EFFECT_HURIKO      = 4,
    MENU_PARTS_EFFECT_STRETCH     = 6,
    MENU_PARTS_EFFECT_STRETCH_REP = 7,
    MENU_PARTS_EFFECT_STRETCH_SIN = 8,
    MENU_PARTS_EFFECT_UNK_9       = 9,
    MENU_PARTS_EFFECT_UNK_10      = 10,
    MENU_PARTS_EFFECT_UNK_11      = 11,
    MENU_PARTS_EFFECT_UNK_12      = 12,
    MENU_PARTS_EFFECT_UNK_100     = 100,
};

struct MENU_BASETEXINFO {
    mgRect<int> rect;
    char *name;
    char *tex_name;
    u8 tex_block;
    u8 unk_19;
    s16 tbl_no;
    u8 unk_1c[0x4];
};
STATIC_ASSERT(sizeof(MENU_BASETEXINFO) == 0x20);

struct MENU_PARTS_EFFECT_STRUCT1 {
    u8 active;
    u8 repeat;
    u16 type;
    float param[8];
};
STATIC_ASSERT(sizeof(MENU_PARTS_EFFECT_STRUCT1) == 0x24);

struct MENUFORMPARTS_TYPE {
    char *name;
    u8 active;
    u8 draw_flag;
    u8 dtype;
    u8 rgba[4];
    u8 viber[2];
    u8 unk_d;
    s16 vibe_cnt[2];
    u8 unk_12[0x2];
    mgCTexture *tex;
    u8 tex_info_no;
    u8 bilinear;
    s8 alpha_blend;
    u8 unk_1b;
    float x;
    float y;
    float w;
    float h;
    float unk_2c;
    int etc_info[4];
    MENU_PARTS_EFFECT_STRUCT1 *effect;
    u8 effect_num;
    u8 item_flag;
    u8 shadow;
    s8 shadow_offset;
};
STATIC_ASSERT(sizeof(MENUFORMPARTS_TYPE) == 0x48);

struct MENU_FORM_ACTION_MOVE {
    s16 mtype;
    float x;
    float y;
    float rate_x;
    float rate_y;
};
STATIC_ASSERT(sizeof(MENU_FORM_ACTION_MOVE) == 0x14);

struct MENU_FORM_ACTION {
    char name[0x10];
    MENU_FORM_ACTION_MOVE *move;
};
STATIC_ASSERT(sizeof(MENU_FORM_ACTION) == 0x14);

struct MENU_ETCINFO {
    char *name;
    int value[2];
};
STATIC_ASSERT(sizeof(MENU_ETCINFO) == 0xC);

struct MENU_ETCINFO2 {
    char *name;
    float value[4];
};
STATIC_ASSERT(sizeof(MENU_ETCINFO2) == 0x14);

struct MENUFORM_MAKEBRD_LINE {
    u8 kind;
    u8 button;
    s16 num;
    s16 sub_num;
};
STATIC_ASSERT(sizeof(MENUFORM_MAKEBRD_LINE) == 0x6);

struct MENUFORM_MAKEBRD_INFO {
    MENUFORM_MAKEBRD_LINE line[4];
    int material_num;
    int unk_1c;
    int unk_20;
    int unk_24;
    int unk_28;
};
STATIC_ASSERT(sizeof(MENUFORM_MAKEBRD_INFO) == 0x2C);

struct MENU_EFFECT_INFO {
    float unk_0;
    float unk_4;
    float unk_8;
    float x;
    float y;
    float unk_14;
    float unk_18;
    float unk_1c;
    float unk_20;
    float unk_24;
    float unk_28;
    float unk_2c;
    float unk_30;
    float unk_34;
    float unk_38;
    float unk_3c;
};
STATIC_ASSERT(sizeof(MENU_EFFECT_INFO) == 0x40);

struct REPAIR_EFFECT_PARTICLE {
    float unk_0;
    float unk_4;
    float unk_8;
    float alpha;
    float vx;
    float unk_14;
    float x;
    float y;
    int counter;
    u8 unk_24;
    u8 active;
    u8 unk_26[0xa];
};
STATIC_ASSERT(sizeof(REPAIR_EFFECT_PARTICLE) == 0x30);

class CMenuPosDataForm {
public:
    u8 active;
    u8 draw_flag;
    u8 dtype;
    u8 step_stop;
    s16 clip_w;
    s16 clip_h;
    s16 vibe_cnt[2];
    float x;
    float y;
    char *name;
    int counter;
    u8 sub_no;
    u8 unk_1d[0x3];
    u8 mtype;
    u8 unk_21[0x3];
    int next_x;
    int next_y;
    float rate_x;
    float rate_y;
    s16 chara_tex_block;
    s16 unk_36;
    CActionChara *chara;
    u8 unk_3c[0x4];
    float ambient[4];
    u8 rgba_bit;
    s8 rgba_add[4];
    u8 rgba[4];
    u8 rgba_target[4];
    u8 unk_5d;
    s16 action_no;
    s16 action_state;
    s16 action_num;
    MENU_FORM_ACTION *action;
    s16 parts_num;
    MENUFORMPARTS_TYPE *parts;
    CMenuPosDataForm *prev;
    CMenuPosDataForm *next;
    u8 unk_78[0x8];

    void SetPos(int pos_x, int pos_y) {
        x = pos_x;
        y = pos_y;
    }

    void Initialize();

    MENUFORMPARTS_TYPE *GetPartInfo(char *part_name);

    void SetPartDrawFlag(char *part_name, bool draw);

    void SetActionCharaPtr(CActionChara *new_chara, int tex_block, int unk);

    void SetRGBACalcParam(int channel, int add, int target);

    void FormFadeIn(int frames, int reset);

    void FormFadeOut(int frames, int reset);

    void SetNumber(char *part_name, int number);

    void SetPartRGBA(char *part_name, int r, int g, int b, int a);

    void GetPutPosXY(char *part_name, int &out_x, int &out_y);

    void GetPutPosXY(char *part_name, float &out_x, float &out_y);

    MENUFORMPARTS_TYPE *GetEnableEnterPart();

    int GetNowPosRGBA(MENUFORMPARTS_TYPE *part, MENU_BASETEXINFO *tex_info, float *pos, u8 *rgba);

    void MenuPartsStep();

    int MenuFormStep();

    int CheckMoveEnd(int target_x, int target_y);

    int CheckMoveEnd();

    void SetAction(char *action_name);

    void SetNextMovePos(int *pos, int move_type);

    int GetNextMovePos(int *out_pos);

    void MenuFormDrawNormal(int x, int y, float sway_x, float sway_y, int &tex_block);

    void MenuFormDraw(int x, int y, int &tex_block);

    void MenuFormDraw(int &tex_block);
};
STATIC_ASSERT(sizeof(CMenuPosDataForm) == 0x80);

class CPosDataManage {
public:
    MENU_ETCINFO *etc_tbl;
    u16 etc_tbl_num;
    MENU_ETCINFO2 *etc_tbl2;
    u16 etc_tbl2_num;
    MENU_BASETEXINFO *tex_info;
    u16 tex_info_num;
    CMenuPosDataForm *form;
    u16 form_num;
    u8 step_stop;

    void Initialize();

    MENU_BASETEXINFO *GetTexGetInfo(int no);

    MENU_BASETEXINFO *GetTexGetInfo(char *info_name);

    int GetTexGetInfoTblNo(char *info_name);

    void TexGetInfoClear(int start, int end);

    void ResetTextureBlockNo(char *tex_name, int tex_block);

    void ResetTextureInfoAll();

    void EtcTblClear(int start, int end);

    MENU_ETCINFO *GetEtcTbl(char *info_name);

    void GetEtcTblValue(char *info_name, int &out_value0, int &out_value1);

    MENU_ETCINFO2 *GetEtcTbl2(char *info_name);

    void GetEtcTbl2Value(char *info_name, float *out_values, int num);

    void EtcTbl2Clear(int start, int end);

    CMenuPosDataForm *GetFormInfo(char *form_name);

    CMenuPosDataForm *GetFormInfo(int no);

    void FormInfoClear(int start, int end);

    void SetFormPos(char *form_name, int *pos);

    void InitDrawList();

    CMenuPosDataForm *GetDrawTopList();

    void FormReLink(char *form_name0, char *form_name1);

    void FormReLink2(char *first0, char *last0, char *first1, char *last1);

    void FormStep();

    void FormDraw();

    void ClearPos();

};
STATIC_ASSERT(sizeof(CPosDataManage) == 0x20);

class CMenuPosDataManage : public CPosDataManage {
public:
    u_long128 *pallet[3][2];
    s16 trans_pallet_no[2];
    mgCTexture *common_tex;
    int unk_40;
    int unk_44;
    int unk_48;
    mgCTexture *icon_effect_tex;
    mgCTexture *effect_tex;
    mgCTexture *item_icon_tex[4][2];
    float fish_jump_wait[150];
    float fish_jump_height[150];
    s8 fish_jump_count[150];

    void AttachCommonTexInfo();

    int StepMainMenuIconMove(int *icon_list, int select, int mode);

    void GetPosMenuItemBrdKoma(int *out_pos, int no, int clip);

    void GetPosMenuItemOnItemBrd(int *out_pos, int no, int clip);

    void GetPosMenuItemBrdForEffect(int *out_pos, int no, int clip);

    void MallocPallet(mgCMemory *stack);

    void SearchTransPalletNo();

    void InitializeCMenuPosDataManage();

};
STATIC_ASSERT(sizeof(CMenuPosDataManage) == 0x5BC);

class CRepairEffect {
public:
    u8 active;
    int particle_num;
    int counter;
    int x;
    int y;
    int alpha;
    REPAIR_EFFECT_PARTICLE *particle;
    mgCTexture *unk_1c;
    mgCTexture *tex;

    void Initialize();

    void Generate(mgCMemory *stack, int num);

    void Step();

    void Draw();

};
STATIC_ASSERT(sizeof(CRepairEffect) == 0x24);

class CRepairManager {
public:
    u8 bg_load;
    u8 data_ready;
    s16 tex_block;
    CRepairEffect *effect[8];
    mgCMemory effect_stack[8];
    mgCTexture *unk_1a4;
    mgCTexture *tex;
    u32 *data;
    CActionChara *model;
    mgCMemory model_stack;
    float model_counter;
    u8 keep;

    void Initialize();

    void SetStack(mgCMemory *stack, int mode);

    void Clear();

    void LoadDataBG(mgCMemory *stack);

    void CheckDataBG(int new_tex_block);

    void SetRepairData(mgCMemory *stack, int new_tex_block, u32 *new_data);

    void GeneratePoly(float *pos, int unk);

    void Generate(int x, int y);

    int IsRunModel();

    int IsRun();

    void Step();

    void Draw();

};
STATIC_ASSERT(sizeof(CRepairManager) == 0x1EC);

class CLevelUpEffect {
public:
    u8 active;
    int counter;
    int kind;
    sceVu0FVECTOR pos;
    mgCTexture *tex;
    CCharacter2 *chara;

    void Initialize();

    void Generate(mgCTexture *new_tex, int new_kind, int x, int y);

    void Generate(mgCTexture *new_tex, int new_kind, CCharacter2 *new_chara);

    int IsRun();

    void Step();

    void Draw();

};
STATIC_ASSERT(sizeof(CLevelUpEffect) == 0x30);

class CLevelUpEffectManager {
public:
    mgCTexture *label_tex;
    mgCTexture *spark_tex;
    CLevelUpEffect effect[8];

    void Initialize();

    int IsRun();

    void Generate(int kind, int x, int y);

    void Generate(int kind, CCharacter2 *chara);

    void Step();

    void Draw();

};
STATIC_ASSERT(sizeof(CLevelUpEffectManager) == 0x190);

class CStarDust {
public:
    float x;
    float y;
    s16 life;
    u8 active;

    CStarDust();

    void Generate(int new_x, int new_y, int base_life, int rand_life);

    void Step();

    void Draw(mgCTexture *tex, int u, int v);

};
STATIC_ASSERT(sizeof(CStarDust) == 0xC);

class CEffVerticalLine {
public:
    sceVu0FVECTOR pos;
    float w;
    float h;
    float speed;
    float r;
    float g;
    float b;
    float alpha;
    float angle;
    float angle_add;

    void Generate(float *center, float range, float unk);

    void Step();

    void Draw();

};
STATIC_ASSERT(sizeof(CEffVerticalLine) == 0x40);

class CMenuEffect {
public:
    s16 tex_block;
    mgCTexture *tex;
    u8 end;
    s8 type;
    u8 run;
    s16 info_num;
    MENU_EFFECT_INFO *info;
    s16 base_info[16];
    s16 alpha;
    s16 counter;

    void Initialize();

    void PresetEffect(mgCMemory *stack, mgCTexture *new_tex, int new_type, int *base);

    void SetMemory(mgCMemory *stack);

    void SetTexInfo(mgCTexture *new_tex, int *new_tex_block);

    void SetBaseInfo(int *base, int preset, int mode, int num);

    void EffectStart();

    void PresetInfoAll(int mode);

    void PresetInfo(MENU_EFFECT_INFO *particle, int no, int mode);

    void Step();

    void Draw();

};
STATIC_ASSERT(sizeof(CMenuEffect) == 0x38);

void AttachMessageForm();

void Init_MENUFORM_MAKEBRD_INFO(MENUFORM_MAKEBRD_INFO *info);

void GetMenuItemIconTexGetXY(int item, mgRect<int> &out_rect);

mgCTexture *GetMenuItemIconTexInfo(int item, int kind);

void SetSpriteEnv(mgCDrawPrim *prim, int mode);

void PrimQuad(mgCDrawPrim *prim, float x, float y, mgRect<int> tex_rect);

void PrimQuad(mgCTexture *tex, float x, float y, mgRect<int> tex_rect, int a, int r, int g, int b);

void PrimQuad(mgCDrawPrim *prim, mgCTexture *tex, float x, float y, mgRect<int> tex_rect, int a, int r, int g, int b);

void PrimQuad(mgCTexture *tex, mgRect<int> put_rect, mgRect<int> tex_rect, int a, int r, int g, int b);

void PrimQuad(mgCDrawPrim *prim, mgCTexture *tex, mgRect<int> put_rect, mgRect<int> tex_rect, int a, int r, int g, int b);

void MenuClipRectCheck(mgRect<int> &rect);

void SetMenuScissor(mgRect<int> rect);

void ResetMenuScissor();

int SetModeMenuDrawItemBoard(int mode);

void EnableUseItemAlphaStep();

void InitSpectolRasterTable(mgCMemory *stack);

void DrawOneItem(mgCDrawPrim *prim, mgRect<float> rect, int item, int mode, MENU_PARTS_EFFECT_STRUCT1 *effect, u8 *rgba, int item_flag);

void MenuPresentBoxView(int x, int y, int &tex_block, mgCTexture *tex, mgCTexture *cursor_tex);

void PrimDrawNumber(mgCDrawPrim *prim, int number, int keta, int x, int y, mgRect<int> tex_rect, int space, int unk);

void PrimDrawNumber2(mgCDrawPrim *prim, int number, int keta, int x, int y, mgRect<int> tex_rect, int space, int unk);

void PrimFillRect4(mgCDrawPrim *prim, mgRect<float> rect, float *rgba0, float *rgba1, float *rgba2, float *rgba3);

void MenuReloadTexture(int &tex_block, int new_tex_block);

void MenuReloadCLUT(int no);

void DrawMenuFillBox(int alpha, int red, int green, int blue);

void DrawMenuFillBox(float x, float y, float w, float h, int alpha, int red, int green, int blue);

void DrawMenuFillBox(mgCDrawPrim *prim, float x, float y, float w, float h, int alpha, int red, int green, int blue);

mgCTexture *GetMenuDlTexture();

void InitMenuDl(mgCTexture *tex, int total_size);

int StepMenuDl(int add_size);

int StepMenuDl2(int size);

void DrawMenuDl(int &tex_block, int x, int y, int w, int alpha);

void DrawMenuDl(int alpha);

void CalcCommonBrdDrawInfo(float *pos, MENUFORM_MAKEBRD_INFO *info, ClsMes *mes);

void CommonBoardDraw(float *pos, int &tex_block);

void MenuCursorDraw(mgCTexture *tex, float *pos, float rot, int reverse, int alpha, float scale);

void MenuCursorDraw(mgCTexture *tex, float *pos, float rot, int alpha);

void DrawMenuTilePattern(mgCDrawPrim *prim, mgCTexture *tex, float x, float y, mgRect<int> tex_rect, int unk, u8 *rgba);

void DrawMenuMainFrmImg(int &tex_block, mgRect<int> put_rect, mgRect<int> tex_rect, int unk, int r, int g, int b, int a);

int GetMenuMainFrameEndFlag();

float *GetMenuMainFrameLeftTopPos(int unk);

float GetMenuMainFrameCount();

void MenuMainFrameModeSet(int mode, int reset);

void MenuMainFrameStep();

void MenuMainFrameDraw(int &tex_block, int alpha);

void MenuMainFrameImgDraw(int &tex_block);

void DrawMenuWakuStep();

void DrawMenuWakuRect(mgCTexture *tex, mgRect<float> rect, mgRect<int> tex_rect, int a, int r, int g, int b);

void DrawWakuCircle(mgCDrawPrim *prim, mgCTexture *tex, mgRect<float> rect, mgRect<int> tex_rect, float rot, float size, int a, int r, int g, int b);

void MenuPosDataTypeInit(MENUFORMPARTS_TYPE *part);

void MenuFormPartsPresetItem(MENUFORMPARTS_TYPE *part, int draw, int item, int sub_item);

void Func_MallocPartEffectInfo(MENUFORMPARTS_TYPE *part, mgCMemory *stack, int num);

void Func_SetPartEffectInfo(MENU_PARTS_EFFECT_STRUCT1 *effect, unsigned int type, short *param);

void MenuItemBrdSetInfo(int unk, int top_line, int max_line, int view_line);

void MenuItemBrdFrameDraw(int x, int y, int &tex_block, int a, int r, int g, int b);

void MenuItemBrdDraw(float *pos, mgRect<int> clip_rect, int &tex_block, int a, int r, int g, int b);

void MenuItemModeItemDraw(int &tex_block, mgRect<int> clip_rect, float *pos, MENUFORMPARTS_TYPE *parts, mgCTexture *cursor_tex, mgRect<int> cursor_rect, int unk);

void Menu3DivideTextureDraw(mgCDrawPrim *prim, mgRect<int> rect, short *tex_tbl, int unk);

void *GetMenuMainIconChar(int no);

void MenuDrawParamStep();

int CheckItemUseVariable(CGameDataUsed *item, CItemUseTarget *target);

void Func_MenuItemBrdPrepare(MENUFORMPARTS_TYPE *parts, CGameDataUsed *items, CGameDataUsed *target, int num);

void Func_MenuItemBrdPrepare2(MENUFORMPARTS_TYPE *parts, CGameDataUsed *items, CGameDataUsed *target);

int NowUseNeedItemCheck(CUserDataManager *user);

void Func_MenuIconDrawPrepare(MENUFORMPARTS_TYPE *part, CGameDataUsed *item, int unk);

void CheckItemBoardFunc_MenuIconDrawPrepare(CUserDataManager *user, MENUFORMPARTS_TYPE *parts);

void MenuItemBrdScrlBarStep(int top_line, int y, int manner);

void Func_MenuItemBrdPosStep(int top_line);

void Func_MenuItemIconSetEffectOne(MENUFORMPARTS_TYPE *part);

void MenuItemBrdItemIconEffectMalloc(mgCMemory *stack, MENUFORMPARTS_TYPE *parts, int num);

int MenuCapture(int tex_block, mgCMemory *stack, int unk);

void SetBGFrameForMenu(int tex_block, char *tex_name);

CStarDust *CheckNotRunStarDust(CStarDust *star, int num);

int CheckRunStarDust(CStarDust *star, int num);

void InitBuildUpInfoEffect(mgCMemory *stack, mgCTexture *tex, int num, float up_limit);

void SetBuildUpInfoChara(CCharacter2 *chara, float range);

void StepBuildUpInfoEffect();

void DrawBuildUpInfoEffect();

void InitFishBoiledEffect(int *pos, mgCTexture *tex);

int StepFishBoiledEffect();

void DrawFishBoiledEffect();

void SetEffectSpectolBreak(mgCMemory *stack, CMenuEffect *effect, int item);

void SetEffectSpectolFusion(mgCMemory *stack, CMenuEffect **effect, CGameDataUsed *item, int unk);

template <class T>
void PrimQuad(mgCDrawPrim *prim, mgRect<T> put_rect, mgRect<int> tex_rect);

extern u8 menu_limmit_displayflag[0x9C];

extern CMenuPosDataForm *MenuMesForm[9];

extern CGameDataUsed *MenuDrawItemInfo[150];

extern int MenuDrawItemInfoNum;

extern mgRect<int> GiftBoxWindowPutPos;

extern s16 Pos_ItemInGiftBox[3][2];

extern float MakeBoardDrawInfo[5];

extern mgRect<int> menu_long_hand;

extern CGameDataUsed *NowGiftBoxPtr;

extern CMenuPosDataForm *GiftBoxViewForm;

extern int NowGiftBoxSelect;

extern u8 GiftBoxViewFlag;

extern int *menu_randam_line_draw_postbl;

extern int MenuCursorReverseFlag;

extern s8 MenuItemBrdCalcManner;

extern float MenuItemBrdUnderBrdPosXY[2];

extern CMenuPosDataManage *MenuPosData;

extern mgCTexture *MenuFrameTex;
