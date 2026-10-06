#pragma once

#include "common.h"
#include "mg_visual.hpp"

class mgCMemory;
class mgCFace;
class mgCDrawManager;
class mgCTextureManager;
class mgRENDER_INFO;
struct FACES_ID;
struct MDT_HEADER;

class mgCShadowMDT : public mgCVisualMDT {
public:
    virtual int CreateRenderInfoPacket(u_int *packet, float (*matrix)[4], mgRENDER_INFO *info);

    virtual u_int CreatePacket(mgCDrawManager *manager);

    virtual int CreateFacePacket(u_int *packet, mgCFace *face);

    virtual FACES_ID *CreateFace(FACES_ID *faces, mgCMemory *memory, mgCMemory *index_memory, mgCFace **face);

    virtual int DataAssignMDT(MDT_HEADER *header, mgCMemory *memory, mgCTextureManager *texture_manager);
};
STATIC_ASSERT(sizeof(mgCShadowMDT) == 0x50);

class mgCShadowFixMDT : public mgCShadowMDT {
public:
};
STATIC_ASSERT(sizeof(mgCShadowFixMDT) == 0x50);
