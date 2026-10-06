#pragma once

#include "common.h"

class CGamePad;

#define PAD_CTRL_BTN_MAX 128

#define PAD_CTRL_ANALOG_MAX 32

enum PadCtrlTrigger {
    PAD_CTRL_TRIGGER_ON   = 0x00000,
    PAD_CTRL_TRIGGER_DOWN = 0x10000,
    PAD_CTRL_TRIGGER_UP   = 0x20000,
    PAD_CTRL_TRIGGER_MASK = 0xF0000,
    PAD_CTRL_BUTTON_MASK  = 0x0FFFF,
};

enum PadCtrlButton {
    PAD_BTN_CONFIRM        = 0,
    PAD_BTN_CANCEL         = 1,
    PAD_BTN_MENU           = 5,
    PAD_BTN_RIGHT          = 9,
    PAD_BTN_LEFT           = 10,
    PAD_BTN_START          = 0x0F,
    PAD_BTN_PAUSE          = 0x15,
    PAD_BTN_EVENT_SKIP     = 0x16,
    PAD_BTN_QUICK_CHANGE   = 0x17,
    PAD_BTN_ACTION_CONFIRM = 0x32,
    PAD_BTN_ACTION_SQUARE  = 0x33,
    PAD_BTN_ACTION_CANCEL  = 0x34,
    PAD_BTN_ACTION_HELD    = 0x38,
    PAD_BTN_EDIT_SWITCH    = 0x6C,
};

enum PadCtrlAxis {
    PAD_CTRL_AXIS_NONE = 0,
    PAD_CTRL_AXIS_LX   = 1,
    PAD_CTRL_AXIS_LY   = 2,
    PAD_CTRL_AXIS_RX   = 3,
    PAD_CTRL_AXIS_RY   = 4,
};

struct PAD_CTRL_BTN {
    int value;
    int config;
};
STATIC_ASSERT(sizeof(PAD_CTRL_BTN) == 0x8);

struct PAD_CTRL_ANALOG {
    float value;
    int axis;
};
STATIC_ASSERT(sizeof(PAD_CTRL_ANALOG) == 0x8);

class CPadControl {
public:
    void Initialize();

    int RegisterBtn(int no, int button, int trigger);

    int RegisterAnalog(int no, int axis);

    int Btn(int no);

    float Analog(int no);

    void Update(CGamePad *pad);

    float rx;
    float ry;
    float lx;
    float ly;
    PAD_CTRL_BTN btn[PAD_CTRL_BTN_MAX];
    PAD_CTRL_ANALOG analog[PAD_CTRL_ANALOG_MAX];
};
STATIC_ASSERT(sizeof(CPadControl) == 0x510);
