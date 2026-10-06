#include "common.h"
#include "mg_memory.hpp"
#include "mg_drawprim.hpp"
#include "mg_texture.hpp"
#include "mg_frame.hpp"

#include <cstring>
#include <libvu0.h>

#include "mg_drawenv.hpp"
#include "mg_math.hpp"
#include "mglib.hpp"

extern "C" u_char at_844[];
extern const unsigned char at_307__DATA[];
extern u_char at_324[];
extern u_char at_341[];
extern u_char at_1118[];
extern u_char at_1119[];

static mgCFrameAttr dmy_attr;

void mgCFrameAttr::Initialize() {
    memset(this, 0, sizeof(mgCFrameAttr));
    mgCVisualAttr::Initialize();
    color[0] = color[1] = color[2] = color[3] = 128.0f;
    alpha_ref = -1;
    draw = MG_FRAME_DRAW_VISIBLE;
    z_write = MG_ZBUF_WRITE;
    unk_3c = 0;
    unk_20 = 100.0f;
    fog = 1;
    obj_alpha = 1.0f;
    point_light = 1;
    unk_50[3] = 0.0f;
    unk_50[2] = 0.0f;
    unk_50[0] = 0.0f;
    unk_50[1] = 1.0f;
    depth_bias = 0.0f;
    unk_84 = 0;
}

mgCFrameAttr::mgCFrameAttr() {
    Initialize();
}

static void QuatToMat(float *quaternion, float (*matrix)[4]) {
    float yy;
    float zz;
    float ww;
    float y;
    float xy;
    float z;
    float xz;
    float zw;
    float xw;
    float yz;
    float yw;
    float x;
    float w;
    y = quaternion[1];
    z = quaternion[2];
    w = quaternion[3];
    x = quaternion[0];
    yz = y * z;
    zz = z * z;
    zw = z * w;
    xz = x * z;
    xy = x * y;
    yy = y * y;
    yw = y * w;
    ww = w * w;
    xw = x * w;
    matrix[0][0] = 1.0f - (2.0f * (zz + ww));
    matrix[0][1] = 2.0f * (yz - xw);
    matrix[0][2] = 2.0f * (yw + xz);
    matrix[0][3] = 0.0f;
    matrix[1][0] = 2.0f * (yz + xw);
    matrix[1][1] = 1.0f - (2.0f * (yy + ww));
    matrix[1][2] = 2.0f * (zw - xy);
    matrix[1][3] = 0.0f;
    matrix[2][0] = 2.0f * (yw - xz);
    matrix[2][1] = 2.0f * (zw + xy);
    matrix[2][2] = 1.0f - (2.0f * (yy + zz));
    matrix[2][3] = 0.0f;
    matrix[3][0] = 0.0f;
    matrix[3][1] = 0.0f;
    matrix[3][2] = 0.0f;
    matrix[3][3] = 1.0f;
}

INCLUDE_ASM("ps2/asm/pal/nonmatchings/mg_frame", test1__FPA4_fPA4_fPA4_fPfPf);

INCLUDE_ASM("ps2/asm/pal/nonmatchings/mg_frame", test2__FPfPf);

int mgInsideScreen(mgVu0FBOX *box) {
    sceVu0FMATRIX matrix;
    sceVu0FVECTOR corners[8];

    mgUnitMatrix(matrix);
    mgCreateBox8(corners, box->max, box->min);
    return mgInsideScreen(corners, matrix);
}
int mgInsideScreen(mgVu0FBOX *box, float (*matrix)[4]) {
    sceVu0FVECTOR corners[8];

    mgCreateBox8(corners, box->max, box->min);
    return mgInsideScreen(corners, matrix);
}
#pragma global_optimizer off
int mgInsideScreen(mgVu0FBOX *box, float (*matrix)[4], float *out_max, float *out_min) {
    sceVu0FVECTOR corners[8];
    mgCreateBox8(corners, box->max, box->min);
    return mgInsideScreen(corners, matrix, out_max, out_min);
}
#pragma global_optimizer reset
int mgInsideScreen(float (*corners)[4], float (*matrix)[4]) {
    sceVu0FVECTOR max;
    sceVu0FVECTOR min;

    return mgInsideScreen(corners, matrix, max, min);
}
#pragma global_optimizer off
#ifdef NONMATCHING
int mgInsideScreen(float (*corners)[4], float (*matrix)[4], float *out_max, float *out_min) {
    sceVu0FMATRIX screen_matrix;
    sceVu0MulMatrix(screen_matrix, mgRenderInfo.world_screen_rel, matrix);

    for (int i = 0; i < 8; i++) {
        sceVu0FVECTOR transformed;
        sceVu0ApplyMatrix(transformed, screen_matrix, corners[i]);
        float depth = transformed[3];
        if (depth < 0.0f) depth = -depth;
        transformed[0] /= depth;
        transformed[1] /= depth;
        if (i == 0) {
            sceVu0CopyVector(out_max, transformed);
            sceVu0CopyVector(out_min, transformed);
        } else {
            for (int axis = 0; axis < 4; axis++) {
                if (out_max[axis] < transformed[axis]) out_max[axis] = transformed[axis];
                if (out_min[axis] > transformed[axis]) out_min[axis] = transformed[axis];
            }
        }
    }
    return mgClipBoxW(out_max, out_min, mgRenderInfo.screen_box_max, mgRenderInfo.screen_box_min);
}
#else
INCLUDE_ASM("ps2/asm/pal/nonmatchings/mg_frame", mgInsideScreen__FPA4_fPA4_fPfPf);
#endif
#pragma global_optimizer reset

