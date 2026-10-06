#pragma once

#include "common.h"

#include <libvu0.h>

enum SceneSeqResult {
    SCENE_SEQ_NEXT = 0,
    SCENE_SEQ_WAIT = 1,
    SCENE_SEQ_RETURN = 2,
};

enum SceneSeqEase {
    SCENE_SEQ_EASE_IN_OUT = 0,
    SCENE_SEQ_EASE_IN = 1,
    SCENE_SEQ_EASE_OUT = 2,
};

enum SceneCmrSeqTrack {
    SCENE_CMR_TRACK_PR = 0,
    SCENE_CMR_TRACK_AHD = 1,
    SCENE_CMR_TRACK_FADE = 2,
    SCENE_CMR_TRACK_QUAKE = 3,
    SCENE_CMR_TRACK_CHARA = 4,
    SCENE_CMR_TRACK_NUM = 5,
};

enum SceneCmrSeqCmd {
    SCENE_CMR_CMD_NONE = 0,
    SCENE_CMR_CMD_PR_DELAY = 1,
    SCENE_CMR_CMD_SET_POS = 2,
    SCENE_CMR_CMD_SET_REF = 3,
    SCENE_CMR_CMD_MOVE = 4,
    SCENE_CMR_CMD_MOVE2 = 5,
    SCENE_CMR_CMD_MOVE_REF = 6,
    SCENE_CMR_CMD_MOVE_POS = 7,
    SCENE_CMR_CMD_INIT_PAS = 8,
    SCENE_CMR_CMD_SET_PAS_FRM = 9,
    SCENE_CMR_CMD_ADD_PAS = 10,
    SCENE_CMR_CMD_START_PAS = 11,
    SCENE_CMR_CMD_PR_SLOWING = 12,
    SCENE_CMR_CMD_PR_KEEP = 13,
    SCENE_CMR_CMD_PR_RETURN = 14,
    SCENE_CMR_CMD_AHD_DELAY = 15,
    SCENE_CMR_CMD_SET_ANGLE = 16,
    SCENE_CMR_CMD_SET_HEIGHT = 17,
    SCENE_CMR_CMD_SET_DIST = 18,
    SCENE_CMR_CMD_SET_AHD = 19,
    SCENE_CMR_CMD_MOVE_AHD = 20,
    SCENE_CMR_CMD_MOVE_AHD2 = 21,
    SCENE_CMR_CMD_SET_SYNC_OBJ = 22,
    SCENE_CMR_CMD_RELEASE_SYNC_OBJ = 23,
    SCENE_CMR_CMD_AHD_SLOWING = 24,
    SCENE_CMR_CMD_AHD_KEEP = 25,
    SCENE_CMR_CMD_AHD_RETURN = 26,
    SCENE_CMR_CMD_FADE_DELAY = 27,
    SCENE_CMR_CMD_FADE_INIT = 28,
    SCENE_CMR_CMD_FADE_IN = 29,
    SCENE_CMR_CMD_FADE_OUT = 30,
    SCENE_CMR_CMD_QUAKE_DELAY = 31,
    SCENE_CMR_CMD_QUAKE = 32,
    SCENE_CMR_CMD_QUAKE2 = 33,
    SCENE_CMR_CMD_CHARA_DELAY = 34,
    SCENE_CMR_CMD_CHARA_ATTACH = 35,
    SCENE_CMR_CMD_NUM = 36,
};

enum SceneCmrSyncMode {
    SCENE_CMR_SYNC_FIXED = 0,
    SCENE_CMR_SYNC_YAW = 1,
    SCENE_CMR_SYNC_FRAME = 2,
};

enum SceneObjSeqTrack {
    SCENE_OBJ_TRACK_POS = 0,
    SCENE_OBJ_TRACK_ROT = 1,
    SCENE_OBJ_TRACK_MOT = 2,
    SCENE_OBJ_TRACK_ANM = 3,
    SCENE_OBJ_TRACK_COL = 4,
    SCENE_OBJ_TRACK_SCALE = 5,
    SCENE_OBJ_TRACK_SE = 6,
    SCENE_OBJ_TRACK_NUM = 7,
};

