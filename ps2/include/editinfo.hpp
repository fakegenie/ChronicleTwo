#pragma once

#include "common.h"

class CEditPartsInfo;
class mgCMemory;

struct ePlaceData {
    s32   id;
    s32   angle;
    s32   unk_8;
    s32   unk_c;
    float position[3];
    s32   unk_1c;
};
STATIC_ASSERT(sizeof(ePlaceData) == 0x20);

class CEditInfoMngr {
public:
    s32             parts_info_num;
    CEditPartsInfo *parts_info;
    s32             fix_parts_num;
    ePlaceData     *fix_parts;
    s32             init_parts_num;
    ePlaceData     *init_parts;

    CEditInfoMngr() {
        Initialize();
    }

    void Initialize();

    void SetePartsInfoTable(CEditPartsInfo *table, int num);

    void SeteFixPartsTable(ePlaceData *table, int num);

    CEditPartsInfo *GetePartsInfo(int no);

    CEditPartsInfo *GetePartsInfo(char *name);

    CEditPartsInfo *GetePartsInfoAtID(int id);

    CEditPartsInfo *GetePartsInfoAtType(int type);

    void LoadEditInfo(char *script, int size, mgCMemory *stack);
};
STATIC_ASSERT(sizeof(CEditInfoMngr) == 0x18);
