#pragma once

#include "common.h"

struct mgVu0FBOX;

enum mgInterpolateMode {
    MG_INTERPOLATE_STEP = 0,
    MG_INTERPOLATE_FRACTION = 1,
};

enum mgPointPoly3Result {
    MG_POINT_POLY3_OUTSIDE = 0,
    MG_POINT_POLY3_INSIDE = 1,
    MG_POINT_POLY3_EDGE_01 = 2,
    MG_POINT_POLY3_EDGE_12 = 3,
    MG_POINT_POLY3_EDGE_20 = 4,
};

enum mgVu0Status {
    MG_VU0_STATUS_SIGN_STICKY = 0x80,
};

extern float sin_table_num;

extern float sin_table_unit_1;

extern float SinTable[1024];

void mgFotI4(int *out, float *in);

void mgCreateBox8(float (*corners)[4], float *max, float *min);

void mgZeroVector(float *vector);

void mgZeroVectorW(float *vector);

int mgClipBoxVertex(float *point, float *max, float *min);

int mgClipBox(float *max0, float *min0, float *max1, float *min1);

int mgClipBoxW(float *max0, float *min0, float *max1, float *min1);

int mgClipInBox(float *max0, float *min0, float *max1, float *min1);

int mgClipInBoxW(float *max0, float *min0, float *max1, float *min1);

void mgAddVector(float *vector, float *add);

void mgSubVector(float *vector, float *sub);

void mgNormalizeVector(float *out, float *in, float length);

void mgVectorMin(float *min, float *a, float *b);

void mgVectorMin(float *min, float *a, float *b, float *c, float *d);

void mgVectorMaxMin(float *max, float *min, float *a, float *b);

void mgVectorMaxMin(float *max, float *min, float *a, float *b, float *c);

void mgVectorMaxMin(float *max, float *min, float *a, float *b, float *c, float *d);

void mgBoxMaxMin(mgVu0FBOX *box, mgVu0FBOX *other);

void mgPlaneNormal(float *normal, float *v0, float *v1, float *v2);

float mgDistPlanePoint(float *normal, float *on_plane, float *point);

float mgDistLinePoint(float *point, float *start, float *end, float *nearest);

float mgReflectionPlane(float *normal, float *on_plane, float *point, float *reflection);

int mgIntersectionSphereLine0(float radius, float *from, float *to, float (*hits)[4]);

int mgIntersectionSphereLine(float *sphere, float *from, float *to, float (*hits)[4]);

int mgIntersectionPoint_line_poly3(float *from, float *to, float *v0, float *v1, float *v2, float *normal, float *hit);

int mgCheckPointPoly3_XYZ(float *point, float *v0, float *v1, float *v2, float *normal);

int mgCheckPointPoly3_XZ(float *point, float *v0, float *v1, float *v2);

float mgDistVector(float *vector);

float mgDistVectorXZ(float *vector);

float mgDistVector2(float *vector);

float mgDistVector(float *a, float *b);

float mgDistVectorXZ(float *a, float *b);

float mgDistVector2(float *a, float *b);

float mgDistVectorXZ2(float *a, float *b);

void mgUnitMatrix(float (*matrix)[4]);

void mgZeroMatrix(float (*matrix)[4]);

void mgMulMatrix(float (*product)[4], float (*left_matrix)[4], float (*right_matrix)[4]);

void mgInversMatrix(float (*inverse)[4], float (*matrix)[4]);

void mgRotMatrixX(float (*matrix)[4], float angle_x);

void mgRotMatrixY(float (*matrix)[4], float angle_y);

void mgRotMatrixZ(float (*matrix)[4], float angle_z);

void mgRotMatrixXYZ(float (*matrix)[4], float *rotation);

void mgCreateMatrixPY(float (*matrix)[4], float *position, float angle_y);

void mgLookAtMatrixZ(float (*matrix)[4], float *direction);

void mgShadowMatrix(float (*matrix)[4], float *light_direction, float *on_plane, float *plane_normal);

void mgApplyMatrixN(float (*out)[4], float (*matrix)[4], float (*in)[4], int count);

void mgApplyMatrixN_MaxMin(float (*out)[4], float (*matrix)[4], float (*in)[4], int count, float *max, float *min);

void mgVectorMinMaxN(float *max, float *min, float (*vectors)[4], int count);

void mgApplyMatrix(float *max, float *min, float (*matrix)[4], float *box_max, float *box_min);

void mgVectorInterpolate(float *out, float *from, float *to, float step, int mode);

float mgAngleInterpolate(float from, float to, float step, int mode);

int mgAngleCmp(float a, float b, float tolerance);

float mgAngleLimit(float angle);

float mgRnd();

float mgNRnd();

void mgCreateSinTable();

float mgSinf(float angle);

float mgCosf(float angle);
