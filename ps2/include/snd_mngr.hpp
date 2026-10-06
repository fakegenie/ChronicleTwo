#pragma once

#include "common.h"

class mgCMemory;
class sndCSeSeqData;

enum sndPORT {
    SND_PORT_BGM = 0,
    SND_PORT_OB = 1,
    SND_PORT_BASE = 3,
    SND_PORT_EVENT = 4,
    SND_PORT_ENEMY = 5,
    SND_PORT_SYSTEM = 6,
    SND_PORT_MENU = 8,
    SND_PORT_BGM2 = 11,
    SND_PORT_NUM = 16,
};

enum sndSE_TYPE {
    SND_SE_TYPE_NONE = 0,
    SND_SE_TYPE_KEYON = 1,
    SND_SE_TYPE_SQ = 2,
    SND_SE_TYPE_SESEQ = 3,
};

enum sndSE_CENTER {
    SND_SE_PITCH_CENTER = 0x2000,
};

enum sndSQ_STATE {
    SND_SQ_STATE_STOP = 0,
    SND_SQ_STATE_PLAY = 1,
    SND_SQ_STATE_PAUSE = 2,
    SND_SQ_STATE_PORT_PAUSE = 3,
};

enum sndSTREAM_STATE {
    SND_STREAM_STATE_PLAYING = 0x1000,
};

enum sndREVERB_TYPE {
    SND_REVERB_OFF = 0,
    SND_REVERB_ROOM = 1,
    SND_REVERB_STUDIO_A = 2,
    SND_REVERB_STUDIO_B = 3,
    SND_REVERB_STUDIO_C = 4,
    SND_REVERB_HALL = 5,
    SND_REVERB_SPACE = 6,
    SND_REVERB_ECHO = 7,
    SND_REVERB_DELAY = 8,
    SND_REVERB_PIPE = 9,
    SND_REVERB_MAX = 10,
};

struct SND_LOOP_SE_SEQ {
    u32 se_id;
    s16 keep_time;
    s16 count;
    s16 voice;
    s16 unk_a;
    float vol;
    float pan;

    SND_LOOP_SE_SEQ();
};
STATIC_ASSERT(sizeof(SND_LOOP_SE_SEQ) == 0x14);

class CLoopSeMngr {
public:
    int loop_se_num;
    SND_LOOP_SE_SEQ *loop_se;

    CLoopSeMngr() { Initialize(); }

    int Create(int num, mgCMemory *memory);

    void Initialize();

    void Clear();

    SND_LOOP_SE_SEQ *GetLoopSe(int *found, unsigned int se_id, int voice);

    int SeLoopPlayStop(unsigned int snd_id, int se_no, int keep_time, int voice);

    int SeLoopPlayStop(unsigned int snd_id, int se_no, int keep_time, float vol, float pan, int voice);

    void Step();

    void AllSeStop();
};
STATIC_ASSERT(sizeof(CLoopSeMngr) == 0x8);

struct sndSeInfo {
    int unk_0;
    s8 type;
    s8 prog;
    s8 key;
    s8 unk_7;
    s8 def_vol;
    s8 unk_9[3];

    sndSeInfo();
};
STATIC_ASSERT(sizeof(sndSeInfo) == 0xC);

class sndBankInfo {
public:
    int unk_0;
    int se_num;
    sndSeInfo *se;
    int sq_num;
    char **sq_name;
    int seseq_num;
    sndCSeSeqData *seseq;

    sndBankInfo() {
        seseq_num = 0;
        sq_num = 0;
        se_num = 0;
        se = NULL;
        sq_name = NULL;
        seseq = NULL;
        unk_0 = 0;
    }

    sndSeInfo *GetSe(int se_no) {
        if (se_no < 0 || se_no >= se_num) {
            return NULL;
        }
        return &se[se_no];
    }

    inline sndCSeSeqData *GetSeSeqData(int seseq_no);

    int SearchSeq(char *name, int *index);
};
STATIC_ASSERT(sizeof(sndBankInfo) == 0x1C);

struct sndPortSeSeq {
    s16 seseq_no;
    s16 se_no;
    s8 bank;
    s8 voice;
    s8 unk_6;
    s8 unk_7;

    sndPortSeSeq() { seseq_no = -1; }
};
STATIC_ASSERT(sizeof(sndPortSeSeq) == 0x8);

class sndPortInfo {
public:
    int port;
    int sq_port;
    int bank_num;
    sndBankInfo bank[16];
    u8 unk_1cc[0x40];
    int sq_no;
    int sq_state;
    int sq_vol;
    int sq_se_no;
    sndPortSeSeq seseq[16];

    sndPortInfo() {
        int i;

        port = -1;
        sq_port = -1;
        bank_num = 0;
        sq_no = -1;
        sq_state = SND_SQ_STATE_STOP;
        sq_vol = 0;
        sq_se_no = -1;
        for (i = 0; i < 16; i++) {
            seseq[i].seseq_no = -1;
        }
        for (int j = 0; j < 16; j++) {
            bank[j].seseq_num = 0;
            bank[j].sq_num = 0;
            bank[j].se_num = 0;
            bank[j].se = NULL;
            bank[j].sq_name = NULL;
            bank[j].seseq = NULL;
            bank[j].unk_0 = 0;
        }
    }

