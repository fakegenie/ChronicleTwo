#pragma once

#include "common.h"

#include <libvu0.h>

#include "effectlist.hpp"
#include "funcpoint.hpp"
#include "mapinfo.hpp"
#include "mg_drawenv.hpp"
#include "mg_frame.hpp"
#include "mg_tanime.hpp"
#include "occlusion.hpp"

class mgCCamera;
class mgCFrame;
class mgCMemory;
class mgCTexture;
class CCameraInfo;
class CCPoly;
class CFireRaster;
class CFuncPoint;
class CFuncPointCheck;
class CMapLightingInfo;
class CMapParts;
class CMapTreasureBox;
class CMdsInfo;
class CMdsListSet;
class CObjAnime;
class CObjAnimeEnv;
class CWaterFrame;
struct InScreenFuncInfo;

enum {
    MAP_FLAG_MAX = 128,
    MAP_PARTS_GROUP_MAX = 32,
    MAP_DRAW_RECT_MAX = 16,
    MAP_OCCLUSION_MAX = 8,
};

enum MapFixCamera {
    MAP_FIX_CAMERA_NONE = 0,
    MAP_FIX_CAMERA_POINT = 1,
    MAP_FIX_CAMERA_PATH = 2,
};

class CMapFlagData {
public:
    u32 flag[MAP_FLAG_MAX / 32];

    int SetFlag(int no, int on);

    int GetFlag(int no);
};

STATIC_ASSERT(sizeof(CMapFlagData) == 0x10);

struct PartsGroupData {
    CMapParts *parts;

    PartsGroupData() { parts = 0; }
};

STATIC_ASSERT(sizeof(PartsGroupData) == 0x4);
STATIC_ASSERT(sizeof(CList<PartsGroupData>) == 0x10);
STATIC_ASSERT(sizeof(CList<CMapParts *>) == 0x10);

class CPartsGroup {
public:
    CPartsGroup() { Initialize(); }

    char *name;
    s32 off;
    s32 camera_off;
    CList<PartsGroupData> *list;

    void Initialize();

    void Add(CList<PartsGroupData> *entry);
};

STATIC_ASSERT(sizeof(CPartsGroup) == 0x10);

struct MapDrawOffRect {
    MapDrawOffRect() {
        outside = 0;
        used = 0;
        parts = NULL;
    }

    mgVu0FBOX area;
    s32 used;
    s32 outside;
    CList<CMapParts *> *parts;
};

STATIC_ASSERT(sizeof(MapDrawOffRect) == 0x30);

struct MapEventInfo {
    s32 check_type;
    s32 event_no;
    sceVu0FMATRIX matrix;
    s32 parts_no;
    s32 point_no;
};

STATIC_ASSERT(sizeof(MapEventInfo) == 0x60);

class CObject : public mgCObject {
public:
    float far_dist;
    s32 fade;
    float fade_alpha;
    float fade_speed;
    float near_dist;
    s32 show;
    s32 draw_off;

    CObject() { Initialize(); }

    virtual int Draw();

    virtual int DrawDirect();

    virtual void Initialize();

    virtual int PreDraw();

    virtual float GetCameraDist();

    virtual int FarClip(float dist, float *out_alpha);

    virtual void DrawStep();

    virtual float GetAlpha();

    virtual void Show(int on) { show = on; }

    virtual int GetShow() { return show; }

    virtual void SetFarDist(float dist) { far_dist = dist; }

    virtual float GetFarDist() { return far_dist; }

    virtual void SetNearDist(float dist) { near_dist = dist; }

    virtual float GetNearDist() { return near_dist; }

    virtual int CheckDraw();

    virtual void Copy(CObject &dest, mgCMemory *stack) { dest = *this; }

    void GetMatrix(float (*out_matrix)[4]);
};

STATIC_ASSERT(sizeof(CObject) == 0x70);

class CMapWater : public CObject {
public:
    CWaterFrame *frame;
    sceVu0IVECTOR follow;
    char *parts_name;
    s32 parts_max;
    s32 parts_num;
    CMapParts **parts;

    CMapWater();

    virtual void Initialize();

    void Clear();
};

STATIC_ASSERT(sizeof(CMapWater) == 0xA0);

class CMap : public CMapInfo {
public:
    CMdsListSet *mds_list_set;
    CList<CMapParts> *parts_list;
    s32 parts_group_max;
    CPartsGroup parts_group[MAP_PARTS_GROUP_MAX];
    s32 unk_30c;
    CEffectList effect_list;
    s32 place_parts_max;
    CMapParts *place_parts;
    s32 place_parts_num;
    s32 bbox_valid;
    mgVu0FBOX bbox;
    s32 draw_parts_num;
    CMapParts **draw_parts;
    s32 draw_rect_max;
    MapDrawOffRect draw_rect[MAP_DRAW_RECT_MAX];
    s32 occlusion_num;
    COcclusion occlusion[MAP_OCCLUSION_MAX];
    s32 camera_info_num;
    CCameraInfo *camera_info;
    float now_time;
    s32 obj_anime_num;
    CObjAnime *obj_anime;
    s32 tr_box_texture;
    s32 tr_box_num;
    CMapTreasureBox *tr_box;
    CMapTreasureBox *tr_box_model;
    s32 unk_ca4;
    s32 piece_load_skip;
    s32 parts_event;
    CFuncPointMngr func_point;
    float anime_time;
    s32 anime_frame;
    s32 water_surface_num;
    CWaterFrame **water_surface;
    s32 water_num;
    CMapWater *water;
    CFireRaster *fire_raster;

