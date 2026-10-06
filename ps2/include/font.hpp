#pragma once

#include "common.h"

#include "mg_tanime.hpp"

class mgCDrawPrim;

struct RECT {
    s32 x;
    s32 y;
    s32 width;
    s32 height;
};

STATIC_ASSERT(sizeof(RECT) == 0x10);

struct RGBAQ_TYPE {
    u_long r : 8;
    u_long g : 8;
    u_long b : 8;
    u_long a : 8;
    u_long q : 32;
};

STATIC_ASSERT(sizeof(RGBAQ_TYPE) == 0x8);

enum {
    FONT_STR_MAX             = 0x80,
    FONT_NO_NONE             = -1,
    FONT_NO_NEWLINE          = -2,
    FONT_NO_ALPHABETICAL_TOP = 0x5E,
    FONT_NO_FONT_GAIJI_TOP   = 0x9D,
    FONT_NO_FONT_GAIJI_END   = 0xB5,
    FONT_NO_HALF_SPACE       = 0xFF02,
    FONT_TEX_PAGE_CHARS      = 0x260,
    FONT_TEX_COLUMNS         = 32,
    FONT_TEX_CHAR_W          = 16,
    FONT_TEX_CHAR_H          = 20,
    GAIJI_CODE_TOP           = 0xFD00,
    GAIJI_CODE_END           = 0xFD32,
    FONT_GAIJI_CODE_TOP      = 0xFDE0,
    FONT_GAIJI_CODE_END      = 0xFDF8,
    GAIJI_DATA_NUM           = 51,
    FCONV_CODE_NUM           = 46,
    FONT_GAIJI_CONV_NUM      = 24,
    ALPHABETICAL_CHARA_NUM   = 63,
    ALPHABETICAL_CHARA_LEN   = 5,
    FONT_TBL_BIN_SIZE        = 0x1000,
};

enum FontFuchi {
    FUCHI_NONE              = 0,
    FUCHI_SHADOW_WHITE      = 1,
    FUCHI_SHADOW_BLACK      = 2,
    FUCHI_OUTLINE           = 3,
    FUCHI_SHADOW_DOUBLE     = 4,
    FUCHI_SHADOW_BLACK_WIDE = 5,
    FUCHI_OUTLINE_WIDE      = 6,
    FUCHI_SHADOW_WHITE_BLUE = 7,
    FUCHI_OUTLINE_THICK     = 8,
    FUCHI_NUM               = 9,
};

enum FontPreset {
    FONT_PRESET_DARK      = 0,
    FONT_PRESET_DARK_2    = 1,
    FONT_PRESET_THICK     = 2,
    FONT_PRESET_THICK_2   = 3,
    FONT_PRESET_SHADOWED  = 4,
};

struct GAIJI_DATA {
    u16 code;
    s16 u;
    s16 v;
    s16 w;
    s16 h;
    s16 off_x;
    s16 off_y;
};

STATIC_ASSERT(sizeof(GAIJI_DATA) == 0xE);

struct FCONV_CODE {
    char *str;
    s32 len;
    u16 code;
};

STATIC_ASSERT(sizeof(FCONV_CODE) == 0xC);

struct FONT_TBL_BIN {
    u16 half_font_num;
    u16 kanji_top_no;
    u16 yoyaku_num;
    u16 unk_6;
    u8 yoyaku_tbl[0x7FC][2];
};

STATIC_ASSERT(sizeof(FONT_TBL_BIN) == FONT_TBL_BIN_SIZE);

class CFont {
public:
    char str[FONT_STR_MAX];
    s32 fuchi;
    s32 unk_84;
    RGBAQ_TYPE color;
    s32 alpha;
    s32 pos_x;
    s32 pos_y;
    s32 clearance_w;
    s32 clearance_h;
    s32 draw_w;
    s32 draw_h;
    s32 mini;
    float offset_x;
    float offset_y;

    CFont() { Init(); }

    int CheckKanjiFont(int font_no);

    int CheckHalfFont(int font_no);

    void SetDrawSize(int w, int h);

    void SetClearance(int w, int h);

    void SetPos(int x, int y);

    void SetColor(int r, int g, int b, int a);

    void SetColor(RGBAQ_TYPE color);

    void SetColor(unsigned int color);

    void SetFuchi(int fuchi);

    void SetStr(char *str);

    int GetDigitNo(int font_no);

    void DrawChar(mgCDrawPrim *prim, int font_no, int x, int y, int fuchi_on, RGBAQ_TYPE color, unsigned char alpha);

    void DrawChar(mgCDrawPrim *prim, char *str, int x, int y);

    void DrawGaiji(mgCDrawPrim *prim, int code, int x, int y);

    void CalcDrawWH(char *str, int *w, int *h);

    void DrawDirect(char *str, int x, int y);

    void Preset(int preset);

    void Init();
};

STATIC_ASSERT(sizeof(CFont) == 0xB8);

int GetGaijiW(int code);

int GetGaijiH(int code);

RECT GetRectFontTex(int font_no, int *tex_no);

void MySetTexMini(int tex_no, mgCDrawPrim *prim);

RECT GetRectFontTexMini(int font_no, int *tex_no);

char *My_strncpy(char *dst, const char *src, unsigned int n);

u8 *GetYoyakuTblTop();

int LoadFontTblBin();

int GetYoyakuTblNum();

int GetKanjiTopNo();

int GetHalfFontNum();

unsigned short GetGaijiFontNo(char *str);

int GetGaijiLen(unsigned short code);

unsigned short GetAlphabeticalFontNo_uc(unsigned char c);

unsigned short GetAlphabeticalFontNo_cp(char *str);

unsigned short GetFontGaijiFontNo(char *str);

unsigned short GetAlphabeticalFontNo_us(unsigned short code);

unsigned short GetFontNoFromFontGaijiCode(unsigned short code);

int GetFontGaijiHankaku(unsigned short code);

int GetFontNo(char *str);

int GetHalfFontNo(char c);

void set2DSpriteEasyFont(mgCDrawPrim *prim, mgRect<int> xy, mgRect<int> uv, RGBAQ_TYPE *color);

void set2DSprite_Fuchi(mgCDrawPrim *prim, RECT xy, RECT uv, int fuchi, int alpha);

void MySetTex(char *name, mgCDrawPrim *prim);

void MySetTex(int tex_no, mgCDrawPrim *prim);

void DrawGaiji_sub(mgCDrawPrim *prim, int code, int x, int y, RGBAQ_TYPE color, int line_h);

void UpDateWH(int *w, int *h, int x, int y);

extern GAIJI_DATA GaijiDataTbl[GAIJI_DATA_NUM];

extern FCONV_CODE FconvCodeTbl[FCONV_CODE_NUM];

extern FCONV_CODE FontGaijiConvTbl[FONT_GAIJI_CONV_NUM];

extern char alphabetical_chara_tbl[ALPHABETICAL_CHARA_NUM][ALPHABETICAL_CHARA_LEN];
