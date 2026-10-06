#pragma once

#include "types.h"

struct sceIpuDmaEnv {
    u_int d4madr;
    u_int d4tadr;
    u_int d4qwc;
    u_int d4chcr;
    u_int d3madr;
    u_int d3qwc;
    u_int d3chcr;
    u_int ipubp;
    u_int ipuctrl;
};

struct sceIpuRGB32 {
    u_int c[16 * 16];
};