void mgCObject::SetPosition(float *position) {
    if (this->position[0] != position[0] || this->position[1] != position[1] ||
        this->position[2] != position[2]) {
        use_srt = 1;
        sceVu0CopyVector(this->position, position);
        this->position[3] = 1.0f;
        changed = 1;
    }
}

void mgCObject::SetPosition(float x, float y, float z) {
    float position[4];
    *(u_long128 *)position = *(u_long128 *)at_307__DATA;
    position[0] = x;
    position[1] = y;
    position[2] = z;

    mgCObject::SetPosition(position);
}
void mgCObject::GetPosition(float *out_position) {
    sceVu0CopyVector(out_position, position);
}
void mgCObject::SetRotation(float *rotation) {
    if (this->rotation[0] != rotation[0] || this->rotation[1] != rotation[1] ||
        this->rotation[2] != rotation[2]) {
        use_srt = 1;
        changed = 1;
        sceVu0CopyVector(this->rotation, rotation);
        this->rotation[3] = 0.0f;
    }
}
void mgCObject::SetRotation(float x, float y, float z) {
    float rotation[4];
    *(u_long128 *)rotation = *(u_long128 *)at_324;
    rotation[0] = x;
    rotation[1] = y;
    rotation[2] = z;

    mgCObject::SetRotation(rotation);
}
void mgCObject::GetRotation(float *out_rotation) {
    sceVu0CopyVector(out_rotation, rotation);
}
void mgCObject::SetScale(float *scale) {
    if (this->scale[0] != scale[0] || this->scale[1] != scale[1] || this->scale[2] != scale[2]) {
        use_srt = 1;
        this->scale[0] = scale[0];
        this->scale[1] = scale[1];
        this->scale[2] = scale[2];
        changed = 1;
        this->scale[3] = 0.0f;
    }
}
void mgCObject::SetScale(float x, float y, float z) {
    float scale[4];
    *(u_long128 *)scale = *(u_long128 *)at_341;
    scale[0] = x;
    scale[1] = y;
    scale[2] = z;

    mgCObject::SetScale(scale);
}
void mgCObject::GetScale(float *out_scale) {
    sceVu0CopyVector(out_scale, scale);
}
void mgCObject::Initialize() {
    SetPosition(0.0f, 0.0f, 0.0f);
    SetRotation(0.0f, 0.0f, 0.0f);
    SetScale(1.0f, 1.0f, 1.0f);
    changed = 1;
    use_srt = 0;
}
mgCFrame::mgCFrame() {
    Initialize();
}

void mgCFrame::Initialize() {
    elder = NULL;
    brother = NULL;
    child = NULL;
    parent = NULL;
    sceVu0UnitMatrix(lw_matrix);
    sceVu0UnitMatrix(trans_matrix);
    name = NULL;
    rot_type = 0;
    reference = 0;
    visual = NULL;
    attr = NULL;
    frame_num = 0;
    frame_list = NULL;
    init_matrix = NULL;
    bound = NULL;
    mgCObject::Initialize();
}

void mgCFrame::SetName(char *name) {
    this->name = name;
}
void mgCFrame::SetTransMatrix(float *quaternion) {
    float saved_row[4];
    changed = 1;
    *(u_long128 *)saved_row = *(u_long128 *)trans_matrix[3];
    QuatToMat(quaternion, trans_matrix);
    *(u_long128 *)trans_matrix[3] = *(u_long128 *)saved_row;
}

void mgCFrame::SetBBox(float *max, float *min) {
    mgCFrame::BoundInfo *record = (mgCFrame::BoundInfo *)bound;
    if (record != 0) {
        sceVu0CopyVector(((mgCFrame::BoundInfo *)bound)->max, max);
        sceVu0CopyVector(((mgCFrame::BoundInfo *)bound)->min, min);

        float *extremes[4];
        extremes[0] = ((mgCFrame::BoundInfo *)bound)->min;
        extremes[1] = ((mgCFrame::BoundInfo *)bound)->max;
        for (s32 i = 0; i < 8; i++) {
            ((mgCFrame::BoundInfo *)bound)->corner[i][3] = 1.0f;
            ((mgCFrame::BoundInfo *)bound)->corner[i][0] = extremes[(i & 1) != 0][0];
            ((mgCFrame::BoundInfo *)bound)->corner[i][1] = extremes[(i & 2) != 0][1];
            ((mgCFrame::BoundInfo *)bound)->corner[i][2] = extremes[(i & 4) != 0][2];
        }
    }
}

