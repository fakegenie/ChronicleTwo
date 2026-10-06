#pragma once

#include "common.h"

#include "mg_sprite.hpp"

class CScene;
class mgCFrame;
class mgCMemory;
class mgCTexture;

enum {
    FIRE_POWDER_NUM = 0x100,
    GEYSER_EFFECT_NUM = 4,
    GEYSER_EFFECT_POINT_NUM = 0x30,
};

struct FirePowder {
    float pos[4];
    float phase_speed;
    float sway_x;
    float sway_z;
    float fall_speed;
};

STATIC_ASSERT(sizeof(FirePowder) == 0x20);

class CGeyserEffectPoint {
public:
    float pos[4];
    float phase_speed;
    float sway_x;
    float sway_z;
    float rise_speed;
    float alpha;
    float scale;
    s32 active;
    s32 unk_2c;

    CGeyserEffectPoint();
};

STATIC_ASSERT(sizeof(CGeyserEffectPoint) == 0x30);

class CGeyserEffect {
public:
    s32 wait;
    s32 erupting;
    s32 erupt_frame;
    s32 erupt_count;
    s32 point_num;
    CGeyserEffectPoint *point;
    u8 unk_18[0x8];
    mgC3DSprite sprite;
    mgCTexture *texture;
    u8 unk_74[0xC];

    CGeyserEffect();

    void Create();

    void Step();

    CGeyserEffectPoint *GetEmpty();

    void CreatePoint();

    void CreatePacket();
};

STATIC_ASSERT(sizeof(CGeyserEffect) == 0x80);

void EditExceptionStep(int map_no, CScene *scene);

void InitNpcCameraReaction();

void InitS51Thunder();

void S51Thunder(CScene *scene);

void InitFirePowder(int map_no, CScene *scene, int texb, mgCMemory *memory);

void StepFirePowder(CScene *scene);

void DrawFirePowder(CScene *scene);

void InitGeyserEffect(int map_no, CScene *scene, int texb, mgCMemory *memory);

void StepGeyserEffect(CScene *scene);

void DrawGeyserEffect(CScene *scene);
