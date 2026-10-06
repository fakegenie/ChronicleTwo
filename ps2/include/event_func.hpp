#pragma once

#include "common.h"

#include <libvu0.h>

#include "dng_effect.hpp"
#include "runscript.hpp"
#include "scenesnd.hpp"
#include "sceneseq.hpp"

class CCharacter2;
class CEventSprite2;
class CEventSpriteMother;
class CFuncPoint;
class CMapParts;
class CMarker;
class CObject;
class CRain;
class mgCCamera;
class mgCFrame;
class mgCMemory;
class mgCTexture;
class ClsMes;

enum EOH_TYPE {
    EOH_TYPE_NONE = -1,
    EOH_TYPE_CHARA = 0,
    EOH_TYPE_OBJECT = 1,
    EOH_TYPE_SPRITE = 2,
    EOH_TYPE_FRAME = 3,
    EOH_TYPE_FUNC_POINT = 4,
};

#define EOH_NUM 32

enum RASTER_STATE {
    RASTER_OFF = 0,
    RASTER_START = 1,
    RASTER_ON = 2,
    RASTER_STOP = 3,
};

#define EVENT_CAPTION_NUM 18

struct ED_EVENT_INFO {
    sceVu0FVECTOR world_coord_pos;
    sceVu0FVECTOR world_coord_rot;
    float projection;
    u8 unk_24[0x40];
    int jump_point;
    char jump_map_name[0x20];
    int event_no;
    char script_name[0x40];
    int request;
    int command_mode;
    int skip_state;
    int skip_button;
    s32 unk_dc;
    float skip_fade_color[4];
    int start_button;
    int snd_id[12];
    int last_snd_id;
    s32 unk_128;
    float env_bgm_volume;
    int env_bgm_no;
    int stream_playing;
    int stream_from_fpl;
    int func_iparam[16];
    float func_fparam[16];
    int monster_talk[3];
    int door_type;
    int interior_entrance;
    u64 stopwatch_start;
    s64 stopwatch_limit;
    int stopwatch_x;
    int stopwatch_y;
    int stopwatch_style;
    CMapParts *dng_event_parts;
    int dng_event_found;
    int pack_loaded;
    int map_draw;
    int stream_reading;
    int stream_volume;
    int caption_enable;
    int caption_start[EVENT_CAPTION_NUM];
    int caption_frames[EVENT_CAPTION_NUM];
    char caption_text[EVENT_CAPTION_NUM][0xE1];
    u8 unk_126a[0x2];
    char *npc_talk_text;
    int npc_talk_size;
    CScene::BGM_STATUS bgm_status;
    float keep_time;
    u8 unk_1294[0xC];
};

STATIC_ASSERT(sizeof(ED_EVENT_INFO) == 0x12A0);

class CEoh {
public:
    int type;
    int scene_no;
    int world_coord;

    union {
        CCharacter2 *chara;
        CObject *object;
        CEventSprite2 *sprite;
        mgCFrame *frame;
        CFuncPoint *func_point;
    };

    CEoh();

    int Set(int type, CObject *object, int world_coord);

    int Set(int type, int scene_no, CCharacter2 *chara);

    int Set(int type, CEventSprite2 *sprite);

    int Set(int type, mgCFrame *frame);

    int Set(int type, CFuncPoint *func_point);
};

STATIC_ASSERT(sizeof(CEoh) == 0x10);

class CEohMother {
public:
    CEoh eoh[EOH_NUM];

    CEohMother();

    int Set(int no, int type, CObject *object, int world_coord);

    int Set(int no, int type, int scene_no, CCharacter2 *chara);

    int Set(int no, int type, CEventSprite2 *sprite);

    int Set(int no, int type, mgCFrame *frame);

    int Set(int no, int type, CFuncPoint *func_point);

    int SetPos(int no, float x, float y, float z);

    int SetRot(int no, float x, float y, float z);

    int GetPos(int no, float *pos);

