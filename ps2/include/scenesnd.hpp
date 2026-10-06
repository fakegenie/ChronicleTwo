#pragma once

#include "common.h"

#include <libvu0.h>

#include "dngfloor.hpp"
#include "effectlist.hpp"
#include "mdslist.hpp"
#include "mg_memory.hpp"
#include "scene.hpp"
#include "sceneevent.hpp"
#include "sceneload.hpp"
#include "snd_mngr.hpp"
#include "villagermngr.hpp"
#include "water.hpp"

class BattleEffectMan;
class CCharacter2;
class CEffectScriptMan;
class CFuncPoint;
class CMap;
class CMapSky;
class CSaveData;
class CTreasureBoxManager;
class CVillagerPlaceInfo;
class ClsMes;
class mgCCamera;
class mgCFrame;
struct CCPoly;
struct InScreenFuncInfo;
struct mgVu0FBOX;

enum SND_FILE_NO {
    SND_FILE_NO_NONE = -1,
    SND_FILE_NO_KEEP = 9999,
};

struct SYSTEM_SCRIPT_INFO {
    s16 event_no;
    s16 running;
};

enum MINIMAP_REVEAL {
    MINIMAP_REVEAL_ROOMS   = 1,
    MINIMAP_REVEAL_SYMBOLS = 2,
};

struct DNG_BATTLE_AREA {
    s32                 unk_0;
    s32                 unk_4;
    u32                 pause_flag;
    u16                 floor_status;
    u8                  unk_e[0x2];
    s32                 timer;
    CDngFloorManager    floor_manager;
    char                map_name[0x20];
    SYSTEM_SCRIPT_INFO  script;
    s8                  statusbar_show;
    s8                  statusbar_show_old;
    u8                  unk_4a[0x2];
    float               statusbar_rate;
    float               statusbar_speed;
    s32                 camera_mode;
    s32                 boss_map;
    s32                 battle_clear;
    u8                  unk_60[0x4];
    u32                 minimap_reveal;
    u8                  unk_68[0x4];
    float               bright_rate;
    float               quake_power;
    float               quake_step;
    s16                 quake_count;
    u8                  unk_7a[0x2];
    CTreasureBoxManager *treasure_box;
    BattleEffectMan    *battle_effect;
    s32                 battle_bgm_state;
    float               battle_bgm_vol;
    s8                  unk_8c;
    u8                  unk_8d[0x3];
    u64                 subject_counter;
    u32                 unk_98;
    s8                  map_effect_id;
    u8                  unk_9d;
    s16                 lock_on_mode;
    s32                 free_texb;
    u8                  unk_a4[0x4];

    void SetStatusBar(int show, float speed) {
        statusbar_show_old = statusbar_show;
        statusbar_show = show;
        if (show) {
            statusbar_rate = 0.0f;
        } else {
            statusbar_rate = 1.0f;
        }
        statusbar_speed = speed;
    }

    void ApplyQuake(float *value) {
        float *power = &quake_power;

        if (quake_count > 0) {
            if (quake_count % 2) {
                *value += *power;
            } else {
                *value -= *power;
            }
        }
    }

    void SetStatusBarNow(int show) {
        SetStatusBar(show, 1.0f);
        statusbar_rate = show ? 1.0f : 0.0f;
    }
};

STATIC_ASSERT(sizeof(DNG_BATTLE_AREA) == 0xA8);

struct SND_FILE_INFO {
    s16 id;
    s16 bgm_no;
    s16 se_base;
    s16 se_battle;
    s16 se_env;
    s16 env_bgm;
    s16 env_vol;
    s16 se_src[8];
    s16 event_se[2];
    u8  reverb_type;
    u8  reverb_depth;
};

STATIC_ASSERT(sizeof(SND_FILE_INFO) == 0x24);

struct SND_REV_INFO {
    s16 id;
    s16 type;
    s16 depth;
    s16 unk_6;
};

STATIC_ASSERT(sizeof(SND_REV_INFO) == 0x8);

struct SE_SRC_PLAY_INFO {
    s32   se_no;
    s32   num;
    float vol[16];
    float pan[16];
};

STATIC_ASSERT(sizeof(SE_SRC_PLAY_INFO) == 0x88);

class CScene {
public:
    CScene() : event_data() { InitAllData(); }

    struct BGM_INFO {
        s32       port;
        s32       snd_id;
        s32       load_no;
        float     unk_c;
        s32       vol;
        float     volf;
        float     fade_volf;
        float     fade_speed;
        s32       play_no;
        s32       time_vol;
        u8        unk_28[0x8];
        u_long128 buff[0x40];
        mgCMemory stack;

        void Init();
    };

    struct BGM_STATUS {
        s32   state;
        s32   load_no;
        s32   play_no;
        float unk_c;
        s32   vol;
        float volf;
        s32   time_vol;
    };

