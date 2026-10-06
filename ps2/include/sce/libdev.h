#pragma once

#include "common.h"

extern "C" {

void sceDevConsInit();

int sceDevConsOpen(u_int x, u_int y, u_int width, u_int height);

void sceDevConsClose(int handle);

void sceDevConsAttribute(int handle, u_char attributes);

void sceDevConsDraw(int handle);

}
