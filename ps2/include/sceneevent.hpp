#pragma once
#include <cstring>

#include "common.h"

#include <libvu0.h>

#include "map.hpp"
#include "mapload.hpp"

struct EventFloat2 { float v[2];   };
struct EventFloat4 { float v[4];   };
struct EventVector2 { u_long128 v[2];   };
struct EventVector4 { u_long128 v[4];   };

#pragma push
#pragma cpp_extensions on
struct CSceneEventData {
    CSceneEventData() { memset(this, 0, sizeof(*this)); }
    union {
        struct {
    CFuncPoint::EventData event;
    sceVu0FVECTOR         position;
    sceVu0FVECTOR         rotation;
    sceVu0FVECTOR         scale;
    MapEventInfo          map_event;
            int chara_no;
            int chara_slot;
            int gameobj_no;
            int unk_cc;
};
        struct {
            EventFloat4 head;
            EventFloat4 group_1;
            EventFloat2 group_2;
            EventFloat4 group_3 __attribute__((aligned(16)));
            EventFloat4 group_4;
            EventFloat4 group_5;
            EventVector4 vectors_a;
            EventVector2 vectors_b;
        };
    };
};
#pragma pop

STATIC_ASSERT(sizeof(CSceneEventData) == 0xD0);
