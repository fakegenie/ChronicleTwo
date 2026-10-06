#pragma once

#include "common.h"

#include <libvu0.h>

#include "collision.hpp"
#include "font.hpp"

class mgCCamera;
class mgCFrame;
class mgCMemory;
class mgCVisualMDT;
struct MoveCheckInfo;

enum MotionKeyType {
    MOTION_KEY_ROTATION        = 0,
    MOTION_KEY_SCALE           = 1,
    MOTION_KEY_TRANSLATION     = 2,
    MOTION_KEY_VERTEX          = 12,
    MOTION_KEY_SKIN_WEIGHTED   = 20,
    MOTION_KEY_SKIN_AVERAGED   = 21,
    MOTION_KEY_CAMERA_POSITION = 30,
    MOTION_KEY_CAMERA_TARGET   = 31,
    MOTION_KEY_CAMERA_ROLL     = 32,
    MOTION_KEY_CAMERA_FOV      = 33,
    MOTION_KEY_MATERIAL_ALPHA  = 40,
    MOTION_KEY_MATERIAL_COLOR  = 41,
    MOTION_KEY_VISIBLE         = 50,
    MOTION_KEY_VISIBLE_TREE     = 51,
};

enum CheckWidthSide {
    CHECK_WIDTH_SIDE_POS_X = 1 << 0,
    CHECK_WIDTH_SIDE_NEG_X = 1 << 1,
    CHECK_WIDTH_SIDE_POS_Z = 1 << 2,
    CHECK_WIDTH_SIDE_NEG_Z = 1 << 3,
};

struct FRAME_VECTOR_EX_DATA {
    u32           frame;
    u8            unk_04[0xC];
    sceVu0FVECTOR value;
};

STATIC_ASSERT(sizeof(FRAME_VECTOR_EX_DATA) == 0x20);

struct Mot_File_List {
    s32 frame;
    s32 target;
    s32 type;
    u8  unk_0C[4];
    u32 key_count;
    u32 more;
    u8  unk_18[8];
};

STATIC_ASSERT(sizeof(Mot_File_List) == 0x20);

struct Mot_List {
    s32           frame;
    s32           target;
    s32           type;
    u32           key_count;
    sceVu0FVECTOR *values;
    u32           *key_frames;
    Mot_List      *next;
    u8            unk_1C[4];
};

STATIC_ASSERT(sizeof(Mot_List) == 0x20);

struct tagFRAME_INF {
    s32            parent;
    u32            vertex_count;
    u32            normal_count;
    s32            (*vertex_refs)[12];
    sceVu0FVECTOR *base_vertices;
    sceVu0FVECTOR *base_normals;
    u8             unk_18[8];
};

STATIC_ASSERT(sizeof(tagFRAME_INF) == 0x20);

struct tagMOTION_TYPE {
    sceVu0FMATRIX *base_matrices;
    Mot_List      *motion_list;
    Mot_List      *skin_list;
    u32            unk_0C;
    tagFRAME_INF  *frame_info;
};

STATIC_ASSERT(sizeof(tagMOTION_TYPE) == 0x14);

struct MOTION_FILE_INFO {
    char *name;
    void *data;
    int   size;
};

STATIC_ASSERT(sizeof(MOTION_FILE_INFO) == 0xC);

struct CollisionInfo {
    s32     count;
    CCPoly *polys;
    s32     unk_08;
    s32     unk_0C;
};

STATIC_ASSERT(sizeof(CollisionInfo) == 0x10);

Mot_List *MotionProc(mgCFrame *root, float time, Mot_List *list, mgCCamera *camera);

Mot_List *MotionProc(mgCFrame *root, unsigned int from_frame, unsigned int to_frame, float blend, Mot_List *list, mgCCamera *camera);

Mot_List *MotionProc2(mgCFrame *root, tagMOTION_TYPE *motion, tagFRAME_INF *frame_info, Mot_List *list);

Mot_List *MotionProc3(mgCFrame *root, tagMOTION_TYPE *motion, tagFRAME_INF *frame_info, Mot_List *list);

