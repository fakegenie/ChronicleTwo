#pragma once

#include "common.h"

#include <libvu0.h>

#include "gamedata.hpp"
#include "mg_memory.hpp"
#include "mg_tanime.hpp"
#include "userdata.hpp"

class CActionChara;
class CCharacter2;
class CDC2Mes;
class CMenuEffect;
class CMenuPosDataForm;
class CRepairManager;
class mgCTexture;
struct MENUFORMPARTS_TYPE;

enum MENU_ASK_MODE {
    MENU_ASK_MODE_NONE         = 0,
    MENU_ASK_MODE_OPEN         = 1,
    MENU_ASK_MODE_CLOSE        = 2,
    MENU_ASK_MODE_HOW_MUCH     = 3,
    MENU_ASK_MODE_ITEM_COMMAND = 4,
    MENU_ASK_MODE_CREATE       = 5,
    MENU_ASK_MODE_MAKE         = 6,
    MENU_ASK_MODE_SPECTOL      = 7,
    MENU_ASK_MODE_FUSION       = 8,
    MENU_ASK_MODE_TRUSH        = 9,
    MENU_ASK_MODE_ITEM_USE_NUM = 10,
    MENU_ASK_MODE_GIFT_BOX     = 11,
    MENU_ASK_MODE_EXTEND       = 12,
};

enum MENU_SELECT_KEY {
    MENU_SELECT_KEY_UP    = 0x1,
    MENU_SELECT_KEY_DOWN  = 0x2,
    MENU_SELECT_KEY_LEFT  = 0x4,
    MENU_SELECT_KEY_RIGHT = 0x8,
    MENU_SELECT_KEY_L1    = 0x10,
    MENU_SELECT_KEY_R1    = 0x20,
    MENU_SELECT_KEY_L2    = 0x40,
    MENU_SELECT_KEY_R2    = 0x80,
};

enum MENU_PUSH_BUTTON {
    MENU_PUSH_BUTTON_DECIDE   = 0x1,
    MENU_PUSH_BUTTON_CANCEL   = 0x2,
    MENU_PUSH_BUTTON_TRIANGLE = 0x4,
    MENU_PUSH_BUTTON_SQUARE   = 0x8,
    MENU_PUSH_BUTTON_SELECT   = 0x10,
    MENU_PUSH_BUTTON_START    = 0x20,
    MENU_PUSH_BUTTON_R3       = 0x40,
    MENU_PUSH_BUTTON_L3       = 0x80,
};

enum MENU_INPUTKEY_TYPE {
    MENU_INPUTKEY_TYPE_LINE = 0,
    MENU_INPUTKEY_TYPE_GLID = 1,
};

enum MENU_SWAP_TYPE {
    MENU_SWAP_TYPE_ACTIVE_ITEM = 0,
    MENU_SWAP_TYPE_EQUIP = 1,
    MENU_SWAP_TYPE_ROBO_PART = 2,
    MENU_SWAP_TYPE_ITEM_BOARD = 3,
    MENU_SWAP_TYPE_UNK_4 = 4,
    MENU_SWAP_TYPE_UNK_9 = 9,
    MENU_SWAP_TYPE_ACTIVE_ESA = 10,
};

struct MENU_SWAPITEM_INFO {
    s16 flag;
    s16 type;
    s16 no;
    s16 chara;

    void Set(int type, int no, int chara, int flag);
};
STATIC_ASSERT(sizeof(MENU_SWAPITEM_INFO) == 0x8);

struct MENU_ASKMODE_PARA {
    s16 unk_0;
    s16 mes_no;
    s16 cmd_num;
    s16 unk_6;
    int cmd_msg[8];
    u32 cmd_color[8];
    s16 unk_48[8];
    s16 cmd_mark[8];
    s16 arg0;
    s16 arg1;
    s16 unk_6C;
    s16 unk_6E;
    s16 unk_70;
    s32 unk_74;
    CMenuPosDataForm *form;
    CGameDataUsed *item;
    CGameDataUsed *item2;
    s32 unk_84;
    s32 unk_88;
    s32 unk_8C;
    s32 unk_90;

