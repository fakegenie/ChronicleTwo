#pragma once

#include "common.h"

#include <libvu0.h>

#include "mg_sprite.hpp"
#include "runscript.hpp"

class mgCMemory;
class CCharacter2;
class CColPrim;
class CScene;

#define EFF_SPT_BASE_MAX 64
#define EFF_SPT_OWNER_MAX 128
#define EFF_SPT_OWNER_SLOT_MAX 8
#define EFF_SPT_SUB_CHARA_MAX 4
#define EFF_SPT_VALUE_MAX 8
#define EFF_SPT_LEVEL_MAX 4
#define EFF_SPT_BASE_DEF_NUM 219

enum EffSptBaseType {
    EFF_SPT_BASE_END = -1,
    EFF_SPT_BASE_CHR = 0,
    EFF_SPT_BASE_IMG = 1,
};

enum EffSptState {
    EFF_SPT_STATE_RUN          = 0,
    EFF_SPT_STATE_SCRIPT_PAUSE = 1,
    EFF_SPT_STATE_HIDE_STOP    = 2,
    EFF_SPT_STATE_STOP         = 3,
    EFF_SPT_STATE_HIDE         = 4,
};

struct EFF_SPT_BASE_DEF {
    char name[0x20];
    int  type;
    char file[0x20];
    char script[0x20];
};

STATIC_ASSERT(sizeof(EFF_SPT_BASE_DEF) == 0x64);

struct EFF_SPT_BASE {
    int          base_no;
    CCharacter2 *chara;
    int          texb;
    int          texb_owned;
    char        *script;
    int          level;
    int          work_size;
};

STATIC_ASSERT(sizeof(EFF_SPT_BASE) == 0x1C);

struct _ES_SPRITE {
    int           draw_flag;
    int           alpha;
    u_char            unk_08[0x8];
    sceVu0FVECTOR pos;
    float         uv[4];
    sceVu0FVECTOR color;
    float         scale[2];
    float         put_size[2];
    float         rotz;
    u_char            unk_54[0xC];
    sceVu0FVECTOR velo_pos;
    sceVu0FVECTOR acc_pos;
    sceVu0FVECTOR velo_col;
    sceVu0FVECTOR acc_col;
    float         velo_rotz;
    float         acc_rotz;
    float         velo_scl[2];
    float         acc_scl[2];
    float         scale_target[2];
    float         scale_conv_div;
    u_char            unk_c4[0xC];
    sceVu0FVECTOR color_target;
    float         color_conv_div;
    u_char            unk_e4[0xC];
    sceVu0FVECTOR blink_amp;
    float         blink_speed;
    float         blink_phase;
    u_char            unk_108[0x8];
};

STATIC_ASSERT(sizeof(_ES_SPRITE) == 0x110);

union EFF_SPT_VALUE {
    int   i;
    float f;
};

struct _EFF_SCRIPT {
    u_long128    *work;
    u_long128    *chara_work;
    CCharacter2  *chara;
    u_long128    *sub_chara_work;
    CCharacter2  *sub_chara[EFF_SPT_SUB_CHARA_MAX];
    int           texb;
    int           level;
    _ES_SPRITE   *sprite;
    int           sprite_num;
    char          tex_name[0x20];
    CRunScript    run;
    int           prog_no;
    int           user_id;
    int           slot;
    sceVu0FVECTOR origin;
    int           auto_offset;
    char          offset_frame[0x20];
    u_char            unk_e4[0xC];
    sceVu0FVECTOR work_vect1;
    sceVu0FVECTOR work_vect2;
    int           target_id;
    EFF_SPT_VALUE value[EFF_SPT_VALUE_MAX];
    CColPrim     *colprim;
    int           light_flag;
    int           state;
    _EFF_SCRIPT  *prev;
    _EFF_SCRIPT  *next;
    u_char            unk_148[0x8];
};

STATIC_ASSERT(sizeof(_EFF_SCRIPT) == 0x150);