void mgCFrame::GetBBox(float *out_max, float *out_min) {
    if (bound == NULL) {
        mgZeroVectorW(out_max);
        mgZeroVectorW(out_min);
    } else {
        sceVu0CopyVector(out_max, bound->max);
        sceVu0CopyVector(out_min, bound->min);
    }
}
void mgCFrame::SetBSphere(float *center, float radius) {
    if (bound != NULL) {
        sceVu0CopyVector(bound->center, center);
        bound->radius = radius;
    }
}
mgCFrame *mgCFrame::GetFrame(int index) {
    if (index < 0 || index > this->frame_num || this->frame_list == 0) {
        return 0;
    }
    return this->frame_list[index];
}

int mgCFrame::RemakeBBox(float *out_max, float *out_min) {
    float matrix[4][4];
    mgCVisual *frameVisual = visual;
    if (frameVisual == 0) {
        return 0;
    }
    GetLWMatrix(matrix);
    if (frameVisual->CreateBBox(out_max, out_min, matrix) != 0) {
        SetBBox(out_max, out_min);
        return 1;
    }
    return 0;
}

extern "C" int __as__9mgVu0FBOXFR9mgVu0FBOX(...);
int mgCFrame::GetWorldBBox(mgVu0FBOX *box) {
    float worldBox[8];
    float matrix[4][4];
    float center[4];
    struct {
        float x;
        float y;
        float z;
        u_int w;
    } half;
    mgVu0FBOX child_box;
    s32 found = 0;
    if (visual != 0 && bound != 0) {
        found = 1;
        GetLWMatrix(matrix);

        mgApplyMatrix(&worldBox[0], &worldBox[4], matrix,
                      ((mgCFrame::BoundInfo *)bound)->max,
                      ((mgCFrame::BoundInfo *)bound)->min);
        if (attr != 0 && attr->billboard != 0) {
            float extent;
            sceVu0AddVector(center, &worldBox[0], &worldBox[4]);
            sceVu0ScaleVector(center, center, 0.5f);
            sceVu0SubVector(&half.x, &worldBox[0], center);
            if (half.x > half.y) {
                extent = half.x > half.z ? half.x : half.z;
            } else {
                extent = half.y > half.z ? half.y : half.z;
            }
            half.z = extent;
            half.y = extent;
            half.x = extent;
            half.w = 0;
            sceVu0AddVector(&worldBox[0], center, &half.x);
            sceVu0SubVector(&worldBox[4], center, &half.x);
        }
    }
    for (mgCFrame *node = child; node != 0; node = node->brother) {
        if (node->GetWorldBBox(&child_box) != 0) {
            if (found == 0) {
                __as__9mgVu0FBOXFR9mgVu0FBOX(worldBox, &child_box);
            } else {
                mgVectorMaxMin(&worldBox[0], &worldBox[4], &worldBox[0], &worldBox[4], child_box.max,
                               child_box.min);
            }
            found = 1;
        }
    }
    __as__9mgVu0FBOXFR9mgVu0FBOX(box, worldBox);
    return found;
}
#pragma global_optimizer reset

int mgCFrame::GetFrameNum() {
    s32 count;
    mgCFrame *node;
    s32 childCount;

    node = child;
    count = 1;
    if (node != NULL) {
        do {
            childCount = node->GetFrameNum();
            node = node->brother;
            count += childCount;
        } while (node != NULL);
    }
    return count;
}

void mgCFrame::SetParent(mgCFrame *parent) {
    if (this->parent == NULL) {
        this->parent = parent;
        if (parent != NULL) {
            parent->SetChild(this);
        }
    }
}
void mgCFrame::SetBrother(mgCFrame *new_brother) {
    if (new_brother != 0) {
        mgCFrame *next = brother;
        if (next != 0) {
            next->SetBrother(new_brother);
        } else {
            brother = new_brother;
            brother->elder = this;
        }
    }
}

void mgCFrame::SetChild(mgCFrame *new_child) {
    mgCFrame *first;

    if (new_child != NULL) {
        first = child;
        if (first != NULL) {
            first->SetBrother(new_child);
        } else {
            child = new_child;
        }
        new_child->parent = this;
    }
}

