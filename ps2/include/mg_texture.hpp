#pragma once

#include "common.h"

#include <libgraph.h>

#include "mg_memory.hpp"

class mgCTexture;
class mgCTextureAnime;
struct sceVif1Packet;

enum mgTEXTURE_CONST {
    MG_TEXTURE_HASH_SIZE = 101,
    MG_TEXTURE_VRAM_FIX_DEFAULT = 0x3FE0,
    MG_TEXTURE_BLOCK_FIX = 0x7FFF,
    MG_TEXTURE_LEVEL_MAX = 4,
    MG_TEXTURE_CLUT_BLOCKS = 4,
    MG_TEXTURE_PAGE_BLOCKS = 32,
    MG_TEXTURE_IMG_GROUP_MAX = 32,
};

enum mgTEXTURE_FILTER {
    MG_TEXTURE_FILTER_NEAREST = 0,
    MG_TEXTURE_FILTER_LINEAR = 1,
    MG_TEXTURE_FILTER_2 = 2,
};

enum mgIMG_VERSION {
    MG_IMG_VERSION_NONE = 0,
    MG_IMG_VERSION_IMG = 1,
    MG_IMG_VERSION_IM2 = 2,
    MG_IMG_VERSION_IM3 = 3,
};

enum TIM2_IMAGE_TYPE {
    TIM2_RGB16 = 1,
    TIM2_RGB24 = 2,
    TIM2_RGB32 = 3,
    TIM2_IDTEX4 = 4,
    TIM2_IDTEX8 = 5,
};

struct TM2_PICTURE {
    u_int total_size;
    u_int clut_size;
    u_int image_size;
    u_short header_size;
    u_short clut_colors;
    u_char picture_format;
    u_char mipmap_count;
    u_char clut_type;
    u_char image_type;
    u_short width;
    u_short height;
    unsigned long long tex0;
    unsigned long long tex1;
    u_int gs_regs;
    u_int gs_tex_clut;
    long long mip_tbp1;
    long long mip_tbp2;
    int mip_sizes[1];
};
#pragma cpp_extensions on

struct TM2_head {
    char tag[4];
    char unk_04[0xC];
    union {
        struct {
    u_int total_size;
    u_int unk_14;
    u_int image_size;
    u_short header_size;
    u_short unk_1e;
    u_char unk_20;
    u_char mipmap_textures;
    u_char unk_22;
    u_char image_type;
    u_short image_width;
    u_short image_height;
    u_long unk_28;
    u_long tex1;
    char unk_38[0x18];
    u_int mipmap_size[4];
};
        TM2_PICTURE picture;
    };
};
#pragma cpp_extensions reset

struct mgIMG_FILE_HEADER {
    char tag[4];
    u_int num;
    u_int num3;
    int unk_c;
};
STATIC_ASSERT(sizeof(mgIMG_FILE_HEADER) == 0x10);

struct mgIMG1_HEADER {
    char name[0x20];
    int offset;
    char unk_24[0xC];
};
STATIC_ASSERT(sizeof(mgIMG1_HEADER) == 0x30);

struct IMG_HEADER_NAME {
    char bytes[0x20];
};

struct mgIMG_HEADER {
    union {
    char name[0x20];
        IMG_HEADER_NAME name_copy;
    };
    int unk_20;
    int offset;
    int swizzled;
    int block;
    short no_image;
    short unk_32;
    int size;
    union {
    sceGsClamp clamp;
        long long clamp_bits;
    };
};
STATIC_ASSERT(sizeof(mgIMG_HEADER) == 0x40);

class mgCEnterIMGInfo {
public:
    int block[MG_TEXTURE_IMG_GROUP_MAX];
    int block_num[MG_TEXTURE_IMG_GROUP_MAX];
};
STATIC_ASSERT(sizeof(mgCEnterIMGInfo) == 0x100);

