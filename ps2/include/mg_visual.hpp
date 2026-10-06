#pragma once

#include "common.h"

#include <libvu0.h>

#include "mg_dataset.hpp"

class mgCMemory;
class mgCTexture;
class mgCTextureManager;
class mgCDrawEnv;
class mgCDrawManager;
class mgRENDER_INFO;
class mgCFace;

enum mgFaceType {
    MG_FACE_PRIM_MASK = 0x7,
    MG_FACE_FLAT = 0x8,
    MG_FACE_NO_TEXTURE = 0x10,
    MG_FACE_COLOUR = 0x100,
    MG_FACE_NO_NORMAL = 0x200,
};

enum mgDestAlphaTest {
    MG_DEST_ALPHA_TEST_OFF = -1,
    MG_DEST_ALPHA_TEST_KEEP = 0,
    MG_DEST_ALPHA_TEST_ZERO = 1,
    MG_DEST_ALPHA_TEST_ONE = 2,
};

struct mgMaterial {
    sceVu0FVECTOR diffuse;
    sceVu0FVECTOR unk_10;
    mgCTexture *texture;
};
STATIC_ASSERT(sizeof(mgMaterial) == 0x30);

class mgCFace {
public:
    u_short type;
    short index_stride;
    short material;
    short index_num;
    short vertex_num;
    int *index;
    mgCFace *next;
    u_long128 packet_tag;
};
STATIC_ASSERT(sizeof(mgCFace) == 0x30);

struct mgFACE_GROUP {
    int material;
    mgCFace *face;
    mgFACE_GROUP *next;
    int vu_program;
    u_long128 *packet;
    int packet_size;
    int unk_18;
    int unk_1c;
};
STATIC_ASSERT(sizeof(mgFACE_GROUP) == 0x20);

class mgCVisualAttr {
public:
    int alpha_ref;
    int alpha_blend;
    int z_write;
    int z_test;
    int alpha_test;
    int dest_alpha_test;

    mgCVisualAttr();

    void Initialize();
};
STATIC_ASSERT(sizeof(mgCVisualAttr) == 0x18);

class mgCVisualMDT : public mgCVisual {
public:
    int vertex_num;
    int normal_num;
    int colour_num;
    int uv_num;
    sceVu0FVECTOR *vertex;
    sceVu0FVECTOR *normal;
    sceVu0FVECTOR *colour;
    sceVu0FVECTOR *uv;
    int material_num;
    mgMaterial *material;
    mgFACE_GROUP *face_group;

    mgCVisualMDT() {
        Initialize();
    }

    mgCVisualMDT &operator=(const mgCVisualMDT &source);

    virtual int Iam();

    virtual int GetMaterialNum();

    virtual mgMaterial *GetpMaterial();

    virtual mgMaterial *GetMaterial(int index);

    virtual int CreateBBox(float *max, float *min, float (*matrix)[4]);

    virtual int CreateRenderInfoPacket(u_int *packet, float (*matrix)[4], mgRENDER_INFO *info);

    virtual void Draw(float (*matrix)[4], mgCDrawManager *draw_manager);

    virtual int Draw(u_int *packet, float (*matrix)[4], mgCDrawManager *draw_manager);

    virtual void Initialize();

    virtual u_int CreatePacket(mgCDrawManager *draw_manager);

    virtual int CreateFacePacket(u_int *packet, mgCFace *face);

    virtual FACES_ID *CreateFace(FACES_ID *faces, mgCMemory *memory, mgCMemory *index_memory,
                                 mgCFace **face);

    virtual int CreateExtRenderInfoPacket(u_int *packet, float (*matrix)[4], mgRENDER_INFO *info);

    virtual int DataAssignMDT(MDT_HEADER *header, mgCMemory *memory,
                              mgCTextureManager *texture_manager);

    int SetMaterialRef(u_long128 *packet, mgMaterial *material, int flags);

    int SetPModeRef(u_long128 *packet, int type);

    void CopyMDTData(MDT_HEADER *header, mgCMemory *memory);

