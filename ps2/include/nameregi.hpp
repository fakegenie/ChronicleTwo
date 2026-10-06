#pragma once

#include "common.h"

#include "font.hpp"
#include "menusys.hpp"

class CDC2Mes;
class mgCMemory;

enum NAMEREGI_TARGET {
    NAMEREGI_TARGET_ITEM    = 0,
    NAMEREGI_TARGET_ROBO    = 1,
    NAMEREGI_TARGET_KEYWORD = 2,
    NAMEREGI_TARGET_FISH    = 3,
    NAMEREGI_TARGET_SPHIDA  = 4,
};

enum NAMEREGI_FONT_MODE {
    NAMEREGI_FONT_MODE_ALPHA = 0,
    NAMEREGI_FONT_MODE_HIRA  = 1,
    NAMEREGI_FONT_MODE_KATA  = 2,
    NAMEREGI_FONT_MODE_KANJI = 3,
    NAMEREGI_FONT_MODE_KIGOU = 4,
    NAMEREGI_FONT_MODE_NUM   = 5,
};

enum NAMEREGI_MODE {
    NAMEREGI_MODE_INPUT   = 0,
    NAMEREGI_MODE_OPEN    = 1,
    NAMEREGI_MODE_CLOSE   = 2,
    NAMEREGI_MODE_MESSAGE = 13,
};

struct NAMEREGI_TARGET_INFO {
    s16 target;
    CGameDataUsed *item;
    char keyword[0x40];
};
STATIC_ASSERT(sizeof(NAMEREGI_TARGET_INFO) == 0x48);

struct MENU_SELECT_PARAM {
    int pos;
    int row;
};

struct NAMEREGI_KANJI_NODE {
    u8 code[2];
    u8 unk_2[2];
    NAMEREGI_KANJI_NODE *next;
};

struct NAMEREGI_KANJI_INDEX {
    u8 code[2];
    u8 unk_2[2];
    s16 num;
    u8 unk_6[2];
    NAMEREGI_KANJI_NODE *list;
    u8 unk_C[4];
};
STATIC_ASSERT(sizeof(NAMEREGI_KANJI_INDEX) == 0x10);

class CNameRegiMenu : public CBaseMenuClass {
public:
    int select_mode;
    MENU_SELECT_PARAM select;
    int command_pos;
    s32 unk_120;
    int kanji_cell_num;
    int kanji_page_num;
    int kanji_line_max;
    u8 cursor_snap;
    float cursor_x;
    float cursor_y;
    int cursor_cnt;
    RECT waku;
    int password_input;
    s32 unk_154;
    s16 button_flash[16];
    float select_box_x;
    float select_box_y;
    CFont name_font;
    int caret_cnt;
    float wave_angle;
    char old_name[0x61];
    char name[0x61];
    int name_pos;
    CFont grid_font[1];
    int message_open;
    float tile_scroll;
    char jis_table[0x800];

    int GetActiveFontMode();
    CNameRegiMenu();

    void CopyAsciiToJis(char *src, char *dst);

    void CopyJisToAscii(char *src, char *dst);

    void ConvertPositionNameRegi(int to_command);

    int CheckKanjiPosition(int key, short *step, int limit_no);

    int KeyStep();

    void GetSelectedActiveFont(char *dst);

    void ChangeFontSelectMode(int font_mode);

    void DrawBaseBoard();

    void DrawActiveFont();

    void StepMarkCursor();

    void DrawMarkCursor();

    void DrawSelectedWord();

    void DrawMessage();
};
STATIC_ASSERT(sizeof(CNameRegiMenu) == 0xBC8);

void SetEventKeyword(char *keyword, char *topic, int code);

int CheckDeleteNameRegisteItem(CGameDataUsed *item);

int CheckChronicleKanjiFont(mgCMemory *stack);

int GetNameRegistFontKanjiList(int cell, char *dst);

void AdjustWaku(CDC2Mes *mes, RECT *waku);

void ConvertShitJiss2Ascii(char *src, char *dst);

void ConvertAscii2ShitJiss(char *src, char *dst);

void NameRegistInit(mgCMemory *stack, int *tex_block, int open_type);

int NameRegistKey();

void NameRegistDraw();

int ConvertNameRegiBaseBoardTable(int font_mode);

extern NAMEREGI_TARGET_INFO Nameregi_Target;
