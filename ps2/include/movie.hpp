#pragma once

#include "common.h"
#include <libcdvd.h>
#include <libmpeg.h>

class mgCMemory;

enum VideoDecState {
    VIDEO_DEC_STATE_NORMAL = 0,
    VIDEO_DEC_STATE_FLUSH = 2,
    VIDEO_DEC_STATE_END = 3,
};

enum AudioDecState {
    AUDIO_DEC_STATE_HEADER = 0,
    AUDIO_DEC_STATE_PRESET = 1,
    AUDIO_DEC_STATE_PLAY = 2,
    AUDIO_DEC_STATE_PAUSE = 3,
};

enum VoTagStatus {
    VO_TAG_STATUS_FREE = 0,
    VO_TAG_STATUS_FIRST = 1,
    VO_TAG_STATUS_READY = 2,
};

struct TimeStamp {
    long pts;
    long dts;
    int pos;
    int len;
};
STATIC_ASSERT(sizeof(TimeStamp) == 0x18);

union QWORD {
    u_long128 q;
    u_long l[2];
};
STATIC_ASSERT(sizeof(QWORD) == 0x10);

struct ViBuf {
    u_long128 *data;
    u_long128 *tag;
    int n;
    int dma_start;
    int dma_n;
    int read_bytes;
    int buff_size;
    sceIpuDmaEnv env;
    int sema;
    int is_active;
    long total_bytes;
    TimeStamp *ts;
    int n_ts;
    int count_ts;
    int wt_ts;
};
STATIC_ASSERT(sizeof(ViBuf) == 0x60);

struct VideoDec {
    sceMpeg mpeg;
    ViBuf vibuf;
    volatile u_int state;
    int unk_ac;
    int hid_endimage;
    int hid_vblank;
};
STATIC_ASSERT(sizeof(VideoDec) == 0xB8);

struct VoData {
    u_int v[512 * 448];
};
STATIC_ASSERT(sizeof(VoData) == 0xE0000);

struct VoTag {
    volatile int status;
    int unk_4[15];
    u_int *v[2];
};
STATIC_ASSERT(sizeof(VoTag) == 0x48);

struct VoBuf {
    VoData *data;
    VoTag *tag;
    VoTag *ring_tag;
    volatile int write;
    volatile int count;
    int size;
};
STATIC_ASSERT(sizeof(VoBuf) == 0x18);

struct StrFile {
    sceCdlFILE fp;
    int unk_20;
    int fd;
    int is_on_cd;
    int size;
    void *iop_buf;
};
STATIC_ASSERT(sizeof(StrFile) == 0x34);

struct ReadBuf {
    u_char data[0x50000];
    int put;
    int count;
    int size;
};

struct AudioDec {
    int state;
    u_char hdr[0x28];
    int hdr_count;
    u_char *data;
    int put;
    int count;
    int size;
    int total_bytes;
    int iop_buff;
    int iop_buff_size;
    int iop_last_pos;
    int iop_pause_pos;
    int total_bytes_sent;
    int iop_zero;
};
STATIC_ASSERT(sizeof(AudioDec) == 0x5C);

class CMovie {
public:
    int unk_0;
    VoData *vo_data;
    u_long128 *vi_buf_data;
    u_long128 *vi_buf_tag;
    u_char *mpeg_work;
    u_int *image_tag[2][2];
    u_char unk_24[0x1C];
    VoTag vo_tag[2];
    u_char unk_d0[0x30];
    u_char def_stack[0x800];
    u_char video_stack[0x4000];
    u_char step_stack[0x4000];
    u_char audio_buf[0x18000];
    TimeStamp time_stamp[0x200];
    bool is_playing;
    int video_thread;
    int def_thread;
    int step_thread;
    u_char unk_23910[0x30];

    void Load(char *name, mgCMemory **memory, int width, int height, bool with_audio, bool loop,
              bool init_sound);

    void Load(char *name, mgCMemory *memory, int width, int height, bool with_audio, bool loop);

    void Load(char *name, mgCMemory *memory, int width, int height, bool with_audio, bool loop,
              bool init_sound);

    void Play(char *texture_name);

    void SwitchThread();

    void Term();

    int EndCheck();

    int IsStarted();

    int GetVoBufDataSize();

    int GetViBufDataSize();

    int GetViBufTagSize();

    int GetMpegWorkSize(int width, int height);

    int GetReadBufSize();

    int GetTagProgSize(int width, int height);

    int videoDecCreate(VideoDec *vd, u_char *mpeg_work, int mpeg_work_size, u_long128 *data,
                       u_long128 *tag, int n, TimeStamp *ts, int n_ts);

