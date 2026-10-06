#pragma once

#include "common.h"
#include "mg_memory.hpp"

class ClsMes;

extern mgCMemory SystemMesStack;

extern ClsMes SystemMessage;
extern ClsMes SystemMessage2;
extern ClsMes SystemMessage3;
extern short SystemMesBuffer[];
extern short SysMesBuffer[];

ClsMes *GetSystemMessage();

ClsMes *GetSystemMessage(int index);

void LoadSystemMes();

short *GetSystemMesBuffer();

short *GetSysMesBuffer();

void CreateSystemMes();

void CreateSystemMes(int index, int unused);
