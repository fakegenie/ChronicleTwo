#pragma once

#include "common.h"

#include "map.hpp"

class mgCFrame;
class mgCMemory;

class CObjectFrame : public CObject {
public:
    mgCFrame *frame;

    CObjectFrame() { Initialize(); }

    mgCFrame *GetFrame() {
        return frame;
    }

    virtual int Draw();

    virtual int DrawDirect();

    virtual void Initialize();

    virtual int PreDraw();

    virtual float GetCameraDist();

    virtual void DrawStep();

    virtual void UpDatePosition();

    virtual void Copy(CObjectFrame &dest, mgCMemory *memory);
};

STATIC_ASSERT(sizeof(CObjectFrame) == 0x80);
