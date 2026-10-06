#pragma once

#include "common.h"

typedef struct {
    u_int DIR : 1;
    u_int pad1 : 1;
    u_int MOD : 2;
    u_int ASP : 2;
    u_int TTE : 1;
    u_int TIE : 1;
    u_int STR : 1;
    u_int pad9 : 7;
    u_int TAG : 16;
} sceDmaChcr;

typedef struct {
    sceDmaChcr chcr;
    u_int reserved_04[3];
    u_int madr;
    u_int reserved_14[3];
    u_int qwc;
    u_int reserved_24[3];
    u_int tadr;
    u_int reserved_34[3];
    u_int asr0;
    u_int reserved_44[3];
    u_int asr1;
    u_int reserved_54[11];
    u_int sadr;
    u_int reserved_84[3];
} sceDmaChan;

STATIC_ASSERT(sizeof(sceDmaChcr) == 4);
STATIC_ASSERT(sizeof(sceDmaChan) == 0x90);

typedef struct sceDmaEnv {
    u_char sts;
    u_char std;
    u_char mbs;
    u_char mbd;
    u_short unk_04;
    u_short notify;
    u_short unk_08;
    u_short unk_0A;
    u_int unk_0C;
    void *mem;
} sceDmaEnv;

STATIC_ASSERT(sizeof(sceDmaEnv) == 0x14);

extern "C" {

sceDmaChan *sceDmaGetChan(int channel);
int sceDmaSend(sceDmaChan *chan, void *data);
int sceDmaSync(sceDmaChan *chan, int mode, int timeout);

int sceDmaReset(int mode);

int sceDmaGetEnv(sceDmaEnv *env);

int sceDmaPutEnv(sceDmaEnv *env);
}
