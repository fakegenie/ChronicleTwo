#pragma once

#include "common.h"

struct mgVu0FBOX;
struct RS_STACKDATA;

enum SpherePoly3Contact {
    SPHERE_POLY3_NONE   = 0,
    SPHERE_POLY3_FACE   = 1,
    SPHERE_POLY3_VERTEX = 2,
    SPHERE_POLY3_EDGE   = 3,
};

int IntersectionPipeYPoly3(float *pipe, float (*poly)[4], float *normal, float (*hits)[4]);

int IntersectionPipePoly3(float *pipe, float *dir, float (*poly)[4], float *normal, float (*hits)[4]);

int IntersectionSpherePoly3(float *sphere, float (*poly)[4], float *normal, float *push);

int IntersectionBox(float *from, float *to, mgVu0FBOX *box, float (*hits)[4]);

int IntersectionBox(float *from, float *to, mgVu0FBOX *box, float (*matrix)[4], float (*hits)[4]);

int mt_test(RS_STACKDATA *args, int count);