    struct InScreenCharaInfo {
        s32   chara_no;
        float dist;
        s32   in_center;
    };

    s32                stack_num;
    s32                stack_no;
    mgCMemory         *stack[12];
    mgCMemory         *work_stack;
    u_long128         *read_buff;
    s32                chara_num;
    CSceneCharacter    chara[128];
    s32                camera_num;
    CSceneCamera       camera[8];
    s32                message_num;
    CSceneMessage      message[8];
    u8                 unk_23cc[0x4];
    CMdsListSet        mds_list_set;
    CFireRaster        fire_raster;
    s32                map_num;
    CSceneMap          map[4];
    s32                sky_num;
    CSceneSky          sky[4];
    s32                gameobj_num;
    CSceneGameObj      gameobj[4];
    s32                effect_num;
    CSceneEffect       effect[8];
#pragma cpp_extensions on
    union {
    CFadeInOut         fade;
        struct {
            u8 unk_2c70[0x2C];
            int motion_blur;
        };
    };
#pragma cpp_extensions reset
    s32                bg_load_step;
    u8                 unk_2ca4[0x4];
    SCN_LOADMAP_INFO2  bg_load_info;
    s32                player_chara;
    s32                active_camera;
    s32                before_camera;
    s32                active_map;
    s32                now_map_no;
    s32                now_sub_map_no;
    s32                old_map_no;
    s32                old_sub_map_no;
    s32                chara_texb;
    s32                villager_texb;
    s32                villager_texb_num;
    s32                event_texb;
    s32                event_texb_num;
    s32                unk_2e84;
    s32                event_run;
    s32                event_no;
#pragma cpp_extensions on
    union {
    CSceneEventData    event_data;
        struct {
            u32 map_jump_flags;
            u8 unk_2e94[8];
            int door_place_no[2];
            u8 unk_2ea4[4];
            char map_jump_name[1];
            u8 unk_2ea9[0x77];
            float door_dir_x;
            u8 unk_2f24[4];
            float door_dir_z;
            u8 unk_2f2c[4];
            float door_vec[3];
            u8 unk_2f3c[0x4];
            int event_parts_id;
            u8 unk_2f44[0x18];
            int villager_id;
        };
    };
#pragma cpp_extensions reset
    s32                map_event_no;
    s32                exit_flag;
    s32                day;
    float              time;
    float              time_speed;
    s32                time_step;
    float              wind_power;
    u8                 unk_2f7c[0x4];
    sceVu0FVECTOR      wind_dir;
    DNG_BATTLE_AREA    battle_area;
    s32                skip_load_villager;
    s32                skip_load_sub_villager;
    CSaveData         *save_data;
    u8                 unk_3044[0xC];
    CVillagerMngr      villager_mngr;
    s32                villager_time;
    s32                sub_villager_time;
    s32                tex_block_base;
    s32                tex_block_count;
    CThunderEffect     thunder;
    u8                 unk_3f0c[0x154];
    s32                snd_file_num;
    SND_FILE_INFO      snd_file[512];
    s32                snd_rev_num;
    SND_REV_INFO       snd_rev[256];
    s32                snd_file_id;
    s32                skip_load_bgm;
    s32                skip_load_sound;
    s32                skip_play_bgm;
    u8                 unk_9078[0x8];
    BGM_INFO           bgm[2];
    s32                bgm_no;
    s32                se_src_id[16];
    s32                se_src_no[16];
    u8                 unk_99c4[0xC];
    u_long128          se_src_buff[0x40];
    mgCMemory          se_src_stack;
    SE_SRC_PLAY_INFO   se_src_play[4];
    s32                se_src_play_no[4];
    s32                se_src_play_flag[4];
    s32                se_env_id;
    s32                se_env_no;
    u8                 unk_a048[0x8];
    u_long128          se_env_buff[0x40];
    mgCMemory          se_env_stack;
    s32                unk_a480;
    s32                env_bgm_no;
    float              env_bgm_vol;
    float              env_bgm_volf;
    s32                env_bgm_auto;
    s32                env_bgm_offset;
    s32                se_base_id;
    s32                se_base_no;
    u_long128          se_base_buff[0x200];
    mgCMemory          se_base_stack;
    s32                se_battle_id;
    s32                se_battle_no;
    u8                 unk_c4d8[0x8];
    u_long128          se_battle_buff[0x200];
    mgCMemory          se_battle_stack;
    u_long128          loop_se_buff[0x200];
    mgCMemory          loop_se_stack;
    CLoopSeMngr        loop_se;

    void InitAllData();

    virtual void Initialize();

    void SetStack(int no, mgCMemory *stack);

    mgCMemory *GetStack(int no);

