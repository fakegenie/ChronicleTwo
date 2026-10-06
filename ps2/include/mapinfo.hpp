#pragma once

#include "common.h"

#include <libvu0.h>

#include "mapload.hpp"

class mgCMemory;
class CColFrame;
class CMapLightingInfo;
class CCameraDrawInfo;

class CCameraInfo {
public:
    int             pos_num;
    sceVu0FVECTOR   pos[8];
    int             rect_num;
    CColFrame      *rect[4];
    int             draw_info_num;
    CCameraDrawInfo draw_info[4];

    CCameraInfo();

    void Initialize();

    CCameraDrawInfo *GetDrawInfo(int index);
};
STATIC_ASSERT(sizeof(CCameraInfo) == 0xD0);

class CMapInfo {
public:
    CMapInfo() { Initialize(); }

    int               img_num;
    char             *img_name[16];
    int               pcp_num;
    char             *pcp_name[16];
    char             *map_file;
    int               map_file_size;
    char             *add_map_file;
    int               add_map_file_size;
    int               active_light_no;
    int               lighting_info_num;
    CMapLightingInfo *lighting_info;
    int               time_cfade;
    float             floor;
    int               unk_ac;
    sceVu0FVECTOR     chara_pos;
    int               time_enable;
    int               time_light_blend;
    float             fixed_time;
    int               fixed_time_enable;
    int               time_light_num;
    int               def_foot;
    int               sky_info;
    float             sky_height;
    float             sun_angle;
    int               lens_flare;
    int               all_scissor;
    int               chara_light_adjust;
    float             chara_light_adjust_value[3];
    int               unk_fc;

    void Initialize();

    char *GetImgName(int index);

    char *GetPCPName(int index);

    char *GetMapFile(int *size);

    char *GetAddMapFile(int *size);

    CMapLightingInfo *GetLightingInfo(int index);

    int GetActiveLightNo() { return active_light_no; }

    void LoadMapInfo(char *script, int script_size, mgCMemory *stack);

    void AddMapInfo(char *script, int script_size, mgCMemory *stack);

    int OutputLightData(char *buff);
};
STATIC_ASSERT(sizeof(CMapInfo) == 0x100);