    sndBankInfo *GetBank(int bank_no) {
        if (bank_no < 0 || bank_no >= bank_num) {
            return NULL;
        }
        return &bank[bank_no];
    }

    sndPortSeSeq *GetFreeSeSeq() {
        for (int i = 0; i < 16; i++) {
            if (seseq[i].seseq_no < 0) {
                return &seseq[i];
            }
        }
        return NULL;
    }

    sndPortSeSeq *SearchSeSeq(int bank_no, int se_no, int voice) {
        for (int i = 0; i < 16; i++) {
            sndPortSeSeq *entry = &seseq[i];
            if (entry->seseq_no >= 0 && entry->bank == bank_no && entry->se_no == se_no && entry->voice == voice) {
                return entry;
            }
        }
        return NULL;
    }

    void LoadSeInfoTxt(int bank_no, char *text, int size, mgCMemory *memory);

    void LoadVolInfoTxt(int bank_no, char *text, int size);
};
STATIC_ASSERT(sizeof(sndPortInfo) == 0x29C);

int sndGetReverbDepth(int core);

unsigned int sndCreateID(unsigned int snd_id, int se_no);

int sndGetSeNo(unsigned int snd_id);

void sndInitMngr();

void sndWaitSema();

void sndSignalSema();

void sndInitPort(int port_no);

void sndInitSeSeq(int port_no);

void sndSetReverb(int core, int type, int depth);

void sndStopVoice(int voice);

void sndSetMasterVol(int core, float vol);

float sndGetMasterVol(int core);

void sndMasterVolFadeInOut(int core, int frames, float target, float start);

void sndSetPortVol(int port_no, float vol);

float sndGetPortVol(int port_no);

int sndTransBdState();

void sndWaitTransBd();

void sndStep(float frames);

void sndFlush();

void sndSeAllStop(int port_no);

int sndGetSeDefVol(unsigned int snd_id, int se_no);

unsigned int sndLoadSound(int port_no, unsigned int *pack, mgCMemory *memory);

void sndDeletePort(int port_no);

void sndSePlay(unsigned int snd_id, int se_no, int voice);

void sndSePlayV(unsigned int snd_id, int se_no, int vol, int voice);

void sndSePlayVP(unsigned int snd_id, int se_no, int vol, int pan, int voice);

void sndSePlayVPf(unsigned int snd_id, int se_no, float vol, float pan, int voice);

void sndSePlayVf(unsigned int snd_id, int se_no, float vol, int voice);

void sndSePause(unsigned int snd_id, int se_no);

int sndGetSeStatus(unsigned int snd_id, int se_no);

void sndPortSqPause(int port_no);

void sndPortSqReplay(int port_no);

int sndSeCheck(unsigned int snd_id, int se_no);

void sndSePlaySeID(unsigned int snd_id, int se_no, int velocity, int vol, int pan, int pitch, int voice);

void sndSeStop(unsigned int snd_id, int se_no, int voice);

void sndSetSeVol(unsigned int snd_id, int se_no, int vol, int voice);

void sndSetSePan(unsigned int snd_id, int se_no, int pan, int voice);

void sndSetSeVolf(unsigned int snd_id, int se_no, float vol, int voice);

void sndSetSePanf(unsigned int snd_id, int se_no, float pan, int voice);

void sndSetSePitch(unsigned int snd_id, int se_no, int pitch, int voice);

void sndSetMicPos(float *pos, float *dir);

void sndGetVolPan(float *vol, float *pan, float *pos, float near_dist, float far_dist);

void sndGetVolPan(float *vol, float *pan, float *start, float *end, float near_dist, float far_dist);

int sndVolLimit(int vol);

void sndSePlayPrKr(unsigned int snd_id, int prog, int key, int velocity, int vol, int pan, int pitch, int voice);

void sndSeStopPrKr(unsigned int snd_id, int prog, int key, int voice);

void sndSetSeVolPrKr(unsigned int snd_id, int prog, int key, int vol, int voice);

void sndSetSePanPrKr(unsigned int snd_id, int prog, int key, int pan, int voice);

void sndSetSePitchPrKr(unsigned int snd_id, int prog, int key, int pitch, int voice);

void sndSePlayPBPrKr(int port, int bank, int prog, int key, int velocity, int vol, int pan, int pitch, int voice);

void sndSeStopPBPrKr(int port, int bank, int prog, int key, int voice);

void sndSetSeVolPBPrKr(int port, int bank, int prog, int key, int vol, int voice);

void sndSetSePanPBPrKr(int port, int bank, int prog, int key, int pan, int voice);

void sndSetSePitchPBPrKr(int port, int bank, int prog, int key, int pitch, int voice);

void sndSqPlay(int port, int sq_no, int vol);

void sndSqStop(int port, int sq_no);

void sndSetSqVol(int port, int sq_no, int vol);

void sndSqRePlay(int port, int sq_no);

void sndStopSeSeq(int port_no);

void sndStreamOpenFast(char *name);

int sndStreamOpenState();

void sndStreamStandBy();

void sndStreamSetVol(float left, float right);

void sndStreamPlay();

void sndStreamPause();

void sndStreamRePlay();

int sndStreamGetState();

void sndStreamClose();
