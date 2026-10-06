#include "common.h"
#include "mg_memory.hpp"
#include "mglib.hpp"
#include "scriptinterpreter.hpp"
#include <cstring>
#include "editmap.hpp"
#include "dbg_font.hpp"
#include "menucommon.hpp"
#include "menudraw.hpp"
#include "gamepad.hpp"
#include "scene.hpp"
#include "editdebug.hpp"
#include "dataread.hpp"
#include "cameracontrol.hpp"
#include "editloop.hpp"
#include "font.hpp"
#include "mainloop.hpp"
#include "map.hpp"
#include "mapjump.hpp"
#include "menuaqua.hpp"
#include "mg_drawprim.hpp"
#include "mg_math.hpp"
#include "savedata.hpp"
#include "scenesnd.hpp"
#include "userdata.hpp"
#include <cstdio>

extern char at_1028__2[];
extern char at_1029__2[];

extern int EditDebugFlag;
extern int EditDebugTexb;
extern int Select;
extern int LEditFlag;

extern int EditDebugFlag, EditDebugTexb, Select, SelTAG, sg_type, map_jump;
extern int save_no, load_no, condition, map_flag_no, LEditFlag, LightType, DirLightNo, fish_num;
extern int EventNo;
extern int SelMax[EDIT_DEBUG_PAGE_COUNT];
extern int LightSel[LIGHTING_EDIT_PAGE_COUNT], LightListNum[LIGHTING_EDIT_PAGE_COUNT];
extern int *SelData[EDIT_DEBUG_PAGE_COUNT][8];
extern char *SelText[EDIT_DEBUG_PAGE_COUNT][8];
extern char *SelHelp[EDIT_DEBUG_PAGE_COUNT][8];

static int PrintCursor(char *text, int row);

int tagGyoFish(SPI_STACK *stack, int argument_count);

static void LoadGyorace();

