#pragma once

#include "common.h"

#include "gamedata.hpp"
#include "mg_tanime.hpp"
#include "nd_meswin.hpp"
#include "userdata.hpp"

class CMenuPosDataForm;

enum MesYesNoResult {
    MES_YESNO_NONE = 0,
    MES_YESNO_YES = 1,
    MES_YESNO_NO = 2,
};

enum MenuMoveItemMode {
    MENU_MOVE_ITEM_COPY = 0,
    MENU_MOVE_ITEM_STACK = 1,
    MENU_MOVE_ITEM_ONE = 2,
};

class CMenuFont : public CFont {
public:

    CMenuFont();
};
STATIC_ASSERT(sizeof(CMenuFont) == 0xB8);

class CDC2Mes : public ClsMes {
public:
    u8 msg_change;
    s8 cursor;
    s16 text_off_x;
    s16 text_off_y;
    s16 mes_no;
    u8 cursor_on;
    u8 put_centering;
    u8 scissor_on;
    u8 unk_2963[0xD];
    mgRect<int> scissor;
    char str[0xC1];
    u8 unk_2a41[0xF];

    CDC2Mes();

    void SetMessData(short *buff_system, short *buff);

    void MsgPreset(int preset);

    void MsgPreset(int preset, int unused);

    void SetMsgCursor(int cursor);

    int AddMsgCursor2(int min, int max, int loop);

    int AddMsgCursor(int step, int min, int max, int loop);

    int CommandMsgCursor();

    int YesNoCursor();

    int YesNoCursor2(int alt_button);

    int GetMsgCursor();

    int GetMsgItemNo(int index);

    void SetFontColor(int r, int g, int b, int a);

    void SetPutPos(int x, int y, int w, int h);

    void SetPutPos(int *pos);

    void SetAbsPos(int pos);

    int GetStringDrawWidthDC(char *str);

    void SetMovePosCenteringGyou(int line, int centre_x, int y);

    void SetMsgItemNo(int *mes_no, int num);

    void SetMsgItemNo(char **str, int num);

    void SetMsgVolumeNo(int *values, int num);

    void SetMsgVolumeNo(int *values, int *width, int num);

    void SetMsgVolumeNoOne(int value);

    void SetMsgItemPos(int *pos, int num);

    void MakeMsg(int mes_no);

    void MakeMsg(char *str);

    void MakeMsg(CGameDataUsed *item);

    void MakeMsg(CGameDataUsed *item, CGameDataUsed *weapon);

    void StepMsg();

    void DrawMsg();

    void SetMsgAlpha(int alpha);
};
STATIC_ASSERT(sizeof(CDC2Mes) == 0x2A50);

struct MENU_ITEM_MOVE_INFO {
    u8 active;
    u8 mode;
    u8 unk_2[2];
    CGameDataUsed *dest;
    CGameDataUsed item;
    s16 from[4];
};
STATIC_ASSERT(sizeof(MENU_ITEM_MOVE_INFO) == 0x7C);

class CMenuMoveItem {
public:
    s8 move_on;
    CMenuPosDataForm *form[2];
    MENU_ITEM_MOVE_INFO info[2];

    CMenuMoveItem() { Initialize(); }

    void Initialize();

    void AttachForm();

    int CheckMove();

    void SetMoveItemInfo(MENU_ITEM_MOVE_INFO *info, int *start, int *goal);
};
STATIC_ASSERT(sizeof(CMenuMoveItem) == 0x104);

class CMenuItemUse {
public:
    int item_no;
    int target_type;
    u8 unk_8[0x10];
    s32 unk_18;

    int CheckItemUseEnable(CGameDataUsed *item, int target_type, void *target);

    int UseItem(CGameDataUsed *item, int target_type, void *target);

    int UseItem(CGameDataUsed *item, CItemUseTarget *target);

    void Initialize();
};
STATIC_ASSERT(sizeof(CMenuItemUse) == 0x1C);

char *GetHatena();

char *GetMenuBigNum(int num);

void SetMenuBigNum2(char *buff, int num);

void SetMenuBigNum(char *buff, int num);

void MenuMesInit(ClsMes *mes);

int CheckRoboShieldKit(CUserDataManager *user, CGameDataUsed *target, int use, int *enable_num,
                       int *use_num);

int MenuUseItemCheckFunc(CGameDataUsed *item, CItemUseTarget *target, int use);

int CheckNowStateUseThisItem(CGameDataUsed *item, CItemUseTarget *target);

extern char *MenuBigNum[10];

extern int MenuUsedItemNo;

extern u32 MenuUsedItemType;

extern int MenuUsedNotErrorCode;

extern CItemUseTarget MenuUsedTarget;
