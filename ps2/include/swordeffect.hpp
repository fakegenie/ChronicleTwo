#pragma once

#include "common.h"

#include <libvu0.h>

class mgCFrame;
class mgCMemory;
class mgCTexture;

struct SWordFloat4 {
    float values[4];
};
struct SWordFloat2 {
    float values[2];
};

class CSWordAfterEffect {
public:
    mgCFrame      *frame0;
    mgCFrame      *frame1;
    sceVu0FVECTOR *point0;
    sceVu0FVECTOR *point1;
    sceVu0FVECTOR *smooth0;
    sceVu0FVECTOR *smooth1;
    u_char             unk_18[8];
    sceVu0IVECTOR  color0;
    sceVu0IVECTOR  color1;
    SWordFloat4    unk_40;
    SWordFloat2    unk_50;
    int            division;
    int            smooth_num;
    int            tex_block;
    mgCTexture    *texture;
    int            tex_u;
    int            tex_v;
    int            tex_w;
    int            tex_h;
    int            point_max;
    int            point_num;
    int            write_index;
    int            head_index;
    int            active;
    int            length;
    int            hold_time;
    float          alpha;
    float          fade_speed;
    u_char             unk_9c[4];

    CSWordAfterEffect() {
        color0[0] = 0x80;
        color0[1] = 0x80;
        color0[2] = 0x80;
        color0[3] = 0x80;
        color1[0] = 0x80;
        color1[1] = 0x80;
        color1[2] = 0x80;
        color1[3] = 0x80;
    }

    void Draw();

    void CreatPointList();

    void SetTexture(int block, mgCTexture *tex, int u, int v, int w, int h);

    void SetTexture(int u, int v, int w, int h);

    void StartEffect(mgCFrame *frame_0, mgCFrame *frame_1, int length, int fade_time, int hold_time);

    void AddPoint(float *pos0, float *pos1);

    void Step();

    void Clear();

    void Initialize(mgCMemory *memory, int point_max, int division);

    void Copy(CSWordAfterEffect &dst, mgCMemory *memory);
};

STATIC_ASSERT(sizeof(CSWordAfterEffect) == 0xA0);

int CreatSmoothPassSW(float (*dst)[4], float (*src)[4], int num, int division, int start, int ring_size);