    void CopyMDTDataPointer(MDT_HEADER *header, mgCMemory *memory);

    sceVu0FVECTOR *GetColor(int *num);
} __attribute__((aligned(16)));
STATIC_ASSERT(sizeof(mgCVisualMDT) == 0x50);

class mgCVisualFixMDT : public mgCVisualMDT {
public:
    mgCVisualFixMDT() {
        Initialize();
    }

    virtual int Iam();

    virtual mgCVisual *Copy(mgCMemory *memory);

    virtual void Initialize();

    virtual u_int CreatePacket(mgCDrawManager *draw_manager);

    virtual int DataAssignMDT(MDT_HEADER *header, mgCMemory *memory,
                              mgCTextureManager *texture_manager);
};
STATIC_ASSERT(sizeof(mgCVisualFixMDT) == 0x50);

class mgCVisualPrim : public mgCVisual {
public:
    mgCVisualAttr attr;

    mgCVisualPrim() {
        Initialize();
    }

    virtual int Iam();

    virtual int CreateRenderInfoPacket(u_int *packet, float (*matrix)[4], mgRENDER_INFO *info);

    virtual void Initialize();
};

u_int *GetScrPad();

void SendDMA(void *packet, int size);

int mgSetPkTEX0(u_int *packet, u_long tex0, u_long tex1);

int mgSetPkTEX0(u_int *packet, u_long tex0, u_long tex1, u_long texa);

int mgSetPkTexFlush_TagCnt(u_int *packet);

int SetPointLight(u_int *packet, float (*matrix0)[4], float (*matrix1)[4]);

void CopyMaterial(mgMaterial *material, MDT_MATERIAL_ *source, mgCTextureManager *texture_manager);

u_long128 *SetData0(int vertex_num, int type, int **index, u_long128 *packet, u_long128 *vertex,
                    u_long128 *normal, u_long128 *uv, u_long128 *colour);

u_long128 *SetData1(int vertex_num, int type, int **index, u_long128 *packet, u_long128 *vertex,
                    u_long128 *normal, u_long128 *uv, u_long128 *colour);

u_long128 *SetData2(int vertex_num, int type, int **index, u_long128 *packet, u_long128 *vertex,
                    u_long128 *normal, u_long128 *uv, u_long128 *colour);

u_long128 *SetData3(int vertex_num, int type, int **index, u_long128 *packet, u_long128 *vertex,
                    u_long128 *normal, u_long128 *uv, u_long128 *colour);

u_long128 *SetData4(int vertex_num, int type, int **index, u_long128 *packet, u_long128 *vertex,
                    u_long128 *normal, u_long128 *uv, u_long128 *colour);

u_long128 *SetData5(int vertex_num, int type, int **index, u_long128 *packet, u_long128 *vertex,
                    u_long128 *normal, u_long128 *uv, u_long128 *colour);

u_long128 *SetData6(int vertex_num, int type, int **index, u_long128 *packet, u_long128 *vertex,
                    u_long128 *normal, u_long128 *uv, u_long128 *colour);

u_long128 *SetData7(int vertex_num, int type, int **index, u_long128 *packet, u_long128 *vertex,
                    u_long128 *normal, u_long128 *uv, u_long128 *colour);

void SetDrawEnv(mgCDrawEnv *env, mgCVisualAttr *attr, mgCDrawEnv *base);

struct mgVisualGifTag {
    u_int word0;
    u_int words[3];
};
STATIC_ASSERT(sizeof(mgVisualGifTag) == 0x10);
extern mgVisualGifTag giftag;

extern u_long128 set_tex0_dma;

extern u_long128 set_tex0_giftag;

extern u_long128 set_texa_dma;

extern u_long128 set_texa_giftag;

extern u_long128 mat_vif;

extern u_long128 mat_vif_dif;

extern u_long128 mat_vif_d;

extern u_long128 mat_pw;

extern u_long128 mat_vif_d_tex;

extern int start_dma;

extern int buff_id;

extern mgCTexture *prev_tex;
