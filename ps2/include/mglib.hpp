#pragma once

#include "common.h"

#include <libdma.h>
#include <libgraph.h>
#include <libpkt.h>
#include <libvu0.h>

#include "mg_drawenv.hpp"

class mgCDrawEnv;
class mgCDrawManager;
class mgCFrame;
class mgCMemory;
class mgCTexture;
class mgCTextureManager;
class mgCVisual;
class mgRENDER_INFO;
struct mgPOINT_LIGHT;
struct mgVu0FBOX;
struct sceGsClamp;
template <typename T> class mgRect;

enum mgSCREEN_MODE {
    MG_SCREEN_MODE_512X448 = 0,
    MG_SCREEN_MODE_512X416 = 1,
    MG_SCREEN_MODE_512X480 = 2,
    MG_SCREEN_MODE_640X448 = 3,
};

enum mgVU_PROG_ID {
    MG_VU_PROG_MAIN = 0,
    MG_VU_PROG_SHADOW = 1,
    MG_VU_PROG_3DSPRITE = 2,
    MG_VU_PROG_USER = 0x100,
};

extern u_long128 My_dma_start0[];

extern u_long128 Vu_progmain[];

extern u_long128 Vu_prog0[];

extern u_long128 Vu_prog_sdw[];

extern u_long128 Vu_prog_3dsp[];

struct MG_PICKZ {
    int enable;
    int x;
    int y;
    int z;
};
STATIC_ASSERT(sizeof(MG_PICKZ) == 0x10);

extern int mgAntialiasing;

extern int mgFrameRate;

extern float mgNowFrameRate;

extern sceDmaChan *DmaCH1;

extern sceDmaChan *DmaCH2;

extern sceDmaChan *DmaCH8;

extern sceVif1Packet *mgVif1Packet;

extern int mgClearBackFlag;

extern int mgScreenMode;

extern int mgScreenWidth;

extern int mgScreenHeight;

extern int mgScreenNX;

extern int mgScreenNY;

extern int mgScreenMX;

extern int mgScreenMY;

extern int mgScreenOffx;

extern int mgScreenOffy;

extern int mgScreenDepth;

extern int mgScreenZDepth;

extern int mgScreenLeft;

extern int mgScreenRight;

extern int mgScreenTop;

extern int mgScreenBottom;

extern int VSyncField;

extern sceGsTex1 mgTEX1_1;

extern sceGsTex1 mgTEX1_2;

extern sceGsTest mgTEST_1;

extern sceGsTest mgTEST_2;

extern sceGsZbuf mgZBUF_1;

extern sceGsZbuf mgZBUF_2;

extern sceGsAlpha mgALPHA_1;

extern sceGsAlpha mgALPHA_2;

extern sceGsTexa mgTEXA_1;

extern sceGsTexa mgTEXA_2;

extern sceGsFrame mgFRAME_1;

extern int ddraw_size;

extern sceGifTag mgGiftagAD;

extern mgRENDER_INFO mgRenderInfo;

extern sceVu0FVECTOR mgBackColor;

extern mgCTextureManager mgTexManager;

extern mgCDrawManager mgDrawManager;

extern sceGsDBuff mgDBuff;

extern MG_PICKZ mgPickZBuff[4];

void mgPerformanceMeter(int enable);

int mgGetPerformanceMeterFlag();

void mgInitVSyncCallBack(int (*callback)(int));

void mgSetRotateThread(int priority);

int mgGetVSyncCount();

void mgInit(int screen_mode, int video_mode);

void mgInitVif1Packet(u_long128 *buffer0, u_long128 *buffer1, int size);

void mgSetPacketBuffer(mgCMemory *memory0, mgCMemory *memory1);

void mgSetDataBuffer(mgCMemory *memory0, mgCMemory *memory1, int skip_head);

mgCMemory *mgGetDataBuffer();

int mgGetTopVRAMAddress();

float mgGetNowFrameRate();

void mgBeginFrame(mgCDrawManager *manager);

void mgBeginPacket(mgCDrawManager *manager);

void mgBeginDraw(mgCMemory *memory, int *block_list, mgCDrawManager *manager);

void mgEndDraw(mgCDrawManager *manager);

void mgPreEndDraw(mgCDrawManager *manager);

int mgEndDrawReloadTexture(int block, mgCDrawManager *manager);

void mgEndDraw(int block, mgCDrawManager *manager);

void mgStoreFrameImage();

void mgEndFrame(mgCDrawManager *manager);

void mgSendPacket(mgCDrawManager *manager);

