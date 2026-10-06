#pragma once

#include "common.h"

class mgCMemory;

enum QUEST_LIMIT {
    QUEST_PLAY_DATA_MAX = 0x40,
    QUEST_INFO_COMMENT_MAX = 4,
    MONSTER_BOOK_ENTRY_MAX = 0x180,
    MONSTER_BOOK_KILL_MAX = 60000,
};

enum QUEST_REQUEST_STATUS {
    QUEST_REQUEST_STATUS_INVALID = -1,
    QUEST_REQUEST_STATUS_NONE = 0,
    QUEST_REQUEST_STATUS_ACCEPTED = 1,
    QUEST_REQUEST_STATUS_CLEARED = 2,
};

struct QUEST_INFO {
    s32  id;
    char name[0x84];
    char comment[0x140];
    char reaction[QUEST_INFO_COMMENT_MAX][0x82];
};

STATIC_ASSERT(sizeof(QUEST_INFO) == 0x3D0);

class CQuestManager {
public:
    s32         num;
    QUEST_INFO *info;

    CQuestManager() { Initialize(); }

    void Initialize();

    QUEST_INFO *GetQuestInfo(int id);

    void LoadCfg(mgCMemory *stack, char *script, int script_size);
};

STATIC_ASSERT(sizeof(CQuestManager) == 0x8);

struct QUEST_PLAY_DATA {
    s8 accepted;
    s8 cleared;
    u8 unk_2[0xE];
};

STATIC_ASSERT(sizeof(QUEST_PLAY_DATA) == 0x10);

class CQuestData {
public:
    CQuestData() { Initialize(); }

    QUEST_PLAY_DATA play[QUEST_PLAY_DATA_MAX];
    u8              unk_400[0x80];

    void Initialize();

    void SetQuestFlag(int id, int flag);

    void QuestClear(int id);

    QUEST_PLAY_DATA *GetPlayQuestData(int id);
};

STATIC_ASSERT(sizeof(CQuestData) == 0x480);

struct MONSTER_BOOK_ENTRY {
    u8  unk_0[0x2];
    u16 kill_count;
    u8  unk_4[0x8];
};

STATIC_ASSERT(sizeof(MONSTER_BOOK_ENTRY) == 0xC);

class CMonsterBook {
public:
    MONSTER_BOOK_ENTRY entry[MONSTER_BOOK_ENTRY_MAX];

    int CountKill(int monster_id, int count);
};

STATIC_ASSERT(sizeof(CMonsterBook) == 0x1200);

void QuestRequestSetFlag(int id, int flag);

void QuestRequestClear(int id, int unused);

int GetQuestRequestStatus(int id);