void EditDebugInit() { EditDebugFlag = 0; Select = 0; EditDebugTexb = -1; }
int EditDebugMode() { return EditDebugFlag; }
void EditDebugStart(int texb, mgCMemory *buffer) {
    buffer->stack_used = 0;
    buffer->lock = 0;
    EditDebugFlag = 1;
    EditDebugTexb = texb;
}
static int PrintCursor(char *text, int row) {
    if (row == Select) {
        int length = sprintf(text, "->");
        return length;
    }
    return sprintf(text, "  ");
}
#ifdef NONMATCHING
int EditDebugLoop(CScene *scene, EditDebugInfo *info) {
    if (!EditDebugFlag || !DebugFlag) return 0;
    CCharacter2 *character = scene->GetCharacter(scene->player_chara);
    CMapFlagData *map_flags = GetSaveData()->GetMapFlag(scene->GetMainMapNo());
    mgCDrawPrim background;
    background.Initialize(NULL, NULL);
    background.AlphaBlendEnable(1);
    background.AlphaTestEnable(0);
    background.DepthTestEnable(0);
    background.Begin(6);
    background.Color(1, 1, 1, 64);
    background.Vertex(10, 10, 0);
    background.Vertex(250, 200, 0);
    background.End();

    char text[4096];
    char *end = text;
    if (character) {
        float position[4], rotation[4];
        character->GetPosition(position);
        character->GetRotation(rotation);
        end += sprintf(end, "%7.1f %7.1f %7.1f R%4.2f\n", position[0], position[1], position[2], rotation[1]);
        if (GamePad__2.Down(PAD_START)) {
            char coordinates[512];
            int length = sprintf(coordinates, "%.1f,%.1f,%.1f,%.2f;", position[0], position[1], position[2], rotation[1]);
            WriteFile("host0:pos.txt", coordinates, length);
        }
    } else end += sprintf(end, "\n");

    const char *state[2] = {"X", "O"};
    for (int row = 0; row < SelMax[SelTAG]; ++row) {
        end += PrintCursor(end, row);
        end += sprintf(end, "%s ", SelText[SelTAG][row]);
        if (SelTAG == EDIT_DEBUG_PAGE_EDIT_DATA && row == EDIT_DEBUG_EDIT_DATA_CONDITION) {
            if (info->edit_data) {
                char condition_text[128];
                int flag = info->edit_data->dbgGetContintionFlag(info->edit_data_no, condition, condition_text);
                end += sprintf(end, "%d[%s]%s\n", condition, state[flag != 0], condition_text);
            } else end += sprintf(end, "nothing\n");
        } else if (SelTAG == EDIT_DEBUG_PAGE_EDIT_DATA && row == EDIT_DEBUG_EDIT_DATA_MAP_FLAG) {
            if (map_flags) end += sprintf(end, "(%d)%d = %s\n", scene->GetMainMapNo(), map_flag_no,
                                          state[map_flags->GetFlag(map_flag_no) != 0]);
            else end += sprintf(end, "nothing\n");
        } else if (SelData[SelTAG][row]) {
            end += sprintf(end, "%d\n", *SelData[SelTAG][row]);
        } else end += sprintf(end, "\n");
    }
    end += sprintf(end, "\n");
    if (SelHelp[SelTAG][Select]) sprintf(end, "%s\n", SelHelp[SelTAG][Select]);

    int *value = SelData[SelTAG][Select];
    if (value) {
        if (GamePad__2.Down(PAD_LEFT)) --*value;
        if (GamePad__2.Down(PAD_RIGHT)) ++*value;
        int step = GamePad__2.On(PAD_L2) && GamePad__2.On(PAD_R2) ? 10000 : 10;
        if (GamePad__2.Down(PAD_L1)) *value -= step;
        if (GamePad__2.Down(PAD_R1)) *value += step;
        if (GamePad__2.Down(PAD_L2)) *value -= 100;
        if (GamePad__2.Down(PAD_R2)) *value += 100;
        if (*value < 0) *value = 0;
        if (*value > 99999) *value = 99999;
    }
    if (GamePad__2.Down(PAD_SELECT)) {
        ++SelTAG;
        if (SelTAG >= EDIT_DEBUG_PAGE_COUNT) SelTAG = EDIT_DEBUG_PAGE_GENERAL;
    }
    if (GamePad__2.Down(PAD_DOWN)) ++Select;
    if (GamePad__2.Down(PAD_UP)) --Select;
    if (Select < 0) Select = SelMax[SelTAG] - 1;
    if (Select >= SelMax[SelTAG]) Select = 0;
    DebugInfo.debug_camera = DebugInfo.debug_camera != 0;
    DebugInfo.georama_debug = DebugInfo.georama_debug != 0;
    DebugInfo.param_off = DebugInfo.param_off != 0;
    if (DebugInfo.chara_move < 0) DebugInfo.chara_move = 0;
    if (DebugInfo.chara_move > 2) DebugInfo.chara_move = 2;
    if (DebugInfo.invent_debug < 0) DebugInfo.invent_debug = 0;
    if (DebugInfo.invent_debug > 1) DebugInfo.invent_debug = 1;
    GetDebugFont()->DrawDirect(text, 10, 10);

    int closed = 0;
    if (GamePad__2.Down(PAD_CIRCLE)) {
        if (SelTAG == EDIT_DEBUG_PAGE_GENERAL && Select == EDIT_DEBUG_GENERAL_SUB_GAME) {
            sgInitSubGame(sg_type, info);
            EditDebugEnd();
            closed = 1;
        }
        if (SelTAG == EDIT_DEBUG_PAGE_EDIT_DATA) {
            CEditMap *map = (CEditMap *)scene->GetMap(scene->active_map);
            if (info->edit_data && map) {
                char path[128];
                switch (Select) {
                case EDIT_DEBUG_EDIT_DATA_ALL_CLEAR: map->ClearAllParts(); break;
                case EDIT_DEBUG_EDIT_DATA_SAVE_FILE:
                    EditDataSave();
                    sprintf(path, "host0:geo_data/geo%d-%d.edt", scene->now_map_no, save_no);
                    WriteFile(path, info->edit_data, 0x5510);
                    break;
                case EDIT_DEBUG_EDIT_DATA_LOAD_FILE:
                    sprintf(path, "host0:geo_data/geo%d-%d.edt", scene->now_map_no, load_no);
                    if (LoadFile2(path, info->edit_data, NULL, 0)) EditDataLoad();
                    break;
                case EDIT_DEBUG_EDIT_DATA_CONDITION:
                    info->edit_data->dbgSetContintionFlag(info->edit_data_no, condition,
                        !info->edit_data->dbgGetContintionFlag(info->edit_data_no, condition, NULL));
                    break;
                case EDIT_DEBUG_EDIT_DATA_MAP_FLAG:
                    if (map_flags) map_flags->SetFlag(map_flag_no, !map_flags->GetFlag(map_flag_no));
                    break;
                }
            }
        }
        if (SelTAG == EDIT_DEBUG_PAGE_MAP) {
            if (Select == EDIT_DEBUG_MAP_MAP_JUMP) { info->jump_map_no = map_jump; closed = 1; }
            if (Select == EDIT_DEBUG_MAP_LOAD_GYORACE) LoadGyorace();
        }
    }
    if (GamePad__2.Down(PAD_TRIANGLE) && SelTAG == EDIT_DEBUG_PAGE_EDIT_DATA &&
        Select == EDIT_DEBUG_EDIT_DATA_CONDITION && info->edit_data) {
        int new_flag = !info->edit_data->dbgGetContintionFlag(info->edit_data_no, 0, NULL);
        for (int i = 0; i < 64; ++i) info->edit_data->dbgSetContintionFlag(info->edit_data_no, i, new_flag);
    }
    if (SelTAG == EDIT_DEBUG_PAGE_GENERAL && Select == EDIT_DEBUG_GENERAL_RUN_EVENT) {
        if (GamePad__2.Down(PAD_CIRCLE)) { scene->RunEvent(EventNo, NULL); closed = 1; }
        if (GamePad__2.Down(PAD_TRIANGLE)) ReloadMapScript();
    }
    if (closed || GamePad__2.Down(PAD_CROSS | PAD_L3)) {
        EditDebugEnd();
        return 1;
    }
    return 0;
}
#else
INCLUDE_ASM("ps2/asm/pal/nonmatchings/editdebug", EditDebugLoop__FP6CSceneP13EditDebugInfo);
#endif
void EditDebugEnd(void) {
    EditDebugInit();
}
void InitLightingEdit() { LEditFlag = 0; }
void EndLightingEdit(void) {
    InitLightingEdit();
}
int IsLightingEditMode() { return LEditFlag; }
#ifdef NONMATCHING
void LightingEdit(CScene *scene) {
    if (!LEditFlag) {
        if (GamePad__2.Down2(PAD_L3)) {
            LEditFlag = 1;
            GamePad__2.SetAutoRepeat2(PAD_LEFT | PAD_RIGHT, 10, 1);
            GamePad__2.SetAutoRepeat2(PAD_DOWN | PAD_UP, 15, 3);
        }
        return;
    }
    CMap *map = scene->GetMap(scene->active_map);
    mgCDrawPrim prim;
    prim.Initialize(NULL, NULL);
    prim.AlphaBlendEnable(1);
    prim.AlphaTestEnable(0);
    prim.DepthTestEnable(0);
    prim.Begin(6);
    prim.Color(1, 1, 1, 64);
    prim.Vertex(10, 10, 0);
    prim.Vertex(150, 300, 0);
    prim.End();

    int light_no = map->active_light_no;
    CMapLightingInfo *light = ((CMapInfo *)map)->GetLightingInfo(light_no);
    float *selected = NULL;
    int selected_index = 0;
    const char *channel[3] = {"R", "G", "B"};
    const char *axis[3] = {"X", "Y", "Z"};
    const char *cursor[2] = {"  ", ">>"};
    const char *tail[2] = {"  ", "<<"};
    char text[4096];
    const char *pages[4] = {"<- BG & AMB ", "<-Dir Light ", "<-    Fog   ", "<-   File   "};
    int row = LightSel[LightType];
    char *end = text;
    end += sprintf(end, "%sLightSet [%d]\n", cursor[row == 0], light_no);
    if (LightType != 1) end += sprintf(end, "%s%s\n", cursor[row == 1], pages[LightType]);
    else end += sprintf(end, "%s%s%d->\n", cursor[row == 1], pages[LightType], DirLightNo);

    if (LightType == LIGHTING_EDIT_PAGE_BG_AMBIENT) {
        int edit = row - 2;
        float *colors[3] = {light->bg_color, light->bg_color2, light->ambient};
        const char *groups[3] = {"BG_COL  ", "BG_COL2 ", "AMBIENT "};
        if (row > 10) row = 10;
        selected = colors[edit / 3];
        selected_index = edit % 3;
        for (int group = 0; group < 3; group++) {
            for (int component = 0; component < 3; component++) {
                int hit = edit == group * 3 + component;
                end += sprintf(end, "%s%s%s = %d%s\n", cursor[hit], groups[group], channel[component],
                               (int)colors[group][component], tail[hit]);
            }
        }
        end += sprintf(end, "   BG   BG2   AMB\n");
    }
    if (LightType == LIGHTING_EDIT_PAGE_DIR_LIGHT) {
        int edit = row - 2;
        if (edit >= 3 && edit < 6) {
            sceVu0FVECTOR angles;
            mgZeroVector(angles);
            if (GamePad__2.Down2(PAD_RIGHT)) angles[edit - 3] = 0.01f;
            if (GamePad__2.Down2(PAD_LEFT)) angles[edit - 3] = -0.01f;
            if (!(mgDistVector(angles) <= 0.0f)) {
                sceVu0FVECTOR vector;
                vector[0] = light->light_dir[0][DirLightNo];
                vector[1] = light->light_dir[1][DirLightNo];
                vector[2] = light->light_dir[2][DirLightNo];
                vector[3] = 0.0f;
                if (mgDistVector(vector) == 0.0f) vector[2] = 1.0f;
                sceVu0FMATRIX transform;
                mgUnitMatrix(transform);
                sceVu0RotMatrix(transform, transform, angles);
                sceVu0ApplyMatrix(vector, transform, vector);
                sceVu0Normalize(vector, vector);
                light->light_dir[0][DirLightNo] = vector[0];
                light->light_dir[1][DirLightNo] = vector[1];
                light->light_dir[2][DirLightNo] = vector[2];
            }
        }
        if (edit >= 0) {
            if (edit < 3) {
                selected_index = edit;
                selected = light->light_color[DirLightNo];
            }
        }
        for (int component = 0; component < 3; component++) {
            int hit = edit == component;
            end += sprintf(end, "%sCOL %s = %d%s\n", cursor[hit], channel[component],
                           (int)light->light_color[DirLightNo][component], tail[hit]);
        }
        end += sprintf(end, "%sROTATE X <->%s\n", cursor[edit == 3], tail[edit == 3]);
        end += sprintf(end, "%sROTATE Y <->%s\n", cursor[edit == 4], tail[edit == 4]);
        end += sprintf(end, "%sROTATE Z <->%s\n", cursor[edit == 5], tail[edit == 5]);
        for (int a = 0; a < 3; a++)
            end += sprintf(end, " DIR %s = %f\n", axis[a], light->light_dir[a][DirLightNo]);
    }
    if (LightType == LIGHTING_EDIT_PAGE_FOG) {
        unsigned int edit = row - 2;
        mgFOG_PARAM *fog = &light->fog;
        int direction = 0;
        if (GamePad__2.Down2(PAD_RIGHT)) direction = 1;
        if (GamePad__2.Down2(PAD_LEFT)) direction = -1;
        if (direction != 0) {
            if (edit < 7U) {
                switch (row) {
                case 2:
                    fog->near_dist += 10.0f * direction;
                    break;
                case 3:
                    fog->far_dist += 10.0f * direction;
                    break;
                case 4:
                case 5:
                case 6: {
                    u_char *component = &fog->r + edit;
                    int value = *component + direction;
                    if (value < 0) value = 0;
                    if (value >= 256) value = 255;
                    *component = value;
                    break;
                }
                case 7:
                    fog->far_value = (int)fog->far_value + direction;
                    break;
                case 8:
                    fog->near_value = (int)fog->near_value + direction;
                    break;
                }
            }
            if (fog->far_value < 0.0f) fog->far_value = 0.0f;
            if (fog->near_value < 0.0f) fog->near_value = 0.0f;
            if (!(fog->far_value <= 255.0f)) fog->far_value = 255.0f;
            if (!(fog->near_value <= 255.0f)) fog->near_value = 255.0f;
            if (fog->near_dist < 10.0f) fog->near_dist = 10.0f;
            if (fog->far_dist < fog->near_dist) fog->far_dist = fog->near_dist;
        }
        end += sprintf(end, "%sNEAR = %f%s\n", cursor[edit == 0], fog->near_dist, tail[edit == 0]);
        end += sprintf(end, "%sFAR  = %f%s\n", cursor[edit == 1], fog->far_dist, tail[edit == 1]);
        end += sprintf(end, "%sR    = %d%s\n", cursor[edit == 2], fog->r, tail[edit == 2]);
        end += sprintf(end, "%sG    = %d%s\n", cursor[edit == 3], fog->g, tail[edit == 3]);
        end += sprintf(end, "%sB    = %d%s\n", cursor[edit == 4], fog->b, tail[edit == 4]);
        end += sprintf(end, "%sMIN  = %d%s\n", cursor[edit == 5], (int)fog->far_value, tail[edit == 5]);
        end += sprintf(end, "%sMAX  = %d%s\n", cursor[edit == 6], (int)fog->near_value, tail[edit == 6]);
    }
    if (LightType == LIGHTING_EDIT_PAGE_FILE) {
        int edit = row - 2;
        sprintf(end, "%sSAVE <->%s\n", cursor[edit == 0], tail[edit == 0]);
        if (edit == 0 && (GamePad__2.Down2(PAD_LEFT) || GamePad__2.Down2(PAD_RIGHT))) {
            char script[0x5000];
            int size = ((CMapInfo *)map)->OutputLightData(script);
            if (size > 0) {
                char host[16] = "host:";
                char path[128];
                sprintf(path, "%sy:/dc2/build/light_info/%s.lgt", host, scene->GetMapName(scene->active_map));
                WriteFile(path, script, size);
            }
        }
    }
    if (selected != NULL) {
        float *target = selected + selected_index;
        int value = (int)*target;
        if (GamePad__2.Down2(PAD_RIGHT)) value += 1;
        if (GamePad__2.Down2(PAD_LEFT)) value -= 1;
        if (value < 0) value = 0;
        if (value >= 256) value = 255;
        *target = value;
    }
    if (GamePad__2.Down2(PAD_UP)) row -= 1;
    if (GamePad__2.Down2(PAD_DOWN)) row += 1;
    if (row < 0) row = LightListNum[LightType] - 1;
    int previous = LightType;
    if (row >= LightListNum[previous]) row = 0;
    LightSel[previous] = row;
    if (row == 1) {
        if (previous == 1) {
            if (GamePad__2.Down2(PAD_RIGHT)) DirLightNo += 1;
            if (GamePad__2.Down2(PAD_LEFT)) DirLightNo -= 1;
            if (DirLightNo < 0) {
                DirLightNo = 0;
                LightType -= 1;
            }
            if (DirLightNo >= 4) {
                DirLightNo = 3;
                LightType += 1;
            }
        } else {
            if (GamePad__2.Down2(PAD_RIGHT)) LightType += 1;
            if (GamePad__2.Down2(PAD_LEFT)) LightType -= 1;
        }
        if (LightType < 0) LightType = 0;
        if (LightType >= 4) LightType = 3;
        if (LightType == 0) DirLightNo = 0;
        if (LightType == 2) DirLightNo = 3;
        if (previous != LightType) LightSel[LightType] = 1;
    }
    if (row == 0) {
        if (GamePad__2.Down2(PAD_RIGHT)) light_no += 1;
        if (GamePad__2.Down2(PAD_LEFT)) light_no -= 1;
        if (light_no < 0) light_no = 0;
        if (light_no >= map->lighting_info_num) light_no = map->lighting_info_num - 1;
        float time = map->GetLightNoTime(light_no);
        if (!(time < 0.0f)) scene->SetTime(time);
        if (light_no >= 0 && light_no < map->lighting_info_num) map->active_light_no = light_no;
    }
    GetDebugFont()->DrawDirect(text, 10, 10);
    if (LightType == LIGHTING_EDIT_PAGE_BG_AMBIENT) {
        prim.AlphaBlendEnable(0);
        prim.AlphaTestEnable(0);
        prim.DepthTestEnable(0);
        prim.Begin(6);
        prim.Color(light->bg_color);
        prim.Vertex(20, 230, 0);
        prim.Vertex(50, 260, 0);
        prim.Color(light->bg_color2);
        prim.Vertex(60, 230, 0);
        prim.Vertex(90, 260, 0);
        prim.Color(light->ambient);
        prim.Vertex(100, 230, 0);
        prim.Vertex(130, 260, 0);
        prim.End();
    }
    if (LightType == LIGHTING_EDIT_PAGE_DIR_LIGHT) {
        prim.AlphaBlendEnable(0);
        prim.AlphaTestEnable(0);
        prim.DepthTestEnable(0);
        prim.Begin(6);
        prim.Color(light->light_color[DirLightNo]);
        prim.Vertex(20, 230, 0);
        prim.Vertex(50, 260, 0);
        prim.End();
        int anchor[4] = {0x4B0, 0x1040, 0, 0};
        float x_axis[4] = {1.0f, 0.0f, 0.0f, 0.0f};
        float y_axis[4] = {0.0f, 1.0f, 0.0f, 0.0f};
        float z_axis[4] = {0.0f, 0.0f, 1.0f, 0.0f};
        float direction[4];
        direction[0] = light->light_dir[0][DirLightNo];
        direction[1] = light->light_dir[1][DirLightNo];
        direction[2] = light->light_dir[2][DirLightNo];
        direction[3] = 0.0f;
        sceVu0ScaleVector(direction, direction, 10.0f);
        sceVu0ScaleVector(x_axis, x_axis, 10.0f);
        sceVu0ScaleVector(y_axis, y_axis, 10.0f);
        sceVu0ScaleVector(z_axis, z_axis, 10.0f);
        mgCCamera *camera = scene->GetCamera(scene->active_camera);
        float reference[4];
        if (camera != NULL) camera->GetRef(reference);
        reference[3] = 1.0f;
        float tip_light[4];
        float tip_x[4];
        float tip_y[4];
        float tip_z[4];
        sceVu0AddVector(tip_light, reference, direction);
        sceVu0AddVector(tip_x, reference, x_axis);
        sceVu0AddVector(tip_y, reference, y_axis);
        sceVu0AddVector(tip_z, reference, z_axis);
        int origin[4];
        int screen_light[4];
        int screen_x[4];
        int screen_y[4];
        int screen_z[4];
        mgTransWorldScreen(origin, reference);
        mgTransWorldScreen(screen_light, tip_light);
        mgTransWorldScreen(screen_x, tip_x);
        mgTransWorldScreen(screen_y, tip_y);
        mgTransWorldScreen(screen_z, tip_z);
        screen_light[0] -= origin[0];
        screen_x[0] -= origin[0];
        screen_y[0] -= origin[0];
        screen_z[0] -= origin[0];
        screen_light[1] -= origin[1];
        screen_x[1] -= origin[1];
        screen_y[1] -= origin[1];
        screen_z[1] -= origin[1];
        sceVu0ITOF4Vector(tip_light, screen_light);
        sceVu0ITOF4Vector(tip_x, screen_x);
        sceVu0ITOF4Vector(tip_y, screen_y);
        sceVu0ITOF4Vector(tip_z, screen_z);
        float unit = tip_y[1];
        if (unit < 0.0f) unit = -unit;
        float ratio = 30.0f / unit;
        sceVu0ScaleVector(tip_light, tip_light, ratio);
        sceVu0ScaleVector(tip_x, tip_x, ratio);
        sceVu0ScaleVector(tip_y, tip_y, ratio);
        sceVu0ScaleVector(tip_z, tip_z, ratio);
        sceVu0FTOI4Vector(screen_light, tip_light);
        sceVu0FTOI4Vector(screen_x, tip_x);
        sceVu0FTOI4Vector(screen_y, tip_y);
        sceVu0FTOI4Vector(screen_z, tip_z);
        screen_light[0] += anchor[0];
        screen_x[0] += anchor[0];
        screen_y[0] += anchor[0];
        screen_z[0] += anchor[0];
        screen_light[1] += anchor[1];
        screen_x[1] += anchor[1];
        screen_y[1] += anchor[1];
        screen_z[1] += anchor[1];
        prim.AlphaBlendEnable(1);
        prim.AlphaTestEnable(0);
        prim.DepthTestEnable(0);
        prim.Begin(1);
        prim.Color(0, 255, 0, 64);
        prim.Vertex4(anchor);
        prim.Vertex4(screen_x);
        prim.Color(0, 0, 255, 64);
        prim.Vertex4(anchor);
        prim.Vertex4(screen_y);
        prim.Color(255, 0, 0, 64);
        prim.Vertex4(anchor);
        prim.Vertex4(screen_z);
        prim.Color(255, 255, 255, 64);
        prim.Vertex4(anchor);
        prim.Color(255, 255, 255, 128);
        prim.Vertex4(screen_light);
        prim.End();
    }
    mgCCamera *camera = scene->GetCamera(scene->active_camera);
    if (camera != NULL) {
        float angle = 0.05f * -GamePad__2.GetRXf2();
        float magnitude = angle;
        if (angle < 0.0f) magnitude = -angle;
        if (!(magnitude <= 0.001f)) ((CCameraControl *)camera)->Rotate(angle);
    }
    if (GamePad__2.Down2(PAD_L3)) {
        LEditFlag = 0;
        EndLightingEdit();
        GamePad__2.CancelAutoRepeat2(PAD_UP | PAD_DOWN | PAD_LEFT | PAD_RIGHT);
    }
}
#else
INCLUDE_ASM("ps2/asm/pal/nonmatchings/editdebug", LightingEdit__FP6CScene);
#endif
int tagGyoFish(SPI_STACK *stack, int argument_count) {
    CGameDataUsed *racer = GetOmakeGyoracer2(fish_num);
    if (racer == NULL) {
        return 0;
    }
    BREEDFISH_USED *fish = &racer->data.fish;
    char *name = spiGetStackString(stack++);
    if (name != NULL) {
        strcpy(fish->name, name);
    }
    racer->item_no = spiGetStackInt(stack++);
    fish->color = spiGetStackInt(stack++);
    fish->kind = spiGetStackInt(stack++);
    int tactics = spiGetStackInt(stack++);
    fish->param[4] = spiGetStackInt(stack++);
    fish->param[3] = spiGetStackInt(stack++);
    fish->param[0] = spiGetStackInt(stack++);
    fish->param[1] = spiGetStackInt(stack++);
    fish->param[2] = spiGetStackInt(stack);
    SetOmakeGyoracerTactics(fish_num, tactics);
    ++fish_num;
    return 1;
}
static void LoadGyorace() {
    char script[0x4000];
    int size;
    if (LoadFile2("host:gyorace.cfg", script, &size, 0)) {
        fish_num = 0;
        SPI_TAG_PARAM tags[2] = {{"GYOFISH", tagGyoFish}, {NULL, NULL}};
        CScriptInterpreter interpreter;
        interpreter.SetTag(tags);
        interpreter.SetScript((char *)&script, size);
        interpreter.Run();
    }
}

