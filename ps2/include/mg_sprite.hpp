#pragma once

#include "common.h"

#include <libgraph.h>

#include "mg_dataset.hpp"
#include "mg_tanime.hpp"
#include "mg_visual.hpp"

class mgCDrawEnv;
class mgCDrawManager;
class mgCMemory;
class mgCTexture;
class mgRENDER_INFO;

enum mgC3DSpriteMode {
    MG_3DSPRITE_MODE_UPRIGHT = 0,
    MG_3DSPRITE_MODE_ROTATE = 1,
};

enum mg3DSpriteDrawFlag {
    MG_3DSPRITE_FLAG_CLIP = 1 << 0,
    MG_3DSPRITE_FLAG_SCISSOR = 1 << 1,
    MG_3DSPRITE_FLAG_PROGRAM_OPTION = 1 << 2,
    MG_3DSPRITE_FLAG_PROGRAM_MODE = 1 << 3,
    MG_3DSPRITE_FLAG_POINT_LIGHT = 1 << 4,
    MG_3DSPRITE_FLAG_NO_LIGHT = 1 << 5,
};

enum {
    MG_3DSPRITE_BATCH_MAX = 32,
};

struct mg3DSpriteRenderHead {
    u_int dma_tag[4];
    u_int vif_code[4];
    sceVu0IVECTOR unk_20[3];
    u_int unk_50[4];
    sceVu0FMATRIX local_screen;
    sceVu0FMATRIX local_world;
    u_int unk_e0[11][4];
    sceVu0FVECTOR fog;
};

struct mg3DSpriteRenderTail {
    u_int unk_00[4];
    sceVu0FMATRIX view_screen;
    u_int program_call[4];
    u_int flags_tag[4];
    u_int flags[4];
    u_int direct_tag[4];
    u_int giftag[4];
    u_int prmodecont[4];
    u_int prmode[4];
    u_int fogcol[4];
    u_int ret_tag[4];
};

struct mg3DSpriteRenderInfo {
    mg3DSpriteRenderHead head;
    mg3DSpriteRenderTail tail;
};
STATIC_ASSERT(sizeof(mg3DSpriteRenderInfo) == 0x280);

class mgCSprite : public mgCVisualPrim {
public:
    int unk_38;
    int unk_3C;
    mgCTexture *texture;
    float depth;
    int unk_48;
    int unk_4C;
    mgRect<int> screen;
    mgRect<int> uv;
    sceGsRgbaq color;

    mgCSprite() {
        screen.Set(0, 0, 0, 0);
        uv.Set(0, 0, 0, 0);
        Initialize();
    }

    virtual void Draw(float (*matrix)[4], mgCDrawManager *manager);

    virtual int Draw(u_int *tag, float (*matrix)[4], mgCDrawManager *manager);

    virtual void Initialize();

    virtual u_int CreatePacket(mgCDrawManager *manager);

    void SetColor(int r, int g, int b, int a);
};

class mgC3DSprite : public mgCVisual {
public:
    u_long128 *packet;
    mgCMemory *memory;
    u_long128 *packet_start;
    u_long128 *packet_cur;
    int unk_30;
    u_int *batch_tag;
    sceGifTag *batch_giftag;
    u_int *batch_header;
    int sprite_num;
    int mode;
    int prog_started;
    int unk_4C;

    mgC3DSprite() {
        Initialize();
    }

    virtual int CreateRenderInfoPacket(u_int *packet, float (*matrix)[4],
                                       mgRENDER_INFO *render_info);

    virtual void Draw(float (*matrix)[4], mgCDrawManager *manager);

    virtual int Draw(u_int *tag, float (*matrix)[4], mgCDrawManager *manager);

    virtual void Initialize();

    void BeginCreatePacket(int mode, mgCDrawManager *manager);

    void CPSetDrawEnv(mgCDrawEnv *env);

    void CPSetTexture(mgCTexture *texture);

    void BeginCPSprite();

    void CPSetSprite(float *pos, float *size, float *color, float *uv0, float *uv1);

    void EndCPSprite();

    void EndCreatePacket();
};

STATIC_ASSERT(sizeof(mgC3DSprite) == 0x50);
