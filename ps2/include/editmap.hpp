#pragma once

#include "common.h"

#include <libvu0.h>

#include "editinfo.hpp"
#include "editparts.hpp"
#include "map.hpp"
#include "mg_memory.hpp"
#include "mg_tanime.hpp"
#include "sceneload.hpp"

class mgCFrame;
class mgCMemory;
class CCPoly;
class CEditData;
class CEditGrid;
class CFuncPoint;
class CMapParts;
class CMapPiece;
class CObjAnimeEnv;
struct EMAP_MESSAGE;
struct InScreenFuncInfo;
struct MapEventInfo;
struct mgVu0FBOX;

enum {
    EDIT_MAP_HOUSE_MAX = 32,
    EDIT_MAP_GRID_MAX = 4,
    EDIT_MAP_RIVER_PARTS_MAX = 8,
    EDIT_MAP_MASK_PIECE_MAX = 1,
    EDIT_MAP_BALANCE_MAX = 4,
    EDIT_MAP_LOG_PER_PARTS = 4,
    EDIT_ANGLE_MAX = 24,
    EDIT_ANGLE_90 = 6,
    EP_PLACE_BASE_MAX = 16,
    EDIT_REMOVE_INFO_ID_MAX = 256,
    EDIT_REMOVE_HOUSE_MAX = 32,
};

enum EditBuildResult {
    EDIT_BUILD_NO_INFO = -1,
    EDIT_BUILD_NO_SLOT = -2,
    EDIT_BUILD_NO_HOUSE = -3,
};

struct EP_PLACE_INFO {
    s32 num;
    s32 base[EP_PLACE_BASE_MAX];
    s32 unk_44;
};

STATIC_ASSERT(sizeof(EP_PLACE_INFO) == 0x48);

struct EditPlaceLog {
    s16 parts_no;
    s16 base_no;
};

STATIC_ASSERT(sizeof(EditPlaceLog) == 0x4);

class CEditMap : public CMap {
public:

    struct RemoveInfo {
        s32 force;
        s32 color_num;
        float (*color)[4];
        s32 *paint_num;
        s32 parts_num[EDIT_REMOVE_INFO_ID_MAX];
        s32 house_num;
        s32 house_npc[EDIT_REMOVE_HOUSE_MAX];
    };

    mgCMemory parts_heap;
    s32 edit_parts_max;
    CEditParts *edit_parts;
    CEditHouse house[EDIT_MAP_HOUSE_MAX];
    s32 place_log_max;
    EditPlaceLog *place_log;
    s32 grid_max;
    CEditGrid *grid[EDIT_MAP_GRID_MAX];
    s32 focus_parts;
    s32 frame;
    mgCObjectStack<CList<EMAP_MESSAGE> > message;
    s32 area_no;
    s32 balance_weight[EDIT_MAP_BALANCE_MAX];
    CEditInfoMngr info_mngr;
    CMapParts *river_parts[EDIT_MAP_RIVER_PARTS_MAX];
    CEditPartsInfo *river_info;
    CMapPiece *river_piece[EDIT_MAP_RIVER_PARTS_MAX];
    CMapPiece *water_piece;
    CMapPiece *mask_piece[EDIT_MAP_MASK_PIECE_MAX];
    float river_poly_margin;
    s32 fence_num;
    CEditParts **fence_list;
    CEditParts *fence_now;
    sceVu0FVECTOR fence_color;
    s32 paint_num;
    u8 unk_1024[0x2C];
    s32 balance_moved;
    CMapParts *balance_parts[EDIT_MAP_BALANCE_MAX];
    sceVu0FVECTOR balance_pos[EDIT_MAP_BALANCE_MAX];
    sceVu0FVECTOR balance_base_pos[EDIT_MAP_BALANCE_MAX];

    CEditMap() {
        Initialize();
    }

    virtual int DrawSub(int direct);

    virtual int PreDraw(float *view_pos);

    virtual void DrawEffect();

    virtual void DrawFireEffect(int tex_block);

    virtual void DrawFireRaster();

    virtual int GetPoly(int kind, CCPoly *polys, mgVu0FBOX &box, int max);

    virtual CFuncPoint *GetEvent(float *pos, int check_type, MapEventInfo *info);

    virtual CFuncPoint *InScreenFunc(InScreenFuncInfo *info);

    virtual void DrawScreenFunc(mgCFrame *marker);

    virtual int GetSeSrcVolPan(int *se_no, float *vol, float *pan, int max);

    virtual void AnimeStep(CObjAnimeEnv *env);

    virtual void Step();

    virtual char *Iam();

    virtual void Initialize();

    void ClearGrid();

    void ClearHouse();

    void ClearAllParts();

    void InitialPlaceParts(CEditData *data);

    void CreateTable(mgCMemory *stack, int parts_max, int heap_size);