    MENU_ASKMODE_PARA();

    void Initialize();
};
STATIC_ASSERT(sizeof(MENU_ASKMODE_PARA) == 0x94);

struct ITEMCMD_RET_PARA {
    s16 cmd;
    s8 unk_2;
    s8 chara;
    s16 result;
    s16 item_no;
    s16 unk_8;
    s16 unk_A;
    CGameDataUsed *item;
    CGameDataUsed *item2;
};
STATIC_ASSERT(sizeof(ITEMCMD_RET_PARA) == 0x14);

class CMENU_USERPARAM {
public:
    CHARA_DATA *chara[2];
    ROBO_DATA *robo;
    MOS_CHANGE_PARAM *monster;
    CGameDataUsed *used_data;
    MOS_CHANGE_PARAM *monster1;

    CMENU_USERPARAM() { Initialize(); }

    void Initialize();

    void AttachInfo();
};
STATIC_ASSERT(sizeof(CMENU_USERPARAM) == 0x18);

struct MENU_INPUTKEY_ARG {
    s16 step[4];
    int type;
    s16 min;
    s16 max;
    u8 disp_lines;
    u8 disp_columns;
    u8 rows;
    u8 columns;
    s16 limit[4];
    s16 exit_no[4];
};
STATIC_ASSERT(sizeof(MENU_INPUTKEY_ARG) == 0x24);

class CBaseMenuClass {
public:
    s16 mode;
    s16 step;
    u8 opened;
    s16 unk_6;
    char *script;
    int script_size;
    s32 unk_10;
    s16 key_arg_no;
    int tex_block[16];
    MENU_ASKMODE_PARA ask_para;
    MENU_SWAPITEM_INFO swap_info;
    s16 cmd_arg_pos;
    s32 unk_F8;
    s32 unk_FC;
    int make_num;
    s32 unk_104;
    s8 make_cursor;
    s16 make_num_max;

    CBaseMenuClass();

    virtual int IsCreateObject(int select_key, int push_button);

    virtual int IsMakeObject(int select_key, int push_button);

    virtual int IsAskExtend(int select_key, int push_button);

    virtual int ItemCmdAfter(int cmd_ret, ITEMCMD_RET_PARA *ret);

    virtual void InitEnd();

    virtual void ExitEnd();

    void SetTexBlock(int *blocks);

    void DeleteTexBlock();

    int MenuItemCommnadSelectPrepare(CGameDataUsed *item, int arg_pos, int chara);

    int MenuItemMoveItemCommand(CGameDataUsed *item, int arg_pos, int mes_no, CMenuPosDataForm *form, int chara);

    int MenuItemCommandSelect(int select_key, int push_button);

    void SetItemCmdMsgPos(int *pos);

    void MenuItemAskMode_HowMuch(int select_key, int push_button);

    int CheckSpectolFusion(CGameDataUsed *item, int mes_no, CMenuPosDataForm *form);

    int IsSpectolTrans(int select_key, int push_button);

    int IsSpectolFusion(int select_key, int push_button);

    int IsTrush(int select_key, int push_button);

    int IsItemUseNum(int mes_no, int select_key, int push_button, CGameDataUsed *item, CItemUseTarget *target);

    int SelectInGiftBox(int select_key, int push_button);

    void SetAskHowMuchItemNum(MENU_SWAPITEM_INFO *swap, CGameDataUsed *item);

    void SetAskParam(MENU_ASKMODE_PARA *para);

    void ExeScript(char *command_name);

    int ExtendCommand(int select_key, int push_button);

    int SelectMakeObject(int select_key);

    void IsAskEnd(int se_no, CMenuPosDataForm *form);

    void FadeInMenu(int frames, float unused);

    void FadeOutMenu(int frames, float unused);

    int FadeCheckMenu();

    void EffectDrawCheck(CMenuPosDataForm *form);
};
STATIC_ASSERT(sizeof(CBaseMenuClass) == 0x110);

