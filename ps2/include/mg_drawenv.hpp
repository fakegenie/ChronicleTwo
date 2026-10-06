#pragma once

#include "common.h"

#include <libvu0.h>
#include <libgraph.h>

class mgCFrameAttr;

enum mgAlphaMacroID {
    MG_ALPHA_MACRO_NONE = 0,
    MG_ALPHA_MACRO_BLEND = 1,
    MG_ALPHA_MACRO_ADD = 2,
    MG_ALPHA_MACRO_SUB = 3,
    MG_ALPHA_MACRO_OPAQUE = 4,
    MG_ALPHA_MACRO_ADD_FIX = 5,
};

enum mgZBufMode {
    MG_ZBUF_NO_WRITE = -1,
    MG_ZBUF_KEEP = 0,
    MG_ZBUF_WRITE = 1,
};

struct mgVu0FBOX {
    sceVu0FVECTOR max;
    sceVu0FVECTOR min;

    mgVu0FBOX &operator=(mgVu0FBOX &other);
};
STATIC_ASSERT(sizeof(mgVu0FBOX) == 0x20);

struct mgVec4 { float v[4]; };

struct mgPOINT_LIGHT {
    union { sceVu0FVECTOR pos; mgVec4 pos_copy; };
    union { sceVu0FVECTOR color;  mgVec4 color_copy; };
    float power;
    float range;
};
STATIC_ASSERT(sizeof(mgPOINT_LIGHT) == 0x30);

struct mgLIGHT_INFO {
    sceVu0FMATRIX light_dir;
    sceVu0FMATRIX light_color;
    sceVu0FVECTOR ambient;
    mgPOINT_LIGHT point_light[4];
};
STATIC_ASSERT(sizeof(mgLIGHT_INFO) == 0x150);

#pragma cpp_extensions on

struct mgFOG_PARAM {
    float near_dist;
    float far_dist;
    u_char r;
    u_char g;
    u_char b;
    u_char a;
    union {
        struct {
    float offset;
    float far_value;
    float near_value;
    float scale;
        };
        float values[4];
    };
    sceVu0FVECTOR coef;
};
#pragma cpp_extensions reset
STATIC_ASSERT(sizeof(mgFOG_PARAM) == 0x30);

class mgCDrawEnv {
public:
    sceGifTag giftag;
    sceGsTest test;
    u_long test_addr;
    sceGsZbuf zbuf;
    u_long zbuf_addr;
    sceGsAlpha alpha;
    u_long alpha_addr;

#ifndef MG_DRAWPRIM_MANUAL_CTOR
    mgCDrawEnv();
#endif

    mgCDrawEnv &operator=(mgCDrawEnv &other);

    void Initialize(int context);

    void SetAlpha(int mode);

    int GetAlphaMacroID();

    void SetZBuf(int mode);
};
STATIC_ASSERT(sizeof(mgCDrawEnv) == 0x40);

class mgRENDER_INFO {
public:
    float projection;
    sceVu0FMATRIX world_screen;
    sceVu0FMATRIX view_screen;
    sceVu0FMATRIX world_screen_rel;
    sceVu0FMATRIX aspect;
    sceVu0FMATRIX screen;
    sceVu0FMATRIX world_view;
    u_int unk_190[4];
    sceVu0FMATRIX view;
    sceVu0FMATRIX view_clip;
    sceVu0FMATRIX world_clip;
    sceVu0FMATRIX clip_screen;
    sceVu0FMATRIX view_clip_full;
    sceVu0FMATRIX clip_screen_full;
    sceVu0FVECTOR shadow_plane_pos;
    sceVu0FVECTOR shadow_plane_normal;
    sceVu0FMATRIX shadow;
    u_int unk_380[4];
    sceVu0FVECTOR shadow_light_dir;
    sceVu0FVECTOR camera_pos;
    sceVu0FMATRIX camera_pose;
    int light_changed;
    int active_light;
    mgLIGHT_INFO light_info[8];
    sceVu0FVECTOR clip_min;
    sceVu0FVECTOR clip_max;
    sceVu0FVECTOR guard_max;
    sceVu0FVECTOR guard_min;
    sceVu0FVECTOR full_max;
    sceVu0FVECTOR full_min;
    sceVu0FVECTOR screen_box_max;
    sceVu0FVECTOR screen_box_min;
    sceVu0FVECTOR gs_box_max;
    sceVu0FVECTOR gs_box_min;
    mgCDrawEnv draw_env[2];
    int all_scissor;
    int fog_enable;
    int plight_enable;
    int unk_fac;
    u_int unk_fb0[4];
    int clip;
    int scissor;
    int plight_hit;
    mgCFrameAttr *attr;
    mgFOG_PARAM fog;
    sceVu0FVECTOR object_color;
    int motion;

    void Initialize();

    void SetRenderInfo(float projection, int width, int height, float near_dist, float far_dist,
                       int zdepth, float aspect_y);

    void SetViewMatrix(float (*view)[4], float *camera_pos);

    void SetDropShadowMatrix(float *light_dir, float *plane_pos, float *plane_normal);

    int ActiveLighting(int index, int copy);

    mgLIGHT_INFO *GetpLightInfo();

    void InitActiveLighting();

    void InitLighting();

    void SetLight(float (*light_dir)[4], float (*light_color)[4]);

    void GetLight(float (*light_dir)[4], float (*light_color)[4]);

    void SetLight(int index, float *dir, float *color);

    void SetAmbient(float *color);

    void GetAmbient(float *color);

    void SetPlight(int index, float *pos, float *color, float power, float range);

    void SetPlight(int index, mgPOINT_LIGHT *light);

    void GetPlight(int index, mgPOINT_LIGHT *light);

    void FogEnable(int enable);

    int GetFogEnable();

    void PlightEnable(int enable);

    int GetPlightEnable();

    void SetFogParam(float near_dist, float far_dist, u_char r, u_char g, u_char b,
                     float far_value, float near_value);
};
STATIC_ASSERT(sizeof(mgRENDER_INFO) == 0x1020);
