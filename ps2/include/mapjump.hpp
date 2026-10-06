#pragma once

#include "common.h"

class mgCMemory;
class CScene;
struct SCN_LOADMAP_INFO2;

class MapJumpMapInfo {
public:
    s32 map_no;
    s32 tex_block;
    s32 stack_no;
    s32 efp_tex_block;
    s32 sky_tex_block;
    u8 *load_buf;

    MapJumpMapInfo();
};
STATIC_ASSERT(sizeof(MapJumpMapInfo) == 0x18);

int GetMainMapNo();

int GetSubMapNo();

void ClearSubMapNo();

void SetMainMapInfo(MapJumpMapInfo *info);

void SetSubMapInfo(MapJumpMapInfo *info);

void SetScriptBuffer(mgCMemory *buffer);

void PreLoadSync();

int MapJump(CScene *scene, SCN_LOADMAP_INFO2 *info, int map_no);

int GetLoadMapInfo(SCN_LOADMAP_INFO2 *info, int map_no);

int LoadSubMap(CScene *scene, int map_no, int background);

void LoadMapScript(char *map_name);

void ReloadMapScript();

void LoadScript(char *file_name);

int GetOldInteriorMapNo();

void InitInterior();

int InInterior();

void SaveBeforeInterior(CScene *scene);

void SetInteriorDoorPos(CScene *scene);

void GotoInterior(CScene *scene, int map_no);

void DeleteInterior(CScene *scene);

void ExitInterior(CScene *scene, int *sub_map_no);

int InteriorMapJump(CScene *scene, int map_no);
