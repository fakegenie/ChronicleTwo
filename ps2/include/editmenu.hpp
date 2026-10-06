#pragma once

#include "common.h"

#include <libvu0.h>

#include "actionchara.hpp"
#include "menudraw.hpp"
#include "menusys.hpp"
#include "mg_memory.hpp"

class CDC2Mes;
class CEditHouse;
class CEditMap;
class CEditParts;
class CEditPartsInfo;
class CMapParts;
class CMenuPosDataForm;
class mgCTexture;
struct MENUFORMPARTS_TYPE;

#define GEORAMA_PARTS_LIST_MAX 0x180

#define GEORAMA_VIEW_MODE_NUM 7

#define GEORAMA_LIST_LINE_NUM 8

#define GEORAMA_PENKI_NUM 8

#define REMOVAL_NPC_LIST_MAX 0xB4

#define REMOVAL_NAME_LINE_MAX 10

enum GeoramaViewMode {
    GEORAMA_VIEW_MAKE        = 0,
    GEORAMA_VIEW_STOCK       = 1,
    GEORAMA_VIEW_PAINT       = 2,
    GEORAMA_VIEW_EDIT        = 3,
    GEORAMA_VIEW_CHECK_POINT = 4,
    GEORAMA_VIEW_ANALYZE     = 5,
    GEORAMA_VIEW_PLACED      = 6,
};

enum GeoramaSortMode {
    GEORAMA_SORT_NO        = 0,
    GEORAMA_SORT_NAME      = 1,
    GEORAMA_SORT_NAME_DESC = 2,
    GEORAMA_SORT_NUM       = 3,
};

enum GeoramaLoadPartKind {
    GEORAMA_LOAD_INFO_ID    = 0,
    GEORAMA_LOAD_INFO_INDEX = 1,
    GEORAMA_LOAD_PLACE      = 2,
};

struct GEORAMA_PARTS_LIST_ITEM {
    s32  no;
    s32  num;
    char name[0x30];
};

STATIC_ASSERT(sizeof(GEORAMA_PARTS_LIST_ITEM) == 0x38);

struct GEORAMA_LIST_INFO {
    s32 select;
    s32 top;
};

STATIC_ASSERT(sizeof(GEORAMA_LIST_INFO) == 0x8);

class CMenuGeorama : public CBaseMenuClass {
public:
    CEditPartsInfo        *parts_info;
    CEditParts            *place_parts;
    CMapParts             *view_parts;
    u8                     unk_11C[0x14];
    sceVu0FVECTOR          paint_color;
    s32                    town_no;
    s32                    start_wait;
    s32                    view_mode;
    s8                     view_loaded;
    s32                    top;
    s32                    select;
    s32                    polygon_left;
    s32                    paint_select;
    s32                    paint_top;
    s32                    free_color_select;
    s32                    paint_return;
    s32                    unk_16C;
    mgCMemory              parts_stack;
    s32                    sort_mode[3];
    s32                    unk_1AC;
    s32                    place_num;
    s32                    place_no[GEORAMA_PARTS_LIST_MAX];
    char                   place_name[GEORAMA_PARTS_LIST_MAX][0x40];
    s32                    placed_num;
    GEORAMA_PARTS_LIST_ITEM placed_list[GEORAMA_PARTS_LIST_MAX];
    s32                    stock_num;
    GEORAMA_PARTS_LIST_ITEM stock_list[GEORAMA_PARTS_LIST_MAX];
    s32                    make_num;
    GEORAMA_PARTS_LIST_ITEM make_list[GEORAMA_PARTS_LIST_MAX];
    s32                    house_num;
    GEORAMA_PARTS_LIST_ITEM house_list[GEORAMA_PARTS_LIST_MAX];
    MENUFORM_MAKEBRD_INFO  make_brd;
    CEditPartsInfo        *make_parts;
    GEORAMA_LIST_INFO      list_info[GEORAMA_VIEW_MODE_NUM];
    CMenuPosDataForm      *make_brd_form;
    CMenuPosDataForm      *free_color_form;
    CMenuPosDataForm      *title_form;
    CMenuPosDataForm      *cpview_form;
    s32                    unk_1B83C;
    float                  list_target_y[GEORAMA_VIEW_MODE_NUM];
    float                  scroll_bar_y[GEORAMA_VIEW_MODE_NUM];
    float                  scroll_bar_h[GEORAMA_VIEW_MODE_NUM];
    float                  list_pos[GEORAMA_VIEW_MODE_NUM][2];
    CMenuPosDataForm      *list_form[GEORAMA_VIEW_MODE_NUM];
    CMenuPosDataForm      *analyze_form;
    CMenuPosDataForm      *analyze_percent_form;
    CMenuPosDataForm      *house_info_form;
    s32                    sub_step;
    u8                     unk_1B8F8[8];

