#include "common.h"
#include "mg_memory.hpp"
#include "mg_drawprim.hpp"
#include "mg_texture.hpp"
#include "mg_frame.hpp"
#include "mg_drawenv.hpp"
#include "mg_math.hpp"
#include "mglib.hpp"
#include "actionchara.hpp"
#include "scene.hpp"
#include "object.hpp"
#include "padcontrol.hpp"
#include "cameracontrol.hpp"
#include "subgame.hpp"
#include "scenesnd.hpp"
#include "fishing.hpp"
#include "gyorace.hpp"
#include "pbuggy.hpp"
#include "snd_mngr.hpp"
#include <cstdio>

extern int SubGame;
extern int MenuOpenFlag;
extern int ItemOver;
static SubGameInfo GameInfo;
extern char at_985__3[];

void InitSubGame(CScene *scene) {
    SubGame = SUBGAME_NONE;
    MenuOpenFlag = 0;
    ItemOver = 0;
    if (scene->GetCharacter(scene->player_chara) != 0) {
        mgCTextureManager *tex_manager = &mgTexManager;
        for (int i = 0; i < scene->tex_block_count; i++) {
            tex_manager->DeleteBlock(scene->tex_block_base + i);
        }
        for (int j = 0; j < SUBGAME_CHARA_NUM; j++) {
            scene->DeleteChara(j + SUBGAME_CHARA_BASE);
        }
        scene->DeleteEffect(SUBGAME_EFFECT_SLOT);
    }
}
int SubGameRunning(void) {
    return SubGame != 0;
}
int GetSubGameNo(void) {
    return SubGame;
}
SubGameInfo *GetNowSubGameInfo(void) {
    return &GameInfo;
}
int sgMenuOpenEnable(void) {
    return SubGameRunning() != 0 ? MenuOpenFlag : 1;
}
void sgSetMenuOpenEnableFlag(int value) {
    MenuOpenFlag = value;
}
int sgGetItemOver(void) {
    return ItemOver;
}
void sgGetItemOverReset(void) {
    ItemOver = 0;
}
void sgGetItemOverFlagOn(void) {
    ItemOver = 1;
}
int sgInitSubGame(int type, SubGameInfo *info) {
    int result;

    MenuOpenFlag = 0;
    ItemOver = 0;
    SubGame = type;
    if (type <= SUBGAME_NONE || type >= SUBGAME_MAX) {
        return 0;
    }
    result = 0;
    GameInfo = *info;
    GameInfo.texb = GameInfo.scene->tex_block_base;
    GameInfo.texb_num = GameInfo.scene->tex_block_count;
    switch (type) {
        case SUBGAME_FISHING:
            result = sgInitFishing(&GameInfo);
            break;
        case SUBGAME_GYORACE:
            result = sgInitGyoRace(&GameInfo);
            break;
        case SUBGAME_BUGGY:
            result = sgInitBuggy(&GameInfo);
            break;
        case SUBGAME_UNK_4:
            break;
    }
    if (result == 0) {
        SubGame = SUBGAME_NONE;
    }
    return result;
}
int sgLoopSubGame(void) {
    int finished;

    if (SubGameRunning() == 0) {
        return 0;
    }
    finished = 0;
    switch (SubGame) {
        case SUBGAME_FISHING:
            finished = sgLoopFishing(&GameInfo);
            break;
        case SUBGAME_GYORACE:
            finished = sgLoopGyoRace(&GameInfo);
            break;
        case SUBGAME_BUGGY:
            finished = sgLoopBuggy(&GameInfo);
            break;
        case SUBGAME_UNK_4:
            finished = 1;
            break;
    }
    if (finished != 0) {
        SubGame = SUBGAME_NONE;
    }
    return 0;
}
int sgLoopSubGame2(void) {
    if (SubGameRunning() == 0) {
        return 0;
    }
    switch (SubGame) {
        case SUBGAME_FISHING:
            sgLoopFishing2(&GameInfo);
            break;
        case SUBGAME_GYORACE:
        case SUBGAME_BUGGY:
        case SUBGAME_UNK_4:
            break;
    }
    return 0;
}
int sgExitSubGame(void) {
    int result = 0;
    if (SubGameRunning() == 0) {
        return 0;
    }
    switch (SubGame) {
        case SUBGAME_FISHING:
            result = sgExitFishing(&GameInfo);
            break;
        case SUBGAME_GYORACE:
        case SUBGAME_BUGGY:
        case SUBGAME_UNK_4:
            break;
    }
    SubGame = SUBGAME_NONE;
    return result;
}
int sgRestartSubGame(SubGameInfo *info) {
    int result = 0;
    if (SubGameRunning() == 0) {
        return 0;
    }
    switch (SubGame) {
        case SUBGAME_FISHING:
            result = sgRestartFishing(info);
            break;
        case SUBGAME_GYORACE:
        case SUBGAME_BUGGY:
        case SUBGAME_UNK_4:
            break;
    }
    return result;
}
int sgBreakSubGame(void) {
    int result = 0;
    if (SubGameRunning() == 0) {
        return 0;
    }
    switch (SubGame) {
        case SUBGAME_FISHING:
            result = sgBreakFishing();
            break;
        case SUBGAME_GYORACE:
        case SUBGAME_BUGGY:
        case SUBGAME_UNK_4:
            break;
    }
    SubGame = SUBGAME_NONE;
    return result;
}
int sgDrawSubGameMap(void) {
    if (SubGameRunning() == 0) {
        return 0;
    }
    if (SubGame != SUBGAME_GYORACE) {
        return 0;
    }
    return sgMapDrawGyoRace(&GameInfo);
}
int sgDrawSubGameCharaShadow(void) {
    if (SubGameRunning() == 0) {
        return 0;
    }
    switch (SubGame) {
        case SUBGAME_FISHING:
        case SUBGAME_GYORACE:
            break;
        case SUBGAME_BUGGY:
            return sgDrawShadowBuggy(&GameInfo);
        case SUBGAME_UNK_4:
            break;
    }
    return 0;
}
int sgDrawSubGameChara(void) {
    if (SubGameRunning() == 0) {
        return 0;
    }
    switch (SubGame) {
        case SUBGAME_FISHING:
            return sgDrawFishing(&GameInfo);
        case SUBGAME_GYORACE:
            return sgCharaDrawGyoRace(&GameInfo);
        case SUBGAME_BUGGY:
            return sgDrawBuggy(&GameInfo);
        default:
        case SUBGAME_UNK_4:
            return 0;
    }
}
int sgDrawSubGameEffect(void) {
    if (SubGameRunning() == 0) {
        return 0;
    }
    switch (SubGame) {
        case SUBGAME_GYORACE:
            return sgEffectDrawGyoRace(&GameInfo);
        case SUBGAME_BUGGY:
            return sgEffectDrawBuggy(&GameInfo);
        default:
            return 0;
    }
}
int sgDrawSubGameSystem(void) {
    if (SubGameRunning() == 0) {
        return 0;
    }
    switch (SubGame) {
        case SUBGAME_FISHING:
            return sgSystemDrawFishing(&GameInfo);
        case SUBGAME_GYORACE:
            return sgSysDrawGyoRace(&GameInfo);
        case SUBGAME_BUGGY:
            return sgSystemDrawBuggy(&GameInfo);
        default:
        case SUBGAME_UNK_4:
            return 0;
    }
}
void sgCPlayVoice::Open(int file) {
    if (step > SG_PLAY_VOICE_IDLE) {
        Close();
    }
    step = SG_PLAY_VOICE_OPEN;
    file_no = file;
    play = 0;
}
void sgCPlayVoice::SetVol(float left, float right) {
    float left_volume = left;
    float right_volume = right;
    if (left_volume < 0.0f) {
        left_volume = 0.0f;
    }
    if (!(left_volume <= 1.0f)) {
        left_volume = 1.0f;
    }
    vol_l = left_volume;
    if (right_volume < 0.0f) {
        right_volume = left_volume;
    }
    if (!(right_volume <= 1.0f)) {
        right_volume = 1.0f;
    }
    vol_r = right_volume;
}
void sgCPlayVoice::Play(void) {
    play = 1;
}
int sgCPlayVoice::Step(void) {
    char name[0x80];
    if (step <= 0) {
        return 0;
    }
    switch (step) {
        case SG_PLAY_VOICE_OPEN:
            sprintf(name, at_985__3, file_no);
            sndStreamOpenFast(name);
            step++;
            break;
        case SG_PLAY_VOICE_OPENING:
            if (sndStreamOpenState() == 0) {
                sndStreamStandBy();
                step++;
            }
            break;
        case SG_PLAY_VOICE_STANDBY:
            if (sndStreamOpenState() == 0) {
                step++;
            }
            break;
        case SG_PLAY_VOICE_READY:
            if (play != 0) {
                sndStreamSetVol(vol_l, vol_r);
                sndStreamPlay();
                step++;
            }
            break;
        case SG_PLAY_VOICE_PLAYING:
            if (sndStreamGetState() != SND_STREAM_STATE_PLAYING) {
                sndStreamClose();
                step = 0;
                return 0;
            }
            break;
    }
    return 1;
}
void sgCPlayVoice::Close(void) {
    if (step > 0) {
        sndStreamClose();
        step = 0;
    }
}

INCLUDE_RODATA("ps2/asm/pal/nonmatchings/subgame", at_985__3__DATA);

INCLUDE_BSS(SubGame, 0x4);
INCLUDE_BSS(MenuOpenFlag, 0x4);
INCLUDE_BSS(ItemOver, 0x4);