    int videoDecSetStream(VideoDec *vd, int str_type, int ch,
                          int (*callback)(sceMpeg *, sceMpegCbData *, void *), void *data);

    int videoDecDelete(VideoDec *vd);

    int videoDecFlush(VideoDec *vd);
};
STATIC_ASSERT(sizeof(CMovie) == 0x23940);

int mpegError(sceMpeg *mpeg, sceMpegCbDataError *error, void *user);
int mpegNodata(sceMpeg *mpeg, sceMpegCbData *data, void *user);
int mpegStopDMA(sceMpeg *mpeg, sceMpegCbData *data, void *user);
int mpegRestartDMA(sceMpeg *mpeg, sceMpegCbData *data, void *user);
int mpegTS(sceMpeg *mpeg, sceMpegCbDataTimeStamp *data, void *user);
int pcmCallback(sceMpeg *mpeg, sceMpegCbDataStr *str, void *user);
int videoCallback(sceMpeg *mpeg, sceMpegCbDataStr *str, void *user);
int decBs0(VideoDec *dec);
void videoDecMain(void *arg);
int defMain(void *);
void stepMain(void *arg);
int vblankHandler(int irq);
int handler_endimage(int irq);
int videoDecGetState(VideoDec *dec);
u32 videoDecSetState(VideoDec *dec, u32 state);
int switchThread(void);
int viBufCreate(ViBuf *buf, u_long128 *data, u_long128 *tags, int sectors, TimeStamp *ts, int ts_count);
int viBufReset(ViBuf *buf);
int viBufAddDMA(ViBuf *buf);
int viBufStopDMA(ViBuf *buf);
int viBufRestartDMA(ViBuf *buf);
int viBufModifyPts(ViBuf *buf, TimeStamp *range);
int viBufPutTs(ViBuf *buf, TimeStamp *ts);
int viBufGetTs(ViBuf *buf, TimeStamp *ts);
int viBufDelete(ViBuf *buf);
void videoDecBeginPut(VideoDec *dec, u8 **area1, int *size1, u8 **area2, int *size2);
void videoDecEndPut(VideoDec *dec, int count);
int isAudioOK(void);
int audioDecSendToIOP(AudioDec *dec);
int videoDecPutTs(VideoDec *dec, long pts, long dts, u8 *area, int size);
void viBufFlush(ViBuf *buf);
VoTag *voBufGetTag(VoBuf *buf);
void voBufReset(VoBuf *buf);
void voBufDecCount(VoBuf *buf);
void voBufIncCount(VoBuf *buf);
u8 *voBufGetData(VoBuf *buf);
void audioDecBeginPut(AudioDec *dec, u8 **area1, int *size1, u8 **area2, int *size2);
void audioDecEndPut(AudioDec *dec, int count);
void audioDecResume(AudioDec *dec);
void audioDecPause(AudioDec *dec);
int cpy2area(u8 *dst1, int size1, u8 *dst2, int size2, u8 *src1, int len1, u8 *src2, int len2);
int sendToIOP(int iop_addr, u8 *src, int size);
void changeMasterVolume(u32 volume);
void changeInputVolume(u32 volume);
void setD4_CHCR(u32 chcr);
int audioDecDelete(AudioDec *dec);
void audioDecReset(AudioDec *dec);
int strFileClose(StrFile *file);
void startDisplay(int field);
void iopGetArea(int *addr1, int *size1, int *addr2, int *size2, AudioDec *dec, int wanted);
int sendToIOP2area(int dest1, int size1, int dest2, int size2, u8 *src1, int len1, u8 *src2,
                   int len2);
void audioDecStart(AudioDec *dec);
void strFileSeek(StrFile *file);
int strFileRead(StrFile *file, void *buf, int size);
int readBufBeginPut(ReadBuf *buf, u8 **out);
int readBufEndPut(ReadBuf *buf, int count);
int readBufBeginGet(ReadBuf *buf, u8 **out);
int readBufEndGet(ReadBuf *buf, int count);
void setImageTag(u32 *tag, void *data, int a, int width, int height);
void voBufCreate(VoBuf *buf, VoData *data, VoTag *tags, int count);
void readBufCreate(ReadBuf *buf);
int audioDecCreate(AudioDec *dec, u8 *ring_buf, int ring_size, int iop_size);
int strFileOpen(StrFile *file, char *path);

void viBufBeginPut(ViBuf *buf, u8 **area1, int *size1, u8 **area2, int *size2);

void viBufEndPut(ViBuf *buf, int count);

int audioDecIsPreset(AudioDec *dec);