void mgCFrame::DeleteParent() {
    if (parent != NULL) {
        if (parent->child == this) {
            parent->child = brother;
            parent = NULL;
            if (brother != NULL) {
                brother->elder = NULL;
            }
            brother = NULL;
            elder = NULL;
        } else {
            parent = NULL;
            if (elder != NULL) {
                elder->brother = brother;
            }
            brother = NULL;
            elder = NULL;
        }
    }
}
void mgCFrame::SetReference(mgCFrame *reference) {
    if (parent == NULL && reference != NULL) {
        parent = reference;
        this->reference = 1;
        changed = 1;
    }
}
void mgCFrame::DeleteReference() {
    parent = NULL;
    reference = 0;
    changed = 1;
}
#pragma global_optimizer off
void mgCFrame::ClearChildFlag() {
    mgCFrame *frame;
    int flag = 1;

    if (child != NULL) {
        child->changed = flag;
        frame = child;
        if (frame->brother != NULL) {
            mgCFrame *next;
            while ((next = frame->brother) != NULL) {
                next->changed = flag;
                frame = frame->brother;
            }
            return;
        }
    }
}
#pragma global_optimizer reset
#pragma schedule reset

#pragma global_optimizer off
void mgCFrame::GetLocalMatrix(float (*matrix)[4]) {
    sceVu0FVECTOR translation;

    if (use_srt) {
        float *factor;
        float (*trans)[4];
        trans = trans_matrix;
        factor = scale;
        asm {
            lqc2 vf10, 0x0(factor)
            lqc2 vf1, 0x0(trans)
            lqc2 vf2, 0x10(trans)
            lqc2 vf3, 0x20(trans)
            lqc2 vf4, 0x30(trans)
            vmul.xyzw vf1, vf1, vf10
            vmul.xyzw vf2, vf2, vf10
            vmul.xyzw vf3, vf3, vf10
            vmulw.xyzw vf4, vf4, vf0w
            sqc2 vf1, 0x0(matrix)
            sqc2 vf2, 0x10(matrix)
            sqc2 vf3, 0x20(matrix)
            sqc2 vf4, 0x30(matrix)
        }
        if (rot_type & MG_FRAME_ROT_LOCAL_ORIGIN) {
            sceVu0CopyVector(translation, matrix[3]);
            mgZeroVectorW(matrix[3]);
        }
        if (rot_type & MG_FRAME_ROT_APPLY) {
            if (rotation[0] != 0.0f) sceVu0RotMatrixX(matrix, matrix, rotation[0]);
            if (rotation[1] != 0.0f) sceVu0RotMatrixY(matrix, matrix, rotation[1]);
            if (rotation[2] != 0.0f) sceVu0RotMatrixZ(matrix, matrix, rotation[2]);
        }
        if (rot_type & MG_FRAME_ROT_LOCAL_ORIGIN) {
            sceVu0AddVector(matrix[3], translation, position);
            matrix[3][3] = 1.0f;
        } else {
            sceVu0AddVector(matrix[3], matrix[3], position);
            matrix[3][3] = 1.0f;
        }
    } else {
        sceVu0CopyMatrix(matrix, trans_matrix);
    }
}
#pragma global_optimizer reset

#pragma global_optimizer off
#ifdef NONMATCHING
void mgCFrame::GetBBoardMatrix(int mode, float (*matrix)[4], mgRENDER_INFO *render_info) {
    sceVu0FMATRIX world;
    GetLWMatrix(world);
    sceVu0FVECTOR dimensions;
    dimensions[0] = mgDistVector(world[0]);
    dimensions[1] = mgDistVector(world[0]);
    dimensions[2] = mgDistVector(world[0]);
    dimensions[3] = 1.0f;

    sceVu0UnitMatrix(matrix);
    if (mode & 2) {
        sceVu0SubVector(matrix[2], render_info->camera_pos, world[3]);
        matrix[2][1] = 0.0f;
        matrix[2][3] = 0.0f;
        sceVu0Normalize(matrix[2], matrix[2]);
        matrix[0][0] = matrix[2][2];
        matrix[0][2] = -matrix[2][0];
    }
    if (mode & 1) {
        sceVu0FMATRIX pitch;
        sceVu0UnitMatrix(pitch);
        sceVu0FVECTOR direction;
        sceVu0SubVector(direction, render_info->camera_pos, world[3]);
        sceVu0Normalize(direction, direction);
        float rise = direction[1];
        direction[1] = 0.0f;
        direction[3] = 0.0f;
        float horizontal = mgDistVector(direction);
        pitch[1][1] = horizontal;
        pitch[1][2] = -rise;
        pitch[2][1] = rise;
        pitch[2][2] = horizontal;
        sceVu0SubVector(matrix[2], render_info->camera_pos, world[3]);
        matrix[2][1] = 0.0f;
        matrix[2][3] = 0.0f;
        sceVu0Normalize(matrix[2], matrix[2]);
        matrix[0][0] = matrix[2][2];
        matrix[0][2] = -matrix[2][0];
        mgMulMatrix(matrix, matrix, pitch);
    }
    for (int row = 0; row < 3; row++) {
        for (int axis = 0; axis < 4; axis++) matrix[row][axis] *= dimensions[axis];
    }
    matrix[3][0] = world[3][0];
    matrix[3][1] = world[3][1];
    matrix[3][2] = world[3][2];
    sceVu0CopyMatrix(lw_matrix, matrix);
    changed = 0;
    ClearChildFlag();
}
#else
INCLUDE_ASM("ps2/asm/pal/nonmatchings/mg_frame", GetBBoardMatrix__8mgCFrameFiPA4_fP13mgRENDER_INFO);
#endif
#pragma global_optimizer reset

