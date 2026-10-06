#pragma once

#include "common.h"

class CCharacter2;
class CGameDataUsed;
class CSaveData;
class mgCCamera;
class mgCFrame;
class mgCMemory;
struct BG_READ_INFO;
struct mgVu0FBOX;

enum MenuFileLoadMode {
    MENU_FILE_LOAD_BG     = 0,
    MENU_FILE_LOAD_DIRECT = 1,
};

struct MENU_SPI_ANALYZE_STRUCT1 {
    char *name;
    int   value;
};

STATIC_ASSERT(sizeof(MENU_SPI_ANALYZE_STRUCT1) == 0x8);

int menu_spi_analyze_func_strcut1(MENU_SPI_ANALYZE_STRUCT1 *table, char *name);

struct MENU_COMMAND_ANALYZE_INFO {
    char   command_name[0x48];
    short *system_mes_buff[4];
    short *mes_buff[4];
};

STATIC_ASSERT(sizeof(MENU_COMMAND_ANALYZE_INFO) == 0x68);

int GetRandI(int limit);

float GetRandF(float limit);

float MenuAdjustPolygonScale(mgCFrame *frame, float size);

float MenuAdjustPolygonScale(mgVu0FBOX box, float size);

void MenuAdjustPolygonScale(CCharacter2 *chara, float size);

void AddRotationCharaY(CCharacter2 *chara, float angle);

void MenuSePlay(int se_no);

void MenuSePlay(unsigned int snd_id, int se_no);

void MenuSePlay(int se_no, unsigned int *sound, mgCMemory *stack);

void StopEnvSoundMenu(int stop_event);

void ReStartEnvSoundMenu();

int MenuSeiton(CGameDataUsed *items, int item_num);

int GetSameAdrressUserData(CGameDataUsed *item, int bag);

void local_sort1(int &select, int *num, int *list);

int GetNowChapter(CSaveData *save);

u_long128 *MenuCalcBufAlignment(u_long128 *buffer);

int LoadFileMenu(char *name, u_long128 *buffer, int mode);

void ConvertFontCode(char *src, char *dst);

int CheckNowEurope();

int MenuCommonReadData(mgCMemory *stack, char **names, int mode);

void MenuDeleteTextureBlock(int *blocks);

void MenuWorkTextureEnter(int block, char *name, int width, int height, int bpp);

void MenuEnterIMG(int block, unsigned char *img, char *name_suffix);

BG_READ_INFO *GetReadBGInfo(char *name);

void CalcMenu1(float target, float *value, float divisor, float snap_range, int snap);

void CalcMenu1(int target, int *value, int divisor, int snap_range, int snap);

int CalcMenuAdd(int *value, int step, int limit);

int CalcMenuAdd(float *value, float step, float limit);

int CalcMenuAdd2(int *value, int step, int limit);

int GetNumberKeta(int value);

int GetDispVolumeForFloat(float value);

float GetFloatCommaValue(float value);

int CalcScrlBarPutPos(int top, float pos, int length, float pos_max);

void Trans3DPosTo2DPos(mgCCamera *camera, mgCFrame *frame, int *screen_pos);

int MenuDataAnalyze(char *script, int size, mgCMemory *stack);

void MenuCommandAnalyze(char *script, int size, char *command_name);

extern u8 MenuSePlayUsedFlag;

extern mgCMemory *MenuSpiStack;

extern MENU_COMMAND_ANALYZE_INFO MenuCommandAnalyzeInfo;
