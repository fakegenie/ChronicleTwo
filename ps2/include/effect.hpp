#pragma once

#include "common.h"

#include <libvu0.h>

class mgC3DSprite;
class mgCTexture;

enum EFFECT_RAND_TYPE {
    EFFECT_RAND_NONE = 0,
    EFFECT_RAND_UNIFORMITY = 1,
    EFFECT_RAND_REGULARITY = 2,
};

enum EFFECT_CHANGE_TYPE {
    EFFECT_CHANGE_NONE = 0,
    EFFECT_CHANGE_ADD = 1,
    EFFECT_CHANGE_SUB = 2,
    EFFECT_CHANGE_ADD_HEAD = 3,
    EFFECT_CHANGE_SUB_TAIL = 4,
    EFFECT_CHANGE_ADD_HEAD_TAIL = 5,
    EFFECT_CHANGE_SINE = 6,
};

enum EFFECT_ALPHA_BLEND {
    EFFECT_ALPHA_BLEND_NONE = 0,
    EFFECT_ALPHA_BLEND_ADD = 1,
    EFFECT_ALPHA_BLEND_SUB = 2,
};

struct EffectTypeTriple {
    EFFECT_CHANGE_TYPE x;
    EFFECT_CHANGE_TYPE y;
    EFFECT_CHANGE_TYPE z;

    EffectTypeTriple() {}

    EffectTypeTriple(const EffectTypeTriple &other)
        : x(other.x), y(other.y), z(other.z) {}
};

struct EffectRect {
    int left;
    int top;
    int right;
    int bottom;
};

struct EFFECT_PARAM {
    int                life;
    float              width;
    float              height;
    int                dir;
    sceVu0FVECTOR      pos;
    sceVu0FVECTOR      velo;
    sceVu0FVECTOR      acc;
    sceVu0FVECTOR      velo_mul;
    sceVu0FVECTOR      acc_mul;
    EFFECT_CHANGE_TYPE move_type[3];
    u_int                unk_6c;
    sceVu0FVECTOR      move_p1;
    sceVu0FVECTOR      move_p2;
    EFFECT_CHANGE_TYPE scale_type[3];
    u_int                unk_9c;
    sceVu0FVECTOR      scale;
    sceVu0FVECTOR      svelo;
    sceVu0FVECTOR      scale_p1;
    sceVu0FVECTOR      scale_p2;
    EFFECT_ALPHA_BLEND alpha_blend;
    EFFECT_CHANGE_TYPE alpha_type;
    float              alpha;
    float              alpha_p1;
    float              alpha_p2;
    mgCTexture        *texture;
    union {
        int tex_rect[8][4];
        EffectRect tex_rect_copy[8];
    };
    int                tex_get_type;
    int                tex_frame;
    int                gravity;
    u_int                unk_184;
    u_int                unk_188;
    u_int                unk_18c;
    sceVu0FVECTOR      gravity_pos;
    float              gravity_accel;
    float              gravity_mass;
    u_int                unk_1a8;
    u_int                unk_1ac;
};
STATIC_ASSERT(sizeof(EFFECT_PARAM) == 0x1B0);

void InitEffectParam(EFFECT_PARAM *param);

class CEffect {
public:
    int           active;
    int           frame;
    float         alpha;
    u_int           unk_0c;
    sceVu0FVECTOR pos;
    sceVu0FVECTOR scale;
    int           tex_rect[4];
    int           tex_count;
    int           tex_index;
    u_int           unk_48;
    u_int           unk_4c;
    EFFECT_PARAM  param;

    CEffect();

    void Initialize();

    void SetEffect(EFFECT_PARAM *param);

    void Step(int steps);

    void Draw();
};
STATIC_ASSERT(sizeof(CEffect) == 0x200);

