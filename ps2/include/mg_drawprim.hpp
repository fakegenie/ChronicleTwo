#pragma once

#include "common.h"

#include <libpkt.h>

#include "mg_drawenv.hpp"
#include "mg_texture.hpp"

class mgCMemory;
class mgCTextureManager;
class mgCDrawManager;

enum mgPRIM_TYPE {
    MG_PRIM_POINT = 0,
    MG_PRIM_LINE = 1,
    MG_PRIM_LINE_STRIP = 2,
    MG_PRIM_TRIANGLE = 3,
    MG_PRIM_TRIANGLE_STRIP = 4,
    MG_PRIM_TRIANGLE_FAN = 5,
    MG_PRIM_SPRITE = 6,
};

enum mgALPHA_BLEND {
    MG_ALPHA_BLEND_NORMAL = 1,
    MG_ALPHA_BLEND_ADD = 2,
    MG_ALPHA_BLEND_SUB = 3,
    MG_ALPHA_BLEND_NONE = 4,
    MG_ALPHA_BLEND_ADD_FULL = 5,
};

enum mgDEPTH_TEST {
    MG_DEPTH_TEST_ALWAYS = -1,
    MG_DEPTH_TEST_GEQUAL = 1,
    MG_DEPTH_TEST_GREATER = 2,
};

enum mgZ_MASK {
    MG_Z_MASK_MASKED = -1,
    MG_Z_MASK_WRITE = 1,
};

enum mgPACKET_CODE {
    MG_DMA_CNT = 1 << 28,
    MG_DMA_CALL = 5 << 28,
    MG_DMA_RET = 6 << 28,
    MG_VIF_DIRECT = 0x50 << 24,
    MG_GIFTAG_EOP = 1 << 15,
    MG_GIFTAG_PRE = 1 << 14,
    MG_GIFTAG_PRIM_SHIFT = 15,
    MG_GIFTAG_NREG_SHIFT = 28,
    MG_UNCACHED = 0x20000000,
    MG_VIF_OFFSET = 0x02 << 24,
    MG_VIF_BASE = 0x03 << 24,
    MG_VIF_FLUSHA = 0x13 << 24,
    MG_VIF_MSCAL = 0x14 << 24,
    MG_VIF_MSCNT = 0x17 << 24,
    MG_VIF_UNPACK_V4_32 = 0x6C << 24,
    MG_VIF_UNPACK_FLG = 1 << 15,
    MG_VIF_NUM_SHIFT = 16,
};

enum mgGS_CODE {
    MG_GS_PRMODECONT = 0x1A,
    MG_GS_ZGREATER = 3,
    MG_GS_PRIM_FST = 1 << 8,
};

struct mgSORT_PACKET {
    u_long128 *common;
    u_long128 *packet;
    mgSORT_PACKET *next;
    s16 group;
    s16 vu_program;
};
STATIC_ASSERT(sizeof(mgSORT_PACKET) == 0x10);

class mgCDrawPrim {
public:
    mgCDrawManager *draw_manager;
    mgCMemory *memory;
    sceVif1Packet *vif_packet;
    int detached;
    mgCDrawEnv draw_env;
    sceGsPrim prim;
    mgCTexture texture;
    int bilinear;
    int z_mask;
    int disabled;
    u_long128 *packet_start;
    u_long128 *packet_top;
    union { u_long128 *write; u_int *write_words; u_long *command_write; };
    union { u_long128 *dma_start; u_int *dma_start_words; };
    union { u_long128 *direct_start; u_int *direct_start_words; };
    u_int *giftag;
    union { u_int *dma_tag; int *dma_tag_words; };
    union { u_int *direct_code; int *direct_code_words; };
    int unk_f4;
    union { float q; u_int q_bits; };
    int coord;
    int packed;
    int nreg;
    int unk_108;
    int unk_10c;
    int offset_x;
    int offset_y;
    int unk_118;
    int unk_11c;

#ifndef MG_DRAWPRIM_MANUAL_CTOR
    mgCDrawPrim();
#endif

    void Initialize(mgCMemory *memory, sceVif1Packet *vif_packet);

    void Begin(int type);

    void BeginDma();

    void EndDma();

    void Flush();

    void End();

    void Begin2();

    void BeginPrim2(int type);

    void BeginPrim2(int type, unsigned int regs_lo, unsigned int regs_hi, int nreg);

    void EndPrim2();

    void End2();

    void Data0(float *data);

    void Data4(float *data);

    void Data(int *data);

    u_char *DirectData(int count);

    void Vertex(int x, int y, int z);

    void Vertex(float x, float y, float z);

    void Vertex(float *pos);

    void Vertex4(int x, int y, int z);

    void Vertex4(int *pos);

    void Color(int r, int g, int b, int a);

    void Color(float *color);

    void TextureCrd4(int u, int v);

    void TextureCrd(int u, int v);

    void Direct(unsigned long reg, unsigned long data);

    void Texture(mgCTexture *texture);

    void AlphaBlendEnable(int enable);

    void AlphaBlend(int mode);

    void AlphaTestEnable(int enable);

    void AlphaTest(int method, int ref);

    void DAlphaTest(int enable, int mode);

    void DepthTestEnable(int enable);

    void DepthTest(int method);

    void ZMask(int mask);

    void TextureMapEnable(int enable);

    void Bilinear(int enable);

    void Shading(int enable);

    void AntiAliasing(int enable);

    void FogEnable(int enable);

    void Coord(int coord);

    void GetOffset(int *x, int *y);
};
STATIC_ASSERT(sizeof(mgCDrawPrim) == 0x120);

class mgCDrawManager {
public:
    int *draw_order;
    int *order_index;
    int group_max;
    int group_num;
    mgSORT_PACKET ***packet_list;
    int *unk_14;
    int *packet_num;
    int sort_num;
    int sort_max;
    float sort_num_f;
    float near_clip;
    float far_clip;
    float clip_range;
    int unk_34;
    int unk_38;
    int unk_3c;
    int unk_40;
    float sort_near;
    float sort_ratio;
    float sort_scale;
    mgSORT_PACKET **sort_table;
    mgCMemory *memory;
    mgCTextureManager *texture_manager;
    mgCMemory *packet_memory;
    mgCMemory *data_memory;
    mgRENDER_INFO *render_info;
    int unk_68;
    int unk_6c;
    int unk_70;
    mgSORT_PACKET ***packet_cursor;
    int unk_78;
    int unk_7c;

    mgCDrawManager();

    void SetSortTable(int num);

    void BeginDraw(mgCMemory *memory, int *order);

    void ClearTable();

    void PreEndDraw();

    int ReloadTexture(int group, sceVif1Packet *vif_packet);

    int Draw(int group, sceVif1Packet *vif_packet);

    void EndDraw(sceVif1Packet *vif_packet);

    void AddPacket(int group, u_long128 *common, u_long128 *packet, int vu_program);
};
STATIC_ASSERT(sizeof(mgCDrawManager) == 0x80);
