#pragma once

#include "common.h"

#include <libmc.h>

#include "savedata.hpp"

class mgCMemory;

enum MC_FUNC_NO {
    MC_FUNC_SEARCH_TYPE        = 0,
    MC_FUNC_IDLE               = 1,
    MC_FUNC_NONE               = 2,
    MC_FUNC_MAKE_DIR           = 3,
    MC_FUNC_GET_ALL_FILE_INFO  = 5,
    MC_FUNC_SAVE               = 6,
    MC_FUNC_LOAD               = 7,
    MC_FUNC_DELETE             = 8,
    MC_FUNC_FORMAT             = 10,
    MC_FUNC_UNFORMAT           = 11,
    MC_FUNC_WRITE_TEST         = 13,
    MC_FUNC_SAVE_ALBUM         = 16,
    MC_FUNC_LOAD_ALBUM         = 17,
    MC_FUNC_CHECK_ALBUM        = 18,
    MC_FUNC_MAKE_ALBUM_DIR     = 19,
    MC_FUNC_SAVE_OMAKE         = 20,
    MC_FUNC_LOAD_OMAKE         = 21,
    MC_FUNC_CHECK_OMAKE        = 22,
    MC_FUNC_MAKE_OMAKE_DIR     = 23,
    MC_FUNC_CONVERT            = 24,
};

enum MC_STEP_RESULT {
    MC_STEP_FAILED = -1,
    MC_STEP_BUSY   = 0,
    MC_STEP_DONE   = 1,
};

enum MC_ERROR_CODE {
    MC_ERROR_NONE        = 0,
    MC_ERROR_LOAD        = 2,
    MC_ERROR_BROKEN      = 3,
    MC_ERROR_FULL        = 4,
    MC_ERROR_FILE        = 6,
    MC_ERROR_UNFORMATTED = 7,
    MC_ERROR_NO_CARD     = 8,
    MC_ERROR_COMMAND     = 11,
};

enum MC_DATA_SIZE_TYPE {
    MC_SIZE_SAVE_TOTAL  = 0,
    MC_SIZE_SAVE_FILE   = 1,
    MC_SIZE_ALBUM_FILE  = 2,
    MC_SIZE_ICONS       = 3,
    MC_SIZE_ALBUM_TOTAL = 4,
    MC_SIZE_SAVE_KB     = 5,
    MC_SIZE_UNK_6       = 6,
    MC_SIZE_OMAKE_FILE  = 7,
    MC_SIZE_OMAKE_TOTAL = 8,
    MC_SIZE_OMAKE_KB    = 9,
};

struct MC_ICON_DATA {
    char  name[0x20];
    void *data;
    int   size;
};

STATIC_ASSERT(sizeof(MC_ICON_DATA) == 0x28);

struct MC_CARD_INFO {
    s32 present;
    s32 type;
    s32 formatted;
    s32 format_change;
    u8  unk_10[4];
    s32 free_size;
    u8  unk_18[4];
    s32 result;
};

STATIC_ASSERT(sizeof(MC_CARD_INFO) == 0x20);

struct MC_DIR_ENTRY {
    u8   unk_00[0x10];
    u32  file_size;
    u8   unk_14[0xC];
    char name[0x20];
};

STATIC_ASSERT(sizeof(MC_DIR_ENTRY) == 0x40);

struct MC_ERROR_INFO {
    s32 code;
    s32 func_no;
    s32 file_no;
    s32 step;
    s32 retry_count;
};

STATIC_ASSERT(sizeof(MC_ERROR_INFO) == 0x14);

struct SAVEDATA_INFO {
    s32 state;
    s32 file_no;
    s16 map_no;
    s16 dungeon_no;
    s16 floor_id;
    s16 progress;
    u8  unk_10[2];
    s16 program_loop_no;
    u32 omake_flag;
    s16 debug_code;
    u8  unk_1A[6];
    u64 costume_bit;
    u64 play_time;
    u64 unique_counter;
    s32 fish_num;
    u8  unk_3C[4];
};

STATIC_ASSERT(sizeof(SAVEDATA_INFO) == 0x40);