enum SceneObjSeqCmd {
    SCENE_OBJ_CMD_NONE = 0,
    SCENE_OBJ_CMD_POS_DELAY = 1,
    SCENE_OBJ_CMD_SET_POS = 2,
    SCENE_OBJ_CMD_MOVE = 3,
    SCENE_OBJ_CMD_MOVE2 = 4,
    SCENE_OBJ_CMD_INIT_PAS = 5,
    SCENE_OBJ_CMD_SET_PAS_FRM = 6,
    SCENE_OBJ_CMD_ADD_PAS = 7,
    SCENE_OBJ_CMD_START_PAS = 8,
    SCENE_OBJ_CMD_JUMP = 9,
    SCENE_OBJ_CMD_SET_EOH_FRAME_POS = 10,
    SCENE_OBJ_CMD_ADD_POS = 11,
    SCENE_OBJ_CMD_ATTACH_CAMERA = 12,
    SCENE_OBJ_CMD_ROT_DELAY = 13,
    SCENE_OBJ_CMD_SET_ROT = 14,
    SCENE_OBJ_CMD_ROTATION = 15,
    SCENE_OBJ_CMD_ROTATION2 = 16,
    SCENE_OBJ_CMD_REFERENCE = 17,
    SCENE_OBJ_CMD_MOTION_DELAY = 18,
    SCENE_OBJ_CMD_SET_MOTION = 19,
    SCENE_OBJ_CMD_NEXT_MOTION = 20,
    SCENE_OBJ_CMD_MOTION_WAIT = 21,
    SCENE_OBJ_CMD_MOTION_TRG = 22,
    SCENE_OBJ_CMD_MOTION_TRG_WAIT = 23,
    SCENE_OBJ_CMD_SET_MOT_STEP = 24,
    SCENE_OBJ_CMD_SET_MOT_CHANGE_STEP = 25,
    SCENE_OBJ_CMD_RESET_MOTION = 26,
    SCENE_OBJ_CMD_SET_MOTION_NOW_TIME = 27,
    SCENE_OBJ_CMD_SET_MOTION_WAIT_TIME = 28,
    SCENE_OBJ_CMD_NORMAL_DRIVE = 29,
    SCENE_OBJ_CMD_TEX_ANIME_DELAY = 30,
    SCENE_OBJ_CMD_TEX_ANIME = 31,
    SCENE_OBJ_CMD_COLOR_DELAY = 32,
    SCENE_OBJ_CMD_SET_COLOR = 33,
    SCENE_OBJ_CMD_SCALE_DELAY = 34,
    SCENE_OBJ_CMD_SET_SCALE = 35,
    SCENE_OBJ_CMD_SE_DELAY = 36,
    SCENE_OBJ_CMD_SE_PLAY = 37,
    SCENE_OBJ_CMD_RESET_DA_POSITION = 38,
    SCENE_OBJ_CMD_NUM = 39,
};

struct SPLINE_KEY {
    int frame;
    int length;
    float a[3];
    float b[3];
    float c[3];
    float d[3];
};
STATIC_ASSERT(sizeof(SPLINE_KEY) == 0x38);

class C3DSpline {
public:
    SPLINE_KEY key[16];
    int key_num;
    int now_key;
    float now_frame;
    float now_pos[3];
    float speed;

    C3DSpline();

    void Initialize();

    void SetUpSpline(float (*points)[4], int *frames, int num, float speed);

    int StepS();

    int Step();

    void GetNowXYZ(float *pos);
};
STATIC_ASSERT(sizeof(C3DSpline) == 0x39C);

