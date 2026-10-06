#pragma once

#include "common.h"

#include <cstring>

#include "editmap.hpp"

class CEditParts;

#define EDIT_ANALYZE_MAP_MAX 5

#define EDIT_ANALYZE_CONDITION_MAX 64

#define EDIT_ANALYZE_DATA_MAX 16

#define EDIT_ANALYZE_CON_NO_MAX 8

#define EDIT_ANALYZE_DEPTH_MAX 64

#define EDIT_DATA_PARTS_MAX 300

#define EDIT_DATA_HOUSE_MAX 32

#define EDIT_DATA_PLACE_LOG_MAX 0x800

#define EDIT_DATA_GRID_SIZE 0x400

#define EDIT_DATA_COLOR_MAX 4

class EditAnalyzeDataSrc {
public:
    char *message;
    s16   percent;
    s16   geo_floor;
    s8    con_no[EDIT_ANALYZE_CON_NO_MAX];
    s32   unk_10;
    char *on_parts;
    char *off_parts;

    void Init();
};

STATIC_ASSERT(sizeof(EditAnalyzeDataSrc) == 0x1C);

class EditAnalyzeSrc {
public:
    char              *condition[EDIT_ANALYZE_CONDITION_MAX];
    s16                geo_floor[EDIT_ANALYZE_CONDITION_MAX];
    EditAnalyzeDataSrc data[EDIT_ANALYZE_DATA_MAX];

    EditAnalyzeSrc();

    void Init();
};

STATIC_ASSERT(sizeof(EditAnalyzeSrc) == 0x340);

struct EditDataParts {
    s32 id;
    s8  state;
    s8  angle;
    s16 pos[3];
    u8  color[EDIT_DATA_COLOR_MAX][3];
    s16 house_no;
    u8  unk_1a[0xA];

    EditDataParts() {
        memset(this, 0, sizeof(EditDataParts));
    }
};

STATIC_ASSERT(sizeof(EditDataParts) == 0x24);

struct EditDataGrid {
    u8  num_x;
    u8  num_z;
    s16 pos[3];
    u8  unk_8[0x10];
};

STATIC_ASSERT(sizeof(EditDataGrid) == 0x18);

struct EditDataHouse {
    s16 npc_no;
    u8  unk_2[0xE];

    EditDataHouse() {
        memset(this, 0, sizeof(EditDataHouse));
    }
};

STATIC_ASSERT(sizeof(EditDataHouse) == 0x10);

struct EditDataAnalyze {
    u8 data_open[EDIT_ANALYZE_DATA_MAX];
    s8 condition[EDIT_ANALYZE_CONDITION_MAX];
    u8 condition_open[EDIT_ANALYZE_CONDITION_MAX];
    u8 unk_90[0x40];

    EditDataAnalyze() {
        memset(this, 0, sizeof(EditDataAnalyze));
    }
};

STATIC_ASSERT(sizeof(EditDataAnalyze) == 0xD0);

class CEditData {
public:
    s32             save_count;
    s32             culture_point;
    s32             parts_max;
    EditDataParts   parts[EDIT_DATA_PARTS_MAX];
    s32             house_max;
    EditDataHouse   house[EDIT_DATA_HOUSE_MAX];
    EditPlaceLog    place_log[EDIT_DATA_PLACE_LOG_MAX];
    u8              grid[EDIT_DATA_GRID_SIZE];
    EditDataAnalyze analyze;
    u8              unk_5110[0x400];

    CEditData();

    void Initialize();

    void InitPlaceData();

    int GetPartsNumID(int id);

    s8 Analyze(int data_no, int map_no, int *con_src, int depth);

    void Analize(int map_no, int *con_value, int *con_src);

    EditAnalyzeDataSrc *GetAnalyzeData(int map_no, int data_no);

    EditAnalyzeSrc *GetAnalyzeSrc(int map_no);

    int GetAnalyzePercent(int map_no);

    int GetAnalyzeFlag(int map_no, int data_no, int *con_no, int *con_flag);

    int GetAnalyzeFlag(int map_no, int data_no);

    void dbgSetContintionFlag(int map_no, int con_no, int flag);

    void dbgSetAnalyzeFlag(int map_no, int data_no, int flag);

    void dbgSetAllContintionFlag(int map_no, int flag);

    int dbgGetContintionFlag(int map_no, int con_no, char *name);
};

STATIC_ASSERT(sizeof(CEditData) == 0x5510);

void LoadEditAnalyzeData(int language, u_long128 *buffer);

int GetMaxPolyn(int map_no);

int GetMaxDrawMem(int map_no);
