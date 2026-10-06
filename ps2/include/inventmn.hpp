#pragma once

#include "common.h"
#include "mg_memory.hpp"
#include "mg_tanime.hpp"
#include "memcard.hpp"
#include "menudraw.hpp"
#include "menusys.hpp"
#include "userdata.hpp"

struct InventFoundFlags {
    u8 flag[3];
};
STATIC_ASSERT(sizeof(InventFoundFlags) == 3);

class CActionChara;
class CDC2Mes;
class CMenuPosDataForm;
class mgCTexture;
struct ITEMCMD_RET_PARA;
struct BG_READ_INFO;

enum INVENT_MENU_MODE {
    INVENT_MODE_THINK      = 0,
    INVENT_MODE_CARD_LIST  = 2,
    INVENT_MODE_ITEM_LIST  = 3,
    INVENT_MODE_ALBUM_VIEW = 5,
    INVENT_MODE_PHOTO_VIEW = 6
};

enum INVENT_PHOTO_CHECK {
    INVENT_PHOTO_CHECK_NETA    = 0,
    INVENT_PHOTO_CHECK_NPC     = 2,
    INVENT_PHOTO_CHECK_MONSTER = 3
};

struct SCOOP_DATA {
    short scoop_id;
    short flag_no;
    s8    info_no;
    u8    unk_5[3];
    char *text;
    int   unk_c;
    int   unk_10;
};
STATIC_ASSERT(sizeof(SCOOP_DATA) == 0x14);

struct PIC_NAME_INFO {
    u16   neta_id;
    short unk_2;
    char *name;
};
STATIC_ASSERT(sizeof(PIC_NAME_INFO) == 0x8);

struct INVENT_MATERIAL {
    short item_id;
    u8    num;
    u8    unk_3;
};
STATIC_ASSERT(sizeof(INVENT_MATERIAL) == 0x4);

struct INVENT_MATERIAL_LIST {
    INVENT_MATERIAL *material;
    short num;
    u8 unk_6[2];
};
STATIC_ASSERT(sizeof(INVENT_MATERIAL_LIST) == 0x8);

struct MakeItemNeeds {
    struct Need {
        int item_id;
        int amount;
    };
    int num;
    Need need[4];
};
STATIC_ASSERT(sizeof(MakeItemNeeds) == 0x24);

struct INVENT_DATA_INFO {
    short            item_id;
    short            neta_id[3];
    union {
        struct {
    INVENT_MATERIAL *material;
    short            material_num;
    u8               unk_e[2];
        };
        INVENT_MATERIAL_LIST materials;
    };
    short            unk_10;
    u8               unk_12[2];
    float            model_pos[3];
    float            model_scale;
};
STATIC_ASSERT(sizeof(INVENT_DATA_INFO) == 0x24);

class CDC2AlbumData {
public:
    char              photo_work[50][0x2000];
    USER_PICTURE_INFO photo[50];
    u8                unk_644b0[0x800];

    CDC2AlbumData() { Initialize(); }

    void Initialize();

    void RelateAlbumPicData();

    void DeletePhotoData(int index);

    USER_PICTURE_INFO *GetAlbumPhotoInfo(int index);
};
STATIC_ASSERT(sizeof(CDC2AlbumData) == 0x64CB0);

class CInventDataManage {
public:
    short             num;
    INVENT_DATA_INFO *table;

    void Clear() {
        num = 0;
        table = NULL;
    }

    INVENT_DATA_INFO *GetInventDataInfoByItemID(int item_id);

    int CheckInventEnable(int *neta_id, int *near_match);

    int HowMuchZairyouMakeItem(int item_id, int count, int *result);

    int DeleteUserUsedItem(int item_id, int count);

    int CheckMakeItem(int item_id, int count, CGameDataUsed *item);

    int LoadAnalyzeInventFile(char *script, int size);
};
STATIC_ASSERT(sizeof(CInventDataManage) == 0x8);

