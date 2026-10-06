#pragma once

#include "common.h"

int ConvertBinToTxt(u8* data, int size, char* text);

int ConvertTxtToBin(char* text, u8* data);

int EncodePassword(u8* data, int size, u8* key, int key_size, char* text, int text_size);

int DecodePassword(char* text, u8* data, int size, u8* key, int key_size);
