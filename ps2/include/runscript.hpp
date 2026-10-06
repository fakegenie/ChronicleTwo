#pragma once

#include "common.h"

enum RS_OPCODE {
    RS_OP_LOAD       = 1,
    RS_OP_LOAD_ADDR  = 2,
    RS_OP_PUSH_CONST = 3,
    RS_OP_POP        = 4,
    RS_OP_STORE      = 5,
    RS_OP_ADD        = 6,
    RS_OP_SUB        = 7,
    RS_OP_MUL        = 8,
    RS_OP_DIV        = 9,
    RS_OP_MOD        = 10,
    RS_OP_NEG        = 11,
    RS_OP_ITOF       = 12,
    RS_OP_FTOI       = 13,
    RS_OP_CMP        = 14,
    RS_OP_RET        = 15,
    RS_OP_JMP        = 16,
    RS_OP_JMP_FALSE  = 17,
    RS_OP_JMP_TRUE   = 18,
    RS_OP_CALL       = 19,
    RS_OP_PRINT      = 20,
    RS_OP_EXT        = 21,
    RS_OP_WAIT       = 23,
    RS_OP_AND        = 24,
    RS_OP_OR         = 25,
    RS_OP_NOT        = 26,
    RS_OP_END        = 27,
    RS_OP_SKIP_END   = 28,
    RS_OP_SIN        = 29,
    RS_OP_COS        = 30,
};

enum RS_ADDR_MODE {
    RS_ADDR_LOCAL               = 0x1,
    RS_ADDR_LOCAL_INDEX         = 0x2,
    RS_ADDR_POINTER_INDEX       = 0x4,
    RS_ADDR_LOCAL_FLOAT         = 0x8,
    RS_ADDR_LOCAL_INDEX_FLOAT   = 0x10,
    RS_ADDR_POINTER_INDEX_FLOAT = 0x20,
    RS_ADDR_GLOBAL              = 0x40,
    RS_ADDR_GLOBAL_FLOAT        = 0x200,
};

enum RS_CONST_TYPE {
    RS_CONST_INT   = 1,
    RS_CONST_FLOAT = 2,
    RS_CONST_STR   = 3,
};

enum RS_COMPARE {
    RS_CMP_EQ = 40,
    RS_CMP_NE = 41,
    RS_CMP_LT = 42,
    RS_CMP_LE = 43,
    RS_CMP_GT = 44,
    RS_CMP_GE = 45,
};

enum RS_STACK_TYPE {
    RS_INT   = 0,
    RS_FLOAT = 1,
    RS_STR   = 2,
    RS_PTR   = 3,
};

enum RS_VERSION {
    RS_VERSION_1 = 1,
    RS_VERSION_2 = 2,
};

struct RS_STACKDATA {
    int type;

    union {
        float         f;
        int           i;
        char         *s;
        RS_STACKDATA *p;
    };
};

STATIC_ASSERT(sizeof(RS_STACKDATA) == 0x8);

struct vmcode_t {
    int op;
    int arg1;
    int arg2;
};

STATIC_ASSERT(sizeof(vmcode_t) == 0xC);

struct funcdata {
    int   addr;
    char *name;
    int   local;
    int   arg;
};

STATIC_ASSERT(sizeof(funcdata) == 0x10);

struct RS_CALLDATA {
    vmcode_t     *ret;
    RS_STACKDATA *frame;
    funcdata     *func;
};

STATIC_ASSERT(sizeof(RS_CALLDATA) == 0xC);

struct RS_PROGDATA {
    int no;
    int func;
};

STATIC_ASSERT(sizeof(RS_PROGDATA) == 0x8);

struct RS_PROG_HEADER {
    char magic[4];
    int  main;
    int  code;
    int  prog;
    int  prog_num;
    int  unk_14;
    int  global_num;
};

class CRunScript {
public:
    int             version;
    int             ext_func_num;
    int (**ext_func_table)(RS_STACKDATA *, int);
    int             stack_num;
    RS_STACKDATA   *stack;
    RS_STACKDATA   *sp;
    RS_STACKDATA   *stack_end;
    RS_STACKDATA   *global;
    int             call_num;
    RS_CALLDATA    *call;
    RS_CALLDATA    *call_sp;
    RS_CALLDATA    *call_end;
    RS_STACKDATA   *frame;
    funcdata       *func;
    vmcode_t       *pc;
    int             end;
    int             skip_wait;
    RS_PROG_HEADER *prog;
    char           *code;
    int             result;
    int             skip_end_count;

    CRunScript();

    void DeleteProgram();

    void check_stack();

    void push(RS_STACKDATA value);

    void push_int(int value);

    void push_str(char *string);

    void push_ptr(RS_STACKDATA *pointer);

    void push_float(float value);

    RS_STACKDATA pop();

    vmcode_t *call_func(funcdata *callee, vmcode_t *return_pc);

    vmcode_t *ret_func();

    void ext(RS_STACKDATA *args, int argc);

    void load(RS_PROG_HEADER *prog, RS_STACKDATA *stack, int stack_num, RS_CALLDATA *call, int call_num);

    void ext_func(int (**table)(RS_STACKDATA *, int), int count);

    void resume();

    int run(int no);

    int check_program(int no);

    void skip();

    void exe(vmcode_t *entry);
};

STATIC_ASSERT(sizeof(CRunScript) == 0x54);

int rsGetStackInt(RS_STACKDATA *data);

void rsSetStack(RS_STACKDATA *data, int value);