    int GetRot(int no, float *rot);

    int SetMotion(int no, char *name, int flag, float time);

    int CheckMotionEnd(int no);

    int SetMotionTrg(int no);

    int GetSeqStatus(int no);

    int SetStep(int no, float step);

    int SetChangeStep(int no, float step);

    int ResetMotion(int no);

    int SetTexAnim(int no, int on, char *name);

    int SetScale(int no, float x, float y, float z);

    int GetScale(int no, float *scale);

    int SetShow(int no, int show);

    int GetShow(int no, int *show);

    mgCFrame *SearchFrame(int no, char *name);

    int SetFrameShow(int no, char *name, int show);

    int SetShadow(int no, int on);

    int SetShadowFrameShow(int no, char *name, int show);

    int SetTranslate(int no, float *translate);

    int SetColor(int no, float *color);

    int GetColor(int no, float *color);

    char *GetNowMotionName(int no);

    int GetNowMotionStatus(int no);

    int SetMotionNowTime(int no, float time);

    int SetMotionWaitTime(int no, float rate);

    int SetFootSoundID(int no, int id);

    int GetFramePos(int no, char *name, float *pos);

    int SetSoundID(int no, unsigned int id);

    int GetFrameShow(int no, char *name);

    int SetFadeFlag(int no, int flag);

    int ResetDAPosition(int no);

    int NormalDrive(int no);

    int UpdatePosition(int no);

    int SetFrameObjAlpha(int no, char *name, float alpha);

    int SetFootSeId(int no, int id);
};

STATIC_ASSERT(sizeof(CEohMother) == 0x200);

struct ARG_DATA {
    int type;

    union {
        int i;
        float f;
        char *s;
    };
};

STATIC_ASSERT(sizeof(ARG_DATA) == 0x8);

struct ARG_LIST {
    int id;
    ARG_DATA *args;
    int arg_num;
    ARG_LIST *next;
};

STATIC_ASSERT(sizeof(ARG_LIST) == 0x10);

class CEventScriptArg {
public:
    CEventScriptArg();
    int next_id;
    ARG_LIST *list;
    int list_num;
    mgCMemory *memory;

    void BuildArgData(unsigned int *program);
};

STATIC_ASSERT(sizeof(CEventScriptArg) == 0x10);

class CRaster {
public:
    CRaster();
    int state;
    float amplitude;
    float amplitude_step;
    float speed;
    float speed_step;
    float pitch;
    float pitch_step;
    float phase;
    s32 unk_20;
    int frames;
    int frame;

    void Initialize();

    void SetParam(float amplitude, float speed, float pitch);

    void StartRaster(float amplitude, float speed, float pitch, int frames);

    void StopRaster(float amplitude, float speed, float pitch, int frames);

    void StepRaster();

    void DrawRaster();
};

STATIC_ASSERT(sizeof(CRaster) == 0x2C);

class CScreenEffect {
public:
    CScreenEffect();
    CRaster raster;
    mgCTexture *sepia_texture;
    int sepia;
    mgCTexture *mono_flash_texture[2];
    int mono_flash;
    int mono_flash_interval;
    int mono_flash_frame;
    int mono_flash_no;

    void Initialize();

    void Step();

    void Draw();

    void InitRaster(float amplitude, float speed, float pitch);

    void StartRaster(float amplitude, float speed, float pitch, int frames);

    void StopRaster(float amplitude, float speed, float pitch, int frames);

    void SetSepiaTexture(mgCTexture *texture, u_long128 *image);

    void CaptureSepiaScreen();

    void SetSepiaFlag(int on);

    void SetMonoFlashTexture(mgCTexture **texture, u_long128 **image);

    void CaptureMonoFlashScreen();

    void SetMonoFlashFlag(int on, int interval);
};

STATIC_ASSERT(sizeof(CScreenEffect) == 0x4C);

