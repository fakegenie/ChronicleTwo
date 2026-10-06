#include "common.h"
#include "mg_drawprim.hpp"
#include "mg_texture.hpp"
#include "mg_frame.hpp"
#include "mg_drawenv.hpp"
#include "mglib.hpp"
#include "collision.hpp"

#include <cstring>
#include <libvu0.h>

#include "mg_dataset.hpp"
#include "mg_math.hpp"
#include "mg_memory.hpp"

int CCollision::InsidePoint(float *point) {
    return mgClipBoxVertex(point, bbox.max, bbox.min) != 0;
}

struct CollisionQuad {
    float v[4];
};
struct CollisionTri {
    CollisionQuad q[5];
};
static inline u_int Align16Blocks(u_int n) {
    if (n & 0xF) {
        return (n >> 4) + 1;
    }
    return n >> 4;
}
void CCollisionMDT::Copy(CCollisionMDT &dest, mgCMemory *memory) {
    int i;
    int offset;
    CollisionTri *src;
    CollisionTri *dst;
    dest.bbox = bbox;
    dest.poly_count = poly_count;
    if (dest.poly_count <= 0) {
        dest.poly = NULL;
        return;
    }
    if (memory != NULL) {
        dest.poly = (CCPoly *)operator new[](
            dest.poly_count * 0x50,
            (u_long128 *)memory->Alloc(Align16Blocks(dest.poly_count * 0x50) + 2));
        i = 0;
        if (dest.poly != NULL) {
            offset = 0;
            for (; i < dest.poly_count; i++) {
                src = (CollisionTri *)((u_char *)poly + offset);
                dst = (CollisionTri *)((u_char *)dest.poly + offset);
                offset += 0x50;
                dst->q[0] = src->q[0];
                dst->q[1] = src->q[1];
                dst->q[2] = src->q[2];
                dst->q[3] = src->q[3];
                dst->q[4] = src->q[4];
            }
        }
    } else {
        dest.poly = poly;
    }
}

void CCollisionMDT::CreateBBox() {
    float polygon_max[4];
    float polygon_min[4];
    int index;
    CCPoly *polygon;

    bbox.min[0] = 0.0f;
    bbox.max[0] = 0.0f;
    bbox.min[1] = 0.0f;
    bbox.max[1] = 0.0f;
    bbox.min[2] = 0.0f;
    bbox.max[2] = 0.0f;
    bbox.min[3] = 1.0f;
    bbox.max[3] = 1.0f;

    polygon = poly;
    if (polygon == NULL || poly_count <= 0) {
        return;
    }
    mgVectorMaxMin(bbox.max, bbox.min, polygon->vertex[0], polygon->vertex[1], polygon->vertex[2]);

    for (index = 0; index < poly_count; index++, polygon++) {
        mgVectorMaxMin(polygon_max, polygon_min, polygon->vertex[0], polygon->vertex[1], polygon->vertex[2]);
        mgVectorMaxMin(bbox.max, bbox.min, bbox.max, bbox.min, polygon_max, polygon_min);
    }
}

int CCollisionMDT::GetMaxY(float *position) {
    float from[4];
    float to[4];
    float hit[4];
    int i;
    int found;
    CCPoly *cursor;
    float max_y;

    cursor = poly;
    if (cursor == 0) {
        return 0;
    }

    if (!(position[0] <= bbox.max[0])) {
        return 0;
    }

    if (!(position[2] <= bbox.max[2])) {
        return 0;
    }

    if (position[0] < bbox.min[0]) {
        return 0;
    }

    if (position[2] < bbox.min[2]) {
        return 0;
    }

    from[0] = to[0] = position[0];
    from[2] = to[2] = position[2];
    from[1] = 0.0f;
    found = 0;
    max_y = -1e8f;
    to[1] = 1.0f;
    for (i = 0; i < poly_count; i++, cursor++) {
        if (mgIntersectionPoint_line_poly3(from, to, cursor->vertex[0], cursor->vertex[1], cursor->vertex[2], cursor->normal, hit) != 0) {
            found = 1;
            if (max_y < hit[1]) {
                max_y = hit[1];
            }
        }
    }

    position[1] = max_y;
    return found;
}

