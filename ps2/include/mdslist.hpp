#pragma once

#include "common.h"

#include "object.hpp"

class CCharacter2;
class mgCEnterIMGInfo;
class mgCFrame;
class mgCMemory;
class PieceMaterial;
struct CCPoly;
struct mgVu0FBOX;

enum MdsType {
    MDS_TYPE_MODEL            = 0,
    MDS_TYPE_COLLISION        = 1,
    MDS_TYPE_CAMERA_COLLISION = 3,
    MDS_TYPE_CHARA            = 4,
};

class CMdsInfo {
public:
    char        *name;
    int          type;
    mgCFrame    *frame;
    CCharacter2 *chara;
    float        far_dist;
    int          far_fade;

    CMdsInfo();

    virtual void Initialize();

    int unk_1c;
};

STATIC_ASSERT(sizeof(CMdsInfo) == 0x20);

class CMdsList {
public:
    char     *name;
    int       num;
    CMdsInfo *list;
    int       unk_c;

    CMdsInfo *GetList(int index);

    int GetListID(char *name);

    CMdsInfo *GetList(char *name);

    void LoadPCPFile(char *name, unsigned int *pack, mgCMemory *stack, int all_scissor);
};

STATIC_ASSERT(sizeof(CMdsList) == 0x10);

class CIMGList {
public:
    char            *name;
    mgCEnterIMGInfo *info;

    int LoadIMGFile(char *name, mgCEnterIMGInfo *info, mgCMemory *stack);
};

STATIC_ASSERT(sizeof(CIMGList) == 0x8);

class CMdsListSet {
public:
    CMdsListSet() { Initialize(); }
    int      mds_list_num;
    u_char       unk_4[0xC];
    CMdsList mds_list[8];
    int      img_list_num;
    CIMGList img_list[16];

    CMdsList *SearchMdsList(char *name);

    CMdsList *GetMdsList(int index);

    CMdsInfo *SearchMDS(char *name);

    int LoadPCPFile(char *name, unsigned int *pack, mgCMemory *stack, int all_scissor);

    int DeleteMdsList(char *name);

    int LoadIMGFile(char *name, mgCEnterIMGInfo *info, mgCMemory *stack);

    void DeleteIMG(char *name);

    CIMGList *SearchIMGList(char *name);

    int GetTextureBlockNo(int group, int *out_block, int max);

    void Initialize();
};

class CMapPiece : public CObjectFrame {
public:
    char          *name;
    int            type;
    int            draw_enable;
    int            material_num;
    PieceMaterial *material;
    float          time_start;
    float          time_end;
    CCharacter2   *chara;
    short            col_type;
    short            col_param;

    CMapPiece() { Initialize(); }

    void SetName(char *name) { this->name = name; }

    void SetMaterial(PieceMaterial *material, int num) {
        this->material = material;
        material_num   = num;
    }

    virtual void Initialize();

    virtual int DrawDirect();

    virtual int Draw();

    int AssignMds(CMdsInfo *info);

    int GetPoly(int type, CCPoly *poly, mgVu0FBOX &box, int max);

    void SetTimeBand(float start, float end);

    PieceMaterial *GetMaterial(int index);

    void Step();

    int GetBoundBox(mgVu0FBOX *box);

    int DrawSub(int direct);

    void Copy(CMapPiece &dest, mgCMemory *stack);
};

STATIC_ASSERT(sizeof(CMapPiece) == 0xB0);