#pragma push
#pragma cpp_extensions on
class CMenuKeyFunc {
public:
    u8 unk_0;
    u8 key_enable;
    u8 key_input;
    u32 select_key;
    int push_button;
    int tex_block[16];
    s32 unk_4C;
    s16 open_type;
    int now_mode;
    int next_mode;
    s16 up_arrow_cnt;
    s16 down_arrow_cnt;
    u_int *pack;
    int pack_size;
    s16 waku_type;
    s32 unk_6C;
    union {
        struct { int cursor; int top_line; };
        int select_pos[2];
    };
    int save_cursor;
    int save_top_line;
    u8 return_item;
    u8 unk_81[0xF];
    mgRect<int> rect;
    CUserDataManager *user_data;
    u8 unk_A4[0x1C];
    CGameDataUsed have_item;
    MENU_SWAPITEM_INFO have_swap;
    MENU_INPUTKEY_ARG *key_arg;
    CMenuPosDataForm *cursor_form;
    CMenuPosDataForm *waku_form;
    CMenuPosDataForm *how_much_form;
    MENUFORMPARTS_TYPE *have_icon;
    MENUFORMPARTS_TYPE *have_shadow;
    MENUFORMPARTS_TYPE *have_num;
    int bgm_vol;
    int bgm_step;
    s16 bgm_target;
    s16 bgm_fading;
    s32 unk_15C;

    CMenuKeyFunc() {
        have_swap.Set(-1, 0, -1, 0);
        Initialize();
    }

    void Initialize();

    void AttachFuncData();

    int GetActiveCharaNo();

    int MenuPosStep(int *pos, int *offset);

    void MenuSetPos(int x, int y);

    void MenuPosStop();

    void MenuPosPlay();

    void SetMoveMethod(int method);

    void SetWakuMoveMethod(int method);

    void GetItemPos(int *pos);

    void SetWakuType(int type);

    void SetWakuWH(int no, int width, int height);

    void SetVibeCnt(int count0, int count1);

    void SetVibeR(int range0, int range1);

    void GetCursorPos(int *pos);

    int GetTopLine() { return top_line; }

    void CursorFadeIn(float frames, int alpha);

    void CursorFadeOut(float frames, int alpha);

    int EnableSwapNowPos(MENU_SWAPITEM_INFO *swap);

    int GetItemAll(CGameDataUsed *item, MENU_SWAPITEM_INFO *swap);

    void SelDataInit();

    int CheckSelectKey();

    int CheckLRKey();

    int CheckPushButton();

    float CheckAnalogKey(int stick, float *dir);

    u8 CheckKeyInput();

    int GetDebugInputKey(int &x, int &y);

    int MenuSwapItem(CGameDataUsed *item, MENU_SWAPITEM_INFO *swap, int num, bool flag);

    int ReturnItemMenu(int hide);

    void InitHaveData();

    void SetHaveItemInfo(int visible, int update);

    int menu_inputkey_limmit_check_line(int select_key);

    int menu_inputkey_limmit_check_glid(int select_key);

    int CheckMoveSelect(int select_key);

    void FadeOutMenuBGMVol(int step, int target);

    void FadeInMenuBGMVol(int step);

    s16 StepMenuBGM();
};
STATIC_ASSERT(sizeof(CMenuKeyFunc) == 0x160);
#pragma pop

class CMenuItemInfo : public CBaseMenuClass {
public:
    s16 view_mode;
    s16 unk_112;
    s16 sub_view;
    s16 view_chara;
    s16 load_item_no;
    s16 mos_id;
    s32 unk_11C;
    s16 equip_list[8];
    u8 equip_flag[8];
    s16 load_weapon_no;
    u8 reset_cursor_pos;
    sceVu0FVECTOR camera_ref;
    sceVu0FVECTOR camera_pos;
    u8 viewing_weapon;
    u8 unk_161[0xB];
    u8 repair_running;
    u8 effect_pos;
    u8 sound_loaded;
    u8 sound_load;
    u8 item_consumed;
    s16 equipped_model_no;
    s16 chara_reload;
    s16 sub_menu;
    s16 next_sub_menu;
    CGameDataUsed *view_weapon;
    CMenuPosDataForm *view_form[6];
    s16 status_check_ready;
    CMenuPosDataForm *item_board_form;
    s32 unk_1A0;
    CMenuPosDataForm *money_form;
    CMenuPosDataForm *chara_poly_form[2];
    CMenuPosDataForm *fill_form;
    MENUFORMPARTS_TYPE *item_board_icon;
    MENUFORMPARTS_TYPE *wep_parts[2][16];
    u8 unk_238[0x68];
    MENUFORMPARTS_TYPE *robo_parts[6];
    MENUFORMPARTS_TYPE *hp_bar[2];
    MENUFORMPARTS_TYPE *item_parts[2][3];
    MENUFORMPARTS_TYPE *item_num[2][3];
    MENUFORMPARTS_TYPE *voice_part;
    CActionChara *build_up_chara;
    s32 build_loading;
    s16 unk_2FC;
    s16 debug_item_no;
    u8 debug_item_count;
    CGameDataUsed debug_item;

