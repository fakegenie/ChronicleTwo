#pragma once

#include "common.h"

class mgCMemory;
class mgCTexture;
struct sceVif1Packet;

enum {
    MG_TEX_ANIME_GROUP_MAX = 24,
};

enum mgTEX_ANIME_TYPE {
    MG_TEX_ANIME_TYPE_NONE = -1,
    MG_TEX_ANIME_TYPE_COPY = 0,
    MG_TEX_ANIME_TYPE_SCROLL = 1,
    MG_TEX_ANIME_TYPE_WAVE = 2,
};

enum {
    MG_TEX_ANIME_ALPHA_BLEND_OFF = 4,
    MG_TEX_ANIME_ALPHA_TEST_OFF = -1,
    MG_TEX_ANIME_WAIT_FOREVER = -1,
};

enum mgTEX_ANIME_CONST {
    MG_TEX_ANIME_SUBTEXEL = 16,
    MG_TEX_ANIME_BPP_INDEXED = 8,
    MG_TEX_ANIME_BPP_TRUE_COLOUR = 24,
    MG_TEX_ANIME_AMPLITUDE_FULL = 10000,
    MG_TEX_ANIME_FRAME_ALIGN = 64,
    MG_TEX_ANIME_NAME_ALLOC_UNIT = 16,
};

template <class T>
class mgRect {
public:
    T left;
    T top;
    T right;
    T bottom;

    mgRect() { Set(0, 0, 0, 0); }

    mgRect(T new_left, T new_top, T new_right, T new_bottom) { Set(new_left, new_top, new_right, new_bottom); }

    void Set(T new_left, T new_top, T new_right, T new_bottom);
} __attribute__((aligned(16)));

template <>
class mgRect<short> {
public:
    short left;
    short top;
    short right;
    short bottom;

    mgRect() { Set(0, 0, 0, 0); }
    mgRect(short new_left, short new_top, short new_right, short new_bottom) {
        Set(new_left, new_top, new_right, new_bottom);
    }
    void Set(short new_left, short new_top, short new_right, short new_bottom) {
        left = new_left;
        top = new_top;
        right = new_right;
        bottom = new_bottom;
    }
};

template <class T>
void mgRect<T>::Set(T new_left, T new_top, T new_right, T new_bottom) {
    left = new_left;
    top = new_top;
    right = new_right;
    bottom = new_bottom;
}

template <>
inline mgRect<int>::mgRect() {}

template <>
void mgRect<int>::Set(int new_left, int new_top, int new_right, int new_bottom);

template <>
inline mgRect<float>::mgRect() { Set(0, 0, 0, 0); }

template <>
void mgRect<float>::Set(float new_left, float new_top, float new_right, float new_bottom);

STATIC_ASSERT(sizeof(mgRect<int>) == 0x10);

template <class T>
class CList {
public:
    CList<T> *next;
    CList<T> *prev;
    T data;

    CList() { Initialize(); }

    T *pGetData() { return &data; }

    virtual void Initialize();
};

template <class T>
void CList<T>::Initialize() {
    prev = 0;
    next = 0;
}

class mgCTexAnimeData {
public:
    signed char type;
    signed char group;
    signed char link_group;
    u_char clut_copy;
    mgCTexture *src_tex;
    mgCTexture *dest_tex;
    short src_x;
    short src_y;
    short src_w;
    short src_h;
    short dest_x;
    short dest_y;
    short dest_w;
    short dest_h;
    short period_x;
    short period_y;
    short phase_x;
    short phase_y;
    short amplitude_x;
    short amplitude_y;
    short wait;
    short bug_patch;
    u_char bilinear;
    u_char alpha_blend;
    signed char alpha_test;
    u_char alpha_ref;
    u_char r;
    u_char g;
    u_char b;
    u_char a;

    mgCTexAnimeData();

    void Initialize();
};

STATIC_ASSERT(sizeof(mgCTexAnimeData) == 0x34);
STATIC_ASSERT(sizeof(CList<mgCTexAnimeData>) == 0x40);

class mgCTextureAnime {
public:

    static int stop_anime;

    int group_num;
    int enable[MG_TEX_ANIME_GROUP_MAX];
    CList<mgCTexAnimeData> *list[MG_TEX_ANIME_GROUP_MAX];
    CList<mgCTexAnimeData> *now[MG_TEX_ANIME_GROUP_MAX];
    char *name[MG_TEX_ANIME_GROUP_MAX];
    int frame[MG_TEX_ANIME_GROUP_MAX];

    void TexAnime(int texb, sceVif1Packet *packet);

    void Initialize();

    mgCTextureAnime();

    void SetGroupName(int group, char *group_name);

    int GetEmptyGroup();

    int SearchGroupName(char *group_name);

    CList<mgCTexAnimeData> *NewTexAnimeData(mgCMemory *stack);

    CList<mgCTexAnimeData> *NewTexAnimeGroupData(int group, mgCMemory *stack);

    int EnterTexAnime(mgCTexAnimeData *data, mgCMemory *stack);

    void DeleteGroup(int group);

    void DisableAll();

    void Enable(int group);

    void Disable(int group);

    CList<mgCTexAnimeData> *GetAnimeList(int group);
};

STATIC_ASSERT(sizeof(mgCTextureAnime) == 0x1E4);