#ifdef NONMATCHING
int CCollisionMDT::PickUpNearPoly(CCPoly *out, const mgVu0FBOX &box, int max) {
    if (poly == NULL || !mgClipBox((float *)box.max, (float *)box.min, bbox.max, bbox.min)) {
        return 0;
    }

    int count = 0;
    for (int i = 0; i < poly_count; i++) {
        sceVu0FVECTOR poly_max;
        sceVu0FVECTOR poly_min;
        mgVectorMaxMin(poly_max, poly_min, poly[i].vertex[0], poly[i].vertex[1], poly[i].vertex[2]);
        if (mgClipBox((float *)box.max, (float *)box.min, poly_max, poly_min)) {
            out[count++] = poly[i];
            if (count >= max) break;
        }
    }
    return count;
}
#else
INCLUDE_ASM("ps2/asm/pal/nonmatchings/collision", PickUpNearPoly__13CCollisionMDTFP6CCPolyRC9mgVu0FBOXi);
#endif

int CCollision::Intersection(float *from, float *to, float *hit) {
    return 0;
}

int CColFrame::InsidePoint(float *point) {
    sceVu0FVECTOR local_point;
    sceVu0FMATRIX lw_matrix;
    sceVu0FMATRIX inverse_matrix;

    if (collision == 0) {
        return 0;
    }

    GetLWMatrix(lw_matrix);
    GetInverseMatrix(inverse_matrix);
    point[3] = 1.0f;
    sceVu0ApplyMatrix(local_point, inverse_matrix, point);
    return collision->InsidePoint(local_point);
}

#pragma force_active on
INCLUDE_ASM("ps2/asm/pal/nonmatchings/collision", pre_trance_normal__FPA4_f);

INCLUDE_ASM("ps2/asm/pal/nonmatchings/collision", trance_normal__FPfPfPfPf);

#pragma force_active reset
#ifdef NONMATCHING
void pre_trance_normal(float (*matrix)[4]);
void trance_normal(float *v0, float *v1, float *v2, float *normal);

int CColFrame::PickUpNearPoly(CCPoly *out, const mgVu0FBOX &box, int max) {
    if (flags == COL_FRAME_FLAG_NO_CHILDREN) {
        return 0;
    }
    int count = 0;
    if (collision != NULL && (flags & COL_FRAME_FLAG_SELF)) {
        sceVu0FMATRIX world;
        sceVu0FMATRIX inverse;
        GetLWMatrix(world);
        GetInverseMatrix(inverse);
        sceVu0FVECTOR corners[8];
        for (int i = 0; i < 8; i++) {
            corners[i][0] = (i & 1) ? box.max[0] : box.min[0];
            corners[i][1] = (i & 2) ? box.max[1] : box.min[1];
            corners[i][2] = (i & 4) ? box.max[2] : box.min[2];
            corners[i][3] = 1.0f;
        }
        sceVu0FVECTOR transformed[8];
        mgApplyMatrixN(transformed, inverse, corners, 8);
        mgVu0FBOX local_box;
        sceVu0FVECTOR max0, min0, max1, min1;
        mgVectorMaxMin(max0, min0, transformed[0], transformed[1], transformed[2], transformed[3]);
        mgVectorMaxMin(max1, min1, transformed[4], transformed[5], transformed[6], transformed[7]);
        mgVectorMaxMin(local_box.max, local_box.min, max0, max1, min0, min1);
        count = collision->PickUpNearPoly(out, local_box, max);
        pre_trance_normal(world);
        for (int i = 0; i < count; i++) {
            trance_normal(out[i].vertex[0], out[i].vertex[1], out[i].vertex[2], out[i].normal);
        }
    }
    int rest = max - count;
    if (rest <= 0) {
        return count;
    }
    if ((flags & COL_FRAME_FLAG_NO_CHILDREN) == 0) {
        CColFrame *node = (CColFrame *)child;
        while (node != NULL) {
            if ((flags & COL_FRAME_FLAG_UNK_4) == 0) {
                int added = node->PickUpNearPoly(out + count, box, rest);
                count += added;
                rest -= added;
                if (rest <= 0) {
                    break;
                }
            }
            node = (CColFrame *)node->brother;
        }
    }
    return count;
}
#else
INCLUDE_ASM("ps2/asm/pal/nonmatchings/collision", PickUpNearPoly__9CColFrameFP6CCPolyRC9mgVu0FBOXi);
#endif