    CMenuGeorama() {
        view_mode = GEORAMA_VIEW_STOCK;
        top = 0;
        select = 0;
        make_parts = NULL;
        start_wait = 0;
        paint_select = 0;
        paint_top = 0;
        view_loaded = 0;
        parts_info = NULL;
        place_parts = NULL;
        view_parts = NULL;
        title_form = NULL;
        cpview_form = NULL;
        free_color_form = NULL;
        make_brd_form = NULL;
        house_info_form = NULL;
        unk_1B83C = 0;
        sub_step = 0;
        for (int i = 0; i < GEORAMA_VIEW_MODE_NUM; i++) {
            list_form[i] = NULL;
            list_target_y[i] = 0.0f;
            scroll_bar_y[i] = 0.0f;
            list_pos[i][1] = 0.0f;
            list_pos[i][0] = 0.0f;
        }
        analyze_form = NULL;
        analyze_percent_form = NULL;
        list_pos[GEORAMA_VIEW_ANALYZE][1] = 164.0f;
        memset(list_info, 0, sizeof(list_info));
        memset(place_no, 0, sizeof(place_no));
        memset(place_name, 0, sizeof(place_name));
        memset(placed_list, 0, sizeof(placed_list));
        stock_num = 0;
        memset(stock_list, 0, sizeof(stock_list));
        make_num = 0;
        memset(make_list, 0, sizeof(make_list));
        house_num = 0;
        memset(house_list, 0, sizeof(house_list));
        sort_mode[0] = 0;
        sort_mode[1] = 0;
        sort_mode[2] = 0;
        unk_1AC = 0;
    }

    virtual void InitEnd();

    virtual void ExitEnd();

    int GetPartsIDListNum(int mode);

    int GetNowMakePartsNum(int id);

    int ArrangePartsList(int list, int next);

    void UpdateGeoramaPartsList();

    int GetNowModeLoadPartsID();

    CEditPartsInfo *GetNowSelectEditPartsInfo(int mode, int line);

    void LoadGeoramaPart(int no, int kind);

    void UpdateGeoramaPartColor(int update);

    void AttachFormInfo();

    void SetGeoListInfo(int mode, int select, int top);

    int ReturnSelectMode(int script);

    int GetNowViewModeMax(int mode);

    int LRCheck();

    virtual int IsMakeObject(int key, int push);

    void CalcCursorPosition();

    void CalcTex();

    void CalcMakeBrd();
};

STATIC_ASSERT(sizeof(CMenuGeorama) == 0x1B900);

class CRemovalMenu : public CBaseMenuClass {
public:
    mgCMemory           data_stack;
    s32                 exit_wait;
    s32                 npc_list[REMOVAL_NPC_LIST_MAX];
    s32                 npc_num;
    s32                 place_no;
    mgCMemory           chara_stack;
    s32                 special_house;
    s32                 first_npc;
    CEditParts         *parts;
    CEditPartsInfo     *parts_info;
    CEditHouse         *house;
    s32                 model_state;
    s32                 model_wait;
    s32                 select_npc;
    s32                 unk_46C;
    CActionChara        chara;
    CMenuPosDataForm   *house_form;
    u8                  list_jump;
    s32                 list_scroll_dir;
    float               list_x;
    float               list_y;
    CMenuPosDataForm   *list_form;
    MENUFORMPARTS_TYPE *scroll_parts[3];
    MENUFORMPARTS_TYPE *line_parts[REMOVAL_NAME_LINE_MAX];
    CMenuPosDataForm   *npc_win_form;
    CMenuPosDataForm   *npc_chr_form;
    CMenuPosDataForm   *clip_form;
    s32                 select;
    s32                 top;

    CRemovalMenu() {
        data_stack.stSetBuffer(NULL, 0);
        chara_stack.stSetBuffer(NULL, 0);
        exit_wait = 0;
        place_no = 0;
        select_npc = 0;
        model_wait = 0;
        model_state = 0;
        chara.Initialize(NULL);
        parts = NULL;
        house = NULL;
        house_form = NULL;
        list_form = NULL;
        npc_win_form = NULL;
        npc_chr_form = NULL;
        clip_form = NULL;
        parts_info = NULL;
        list_x = 0.0f;
        list_y = 0.0f;
        npc_num = 0;
        memset(npc_list, 0, sizeof(npc_list));
        for (int i = 0; i < REMOVAL_NAME_LINE_MAX; i++) {
            line_parts[i] = NULL;
        }
        scroll_parts[0] = NULL;
        scroll_parts[1] = NULL;
        scroll_parts[2] = NULL;
        clip_form = NULL;
        select = 0;
        top = 0;
        key_arg_no = 0;
        special_house = 0;
        first_npc = -1;
    }

    void MakeNPCList();

    int KeyStep();
};

STATIC_ASSERT(sizeof(CRemovalMenu) == 0x1500);

void GetPenkiColor(int no, float *out_rgb);

int ConvGeoramaDataNo(int data_no);

void CheckMenuLine(int *select, int *top, int num, int line_num);

int MenuGeoramaInit(mgCMemory *stack, int open_type);

int MenuGeoramaKey();

void MenuGeoramaDraw();

void MenuGeoramaTitleDraw(int &tex_block, float *pos, int alpha);

void MenuGeoramaListDraw(int &tex_block, float *pos, int data_no, int alpha);

void MenuGeoramaAnalyzeDraw(int &tex_block, float *pos, int alpha);

void InitDownLoadAnaunce(mgCMemory *stack);

void DrawDownLoadAnaunceSwitch(int draw);

int StepDownLoadAnaunce(int push);

void DrawDownLoadAnaunce();

int MakeDownLoadAnaunce(int town_no, mgCMemory *stack, int *out_num, int *out_sub_num, int *out_height);

void InitMenuDl3(mgCTexture *texture);

int StepMenuDl3();

void MenuPlacedHouseDraw(int &tex_block);

void MenuMapPartsDraw(int &tex_block);

int CheckGekkaViewMode(int town_no);

int GetPenkiItemNo(int no);

void MakeMsgPartsItemInfo(CDC2Mes *mes, CEditPartsInfo *info, MENUFORM_MAKEBRD_INFO *brd);

void MenuRemovalInit(mgCMemory *stack, int *arg);

int MenuRemovalKey();

void MenuRemovalDraw();
