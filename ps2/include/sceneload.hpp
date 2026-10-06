#pragma once

#include "common.h"

#include "mg_tanime.hpp"

class mgCMemory;
struct EMAP_MESSAGE;

enum {
    SCN_LOADMAP_FILES_MAX = 2,
};

enum SCN_LOADMAP_STEP {
    SCN_LOADMAP_STEP_CREATE = 0,
    SCN_LOADMAP_STEP_MAP_INFO = 1,
    SCN_LOADMAP_STEP_DATA = 2,
    SCN_LOADMAP_STEP_EFFECT = 3,
    SCN_LOADMAP_STEP_CREATE_MAP = 4,
    SCN_LOADMAP_STEP_FUNC_POINT = 5,
    SCN_LOADMAP_STEP_CFG = 6,
};

struct SCN_LOADMAP_INFO2 {
    SCN_LOADMAP_INFO2() { Initialize(); }
    struct MapFiles {
        s32 enable;
        char dir[0x20];
        char map_name[0x10];
        char cfg_name[0x10];
        char mpk_name[0x10];
        char ipk_name[0x10];
        char efp_name[0x10];
        char sky_name[0x10];
        char def_sky_name[0x10];
        char *map_data;
        s32 map_size;
        char *cfg_data;
        s32 cfg_size;
        unsigned int *mpk_data;
        unsigned int *ipk_data;
        unsigned int *efp_data;
        unsigned int *sky_data;
    };

    s32 tex_block;
    s32 stack_no;
    u8 *load_buf;
    s32 efp_tex_block;
    s32 sky_tex_block;
    char name[0x10];
    MapFiles files[SCN_LOADMAP_FILES_MAX];
    s32 load_sky;
    s32 place_parts_max;
    s32 unk_194;
    s32 tex_block_num;
    s32 data_ready;
    s32 map_no;
    mgCMemory *stack;

    void Initialize();
};
STATIC_ASSERT(sizeof(SCN_LOADMAP_INFO2::MapFiles) == 0xB4);
STATIC_ASSERT(sizeof(SCN_LOADMAP_INFO2) == 0x1A8);

template <typename T>
class mgCObjectStack {
public:
    u8 unk_0[0x8];
    s32 unk_8;
    u8 unk_c[0x8];

    mgCObjectStack() {
        Initialize();
    }

    void Initialize();
};

template <typename T>
void mgCObjectStack<T>::Initialize() {
    unk_8 = 0;
}

template <>
void mgCObjectStack<CList<EMAP_MESSAGE> >::Initialize();

STATIC_ASSERT(sizeof(mgCObjectStack<CList<EMAP_MESSAGE> >) == 0x14);
