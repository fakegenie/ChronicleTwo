#pragma once

#include "common.h"

#include <cstring>

#include "font.hpp"
#include "mg_tanime.hpp"

class CCharacter2;
class mgCDrawPrim;

enum {
    MES_WIN_TBL_MAX = 450,
    MES_LINE_MAX = 20,
    MES_PAGE_MAX = 16,
    MES_NAME_MAX = 16,
    MES_NAME_LEN = 50,
    MES_VALUE_MAX = 16,
    MES_ITEM_MAX = 16,
    NAME_REGIST_MAX = 8,
    NAME_REGIST_LEN = 11,
    NAME_REGIST_USED = 6,
    NPC_NAME_CHARA_TOP = 8,
    NPC_NAME_CHARA_NUM = 56,
    MOVIE_CC_MAX = 20,
    MOVIE_CC_LEN = 350,
    WAKU_DATA_MAX = 9,
};

enum ClsMesState {
    CLSMES_CLOSED = 0,
    CLSMES_OPENING = 1,
    CLSMES_REVEALING = 2,
    CLSMES_SHOWN = 3,
    CLSMES_CLOSING = 4,
    CLSMES_PAGE_WAIT = 5,
    CLSMES_SCROLLING = 6,
};

enum MesWindowMode {
    MES_WIN_NONE = 0,
    MES_WIN_FUKIDASHI = 1,
    MES_WIN_HELP = 2,
    MES_WIN_FLOATING = 3,
    MES_WIN_VERSATILE_1 = 4,
    MES_WIN_YESNO = 5,
    MES_WIN_VERSATILE_3 = 6,
    MES_WIN_BOTTOM = 7,
    MES_WIN_VERSATILE_4 = 8,
    MES_WIN_DQ_FUKIDASHI = 9,
    MES_WIN_DQ_FUKIDASHI_2 = 10,
    MES_WIN_CENTRE = 11,
    MES_WIN_PLAIN = 12,
};

enum MesPreset {
    MES_PRESET_FUKIDASHI = 0,
    MES_PRESET_SYSTEM = 1,
    MES_PRESET_PLAIN = 2,
    MES_PRESET_NPC_NAME = 3,
    MES_PRESET_WINDOW = 4,
    MES_PRESET_SMALL_FUKIDASHI = 5,
    MES_PRESET_WINDOW_REVEAL = 6,
};

enum MesCode {
    MES_CODE_COLOR_A = 0xF200,
    MES_CODE_COLOR_B = 0xF300,
    MES_CODE_COLOR_G = 0xF400,
    MES_CODE_COLOR_R = 0xF500,
    MES_CODE_JUSTIFY = 0xF700,
    MES_CODE_SPACE_W = 0xF800,
    MES_CODE_MOVE_X = 0xF900,
    MES_CODE_ITEM_LAST = 0xFBE7,
    MES_CODE_ITEM_FIRST = 0xFBFE,
    MES_CODE_COLOR_DEFAULT = 0xFC00,
    MES_CODE_COLOR_HIGHLIGHT = 0xFC01,
    MES_CODE_GAIJI = 0xFD00,
    MES_CODE_WAIT = 0xFE00,
    MES_CODE_NEWLINE = 0xFF00,
    MES_CODE_END = 0xFF01,
    MES_CODE_SPACE = 0xFF02,
    MES_CODE_PAGE = 0xFF03,
    MES_CODE_VOICE_1 = 0xFF04,
    MES_CODE_VOICE_0 = 0xFF05,
    MES_CODE_VOICE_2 = 0xFF06,
};

enum MesLineShade {
    MES_SHADE_AUTO = -1,
    MES_SHADE_NORMAL = 0,
    MES_SHADE_DARK = 1,
    MES_SHADE_BRIGHT = 2,
    MES_SHADE_FAINT = 3,
    MES_SHADE_HIDDEN = 4,
};

enum MesSelectShade {
    MES_SELECT_SHADE_NONE = -1,
    MES_SELECT_SHADE_DARK = 0,
    MES_SELECT_SHADE_BRIGHT = 1,
    MES_SELECT_SHADE_FAINT = 2,
};

