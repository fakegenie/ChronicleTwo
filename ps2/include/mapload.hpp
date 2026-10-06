#pragma once

#include "common.h"

#include <cstring>
#include <libvu0.h>

#include "mg_drawenv.hpp"
#include "mg_frame.hpp"

class CFuncPointCheck;

enum MAP_TIME_BAND {
    MAP_TIME_BAND_DAY = 0,
    MAP_TIME_BAND_EVENING = 1,
    MAP_TIME_BAND_NIGHT = 2,
    MAP_TIME_BAND_MORNING = 3,
    MAP_TIME_BAND_NUM = 4,
};

enum FUNC_POINT_TYPE {
    FUNC_POINT_NONE = 0,
    FUNC_POINT_EFFECT = 1,
    FUNC_POINT_FIRE = 2,
    FUNC_POINT_FLARE = 3,
    FUNC_POINT_PLIGHT = 4,
    FUNC_POINT_ANIME = 5,
    FUNC_POINT_EVENT = 6,
    FUNC_POINT_INVENT = 7,
    FUNC_POINT_SOUND = 8,
    FUNC_POINT_POS = 9,
    FUNC_POINT_TYPE_NUM,
};

enum FUNC_EVENT_FLAG {
    FUNC_EVENT_EVERY = 0x1,
    FUNC_EVENT_ACTION = 0x2,
    FUNC_EVENT_ITEM = 0x4,
    FUNC_EVENT_DOOR = 0x8,
    FUNC_EVENT_ED_DOOR = 0x10,
    FUNC_EVENT_LADDER_BOTTOM = 0x20,
    FUNC_EVENT_LADDER_TOP = 0x40,
    FUNC_EVENT_CLOSE_DOOR = 0x80,
    FUNC_EVENT_UNK_100 = 0x100,
    FUNC_EVENT_TREASURE_BOX = 0x200,
    FUNC_EVENT_BOOK = 0x400,
};

enum FUNC_PLIGHT_TYPE {
    FUNC_PLIGHT_DIRECTIONAL = 0,
    FUNC_PLIGHT_AMBIENT = 1,
    FUNC_PLIGHT_POINT = 2,
};

enum FUNC_PLIGHT_FLICKER {
    FUNC_PLIGHT_FLICKER_NONE = 0,
    FUNC_PLIGHT_FLICKER_RANDOM = 1,
    FUNC_PLIGHT_FLICKER_SINE = 2,
    FUNC_PLIGHT_FLICKER_SAW = 3,
};

class CMapLightingInfo {
public:
    float         projection;
    sceVu0FVECTOR bg_color;
    sceVu0FVECTOR bg_color2;
    sceVu0FMATRIX light_dir;
    sceVu0FMATRIX light_color;
    int           plight_enable;
    mgPOINT_LIGHT point_light[4];
    sceVu0FVECTOR ambient;
    int           fog_enable;
    mgFOG_PARAM   fog;

    CMapLightingInfo() { memset(this, 0, sizeof(CMapLightingInfo)); }
    CMapLightingInfo &operator=(const CMapLightingInfo &other);
};
STATIC_ASSERT(sizeof(CMapLightingInfo) == 0x1D0);

class CFuncPoint {
public:
    struct EffectData {
        char *name;
        int   index;
    };

    struct FireData {
        sceVu0FVECTOR color;
        int           effect_off;
        int           heat_haze;
        int           cast_light;
    };

    struct PlightData {
        sceVu0FVECTOR color;
        float         power;
        float         range;
        int           light_type;
        int           light_chara;
        int           unk_40;
        int           unk_44;
        int           no_map_light;
        int           flicker_type;
        float         flicker_depth;
        float         flicker_period;
    };

    struct AnimeData {
        char         *parts_name;
        char         *piece_name;
        char         *frame_name;
        int           kind;
        int           mode;
        s16           uniform;
        s16           piece_space;
        sceVu0FVECTOR param;
        sceVu0FVECTOR speed;
        sceVu0FVECTOR end;
    };

    struct EventData {
        u32  flag;
        int  event_no;
        int  point_no;
        int  unk_2c;
        int  unk_30;
        int  unk_34;
        char unk_38[16];
    };

    struct SoundData {
        int           se_no;
        float         unk_24;
        float         unk_28;
        float         unk_2c;
        int           shape;
        sceVu0FVECTOR start;
        sceVu0FVECTOR end;
    };

    struct InventData {
        int       neta_no;
        int       unk_24;
        float     range;
        float     angle;
        mgVu0FBOX box;
    };

    char    *name;
    int      type;
    int      unk_8;
    int      unk_c;
    int      enable;
    float    start;
    float    end;
    union {
        int        data[0x14];
        EffectData effect;
        FireData   fire;
        PlightData plight;
        AnimeData  anime;
        EventData  event;
        SoundData  sound;
        InventData invent;
    };
    mgCFrame      frame;
    sceVu0FVECTOR position;
    sceVu0FVECTOR rotation;
    sceVu0FVECTOR scale;
    int           active;

    CFuncPoint() {}

    void Initialize();

    int Check(CFuncPointCheck *check);

    void SetPosition(float *position);

    void SetRotation(float *rotation);

    void SetScale(float *scale);
};
STATIC_ASSERT(sizeof(CFuncPoint) == 0x1C0);

class PieceMaterial {
public:
    mgCFrame     *frame;
    int           material_no;
    mgMaterial   *material;
    int           unk_c;
    sceVu0FVECTOR color;

    PieceMaterial();

    void Initialize();
};
STATIC_ASSERT(sizeof(PieceMaterial) == 0x20);

class CCameraDrawInfo {
public:
    int group_no;
    int unk_4;

    CCameraDrawInfo();

    void Initialize();
};
STATIC_ASSERT(sizeof(CCameraDrawInfo) == 0x8);

extern char mapMapPartsGroupName[0x100];

extern sceVu0FVECTOR mapPos;

extern sceVu0FVECTOR mapRot;

extern sceVu0FVECTOR mapScale;

MAP_TIME_BAND GetTimeBand(float time);

inline float mgAbs(float value) {
    if (value < 0.0f) {
        return -value;
    }
    return value;
}

unsigned int algn16_size(unsigned int size);
