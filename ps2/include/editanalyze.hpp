#pragma once

#include "common.h"

class CEditData;

class CEditMap;
class CEditParts;

enum EditAnalyzeMap {
    EDIT_ANALYZE_MAP_SHARLOT     = 0,
    EDIT_ANALYZE_MAP_STERA       = 1,
    EDIT_ANALYZE_MAP_BENIETIO    = 2,
    EDIT_ANALYZE_MAP_HEIM        = 3,
    EDIT_ANALYZE_MAP_MOON_FLOWER = 4,
};

void AnalyzeEditMap(int map_no, CEditMap *edit_map);

int CountPartsType(int parts_type, CEditMap *edit_map, int *list, int num);

int CountPartsInfoID(int info_id, CEditMap *edit_map, int *list, int num);

int GetHouseParts(CEditMap *edit_map, int *list, int max);

CEditParts *GetPartsPos(CEditMap *edit_map, int no, float *pos);

int CheckLiveChara(int map_no, CEditMap *edit_map, int no, int chara);

void EditMapInitEvent(int map_no, CEditMap *edit_map);

void AnalyzeSharlot(CEditData *data, CEditMap *map);

void AnalyzeStera(CEditData *data, CEditMap *map);

void AnalyzeBenietio(CEditData *data, CEditMap *map);

void AnalyzeHeim(CEditData *data, CEditMap *map);

void AnalyzeMoonFlower(CEditData *data, CEditMap *map);

int GetColorType(CEditParts *parts, int no);