    void ClearStack(int no);

    void AssignStack(int no);

    CSceneCharacter *GetSceneCharacter(int no);

    CSceneMap *GetSceneMap(int no);

    CSceneMessage *GetSceneMessage(int no);

    CSceneCamera *GetSceneCamera(int no);

    CSceneSky *GetSceneSky(int no);

    CSceneGameObj *GetSceneGameObj(int no);

    CSceneEffect *GetSceneEffect(int no);

    int CheckIMGName(int no, char *name);

    int CheckMDSName(int no, char *name);

    CSceneData *GetData(int kind, int no);

    int AssignCamera(int no, mgCCamera *camera, char *name);

    int GetCameraID(char *name);

    mgCCamera *GetCamera(int no);

    int AssignMessage(int no, ClsMes *message, char *name);

    ClsMes *GetMessage(int no);

    int AssignChara(int no, CCharacter2 *chara, char *name);

    void SetCharaNo(int no, int chara_no);

    int GetCharaNo(int no);

    CCharacter2 *GetCharacter(int no);

    int AssignMap(int no, CMap *map, char *name);

    char *GetMapName(int no);

    int GetMapID(char *name);

    CMap *GetMap(int no);

    CMapSky *GetSky(int no);

    int GetMainMapNo();

    CFuncPoint *InScreenFunc(InScreenFuncInfo *info);

    void DrawScreenFunc(mgCFrame *frame);

    int AssignSky(int no, CMapSky *sky, char *name);

    int DeleteSky(int no);

    int AssignEffect(int no, CEffectScriptMan *effect, char *name);

    void DeleteEffect(int no);

    CEffectScriptMan *GetEffect(int no);

    void StepEffectScript(int no);

    void DrawEffectScript(int no);

    int IsActive(int kind, int no);

    void SetActive(int kind, int no);

    void ResetActive(int kind, int no);

    void SetStatus(int kind, int no, int flag);

    void ResetStatus(int kind, int no, int flag);

    int GetStatus(int kind, int no);

    void SetType(int kind, int no, int type);

    int GetType(int kind, int no);

    int GetActiveMap(CMap **maps, int max);

    int GetCharaTexb(int no);

    void SetCharaTexb(int no, int texb);

    void SetTime(float time);

    void AddTime(float hours);

    void TimeStep(float step);

    void SetWind(float power, float *dir);

    void ResetWind();

    float GetWind(float *dir);

    void SetNowMapNo(int map_no);

    int GetNowMapNo() { return now_map_no; }

    void SetNowSubMapNo(int map_no);

    int LoadChara(int no, unsigned int *pack, char *name, mgCMemory *model_stack, mgCMemory *motion_stack, mgCMemory *image_stack, int image_block, int no_line);

    void DeleteChara(int no);

    int CopyChara(int no, int src_no, mgCMemory *stack);

    int LoadMapFromMemory(int no, SCN_LOADMAP_INFO2 *info);

    int LoadMapFromMemory(int no, int step, SCN_LOADMAP_INFO2 *info);

    int LoadMapBGStep(SCN_LOADMAP_INFO2 *info);

    int LoadMap(int no, SCN_LOADMAP_INFO2 *info, int background);

    int DeleteMap(int no, int clear_stack);

    void InitSnd();

    void InitBGM();

    void InitSeSrc();

    void InitSeEnv();

    void InitSeBattle();

    void InitSeBas();

    void SeAllStop();

    void SoundAllStop();

    void InitLooSeMngr();

    BGM_INFO *GetActiveBgmInfo();

    void PlayBGM(int bgm_no, int vol, float volf);

    void PauseBGM();

    void RePlayBGM();

    void StopBGM(int bgm_no);

    void SetVolBGM(int vol);

    int GetVolBGM();

    int GetBGMState();

    void SetVolfBGM(float volf);

    float GetVolfBGM();

    void FadeOutBGM(int frames);

    void FadeInBGM(int frames);

    void AutoChangeBGMVol(int enable);

    void GetActiveBgmStatus(BGM_STATUS *status);

    void SetActiveBgmStatus(BGM_STATUS *status);

    void PlayEnvBGM(int env_no, float vol);

    void SetEnvBGMVol(float vol);

    float GetEnvBGMVol();

    void StopEnvBGM();

    void AutoChangeEnvBGM(int enable);

    void AutoChangeEnvOffset(int offset);

    void PlayEnvBgm();

    int GetSeSrcID(int se_src_no);

    void GetBgmFile(char *path, int no);

    void GetSeSrcFile(char *path, int no);

    void GetSeEnvFile(char *path, int no);

    void GetSeBaseFile(char *path, int no);

    void GetSeBattleFile(char *path, int no);

    int CheckLoadBGM(int no);

    int CheckLoadSeSrc(int no);