    virtual int IsAskExtend(int select_key, int push_button);

    virtual int ItemCmdAfter(int cmd_ret, ITEMCMD_RET_PARA *ret);

    virtual void ExitEnd();

    void Initialize();

    void SetEquipListNo(int list_no);

    int CheckEquipListNo(int list_no);

    int CheckSoundLoad();

    CGameDataUsed *SearchNowPosItemExist();

    void IsCancelNoneLoadItem();

    int IsCancelLoadItem();

    void SaveViewWeaponStatus();

    void CheckViewWeaponStatus(int returned);

    int ReturnActiveCharaViewMode(int mode);

    void NextModeBuildUpInfo(CGameDataUsed *weapon);

    int EquipDirect(int chara, CGameDataUsed *item, int &slot);

    void CheckLoadInfo(int chara);

    void EnterDataMenu(unsigned int *pack);

    s16 GetActiveCharaIDForItemCmd();

    int GetActiveCharaNo();

    void AttachFormInfo();

    void MenuModeMalloc(mgCMemory *stack);

    void CalcTex();

    void CalcCursorPosition();

    int PushKey(int select_key, int push_button);

    void CheckLoadItemNo();

    int ModelReadStart(int mode, int chara, int flag);

    void WeaponBuildCheck(CActionChara *chara, int chara_no, int flag);

    int ModelReadEndCheck();

    void SearchEffectDisplayPosition(int *pos, CGameDataUsed *item);

    void SetItemEffect();

    int LRCheck(int key);

    void KeyStepLocal(int select_key, int push_button, int flag);

    int KeyStep();
};
STATIC_ASSERT(sizeof(CMenuItemInfo) == 0x370);

class CItemSelect : public CBaseMenuClass {
public:
    int item_num;
    CGameDataUsed *item_list[150];
    s8 limit_disp[150];
    s16 alpha_step;
    int alpha;
    int bg_alpha;
    s32 unk_40C;
    mgRect<float> list_rect;
    mgRect<float> item_rect;
    float cursor_x;
    float cursor_y;
    float scroll;
    mgCTexture *texture;
    int cursor;
    int top_line;
    float line_num;
    s32 unk_44C;

#ifdef NONMATCHING
    CItemSelect() {
        list_rect.Set(0.0f, 0.0f, 0.0f, 0.0f);
        item_rect.Set(0.0f, 0.0f, 0.0f, 0.0f);
        alpha_step = 0;
        alpha = 0;
        bg_alpha = 0;
        item_num = 0;
        cursor_y = 0.0f;
        cursor_x = 0.0f;
        scroll = 0.0f;
        texture = NULL;
        top_line = 0;
        cursor = 0;
        line_num = 1.0f;
    }
#else
    CItemSelect();
#endif

    void SetPtrList();

    CGameDataUsed *GetExistThisPosData(int pos);

    void CheckUse(CGameDataUsed *item);

    int KeyStep();

    void Draw();
};
STATIC_ASSERT(sizeof(CItemSelect) == 0x450);

struct MENU_ITEM_CURSOR_INFO {
    u8 enable;
    u8 arrow[5];
    u8 chara_mark;
    u8 unk_7;
    int counter;
};
STATIC_ASSERT(sizeof(MENU_ITEM_CURSOR_INFO) == 0xC);

