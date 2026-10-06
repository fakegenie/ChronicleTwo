#pragma once

#include "common.h"

#include <libvu0.h>

#include "character.hpp"
#include "collision.hpp"
#include "colprim.hpp"
#include "dng_effect.hpp"
#include "dng_hud.hpp"
#include "dng_object.hpp"
#include "mg_memory.hpp"
#include "pot.hpp"

class CActionChara;
class CWeaponElement;
class CAutoMapGen;
class CCameraControl;
class CEffectScriptMan;
class CGeoStone;
class CHealingEffectMan;
class CMap;
class CMapEffectsManeger;
class CMiniEffPrimMan;
class CMonsterMan;
class CRandomCircle;
class CRedMarkModel;
class CSaveData;
class CSaveDataDungeon;
class CScene;
class CStartupEpisodeTitle;
class CTreasureBoxManager;
class CUserDataManager;
class BattleEffectMan;
class ClsMes;
class MessageTaskManager;
class mgCFrame;
struct DNG_BATTLE_AREA;
struct DNG_FLOOR_SAVE;
struct INIT_LOOP_ARG;
struct RUN_SCRIPT_ENV;

enum DNG_STATUS_MODE {
    DNG_STATUS_FIELD      = 0,
    DNG_STATUS_MENU       = 1,
    DNG_STATUS_EVENT      = 2,
    DNG_STATUS_EVENT_EDIT = 3,
    DNG_STATUS_EVENT_MENU = 4,
    DNG_STATUS_EXIT       = 5
};

struct MoveCheckInfo {
    float         radius;
    int           skip_ground;
    int           landed;
    CCPoly        ground_poly;
    int           ground_found;
    CCPoly        second_poly;
    sceVu0FVECTOR ground_point;
    int           width_result;
    int           in_water;
    sceVu0FVECTOR water_surface;
    int           crossed_area;
    float         signed_distance;
    sceVu0FVECTOR crossed_point;

    void Initialize() {
        memset(this, 0, sizeof(MoveCheckInfo));
    }

    void Clear() {
        Initialize();
    }
};

STATIC_ASSERT(sizeof(MoveCheckInfo) == 0x110);

struct DNG_STATUS {
    int   mode;
    int   dungeon_no;
    int   eye_view;
    int   active_item;
    float cursor_fade;
    int   status_count;
    int   debug_window;
};

STATIC_ASSERT(sizeof(DNG_STATUS) == 0x1C);

struct ACCUME_EFFECT {
    mgCFrame *frame;
    u8        unk_4[0x30C];
    int       mode;
    u8        unk_314[0xC];
    s32       unk_320;
    u8        unk_324[0xC];
};

STATIC_ASSERT(sizeof(ACCUME_EFFECT) == 0x330);

extern mgCMemory *MainBuffer__2;

extern u_long128 *BuffReadData;

extern DNG_FLOOR_SAVE *NowFloorInfoPtr;

extern RUN_SCRIPT_ENV ActionScriptEnv;

extern CUserDataManager *DngUserData;

extern CSaveData *DngSaveData;

extern CSaveDataDungeon *DngSaveDataDungeon;

extern CScene *DngMainScene;

extern DNG_BATTLE_AREA *BattleAreaScene;

extern CMap *DngMainMap;

extern CMonsterMan *ActiveMonster;

extern ClsMes *DngMess;

extern ClsMes *DngMess2;

extern ClsMes *EventMess;

extern ClsMes *MonsterMess;

extern CRedMarkModel *RedMarkModel;

extern CCharacter2 *TreasureBoxModel;

extern CTreasureBoxManager *TreasureBoxMan;

extern CActionChara *MainChara__2;

extern CEffectScriptMan *FxScriptMan;

extern CColPrim *BTsuboCol;

extern CPullItemManager PullItemMan;

extern mgCFrame *TornadoModel;

extern CAfterWire afterWire[16];

extern mgCMemory BuffPaketList[2];

extern mgCMemory BuffPaketData[2];

extern mgCMemory BuffStageMain;

extern mgCMemory BuffStageChara;

extern mgCMemory BuffStageSubData;

extern mgCMemory BuffStageSubChara;

extern mgCMemory BuffWorkData;

extern mgCMemory BuffCharacter;

extern mgCMemory BaseCharacter[6];

extern mgCMemory BuffTempData;

extern mgCMemory BuffScriptData;

extern mgCMemory BuffEffectScriptData;

extern mgCMemory BuffEventData[4];

extern mgCMemory BuffMDTBuild;

extern mgCMemory BuffMDTBuild2;

extern DNG_STATUS DngStatus;

extern CMapEffectsManeger map_effect;

extern ACCUME_EFFECT AccumulateEffect;

extern CDamageScore DamageScore;

extern CDamageScore DamageScoreMons[8];

extern CDamageScore2 DamageScore2;

extern MessageTaskManager MsgTaskMan;

extern CStartupEpisodeTitle StartupEpisodeTitle;

extern BattleEffectMan BattleFX;

extern CLevelupInfo LevelupInfo;

extern CLockOnModel LockOnModel;

extern CWarningGage2 WarningGage2;

extern CAutoMapGen AutoMapGen;

extern CColPrimMan ColPrimMan;

extern CRandomCircle RandomCircle;

extern CGeoStone GeoStone;

extern CCameraControl MainCamera;

extern CCameraControl EventCamera__2;

extern CHealingEffectMan HealingEffectMan;

extern CMiniEffPrimMan MiniEffPrimMan;

extern CCharacter2 ItemBaseData[19];

extern CRoboVoiceSystem VoiceUnit;

extern CRocketLauncherMan RocketLauncher;

extern CMachineGun MachineGun;

extern CLaserGunMan LaserGun;

extern CCharacter2 LaserGunModel;

extern CPullItem PullItem[72];

extern mgCFrame *SparcModel[3];

CWeaponElement *GetWeaponEffect();

void InitDungeonMain(INIT_LOOP_ARG arg);

void CommonStageClassInit();

void FinishDungeonMain();

int LoopDungeonMain();

void EntryEventScript(int event_no);

void ResetEyeView(CActionChara *chara);
