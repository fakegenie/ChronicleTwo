#pragma once

#include "common.h"

enum FILE_DEV {
    FILE_DEV_DEFAULT = -1,
    FILE_DEV_HOST = 0,
    FILE_DEV_CDROM = 1,
    FILE_DEV_NET = 2,
    FILE_DEV_HDD = 3,
};

enum LOAD_FILE_MODE {
    LOAD_FILE_READ = 0,
    LOAD_FILE_SIZE = 1,
    LOAD_FILE_OPEN = 2,
};

enum FILE_CACHE_TYPE {
    FILE_CACHE_NONE = 0,
    FILE_CACHE_DOWN = 1,
    FILE_CACHE_UP = 2,
};

struct DATA_HEADER {
    union {
        int   name_offset;
        char *name;
    };
    int size;
    int sector;
};
STATIC_ASSERT(sizeof(DATA_HEADER) == 0xC);

struct BG_READ_INFO {
    int        busy;
    int        dev;
    int        issued;
    int        done;
    char       name[256];
    u_long128 *buffer;
    int        size;
    union {
        int sector;
        int fd;
    };
    int sectors;
};
STATIC_ASSERT(sizeof(BG_READ_INFO) == 0x120);

struct FILE_CACHE {
    u_long128 *address;
    int        size;
    int        ref_count;
    int        unk_0c;
    char       name[48];
};
STATIC_ASSERT(sizeof(FILE_CACHE) == 0x40);

struct PACK_ENTRY {
    char name[64];
    int  offset;
    int  size;
    int  next;
};

int size_to_sector(int size);

int GetMainFileDev();

int ChangeHddFile();

int ChangeDefaultFile();

void SetIoErrCallBack(int (*callback)(int));

void SetCurrentDir(char *dir);

void GetCurrentDir(char *out_dir);

void ChangeDir(char *dir);

void InitReadBG();

int LoadFileBG(char *name, u_long128 *buffer, int *out_size);

BG_READ_INFO *GetReadBGFile(char *name);

BG_READ_INFO *GetReadBGFile(int index);

void StartReadBG();

void ReadBG();

int ReadBGSync();

void BreakReadBG();

void InitCDFile();

int LoadFile(char *path, void *buffer, int *out_size);

int LoadFile2(char *path, void *buffer, int *out_size, int mode);

void InitFileCache(u_long128 *address, int type);

void DeleteFileCache();

int LoadFileCacheBG(char *path);

u_long128 *SearchFileCache(char *path, int *out_size);

int WriteFile(char *path, void *buffer, int size);

u_int *GetPackFile(u_int *pack, char *name, int *out_size);

u_int *GetPackFile(u_int *pack, int index, char **out_name, int *out_size);

int GetPackFileExt(u_int *pack, char *extension, u_int **files, int max_files, int *sizes, char **names);

int GetPackFileNum(u_int *pack);

void DivPathName(char *path, char *out_dir, char *out_name);

void DivPathNameExt(char *path, char *out_dir, char *out_name, char *out_ext);