enum MesPrimSetup {
    MES_PRIM_SPRITE = 1,
    MES_PRIM_SHADED = 3,
    MES_PRIM_SHADED_2 = 4,
    MES_PRIM_UNTEXTURED = 7,
};

enum MesFukidashiLayer {
    MES_FUKIDASHI_OUTLINE = 1,
    MES_FUKIDASHI_BODY = 3,
};

enum MesTextColor {
    MES_COLOR_DARK = 0x80202020,
    MES_COLOR_GREY = 0x80686A6B,
};

struct MES_WIN_TBL {
    u16 code;
    s16 x;
    s16 y;
    u32 color;
    u8 wait;
};

STATIC_ASSERT(sizeof(MES_WIN_TBL) == 0x10);

class ClsMes : public CFont {
public:
    s32 fuchi;
    s32 npc_name_mode;
    s32 text_x;
    s32 text_y;
    s32 font_w;
    s32 font_h;
    float half_font_w_percent;
    s32 columns;
    s32 rows;
    s32 char_num;
    s32 text_w;
    s32 text_h;
    s32 page;
    s32 page_num;
    s32 page_chars[MES_PAGE_MAX];
    s32 last_x;
    s32 last_y;
    s32 window_mode;
    s32 bg_opaque;
    s32 fukidashi_centre_x;
    s32 fukidashi_centre_y;
    s32 fukidashi_x;
    s32 fukidashi_y;
    s32 fukidashi_w;
    s32 fukidashi_h;
    s32 fukidashi_pos;
    s32 tail_on;
    s32 tail_target_x;
    s32 tail_target_y;
    s32 tail_root_x;
    s32 tail_root_y;
    s32 tail_half_w;
    s32 tail_length;
    s32 tail_left_x;
    s32 tail_left_y;
    s32 tail_right_x;
    s32 tail_right_y;
    s32 tail_tip_x;
    s32 tail_tip_y;
    float fade_speed;
    float fade;
    s32 open;
    RECT abs_win;
    s32 abs_text_off_x;
    s32 abs_text_off_y;
    float draw_off_x;
    float draw_off_y;
    s32 point_x;
    s32 point_y;
    s32 unk_1c4;
    RGBAQ_TYPE win_color;
    float draw_speed;
    float draw_speed_def;
    s32 page_wait;
    s32 page_auto;
    s32 unk_1e0;
    s32 scroll_wait;
    float reveal;
    s32 reveal_num;
    s32 page_top;
    s32 unk_1f4;
    MES_WIN_TBL tbl[MES_WIN_TBL_MAX];
    s32 tbl_num;
    s32 scroll_y;
    s32 scroll_goal;
    s32 scroll_speed;
    u32 def_color;
    u32 color;
    s32 wait;
    s32 page_time;
    s32 page_auto_time;
    s32 mes_no;
    s32 text_ptr;
    char *mes_data;
    s32 mes_data_size;
    s32 push_button;
    s32 centering;
    s32 line_indent_on;
    u8 alpha;
    char name[MES_NAME_MAX][MES_NAME_LEN];
    s32 item_mes[MES_ITEM_MAX];
    s32 values[MES_VALUE_MAX];
    s32 value_width[MES_VALUE_MAX];
    s32 value;
    s32 value_sign;
    s32 value_zero;
    s32 value_half;
    s32 value_space;
    s32 digit_font;
    s32 space_w;
    s32 justify_w;
    s32 select;
    s32 goal_cursor_x;
    s32 goal_cursor_y;
    s32 cursor_x;
    s32 cursor_y;
    s32 select_shade;
    s32 cursor_centering;
    s32 cursor_time;
    s32 choice_pos[2][2];
    s32 select_top;
    s32 cursor_off_y;
    s32 voice_on;
    s32 voice_type;
    s32 voice_cnt;
    s32 close_time;
    s32 texture_block;
    s32 scissor_on;
    RECT scissor;
    s32 line_indent[MES_LINE_MAX];
    s32 line_pos[MES_LINE_MAX][2];
    s32 line_pos_on[MES_LINE_MAX];
    s32 line_shade[MES_LINE_MAX];
    u32 line_color[MES_LINE_MAX];
    s32 equip_on[MES_LINE_MAX];
    s32 equip_x[MES_LINE_MAX];
    s32 equip_y[MES_LINE_MAX];
    s32 line_w[MES_LINE_MAX];
    s32 line_alpha[MES_LINE_MAX];
    s32 cross_on[MES_LINE_MAX];
    s32 cross_x[MES_LINE_MAX];
    s32 cross_y[MES_LINE_MAX];
    s32 unk_271c[MES_LINE_MAX];
    s32 unk_276c[MES_LINE_MAX];
    s32 unk_27bc[MES_LINE_MAX];
    s32 unk_280c[MES_LINE_MAX];
    s32 delta_on[MES_LINE_MAX];
    s32 delta_x[MES_LINE_MAX];
    s32 delta_y[MES_LINE_MAX];
    short *buff;
    short *buff_system;
    s32 unk_2954;

