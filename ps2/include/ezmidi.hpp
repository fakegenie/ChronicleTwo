#pragma once

#include "common.h"

enum EzMidiCommandFlag {
    EZMIDI_ARGUMENT_BLOCK = 0x1000,
    EZMIDI_RESPONSE = 0x8000
};

int ezMidiInit();

int ezMidi(int command, int argument);

int ezTransToIOP2(void *iop_address, void *ee_address, int size);
