#pragma once

#include "common.h"

enum MidiPortLimit {
    MIDI_PORT_COUNT      = 16,
    MIDI_PORT_MSIN_FIRST = 7,
    MIDI_PORT_BANK_MAX   = 16,
    MIDI_PORT_SEQ_MAX    = 10,
    MIDI_MSIN_PORT_COUNT = 9,
};

enum SpuAllocDirection {
    SPU_ALLOC_UPWARD   = 0,
    SPU_ALLOC_DOWNWARD = 1,
};

struct MIDI_FADE {
    s32   active;
    s32   target_volume;
    float volume;
    float step;
};

STATIC_ASSERT(sizeof(MIDI_FADE) == 0x10);

struct MIDI_PORT {
    s32       unk_00;
    u8        spu_direction;
    s32       linked_port;
    s32       dependent_port[MIDI_PORT_BANK_MAX];
    s32       dependent_port_count;
    void     *bank[MIDI_PORT_BANK_MAX];
    s32       bank_count;
    s32       spu_address;
    s32       unk_98;
    s32       spu_next_address;
    void     *sequence[MIDI_PORT_SEQ_MAX];
    void     *resident_sequence;
    s32       unk_CC[MIDI_PORT_SEQ_MAX];
    s32       sequence_count;
    MIDI_FADE fade[2];
    s32       unk_118;
    s32       unk_11C;
    s32       unk_120;
};

STATIC_ASSERT(sizeof(MIDI_PORT) == 0x124);

struct MIDI_STATE {
    MIDI_PORT port[MIDI_PORT_COUNT];
};

STATIC_ASSERT(sizeof(MIDI_STATE) == 0x1240);

struct MIDI_BANK {
    s32   bank_no;
    void *hd_address;
    void *bd_address;
    s32   bd_size;
    s32   spu_address;
    u8    unk_14[0x30];
};

STATIC_ASSERT(sizeof(MIDI_BANK) == 0x44);

struct MSIN_BUFFER {
    s32 size;
    s32 length;
    u8  messages[0x1F8];
};

STATIC_ASSERT(sizeof(MSIN_BUFFER) == 0x200);

struct STREAM_PACK_REQUEST {
    char name[52];
    char pack_name[12];
};

STATIC_ASSERT(sizeof(STREAM_PACK_REQUEST) == 0x40);

class CSound {
public:
    void StopVoice(int core);

    void SndInReverb(bool enable);

    void SetReverb(int core, int mode, int depth);

    int Init(int mode0, int mode1, int depth0, int depth1);

    int Exit();

    void DEL_PORT(int port);

    void SQ_Play(int port, int seq_no, int volume);

    void SQ_RePlay(int port);

    void SE_Play(int port, int bank, int program, int key, int pan, int velocity, int volume, int pitch, int id);

    void SE_SetVol(int port, int bank, int program, int key, int volume, int id);

    void SE_SetPan(int port, int bank, int program, int key, int pan, int id);

    void SE_Stop(int port, int bank, int program, int key, int id);

    void Step();

    void Stop(int port);

    void SetVol(int port, int volume);

    void SetStereoMode(int mode);

    void SetMasterVol(int core, int volume);

    void LoadHdBd(int port, int hd, int hd_size, int bd, int bd_size);

    void LoadHdBd2(int port, int hd, int hd_size, int bd, int bd_size);

    int LoadHdBdAdd(int port, int hd, int hd_size, int bd, int bd_size);

    int LoadSeq(int port, int address, int size);

    void SE_SetPitch(int port, int bank, int program, int key, int pitch, int id);

    void StreamOpenFast(int channel, char *name);

    void StreamOpenFromFPLFast(int channel, char *name, char *pack_name);

    void StreamPlay(int channel);

    void StreamStop(int channel);

    void StreamClose(int channel);

    void StreamEND(int channel);

    void StreamPause(int channel);

    void StreamRePlay(int channel);

    void StreamSetVol(int channel, int left, int right);

    int StreamGetState(int channel);

    int StreamGetLevel(int channel);

    void StreamStandBy(int channel);

    int TransBdState(int channel);

    int StreamOpenState();
};

STATIC_ASSERT(sizeof(CSound) == 1);

void set_spu(int mode0, int mode1, int depth0, int depth1);

int TransHdBd(int hd, int hd_size, int bd, int bd_size);

extern void *iop_bd_addr;

extern CSound CSnd;