void SetMotionTime(mgCFrame *root, tagMOTION_TYPE *motion, float time, mgCCamera *camera);

void ChangeMotion(mgCFrame *root, tagMOTION_TYPE *motion, unsigned int from_frame, unsigned int to_frame, float blend, mgCCamera *camera);

void DeformMesh(mgCFrame *root, tagMOTION_TYPE *motion, tagFRAME_INF *frame_info, bool with_normals);

void ChangeWeight(Mot_List *list, mgCMemory *memory, unsigned char *file, int frame, tagFRAME_INF *frame_info, mgCVisualMDT *visual, mgCFrame *root, mgCFrame *skin_root);

int CreateAnimeDataEX(tagMOTION_TYPE *motion, mgCMemory *memory, MOTION_FILE_INFO *files);

void AnimeDataInit(mgCFrame *root, tagMOTION_TYPE *motion, mgCMemory *memory, tagFRAME_INF **frame_info);

int AnimeDataInit(mgCFrame *root, tagMOTION_TYPE *motion, mgCMemory *memory, tagFRAME_INF *frame_info);

int CheckHit(CCPoly *polys, int count, float *from, float *to, float *hit_point, int nearest, int ignore_mask);

int CheckHit(CollisionInfo *info, float *from, float *to, float *hit_point, int nearest, int ignore_mask);

int CheckHitVertical(CCPoly *polys, int count, float *from, float height, float *hit_point, int ignore_mask);

int CheckHitVertical(CollisionInfo *info, float *from, float height, float *hit_point, int ignore_mask);

int CheckHits(CCPoly *polys, int count, float *from, float *to, int max_hits, int *hit_polys, float (*hit_points)[4], int sort, int ignore_mask);

int CheckHits(CollisionInfo *info, float *from, float *to, int max_hits, int *hit_polys, float (*hit_points)[4], int sort, int ignore_mask);

int CheckHitsPipeY(CCPoly *polys, int count, float *from, float height, int max_hits, int *hit_polys, float (*hit_points)[4], int sort, int ignore_mask);

int CheckHitsPipe(CCPoly *polys, int count, float *from, float *to, int max_hits, int *hit_polys, float (*hit_points)[4], int sort, int ignore_mask);

int CheckHitsSphere(CCPoly *polys, int count, float *sphere, int max_hits, int *hit_polys, float (*hit_points)[4], int sort, int ignore_mask);

int MoveCheck(float *pos, float *velocity, float *out_pos, MoveCheckInfo *info, CCPoly *polys, int count, int ignore_mask);

int GetFootPoly(float *pos, float depth, CCPoly *found, float *ground, CCPoly *polys, int count, int ignore_mask);

void GetCPolyAttr(MoveCheckInfo *info, float *from, float *to, float height, CCPoly *polys, int count, int ignore_mask);

int CheckWidth(CCPoly *polys, int count, float *pos, float radius, float *out_pos, int ignore_mask);

int CheckWidthPipe(CCPoly *polys, int count, float *pos, float radius, float *out_pos, int ignore_mask);

int CreateCharaCPoly(CCPoly *polys, int max_polys, float *pos, float *target, float distance, float half_size);

float LinerInterpolation(float from, float to, float rate);

int LinerInterpolationI(int from, int to, int step, int steps);

void RollPos(float *centre, float *pos, float angle, float *out);

int CheckPosInOutForRect(RECT *rect, int x, int y);

float GetDisPosToRect(RECT *rect, int x, int y);

int CheckPosInOutFor2P(float x0, float y0, float x1, float y1, float x, float y);

int CalcIntersectionPointLineAndLine(float ax0, float ay0, float ax1, float ay1, float bx0, float by0, float bx1, float by1, float *out_x, float *out_y);

int CalcIntersectionPoint2PAnd2P(float ax0, float ay0, float ax1, float ay1, float bx0, float by0, float bx1, float by1, float *out_x, float *out_y);