    void DrawFukidashi_sub(mgCDrawPrim *prim, int dx, int dy, int mode);

    void DrawFukidashi(int dx, int dy, int mode);

    void SetDrawSpeed();

    float GetDrawSpeedDef();

    int GetCaptionOff();

    int GetPageAutoFlg();

    void SetMovePosGyou(int line, int x, int y) {
        if (line >= 0 && line < MES_LINE_MAX) {
            line_pos[line][0] = x;
            line_pos[line][1] = y;
            line_pos_on[line] = 1;
        }
    }

    int GetStrWidth(char *str);

    int GetStrWidth(int name_no);

    void AutoSetSub(CCharacter2 *speaker, CCharacter2 *listener, int *pos);

    void CalcMesWinXYFromFukidashiXY();

    void CalcFukidashiXY(int *pos);

    void AutoSet(int *pos);

    void SetHalfFontWPercent(float percent);

    ClsMes();

    void SetBuff(short *buff);

    void SetBuff_system(short *buff);

    void SetDefColor(unsigned int color);

    void Preset(int preset);

    void SetWindowMode(int mode);

    int GetWindowMode();

    void SetWindowBgOpaqueFlg(int opaque);

    void StepNpcName();

    void StepNormal();

    void Step();

    int State();

    void GoNextPage();

    int MyTextureMake_sub();

    void MyTextureMake();

    void MakeMesWinTbl_value(int *x, int *y);

    void MakeMesWinTbl_value(int value_no, int *x, int *y);

    void MakeMesWinTbl_str(char *str, int *x, int *y);

    void MakeMesWinTbl_str(int name_no, int *x, int *y);

    int MakeMesWinTbl_item(int code, int *x, int *y);

    int GetMesWidth_system(int mes_no);

    short *GetTextLineDataTop(int mes_no);

    short *GetTextLineDataTop_system(int mes_no);

    void InitMesWinTbl();

    int SetMesWinTbl(int code, short x, short y);

    int CalcSpaceW(int width, int font_w, unsigned short *text);

    int MakeMesWinTbl(int mes_no);

    int MakeMesWinTbl(char *str);

    void AddYokoHaba(int line, int width);

    void SetYokoHaba(int line, int width);

    void AddPage(int last, int page);

    void NeedMesWinWH(int mes_no);

    void NeedMesWinWH(char *str);

    void MakeMesWin_init(int reset_fade);

    void MakeMesWin(int mes_no);

    void MakeMesWin(char *str, int open, int reset_fade);

    int MakeAnd3DPosSet(char *str, float *pos, int dx, int dy);

    void DrawFukidashiShadow();

    void SetSelectCursorPos(RECT rect);

    RGBAQ_TYPE GetFontColor(int index, int *fuchi);

    int GetGyouAlpha(int line);

    void DrawFont();

    void SetGoalCursorXY();

    void StepSelectCursor(int steps);

    void DrawSelectCursor(mgCDrawPrim *prim);

    void DrawEquipment(mgCDrawPrim *prim);