void mgEndPacket(mgCDrawManager *manager);

void mgWaitFrame();

int mgDraw(mgCFrame *frame);

int mgDrawDirect(mgCFrame *frame);

int mgDrawDirect(mgCVisual *visual, float (*matrix)[4]);

void mgDrawDirectStart();

int mgDrawDirect2(mgCFrame *frame);

void mgDrawDirectEnd();

int mgGetDrawRect(mgCFrame *frame, mgVu0FBOX *rect);

void mgBeginDrawShadow(mgCTexture *shadow, mgCTexture *unused);

void mgEndDrawShadow(mgCTexture *shadow, mgCTexture *unused);

void mgSetRenderInfo(float projection, float near_z, float far_z);

void mgSetProjection(float projection);

float mgGetProjection();

void mgSetBackGround(float *color);

void mgSetBackGround(float r, float g, float b, float a);

void mgInitLighting();

void mgInitActiveLighting();

int mgActiveLighting(int set, int copy);

void mgSetLight(float (*direction)[4], float (*color)[4]);

void mgGetLight(float (*direction)[4], float (*color)[4]);

void mgSetLight(int light, float *direction, float *color);

void mgSetAmbient(float *ambient);

void mgGetAmbient(float *ambient);

void mgSetPlight(int light, float *position, float *color, float intensity, float range);

void mgSetPlight(int light, mgPOINT_LIGHT *point_light);

void mgGetPlight(int light, mgPOINT_LIGHT *point_light);

void mgResetPlight();

void mgSetViewMatrix(float (*view)[4], float *position);

void mgSetDropShadowMatrix(float *light, float *position, float *normal);

void mgFogEnable(int enable);

int mgGetFogEnable();

void mgPlightEnable(int enable);

int mgGetPlightEnable();

void mgSetFogParam(float near_z, float far_z, unsigned char r, unsigned char g, unsigned char b,
                   float far_fog, float near_fog);

void mgSetFogParam(mgFOG_PARAM *fog);

void mgGetFogParam(mgFOG_PARAM *fog);

void mgSetAllScissorFlag(int flag);

void mgFlushRenderInfo();

void mgSetPkTextureRepeat(int repeat);

void mgSetPkTextureRepeat(sceGsClamp clamp);

void mgSetPkFrameBuffer(mgCTexture *texture);

void mgSetPkFrameBuffer(int fbp, int width, int height, int psm);

void mgGetFrameBuffer(mgCTexture *texture);

void mgGetFrameBackBuffer(mgCTexture *texture);

mgCDrawEnv *mgGetpDrawEnv(int index);

void mgSetPkMoveImage(mgCTexture *src, mgRect<int> src_rect, mgCTexture *dst, int dst_x, int dst_y,
                      int direction);

void mgSetPkMoveImage(sceGsTex0 *src, mgRect<int> src_rect, sceGsTex0 *dst, int dst_x, int dst_y,
                      int direction);

void mgSetPkMoveImage(mgCTexture *src, mgRect<int> src_rect, mgCTexture *dst, mgRect<int> dst_rect,
                      mgCDrawEnv *env);

void mgSetPkMoveImage(sceGsTex0 *src, mgRect<int> src_rect, sceGsTex0 *dst, int dst_height,
                      mgRect<int> dst_rect, mgCDrawEnv *env);

void mgSetPkClearScreen(unsigned char r, unsigned char g, unsigned char b, unsigned char a);

int mgStoreImage(mgCTexture *texture, u_long128 *buffer);

int mgStoreZBuffImage(mgRect<int> &rect, u_long128 *buffer);

float mgConvZBuffToDist(unsigned int z);

mgCTexture *mgGetTextureZ(int index);

int mgTransWorldPrim(int *prim, float *position);

int mgTransWorldScreen(int *screen, float *position);

int mgTransViewPrim(int *prim, float *position);

void mgTransWorldView(float *view, float *position);

int mgTransZPrim(float z);

float mgGetDistFromCamera(float *position);

void mgGetDirFromCamera(float *direction, float *position);

void mgGetCameraPos(float *position);

void mgGetCameraPose(float (*pose)[4]);

int mgTransWorldPrim3DSprite(int *top_left, int *bottom_right, float *position, float width,
                             float height, int unused);

u_long128 *mgGetVuProgPacket(int id);

int mgSendVuProg(unsigned int *packet, int id);

void mgSetUserVuProg(u_long128 **table, int count);

void mgSetUserVuProgAdr(int index, u_long128 *packet);

int mgInitFont();

void mgCloseFont();