INCLUDE_RODATA("ps2/asm/pal/nonmatchings/editdebug", SelMax__DATA);
INCLUDE_RODATA("ps2/asm/pal/nonmatchings/editdebug", SelData__DATA);
INCLUDE_RODATA("ps2/asm/pal/nonmatchings/editdebug", SelText__DATA);
INCLUDE_RODATA("ps2/asm/pal/nonmatchings/editdebug", SelHelp__DATA);
INCLUDE_RODATA("ps2/asm/pal/nonmatchings/editdebug", LightSel__DATA);
INCLUDE_RODATA("ps2/asm/pal/nonmatchings/editdebug", LightListNum__DATA);
INCLUDE_RODATA("ps2/asm/pal/nonmatchings/editdebug", at_1219__DATA);
INCLUDE_RODATA("ps2/asm/pal/nonmatchings/editdebug", at_1222__DATA);
INCLUDE_RODATA("ps2/asm/pal/nonmatchings/editdebug", at_1231__DATA);
INCLUDE_RODATA("ps2/asm/pal/nonmatchings/editdebug", at_1243__DATA);
INCLUDE_RODATA("ps2/asm/pal/nonmatchings/editdebug", at_1321__DATA);
INCLUDE_RODATA("ps2/asm/pal/nonmatchings/editdebug", at_1385__DATA);
INCLUDE_RODATA("ps2/asm/pal/nonmatchings/editdebug", at_1386__DATA);
INCLUDE_RODATA("ps2/asm/pal/nonmatchings/editdebug", at_1387__DATA);
INCLUDE_RODATA("ps2/asm/pal/nonmatchings/editdebug", at_1388__DATA);
INCLUDE_RODATA("ps2/asm/pal/nonmatchings/editdebug", at_1542__DATA);