    void DrawCross(mgCDrawPrim *prim);

    void DrawRightDelta(mgCDrawPrim *prim);

    void DrawDigit(mgCDrawPrim *prim, int digit, int x, int y, int alpha, RGBAQ_TYPE *color);

    void DrawPushButton(mgCDrawPrim *prim, int x, int y);

    void CalcCenteringXY(int *dx, int *dy);

    void SetAbsWinData(RECT *rect);

    void SetOuterRectXYFromFukidashiPos(RECT *rect);

    void DrawMesWin();

    void SetItemMes(int index, int mes) {
        if (index >= 0 && index < MES_ITEM_MAX) {
            item_mes[index] = mes;
        }
    }

    void Init() {
        int name_offset;
        int name_count;
        int i;

        npc_name_mode = 0;
        char_num = 0;
        text_w = 0;
        text_h = 0;
        page = 0;
        page_num = 0;
        for (i = 0; i < MES_PAGE_MAX; i++) {
            page_chars[i] = 0;
        }
        last_x = 0;
        last_y = 0;
        fade = 0.0f;
        open = 1;
        draw_speed = GetDrawSpeedDef();
        page_wait = 0;
        scroll_wait = 0;
        reveal = 0.0f;
        reveal_num = 0;
        page_top = 0;
        unk_1f4 = 0;
        InitMesWinTbl();
        color = def_color;
        wait = 0;
        page_time = 0;
        page_auto_time = 30;
        mes_no = -1;
        text_ptr = 0;
        alpha = 0x80;
        name_count = 0;
        name_offset = 0;
        do {
            memset(((ClsMes *)((char *)this + name_offset))->name[0], 0, MES_NAME_LEN);
            name_count++;
            name_offset += MES_NAME_LEN;
        } while (name_count < MES_NAME_MAX);
        for (int item_index = 0; item_index < MES_ITEM_MAX; item_index++) {
            item_mes[item_index] = -1;
        }
        for (int value_index = 0; value_index < MES_VALUE_MAX; value_index++) {
            values[value_index] = 0;
            value_width[value_index] = 0;
        }
        value = 0;
        value_sign = 0;
        value_zero = 1;
        value_half = 0;
        value_space = 0;
        digit_font = 0;
        space_w = -1;
        justify_w = -1;
        select = -1;
        goal_cursor_x = 0;
        goal_cursor_y = 0;
        cursor_x = 0;
        cursor_y = 0;
        select_shade = MES_SELECT_SHADE_DARK;
        cursor_centering = 0;
        cursor_time = 0;
        choice_pos[0][0] = -1;
        choice_pos[0][1] = -1;
        choice_pos[1][0] = -1;
        choice_pos[1][1] = -1;
        select_top = 0;
        cursor_off_y = 0;
        voice_on = 0;
        voice_type = 0;
        voice_cnt = 0;
        close_time = 0;
        scissor_on = 0;
        scissor.x = 0;
        scissor.width = 0;
        scissor.y = 0;
        scissor.height = 0;
        int pair_offset;
        int line_offset;
        int line_index;
        line_index = 0;
        line_offset = 0;
        pair_offset = 0;
        do {
            ((ClsMes *)((char *)this + line_offset))->line_indent[0] = 0;
            ((ClsMes *)((char *)this + pair_offset))->line_pos[0][0] = 0;
            ((ClsMes *)((char *)this + pair_offset))->line_pos[0][1] = 0;
            ((ClsMes *)((char *)this + line_offset))->line_pos_on[0] = 0;
            ((ClsMes *)((char *)this + line_offset))->line_shade[0] = MES_SHADE_AUTO;
            ((ClsMes *)((char *)this + line_offset))->line_color[0] = 0;
            ((ClsMes *)((char *)this + line_offset))->equip_on[0] = 0;
            ((ClsMes *)((char *)this + line_offset))->equip_x[0] = 0;
            ((ClsMes *)((char *)this + line_offset))->equip_y[0] = 0;
            ((ClsMes *)((char *)this + line_offset))->line_w[0] = 0;
            ((ClsMes *)((char *)this + line_offset))->line_alpha[0] = -1;
            ((ClsMes *)((char *)this + line_offset))->cross_on[0] = 0;
            ((ClsMes *)((char *)this + line_offset))->cross_x[0] = 0;
            ((ClsMes *)((char *)this + line_offset))->cross_y[0] = 0;
            ((ClsMes *)((char *)this + line_offset))->unk_271c[0] = -1;
            ((ClsMes *)((char *)this + line_offset))->unk_276c[0] = -1;
            ((ClsMes *)((char *)this + line_offset))->unk_27bc[0] = 0;
            ((ClsMes *)((char *)this + line_offset))->unk_280c[0] = 0;
            ((ClsMes *)((char *)this + line_offset))->delta_on[0] = 0;
            ((ClsMes *)((char *)this + line_offset))->delta_x[0] = 0;
            ((ClsMes *)((char *)this + line_offset))->delta_y[0] = 0;
            line_index++;
            line_offset += sizeof(int);
            pair_offset += sizeof(int) * 2;
        } while (line_index < MES_LINE_MAX);
    }
};