#ifdef NONMATCHING
void mgCFrame::GetLWMatrix(float (*matrix)[4]) {
    sceVu0FMATRIX parent_matrix;
    sceVu0FMATRIX local;

    if (reference) changed = 1;
    if (!changed) {
        mgCFrame *frame = parent;
        if (frame == NULL) {
            sceVu0CopyMatrix(matrix, lw_matrix);
            return;
        }
        while (frame != NULL) {
            if (frame->changed) break;
            frame = frame->parent;
            if (frame == NULL) {
                sceVu0CopyMatrix(matrix, lw_matrix);
                return;
            }
        }
    }

    ClearChildFlag();
    GetLocalMatrix(local);
    if (parent == NULL) {
        sceVu0CopyMatrix(lw_matrix, local);
        sceVu0CopyMatrix(matrix, lw_matrix);
        changed = 0;
    } else {
        parent->GetLWMatrix(parent_matrix);
        float (*right)[4] = local;
        float (*left)[4] = parent_matrix;
        float (*out)[4] = lw_matrix;
        asm {
            lqc2 vf5, 0x0(right)
            lqc2 vf1, 0x0(left)
            lqc2 vf2, 0x10(left)
            lqc2 vf3, 0x20(left)
            lqc2 vf4, 0x30(left)
            vmulax.xyzw ACC, vf1, vf5x
            vmadday.xyzw ACC, vf2, vf5y
            vmaddaz.xyzw ACC, vf3, vf5z
            vmaddw.xyzw vf20, vf4, vf5w
            lqc2 vf6, 0x10(right)
            lqc2 vf7, 0x20(right)
            lqc2 vf8, 0x30(right)
            vmulax.xyzw ACC, vf1, vf6x
            vmadday.xyzw ACC, vf2, vf6y
            vmaddaz.xyzw ACC, vf3, vf6z
            vmaddw.xyzw vf21, vf4, vf6w
            vmulax.xyzw ACC, vf1, vf7x
            vmadday.xyzw ACC, vf2, vf7y
            vmaddaz.xyzw ACC, vf3, vf7z
            vmaddw.xyzw vf22, vf4, vf7w
            vmulax.xyzw ACC, vf1, vf8x
            vmadday.xyzw ACC, vf2, vf8y
            vmaddaz.xyzw ACC, vf3, vf8z
            vmaddw.xyzw vf23, vf4, vf8w
            sqc2 vf20, 0x0(out)
            sqc2 vf21, 0x10(out)
            sqc2 vf22, 0x20(out)
            sqc2 vf23, 0x30(out)
            sqc2 vf20, 0x0(matrix)
            sqc2 vf21, 0x10(matrix)
            sqc2 vf22, 0x20(matrix)
            sqc2 vf23, 0x30(matrix)
        }
        changed = 0;
    }
}
#else
INCLUDE_ASM("ps2/asm/pal/nonmatchings/mg_frame", GetLWMatrix__8mgCFrameFPA4_f);
#endif

