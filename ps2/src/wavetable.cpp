#include "common.h"
#include "wavetable.hpp"
#include <cstdlib>

extern int cnt_302;
extern signed char init_303;

#include <cstdlib>
#include <libvu0.h>

#include "mg_drawprim.hpp"
#include "mg_texture.hpp"
#include "mglib.hpp"

// Code (.text)
CWaveTable::CWaveTable() {
    int row;
    int col;

    for (row = 0; row < WAVE_TABLE_DIM; row++) {
        for (col = 0; col < WAVE_TABLE_DIM; col++) {
            height[1][row][col] = 0.0f;
            height[0][row][col] = 0.0f;
        }
    }

    current = 0;
}
CWaveTable::~CWaveTable() {
}

#ifdef NONMATCHING
void CWaveTable::CreateTexture(mgCTexture *output_texture) {
    if (output_texture == NULL || output_texture->bpp < 24) {
        return;
    }

    mgSetPkFrameBuffer(output_texture);
    mgCDrawPrim prim;
    prim.Initialize(NULL, NULL);
    prim.DepthTestEnable(0);
    prim.ZMask(-1);
    prim.Shading(1);
    prim.AlphaBlendEnable(1);

    float position[4];
    position[3] = 0.0f;
    position[2] = 0.0f;
    float cell_width = (float)output_texture->width / 23.0f;
    float cell_height = (float)output_texture->height / 23.0f;
    float origin_x = (float)mgScreenOffx;
    float origin_y = (float)mgScreenOffy;
    prim.Begin2();

    float row_offset = 0.0f;
    for (int row = 0; row < WAVE_TABLE_DIM - 1; row++) {
        prim.BeginPrim2(4, 0x4141U, 0U, 4);
        float column_offset = 0.0f;
        for (int column = 0; column < WAVE_TABLE_DIM; column++) {
            position[0] = origin_x + column_offset * cell_width;
            position[1] = origin_y + row_offset * cell_height;
            int sample_column = column;
            if (column >= WAVE_TABLE_DIM - 1) {
                sample_column = 0;
            }
            int next_column = (sample_column + 1) % WAVE_TABLE_DIM;
            float *line = height[current][row];
            float intensity = 40.0f + 540.0f * (line[sample_column] - line[next_column]);
            if (!(intensity <= 200.0f)) {
                intensity = 200.0f;
            }
            if (intensity < 0.0f) {
                intensity = 0.0f;
            }
            float color[4] = {0.0f, 0.0f, 0.0f, 96.0f};
            color[0] = intensity;
            color[1] = intensity;
            color[2] = intensity;
            prim.Data0(color);
            prim.Data4(position);

            float *next_line = height[current][(row + 1) % WAVE_TABLE_DIM];
            intensity = 40.0f + 540.0f * (next_line[sample_column] - next_line[next_column]);
            if (intensity < 0.0f) {
                intensity = 0.0f;
            }
            if (!(intensity <= 200.0f)) {
                intensity = 200.0f;
            }
            float next_color[4] = {0.0f, 0.0f, 0.0f, 96.0f};
            next_color[0] = intensity;
            next_color[1] = intensity;
            next_color[2] = intensity;
            position[1] += cell_height;
            prim.Data0(next_color);
            prim.Data4(position);
            column_offset += 1.0f;
        }
        prim.EndPrim2();
        row_offset += 1.0f;
    }

    prim.End2();
    prim.Shading(0);
    prim.AlphaBlend(2);
    prim.Begin(6);
    prim.Color(0, 0, 0, 128);
    prim.Vertex(-1, -1, 0);
    prim.Vertex(output_texture->width + 1, output_texture->height + 1, 0);
    prim.End();
    mgSetPkFrameBuffer(-1, -1, -1, -1);
}
#else
INCLUDE_ASM("ps2/asm/pal/nonmatchings/wavetable", CreateTexture__10CWaveTableFP10mgCTexture);
#endif

void CWaveTable::GetEffect() {
    static int cnt = 0;
    int        i;
    int        col;
    int        row;

    // Every fifth step drops four random disturbances onto the surface.
    if (cnt == 0) {
        for (i = 0; i < 4; i++) {
            col = rand() % 22 + 1;
            row = rand() % 22 + 1;
            height[current][row][col] += (rand() / 2147483648.0f - 0.5f) * 0.04f;
        }
    }

    cnt++;
    if (cnt > 4) {
        cnt = 0;
    }

    Effect();
    current = 1 - current;
}

#ifdef NONMATCHING
void CWaveTable::Effect() {
    float *before = &height[1 - current][0][0];
    float *now = &height[current][0][0];
    for (int row = 1; row < 23; row++) {
        for (int column = 1; column < 23; column++) {
            float *center = &now[row * 24 + column];
            float *old = &before[row * 24 + column];
            *old = (*center * 1.9216f - *old) - (*center - *old) * 0.0015f + (center[-24] + (center[-1] + center[1] + center[24])) * 0.0196f;
        }
    }
    for (int row = 1; row < 23; row++) {
        float *line = &before[row * 24];
        float seam = (line[22] + line[1]) * 0.5f;
        line[1] = seam;
        line[22] = seam;
    }
}
#else
INCLUDE_ASM("ps2/asm/pal/nonmatchings/wavetable", Effect__10CWaveTableFv);
#endif

// Initialised data (.data)
INCLUDE_RODATA("ps2/asm/pal/nonmatchings/wavetable", at_251__DATA);
INCLUDE_RODATA("ps2/asm/pal/nonmatchings/wavetable", at_256__DATA);

// Virtual tables (.vtables)
INCLUDE_RODATA("ps2/asm/pal/nonmatchings/wavetable", __vt__10CWaveTable__DATA);

INCLUDE_BSS(cnt_302, 0x4);
INCLUDE_BSS(init_303, 0x4);
