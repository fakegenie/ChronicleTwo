#pragma once

#include "common.h"

#include <libvu0.h>

#include "effect.hpp"
#include "gameutil.hpp"
#include "object.hpp"

class CDynamicAnime;
class CEffectManager;
class CLoopSeMngr;
class COutLineDraw;
class CSWordAfterEffect;
class mgCFrame;
class mgCMemory;
struct mgIMG_FILE_HEADER;

#define CHARA_MOTION_SET_MAX 8
#define CHARA_ENTRY_OBJECT_MAX 24
#define CHARA_ENTRY_FRAME_MAX 2
#define CHARA_IMAGE_MAX 6
#define CHARA_DEFORM_FRAME_MAX 24
#define CHARA_SWORD_EFFECT_MAX 3
#define CHARA_ENTRY_EFFECT_MAX 8

enum CharaMotionFlag {
    CHARA_MOTION_PAUSE   = 1 << 0,
    CHARA_MOTION_HOLD    = 1 << 1,
    CHARA_MOTION_RESTART = 1 << 2,
};

enum CharaMotionStatus {
    CHARA_MOTION_STATUS_NONE  = 0,
    CHARA_MOTION_STATUS_START = 1,
    CHARA_MOTION_STATUS_PLAY  = 2,
    CHARA_MOTION_STATUS_BLEND = 3,
    CHARA_MOTION_STATUS_END   = 4,
};

enum CharaSeqState {
    CHARA_SEQ_STATE_NONE  = 0,
    CHARA_SEQ_STATE_START = 1,
    CHARA_SEQ_STATE_PLAY  = 2,
    CHARA_SEQ_STATE_WAIT  = 3,
    CHARA_SEQ_STATE_END   = 4,
};

enum ChrInfoSeqType {
    CHRINFO_SEQ_ONCE      = 0,
    CHRINFO_SEQ_LOOP      = 1,
    CHRINFO_SEQ_HOLD_WAIT = 2,
    CHRINFO_SEQ_WAIT      = 3,
    CHRINFO_SEQ_LOOP_WAIT = 7,
};

enum ChrInfoSeKind {
    CHRINFO_SE_FOOT_0      = 0,
    CHRINFO_SE_FOOT_1      = 1,
    CHRINFO_SE_SOUND       = 2,
    CHRINFO_SE_SOUND_2     = 3,
    CHRINFO_SE_SOUND_FOOT  = 4,
};

enum CharaDynamicAnimeFlag {
    CHARA_DYNAMIC_ANIME_DISABLE = 1 << 0,
};

struct CHRINFO_KEY_SET {
    char  name[0x24];
    s32   start_frame;
    s32   end_frame;
    float step;
};

STATIC_ASSERT(sizeof(CHRINFO_KEY_SET) == 0x30);

struct CHRINFO_SEQ {
    char  name[0x22];
    u8    type;
    u8    unk_23;
    s32   loop_count;
    float blend_speed;
};

STATIC_ASSERT(sizeof(CHRINFO_SEQ) == 0x2C);

struct CHRINFO_SEQ_HEADER {
    char                name[0x24];
    CHRINFO_SEQ        *seq;
    CHRINFO_SEQ_HEADER *next;
    s32                 seq_num;
};

STATIC_ASSERT(sizeof(CHRINFO_SEQ_HEADER) == 0x30);

struct CHRINFO_SE {
    float frame;
    float end_frame;
    s16   loop_slot;
    s16   kind;
    s16   se_no;
    s16   wait;
};

STATIC_ASSERT(sizeof(CHRINFO_SE) == 0x10);

struct CHARA_EFFECT_MANAGER : public CEffectManager {
    CEffectCtrl  *emitter_pool;
    u32           unk_188;
    CEffect      *particle_pool;
    u32           unk_190;
    u32           unk_194;
    s32           local_draw;
    char          frame_name[32];
    char          motion_name[32];
    float         start_ratio;
    sceVu0FVECTOR offset;
};

STATIC_ASSERT(sizeof(CHARA_EFFECT_MANAGER) == 0x1F0);

struct CHRINFO_EFFECT {
    char            name[0x20];
    CHARA_EFFECT_MANAGER *effect;
    CHRINFO_EFFECT *next;
};

STATIC_ASSERT(sizeof(CHRINFO_EFFECT) == 0x28);

struct CHRINFO_EFFECT_IMAGE {
    u8                   *data;
    char                  name[0x20];
    CHRINFO_EFFECT_IMAGE *next;
};

STATIC_ASSERT(sizeof(CHRINFO_EFFECT_IMAGE) == 0x28);