    CEditPartsInfo *GetePartsInfo(int no);

    CEditPartsInfo *GetePartsInfo(char *name);

    CEditPartsInfo *GetePartsInfoAtID(int id);

    CEditPartsInfo *GetePartsInfoAtType(int type);

    CEditPartsInfo *GetePartsInfoAtPlaceID(int no);

    int eNewPlaceParts();

    CEditHouse *eNewHouseInfo();

    CEditParts *GetePlaceParts(int no);

    CEditParts *GetePlaceParts(char *name);

    int GetePlaceIDList(int *out_no, int max);

    void GetRotMatrix(float (*out_matrix)[4], int angle);

    int GetEditAngle90(int angle);

    float GetEditAngle(int angle);

    int ConvEditAngle(float rot);

    int AngleLimit(int angle);

    void GetEditPos(float *out_pos, float *pos);

    int CmpEditAlt(float alt, float base_alt);

    float GetEditAlt(float alt);

    int GetGridPos(float *pos, float *out_pos, float *out_size);

    void GetMatrix(float (*out_matrix)[4], float *pos, int angle);

    void GetInversMatrix(float (*out_matrix)[4], float (*matrix)[4]);

    int ConvertParts(CEditParts *parts);

    int GetSameParts(int no);

    int BuildEditParts(int id);

    int GetTotalPolyn(int *out_polyn1, int *out_polyn2);

    int BuildEditParts(char *name);

    int DeleteEditParts(int no);

    int RemoveEditParts(int no, float *pos, RemoveInfo *info);

    int PlaceBurnParts();

    int BurnEditParts(RemoveInfo *info);

    CEditParts *PlaceEditParts(char *name, float *pos, float *rot);

    CEditParts *PlaceEditParts(int no, EP_PLACE_INFO *place, float *pos, float *rot, int *out_same);

    int PlaceRiverParts(float *pos);

    int CreatePlaceLog(int no, EP_PLACE_INFO *place);

    int GetNearParts(CEditPartsInfo *info, float *pos, float rot_y, CEditParts **out_parts, int max);

    int GetNearParts(mgVu0FBOX &box, CEditParts **out_parts, int max);

    int GetePlaceParts(float *pos);

    int GetePlaceParts(float *pos, CEditParts **parts, int num);

    int CheckEditParts(CEditPartsInfo *info, float *pos, float rot_y, EP_PLACE_INFO *place);

    float GetEditPartsAlt(CEditPartsInfo *info, float *pos, float rot_y);

    int MagnetParts(CEditPartsInfo *info, float *pos, float *rot, CEditParts **parts, int num);

    int MagnetParts(CEditPartsInfo *info, float *pos, float *rot);

    int CheckWallEditParts(CEditPartsInfo *info, float *pos, int wall_no, int base_no, EP_PLACE_INFO *place);

    void LoadEditInfo(char *script, int size, mgCMemory *stack);

    int PlaceRiver(float *pos);

    int RemoveRiver(float *pos);

    void CreateGrid(float *max, float *min, mgCMemory *stack, float *ofs);

    int GetRiverNum(float *sphere);

    int IsRiverGrid(float *pos);

    int GetRiverNum(int no, float range);

    void DrawRiverMask();

    void DrawRiver();

    void SaveData(CEditData *data);

    void LoadData(CEditData *data);

    int CultureAnalyzeParts(int no, int cpoint_no);

    int CultureAnalyze(int cpoint_no);

    int GetOnOffParts(char *name, CMapParts **out_parts, CMapPiece **out_piece, int max);

    void PartsOnOff(int map_no, CEditData *data);

    float GetEditPartsAlt(CEditPartsInfo *info, float *pos, float rot_y, CEditParts **parts, int num);

    int CheckEditParts(CEditPartsInfo *info, float *pos, float rot_y, EP_PLACE_INFO *place, CEditParts **parts, int num);

    int CheckEditPartsOnRiver(CEditPartsInfo *info, float *pos, float rot_y);

    int CheckRiverParts(float *pos);

    int CheckNormalPlaceParts(int no);

    int CheckNormalPlaceParts(CEditParts *parts);

    int CheckLiveNPC(int npc_no, int id);

    int GetePlacePartsAtInfoID(int id, int *out_no, int max);

    int GetTerritoryParts(int no, int *out_no, int max);

    int GetChildParts(int no, int *out_no, int max);

    int RePaintNum(int num);

    int PaintFence(int no, float *color, int num);

    int PaintFence(CEditParts *parts);

    void UpdateHouse();

    void GroundBalance(int keep);

    int BalanceCheck();
};

STATIC_ASSERT(sizeof(CEditMap::RemoveInfo) == 0x494);
STATIC_ASSERT(sizeof(CEditMap) == 0x10F0);
