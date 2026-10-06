#pragma once

#include "common.h"

enum SPI_STACK_TYPE {
    SPI_STACK_TYPE_STRING = 0,
    SPI_STACK_TYPE_INT = 1,
    SPI_STACK_TYPE_FLOAT = 2,
    SPI_STACK_TYPE_INVALID = 0xFF,
};

enum SPI_LIMIT {
    SPI_HASH_BUCKET_COUNT = 101,
    SPI_HASH_TAG_MAX = 128,
    SPI_STACK_SIZE = 64,
    SPI_STRING_BUFF_SIZE = 0x2800,
    SPI_TOKEN_SIZE = 0x100,
};

enum SPI_BINARY_ARG_TYPE {
    SPI_BINARY_ARG_TYPE_INT = 1,
    SPI_BINARY_ARG_TYPE_FLOAT = 2,
    SPI_BINARY_ARG_TYPE_STRING = 3,
};

class input_str {
public:
    char *buffer;
    int   size;
    int   position;

    int GetLine(char *line, int line_size, char *terminator);

    int get(int *c) {
        *c = (u8)buffer[position];
        position++;
        return size >= position;
    }

    input_str() {
        size = 0;
        position = 0;
        buffer = NULL;
    }

    void back() {
        if (position > 0) {
            position--;
        }
    }
};
STATIC_ASSERT(sizeof(input_str) == 0xC);

struct SPI_STACK {
    int type;
    union {
        int   integer;
        float real;
        char *string;
    } value;

    SPI_STACK &operator=(const SPI_STACK &other) {
        type = other.type;
        value.integer = other.value.integer;
        return *this;
    }
};
STATIC_ASSERT(sizeof(SPI_STACK) == 0x8);

typedef int (*SPI_TAG_FUNCTION)(SPI_STACK *stack, int argument_count);

struct SPI_TAG_PARAM {
    char            *name;
    SPI_TAG_FUNCTION function;
};
STATIC_ASSERT(sizeof(SPI_TAG_PARAM) == 0x8);

struct SPI_TAG_HASH {
    SPI_TAG_HASH *next;
    char         *name;
    int           index;
    int           unk_c;
};
STATIC_ASSERT(sizeof(SPI_TAG_HASH) == 0x10);

class CScriptInterpreter : public input_str {
public:
    int            stack_count;
    int            stack_size;
    SPI_STACK     *stack;
    int            string_buff_size;
    char          *string_buff_next;
    char          *string_buff;
    int            binary;
    int            tag_count;
    SPI_TAG_PARAM *tag;
    SPI_TAG_HASH **hash_table;
    u8             unk_34[0xC];
    SPI_TAG_HASH  *hash_buckets[SPI_HASH_BUCKET_COUNT];
    u8             unk_1d4[0xC];
    SPI_TAG_HASH   hash_entries[SPI_HASH_TAG_MAX];
    u8             unk_9e0[0x4F0];

    void PushStack(SPI_STACK argument);

    int GetNextTAG(int call);

    void SetStack(SPI_STACK *stack, int size) {
        this->stack = stack;
        stack_size = size;
        stack_count = 0;
    }

    void SetStringBuff(char *buff, int size) {
        string_buff = buff;
        string_buff_size = size;
        string_buff_next = string_buff;
    }

    void Run();

    int hash(char *name);

    void SetTag(SPI_TAG_PARAM *tags);

    void SetScript(char *script, int script_size);

    CScriptInterpreter();

    int GetArgBin();

    int GetArg();

    int SearchCommand(int *tag_index);
};
STATIC_ASSERT(sizeof(CScriptInterpreter) == 0xED0);

int spiGetStackInt(SPI_STACK *stack);

float spiGetStackFloat(SPI_STACK *stack);

char *spiGetStackString(SPI_STACK *stack);

void spiGetStackVector(float *vector, SPI_STACK *stack);
