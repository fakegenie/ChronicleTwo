#pragma once

#include "common.h"

#include "mg_drawenv.hpp"
#include "mg_visual.hpp"

class mgCFrame;
class mgCMemory;
class mgCTextureManager;
class mgRENDER_INFO;
class mgCFace;

struct mgVertexWeight {
    int matrix[4];
    float weight[4];

    mgVertexWeight();
};
STATIC_ASSERT(sizeof(mgVertexWeight) == 0x20);

class mgCVMotionData {
public:
    u_int *weight_data;
    int frame_id;
    mgCFrame **frame;
    float (*base_matrix)[4][4];
    int unk_10;
};
STATIC_ASSERT(sizeof(mgCVMotionData) == 0x14);

class mgCVisualMotionMDT : public mgCVisualFixMDT {
public:
    mgCFrame **frame;
    int frame_id;
    float (*base_matrix)[4][4];
    mgVu0FBOX base_box;
    int bone[32];
    int weight_num;
    mgVertexWeight *weight;

    mgCVisualMotionMDT() {
        Initialize();
    }

    virtual int Iam();

    virtual mgCVisual *Copy(mgCMemory *memory);

    virtual int CreateBBox(float *max, float *min, float (*matrix)[4]);

    virtual int CreateRenderInfoPacket(u_int *packet, float (*matrix)[4], mgRENDER_INFO *info);

    virtual void Initialize();

    virtual int CreateExtRenderInfoPacket(u_int *packet, float (*matrix)[4], mgRENDER_INFO *info);

    virtual int DataAssignMotionMDT(MDT_HEADER *header, mgCVMotionData *motion, mgCMemory *memory,
                                    mgCMemory *work_memory, mgCTextureManager *texture_manager);

    virtual int CreateFaceMotionPacket(u_int *packet, mgCFace *face, mgCVMotionData *motion);

    void CreateVertexWeight(u_int *weight_data, int frame_id, mgCMemory *memory);

    void ChangeWeight(mgCFrame **frame, float (*base_matrix)[4][4], int frame_id);

    void SetBaseBox(float *max, float *min);
};
STATIC_ASSERT(sizeof(mgCVisualMotionMDT) == 0x110);
