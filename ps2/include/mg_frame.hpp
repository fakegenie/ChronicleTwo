#pragma once

#include "common.h"

#include <libvu0.h>

#include "mg_visual.hpp"

class mgCVisual;
class mgCDrawManager;
class mgRENDER_INFO;
struct mgVu0FBOX;
struct mgMaterial;

enum mgFrameDrawFlag {
    MG_FRAME_DRAW_VISIBLE        = 1,
    MG_FRAME_DRAW_SKIP_CHILDREN  = 2,
    MG_FRAME_DRAW_SKIP_BY_PARENT = 4,
};

enum mgFrameBillboard {
    MG_FRAME_BILLBOARD_NONE = 0,
    MG_FRAME_BILLBOARD_FULL = 1,
    MG_FRAME_BILLBOARD_Y    = 2,
};

enum mgFrameRotType {
    MG_FRAME_ROT_APPLY        = 1,
    MG_FRAME_ROT_LOCAL_ORIGIN = 2,
};

enum mgFrameAttrParam {
    MG_FRAME_ATTR_DRAW          = 0x1,
    MG_FRAME_ATTR_ALPHA_REF     = 0x2,
    MG_FRAME_ATTR_ALPHA_BLEND   = 0x4,
    MG_FRAME_ATTR_Z_WRITE       = 0x8,
    MG_FRAME_ATTR_Z_TEST        = 0x10,
    MG_FRAME_ATTR_CLIP          = 0x20,
    MG_FRAME_ATTR_UNK_20        = 0x40,
    MG_FRAME_ATTR_UNK_24        = 0x80,
    MG_FRAME_ATTR_UNK_28        = 0x100,
    MG_FRAME_ATTR_PROGRAM_OPT   = 0x200,
    MG_FRAME_ATTR_FOG           = 0x400,
    MG_FRAME_ATTR_UNK_34        = 0x800,
    MG_FRAME_ATTR_UNK_38        = 0x1000,
    MG_FRAME_ATTR_UNK_3C        = 0x2000,
    MG_FRAME_ATTR_PROGRAM_MODE  = 0x4000,
    MG_FRAME_ATTR_NO_LIGHT      = 0x8000,
    MG_FRAME_ATTR_COLOR         = 0x10000,
    MG_FRAME_ATTR_POINT_LIGHT   = 0x20000,
    MG_FRAME_ATTR_OBJ_ALPHA     = 0x40000,
    MG_FRAME_ATTR_BILLBOARD     = 0x80000,
    MG_FRAME_ATTR_NO_CULL       = 0x100000,
    MG_FRAME_ATTR_DEPTH_BIAS    = 0x200000,
    MG_FRAME_ATTR_DEST_ALPHA    = 0x400000,
    MG_FRAME_ATTR_AMBIENT_BOOST = 0x800000,
};

class mgCFrameAttr : public mgCVisualAttr {
public:
    int           draw;
    int           clip_enable;
    float         unk_20;
    int           unk_24;
    int           unk_28;
    int           program_option;
    int           fog;
    int           unk_34;
    float         unk_38;
    int           unk_3c;
    int           program_mode;
    float         obj_alpha;
    int           no_cull;
    int           ambient_boost;
    sceVu0FVECTOR unk_50;
    int           no_light;
    sceVu0FVECTOR color;
    int           point_light;
    int           unk_84;
    int           billboard;
    float         depth_bias;

    mgCFrameAttr();

    void Initialize();
};

STATIC_ASSERT(sizeof(mgCFrameAttr) == 0x90);

class mgCObject {
public:

    virtual void ChangeParam();

    virtual void UseParam();

    virtual void SetPosition(float *position);

    virtual void SetPosition(float x, float y, float z);

    virtual void GetPosition(float *out_position);

    virtual void SetRotation(float *rotation);

    virtual void SetRotation(float x, float y, float z);

    virtual void GetRotation(float *out_rotation);

    virtual void SetScale(float *scale);

    virtual void SetScale(float x, float y, float z);

    virtual void GetScale(float *out_scale);

    virtual int Draw();

    virtual int DrawDirect();

    virtual void Initialize();

