#pragma once

#include "common.h"

#include <libvu0.h>

class mgCMemory;
class mgCFrame;
class mgCVisualMDT;
class mgCTextureManager;
class mgCDrawManager;
class mgCDrawEnv;
class mgRENDER_INFO;
struct mgMaterial;

enum mgVisualKind {
    MG_VISUAL_KIND_VISUAL = 0,
    MG_VISUAL_KIND_MDT = 1,
    MG_VISUAL_KIND_FIX_MDT = 2,
    MG_VISUAL_KIND_MOTION_MDT = 3,
    MG_VISUAL_KIND_PRIM = 7,
};

enum mgVisualCreateType {
    MG_VISUAL_CREATE_END = -1,
    MG_VISUAL_CREATE_MDT = 0,
    MG_VISUAL_CREATE_FIX_MDT = 1,
    MG_VISUAL_CREATE_SHADOW_MDT = 2,
    MG_VISUAL_CREATE_SHADOW_FIX_MDT = 3,
    MG_VISUAL_CREATE_MOTION_MDT = 4,
};

enum mgMDTDataType {
    MG_MDT_DATA_NONE = 0,
    MG_MDT_DATA_VERTEX = 1,
    MG_MDT_DATA_NORMAL = 2,
    MG_MDT_DATA_UV = 3,
    MG_MDT_DATA_COLOUR = 4,
    MG_MDT_DATA_MATERIAL = 5,
};

struct MDT_HEADER {
    char magic[4];
    int header_size;
    int unk_08;
    int vertex_num;
    int vertex_ofs;
    int normal_num;
    int normal_ofs;
    int colour_num;
    int colour_ofs;
    int faces_size;
    int faces_ofs;
    int uv_num;
    int uv_ofs;
    int material_num;
    int material_ofs;
    int unk_3c;
};
STATIC_ASSERT(sizeof(MDT_HEADER) == 0x40);

struct MDT_MATERIAL_ {
    sceVu0FVECTOR diffuse;
    float unk_10[4];
    float unk_20[4];
    float unk_30;
    char texture[32];
    int unk_54;
    float extra[2];
};
STATIC_ASSERT(sizeof(MDT_MATERIAL_) == 0x60);

struct MDT_FACES {
    int unk_00;
    int header_size;
    int prim_num;
    int unk_0c;
};
STATIC_ASSERT(sizeof(MDT_FACES) == 0x10);

struct FACES_ID {
    u_int type;
    u_int face_num;
    u_int material;
    int index[1];
};

struct MDS_HEADER {
    int unk_00;
    int unk_04;
    u_int object_num;
    int object_ofs;
};
STATIC_ASSERT(sizeof(MDS_HEADER) == 0x10);

struct MDTOBJ_HEADER {
    int unk_00;
    int size;
    char name[32];
    int mdt_ofs;
    int parent;
    sceVu0FMATRIX matrix;
};
STATIC_ASSERT(sizeof(MDTOBJ_HEADER) == 0x70);

struct mgCreateVisualType {
    int type;
    char *name;
};
STATIC_ASSERT(sizeof(mgCreateVisualType) == 0x8);

struct mgLoadData {
    MDS_HEADER *mds;
    mgCMemory *memory;
    mgCMemory *work_memory;
    mgCreateVisualType *visual_type;
    mgCTextureManager *texture_manager;
    u_int *weight;
    float (*matrix)[4][4];
    int unk_1c[9];
};
STATIC_ASSERT(sizeof(mgLoadData) == 0x40);

class mgCVisual {
public:
    int unk_00;
    mgCDrawEnv *draw_env;
    mgCTextureManager *texture_manager;
    u_int prmode;
    int vu1_base;
    int vu1_offset;
    int unk_18;

    mgCVisual() { Initialize(); }

    virtual int Iam() ;

    virtual int GetMaterialNum() ;

    virtual mgMaterial *GetpMaterial() ;

    virtual mgMaterial *GetMaterial(int index) ;

    virtual mgCVisual *Copy(mgCMemory *memory) ;

    virtual int CreateBBox(float *max, float *min, float (*matrix)[4]) ;

    virtual int CreateRenderInfoPacket(u_int *packet, float (*matrix)[4], mgRENDER_INFO *info) ;

    virtual int CreatePacket(mgCMemory *memory, mgCMemory *work_memory) ;

    virtual void Draw(float (*matrix)[4], mgCDrawManager *draw_manager) ;

    virtual int Draw(u_int *packet, float (*matrix)[4], mgCDrawManager *draw_manager) ;

    virtual void Initialize() ;

    mgCTextureManager *GetTextureManager();

    int SetDrawEnvGifTag(u_long128 *packet, mgRENDER_INFO *info, mgCDrawEnv *draw_env);
};
STATIC_ASSERT(sizeof(mgCVisual) == 0x20);

class mgCMDTBuilder {
public:
    mgCMemory *memory;
    MDT_HEADER *header;
    union { char *end; int cursor; };
    union { char *data; int sectionStart; u_long128 *dataCursor; MDT_MATERIAL_ *materialCursor; };
    int data_num;
    union { MDT_FACES *faces; int *faceBlock; int faceBlockAddr; };
    FACES_ID *prim;
    int index_num;
    int face_index_num;
    union { int *index; int *faceCursor; int faceEnd; };
    int data_type;
    int unk_2c;
    MDT_MATERIAL_ material;

    void Begin(mgCMemory *memory);

    MDT_HEADER *End();

    void End(mgCFrame *frame, mgCVisualMDT *visual, mgLoadData *load);

    void BeginData(int type);

    void SetData(float *vector);

    void SetData(float x, float y, float z, float w);

    void SetMaterial(float *colour, char *texture);

    void EndData();

    void BeginFaces();

    void EndFaces();

    void BeginPrim(int type, int material);

    void AddFace(int index);

    void EndPrim();
};
STATIC_ASSERT(sizeof(mgCMDTBuilder) == 0x90);

void mgSetFrameAttr(mgCFrame *frame, int recursive);

mgCFrame *mgLoadMDSFile(MDS_HEADER *mds, mgCMemory *memory, mgCreateVisualType *visual_type, mgCTextureManager *texture_manager);

mgCFrame *mgLoadMDSFile(mgLoadData *load);

void mgCreateBBoxSphere(float *max, float *min, float *sphere, float (*vertex)[4], int vertex_num);

mgCFrame *mgCopyFrame(mgCFrame *frame, mgCMemory *memory, int copy_visual);