int CCollision::PickUpNearPoly(CCPoly *poly, const mgVu0FBOX &box, int max) {
    return 0;
}

int CColFrame::GetWorldBBox(mgVu0FBOX *box) {
    mgVu0FBOX *result = box;
    mgVu0FBOX world_box;
    float matrix[4][4];
    mgVu0FBOX child_box;
    int found = 0;
    mgCFrame *node = this;
    if (collision != NULL && bound != NULL) {
        found = 1;
        GetLWMatrix(matrix);
        mgApplyMatrix(world_box.max, world_box.min, matrix, bound->max, bound->min);
    }
    for (node = node->child; node != NULL; node = node->brother) {
        if (node->GetWorldBBox(&child_box) != 0) {
            if (found == 0) {
                world_box = child_box;
            } else {
                mgVectorMaxMin(world_box.max, world_box.min, world_box.max, world_box.min, child_box.max,
                               child_box.min);
            }
            found = 1;
        }
    }
    *result = world_box;
    return found;
}

#ifdef NONMATCHING
CColFrame *LoadCollisionFile(MDS_HEADER *header, mgCMemory *memory) {
    sceVu0FMATRIX  matrix;
    sceVu0FVECTOR  max;
    sceVu0FVECTOR  min;
    u_int          i;
    int offset;
    MDTOBJ_HEADER *object;
    CColFrame     *frame;
    MDS_HEADER *base = header;
    CColFrame     *frames;
    int            row;
    int            column;

    header = (MDS_HEADER *)((u_char *)header + sizeof(MDS_HEADER));
    if (base->object_num == 0) {
        return 0;
    }

    frames = new ((u_long128 *)memory->Alloc(Align16Blocks(base->object_num * sizeof(CColFrame)) + 2)) CColFrame[base->object_num];

    offset = 0;
    for (i = 0; i < base->object_num; offset += sizeof(CColFrame), i++) {
        object = (MDTOBJ_HEADER *)header;
        header = (MDS_HEADER *)((u_char *)header + sizeof(MDTOBJ_HEADER));
        frame = (CColFrame *)((u_char *)frames + offset);
        frame->Initialize();

        for (column = 0; column < 4; column++) {
            for (row = 0; row < 4; row++) {
                matrix[row][column] = object->matrix[row][column];
            }
        }

        frame->SetName(object->name);
        frame->SetTransMatrix(matrix);

        if (object->parent < 0) {
            frame->SetParent(0);
        } else {
            frame->SetParent(&frames[object->parent]);
        }

        if (object->mdt_ofs != 0) {
            u_int *model = (u_int *)((u_char *)base + object->mdt_ofs);
            mgZeroVector(max);
            mgZeroVector(min);

            frame->collision = CreateCollisionMDT(model, memory);
            if (frame->collision != 0) {
                *(u_long128 *)max = *(u_long128 *)frame->collision->bbox.max;
                *(u_long128 *)min = *(u_long128 *)frame->collision->bbox.min;
            }

            frame->bound = new ((u_long128 *)memory->Alloc(sizeof(mgCFrame::BoundInfo) / 16 + 2)) mgCFrame::BoundInfo;
            frame->SetBBox(max, min);
        }
    }

    return frames;
}
#else
INCLUDE_ASM("ps2/asm/pal/nonmatchings/collision", LoadCollisionFile__FP10MDS_HEADERP9mgCMemory);
#endif