class CCameraPas {
public:
    sceVu0FVECTOR pos[16];
    sceVu0FVECTOR ref[16];
    int pas_num;
    int frame;
    C3DSpline pos_spline;
    C3DSpline ref_spline;
    int run;

    CCameraPas();

    int AddCameraPas(float *pos, float *ref);

    int InsCameraPas(int no, float *pos, float *ref);

    int SetCameraPas(int no, float *pos, float *ref);

    int GetCameraPas(int no, float *pos, float *ref);

    int DelCameraPas(int no);

    int SetFrame(int frame);

    int GetFrame();

    void Initialize();

    int Setup();

    void Run();

    void Step(float *pos, float *ref);

    int CheckEnd();
};
STATIC_ASSERT(sizeof(CCameraPas) == 0x950);

class CCharaPas {
public:
    sceVu0FVECTOR pos[16];
    int frame;
    int pas_num;
    C3DSpline spline;
    int run;
    int end;

    CCharaPas();

    void Initialize();

    int AddCharaPas(float *pos);

    int Setup();

    void Run();

    void Step(float *pos, float *rot_y);

    int CheckEnd();

    int InsCharaPas(int no, float *pos);

    int SetCharaPas(int no, float *pos);

    int GetCharaPas(int no, float *pos);

    int DelCharaPas(int no);

    void SetFrame(int frame);

    int GetFrame();
};
STATIC_ASSERT(sizeof(CCharaPas) == 0x4B0);

struct _SEN_CMR_SEQ {
    int cmd;
    s32 unk_4;
    s32 unk_8;
    s32 unk_c;
    sceVu0FVECTOR vec0;
    sceVu0FVECTOR vec1;
    union {
        int frame;
        float value;
        int no;
    };
    union {
        int mode;
        int slow_frame;
        float dist;
    };
    union {
        float ease_rate;
        int attach_frame;
    };
    char name[0x20];
    _SEN_CMR_SEQ *next;
};
STATIC_ASSERT(sizeof(_SEN_CMR_SEQ) == 0x60);

struct _SEN_OBJ_SEQ {
    int cmd;
    s32 unk_4;
    s32 unk_8;
    s32 unk_c;
    sceVu0FVECTOR vec;
    union {
        int frame;
        float value;
        int no;
        int grounded;
    };
    union {
        int mode;
        int sub_frame;
        float step;
        int se_no;
    };
    union {
        float ease_rate;
        int started;
    };
    char name[0x20];
    _SEN_OBJ_SEQ *next;
};
STATIC_ASSERT(sizeof(_SEN_OBJ_SEQ) == 0x50);

class CSceneCmrSeq {
public:
    _SEN_CMR_SEQ *seq_tbl;
    int seq_num;
    _SEN_CMR_SEQ *pr_seq;
    _SEN_CMR_SEQ *pr_last;
    _SEN_CMR_SEQ *ahd_seq;
    _SEN_CMR_SEQ *ahd_last;
    _SEN_CMR_SEQ *fade_seq;
    _SEN_CMR_SEQ *fade_last;
    _SEN_CMR_SEQ *quake_seq;
    _SEN_CMR_SEQ *quake_last;
    _SEN_CMR_SEQ *chara_seq;
    _SEN_CMR_SEQ *chara_last;
    _SEN_CMR_SEQ *pr_keep;
    _SEN_CMR_SEQ *ahd_keep;
    int pr_cnt;
    int ahd_cnt;
    int fade_cnt;
    int quake_cnt;
    int chara_cnt;
    s32 unk_4c;
    sceVu0FVECTOR pos;
    sceVu0FVECTOR ref;
    float angle;
    float height;
    float dist;
    int sync;
    int sync_obj;
    int sync_mode;
    s32 unk_88;
    s32 unk_8c;
    sceVu0FVECTOR sync_ofs;
    float sync_angle;
    float sync_height;
    float sync_dist;
    char sync_frame[0x20];
    s32 unk_cc;
    sceVu0FVECTOR pos_spd;
    sceVu0FVECTOR ref_spd;
    float angle_spd;
    s32 unk_f4;
    float height_spd;
    float dist_spd;
    sceVu0FVECTOR pos_ease_spd;
    sceVu0FVECTOR ref_ease_spd;
    sceVu0FVECTOR pos_ease_acc;
    sceVu0FVECTOR ref_ease_acc;
    int ease_frame;
    s32 unk_144;
    s32 unk_148;
    s32 unk_14c;
    sceVu0FVECTOR pos_vel;
    sceVu0FVECTOR ref_vel;
    sceVu0FVECTOR ahd_vel;
    int quake;
    s32 unk_184;
    s32 unk_188;
    s32 unk_18c;
    sceVu0FVECTOR quake_amp;
    sceVu0FVECTOR quake_pos;
    sceVu0FVECTOR quake_ref;
    CCameraPas pas;

