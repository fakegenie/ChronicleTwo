#pragma once

#include "common.h"

#include <libvu0.h>

#include "editparts.hpp"

class CEditMap;
class CMap;
class CScene;
class mgCMemory;
struct EP_PLACE_INFO;

enum EditModeType {
    EDIT_MODE_NONE = 0,
    EDIT_MODE_PLACE = 2,
    EDIT_MODE_REMOVE = 3,
    EDIT_MODE_PAINT = 8,
    EDIT_MODE_REPAINT = 0x10,
};

enum EditPutSideMode {
    EDIT_PUT_SIDE_OFF = 0,
    EDIT_PUT_SIDE_SELECT = 1,
    EDIT_PUT_SIDE_MOVE = 2,
};

enum EditHelpMes {
    EDIT_HELP_NONE = -1,
    EDIT_HELP_PLACE = 0,
    EDIT_HELP_PLACE_WALL = 1,
    EDIT_HELP_PLACE_MAGNET = 2,
    EDIT_HELP_REMOVE = 3,
    EDIT_HELP_SELECT_WALL = 4,
    EDIT_HELP_PAINT = 5,
    EDIT_HELP_PAINT_HOUSE = 6,
    EDIT_HELP_PAINT_FENCE = 7,
    EDIT_HELP_REPAINT = 8,
    EDIT_HELP_REPAINT_HOUSE = 9,
    EDIT_HELP_REPAINT_FENCE = 10,
    EDIT_HELP_UNDO = 11,
};

struct UNDO_DATA {
    s32           info_id;
    s32           parts_no;
    s32           unk_8;
    s32           unk_c;
    sceVu0FVECTOR pos;
    sceVu0FVECTOR rot;
};

STATIC_ASSERT(sizeof(UNDO_DATA) == 0x30);

extern sceVu0FVECTOR WallPutPos;

extern CEditParts::WallInfo WallInfo;

void EditModeControlLock();

void EditModeControlUnLock();

void EditPreMenuAnime(int frames);

void LoadEditCursor(mgCMemory *stack, int block);

int GetSelPartsInfoID();

void ClearUndoFlag();

void ClearEditFlag();

void InitEditFlag();

int StartEditMode(CScene *scene);

void EndEditMode(CScene *scene, float *pos);

int StartEditModeFromMenu(CScene *scene, int mode, int *arg);

void StartEditPutWall(CEditParts::WallInfo *wall);

int PlaceEditParts(CEditMap *map, float *pos, float *rot, EP_PLACE_INFO *place);

void PlaceRiverStart(CEditMap *map, float *pos);

int PlaceRiverStep(CEditMap *map);

int NowPlaceRiver();

void RemoveMtnStart(CEditMap *map, float *pos, float *cursor_pos);

int RemoveMtnStep(CScene *scene);

int RemoveEditParts(CScene *scene, int parts_no, float *pos);

int DeleteKanketuParts(CScene *scene, CEditMap *map, float *pos, int parts_no);

int PaintEditParts(CEditMap *map, int parts_no, int color_no, float *color);

void EditMode(CScene *scene);

void DrawEditCursorParts(CScene *scene);

void DrawEditCursor(CScene *scene);

void DrawEditHelpMes();

void DrawEditSystem(int block, CScene *scene, float *pos, int edit);

int CheckWalkToEdit(CScene *scene, float *pos);

int CheckEditToWalk(CScene *scene, float *out_pos);
