#pragma once

#include "common.h"

#include <cstring>
#include <libvu0.h>

#include "mg_drawenv.hpp"
#include "mg_frame.hpp"

class mgCMemory;
class mgCDrawManager;
struct MDS_HEADER;

enum ColFrameFlag {
    COL_FRAME_FLAG_SELF        = 0x1,
    COL_FRAME_FLAG_NO_CHILDREN = 0x2,
    COL_FRAME_FLAG_UNK_4       = 0x4,
};

struct CCPoly {
    sceVu0FVECTOR vertex[3];
    sceVu0FVECTOR normal;
    short           ground_kind;
    short           foot_sound;
    short           area_kind;
    short           ignore_mask;
    u_short           parts_no;
    short           attr;
    float         attr_value;
};

STATIC_ASSERT(sizeof(CCPoly) == 0x50);

class CCollision {
public:
    int       unk_00;
    mgVu0FBOX bbox;

    CCollision() { CCollision::Initialize(); }

    virtual void CreateBBox() {}

    virtual int InsidePoint(float *point);

    virtual int GetMaxY(float *position) { return 0; }

    virtual int Intersection(float *from, float *to, float *hit);

    virtual int PickUpNearPoly(CCPoly *poly, const mgVu0FBOX &box, int max);

    virtual void Copy(CCollision &dest, mgCMemory *memory);

    virtual void Initialize() {
        unk_00 = 0;
        memset(&bbox, 0, sizeof(bbox));
    }
};

STATIC_ASSERT(sizeof(CCollision) == 0x40);

class CCollisionMDT : public CCollision {
public:
    CCPoly *poly;
    int     poly_count;

    CCollisionMDT() {
        CCollision::Initialize();
        poly = 0;
        poly_count = 0;
    }

    virtual void CreateBBox();

    virtual int GetMaxY(float *position);

    virtual int PickUpNearPoly(CCPoly *poly, const mgVu0FBOX &box, int max);

    virtual void Initialize();

    virtual void Copy(CCollisionMDT &dest, mgCMemory *memory);
};

STATIC_ASSERT(sizeof(CCollisionMDT) == 0x50);

class CColFrame : public mgCFrame {
public:
    u_int         flags;
    CCollision *collision;

    CColFrame();

    void SetCollision(CCollision *col) { collision = col; }

    int InsidePoint(float *point);

    int PickUpNearPoly(CCPoly *poly, const mgVu0FBOX &box, int max);

    virtual void Initialize();

    virtual int GetWorldBBox(mgVu0FBOX *box);

    virtual int Draw(mgCDrawManager *manager) { return 0; }

    virtual int Draw(u_int *packet, mgCDrawManager *manager) { return 0; }
};

STATIC_ASSERT(sizeof(CColFrame) == 0x120);

CColFrame *LoadCollisionFile(MDS_HEADER *header, mgCMemory *memory);

CCollisionMDT *CreateCollisionMDT(u_int *model, mgCMemory *memory);