STATIC_ASSERT(sizeof(ClsMes) == 0x2958);

void MySetPrim(mgCDrawPrim *prim, int type, int bilinear);

void set2DSpriteEasy(mgCDrawPrim *prim, mgRect<int> xy, mgRect<int> uv, RGBAQ_TYPE *color);

void _set2DSprite(char *texture, mgCDrawPrim *prim, mgRect<int> xy, mgRect<int> uv, RGBAQ_TYPE *color);

void set2DSprite(mgCDrawPrim *prim, mgRect<int> xy, mgRect<int> uv, RGBAQ_TYPE *color);

void FillRect(int x, int y, int width, int height, int r, int g, int b, int a);

void GetScrPosFromChar(CCharacter2 *chara, int *pos);

void CalcAutoPosSetData(int screen_w, int screen_h, int width, int height, RECT *slots);

char *GetBuffMesIdPtr(char *buff, int size, int id);

short *SetAndGetNameRegistTbl(int no);

int GetItemNoFromFontNo(int code);

void PreMesMake(char *src, char *dst);

void CalcRectScale(RECT rect, float scale, RECT *out);

void DrawYesNo(mgCDrawPrim *prim, int yes_x, int yes_y, int no_x, int no_y, RGBAQ_TYPE *color);

void GetPos_AbsPosSet(RECT rect, int width, int height, int anchor, int *x, int *y);

float CalcAutoPosSet(float min, float max, float size, float ratio);

RGBAQ_TYPE RgbqToUint(unsigned int color);

void CalcWindowOutRectFromInRect(int mode, RECT in, RECT *out);

void CalcWindowInRectFromOutRect(int mode, RECT out, RECT *in);

void Parametric(float *from, float *to, float *dir);

int Quadratic(float a, float b, float c, float *root0, float *root1);

int CalcIntersectionPointSphereAndLine(float *centre, float radius, float *from, float *to, float *hit0, float *hit1);

int CheckPosInOutForArea(float *a, float *b, float *pos);

int CalcMoveNextPos(float *from, float *to, float speed, float *out);

void InitMovieCC();

void MyStrCpyLineFeed(char *dst, char *src);

void GetNextLineTop(char **text);

char *GetTopAddress(char *buff, int size, int id);

void MovieCCAnalyze(char *buff, int size, int movie_no);

void MovieCCDraw();

void MovieCCInit(char *buff, int size, int movie_no);

extern float p[16][2];

extern s32 waku_data[WAKU_DATA_MAX][4];

extern s32 MesAbsDrawOff;

extern s32 MovieCCCnt;

extern s32 MovieCCW;

extern s32 MovieCCH;

extern short NameRegistTbl[NAME_REGIST_MAX][NAME_REGIST_LEN];

extern CFont MovieCCFont;

extern s32 MovieCCStart[MOVIE_CC_MAX];

extern s32 MovieCCClear[MOVIE_CC_MAX];

extern char MovieCCStr[MOVIE_CC_MAX][MOVIE_CC_LEN];
