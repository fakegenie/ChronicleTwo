#pragma once

#include "common.h"

class mgCTexture;

void DepthOfField(int levels, float *depths, mgCTexture *work_texture, float strength);

void LensFlare(int *screen, float *color, int bank, char *texture_a, char *texture_b);