struct SAVEDATA_FORMAT {
    char      version[0x10];
    u64       costume_bit;
    s16       debug_code;
    s16       unk_1A;
    s32       unk_1C;
    s32       unk_20;
    s32       unk_24;
    s32       check_digit_half;
    s32       check_digit;
    s32       map_no;
    s32       program_loop_no;
    s32       dungeon_no;
    s32       floor_id;
    s32       progress;
    s8        dng_tree_flag;
    u8        incomplete;
    u8        omake_flag;
    u8        unk_47;
    s32       fish_num;
    s32       unk_4C[11];
    u64       unique_counter;
    CSaveData save_data;
    u8        unk_659B0[0x10];
};

STATIC_ASSERT(sizeof(SAVEDATA_FORMAT) == 0x659C0);

struct COSBIT_INFO {
    s16 item_no;
    s8  bit_no;
    u8  unk_03;
};

STATIC_ASSERT(sizeof(COSBIT_INFO) == 0x4);

class CMemoryCardManager {
public:
    char             version[0x10];
    char             file_name[0x20];
    char             game_name[0x20];
    s32              func_no;
    u8               unk_54[4];
    s32              step;
    s32              fd;
    u8               unk_60[0x20];
    MC_DIR_ENTRY     dir_table[17];
    s32              dir_entries;
    s32              album_buffer_set;
    s32              port;
    s32              file_no;
    MC_ERROR_INFO    error;
    char            *write_buffer;
    char            *read_buffer;
    char             work_buffer[0x400];
    SAVEDATA_FORMAT *save_buffer;
    CSubGameData    *sub_game_data;
    char            *album_buffer;
    s32              load_map_no;
    s32              load_program_loop_no;
    s32              load_dungeon_no;
    s32              load_floor_id;
    s32              load_dng_tree_flag;
    s32              search_wait;
    s32              transferred;
    s32              total_transferred;
    s32              transfer_size;
    s32              transfer_result;
    MC_ICON_DATA     icon[3];
    sceMcIconSys     icon_sys;
    MC_CARD_INFO     card[2];
    u8               unk_D9C[4];
    SAVEDATA_INFO    file_info[13];
    s32              file_exists;
    u32              omake_flag;
    u8               unk_10E8[0x18];

    CMemoryCardManager();

    void Initialize(mgCMemory *memory);

    void InitSaveFileInfoTable();

    int GetOpenAttribute(char *name);

    void InitError();

    int InitForMC();

    void FinishForMC();

    void SetBuff_Album(char *buffer);

    void SetIconData(MC_ICON_DATA *icon_data, int name_no);

    int GetIconDataSize();

    int GetSaveDataSize(int type);

    void SetFuncNo(int func_no);

    int GetFuncNo();

    u_long CheckMaxUniqueCounter();

    int GetUpdateFile();

    int CheckDataFileNum();

    u32 CheckOmake(u_long *costume_bit);

    int CheckDebugCode();

    void InitPlayDataInfo();

    void UpDateViewInfo(SAVEDATA_INFO *info, SAVEDATA_FORMAT *format);

    int Step();

    char *GetVersion();

    int SearchMcType();

    int Write();

    int Convert();

    int MakeDir(int file_no);

    int SaveToMc(int file_no);

    int LoadFromMc(int file_no);

    int SaveAlbum();

    int LoadAlbum();

    int CheckAlbum();

    int SaveOamkeFile();

    int LoadOmakeFile();

    int CheckOmakeFile();

    int Format();

    int DeleteFile(int file_no);

    int McError(int result);

    int UnFormat();

    int GetSaveFileInfoFromMc(int file_no, int *step);

    int GetAllSaveFileInfo();
};

STATIC_ASSERT(sizeof(CMemoryCardManager) == 0x1100);

void CopyMCBrowserName(int name_no, char *dest, unsigned short *nl_offset);

void SetDngTreeFlag(int flag);

int GetCostumeList(u_long costume_bit, int type, short *list);

int McCheckMCPs2(MC_CARD_INFO *card);

int McCheckMCPs2Boot(MC_CARD_INFO *card, int size);

COSBIT_INFO *GetCosInfo(int item_no);

extern s16 NowProgramLoopNo;

extern char *SubGameOmakeTempBuffer;
