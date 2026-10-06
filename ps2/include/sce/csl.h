#pragma once

struct sceCslBuffCtx {
    int sema;
    void *buff;
};

struct sceCslBuffGrp {
    int buffNum;
    sceCslBuffCtx *buffCtx;
};

struct sceCslCtx {
    int buffGrpNum;
    sceCslBuffGrp *buffGrp;
    void *conf;
    void *callBack;
    char **extmod;
};