struct CHARA_ENTRY_OBJECT {
    mgCFrame *frame;
    float     unk_04;
    s32       group;
    s32       enable;
};

STATIC_ASSERT(sizeof(CHARA_ENTRY_OBJECT) == 0x10);

struct CHARA_ENTRY_EFFECT {
    CHARA_EFFECT_MANAGER *effect;
    s32             active;
    s32             running;
};

STATIC_ASSERT(sizeof(CHARA_ENTRY_EFFECT) == 0xC);

class CCharaFrameMatching {
public:
    s32  num;
    s32 *src_frame;
    s32 *dst_frame;

    CCharaFrameMatching() {}

    void Initialize() {
        num = 0;
        dst_frame = 0;
        src_frame = 0;
    }
};

STATIC_ASSERT(sizeof(CCharaFrameMatching) == 0xC);

struct CHARA_SOUND_INFO {
    u32          foot_se_bank;
    s32          foot_sound_id;
    s32          foot_sound_enable;
    u32          se_bank;
    u32          se_bank_2;
    s32          se_positional;
    float        se_volume;
    float        se_pan;
    s32          foot_effect_wait;
    CLoopSeMngr *loop_se;
};

STATIC_ASSERT(sizeof(CHARA_SOUND_INFO) == 0x28);

class CCharaLOD {
public:
    float     distance;
    s32       motion;
    s32       standalone;
    mgCFrame *frame;
    s32       link_num;
    s32     (*link)[2];

    CCharaLOD();
};

STATIC_ASSERT(sizeof(CCharaLOD) == 0x18);

class CCharacter2 : public CObjectFrame {
public:
    sceVu0FVECTOR         velocity;
    sceVu0FVECTOR         base_scale;
    float                 move_accel;
    sceVu0FMATRIX         entry_matrix;
    char                  name[0x10];
    float                 alpha;
    s32                   poly_num;
    s32                   shadow_poly_num;
    float                 body_width;
    float                 body_height;

    float GetBodyWidth() {
        return body_width;
    }

    float GetBodyHeight() {
        return body_height;
    }
    float                 body_depth;
    s32                   load_size;
    s32                   copy_size;
    s16                   dynamic_anime_flags;
    COutLineDraw         *outline;
    s32                   outline_tex_no;
    s32                   dynamic_anime_num;
    CDynamicAnime        *dynamic_anime;
    s32                   shape_anime;
    mgCFrame             *entry_frame[CHARA_ENTRY_FRAME_MAX];
    CHARA_ENTRY_OBJECT    entry_object[CHARA_ENTRY_OBJECT_MAX];
    mgCFrame             *shadow_frame;
    mgIMG_FILE_HEADER    *images[CHARA_IMAGE_MAX];
    s32                   tex_anime_group_num;
    s32                   tex_anime_group_start;
    s32                   texture_block;
    mgCFrame             *deform_frame[CHARA_DEFORM_FRAME_MAX];
    s32                   deform_frame_num;
    s32                   lod_num;
    CCharaLOD            *lod;
    s32                   lod_no;
    s32                   motion_enable;
    CCharaFrameMatching   shadow_link;
    CHRINFO_KEY_SET      *next_key;
    s32                   next_flags;
    s32                   next_set;
    CHRINFO_KEY_SET      *now_key;
    s32                   seq_mode;
    s32                   now_flags;
    s32                   now_set;
    s32                   motion_status;
    float                 frame;
    float                 frame_ratio;
    float                 step;
    CHRINFO_KEY_SET      *posed_key;
    s32                   prev_flags;
    s32                   prev_set;
    float                 prev_frame;
    CHRINFO_SEQ_HEADER   *next_seq;
    CHRINFO_SEQ_HEADER   *now_seq;
    CHRINFO_SEQ          *seq_step;
    s32                   seq_flags;
    s32                   seq_loop;
    s32                   seq_state;
    s32                   seq_advance;
    tagMOTION_TYPE        motion[CHARA_MOTION_SET_MAX];
    tagMOTION_TYPE        shadow_motion[CHARA_MOTION_SET_MAX];
    s32                   main_frame_info;
    tagFRAME_INF         *shadow_frame_info;
    float                 blend;
    float                 blend_speed;
    CHRINFO_KEY_SET      *key_list[CHARA_MOTION_SET_MAX];
    s32                   key_num[CHARA_MOTION_SET_MAX];
    CHRINFO_SEQ_HEADER   *seq_list[CHARA_MOTION_SET_MAX];
    CSWordAfterEffect    *sword_effect[CHARA_SWORD_EFFECT_MAX];
    CHARA_SOUND_INFO      sound_info;
    CHRINFO_SE           *se_list[CHARA_MOTION_SET_MAX];
    s32                   se_num[CHARA_MOTION_SET_MAX];
    s32                   effect_image_load;
    CHRINFO_EFFECT       *effect_list;
    CHARA_ENTRY_EFFECT    entry_effect[CHARA_ENTRY_EFFECT_MAX];
    CHRINFO_EFFECT_IMAGE *effect_image_list;
    s32                   effect_enable;