class CEffectScriptMan {
public:
    mgCMemory     *memory;
    mgCMemory     *work_memory;
    u_long128     *load_buffer;
    int            level;
    int            texb_start;
    int            texb_num;
    int            texb_used;
    int            level_texb_used[EFF_SPT_LEVEL_MAX];
    int            unk_2c;
    mgC3DSprite    sprite;
    EFF_SPT_BASE  *base[EFF_SPT_BASE_MAX];
    int            base_num;
    _EFF_SCRIPT   *slot[EFF_SPT_OWNER_MAX][EFF_SPT_OWNER_SLOT_MAX];
    _EFF_SCRIPT   *now;
    _EFF_SCRIPT   *head;
    _EFF_SCRIPT   *tail;

    CEffectScriptMan() { Initialize(NULL, -1, -1); }

    void Initialize(mgCMemory *memory, int texb_start, int texb_num);

    void SetWorkBuffer(mgCMemory *work_memory);

    int SearchBaseNo(char *name);

    int LoadBaseEffSpt(int base_no, mgCMemory *memory, int texb);

    int LoadBaseEffSpt(char *name, mgCMemory *memory, int texb);

    void ClearBaseFromLevel(int level, int *texb_list, int texb_list_max);

    CCharacter2 *GetBaseChara(int base_no);

    CCharacter2 *GetBaseChara(char *name);

    int GetNotUsedTexb();

    void AddTexb();

    int BuildBase(int base_no, u_long128 *data, int data_size, u_long128 *script, int script_size, mgCMemory *memory, int texb);

    int BuildBase(char *name, u_long128 *data, int data_size, u_long128 *script, int script_size, mgCMemory *memory, int texb);

    int BuildPack(int base_no, u_int *pack, mgCMemory *memory, int texb);

    int BuildPack(char *name, u_int *pack, mgCMemory *memory, int texb);

    int GetNeedFilePath(int base_no, char *data_path, char *script_path);

    int GetNeedFilePath(char *name, char *data_path, char *script_path);

    _EFF_SCRIPT *CreateEffSpt(int base_no, int user_id, int use_slot);

    int CreateEffSpt(char *name, int user_id, int use_slot);

    void ClearEffectFromChrid(int user_id);

    void ClearEffectFromLevel(int level);

    void DeleteEffSpt(_EFF_SCRIPT *script);

    int DeleteEffSpt(int user_id, int slot);

    void AllClearEffSpt();

    void Step();

    void Draw();

    _ES_SPRITE *AssignSprite(int num);

    void DeleteSprite(_ES_SPRITE *sprite);

    int AssignCharacter(_EFF_SCRIPT *script, int num);

    int SetScriptProgNo(int prog_no, int user_id, int slot);

    int Pause(int state, int user_id, int slot);

    void PauseFromLevel(int level, int state);

    int SetScriptVect1(float *vect, int user_id, int slot);

    int GetScriptVect1(float *vect, int user_id, int slot);

    int SetScriptVect2(float *vect, int user_id, int slot);

    int GetScriptVect2(float *vect, int user_id, int slot);

    int SetScriptTargetId(int target_id, int user_id, int slot);

    int GetScriptTargetId(int &target_id, int user_id, int slot);

    int SetScriptUserId(int new_user_id, int user_id, int slot);

    int GetScriptUserId(int &out_user_id, int user_id, int slot);

    int SetColPrim(CColPrim *colprim, int user_id, int slot);

    int SetValue(int index, int value, int user_id, int slot);

    int SetValue(int index, float value, int user_id, int slot);

    int SetOrigin(float *origin, int user_id, int slot);

    CCharacter2 *GetCharacter(int user_id, int slot);

    int SetCharacter(CCharacter2 *chara, int user_id, int slot);

    int SetTexb(int texb, int user_id, int slot);
};

STATIC_ASSERT(sizeof(CEffectScriptMan) == 0x1190);

extern EFF_SPT_BASE_DEF eff_spt_base_def[EFF_SPT_BASE_DEF_NUM];

extern "C" CScene *now_scene;

extern "C" CEffectScriptMan *EffScriptMan;