    mgCObject() { Initialize(); }

    sceVu0FVECTOR position;
    sceVu0FVECTOR rotation;
    sceVu0FVECTOR scale;
    int           changed;
    int           use_srt;
};

STATIC_ASSERT(sizeof(mgCObject) == 0x50);

class mgCFrameBase : public mgCObject {
public:

    virtual void Initialize() { mgCObject::Initialize(); }

    mgCFrameBase() { Initialize(); }
};

STATIC_ASSERT(sizeof(mgCFrameBase) == 0x50);

class mgCFrame : public mgCFrameBase {
public:

    struct BoundCorners { float v[32]; };

    struct BoundInfo {
        sceVu0FVECTOR corner[8];
        sceVu0FVECTOR max;
        sceVu0FVECTOR min;
        float         center[3];
        float         radius;
    };

    char          *name;
    mgCFrame      *parent;
    mgCFrame      *child;
    mgCFrame      *brother;
    mgCFrame      *elder;
    int            frame_num;
    mgCFrame     **frame_list;
    float        (*init_matrix)[4][4];
    sceVu0FMATRIX lw_matrix;
    sceVu0FMATRIX trans_matrix;
    BoundInfo     *bound;
    mgCFrameAttr  *attr;
    mgCVisual     *visual;
    int            reference;
    int            rot_type;

    virtual void SetRotation(float *rotation);

    virtual void SetRotation(float x, float y, float z);

    virtual int Draw();

    virtual void Initialize();

    virtual int GetWorldBBox(mgVu0FBOX *box);

    virtual int Draw(unsigned int *packet);

    virtual void SetVisual(mgCVisual *visual);

    mgCFrame();

    void SetName(char *name);

    void SetTransMatrix(float *quaternion);

    void SetBBox(float *max, float *min);

    void GetBBox(float *out_max, float *out_min);

    void SetBSphere(float *center, float radius);

    mgCFrame *GetFrame(int index);

    int RemakeBBox(float *out_max, float *out_min);

    int GetFrameNum();

    void SetParent(mgCFrame *parent);

    void SetBrother(mgCFrame *brother);

    void SetChild(mgCFrame *child);

    void DeleteParent();

    void SetReference(mgCFrame *reference);

    void DeleteReference();

    void ClearChildFlag();

    void GetLocalMatrix(float (*matrix)[4]);

    void GetBBoardMatrix(int mode, float (*matrix)[4], mgRENDER_INFO *info);

    void GetLWMatrix(float (*matrix)[4]);

    void GetLWMatrixTopBottom(float (*matrix)[4]);

    void GetInverseMatrix(float (*matrix)[4]);

    void SetTransMatrix(float (*matrix)[4]);

    mgCFrame *SearchFrame(char *name);

    int SearchFrameID(char *name);

    void GetWorldPosition(float *out_position, float *local_position);

    void GetWorldPosition0(float *out_position);

    void GetWorldDir(float *out_dir, float *local_dir);

    void SetRotType(int type);

    void SetAttrParam(mgCFrameAttr &attr, int children, int mask);

    void SetAttrParamObjAlpha(float alpha, int children);

    void SetAttrParamDraw(int draw, int children);

    int GetDrawRect(mgVu0FBOX *rect, mgCDrawManager *manager);

    mgCFrame &operator=(mgCFrame &other);

    mgMaterial *GetMaterial(int index);

    void SetBound(BoundInfo *bound) { this->bound = bound; }
};

STATIC_ASSERT(sizeof(mgCFrame::BoundInfo) == 0xB0);
STATIC_ASSERT(sizeof(mgCFrame) == 0x110);

int mgFrameNameComp(char *left, char *right);

int mgInsideScreen(mgVu0FBOX *box);

int mgInsideScreen(mgVu0FBOX *box, float (*matrix)[4]);

int mgInsideScreen(mgVu0FBOX *box, float (*matrix)[4], float *out_max, float *out_min);

int mgInsideScreen(float (*corners)[4], float (*matrix)[4]);

int mgInsideScreen(float (*corners)[4], float (*matrix)[4], float *out_max, float *out_min);
