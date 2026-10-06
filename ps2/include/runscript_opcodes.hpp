#pragma once

#include "common.h"

#include "runscript.hpp"

class CActiveMonster;
class mgCMemory;

struct RS_EXTFUNC_INFO {
    int (*func)(RS_STACKDATA *, int);
    int no;
};

STATIC_ASSERT(sizeof(RS_EXTFUNC_INFO) == 0x8);

extern CActiveMonster *nowMonster;

int SetMonsterScript(CRunScript *script, char *program, mgCMemory *memory);

void SetMonsterExtendTable();