    CSceneCmrSeq();

    void ZeroInitialize();

    void Initialize(_SEN_CMR_SEQ *seq_tbl, int seq_num);

    void Clear();

    int CheckEnd();

    void Play();

    _SEN_CMR_SEQ *SearchSeq();

    _SEN_CMR_SEQ *SearchNextPrSeq();

    _SEN_CMR_SEQ *SearchNextAhdSeq();

    _SEN_CMR_SEQ *SearchNextFadeSeq();

    _SEN_CMR_SEQ *SearchNextQuakeSeq();

    _SEN_CMR_SEQ *SearchNextCharaSeq();

    _SEN_CMR_SEQ *GetNextSeq(_SEN_CMR_SEQ *seq, int track);

    void PRDelay(int frame);

    void SetPos(float *pos);

    void SetRef(float *ref);

    void Move(float *pos, float *ref, int frame);

    void Move2(float *pos, float *ref, int frame, int ease, float ease_rate);

    void MoveRef(float *ref, int frame);

    void MovePos(float *pos, int frame);

    void InitPas();

    void SetPasFrm(int frame);

    void AddPas(float *pos, float *ref);

    void StartPas();

    void PRSlowing(float rate, int frame);

    void PRKeep();

    void PRReturn();

    void AHDDelay(int frame);

    void SetAngle(float angle);

    void SetHeight(float height);

    void SetDist(float dist);

    void SetAHD(float angle, float height, float dist);

    void MoveAHD(float angle, float height, float dist, int frame);

    void MoveAHD2(float angle, float height, float dist, int frame, int ease, float ease_rate);

    void SetSyncObj(int obj, float *ofs, float angle, float height, float dist, int mode, char *frame_name);

    void ReleaseSyncObj();

    void AHDSlowing(float rate, int frame);

    void AHDKeep();

    void AHDReturn();

    void FadeDelay(int frame);

    void FadeInit();

    void FadeIn(int frame, float r, float g, float b);

    void FadeOut(int frame, float r, float g, float b);

    void QuakeDelay(int frame);

    void Quake(float *amp, int frame);

    void Quake2(float *amp, int frame);

    void CharaDelay(int frame);

    void CharaAttach(int chara_no, float dist, int frame);
};
STATIC_ASSERT(sizeof(CSceneCmrSeq) == 0xB10);

