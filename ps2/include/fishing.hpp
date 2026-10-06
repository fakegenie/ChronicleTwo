#pragma once

#include "common.h"

class CCameraControl;
class mgCMemory;
struct SubGameInfo;

enum FISHING_CHARA_MODE {
    FISHING_CHARA_MODE_CONTROL = 0,
    FISHING_CHARA_MODE_SELECT_POINT = 1,
    FISHING_CHARA_MODE_CASTING = 2,
    FISHING_CHARA_MODE_UKI_WAIT = 3,
    FISHING_CHARA_MODE_NONE = 4,
    FISHING_CHARA_MODE_BATTLE = 5,
    FISHING_CHARA_MODE_FALSE = 6,
    FISHING_CHARA_MODE_SUCCESS = 7,
};

enum FISH_AFFINITY {
    FISH_AFFINITY_NONE = 0,
    FISH_AFFINITY_LOW = 1,
    FISH_AFFINITY_NORMAL = 2,
    FISH_AFFINITY_HIGH = 3,
};

enum FISH_PLACE_AREA {
    FISH_PLACE_AREA_CIRCLE = 2,
};

struct FISH_PARAM {
    char *name;
    char *file_name;
    int   item_no;
    float base_size;
    float min_size;
    float max_size;
    float unk_18;
    float weight_rate;
    float fishing_point_rate;
    float pull_rate;
    short   bait_affinity[18];
    short   time_band_affinity[4];
};
STATIC_ASSERT(sizeof(FISH_PARAM) == 0x54);

struct FISHING_ROD_DATA {
    int   status[5];
    float status4_rate;
};
STATIC_ASSERT(sizeof(FISHING_ROD_DATA) == 0x18);

struct FISH_DATA {
    int   fish_no;
    float size;
    float weight;
    float length_scale;
    float width_scale;
    float pull_strength;
    float vigour_recovery;
    float vigour;
    int   fishing_point;
};
STATIC_ASSERT(sizeof(FISH_DATA) == 0x24);

struct FISH_PLACE {
    int   fish_no;
    float rate;
    float wait_bias;
};
STATIC_ASSERT(sizeof(FISH_PLACE) == 0xC);

class FISH_PLACE_MAP {
public:
    int        map_no;
    int        exclusive;
    int        area_type;
    char      *name;
    float      area_param[5];
    int        fish_num;
    FISH_PLACE fish[8];

    int SetFishPlace(FISH_PLACE *place, int place_num, int replace);

    int CheckFishPlace(float *position);
};
STATIC_ASSERT(sizeof(FISH_PLACE_MAP) == 0x88);

extern int stack_size;

int sgInitFishing(SubGameInfo *info);

int sgRestartFishing(SubGameInfo *info);

int sgBreakFishing();

int sgExitFishing(SubGameInfo *info);

int sgLoopFishing(SubGameInfo *info);

int sgLoopFishing2(SubGameInfo *info);

int sgDrawFishing(SubGameInfo *info);

int sgSystemDrawFishing(SubGameInfo *info);

void ResetUkiCamera(CCameraControl *camera);

int GetAppearFish(int map_no, float *position, FISH_PLACE *place, int place_num);

void LoadFishPlaceData(char *script, int size, mgCMemory *memory);
