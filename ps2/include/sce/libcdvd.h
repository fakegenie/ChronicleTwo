#pragma once

#include "types.h"

struct sceCdlFILE {
    u_int lsn;
    u_int size;
    char name[16];
    u_char date[8];
};

struct sceCdRMode {
    u_char trycount;
    u_char spindlctrl;
    u_char datapattern;
    u_char pad;
};

extern "C" {
int sceCdInit(int mode);
int sceCdSeek(u_int lsn);
int sceCdMmode(int media);
int sceCdSearchFile(sceCdlFILE *file, const char *name);
int sceCdRead(u_int lsn, u_int sectors, void *buffer, sceCdRMode *mode);
int sceCdSync(int mode);
int sceCdGetError(void);
int sceCdBreak(void);
}
