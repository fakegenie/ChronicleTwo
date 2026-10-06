#pragma once

struct sceSifDmaData {
    void *data;
    void *addr;
    int size;
    int mode;
};

#ifdef __cplusplus
extern "C" {
#endif

int sceSifSetDma(struct sceSifDmaData *transfer, int count);

int sceSifDmaStat(int id);

#ifdef __cplusplus
}
#endif
