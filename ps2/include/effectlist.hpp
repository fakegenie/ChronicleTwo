#pragma once

#include "common.h"

class CEffectManager;
class mgC3DSprite;
class mgCMemory;
class mgCTexture;

enum FadeMode {
    FADE_MODE_OUT = -1,
    FADE_MODE_NONE = 0,
    FADE_MODE_IN = 1,
};

enum CrossFadeType {
    CROSS_FADE_DISSOLVE = 0,
    CROSS_FADE_WIPE = 1,
};

class CEffectList {
public:
    CEffectList() {
        pack = NULL;
        name = NULL;
        block = -1;
        effect_num = 0;
        managers = NULL;
        sprites = NULL;
    }

    char *name;
    u_int *pack;
    int block;
    int effect_num;
    CEffectManager *managers;
    mgC3DSprite *sprites;

    void LoadEFPFile(char *name, u_int *pack, int block, mgCMemory *stack);

    int SaerchEffectIndex(char *name);

    mgC3DSprite *GetEffectVisual(int index);

    void Step();

    void CreatePacket();
};
STATIC_ASSERT(sizeof(CEffectList) == 0x18);

class CFadeInOut {
public:

    CFadeInOut() { Initialize(); }

    float r;
    float g;
    float b;
    float alpha;
    int mode;
    int end;
    float speed;
    int cross_type;
    int cross;
    float cross_alpha_rate;
    mgCTexture *cross_texture;
    int blur_alpha;

    void Initialize();

    void ResetFade();

    void FadeIn(int frames, float r, float g, float b);

    void FadeIn(int frames);

    void FadeOut(int frames, float r, float g, float b);

    void CrossFade(int frames, float alpha_rate);

    void CrossFadeIn(int type, int frames, float alpha_rate);

    void CrossFadeOut(int type, int frames, float alpha_rate);

    int FadeCheck();

    int NowFade();

    int FadeStep();

    void SetCrossTexture(mgCTexture *texture, u_long128 *buffer);

    void CaptureScreen();

    void Draw();
};
STATIC_ASSERT(sizeof(CFadeInOut) == 0x30);
