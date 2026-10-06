#pragma once

#include "common.h"

#include <libvu0.h>

class CCharacter2;
class CEffectScriptMan;
class CMap;
class CMapSky;
class ClsMes;
class mgCCamera;
class mgCMemory;

#define RAIN_DROP_NUM 100

#define RAIN_FAR_DROP_NUM 50

#define RAIN_PARTICLE_NUM 100

#define RAIN_RIPPLE_NUM 200

#define RAIN_DROP_TRAIL_NUM 8

enum SCENE_DATA_KIND {
    SCENE_DATA_CHARA   = 1,
    SCENE_DATA_MAP     = 2,
    SCENE_DATA_MESSAGE = 3,
    SCENE_DATA_CAMERA  = 4,
    SCENE_DATA_SKY     = 5,
    SCENE_DATA_GAMEOBJ = 6,
    SCENE_DATA_EFFECT  = 7,
};

enum SCENE_DATA_STATUS {
    SCENE_DATA_LOADED   = 1 << 0,
    SCENE_DATA_ACTIVE   = 1 << 1,
    SCENE_DATA_ASSIGNED = 1 << 2,
};

enum RAIN_DROP_TYPE {
    RAIN_DROP_NEAR = 0,
    RAIN_DROP_FAR  = 1,
};

float f_rand(float min, float max);

int i_rand(int min, int max);

void InitVector(float *vec);

float RandXYinViewArea(float min_dist, float max_dist, float angle, float *x, float *z);

void DrawScreenRain();

class CRipple {
public:
    s32           active;
    u8            unk_04[0xC];
    sceVu0FVECTOR pos;
    float         size;
    s32           count;
    s32           life;
    s32           unk_2c;

    CRipple() { Init(); }

    int Birth(float *pos);

    int Step();

    void Draw();

    void Init();
};

STATIC_ASSERT(sizeof(CRipple) == 0x30);

class CParticle {
public:
    s32           active;
    u8            unk_04[0xC];
    sceVu0FVECTOR pos;
    sceVu0FVECTOR speed;
    sceVu0FVECTOR accel;
    float         base_y;
    u8            unk_44[0xC];

    CParticle() { Init(); }

    int Birth(float *pos, float *speed);

    int Step();

    void Draw();

    void Init();
};

STATIC_ASSERT(sizeof(CParticle) == 0x50);

class CRainDrop {
public:
    s32           active;
    s32           type;
    u8            unk_08[0x8];
    sceVu0FVECTOR pos[RAIN_DROP_TRAIL_NUM];
    sceVu0FVECTOR speed;
    s32           color[4];

    CRainDrop() { Init(); }

    void Birth(int type);

    int Step();

    void Draw();

    void Init();
};

STATIC_ASSERT(sizeof(CRainDrop) == 0xB0);

class CRain {
public:
    s32       active;
    s32       chara_no;
    u8        unk_08[0x8];
    CRainDrop drop[RAIN_DROP_NUM];
    CRainDrop far_drop[RAIN_FAR_DROP_NUM];
    CParticle particle[RAIN_PARTICLE_NUM];
    CRipple   ripple[RAIN_RIPPLE_NUM];

    CRain() { Init(); }

    void SetCharNo(int chara_no);

    void ParticleBirth(float *pos, int from_chara);

    void Stop();

    void Start();

    void Step();

    void Init();

    void Draw();
};

STATIC_ASSERT(sizeof(CRain) == 0xABF0);

class CSceneData {
public:
    CSceneData() { Initialize(); }
    u32        status;
    s32        type;
    char       name[32];
    s32        tex_block;
    s32        tex_block_num;
    mgCMemory *stack;

    void Initialize();
};

STATIC_ASSERT(sizeof(CSceneData) == 0x34);

class CSceneCharacter : public CSceneData {
public:
    CSceneCharacter() { Initialize(); }
    CCharacter2 *chara;
    s32          texb;
    s32          chara_no;

    int AssignData(CCharacter2 *chara, char *name);

    void Initialize();
};

STATIC_ASSERT(sizeof(CSceneCharacter) == 0x40);

class CSceneMap : public CSceneData {
public:
    CSceneMap() { Initialize(); }
    CMap *map;

    void Initialize();

    int AssignData(CMap *map, char *name);
};

STATIC_ASSERT(sizeof(CSceneMap) == 0x38);

class CSceneMessage : public CSceneData {
public:
    CSceneMessage() { Initialize(); }
    ClsMes *mes;

    void Initialize();

    int AssignData(ClsMes *mes, char *name);
};

STATIC_ASSERT(sizeof(CSceneMessage) == 0x38);

class CSceneCamera : public CSceneData {
public:
    CSceneCamera() { Initialize(); }
    mgCCamera *camera;

    int AssignData(mgCCamera *camera, char *name);

    void Initialize();
};

STATIC_ASSERT(sizeof(CSceneCamera) == 0x38);

class CSceneSky : public CSceneData {
public:
    CSceneSky() { Initialize(); }
    CMapSky *sky;

    int AssignData(CMapSky *sky, char *name);

    void Initialize();
};

STATIC_ASSERT(sizeof(CSceneSky) == 0x38);

class CSceneGameObj : public CSceneCharacter {
public:
    CSceneGameObj() { Initialize(); }
    void Initialize();
};

STATIC_ASSERT(sizeof(CSceneGameObj) == 0x40);

class CSceneEffect : public CSceneData {
public:
    CSceneEffect() { Initialize(); }
    CEffectScriptMan *effect;

    void Initialize();

    int AssignData(CEffectScriptMan *effect, char *name);
};

STATIC_ASSERT(sizeof(CSceneEffect) == 0x38);
