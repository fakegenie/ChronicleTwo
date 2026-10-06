#pragma once

#include "types.h"
#include <libipu.h>

struct sceMpeg {
    int width;
    int height;
    int frameCount;
    long pts;
    long dts;
    u_long flags;
    long pts2nd;
    long dts2nd;
    u_long flags2nd;
    void *sys;
};

enum sceMpegCbType {
    sceMpegCbError = 0,
    sceMpegCbNodata = 1,
    sceMpegCbStopDMA = 2,
    sceMpegCbRestartDMA = 3,
    sceMpegCbBackground = 4,
    sceMpegCbTimeStamp = 5,
    sceMpegCbStr = 6,
};

enum sceMpegStrType {
    sceMpegStrM2V = 0,
    sceMpegStrIPU = 1,
    sceMpegStrPCM = 2,
    sceMpegStrADPCM = 3,
    sceMpegStrDATA = 4,
};

struct sceMpegCbDataError {
    sceMpegCbType type;
    char *errMessage;
};

struct sceMpegCbDataTimeStamp {
    sceMpegCbType type;
    long pts;
    long dts;
};

struct sceMpegCbDataStr {
    sceMpegCbType type;
    u_char *header;
    u_char *data;
    u_int len;
    long pts;
    long dts;
};

union sceMpegCbData {
    sceMpegCbType type;
    sceMpegCbDataError error;
    sceMpegCbDataTimeStamp ts;
    sceMpegCbDataStr str;
};

typedef int (*sceMpegCallback)(sceMpeg *mp, sceMpegCbData *cbdata, void *anyData);

extern "C" {

int sceMpegInit(void);

int sceMpegCreate(sceMpeg *mp, u_char *work_area, int work_area_size);

int sceMpegDelete(sceMpeg *mp);

int sceMpegReset(sceMpeg *mp);

int sceMpegGetPicture(sceMpeg *mp, sceIpuRGB32 *rgb32, int mbcount);

int sceMpegIsEnd(sceMpeg *mp);

sceMpegCallback sceMpegAddCallback(sceMpeg *mp, sceMpegCbType type, sceMpegCallback callback,
                                   void *anyData);

sceMpegCallback sceMpegAddStrCallback(sceMpeg *mp, sceMpegStrType strType, int ch,
                                      sceMpegCallback callback, void *anyData);

int sceMpegDemuxPssRing(sceMpeg *mp, u_char *start, int size, u_char *buf_start, int buf_size);
}
