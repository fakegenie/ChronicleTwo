#pragma once

#include "common.h"

#include <libvu0.h>

class mgCFrame;
class mgCMemory;

enum DA_FRAME_POSE_TYPE {
    DA_FRAME_POSE_NONE    = 0,
    DA_FRAME_POSE_BONE    = 1,
    DA_FRAME_POSE_BONE_YX = 2,
    DA_FRAME_POSE_B_CDLR  = 3,
};

struct DA_FRAME_POSE {
    int  type;
    int  vertex_num;
    int *vertex_id;
    int  local;
};

STATIC_ASSERT(sizeof(DA_FRAME_POSE) == 0x10);

struct DA_FIX_VERTEX {
    sceVu0FVECTOR position;
    int           frame_id;
    float         weight;
    float         velocity_rate;
    float         unk_1c;
};

STATIC_ASSERT(sizeof(DA_FIX_VERTEX) == 0x20);

struct DA_BIND_VERTEX {
    int   vertex_id[2];
    float rate;
    float length;
};

STATIC_ASSERT(sizeof(DA_BIND_VERTEX) == 0x10);

struct DA_BOUNDING_BOX {
    sceVu0FVECTOR unk_0;
    sceVu0FVECTOR unk_10;
    int           frame_id;
};

STATIC_ASSERT(sizeof(DA_BOUNDING_BOX) == 0x30);

class CDACollision {
public:
    int           frame_id;
    float         friction;
    sceVu0FVECTOR center;
    sceVu0FVECTOR radius;
    mgCFrame     *frame;
    sceVu0FMATRIX lw_matrix;
    sceVu0FMATRIX inverse_matrix;

    virtual int CheckHit(float *position);

    virtual void Initialize();

    CDACollision() { Initialize(); }
};

STATIC_ASSERT(sizeof(CDACollision) == 0xD0);

class CDAColPipe : public CDACollision {
public:
    int axis;

    virtual int CheckHit(float *position);

    virtual void Initialize();

    CDAColPipe() { Initialize(); }
};

STATIC_ASSERT(sizeof(CDAColPipe) == 0xE0);

class CDynamicAnime {
public:
    mgCFrame         *top_frame;
    int               frame_num;
    mgCFrame        **frame;
    DA_FRAME_POSE    *frame_pose;
    int               vertex_num;
    sceVu0FVECTOR    *init_vertex;
    sceVu0FVECTOR    *now_vertex;
    sceVu0FVECTOR    *old_vertex;
    sceVu0FVECTOR    *velocity;
    sceVu0FVECTOR    *world_init_vertex;
    int               fix_vertex_num;
    DA_FIX_VERTEX    *fix_vertex;
    int               draw_frame_num;
    int              *draw_frame;
    int               bind_vertex_num;
    DA_BIND_VERTEX   *bind_vertex;
    int               bbox_num;
    DA_BOUNDING_BOX  *bbox;
    int               collision_num;
    CDACollision    **collision;
    sceVu0FVECTOR     gravity;
    float             k;
    float             wind_scale;
    float             wind_power;
    sceVu0FVECTOR     wind_dir;
    int               wind_seed;
    float             wind_gust;
    int               floor_enable;
    float             floor_y;

    CDynamicAnime();

    void ResetPosition();

    void Step();

    void SetWind(float power, float *dir);

    void ResetWind();

    void SetFloor(float y);

    void ResetFloor();

    void FramePose(mgCFrame *frame, DA_FRAME_POSE *pose);

    void PreCollision();

    void Initialize();

    void NewFrameTable(int num, mgCMemory *stack);

    void NewVertexTable(int num, mgCMemory *stack);

    void NewFixVertexTable(int num, mgCMemory *stack);

    void NewDrawFrameTable(int num, mgCMemory *stack);

    void NewBindVertexTable(int num, mgCMemory *stack);

    void NewBoundingBoxTable(int num, mgCMemory *stack);

    void NewCollisionTable(int num, mgCMemory *stack);

    void SetFrame(int index, mgCFrame *frame);

    mgCFrame *GetFrame(int index);

    DA_FRAME_POSE *pGetFramePose(int index);

    int CheckVertexID(int index);

    void SetInitVertex(int index, float *position);

    void GetInitVertex(int index, float *out_position);

    void SetNowVertex(int index, float *position);

    void SetOldVertex(int index, float *position);

    DA_FIX_VERTEX *pGetFixVertex(int index);

    void SetDrawFrame(int index, int frame_id);

    mgCFrame *GetDrawFrame(int index);

    DA_BIND_VERTEX *pGetBindVertex(int index);

    DA_BOUNDING_BOX *pGetBoundingBox(int index);

    void SetCollision(int index, CDACollision *collision);

    int DrawSub(int direct);

    void Copy(CDynamicAnime &dest, mgCFrame *top_frame, mgCMemory *stack);

    void Load(char *script, int size, mgCFrame *top_frame, mgCMemory *stack);
};

STATIC_ASSERT(sizeof(CDynamicAnime) == 0x90);
