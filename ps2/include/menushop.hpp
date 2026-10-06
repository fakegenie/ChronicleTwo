#pragma once

#include "common.h"

#include <cstring>

#include "menusys.hpp"
#include "scenesnd.hpp"
#include "userdata.hpp"

class CMenuPosDataForm;
class mgCMemory;
struct MENUFORMPARTS_TYPE;

enum SHOP_SELL_MODE {
    SHOP_SELL_MODE_MONEY = 0,
    SHOP_SELL_MODE_ROBO_ABS = 1,
    SHOP_SELL_MODE_MEDAL = 2,
    SHOP_SELL_MODE_DONY = 3,
};

enum SHOP_MENU_MODE {
    SHOP_MENU_MODE_BUY_LIST = 0,
    SHOP_MENU_MODE_BAG = 1,
    SHOP_MENU_MODE_BUY_NUM = 2,
    SHOP_MENU_MODE_SELL_NUM = 3,
    SHOP_MENU_MODE_BUY_ASK = 4,
    SHOP_MENU_MODE_SELL_ASK = 5,
    SHOP_MENU_MODE_BUY_ERROR = 6,
    SHOP_MENU_MODE_SELL_ERROR = 7,
};

enum SHOP_MENU_ERROR {
    SHOP_MENU_ERROR_NONE = -1,
    SHOP_MENU_ERROR_NO_MONEY = 1,
    SHOP_MENU_ERROR_BAG_FULL = 2,
    SHOP_MENU_ERROR_ITEM_LIMIT = 3,
    SHOP_MENU_ERROR_LAST_WEAPON = 4,
};

enum DONY_SHOP_STATUS {
    DONY_SHOP_STATUS_ALL_TAKEN = 0,
    DONY_SHOP_STATUS_NONE_YET = 1,
    DONY_SHOP_STATUS_OFFERED = 2,
};

enum QUEST_VIEW_MODE {
    QUEST_VIEW_MODE_QUEST = 0,
    QUEST_VIEW_MODE_SCOOP = 1,
};

enum {
    SHOP_ITEM_MAX = 0x40,
    SHOP_PRICE_MAX = 0x200,
    SHOP_LIST_LINE = 6,
    QUEST_VIEW_PHOTO_MAX = 0x1E,
    QUEST_VIEW_SCOOP_COUNT = 0x35,
};

struct DONY_SHOP_ITEM {
    s16 item_no;
    s8 level;
};

STATIC_ASSERT(sizeof(DONY_SHOP_ITEM) == 0x4);

struct SHOP_PRICE_INFO {
    s32 buy;
    s32 sell;
};

STATIC_ASSERT(sizeof(SHOP_PRICE_INFO) == 0x8);

class CShop {
public:
    s16 shop_id;
    u8 unk_2[0x2];
    s32 item_num;
    s32 item_no[SHOP_ITEM_MAX];
    s32 have_num[SHOP_ITEM_MAX];
    s32 once_item_chosen;
    SHOP_PRICE_INFO price[SHOP_PRICE_MAX];

    CShop() { memset(this, 0, sizeof(CShop)); }

    int GetItemNo(int no) {
        if (no < 0 || item_num <= no) {
            return 0;
        }
        return item_no[no];
    }

    int GetHaveNum(int no) {
        if (no < 0 || item_num <= no) {
            return 0;
        }
        return have_num[no];
    }

    void CheckSyojiHin();

    void CheckEventItem();

    void GetPrice(CGameDataUsed *item, int *buy, int *sell);

    int CheckMoney();

    int AddMoney(int money);

    void AnalyzeShopList(char *script, int size);
};

STATIC_ASSERT(sizeof(CShop) == 0x120C);

class CShopMenu : public CBaseMenuClass {
public:
    CMenuPosDataForm *trade_brd;
    CMenuPosDataForm *item_list;
    CMenuPosDataForm *shop_name_brd;
    CMenuPosDataForm *money_brd;
    CMenuPosDataForm *exp_brd;
    CMenuPosDataForm *medal_brd;
    float scrl_bar_step;
    MENUFORMPARTS_TYPE *scrl_bar_top;
    MENUFORMPARTS_TYPE *scrl_bar_body;
    MENUFORMPARTS_TYPE *scrl_bar_bottom;
    CMenuPosDataForm *item_brd;
    u_int *pack;
    s32 pack_size;
    u_int se_handle;
    CGameDataUsed shop_item;
    s32 bag_pos;
    s32 bag_top;
    s32 list_pos;
    s32 list_top;
    s32 total;
    s16 num_cursor;
    s16 num;
    s16 num_max;
    u8 unk_1ce[0x2];
    s32 arrow_flash[2];
    float list_x;
    float list_y;
    s16 shop_name_ofs_x;
    s16 shop_name_ofs_y;
    s16 price_mes_width;
    s16 unk_1e6;
    s16 no_price_mes_width;
    s16 unk_1ea;
    CScene::BGM_STATUS bgm_status;
    s32 error;
    u8 cursor_reset;
    u8 unk_20d[0x3];

    CShopMenu() {
        list_pos = 0;
        list_top = 0;
        bag_pos = 0;
        bag_top = 0;
        key_arg_no = 0;
        num_cursor = 0;
        total = 0;
        cursor_reset = 1;
        error = -1;
        num = 0;
        num_max = 0;
        arrow_flash[0] = 0;
        arrow_flash[1] = 0;
        list_x = 0.0f;
        list_y = 0.0f;
        shop_name_ofs_x = 0;
        shop_name_ofs_y = 0;
        price_mes_width = 0;
        unk_1e6 = 0;
        no_price_mes_width = 0;
        unk_1ea = 0;
        scrl_bar_top = NULL;
        scrl_bar_body = NULL;
        scrl_bar_bottom = NULL;
        pack = NULL;
        pack_size = 0;
        se_handle = 0;
        trade_brd = NULL;
        item_list = NULL;
        shop_name_brd = NULL;
        money_brd = NULL;
        exp_brd = NULL;
        medal_brd = NULL;
        item_brd = NULL;
    }

    void AttachForm();

    int IsCancelNoneLoadItem();

    void UpdataScrlBar();

    virtual void InitEnd();

    int KeyStep();

    void CalcTex();

    void CalcCursorPosition();

    CGameDataUsed *SearchNowPosItemExist();
};

STATIC_ASSERT(sizeof(CShopMenu) == 0x210);

class CMenuQuestView : public CBaseMenuClass {
public:
    s32 select;
    s32 top;
    s32 photo_no[QUEST_VIEW_PHOTO_MAX];

    void UnderMsg(int type);

    int SelectMax();

    virtual void InitEnd();

    int KeyStep();
};

STATIC_ASSERT(sizeof(CMenuQuestView) == 0x190);

int GetDonyShopLineUp(int *item_no, int *status);

void ShopSellListDraw(int &tex_block, float *pos);

void MenuShopInit(mgCMemory *stack, int *tex_block, int mode);

int MenuShopKey();

void MenuShopDraw();

void MenuNPCQuestViewInit(mgCMemory *stack, int *tex_block, int view_mode);

int MenuNPCQuestViewKey();

void MenuNPCQuestViewDraw();
