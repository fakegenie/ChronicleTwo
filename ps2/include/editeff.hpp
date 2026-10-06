#pragma once

#include "common.h"

#include <libvu0.h>

#include "map.hpp"
#include "mg_sprite.hpp"

class CEditParts;
class CMapParts;
class mgCMemory;
class mgCTexture;

#define EDIT_STAR_EFFECT_MAX 3

#define EDIT_PAINT_EFFECT_MAX 1

#define EDIT_PAINT_DROP_NUM 24

#define EDIT_PLACE_ANIME_MAX 3

enum EditEffectState {
    EDIT_EFFECT_STATE_FREE = 0,
    EDIT_EFFECT_STATE_PLAY = 1,
    EDIT_EFFECT_STATE_SCATTER = 2,
    EDIT_EFFECT_STATE_END = 3,
};

enum EditPlaceAnimeType {
    EDIT_PLACE_ANIME_NONE = 0,
    EDIT_PLACE_ANIME_SWAY = 1,
    EDIT_PLACE_ANIME_SQUASH = 2,
    EDIT_PLACE_ANIME_REMOVE = 3,
};

struct EditStarParticle {
    sceVu0FVECTOR position;
    s32 unk_10;
    s32 shape;
    s32 unk_18;
    s32 unk_1c;
};

STATIC_ASSERT(sizeof(EditStarParticle) == 0x20);

class CStarEffect : public CObject {
public:
    s32 state;
    float spin_speed;
    float rise_speed;
    float alpha;
    float star_angle;
    float size;
    s32 frame;
    s32 particle_max;
    s32 particle_num;
    EditStarParticle *particle;
    s32 unk_98;
    s32 unk_9c;
    mgC3DSprite sprite;
    mgCTexture *texture;
    s32 unk_f4;
    s32 unk_f8;
    s32 unk_fc;

    CStarEffect();

    void ParamInit(float *area, int num);

    void Step();

    virtual int Draw();
};

STATIC_ASSERT(sizeof(CStarEffect) == 0x100);

class CPaintEffect : public CObject {
public:
    s32 state;
    s32 shape;
    s32 unk_78;
    s32 unk_7c;
    sceVu0FVECTOR color;
    mgCTexture *texture;
    s32 unk_94;
    s32 unk_98;
    s32 unk_9c;
    mgC3DSprite sprite;
    float alpha;
    s32 wait;
    s32 unk_f8;
    s32 unk_fc;
    sceVu0FVECTOR drop[EDIT_PAINT_DROP_NUM];
    sceVu0FVECTOR drop_speed[EDIT_PAINT_DROP_NUM];

    CPaintEffect();

    void ParamInit(float scale);

    void Step();

    virtual int Draw();
};

STATIC_ASSERT(sizeof(CPaintEffect) == 0x400);

class CPlaceAnime {
public:
    s32 state;
    s32 type;
    CMapParts *parts;
    s32 unk_0c;
    sceVu0FVECTOR rotation;
    sceVu0FVECTOR scale;
    sceVu0FVECTOR position;
    sceVu0FVECTOR base_rotation;
    sceVu0FVECTOR base_scale;
    sceVu0FVECTOR base_position;
    s32 frame;
    s32 phase;
    float power;
    float height;
    float height_speed;
    s32 unk_84;
    s32 unk_88;
    s32 unk_8c;

    void Step();

    void Step2();

    void Draw();
};

STATIC_ASSERT(sizeof(CPlaceAnime) == 0x90);

extern CPlaceAnime PlaceAnime[EDIT_PLACE_ANIME_MAX];

void EditSetEffectBuffer(mgCMemory *memory);

void EditInitPlaceEffect();

int EditPlaceEffect(CEditParts *parts, float *position);

int EditPaintEffect(CEditParts *parts, float *position, float *color, int river);

void EditPEffectStep();

void EditPEffectDraw(int unused);

int EditGetPEffectState();

int EditPEffectEndCheck();

void EditInitPlaceAnime();

int EditNowPlaceAnime();

int EditSetPlaceAnime(int type, CMapParts *parts);

void EditPlaceAnime();

void EditPlaceAnime2();

void EditPlaceAnimeDraw();

int EditGetPlaceAnimeState();

int EditPlaceAnimeEndCheck();
