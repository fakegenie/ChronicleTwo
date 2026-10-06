#pragma once

#define MC_WAIT 0
#define MC_NOWAIT 1

#define sceMcIniSucceed 0
#define sceMcIniErrKernel (-101)
#define sceMcIniOldMcserv (-120)
#define sceMcIniOldMcman (-121)

#define sceMcResSucceed 0
#define sceMcResChangedCard (-1)
#define sceMcResNoFormat (-2)
#define sceMcResFullDevice (-3)
#define sceMcResNoEntry (-4)
#define sceMcResDeniedPermit (-5)
#define sceMcResFailReplace (-8)
#define sceMcResFailDetect (-12)

#define sceMcTypeNoCard 0
#define sceMcTypePS1 1
#define sceMcTypePS2 2
#define sceMcTypePDA 3

#include "common.h"

struct sceMcColor {
    u_int r;
    u_int g;
    u_int b;
    u_int a;
};

STATIC_ASSERT(sizeof(sceMcColor) == 0x10);

typedef float sceMcColorF[4];

typedef float sceMcVu0FVECTOR[4];

struct sceMcIconSys {
    char head[4];
    u_short unknown1;
    u_short nl_offset;
    u_int unknown2;
    u_int trans_rate;
    sceMcColor bg_color[4];
    sceMcVu0FVECTOR light_dir[3];
    sceMcColorF light_color[3];
    sceMcColorF ambient;
    u_char title_name[68];
    char fname_view[64];
    char fname_copy[64];
    char fname_del[64];
    u_char reserve[512];
};

STATIC_ASSERT(sizeof(sceMcIconSys) == 0x3C4);

#ifdef __cplusplus
extern "C" {
#endif

int sceMcInit(void);

int sceMcEnd(void);

int sceMcEnd(void);

int sceMcSync(int mode, int *cmd, int *result);

int sceMcOpen(int port, int slot, const unsigned char *name, int flag);

int sceMcClose(int fd);

int sceMcRead(int fd, void *buffer, int size);

int sceMcWrite(int fd, void *buffer, int size);

int sceMcFlush(int fd);

int sceMcChdir(int port, int slot, const char *name, char *current);

int sceMcRename(int port, int slot, char *old_name, char *new_name);

int sceMcMkdir(int port, int slot, const unsigned char *name);

int sceMcDelete(int port, int slot, char *name);

struct MC_DIR_ENTRY;
int sceMcGetDir(int port, int slot, const char *name, int mode, int count, MC_DIR_ENTRY *table);

int sceMcGetInfo(int port, int slot, int *type, int *free_size, int *formatted);

int sceMcFormat(int port, int slot);

int sceMcUnformat(int port, int slot);
#ifdef __cplusplus
}
#endif