INCLUDE_RODATA("ps2/asm/pal/nonmatchings/editdebug", at_989__DATA);
INCLUDE_RODATA("ps2/asm/pal/nonmatchings/editdebug", at_990__DATA);
INCLUDE_RODATA("ps2/asm/pal/nonmatchings/editdebug", at_991__DATA);
INCLUDE_RODATA("ps2/asm/pal/nonmatchings/editdebug", at_992__DATA);
INCLUDE_RODATA("ps2/asm/pal/nonmatchings/editdebug", at_993__DATA);
INCLUDE_RODATA("ps2/asm/pal/nonmatchings/editdebug", at_994__DATA);
INCLUDE_RODATA("ps2/asm/pal/nonmatchings/editdebug", at_995__DATA);
INCLUDE_RODATA("ps2/asm/pal/nonmatchings/editdebug", at_996__DATA);
INCLUDE_RODATA("ps2/asm/pal/nonmatchings/editdebug", at_997__DATA);
INCLUDE_RODATA("ps2/asm/pal/nonmatchings/editdebug", at_998__DATA);
INCLUDE_RODATA("ps2/asm/pal/nonmatchings/editdebug", at_999__DATA);
INCLUDE_RODATA("ps2/asm/pal/nonmatchings/editdebug", at_1000__DATA);
INCLUDE_RODATA("ps2/asm/pal/nonmatchings/editdebug", at_1001__DATA);
INCLUDE_RODATA("ps2/asm/pal/nonmatchings/editdebug", at_1002__DATA);
INCLUDE_RODATA("ps2/asm/pal/nonmatchings/editdebug", at_1003__DATA);
INCLUDE_RODATA("ps2/asm/pal/nonmatchings/editdebug", at_1004__DATA);
INCLUDE_RODATA("ps2/asm/pal/nonmatchings/editdebug", at_1005__DATA);
INCLUDE_RODATA("ps2/asm/pal/nonmatchings/editdebug", at_1028__2__DATA);
INCLUDE_RODATA("ps2/asm/pal/nonmatchings/editdebug", at_1029__2__DATA);
INCLUDE_RODATA("ps2/asm/pal/nonmatchings/editdebug", at_1057__DATA);
INCLUDE_RODATA("ps2/asm/pal/nonmatchings/editdebug", at_1058__DATA);
INCLUDE_RODATA("ps2/asm/pal/nonmatchings/editdebug", at_1181__DATA);
INCLUDE_RODATA("ps2/asm/pal/nonmatchings/editdebug", at_1182__DATA);
INCLUDE_RODATA("ps2/asm/pal/nonmatchings/editdebug", at_1183__DATA);
INCLUDE_RODATA("ps2/asm/pal/nonmatchings/editdebug", at_1184__DATA);
INCLUDE_RODATA("ps2/asm/pal/nonmatchings/editdebug", at_1185__DATA);
INCLUDE_RODATA("ps2/asm/pal/nonmatchings/editdebug", at_1186__DATA);
INCLUDE_RODATA("ps2/asm/pal/nonmatchings/editdebug", at_1187__DATA);
INCLUDE_RODATA("ps2/asm/pal/nonmatchings/editdebug", at_1188__DATA);
INCLUDE_RODATA("ps2/asm/pal/nonmatchings/editdebug", at_1189__DATA);
INCLUDE_RODATA("ps2/asm/pal/nonmatchings/editdebug", at_1190__DATA);
INCLUDE_RODATA("ps2/asm/pal/nonmatchings/editdebug", at_1191__DATA);
INCLUDE_RODATA("ps2/asm/pal/nonmatchings/editdebug", at_1216__2__DATA);
INCLUDE_RODATA("ps2/asm/pal/nonmatchings/editdebug", at_1217__DATA);
INCLUDE_RODATA("ps2/asm/pal/nonmatchings/editdebug", at_1218__DATA);
INCLUDE_RODATA("ps2/asm/pal/nonmatchings/editdebug", at_1220__DATA);
INCLUDE_RODATA("ps2/asm/pal/nonmatchings/editdebug", at_1221__DATA);
INCLUDE_RODATA("ps2/asm/pal/nonmatchings/editdebug", at_1223__DATA);
INCLUDE_RODATA("ps2/asm/pal/nonmatchings/editdebug", at_1225__DATA);
INCLUDE_RODATA("ps2/asm/pal/nonmatchings/editdebug", at_1227__DATA);
INCLUDE_RODATA("ps2/asm/pal/nonmatchings/editdebug", at_1228__DATA);
INCLUDE_RODATA("ps2/asm/pal/nonmatchings/editdebug", at_1229__DATA);
INCLUDE_RODATA("ps2/asm/pal/nonmatchings/editdebug", at_1230__DATA);
INCLUDE_RODATA("ps2/asm/pal/nonmatchings/editdebug", at_1240__2__DATA);
INCLUDE_RODATA("ps2/asm/pal/nonmatchings/editdebug", at_1241__2__DATA);
INCLUDE_RODATA("ps2/asm/pal/nonmatchings/editdebug", at_1242__DATA);
INCLUDE_RODATA("ps2/asm/pal/nonmatchings/editdebug", at_1495__DATA);
INCLUDE_RODATA("ps2/asm/pal/nonmatchings/editdebug", at_1496__DATA);
INCLUDE_RODATA("ps2/asm/pal/nonmatchings/editdebug", at_1497__DATA);
INCLUDE_RODATA("ps2/asm/pal/nonmatchings/editdebug", at_1498__DATA);
INCLUDE_RODATA("ps2/asm/pal/nonmatchings/editdebug", at_1499__DATA);
INCLUDE_RODATA("ps2/asm/pal/nonmatchings/editdebug", at_1500__DATA);
INCLUDE_RODATA("ps2/asm/pal/nonmatchings/editdebug", at_1501__2__DATA);
INCLUDE_RODATA("ps2/asm/pal/nonmatchings/editdebug", at_1502__DATA);
INCLUDE_RODATA("ps2/asm/pal/nonmatchings/editdebug", at_1503__DATA);
INCLUDE_RODATA("ps2/asm/pal/nonmatchings/editdebug", at_1504__DATA);
INCLUDE_RODATA("ps2/asm/pal/nonmatchings/editdebug", at_1505__DATA);
INCLUDE_RODATA("ps2/asm/pal/nonmatchings/editdebug", at_1506__2__DATA);
INCLUDE_RODATA("ps2/asm/pal/nonmatchings/editdebug", at_1507__2__DATA);
INCLUDE_RODATA("ps2/asm/pal/nonmatchings/editdebug", at_1508__DATA);
INCLUDE_RODATA("ps2/asm/pal/nonmatchings/editdebug", at_1509__DATA);
INCLUDE_RODATA("ps2/asm/pal/nonmatchings/editdebug", at_1510__DATA);
INCLUDE_RODATA("ps2/asm/pal/nonmatchings/editdebug", at_1511__DATA);
INCLUDE_RODATA("ps2/asm/pal/nonmatchings/editdebug", at_1512__DATA);
INCLUDE_RODATA("ps2/asm/pal/nonmatchings/editdebug", at_1513__DATA);
INCLUDE_RODATA("ps2/asm/pal/nonmatchings/editdebug", at_1514__DATA);
INCLUDE_RODATA("ps2/asm/pal/nonmatchings/editdebug", at_1541__DATA);
INCLUDE_RODATA("ps2/asm/pal/nonmatchings/editdebug", at_1544__2__DATA);