class mgCTexture {
public:
    short block;
    short width;
    short height;
    short bpp;
    char name[0x20];
    int vram_size;
    int image_blocks;
    int clut_size;
    sceGsTex0 tex0;
    sceGsTex1 tex1;
    sceGsClamp clamp;
    u_long128 *image[MG_TEXTURE_LEVEL_MAX];
    u_long128 *clut;
    int swizzled;
    mgCTexture *next;

#ifndef MG_DRAWPRIM_MANUAL_CTOR
    mgCTexture();
#endif

    void Initialize();

    void Bilinear(int mode);
};
STATIC_ASSERT(sizeof(mgCTexture) == 0x70);

class mgCTextureBlock {
public:
    int unk_0;
    int unk_4;
    mgCTexture *texture;
    mgCTextureAnime *anime;

    mgCTextureBlock();

    void Initialize();

    void Add(mgCTexture *texture);

    void Delete(mgCTexture *texture);
};
STATIC_ASSERT(sizeof(mgCTextureBlock) == 0x10);

struct mgTEXTURE_HASH {
    mgCTexture *texture;
    mgTEXTURE_HASH *next;
};
STATIC_ASSERT(sizeof(mgTEXTURE_HASH) == 8);

class mgCTextureManager {
public:
    int vram_top;
    int vram_fix;
    int last_block;
    int block_max;
    mgCTextureBlock *blocks;
    mgCTextureBlock fix_block;
    mgTEXTURE_HASH *hash_table[MG_TEXTURE_HASH_SIZE];
    mgCTexture *texture_buf;
    mgCTexture **texture_stack;
    int texture_max;
    int texture_num;
    mgTEXTURE_HASH *hash_buf;
    mgTEXTURE_HASH **hash_stack;
    int hash_max;
    int hash_num;
    char name_suffix[0x14];
    mgCMemory unk_1ec;

    mgCTextureManager();

    void SetTableBuffer(int texture_max, int block_max, mgCMemory *memory);

    void Initialize(int vram_top, int vram_fix);

    int hash(char *name);

    void AddHash(mgCTexture *texture);

    void DelHash(mgCTexture *texture);

    mgCTexture *SearchHash(char *name, int block);

    mgCTexture *SearchTextureName(char *name, int block);

    mgCTexture *SearchTexture(char *name);

    mgCTexture *GetTexture(char *name, int block);

    mgCTextureBlock *GetTextureBlock(int block);

    int GetRemainVRAM(int block);

    mgCTexture *EnterTexture(int block, char *name, u_long128 **image, int width, int height,
                             int bpp, u_long128 *clut, u_long tex1, int swizzled);

    mgCTexture *EnterTexture(int block, char *name, TM2_head *tm2, int swizzled, int no_image);

    int EnterIMGFile(u_char *img, int block, mgCMemory *stack, mgCEnterIMGInfo *info);

    void DeleteTexture(mgCTexture *texture);

    void DeleteTexture(char *name, int block);

    void DeleteBlock(int block);

    void EndEnterTexture(int block);

    void ReloadTexture(int block, sceVif1Packet *packet);

    int ReloadTexture(int block, u_int *packet);

    int ReloadCLUT(mgCTexture *texture, u_int *packet);

    void ReloadCLUT(mgCTexture *texture, sceVif1Packet *packet);

    void TexAnimeOn(int block, char *group_name);

    void TexAnimeOff(int block, char *group_name);

    void TexAnimeAllOff(int block);

    char **GetGroupNameList(int block, int *num);

    void DeleteTexAnimeGroup(int block, int group);

    void DeleteTexAnime(int block);

    mgCTextureAnime *GetTexAnime(int block);

    void LoadCFGFile(char *script, int size, mgCMemory *stack, mgCTextureAnime *anime);
};
STATIC_ASSERT(sizeof(mgCTextureManager) == 0x21C);

int mgGetIMGHeaderNum(char *img);

mgIMG_HEADER mgGetIMGHeader(char *img, int index);

int mgLoadImage(u_int *packet, int dbp, int dpsm, int dbw, u_long128 *image, int qwc, int x, int y,
                int w, int h);
