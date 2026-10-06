#pragma once

#include "common.h"

#include <cstring>
#include <libvu0.h>

#include "mg_dataset.hpp"
#include "mg_frame.hpp"
#include "mg_texture.hpp"

class mgCMemory;
class mgCDrawManager;
class mgRENDER_INFO;

struct FireRasterParticle {
    sceVu0FVECTOR position;
    float         size;
    int           time;
    int           life;
    int           unk_1c;

    FireRasterParticle() { memset(this, 0, sizeof(FireRasterParticle)); }
};

STATIC_ASSERT(sizeof(FireRasterParticle) == 0x20);

class CFireRaster {
public:
    mgCTexture         texture;
    FireRasterParticle particle[20];

    CFireRaster() { Initialize(); }

    void Step();

    void SetTexture(mgCTexture *texture);

    void Draw(float *position, float *scale);

    void Initialize();
};

STATIC_ASSERT(sizeof(CFireRaster) == 0x2F0);

class CThunderEffect {
public:
    int unk_00;
    u_char  unk_04[0x8C];
    int unk_90;
    int unk_94;
    int unk_98;

    void Init();
};

class CWater : public mgCVisual {
public:
    float         *height_a;
    float         *height_b;
    mgCTexture    *texture;
    u_int          packet;
    int            color[4];
    float          speed;
    float          damping;
    float          surface_param0;
    float          surface_param1;
    int            unk_50;
    int            rows;
    int            columns;
    float         *height;
    sceVu0FVECTOR  min;
    sceVu0FVECTOR  max;

    void Hamon();

    void SetVertex(float *corner0, float *corner1);

    void Shake(int row, int column, float height_change);

    void SetSize(int row_count, int column_count, mgCMemory *memory);

    void SetParam(float speed, float damping, float param0, float param1);

    void SetColor(unsigned char red, unsigned char green, unsigned char blue, unsigned char alpha);

    CWater();

    virtual int CreateRenderInfoPacket(u_int *packet, float (*matrix)[4], mgRENDER_INFO *info);

    virtual int Draw(u_int *packet, float (*matrix)[4], mgCDrawManager *draw_manager);

    virtual u_int CreatePacket(mgCDrawManager *draw_manager);
};

STATIC_ASSERT(sizeof(CWater) == 0x80);

class CWaterFrame : public mgCFrame {
public:
    int unk_110;
    int stop;
    int unk_118;
    int unk_11c;

    CWaterFrame() { Initialize(); }

    void Shake(float x, float z, float height_change);

    virtual CWater *GetWater();

    void SetTexture(mgCTexture *texture);

    virtual void Step();

    void SetParam(float speed, float damping, float param0, float param1);

    void SetColor(unsigned char red, unsigned char green, unsigned char blue, unsigned char alpha);

    void Shake(int row, int column, float height_change);

    void CreatePacket();

    virtual void Initialize();
};

STATIC_ASSERT(sizeof(CWaterFrame) == 0x120);

CWaterFrame *CreateWaterFrame(int rows, int columns, float *min, float *max, mgCMemory *memory);