class CSceneObjSeq {
public:
    _SEN_OBJ_SEQ *seq_tbl;
    int seq_num;
    _SEN_OBJ_SEQ *pos_seq;
    _SEN_OBJ_SEQ *pos_last;
    _SEN_OBJ_SEQ *rot_seq;
    _SEN_OBJ_SEQ *rot_last;
    _SEN_OBJ_SEQ *mot_seq;
    _SEN_OBJ_SEQ *mot_last;
    _SEN_OBJ_SEQ *anm_seq;
    _SEN_OBJ_SEQ *anm_last;
    _SEN_OBJ_SEQ *col_seq;
    _SEN_OBJ_SEQ *col_last;
    _SEN_OBJ_SEQ *scale_seq;
    _SEN_OBJ_SEQ *scale_last;
    _SEN_OBJ_SEQ *se_seq;
    _SEN_OBJ_SEQ *se_last;
    int pos_cnt;
    int rot_cnt;
    int mot_cnt;
    int anm_cnt;
    int col_cnt;
    int scale_cnt;
    int se_cnt;
    s32 unk_5c;
    s32 unk_60;
    int eoh_no;
    s32 unk_68;
    s32 unk_6c;
    sceVu0FVECTOR pos;
    sceVu0FVECTOR rot;
    sceVu0FVECTOR pos_spd;
    sceVu0FVECTOR rot_spd;
    sceVu0FVECTOR pos_ease_spd;
    sceVu0FVECTOR rot_ease_spd;
    sceVu0FVECTOR pos_ease_acc;
    sceVu0FVECTOR rot_ease_acc;
    int pos_ease_frame;
    int rot_ease_frame;
    s32 unk_f8;
    s32 unk_fc;
    sceVu0FVECTOR jump_start;
    sceVu0FVECTOR jump_end;
    sceVu0FVECTOR color_spd;
    sceVu0FVECTOR scale_spd;
    CCharaPas pas;

    CSceneObjSeq();

    void ZeroInitialize();

    void Initialize(_SEN_OBJ_SEQ *seq_tbl, int seq_num);

    void Clear();

    void SetEohNo(int eoh_no);

    _SEN_OBJ_SEQ *SearchSeq();

    _SEN_OBJ_SEQ *GetNextSeq(_SEN_OBJ_SEQ *seq);

    _SEN_OBJ_SEQ *SearchNextPosSeq();

    _SEN_OBJ_SEQ *SearchNextRotSeq();

    _SEN_OBJ_SEQ *SearchNextMotSeq();

    _SEN_OBJ_SEQ *SearchNextAnmSeq();

    _SEN_OBJ_SEQ *SearchNextColSeq();

    _SEN_OBJ_SEQ *SearchNextScaleSeq();

    _SEN_OBJ_SEQ *SearchNextSeSeq();

    int CheckEnd();

    void Play();

    void PosDelay(int frame);

    void SetPos(float *pos);

    void Move(float *pos, int frame, int ground);

    void Move2(float *pos, int frame, int ease, float ease_rate);

    void InitPas();

    void SetPasFrm(int frame);

    void AddPas(float *pos);

    void StartPas(int ground);

    void Jump(float *pos, float height, int frame);

    void SetEohFramePos(int eoh_no, char *frame_name, int frame, float *ofs);

    void AddPos(float *add, int frame);

    void AttachCamera(float dist, int frame);

    void RotDelay(int frame);

    void SetRot(float *rot);

    void Rotation(float *rot, int frame);

    void Rotation2(float *rot, int frame, int ease, float ease_rate);

    void Reference(float *pos, int frame);

    void MotionDelay(int frame);

    void SetMotion(char *name, int flags, float step);

    void NextMotion(char *name, int flags, float step);

    void MotionWait();

    void SetMotionTrg();

    void MotionTrgWait();

    void SetStep(float step);

    void SetChengeStep(float step);

    void ResetMotion();

    void SetMotionNowTime(float time);

    void SetMotionWaitTime(float time);

    void NormalDrive();

    void TexAnimeDelay(int frame);

    void TexAnime(char *name, int on);

    void ColorDelay(int frame);

    void SetColor(float *color, int frame);

    void ScaleDelay(int frame);

    void SetScale(float *scale, int frame);

    void SeDelay(int frame);

    void SePlay(int snd_id, int se_no);

    void ResetDAPosition();
};
STATIC_ASSERT(sizeof(CSceneObjSeq) == 0x5F0);

void InitSceneCmrSeq(_SEN_CMR_SEQ *seq);
void InitSceneObjSeq(_SEN_OBJ_SEQ *seq);
