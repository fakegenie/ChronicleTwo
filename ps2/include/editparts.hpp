#pragma once

#include "common.h"

#include <libvu0.h>
#include <cstring>

#include "editcoll.hpp"
#include "mapparts.hpp"
#include "mg_drawenv.hpp"

class mgCMemory;

#define EDIT_PARTS_MATERIAL_MAX 4

#define EDIT_HOUSE_NPC_MAX 3

enum EditPartsAtr {
    EDIT_PARTS_ATR_GROUND = 0x7,
    EDIT_PARTS_ATR_BLOCK  = 0x30,
    EDIT_PARTS_ATR_TYPE_ONE = 0x40,
    EDIT_PARTS_ATR_RIVER  = 0x80,
    EDIT_PARTS_ATR_FENCE  = 0x130,
    EDIT_PARTS_ATR_BURN   = 0x1000,
};

enum EditPartsType {
    EDIT_PARTS_TYPE_RIVER = 11,
};

enum EditPartsState {
    EDIT_PARTS_STATE_NONE   = 0,
    EDIT_PARTS_STATE_PLACED = 1,
    EDIT_PARTS_STATE_RIVER  = 2,
};

struct EditPartsMaterial {
    s32 item_no;
    s32 num;
};

STATIC_ASSERT(sizeof(EditPartsMaterial) == 0x8);

class CEditPartsInfo {
public:
    s32               id;
    u32               attr;
    s32               cpoint[2];
    s32               weight;
    s32               max_num;
    s32               geo_stone;
    s32               paint_num;
    s32               paint_used;
    s32               parts_type;
    float             place_eps;
    s32               map_no;
    s32               polyn[3];
    char             *edit_name;
    char             *parts_name;
    CMapParts        *parts;
    char             *comment;
    s32               unk_4c;
    mgVu0FBOX         box;
    EditPartsMaterial material[EDIT_PARTS_MATERIAL_MAX];
    s32               place_anime;
    s32               unk_94;
    s32               unk_98;
    s32               unk_9c;
    mgVu0FBOX         area3_box;
    CEditCollision    col_area1;
    CEditCollision    col_floor;
    CEditCollision    col_wall;
    CEditCollision    col_area3;
    CEditCollision    col_area5;
    float             bury_depth;
    s32               wall_group_num;
    s32               unk_258;
    s32               unk_25c;
    sceVu0FVECTOR     territory_center;
    float             territory_radius;
    float             territory_height;
    float             unk_278;
    s32               unk_27c;

    CEditPartsInfo() { Initialize(); }

    void Initialize();

    int GetPartsType();

    void CreateBox();

    float GetPartsHeight();

    float GetPartsMaxWidth();

    EditPartsMaterial *GetMaterial(int no);

    int GetDefColor(int no, float *out_rgba);
};

STATIC_ASSERT(sizeof(CEditPartsInfo) == 0x280);

class CEditHouse {
public:
    s32 active;
    s32 npc_no[EDIT_HOUSE_NPC_MAX];

    CEditHouse() {
        memset(this, 0, sizeof(*this));
    }

    int LiveChara();
};

STATIC_ASSERT(sizeof(CEditHouse) == 0x10);

class CEditParts : public CMapParts {
public:

    struct WallInfo {
        sceVu0FVECTOR plane;
        sceVu0FVECTOR center;
        mgVu0FBOX     box;
    };

    s32             state;
    CMapParts      *ground;
    s32             max_material_num;
    s32             unk_31c;
    s32             unk_320;
    CEditPartsInfo *info;
    CEditHouse     *house;
    s32             unk_32c;

    CEditParts() { Initialize(); }

    virtual void SetPosition(float *position);

    virtual void SetPosition(float x, float y, float z);

    virtual void GetPosition(float *out_position);

    virtual void Initialize();

    virtual void UpDatePosition();

    virtual void Copy(CMapParts &dest, mgCMemory *memory);

    void GetLocalPos(float *out_position);

    int GetInfoID();

    int GetLiveNPC();

    int IsWallParts();

    int IsFence();

    int IsBurn();

    int GetFenceSide(float *out_side0, float *out_side1);

    int GetWallPlane(int wall_no, WallInfo *out_info);

    int GetWallGroupNum();

    int GetPartsType();

    int CheckTerritory(CEditParts *other);

    void CheckColorUpdate();
};

STATIC_ASSERT(sizeof(CEditParts::WallInfo) == 0x40);
STATIC_ASSERT(sizeof(CEditParts) == 0x330);

int EditPartsCmpColor(float *color0, float *color1);