class CMenuInvent : public CBaseMenuClass {
public:
    short                 photo_only;
    short                 unk_112;
    int                   card_cursor;
    int                   card_top;
    int                   item_cursor;
    int                   item_top;
    int                   photo_cursor;
    int                   photo_top;
    int                   album_cursor;
    int                   album_top;
    int                   memo_cursor;
    int                   memo_top;
    MENUFORM_MAKEBRD_INFO make_board;
    CGameDataUsed         create_item;
    MC_ICON_DATA          icon_data[3];
    u8                    card_scroll_dir;
    u8                    album_scroll_reset;
    u8                    unk_24e[2];
    float                 album_scroll_x;
    float                 album_scroll_y;
    u8                    album_enable;
    u8                    unk_259[3];
    float                 photo_scroll;
    float                 photo_bar;
    float                 photo_pos[30][2];
    u8                    memo_scroll_reset;
    u8                    unk_355[3];
    float                 memo_scroll;
    float                 memo_bar;
    int                   blink_count;
    u8                    unk_364[0xC];
    float                 neta_color[4];
    float                 scoop_color[4];
    short                 neta_effect_time;
    short                 unk_392;
    u_int                *create_sound_buffer;
    mgCMemory             data_stack;
    mgCTexture           *photo_tex[30];
    mgCTexture           *album_tex[50];
    s8                    album_flag[50];
    u8                    unk_53a[2];
    mgCMemory             chara_stack;
    u8                   *create_model_file;
    u8                   *create_motion_file;
    CActionChara         *create_chara;
    void                 *load_sound_buffer;
    INVENT_MATERIAL_LIST *make_material;
    short                 create_step;
    short                 create_item_id;
    int                   create_partial_match;
    int                   create_photo_neta[3];
    int                   create_missing_slot;
    s8                    create_photo_name[32];
    s8                    blink_time;
    u8                    unk_5b9[3];
    int                   neta_circle_snap;
    float                 neta_flash_angle;
    u8                    new_neta_photo[0x20];
    float                 create_spin_angle;
    float                 create_scale;
    float                 create_wobble_amp;
    float                 create_wobble_phase;
    u8                    create_show_phase;
    u8                    unk_5f5[3];
    float                 create_scale_in;
    s8                    create_load_state;
    u8                    unk_5fd[3];
    int                   create_timer;
    short                 jingle_state;
    short                 jingle_pending;
    short                 jingle_time;
    short                 create_wait_time;
    short                 neta_select_num;
    u8                    unk_60e[2];
    int                   neta_select_index[3];
    s8                    neta_select_type[3];
    s8                    neta_select_state[3];
    s8                    unk_622[3];
    u8                    unk_625[3];
    float                 neta_circle_radius;
    float                 neta_circle_angle;
    BG_READ_INFO         *chara_read_info;
    s8                    chara_load_step;
    u8                    unk_635[3];
    CActionChara         *sub_chara;
    CActionChara         *create_effect;
    s8                    unk_640;
    u8                    unk_641;
    short                 unk_642;
    u8                    unk_644[4];
    float                 unk_648;
    s8                    arrow_count;
    u8                    unk_64d[3];
    float                 effect_sway;
    float                 effect_bob;
    float                 effect_bob_angle;
    int                   effect_bob_count;
    float                 effect_sway_angle;
    u8                    unk_664[0xC];
    float                 chara_pos[4];
    float                 chara_make_pos[4];
    int                   line_pos[50][2];
    u8                    unk_820[0x528];
    mgCMemory             item_model_memory;
    int                   download_base;
    int                   unk_d7c;
    float                 neta_effect_pos[30][2];
    short                 neta_effect_alpha[30];
    int                   gradation_mode;
    int                   unk_eb0;
    u8                    card_scroll_reset;
    u8                    photo_scroll_reset;
    u8                    unk_eb6;
    u8                    unk_eb7;
    CMenuPosDataForm     *bg_form;
    CMenuPosDataForm     *itembrd_form;
    CMenuPosDataForm     *neta_board_form;
    MENUFORMPARTS_TYPE   *neta_board_bar[3];
    MENUFORMPARTS_TYPE   *neta_board_arrow;
    MENUFORMPARTS_TYPE   *neta_memo_arrow;
    CMenuPosDataForm     *makebrd_form;
    CMenuPosDataForm     *card_list_title_form;
    CMenuPosDataForm     *card_list_form;
    CMenuPosDataForm     *album_sw_form;
    CMenuPosDataForm     *album_big_form;
    CMenuPosDataForm     *neta_memo_form;
    CMenuPosDataForm     *neta_form[3];
    u8                    unk_efc[4];
    CMenuPosDataForm     *neta_name_form[3];
    u8                    unk_f0c[4];
    CMenuPosDataForm     *poly_chr_form[2];
    CMenuPosDataForm     *invent_okeff_form;
    CMenuPosDataForm     *dload_form;
    CMenuPosDataForm     *recbrd_form;
    CMenuPosDataForm     *kakudai_pic_form;
    MENUFORMPARTS_TYPE   *kakudai_pic;
    u8                    unk_f2c[4];