struct BUILDUP_WEAPON_INFO {
    s16 unk_0;
    s8 mode;
    s8 select_no;
    s16 build_up;
    s16 unk_6;
    int select_num;
    int weapon_no[3];
    int enable[3];
    CGameDataUsed *weapon;
    s32 unk_28;
    CDataWeapon *weapon_data[3];
    s32 unk_38[3];
};
STATIC_ASSERT(sizeof(BUILDUP_WEAPON_INFO) == 0x44);

int CheckEquipFishRod(CGameDataUsed *item);

int IsDispTrushCommand(CGameDataUsed *item);

void SetPreCmdTrush(CBaseMenuClass *menu, int mes_no, CGameDataUsed *item, CMenuPosDataForm *form);

void SetPreCmdSpectolBreak(CBaseMenuClass *menu, int mes_no, CMenuPosDataForm *form, CGameDataUsed *item,
                           CGameDataUsed *item2);

void SetPreCmdGiftBoxSelect(CBaseMenuClass *menu, CGameDataUsed *gift_box);

int IsEnableChangeRoboParts(CGameDataUsed *part);

void SetSpectolInfo(CGameDataUsed *item, CGameDataUsed *weapon);

void FusionColor(int type, int step, float *color);

int CheckNowRoboUseCapacity(int *capacity);

int ExchangeItemInfoMake(MENU_SWAPITEM_INFO *swap, int (*table)[4], int pos, int type);

void MenuCheckLine(int *top_line, int pos, int disp_lines);

int MenuKeySelectCheck(int step, int *pos, int *top_line, int min, int max, int disp_lines, int limit);

int MenuListKeyCheck(int select_key, int *pos, int *top_line, int min, int max, int disp_lines, int limit);

int MenuGlidKeyCheck(int select_key, int *pos, int *top_line, int *size, int *disp, int *limit, int max);

int MenuListSelectKeyCheck(int select_key, int page_lines);

int MenuItemBrdKey(int select_key, int *pos, int *top_line, int limit);

int MenuCheckPushButton();

int ConvertCheckPushButton(int push_button);

CGameDataUsed *GetGameDataUsedForSWAPINFO(MENU_SWAPITEM_INFO *swap);

void CheckEnableHaveItemNum();

void MenuMoveItemPos(int *pos, int *top_line, int select_key);

void CommonSetMoveItemClass(int (*table)[4]);

int MenuItemInit(mgCMemory *stack, int *tex_block, int mode);

int CheckBuildUp(CGameDataUsed *weapon, int *result0, int *result1, int *result2);

int BuildUpWeaponTrans(CGameDataUsed *weapon, int no);

void MenuWeaponBuildUpDraw(int &tex_block);

void MenuCharaStatusDraw(int &tex_block);

void MenuItemInfoCursorDraw(int &tex_block);

int MenuItemKey();

void MenuItemDraw();

void MenuItemSelectInit(mgCMemory *stack, int *tex_block, int mode);

int MenuItemSelectKey();

void MenuItemSelectDraw();

extern s16 menu_item_swap_sndtbl[8];

extern int trans_spectol_pos;

extern CRepairManager *MenuRepairMan;

extern u8 menu_chara_activeItem_limmit_check[6];

extern s8 MenuStatusMode;

extern mgCTexture *MenuStatusTex;

extern CItemUseTarget MenuItemUseTarget;

extern CMenuEffect *MenuEffect[];

extern CGameDataUsed *SpectolInfo[2];

extern CCharacter2 *SpectolFusionTargetChara;

extern s16 MenuItemCmdArgPos;

extern int MenuItemCommandDir;

extern float trans_spectol_cnt;

extern u8 itemmenu_chr_rotflag;

extern mgCTexture *Tex_BuildUpBoard;

extern CMENU_USERPARAM MenuUserParam;

extern MENU_ITEM_CURSOR_INFO MenuItemCursorInfo;

extern mgCMemory MenuCharaLoadStack;

extern BUILDUP_WEAPON_INFO BuildUpWeaponInfo;

extern CGameDataUsed SepectolFusionBeforeAfterCheck;

extern s16 BuildUpNameXY[3][2];
