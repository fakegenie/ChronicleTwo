#pragma once

#define scePadStateDiscon 0
#define scePadStateFindPad 1
#define scePadStateFindCTP1 2
#define scePadStateExecCmd 5
#define scePadStateStable 6
#define scePadStateError 7

#define InfoModeCurID 1
#define InfoModeCurExID 2

#ifdef __cplusplus
extern "C" {
#endif

int scePadInit(int mode);

int scePadEnd(void);

int scePadPortOpen(int port, int slot, unsigned char *buffer);

int scePadPortClose(int port, int slot);

int scePadRead(int port, int slot, unsigned char *data);

int scePadGetState(int port, int slot);

int scePadInfoMode(int port, int slot, int info, int index);

int scePadSetMainMode(int port, int slot, int mode, int lock);

int scePadInfoAct(int port, int slot, int actuator, int command);

int scePadSetActAlign(int port, int slot, unsigned char *alignment);

int scePadSetActDirect(int port, int slot, unsigned char *values);

#ifdef __cplusplus
}
#endif
