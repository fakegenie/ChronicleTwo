#pragma once

#include "csl.h"

#ifdef __cplusplus
extern "C" {
#endif

int sceMSIn_Init(sceCslCtx *ctx);

int sceMSIn_PutMsg(sceCslCtx *ctx, unsigned int port, unsigned int msg);

int sceMSIn_PutHsMsg(sceCslCtx *ctx, unsigned int port, unsigned char *msg);

#ifdef __cplusplus
}
#endif
