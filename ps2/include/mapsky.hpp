#pragma once

#include "common.h"

class mgCFrame;
class mgCVisualMDT;
class mgCMemory;

struct MAP_SKY_INFO {
    char  img_name[4][32];
    char  sky_mds_name[4][32];
    float sky_rot_speed[4];
    char  sun_mds_name[4][32];
    char  skyb_mds_name[4][32];
    float skyb_rot_speed[4];
    char  bg_mds_name[32];
    int   sky_anime_id[16];
    char  sky_anime_name[16][32];
    float sky_anime_speed[16];
    int   skyb_anime_id[16];
    char  skyb_anime_name[16][32];
    float skyb_anime_speed[16];
};
STATIC_ASSERT(sizeof(MAP_SKY_INFO) == 0x740);

class CMapSky {
public:

    struct AnimeFrame {
        mgCFrame *frame;
        float     speed;
    };

    mgCFrame     *sky[4];
    float         sky_rot[4];
    float         sky_rot_speed[4];
    mgCFrame     *skyb[4];
    float         skyb_rot[4];
    float         skyb_rot_speed[4];
    mgCFrame     *sun[4];
    int           tex_block[4];
    mgCFrame     *bg;
    mgCVisualMDT *bg_visual;
    AnimeFrame    anime[16];

    CMapSky() {
        Initialize();
    }

    void Initialize();

    void DrawSkyBack(float *camera_pos, float *color1, float *color0);

    void DrawSky(float *camera_pos, float *sun_pos, float *moon_pos, int time_band, float *lighting_ratio,
                 float *sun_lighting_ratio);

    void LoadPack(unsigned int *pack, int tex_block_base, mgCMemory *memory);
};
STATIC_ASSERT(sizeof(CMapSky::AnimeFrame) == 0x8);
STATIC_ASSERT(sizeof(CMapSky) == 0x108);
