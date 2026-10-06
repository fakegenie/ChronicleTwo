#pragma once

#include "common.h"

class CActiveMonster;
class CCharacter2;
class CColPrim;
class CScene;
class mgCMemory;
class mgCTexture;

extern mgCTexture *TEX_ShadowTexture;

extern mgCTexture *TEX_SystenFrame;

extern mgCTexture *TEX_SystenFrame2;

extern mgCTexture *TEX_StatusIcon;

extern mgCTexture *TEX_DummyIcon1;

extern mgCTexture *TEX_DummyIcon2;

extern mgCTexture *TEX_SystemEffect1;

extern mgCTexture *TEX_SystemEffect2;

extern mgCTexture *TEX_SystemEffect3;

extern mgCTexture *TEX_SystemEffectSw;

extern mgCTexture *TEX_ExFx_FIRE;

extern mgCTexture *TEX_ExFx_ICE;

extern mgCTexture *TEX_ExFx_THUN;

void GetTextureInfo(CScene *scene);

void MainTextureInterface(mgCMemory *stack, CScene *scene);

void calcWeaponParamWhp(CActiveMonster *monster, CColPrim *col_prim);

void calcWeaponParam2(int type, int divisor);

void SetDamageParam(CColPrim *col_prim, int chara_no);

void AddExpWeaponParam(float exp, int chara_no, int type);

void SetSwordBlurEffect(CCharacter2 *chara, mgCMemory *stack, int blur_type);
