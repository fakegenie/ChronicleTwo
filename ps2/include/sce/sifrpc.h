#pragma once

struct sceSifRpcHeader {
    void *packet_address;
    unsigned int rpc_id;
    int semaphore_id;
    unsigned int mode;
};

struct sceSifServeData;

struct sceSifClientData {
    sceSifRpcHeader header;
    unsigned int command;
    void *buffer;
    void *callback_buffer;
    void (*callback)(void *);
    void *callback_parameter;
    sceSifServeData *server;
};

#ifdef __cplusplus
extern "C" {
#endif

void sceSifInitRpc(int mode);
int sceSifRebootIop(const char *path);
int sceSifSyncIop(void);
int sceSifLoadModule(const char *path, int arg_len, const char *args);

void sceSifExitCmd(void);

int sceSifBindRpc(struct sceSifClientData *client, unsigned int number, unsigned int mode);

int sceSifCheckStatRpc(struct sceSifClientData *client);

int sceSifCallRpc(struct sceSifClientData *client, unsigned int number, unsigned int mode,
                  void *send, int send_size, void *receive, int receive_size,
                  void (*end_callback)(void *), void *end_parameter);

int sceSifInitIopHeap(void);

void *sceSifAllocIopHeap(unsigned int size);

int sceSifFreeIopHeap(void *address);

void *sceSifAllocSysMemory(int mode, unsigned int size, void *address);

int sceSifFreeSysMemory(void *address);

#ifdef __cplusplus
}
#endif