    int CheckLoadSeEnv(int no);

    int CheckLoadSeBattle(int no);

    int CheckLoadSeBase(int no);

    SND_FILE_INFO *SearchSndDataID(int id);

    int GetDefBgmNo(int id);

    int GetDefEventSeFile(int id, char *path);

    int LoadSound(int id, u_long128 *buff);

    int LoadBGM(int no, u_long128 *buff);

    int LoadSeSrc(int no, u_long128 *buff);

    int LoadSeEnv(int no, u_long128 *buff);

    int LoadSeBattle(int no, u_long128 *buff);

    int LoadSeBase(int no, u_long128 *buff);

    int LoadBGMPack(int no, unsigned int *pack);

    int LoadSeSrcPack(int no, unsigned int *pack);

    int LoadSeEnvPack(int no, unsigned int *pack);

    int LoadSeBattlePack(int no, unsigned int *pack);

    int LoadSeBasePack(int no, unsigned int *pack);

    void PrePlaySeSrc();

    void PlaySeSrc(int se_no, float vol, float pan);

    int check_se_play(int se_no);

    float GetTimeBgmVolf();

    void StepSnd();

    void StopSeSrc();

    void PlayMapSeSrc();

    void SePlayOpenDoor(int type, float *pos);

    void SePlayCloseDoor(int type, float *pos);

    void SePlayFoot(int ground, int foot, float *pos);

    void LoadSndRevInfo(char *data, int size);

    void LoadSndFileInfo(char *data, int size);

    void UpDateMapInfo();

    int GetColPoly(CCPoly *poly, mgVu0FBOX &box, int max);

    int GetCameraPoly(CCPoly *poly, mgVu0FBOX &box, int max);

    void RunEvent(int event_no, CSceneEventData *data);

    int GetMapEvent(float *pos, int check_type, CSceneEventData *data);

    int GetFixCameraPos(float *pos, float *camera);

    void FixCameraPartsOnOff(float *pos);

    void EyeViewDrawOnOff(int on);

    void GetSunPosition(float *pos);

    void GetMoonPosition(float *pos);

    void DrawSky(int no);

    void DrawLensFlare(int texb, char *name0, char *name1);

    void EffectStep();

    void DrawEffect(int mode);

    int CheckDrawChara(int no);

    int CheckDrawCharaShadow(int no);

    int StepChara(int no);

    void GetCharaLighting(float (*light)[4], float *pos);

    void SetVillagerTexb(int texb, int num) {
        villager_texb = texb;
        villager_texb_num = num;
    }

    void SetEventTexb(int texb, int num) {
        event_texb = texb;
        event_texb_num = num;
    }

    int GetTextureBlockNo(int group, int *out_block, int max) {
        return mds_list_set.GetTextureBlockNo(group, out_block, max);
    }

    int DrawChara(int no, int mode);

    int DrawCharaShadow(int no);

    void DrawExclamationMark(mgCFrame *frame);

    int SearchCharaTexb(int chara_no);

    int PreLoadVillager(int map_no, u_long128 *cache);

    void PreLoadVillagerEnd();

    int DeleteVillager(int chara_no);

    void DeleteSubVillager();

    void DeleteVillager();

    int SearchCharaID(int chara_no);

    int GetNowVillagerTime();

    int GetLoadVillagerList(int map_no, int *chara_no, CVillagerPlaceInfo **place);

    int SearchCopyModel(int chara_no);

    void CharaObjectOnOff(int no, mgCMemory *stack);

    int LoadVillager(int map_no, int texb);

    int LoadSubVillager(int map_no, int texb);

    void RegisterVillager(int no, int chara_no, int place_no);

    int RegisterVillager(int no, int chara_no, CVillagerPlaceInfo *place);

    int RegisterVillager(int no, int chara_no, mgCMemory *stack);

    int GetTalkEvent(float *pos, CSceneEventData *data);

    void StepVillager();

    void StayNearVillager(float *pos, int *stay);

    void CancelStayVillager(int *stay);

    void StayVillager(int chara_no);

    void CancelStayVillager(int chara_no);

    void ExModeVillager(int chara_no);

    void SetActiveVillager();

    int InScreenChara(InScreenCharaInfo *info, float *range);

    void LoadGameObject(int map_no, int texb, mgCMemory *stack);

    int GetGameObjectEvent(float *pos, CSceneEventData *data);

    void DrawGameObject(int mode);
};

STATIC_ASSERT(sizeof(CScene::BGM_INFO) == 0x460);
STATIC_ASSERT(sizeof(CScene::BGM_STATUS) == 0x1C);
STATIC_ASSERT(sizeof(CScene::InScreenCharaInfo) == 0xC);
STATIC_ASSERT(sizeof(CScene) == 0x10550);
