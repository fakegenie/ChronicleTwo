#pragma once

#ifdef __cplusplus
extern "C" {
#endif

struct SemaParam {
    int          currentCount;
    int          maxCount;
    int          initCount;
    int          numWaitThreads;
    unsigned int attr;
    unsigned int option;
};

int CreateSema(struct SemaParam *param);

int DeleteSema(int sema_id);

int WaitSema(int sema_id);

int SignalSema(int sema_id);

struct ThreadParam {
    int          status;
    void       (*entry)(void *);
    void        *stack;
    int          stackSize;
    void        *gpReg;
    int          initPriority;
    int          currentPriority;
    unsigned int attr;
    unsigned int option;
};

extern void *_gp;

int CreateThread(struct ThreadParam *param);

int StartThread(int thread_id, void *arg);

int RotateThreadReadyQueue(int priority);

int TerminateThread(int thread_id);

int DeleteThread(int thread_id);

void FlushCache(int operation);

void iFlushCache(int operation);

void iSyncDCache(void *start, void *end);

int GetThreadId(void);

int ChangeThreadPriority(int thread_id, int priority);

void Exit(int status);

void Exit__2(int status);

#ifdef __cplusplus
}
#endif
