#pragma once

#include "common.h"

class mgCMemory;

enum mgSTACK_MODE {
    MG_STACK_MODE_FIRST = 1,
    MG_STACK_MODE_LARGEST = 2,
    MG_STACK_MODE_FIT = 3,
};

struct mgMEMORY_BLOCK {
    u_long128 *data;
    int size;
    int unk_8;
    mgMEMORY_BLOCK *next;
};
STATIC_ASSERT(sizeof(mgMEMORY_BLOCK) == 0x10);

class mgCMemory {
public:
    char name[0x10];
    u_int heap_size;
    u_long128 *heap;
    mgMEMORY_BLOCK *heap_top;
    int lock;
    union {
        u_long128 *stack;
        u8 *stack_bytes;
    };
    int stack_used;
    int stack_size;
    mgMEMORY_BLOCK *stack_block;

    mgCMemory() { Init(); }

    int stGetUsed() {
        return stack_used;
    }

    int stGetSize() {
        return stack_size;
    }

    int stGetRest() {
        return stack_size - stack_used;
    }

    u_long128 *stGetTop() {
        return &stack[stack_used];
    }

    void stReset() {
        stack_used = 0;
        lock = 0;
    }

    void Init();

    void SetHeapMem(u_long128 *buffer, int size);

    void ClearHeapMem();

    void Free(u_long128 *data);

    u_long128 *StartStackMode(int mode, int size);

    void EndStackMode();

    u_long128 *stAlloc64(int size);

    u_long128 *stAllocTest(int size);

    u_long128 *stAlloc(int size);

    u_long128 *Alloc(int size);

    void stAlign64();

    void Align64();

    void stSetBuffer(u_long128 *buffer, int size);
};
STATIC_ASSERT(sizeof(mgCMemory) == 0x30);

void *MG_ADDRESS_CHECK(void *address, char *where);

void *operator new(size_t size, u_long128 *buffer);

void *operator new[](size_t size, u_long128 *buffer);

char *mgCopyString(char *text, mgCMemory *memory);
