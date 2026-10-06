#pragma once

#define SCE_RDONLY 0x0001
#define SCE_WRONLY 0x0002
#define SCE_CREAT 0x0200
#define SCE_TRUNC 0x0400
#define SCE_NOWAIT 0x8000

#define SCE_SEEK_SET 0
#define SCE_SEEK_CUR 1
#define SCE_SEEK_END 2

#define SCE_FS_EXECUTING 0x1

struct sce_stat {
    unsigned int  st_mode;
    unsigned int  st_attr;
    unsigned int  st_size;
    unsigned char st_ctime[8];
    unsigned char st_atime[8];
    unsigned char st_mtime[8];
    unsigned int  st_hisize;
    unsigned int  st_private[6];
};

extern "C" {
void sceFsReset(void);
int sceOpen(const char *name, int flags, ...);
int sceClose(int fd);
int sceLseek(int fd, int offset, int whence);
int sceRead(int fd, void *buffer, int size);
int sceWrite(int fd, void *buffer, int size);
int sceIoctl(int fd, int request, void *argument);
int sceGetstat(const char *name, struct sce_stat *stat);
}
