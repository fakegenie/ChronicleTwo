#include "common.h"
#include "gaiji.hpp"
#include "dataread.hpp"
#include "mainloop.hpp"

static u_char *FontTex_2_Buff;

u_char GaijiBuff[0x11800];

int LoadGaijiImg() {
    int size;
    switch (LanguageCode) {
    case LANG_JAPANESE:
        LoadFile("meswin/jpn/gaiji.img", GaijiBuff, &size);
        break;
    case LANG_FRENCH:
        LoadFile("meswin/eu/fra/gaiji.img", GaijiBuff, &size);
        break;
    case LANG_GERMAN:
        LoadFile("meswin/eu/ger/gaiji.img", GaijiBuff, &size);
        break;
    case LANG_ITALIAN:
        LoadFile("meswin/eu/ita/gaiji.img", GaijiBuff, &size);
        break;
    case LANG_SPANISH:
        LoadFile("meswin/eu/spn/gaiji.img", GaijiBuff, &size);
        break;
    case LANG_ENGLISH:
    default:
        LoadFile("meswin/usa/gaiji.img", GaijiBuff, &size);
        break;
    }
    return size;
}

u_char *GetGaijiImgPtr() {
    return GaijiBuff;
}

int LoadFontTex2Img() {
    if (FontTex_2_Buff == 0) {
        return 0;
    }
    if (LanguageCode != LANG_JAPANESE) {
        return 0;
    }
    int size;
    LoadFile("meswin/font2.img", FontTex_2_Buff, &size);
    return size;
}

u_char *GetFontTex2ImgPtr() {
    return FontTex_2_Buff;
}