    CCharacter2() {
        shadow_link.Initialize();
        Initialize();
    }

    virtual void SetPosition(float *position);

    virtual void SetPosition(float x, float y, float z);

    virtual int Draw();

    virtual int DrawDirect();

    virtual void Initialize();

    virtual float GetCameraDist();

    virtual void DrawStep();

    virtual void LoadPack(unsigned int *pack, char *name, mgCMemory *model_stack, mgCMemory *motion_stack, mgCMemory *image_stack, int image_block, CCharacter2 *parent);

    virtual void LoadPackNoLine(unsigned int *pack, char *name, mgCMemory *model_stack, mgCMemory *motion_stack, mgCMemory *image_stack, int image_block, CCharacter2 *parent);

    virtual void LoadChrFile(unsigned int *pack, char *name, mgCMemory *model_stack, mgCMemory *motion_stack, mgCMemory *image_stack, int image_block, CCharacter2 *parent, int outline);

    virtual int GetMotionStatus() {
        return motion_status;
    }

    virtual char *GetNowMotionName() {
        if (now_key != NULL) {
            return now_key->name;
        }
        return NULL;
    }

    virtual int CheckMotionEnd();

    virtual float GetNowFrameWait() {
        return frame_ratio;
    }

    virtual float GetChgStepWait();

    virtual void SetNowFrame(float now_frame) {
        frame = now_frame;
    }

    virtual void SetNowFrameWeight(float weight);

    virtual float GetNowFrame() {
        return frame;
    }

    virtual float GetWaitToFrame(char *name, float ratio);

    virtual void SetMotion(int no, int flags);

    virtual void SetMotion(char *name, int flags);

    virtual void ResetMotion();

    virtual void SetStep(float frame_step);

    virtual float GetStep() {
        return step;
    }

    virtual float GetDefaultStep();

    virtual void SetFadeFlag(int fade_flag) {
        fade = fade_flag;
    }

    virtual int GetFadeFlag() {
        return fade;
    }

    virtual int DrawShadowDirect();

    virtual void NormalDrive();

    virtual void Step();

    virtual void ShadowStep();

    virtual void SetWind(float power, float *dir);

    virtual void ResetWind();

    virtual void SetFloor(float y);

    virtual void ResetFloor();

    virtual void Copy(CCharacter2 &dest, mgCMemory *memory);

    virtual int GetCopySize() {
        if (copy_size > 0) {
            return copy_size;
        }
        return load_size;
    }

    virtual void DrawEffect();

    void AddOutLine(char *frame_name, COutLineDraw *outline);

    void CopyOutLine(CCharacter2 *source);

    void SetDeformMesh();

    void UpdatePosition();

    void ResetDAPosition();

    void SetMotionPara(char *name, int flags, int keep_seq);

    void SetDAnimeEnable(int enable);

    CHRINFO_SE *GetSoundInfoCopy(mgCMemory *memory);

    int CheckFootEffect();

    void SePlay();

    void StepDA(int count);

    CHRINFO_KEY_SET *GetKeyListIndexPtr(int no, int *out_set);

    CHRINFO_KEY_SET *GetKeyListPtr(char *name, int *out_set);

    CHRINFO_SEQ_HEADER *GetSeqHeaderPtr(char *name, int *out_set);

    void DeleteExtMotion();

    void DeleteImage();

    int GetEntryObjectPos(int no, float *out_position);

    int GetEntryObjectPos(int no, float (*out_matrix)[4]);

    CHARA_ENTRY_OBJECT *GetEntryObjectPos(int group, int no, float *out_position);

    void LoadSkin(unsigned int *pack, char *name, char *skin_name, mgCMemory *stack, int image_block);

    void InitEffect();

    void ExecEntryEffect(CHRINFO_KEY_SET *key);

    void CtrlEffect();

    void StepEffect();

    mgCFrame *ChangeLOD(int no);
};

STATIC_ASSERT(sizeof(CCharacter2) == 0x660);
