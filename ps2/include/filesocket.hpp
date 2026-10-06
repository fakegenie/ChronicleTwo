#pragma once

#include "common.h"

int LoadFileSocket(char *path, unsigned int *data);

void WriteFileSocket(char *path, unsigned int *data, int size);
