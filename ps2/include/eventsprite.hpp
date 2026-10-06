#pragma once

#include "common.h"

#include <libvu0.h>

float ParabolicInitialVectorY(float start_y, float end_y, float gravity, float frames);

void CalcPosParabolicJump(float *pos, float *start, float *end, float gravity, float frames, float frame);

class CMarker {
public:
    int count;

    CMarker() { Init(); }

    void Draw();

    void Set(int count);

    void Init();
};
STATIC_ASSERT(sizeof(CMarker) == 0x4);

enum EVENT_SPRITE_ANIME {
    EVENT_SPRITE_ANIME_NONE = -1,
    EVENT_SPRITE_ANIME_MOVE = 0,
    EVENT_SPRITE_ANIME_FADE = 1,
};

class CEventSprite {
public:
    int  draw;
    int  tex_block;
    char name[0x40];
    int  color[4];
    int  get[4];
    int  put[4];
    int  anime[4];

    CEventSprite() { Init(); }

    void SetName(char *name);

    void SetDraw(int draw);

    void SetGet(int x, int y, int w, int h);

    void SetPut(int x, int y, int w, int h);

    void SetMove(int x, int y, int frames);

    void SetFade(int fade_in, int frames);

    void SetColor(int r, int g, int b, int a);

    void Step();

    void Draw();

    void Init();
};
STATIC_ASSERT(sizeof(CEventSprite) == 0x88);

class CEventSpriteMother {
public:
    CEventSprite sprite[8];

    CEventSpriteMother() { Init(); }

    int SetName(int no, char *name);

    int SetDraw(int no, int draw);

    int SetGet(int no, int x, int y, int w, int h);

    int SetPut(int no, int x, int y, int w, int h);

    int SetMove(int no, int x, int y, int frames);

    int SetFade(int no, int fade_in, int frames);

    int SetColor(int no, int r, int g, int b, int a);

    void Step();

    void Draw();

    int Set(int no, int tex_block);

    void Init();
};
STATIC_ASSERT(sizeof(CEventSpriteMother) == 0x440);

enum EVENT_SPRITE2_DRAW {
    EVENT_SPRITE2_DRAW_OFF = 0,
    EVENT_SPRITE2_DRAW_NORMAL = 1,
    EVENT_SPRITE2_DRAW_FIRST = 2,
};

enum EVENT_SPRITE2_TYPE {
    EVENT_SPRITE2_TYPE_SCREEN = 0,
    EVENT_SPRITE2_TYPE_WORLD = 1,
};

class CEventSprite2 {
public:
    int           draw_flag;
    int           sprite_type;
    int           tex_block;
    char          tex_name[0x20];
    int           alpha_blend;
    sceVu0FVECTOR pos;
    sceVu0FVECTOR color;
    float         rot_z;
    int           put_w;
    int           put_h;
    int           uv_x;
    int           uv_y;
    int           uv_w;
    int           uv_h;
    float         scale_x;
    float         scale_y;

    CEventSprite2();

    void Initialize();

    void SetTexture(char *name, int tex_block);

    void SetDrawFlag(int draw_flag);

    void SetSpriteType(int sprite_type);

    void SetPosition(float *pos);

    void SetColor(float *color);

    void SetPutSize(int w, int h);

    void SetUvSize(int x, int y, int w, int h);

    void SetScale(float scale_x, float scale_y);

    void GetScale(float *scale_x, float *scale_y);

    void GetPosition(float *pos);

    void GetColor(float *color);

    int GetType();

    void SetAlphaBlend(int alpha_blend);

    void SetRotZ(float rot_z);

    float GetRotZ();

    void NormalDraw();

    void FirstDraw();

    void Draw();
};
STATIC_ASSERT(sizeof(CEventSprite2) == 0x80);
