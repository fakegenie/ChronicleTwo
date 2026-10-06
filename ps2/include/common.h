#ifndef COMMON_H
#define COMMON_H

#include "types.h"

// Every source can mark a function or datum that is not decompiled yet.
#include "include_asm.h"

#define STATIC_ASSERT(expr) typedef char _static_assert_##__COUNTER__[(expr) ? 1 : -1]

#ifdef __cplusplus
extern "C" int fptosi(float value);
extern "C" unsigned int fptoui(float value);
#endif

#endif