class CEffectCtrl {
public:
    sceVu0FVECTOR      origin;
    int                run;
    int                entry;
    float              width;
    float              height;
    int                dir;
    int                num;
    EFFECT_RAND_TYPE   num_rand_type;
    float              num_rand;
    int                num_rand_count;
    int                count;
    EFFECT_RAND_TYPE   cnt_rand_type;
    float              cnt_rand;
    int                cnt_rand_count;
    int                repeat;
    int                repeat_wait;
    int                repeat_wait_now;
    int                repeat_timer;
    EFFECT_RAND_TYPE   rep_rand_type;
    float              rep_rand;
    int                rep_rand_count;
    int                repeat_num;
    int                repeat_cnt;
    sceVu0FVECTOR      pos;
    EFFECT_RAND_TYPE   pos_rand_type;
    sceVu0FVECTOR      pos_rand;
    int                pos_rand_count;
    EffectTypeTriple move_type;
    sceVu0FVECTOR      velo;
    sceVu0FVECTOR      acc;
    sceVu0FVECTOR      velo_mul;
    sceVu0FVECTOR      acc_mul;
    sceVu0FVECTOR      move_p1;
    sceVu0FVECTOR      move_p2;
    EFFECT_RAND_TYPE   velo_rand_type;
    EFFECT_RAND_TYPE   acc_rand_type;
    EFFECT_RAND_TYPE   move_p1_rand_type;
    EFFECT_RAND_TYPE   move_p2_rand_type;
    sceVu0FVECTOR      velo_rand;
    sceVu0FVECTOR      acc_rand;
    sceVu0FVECTOR      move_p1_rand;
    sceVu0FVECTOR      move_p2_rand;
    int                velo_rand_count;
    int                acc_rand_count;
    int                move_p1_rand_count;
    int                move_p2_rand_count;
    EffectTypeTriple scale_type;
    sceVu0FVECTOR      scale;
    sceVu0FVECTOR      svelo;
    sceVu0FVECTOR      scale_p1;
    sceVu0FVECTOR      scale_p2;
    EFFECT_RAND_TYPE   scale_rand_type;
    EFFECT_RAND_TYPE   svelo_rand_type;
    EFFECT_RAND_TYPE   scale_p1_rand_type;
    EFFECT_RAND_TYPE   scale_p2_rand_type;
    sceVu0FVECTOR      scale_rand;
    sceVu0FVECTOR      svelo_rand;
    sceVu0FVECTOR      scale_p1_rand;
    sceVu0FVECTOR      scale_p2_rand;
    int                scale_rand_count;
    int                svelo_rand_count;
    int                scale_p1_rand_count;
    int                scale_p2_rand_count;
    EFFECT_ALPHA_BLEND alpha_blend;
    EFFECT_CHANGE_TYPE alpha_type;
    float              alpha;
    float              alpha_p1;
    float              alpha_p2;
    EFFECT_RAND_TYPE   alpha_rand_type;
    EFFECT_RAND_TYPE   alpha_p1_rand_type;
    EFFECT_RAND_TYPE   alpha_p2_rand_type;
    float              alpha_rand;
    float              alpha_p1_rand;
    float              alpha_p2_rand;
    int                alpha_rand_count;
    int                alpha_p1_rand_count;
    int                alpha_p2_rand_count;
    int                tex_rect_num;
    union {
        int tex_rect[8][4];
        EffectRect tex_rect_copy[8];
    };
    mgCTexture        *texture;
    int                tex_get_type;
    int                gravity;
    sceVu0FVECTOR      gravity_pos;
    float              gravity_accel;
    float              gravity_mass;

    CEffectCtrl();

    ~CEffectCtrl();

    void Ctrl(CEffect *effects, int effect_num);

    void Initialize();

    void Run();

    void SetOrigin(float *origin);

    CEffectCtrl &operator=(const CEffectCtrl &other);
};
STATIC_ASSERT(sizeof(CEffectCtrl) == 0x310);

class CEffectManager {
public:
    char         name[32];
    CEffect     *effects;
    int          effect_num;
    CEffectCtrl *ctrls;
    int          ctrl_num;
    int          load;
    int          ctrl_index;
    int          run;
    int          wait_count;
    int          next_ctrl;
    int          wait_frame[8];
    char         ctrl_name[8][32];
    char         img_name[32];

    CEffectManager();

    void Initialize();

    void EntryEffCtrls(CEffect *effects, int effect_num, CEffectCtrl *ctrls, int ctrl_num);

    void SetEffectNums(int effect_num, int ctrl_num);

    void Ctrl();

    void Step(int steps);

    void Draw();

    void Run();

    void Stop();

    int EnterEffectCtrl(CEffectCtrl ctrl, char *name);

    void GetBufferNums(char *script, int size, int *effect_num, int *ctrl_num);

    void Load(char *script, int size);

    void SetOrigin(float *origin);

    void CreatePacket(mgC3DSprite *sprite);
};
STATIC_ASSERT(sizeof(CEffectManager) == 0x184);
