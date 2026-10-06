#pragma once

#include "common.h"

class mgCMemory;

enum sndMIDI_STATUS {
    SND_MIDI_NOTE_OFF = 0x80,
    SND_MIDI_NOTE_ON = 0x90,
    SND_MIDI_CTRL_CHG = 0xB0,
    SND_MIDI_PROG_CHG = 0xC0,
    SND_MIDI_CH_PRESSURE = 0xD0,
    SND_MIDI_PITCH_BEND = 0xE0,
    SND_MIDI_META = 0xFF,
};

enum sndMIDI_META {
    SND_MIDI_META_END_OF_TRACK = 0x2F,
};

enum sndMIDI_CTRL {
    SND_MIDI_CTRL_VOLUME = 7,
    SND_MIDI_CTRL_PAN = 10,
    SND_MIDI_CTRL_EXPRESSION = 11,
    SND_MIDI_CTRL_LOOP = 110,
};

enum sndMIDI_LOOP {
    SND_MIDI_LOOP_START = 0,
    SND_MIDI_LOOP_END = 127,
};

struct sndSeSeqEvent {
    s16 delta;
    u8 status;
    u8 unk_3;
    s8 data[2];
};
STATIC_ASSERT(sizeof(sndSeSeqEvent) == 0x6);

struct sndSeSeqVoice {
    s8 active;
    s8 prog;
    s8 key;
    s8 se_id;

    sndSeSeqVoice() { active = 0; }
};
STATIC_ASSERT(sizeof(sndSeSeqVoice) == 0x4);

class sndCSeSeqData {
public:
    char *name;
    int tick_rate;
    int event_num;
    sndSeSeqEvent *event;

    sndCSeSeqData();

    void Initialize();

    void LoadSMF(char *smf, int size, mgCMemory *memory);
};
STATIC_ASSERT(sizeof(sndCSeSeqData) == 0x10);

class sndTrack {
public:
    s8 vol;
    s8 expression;
    s8 prog;
    s8 pan;
    s8 bend_lsb;
    s8 bend_msb;
    s8 se_id;
    s8 unk_7;
    int voice_num;
    sndSeSeqVoice voice[1];

    sndTrack() { Initialize(); }

    void Initialize();

    sndSeSeqVoice *SaerchVoice(int prog, int key);

    sndSeSeqVoice *GetEmptyVoice();

    int NoteOn(int key, int velocity);

    int NoteOff(int key, int velocity);

    int CtrlChg(int ctrl, int value);

    int ProgChg(int prog);

    int PitchBend(int msb, int lsb);
};
STATIC_ASSERT(sizeof(sndTrack) == 0x10);

class sndCSeSeq {
public:
    int port;
    int bank;
    sndCSeSeqData *data;
    sndSeSeqEvent *event;
    int tick;
    int wait;
    int vol;
    int loop_tick;
    sndSeSeqEvent *loop_event;
    int loop;
    int pause;
    int track_num;
    sndTrack track[8];

    sndCSeSeq() { Initialize(); }

    void Initialize();

    void SetSeID(int id);

    void Count(float frames);

    void Stop();

    int Step(float frames);

    int chk_trk(int trk);

    void NoteOn(int trk, int key, int velocity);

    void NoteOff(int trk, int key, int velocity);

    void AllNoteOff();

    void TrackNoteOff(int trk);

    void CtrlChg(int trk, int ctrl, int value);

    void ProgChg(int trk, int prog);

    void PitchBend(int trk, int msb, int lsb);

    void SendVol(int trk);

    void SendPan(int trk);

    void SendPitch(int trk);
};
STATIC_ASSERT(sizeof(sndCSeSeq) == 0xB0);