#pragma global_optimizer off
void mgCFrame::GetLWMatrixTopBottom(float (*matrix)[4]) {
    sceVu0FMATRIX parent_matrix;
    sceVu0FMATRIX local;

    if (reference) {
        GetLWMatrix(matrix);
        return;
    }
    if (!changed) {
        if (parent == NULL) {
            sceVu0CopyMatrix(matrix, lw_matrix);
            return;
        }
        if (!parent->changed) {
            sceVu0CopyMatrix(matrix, lw_matrix);
            return;
        }
    }
    ClearChildFlag();
    GetLocalMatrix(local);
    if (parent == NULL) {
        sceVu0CopyMatrix(lw_matrix, local);
        sceVu0CopyMatrix(matrix, lw_matrix);
        changed = 0;
    } else {
        sceVu0CopyMatrix(parent_matrix, parent->lw_matrix);
        float (*right)[4];
        float (*left)[4];
        float (*out)[4];
        out = lw_matrix;
        left = parent_matrix;
        right = local;
        asm {
            lqc2 vf5, 0x0(right)
            lqc2 vf1, 0x0(left)
            lqc2 vf2, 0x10(left)
            lqc2 vf3, 0x20(left)
            lqc2 vf4, 0x30(left)
            vmulax.xyzw ACC, vf1, vf5x
            vmadday.xyzw ACC, vf2, vf5y
            vmaddaz.xyzw ACC, vf3, vf5z
            vmaddw.xyzw vf20, vf4, vf5w
            lqc2 vf6, 0x10(right)
            lqc2 vf7, 0x20(right)
            lqc2 vf8, 0x30(right)
            vmulax.xyzw ACC, vf1, vf6x
            vmadday.xyzw ACC, vf2, vf6y
            vmaddaz.xyzw ACC, vf3, vf6z
            vmaddw.xyzw vf21, vf4, vf6w
            vmulax.xyzw ACC, vf1, vf7x
            vmadday.xyzw ACC, vf2, vf7y
            vmaddaz.xyzw ACC, vf3, vf7z
            vmaddw.xyzw vf22, vf4, vf7w
            vmulax.xyzw ACC, vf1, vf8x
            vmadday.xyzw ACC, vf2, vf8y
            vmaddaz.xyzw ACC, vf3, vf8z
            vmaddw.xyzw vf23, vf4, vf8w
            sqc2 vf20, 0x0(out)
            sqc2 vf21, 0x10(out)
            sqc2 vf22, 0x20(out)
            sqc2 vf23, 0x30(out)
            sqc2 vf20, 0x0(matrix)
            sqc2 vf21, 0x10(matrix)
            sqc2 vf22, 0x20(matrix)
            sqc2 vf23, 0x30(matrix)
        }
        changed = 0;
    }
}
#pragma global_optimizer reset

void mgCFrame::GetInverseMatrix(float (*matrix)[4]) {
    sceVu0FMATRIX lw;
    sceVu0FVECTOR translation;
    float det;
    float inv_det;

    GetLWMatrix(lw);
    det = 0.0f;
    det += lw[0][0] * lw[1][1] * lw[2][2];
    det += lw[0][1] * lw[1][2] * lw[2][0];
    det += lw[0][2] * lw[1][0] * lw[2][1];
    det -= lw[0][0] * lw[1][2] * lw[2][1];
    det -= lw[0][1] * lw[1][0] * lw[2][2];
    det -= lw[0][2] * lw[1][1] * lw[2][0];
    sceVu0UnitMatrix(matrix);
    inv_det = 1.0f / det;

    matrix[0][0] = lw[1][1] * lw[2][2] - lw[1][2] * lw[2][1];
    matrix[1][0] = lw[1][2] * lw[2][0] - lw[1][0] * lw[2][2];
    matrix[2][0] = lw[1][0] * lw[2][1] - lw[1][1] * lw[2][0];
    matrix[0][1] = lw[2][1] * lw[0][2] - lw[2][2] * lw[0][1];
    matrix[1][1] = lw[2][2] * lw[0][0] - lw[2][0] * lw[0][2];
    matrix[2][1] = lw[2][0] * lw[0][1] - lw[2][1] * lw[0][0];
    matrix[0][2] = lw[0][1] * lw[1][2] - lw[0][2] * lw[1][1];
    matrix[1][2] = lw[0][2] * lw[1][0] - lw[0][0] * lw[1][2];
    matrix[2][2] = lw[0][0] * lw[1][1] - lw[0][1] * lw[1][0];
    sceVu0ScaleVector(matrix[0], matrix[0], inv_det);
    sceVu0ScaleVector(matrix[1], matrix[1], inv_det);
    sceVu0ScaleVector(matrix[2], matrix[2], inv_det);

    sceVu0ApplyMatrix(translation, matrix, lw[3]);
    sceVu0ScaleVectorXYZ(matrix[3], translation, -1.0f);
    matrix[3][3] = 1.0f;
}
void mgCFrame::SetTransMatrix(float (*matrix)[4]) {
    sceVu0CopyMatrix(trans_matrix, matrix);
    changed = 1;
}

static int StrCmp(char *left, char *right) {
    if (left == 0 || right == 0) {
        return 0;
    }
    s8 *endA = (s8 *)left;
    s8 *endB = (s8 *)right;
    s32 ch;
    s32 lengthA = 0;
    s32 lengthB = 0;
    while ((ch = *endA) != 0) {
        if ((s8)ch == '-' && endA[1] == '-') {
            break;
        }
        lengthA++;
        endA++;
    }
    while ((ch = *endB) != 0) {
        if ((s8)ch == '-' && endB[1] == '-') {
            break;
        }
        lengthB++;
        endB++;
    }
    if (lengthA != lengthB) {
        return 0;
    }
    s8 *pa = (s8 *)left;
    s8 *pb = (s8 *)right;
    for (s32 i = 0; i < lengthA; i++, pa++, pb++) {
        if (*pa != *pb) {
            return 0;
        }
    }
    return 1;
}