void CColFrame::Initialize() {
    flags = COL_FRAME_FLAG_SELF;
    collision = 0;
    mgCFrame::Initialize();
}

CColFrame::CColFrame() {
    Initialize();
}

#ifdef NONMATCHING
CCollisionMDT *CreateCollisionMDT(u_int *model, mgCMemory *memory) {
    MDT_MATERIAL_ *material;
    CCollisionMDT *collision;
    MDT_MATERIAL_ *materials;
    int           *words;
    int            j;
    int            index_count;
    int polygon_no;
    int            prim_num;
    MDT_HEADER    *header;
    FACES_ID      *prim;
    sceVu0FVECTOR *vertices;
    int            i;
    int            poly_count;
    int            material_no;
    FACES_ID      *first_prim;
    CCPoly        *poly;
    CCPoly        *polys;
    int           *index;
    MDT_FACES     *faces;

    collision = new ((u_long128 *)memory->Alloc(sizeof(CCollisionMDT) / 16 + 2)) CCollisionMDT;

    header = (MDT_HEADER *)model;
    vertices = (sceVu0FVECTOR *)((char *)model + header->vertex_ofs);
    materials = (MDT_MATERIAL_ *)((char *)model + header->material_ofs);
    faces = (MDT_FACES *)((char *)model + header->faces_ofs);
    prim_num = faces->prim_num;
    first_prim = (FACES_ID *)(faces + 1);

    poly_count = 0;
    words = (int *)first_prim;
    for (i = 0; i < prim_num; i++) {
        int type = *words++;
        if ((type & 7) == 4) {
            return 0;
        }
        if (type & 0x100) {
            return 0;
        }
        int face_num = *words++;
        poly_count += face_num / 3;
        words++;
        words += face_num;
    }

    polys = (CCPoly *)memory->Alloc(poly_count * sizeof(CCPoly) / 16);
    if (polys == 0) {
        return 0;
    }

    polygon_no = 0;
    words = (int *)first_prim;
    for (i = 0; i < prim_num; i++) {
        index_count = words[1];
        words += 2;
        material_no = *words++;
        index = words;

        for (j = 0; j < index_count; j += 3, index += 3) {
            poly = &polys[polygon_no++];
            *(u_long128 *)poly->vertex[0] = *(u_long128 *)vertices[index[0]];
            *(u_long128 *)poly->vertex[1] = *(u_long128 *)vertices[index[1]];
            *(u_long128 *)poly->vertex[2] = *(u_long128 *)vertices[index[2]];

            if (material_no >= 0 && materials != 0) {
                material = &materials[material_no];
                poly->ground_kind = material->diffuse[0] * 0.7f + 0.01f;
                poly->foot_sound = material->diffuse[1] * 0.7f + 0.01f;
                poly->area_kind = material->diffuse[2] * 0.7f + 0.01f;
                poly->ignore_mask = 1.0f - material->diffuse[3];
            } else {
                memset(&poly->ground_kind, 0, 0x10);
            }

            mgPlaneNormal(poly->normal, poly->vertex[0], poly->vertex[1], poly->vertex[2]);
        }

        words = index;
    }

    collision->poly = polys;
    collision->poly_count = poly_count;
    collision->CreateBBox();
    return collision;
}
#else
INCLUDE_ASM("ps2/asm/pal/nonmatchings/collision", CreateCollisionMDT__FPUiP9mgCMemory);
#endif

void CCollisionMDT::Initialize() {
    CCollision::Initialize();
    poly = 0;
    poly_count = 0;
}

void CCollision::Copy(CCollision &dest, mgCMemory *memory) {
    dest.bbox = bbox;
}

INCLUDE_RODATA("ps2/asm/pal/nonmatchings/collision", __vt__9CColFrame__DATA);
INCLUDE_RODATA("ps2/asm/pal/nonmatchings/collision", __vt__13CCollisionMDT__DATA);
INCLUDE_RODATA("ps2/asm/pal/nonmatchings/collision", __vt__10CCollision__DATA);