    virtual int DrawSub(int direct);

    virtual int Draw() { return DrawSub(0); }

    virtual int DrawDirect() { return DrawSub(1); }

    virtual int PreDraw(float *view_pos);

    virtual void DrawEffect();

    virtual void DrawFireEffect(int tex_block);

    virtual void DrawFireRaster();

    virtual void DrawWater(mgCCamera *camera, mgCTexture *screen, mgCTexture *overlay);

    virtual int GetPoly(int kind, CCPoly *polys, mgVu0FBOX &box, int max);

    virtual int GetColPoly(CCPoly *polys, mgVu0FBOX &box, int max);

    virtual int GetCameraPoly(CCPoly *polys, mgVu0FBOX &box, int max);

    virtual CFuncPoint *GetEvent(float *pos, int check_type, MapEventInfo *info);

    virtual CFuncPoint *InScreenFunc(InScreenFuncInfo *info);

    virtual void DrawScreenFunc(mgCFrame *marker);

    virtual int GetSeSrcVolPan(int *se_no, float *vol, float *pan, int max);

    virtual void AnimeStep(CObjAnimeEnv *env);

    virtual void Step();

    virtual char *Iam();

    virtual void Initialize();

    CMap();

    CPartsGroup *GetPartsGroup(int no);

    int AddPartsGroup(char *name, CMapParts *parts, mgCMemory *stack);

    CPartsGroup *SearchPartsGroup(char *name);

    int SearchPartsGroupNo(char *name);

    int SerachEmptyPartsGroupNo();

    void SetPlacePartsBuff(mgCMemory *stack, int max);

    CMapParts *GetPlacPartsTable(int *out_max);

    void SetCameraInfoTable(CCameraInfo *table, int num);

    CCameraInfo *GetCameraInfo(int no);

    CMapParts *NewPlaceParts();

    CMdsInfo *SearchMDS(char *name);

    void CreateEffect(unsigned int *pack, int tex_block, mgCMemory *stack);

    int SaerchEffectIndex(char *name);

    void AddParts(CList<CMapParts> *parts);

    CMapParts *GetParts(char *name);

    void CreateDrawRect(mgCMemory *stack, mgVu0FBOX *area, mgVu0FBOX *parts_box, int outside);

    void CreateOcclusion(float (*corner)[4]);

    CMapParts *PlaceParts(char *name, float *pos, float *rot, float *scale, mgCMemory *stack);

    void PlacePartsEnd();

    void ClearPlaceParts();

    CMapParts *GetPlaceParts(char *name);

    CMapParts *GetPlaceParts(int no);

    int ConvertParts(CMapParts *parts);

    int GetPlaceParts(mgVu0FBOX *box, CMapParts **out_parts, int max);

    int GetPlaceColParts(mgVu0FBOX *box, CMapParts **out_parts, int max);

    void CreateFuncCheck(CFuncPointCheck *check);

    int GetBBox(mgVu0FBOX *out_box);

    int GetCharaLight(mgCObject *chara, CFuncPoint *points, int max, int use_parts);

    int SetFuncPLight(float *pos, CFuncPointCheck *check);

    void ResetFuncPLight(int num);

    void DrawTrBox();

    int GetTrBoxColPoly(CCPoly *polys, float *pos, int max);

    int GetFixCameraPos(float *pos, float *out_camera_pos);

    void FixCameraPartsOnOff(float *camera_pos);

    void EffectStep();

    void CreateMap(CMdsListSet *mds_list_set, mgCMemory *stack);

    void AssignFuncPoint(mgCMemory *stack);

    void CreateTrBox(CMapTreasureBox *model, int tex_block, mgCMemory *stack);

    CMapTreasureBox *GetTrBox(int no);

    void DeleteTrBox(int no, CMapFlagData *flags);

    void UpdateTrBoxFlag(CMapFlagData *flags);

    void LoadData(unsigned int *pcp_pack, unsigned int *img_pack, int *tex_block, mgCMemory *stack);

    float GetNowTime();

    int GetNowTimeBand();

    int GetNowTimeLightBand();

    void GetLightingRatio(float *out_ratio);

    void GetLightingFlareRatio(float *out_ratio);

    void GetLightingSunRatio(float *out_ratio);

    int GetTimeLightingRatio(float *out_ratio);

    void GetSunPoint(float *out_pos);

    float GetLightNoTime(int light_no);

    int GetTimeEnable();

    void GetLightInfo(CMapLightingInfo *out_info);

    CMapLightingInfo *GetLightingInfo(int no);

    int GetActiveLightNo();

    void GetLightInfo(CMapLightingInfo *out_info, float *ratio, int num);

    void LoadMapFile(char *script, int size, mgCMemory *stack, int add_mode);

    void SetPieceLoadSkip(int skip);

    void LoadCfgFile(char *script, int size, mgCMemory *stack);
};

STATIC_ASSERT(sizeof(CMap) == 0xD10);

extern char *CMapName;

int CheckFuncEvent(CFuncPoint *point, float *pos, int check_type, MapEventInfo *info, float *out_dist);
