#pragma once

#include "common.h"

enum PadSetupPhase {
    PAD_PHASE_QUERY          = 0,
    PAD_PHASE_ANALOG_CHECK   = 40,
    PAD_PHASE_ANALOG_SET     = 41,
    PAD_PHASE_ANALOG_WAIT    = 42,
    PAD_PHASE_ACTUATOR_CHECK = 70,
    PAD_PHASE_ACTUATOR_WAIT  = 71,
    PAD_PHASE_READY          = 99,
};

enum PadTerminalId {
    PAD_TERMINAL_NEGCON          = 2,
    PAD_TERMINAL_KONAMI_GUN      = 3,
    PAD_TERMINAL_DIGITAL         = 4,
    PAD_TERMINAL_ANALOG_JOYSTICK = 5,
    PAD_TERMINAL_NAMCO_GUN       = 6,
    PAD_TERMINAL_DUALSHOCK       = 7,
    PAD_TERMINAL_EX_TSURICON     = 0x100,
    PAD_TERMINAL_EX_JOGCON       = 0x300,
};

enum PadButton {
    PAD_L2       = 0x0001,
    PAD_R2       = 0x0002,
    PAD_L1       = 0x0004,
    PAD_R1       = 0x0008,
    PAD_TRIANGLE = 0x0010,
    PAD_CIRCLE   = 0x0020,
    PAD_CROSS    = 0x0040,
    PAD_SQUARE   = 0x0080,
    PAD_SELECT   = 0x0100,
    PAD_L3       = 0x0200,
    PAD_R3       = 0x0400,
    PAD_START    = 0x0800,
    PAD_UP       = 0x1000,
    PAD_RIGHT    = 0x2000,
    PAD_DOWN     = 0x4000,
    PAD_LEFT     = 0x8000,
};

enum PadMotor {
    PAD_MOTOR_SMALL = 0,
    PAD_MOTOR_LARGE = 1,
};

enum PadCaptureMode {
    PAD_CAPTURE_OFF    = 0,
    PAD_CAPTURE_RECORD = 1,
    PAD_CAPTURE_PLAY   = 2,
};

#pragma push
#pragma cpp_extensions on
struct PAD_STATUS {
    int button;
    int left_y;
    int left_x;
    int right_y;
    int right_x;
    int phase;
    int state;
    int extended_id;
    int pad_mode;
    int previous_pad_mode;
    u8  vibration[6];
    u8  actuator[6];
    union {
        int vibration_words[6];
        struct {
    int vibration_timer[2];
    int unk_3C;
    int unk_40;
    int unk_44;
    int unk_48;
};
    };
};
STATIC_ASSERT(sizeof(PAD_STATUS) == 0x4C);
#pragma pop

struct PAD_REPEAT {
    int enabled;
    int active;
    int counter[32];
    int initial_delay[32];
    int repeat_delay[32];
};
STATIC_ASSERT(sizeof(PAD_REPEAT) == 0x188);

struct PAD_CAPTURE_FRAME {
    u16 button;
    u8  left_y;
    u8  left_x;
    u8  right_y;
    u8  right_x;
};
STATIC_ASSERT(sizeof(PAD_CAPTURE_FRAME) == 0x6);

enum {
    PAD_CAPTURE_BUFFER_SIZE = 0x100000,
    PAD_CAPTURE_FRAME_MAX   = PAD_CAPTURE_BUFFER_SIZE / sizeof(PAD_CAPTURE_FRAME),
};

#define PAD_CAPTURE_BUFFER ((PAD_CAPTURE_FRAME *) 0x3000000)

enum {
    GAMEPAD_THREAD_PRIORITY = 10,
};

class CGamePad {
public:
    int        unk_000;
    PAD_STATUS pad[2];
    PAD_STATUS previous_pad[2];
    int        unk_134;
    int        unk_138;
    int        unk_13C;
    int        unk_140;
    PAD_REPEAT repeat[2];
    int        axis_threshold[2];
    int        key_lock;
    int        key_lock2;
    int        debug_key_lock;
    int        vibration_enabled;
    int        vibration_elapsed;
    int        capture_mode;
    u32        capture_frame;

    void Init();

    void Close();

    void WaitEnable();

    int Connect();

    void UpDate();

    void Step(int elapsed);

    int GetRX();

    int GetRY();

    int GetLX();

    int GetLY();

    int GetRX2();

    void CancelAutoRepeat(int mask);

    void CancelAutoRepeat2(int mask);

    void SetAutoRepeat(int mask, int initial_delay, int repeat_delay);

    void SetAutoRepeat2(int mask, int initial_delay, int repeat_delay);

    void KeyLock(int lock);

    void KeyLock2(int lock);

    void DebugKeyLock(int lock);

    int GetPadOn();

    int GetPadDown();

    int GetPadUp();

    float GetRXf();

    float GetRYf();

    float GetLXf();

    float GetLYf();

    float GetRXf2();

    int On(int mask);

    int On2(int mask);

    int Down(int mask);

    int Down2(int mask);

    int Up(int mask);

    void AutoRepeatOff();

    void MenuModeOn(int threshold);

    void MenuModeOff();

    void SetVibration(int motor, int strength, int duration);

    void VibrationEnable(int enable);

    void StopVibration();

    void CaptureStart();

    void CaptureEnd();

    void CapturePlay();

    void Capture(PAD_STATUS *status);

    void Play(PAD_STATUS *status);

    void SaveCapture();

    void LoadCapture();
};
STATIC_ASSERT(sizeof(CGamePad) == 0x478);

void SwitchGamePadThread();

void CreateGamePadThread(CGamePad *game_pad);