    CMenuInvent();

    void InitPhotoNetaBoardToAlbum(int from_album);

    int CheckRecoverPhotoNum();

    void AttachFormInfo();

    void LoadCharaCheck();

    USER_PICTURE_INFO *GetNowSelectedPictInfo();

    USER_PICTURE_INFO *GetPhotoInfoFromMode(int *num);

    void InitNetaCircle(int keep);

    int SetNetaCircle(int type, int index);

    int CancelNetaCircle(int mode);

    int GetNowSelectNetaID(int slot);

    int SelectedNetaPhotoAlready(int index);

    int SelectedNetaMemoListAlready(int index);

    void UpdataRecordBoard();

    void PrepareNextMode(int mode);

    CGameDataUsed *SearchNowPosItemExist();

    void CreateModeSwapForm(int swap);

    void GradationSet(int mode);

    void GradationStep();

    virtual void InitEnd();

    virtual void ExitEnd();

    void EnterDataMenu(unsigned char *pack);

    virtual int ItemCmdAfter(int command, ITEMCMD_RET_PARA *result);

    virtual int IsCreateObject(int select_key, int push_button);

    void CalcMakeBrd(int message);

    int EnableSelectMaxCardList();

    void CalcCursorPosition();

    virtual int IsMakeObject(int select_key, int push_button);

    void CalcTex();

    void BootExtendCommand();

    virtual int IsAskExtend(int select_key, int push_button);

    void PhotoNetaEnter(int index, int mode);

    void IsAccessAlbum();

    void GetNetaBoardCursorPosition(int index, int *pos);

    void GetNetaMemoCursorPosition(int line, int *pos);

    void UpdataNetaMemoStr();

    void NextDifferentMode(int next, int arg);
};
STATIC_ASSERT(sizeof(CMenuInvent) == 0xF30);

CInventUserData *GetInventUserDataPtr();

void Init_USER_PICTURE_INFO(USER_PICTURE_INFO *photo);

void Copy_USER_PICTURE_INFO(USER_PICTURE_INFO *src, USER_PICTURE_INFO *dst);

void PictureSeiton(USER_PICTURE_INFO *photo, char *work, int num);

void AttachPictTex(int block, mgCTexture **tex, USER_PICTURE_INFO *photo, int num);

int CheckPhotoDataNoNeed(USER_PICTURE_INFO *photo, int num, int *index);

int IsTakePhoto();

void TranslateInventUserData(CInventUserData *src, CInventUserData *dst);

SCOOP_DATA *GetScoopDataTable(int scoop_id);

SCOOP_DATA *GetScoopDataTableIndex(int index);

void InitScoopString();

void AnalyzeScoopString(mgCMemory *memory, char *script, int size);

void LoadFilePictureName();

char *GetPhotoName(USER_PICTURE_INFO *photo);

int GetPhotoNameStr(int neta_id, char *name);

char *GetPhotoNameCheck(USER_PICTURE_INFO *photo);

int CheckPhotoFlag();

int CheckInventItem(int item_id);

int CheckItemTable(int item_id, int *neta_id);

int CheckInventPhoto(int id, int check);

void MenuInventCreateCardDraw(int &tex_block, float *pos);

void PictureDraw(mgCTexture *tex, USER_PICTURE_INFO *photo, float x, float y, float scale, int alpha, int red,
                 int blue, int green);

void PictureDraw(int &tex_block, mgRect<float> rect, int picture_no, float scale, unsigned char *rgba);

void MenuInventPictureBoardDraw(float *pos, int &tex_block, int mode);

void MenuInventAlbumPictureDraw(float *pos, int &tex_block);

void MenuInventNetaMemoDraw(float *pos, int &tex_block);

int MenuInventInit(mgCMemory *memory, int *tex_block, int arg);

int MenuInventKey();

void MenuInventDraw();