int mgFrameNameComp(char *left, char *right) {
    return StrCmp(left, right);
}

mgCFrame *mgCFrame::SearchFrame(char *name) {
    mgCFrame *found;
    mgCFrame *node;
    if (StrCmp(this->name, name) != 0) {
        return this;
    }
    for (node = child; node != 0; node = node->brother) {
        if ((found = node->SearchFrame(name)) != 0) {
            return found;
        }
    }
    return 0;
}

int mgCFrame::SearchFrameID(char *name) {
    if (frame_list == 0) {
        return -1;
    }
    s32 index = 0;
    s32 offset = 0;
    while (index < frame_num) {
        mgCFrame *entry = *(mgCFrame **)((u8 *)frame_list + offset);
        if (entry != 0 && StrCmp(entry->name, name) != 0) {
            return index;
        }
        offset += 4;
        index++;
    }
    return -1;
}

void mgCFrame::GetWorldPosition(float *out_position, float *local_position) {
    sceVu0FMATRIX lw;

    local_position[3] = 1.0f;
    GetLWMatrix(lw);
    sceVu0ApplyMatrix(out_position, lw, local_position);
}

void mgCFrame::GetWorldPosition0(float *out_position) {
    sceVu0FMATRIX lw;

    GetLWMatrix(lw);
    *(u_long128 *)out_position = *(u_long128 *)lw[3];
}

void mgCFrame::GetWorldDir(float *out_dir, float *local_dir) {
    sceVu0FMATRIX lw;
    float         w;

    w = local_dir[3];
    local_dir[3] = 0.0f;
    GetLWMatrix(lw);
    sceVu0ApplyMatrix(out_dir, lw, local_dir);
    local_dir[3] = w;
}
void mgCFrame::SetRotation(float *rot) {
    rot_type |= 1;
    mgCObject::SetRotation(rot);
}

void mgCFrame::SetRotation(float x, float y, float z) {
    float rotation[4];
    *(u_long128 *)rotation = *(u_long128 *)at_844;
    rotation[0] = x;
    rotation[1] = y;
    rotation[2] = z;

    SetRotation(rotation);
}