INCLUDE_RODATA("ps2/asm/pal/nonmatchings/editdebug", EventNo__DATA);
INCLUDE_RODATA("ps2/asm/pal/nonmatchings/editdebug", at_1059__DATA);
INCLUDE_RODATA("ps2/asm/pal/nonmatchings/editdebug", at_1063__2__DATA);
INCLUDE_RODATA("ps2/asm/pal/nonmatchings/editdebug", at_1224__DATA);
INCLUDE_RODATA("ps2/asm/pal/nonmatchings/editdebug", at_1226__DATA);

INCLUDE_BSS(EditDebugFlag, 0x4);
INCLUDE_BSS(EditDebugTexb, 0x4);
INCLUDE_BSS(Select, 0x4);
INCLUDE_BSS(SelTAG, 0x4);
INCLUDE_BSS(sg_type, 0x4);
INCLUDE_BSS(map_jump, 0x4);
INCLUDE_BSS(save_no, 0x4);
INCLUDE_BSS(load_no, 0x4);
INCLUDE_BSS(condition, 0x4);
INCLUDE_BSS(map_flag_no, 0x4);
INCLUDE_BSS(LEditFlag, 0x4);
INCLUDE_BSS(LightType, 0x4);
INCLUDE_BSS(DirLightNo, 0x4);
INCLUDE_BSS(fish_num, 0x4);

INCLUDE_BSS(at_1237, 0x10);
