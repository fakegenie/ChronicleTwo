#include "dataread.hpp"
#include <cstdio>
#include "scenesnd.hpp"
#include "userdata.hpp"
#include "gamedata.hpp"
#include "scriptinterpreter.hpp"
#include "mglib.hpp"
#include "mainloop.hpp"
#include "menucls1.hpp"
#include "menusys.hpp"
#include "menumain.hpp"
#include "common.h"
#include "menusystemdata.hpp"
#include <cstring>

CMenuSystemData::CMenuSystemData() {
    MenuSystemDataInit();
}

void CMenuSystemData::MenuSystemDataInit() {
    memset(this, 0, 4);
}

int CMenuSystemData::CheckGetAlready(int item_no) {
    for (int i = 0; i < MENU_SYSTEM_GHOBI_NUM; i++) {
        if (ghobi[i].item_no == item_no) {
            return 1;
        }
    }
    return 0;
}

void CMenuSystemData::GetGhobi(int item_no) {
    int i = 0;
    do {
        if (ghobi[i].item_no <= 0) {
            ghobi[i].item_no = item_no;
            break;
        }
        i++;
    } while (i < MENU_SYSTEM_GHOBI_NUM);
    }