void mgCFrame::SetRotType(int type) {
    rot_type = type;
    if (type & MG_FRAME_ROT_LOCAL_ORIGIN) {
        rot_type |= MG_FRAME_ROT_APPLY;
    }
}
void mgCFrame::SetAttrParam(mgCFrameAttr &attr, int recurse, int mask) {
    mgCFrameAttr *dst = this->attr;
    if (dst != 0) {
        if (mask == 0) {
            dst->alpha_ref = attr.alpha_ref;
            dst->alpha_blend = attr.alpha_blend;
            dst->z_write = attr.z_write;
            dst->z_test = attr.z_test;
            dst->alpha_test = attr.alpha_test;
            dst->dest_alpha_test = attr.dest_alpha_test;
            dst->draw = attr.draw;
            dst->clip_enable = attr.clip_enable;
            dst->unk_20 = attr.unk_20;
            dst->unk_24 = attr.unk_24;
            dst->unk_28 = attr.unk_28;
            dst->program_option = attr.program_option;
            dst->fog = attr.fog;
            dst->unk_34 = attr.unk_34;
            dst->unk_38 = attr.unk_38;
            dst->unk_3c = attr.unk_3c;
            dst->program_mode = attr.program_mode;
            dst->obj_alpha = attr.obj_alpha;
            dst->no_cull = attr.no_cull;
            dst->ambient_boost = attr.ambient_boost;
            *(mgVec4 *)&dst->unk_50[0] = *(mgVec4 *)&attr.unk_50[0];
            dst->no_light = attr.no_light;
            *(mgVec4 *)dst->color = *(mgVec4 *)attr.color;
            dst->point_light = attr.point_light;
            dst->unk_84 = attr.unk_84;
            dst->billboard = attr.billboard;
            dst->depth_bias = attr.depth_bias;
        } else {
            if (mask & 0x1) {
                dst->draw = attr.draw;
            }
            if (mask & 0x2) {
                this->attr->alpha_ref = attr.alpha_ref;
            }
            if (mask & 0x4) {
                this->attr->alpha_blend = attr.alpha_blend;
            }
            if (mask & 0x8) {
                this->attr->z_write = attr.z_write;
            }
            if (mask & 0x10) {
                this->attr->z_test = attr.z_test;
            }
            if (mask & 0x20) {
                this->attr->clip_enable = attr.clip_enable;
            }
            if (mask & 0x40) {
                this->attr->unk_20 = attr.unk_20;
            }
            if (mask & 0x80) {
                this->attr->unk_24 = attr.unk_24;
            }
            if (mask & 0x100) {
                this->attr->unk_28 = attr.unk_28;
            }
            if (mask & 0x200) {
                this->attr->program_option = attr.program_option;
            }
            if (mask & 0x400) {
                this->attr->fog = attr.fog;
            }
            if (mask & 0x800) {
                this->attr->unk_34 = attr.unk_34;
            }
            if (mask & 0x1000) {
                this->attr->unk_38 = attr.unk_38;
            }
            if (mask & 0x2000) {
                this->attr->unk_3c = attr.unk_3c;
            }
            if (mask & 0x4000) {
                this->attr->program_mode = attr.program_mode;
            }
            if (mask & 0x8000) {
                this->attr->no_light = attr.no_light;
            }
            if (mask & 0x10000) {
                *(u_long128 *)this->attr->color = *(u_long128 *)attr.color;
            }
            if (mask & 0x20000) {
                this->attr->point_light = attr.point_light;
            }
            if (mask & 0x40000) {
                this->attr->obj_alpha = attr.obj_alpha;
            }
            if (mask & 0x80000) {
                this->attr->billboard = attr.billboard;
            }
            if (mask & 0x100000) {
                this->attr->no_cull = attr.no_cull;
            }
            if (mask & 0x200000) {
                this->attr->depth_bias = attr.depth_bias;
            }
            if (mask & 0x800000) {
                this->attr->ambient_boost = attr.ambient_boost;
            }
            if (mask & 0x400000) {
                this->attr->dest_alpha_test = attr.dest_alpha_test;
            }
        }
    }
    if (recurse == 0) {
        return;
    }
    mgCFrame *frame = child;
    if (frame != 0) {
        do {
            frame->SetAttrParam(attr, 1, mask);
            frame = frame->brother;
        } while (frame != 0);
    }
}
void mgCFrame::SetAttrParamObjAlpha(float alpha, int recurse) {
    if (attr != 0) {
        this->attr->obj_alpha = alpha;
    }
    if (recurse == 0)
        return;
    mgCFrame *frame = child;
    if (frame != 0) {
        do {
            frame->SetAttrParamObjAlpha(alpha, 1);
            frame = frame->brother;
        } while (frame != 0);
    }
}
void mgCFrame::SetAttrParamDraw(int value, int recurse) {
    mgCFrameAttr *attr;
    mgCFrame *node;

    attr = this->attr;
    if (attr != NULL) {
        this->attr->draw = value;
    }
    if (recurse == 0) {
        return;
    }
    for (node = child; node != NULL; node = node->brother) {
        node->SetAttrParamDraw(value, 1);
    }
}

INCLUDE_ASM("ps2/asm/pal/nonmatchings/mg_frame", Draw__8mgCFrameFPUi);

#pragma global_optimizer off
INCLUDE_ASM("ps2/asm/pal/nonmatchings/mg_frame", GetDrawRect__8mgCFrameFP9mgVu0FBOXP14mgCDrawManager);
#pragma global_optimizer reset

mgCFrame &mgCFrame::operator=(mgCFrame &other) {
    memcpy(this, &other, sizeof(mgCFrame));
    parent = child = brother = NULL;
    changed = 1;
    reference = 0;

    use_srt = 0;
    if (position[0] != 0.0f || position[1] != 0.0f || position[2] != 0.0f) {
        use_srt = 1;
    }
    if (rotation[0] != 0.0f || rotation[1] != 0.0f || rotation[2] != 0.0f) {
        use_srt = 1;
    }
    if (scale[0] != 1.0f || scale[1] != 1.0f || scale[2] != 1.0f) {
        use_srt = 1;
    }
    return *this;
}
int mgCFrame::Draw() {
    return Draw((u_int *)0);
}
void mgCObject::ChangeParam() {
    changed = 1;
}
void mgCObject::UseParam() {
    changed = 1;
}
int mgCObject::DrawDirect() {
    return 0;
}
int mgCObject::Draw() {
    return 0;
}

INCLUDE_RODATA("ps2/asm/pal/nonmatchings/mg_frame", at_307__DATA);

INCLUDE_RODATA("ps2/asm/pal/nonmatchings/mg_frame", __vt__8mgCFrame__DATA);
INCLUDE_RODATA("ps2/asm/pal/nonmatchings/mg_frame", __vt__12mgCFrameBase__DATA);
INCLUDE_RODATA("ps2/asm/pal/nonmatchings/mg_frame", __vt__9mgCObject__DATA);

INCLUDE_BSS(at_324, 0x10);
INCLUDE_BSS(at_341, 0x10);
INCLUDE_BSS(at_844, 0x10);
INCLUDE_BSS(at_1118, 0x10);
INCLUDE_BSS(at_1119, 0x10);