struct HIT_EFFECT_PARTICLE {
    u8 unk_0[0x10];
    sceVu0FVECTOR pos;
    sceVu0FVECTOR dir;
    float unk_30;
    float speed;
    float slow;
    int life;
    s32 unk_40;
    float alpha;
    float alpha_step;
    s32 unk_4c;
};

STATIC_ASSERT(sizeof(HIT_EFFECT_PARTICLE) == 0x50);

#define EVENT_HIT_EFFECT_NUM 5

#define EVENT_HIT_PARTICLE_NUM 0x40

extern CMarker EventMarker;

extern RS_STACKDATA *p_use_item;

extern int SetWorldCoordFlg;

extern int PakuAnimEohNo;

extern int PakuMotionEohNo;

extern int PakuMotionType;

extern int PakuMotionType2;

extern ED_EVENT_INFO EdEventInfo;

extern CEohMother EventObjHandleMother;

extern CEventSpriteMother esMother;

extern u32 EventLocalFlag[0x40];

extern int EventLocalCnt[0x40];

extern CRain EventRain;

extern HIT_EFFECT_PARTICLE Hit_para[EVENT_HIT_EFFECT_NUM][EVENT_HIT_PARTICLE_NUM];

extern CHitEffectImage HitEffect[EVENT_HIT_EFFECT_NUM];

extern char PakuAnimName[0x40];

extern char PakuAnimName2[0x40];

extern char PakuMotionName[0x40];

extern char PakuMotionName2[0x40];

extern _SEN_CMR_SEQ cmr_seq_tbl[0x100];

extern _SEN_OBJ_SEQ obj_seq_tbl[0x100];

extern CScreenEffect EventScreenEffect;

void VectMatMul(float *out, float *in, float (*matrix)[4]);

void CalcPosWorldCoord(float *pos);

void CalcPosWorldCoordGyaku(float *pos);

void SetCamWorldCoord(mgCCamera *camera);

void SetCamWorldCoordGyaku(mgCCamera *camera);

void InitWorldCoord();

int GetLocalFlag(int no);

int SetLocalFlag(int no, int on);

int GetLocalCnt(int no);

int SetLocalCnt(int no, int value);

int GetLocalCnt2(int value);

void InitLocalCnt();

void EdEventInfoCommandInitialize();

void EventSeqInit();

void EdEventInit();

void EventTimeDraw();

void EdEventDraw();

void EdEventFirstDraw();

int EdEventFinish();

int EdEventStep();

void InitDramaScene();

void CancelDramaScene();

void EdEventMenuExit();

void EdSetBrokenObject();

void ResetMesFileBuffAll();

void EdEventLoopInit();

void EdEventMapInit();

void EdEventTermination();

void EdEventEnd();

unsigned int *CheckLoadedBGFile(char *name, int *size);

unsigned int *GetLoadBGBuff(char *name, int *size);

int _LOAD_CHARA_sub(int stack_no, char **name, int scene_no, unsigned int *data, int flag);

int _LOAD_CHARA_sub(int stack_no, char **name, int scene_no, unsigned int *data);

int _LOAD_MOTION_sub(int stack_no, char *name, int scene_no, unsigned int *data);

int GetConfigCaptionOff();

int LoadMovie(char *name, mgCMemory *memory, bool skip);

int _LOAD_MES_sub(char *name, int no, ClsMes *mes);

int CommandStreamOpenFromFPL(int port, char *pack, char *name);

int CommandStreamOpen(int port, char *name);

int VpkFileNameFromVoiceNo(char *name, int voice_no);

int CommandStreamPlay(int port, int volume);

int CommandStreamOpen2(int port, char *name);

void SetEventFunc(CRunScript *script);

class CCameraControl;

int GetArgInt(ARG_DATA *arg);
float GetArgFloat(ARG_DATA *arg);
char *GetArgString(ARG_DATA *arg);
void GetArgVector(float *out, ARG_DATA *arg);
void FileNameConvLanguage(char *name);
