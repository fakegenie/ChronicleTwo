#pragma once

#include "common.h"

#include <libvu0.h>

#include "character.hpp"
#include "funcpoint.hpp"
#include "map.hpp"
#include "mg_drawenv.hpp"
#include "mg_frame.hpp"
#include "mg_tanime.hpp"

class CCPoly;
class CFuncPoint;
class CMapPiece;
class CObjAnime;
class CObjAnimeEnv;
class COcclusion;
class mgCMemory;

#define MAP_PARTS_COLOR_MAX 4

struct InScreenFuncInfo {
    float range;
    float unk_04;
    float dist;
};

STATIC_ASSERT(sizeof(InScreenFuncInfo) == 0xC);

class CMapParts : public CObject {
public:
    char                       name[32];
    char                       parts_name[32];
    CList<CMapPiece>          *piece_list;
    mgCFrame                   frame;
    s32                        lod_num;
    s32                        lod_blend;
    float                     *lod_dist;
    s32                        minimap_tile;
    float                      fixed_time;
    s32                        need_step;
    s32                        color_num;
    sceVu0FVECTOR              color[MAP_PARTS_COLOR_MAX];
    s32                        bound_valid;
    mgVu0FBOX                  bound_box;
    sceVu0FVECTOR              bound_sphere;
    s32                        col_bound_valid;
    mgVu0FBOX                  col_bound_box;
    sceVu0FVECTOR              col_bound_sphere;
    CFuncPointMngr             func_point_mngr;
    s32                        no_light;
    s32                        no_plight;
    u32                        move_flag;
    CList<CObjAnime>          *anime_list;
    s32                        group_no;
    s32                        in_screen;
    CFuncPointCheck            func_check;

    CMapParts();

    virtual int Draw();

    virtual int DrawDirect();

    virtual void Initialize();

    virtual int PreDraw();

    virtual void DrawStep();

    virtual void Step();

    virtual void AnimeStep(CFuncPointCheck *check, CObjAnimeEnv *env);

    virtual void UpDatePosition();

    virtual void Copy(CMapParts &dest, mgCMemory *memory);

    void SetName(char *new_name);

    void SetPartsName(char *new_name);

    void AddPiece(CList<CMapPiece> *piece);

    CMapPiece *SearchPiece(char *piece_name);

    CMapPiece *SearchPieceColType(int col_type);

    int GetPoly(int kind, CCPoly *poly, mgVu0FBOX &box, int max);

    int GetColPoly(CCPoly *poly, mgVu0FBOX &box, int max);

    int GetCameraPoly(CCPoly *poly, mgVu0FBOX &box, int max);

    int SetColor(int no, float *rgba);

    int GetColor(int no, float *out_rgba);

    int GetDefColor(int no, float *out_rgba);

    void UpdateColor();

    int DrawSub(int direct);

    int CreateBoundBox();

    int CheckColBox(mgVu0FBOX *box);

    int GetBBox(mgVu0FBOX *out_box);

    int GetBoundBox(mgVu0FBOX *out_box);

    int GetBoundSphere(float *out_sphere);

    void GetLWMatrix(sceVu0FMATRIX out_matrix);

    int InsideScreen();

    int InsideScreen(COcclusion *occlusion, int occlusion_num);

    CFuncPoint *InScreenFunc(InScreenFuncInfo *info);

    void DrawScreenFunc(mgCFrame *marker);

    void StepFuncPoint(CFuncPointCheck &check);

    void CopyFuncPointCheck(CFuncPointCheck &check);

    int AssignFuncAnime(mgCMemory *memory);

    void SetLODDist(float *dist, int num) {
        lod_num = num;
        lod_dist = dist;
    }

    void SetLODBlend(int blend) { lod_blend = blend; }

    int GetLODBlend() { return lod_blend; }
};

STATIC_ASSERT(sizeof(CMapParts) == 0x310);

class CMapTreasureBox : public CCharacter2 {
public:
    s32         active;
    s32         flag_no;
    s32         item_no;
    s32         item_num;
    s32         floor_id;
    CFuncPoint *func_point;
    CMapParts  *parts;

    CMapTreasureBox();

    virtual void Initialize();

    int AssignFuncPoint(CFuncPoint *point, CMapParts *owner);

    void GetWorldPosition(float *out_position);
};

STATIC_ASSERT(sizeof(CMapTreasureBox) == 0x680);
