#pragma once

#define rSdInit 0x8000
#define rSdSetParam 0x8010
#define rSdSetSwitch 0x8030
#define rSdSetAddr 0x8050
#define rSdSetCoreAttr 0x8070
#define rSdVoiceTrans 0x80D0
#define rSdVoiceTransStatus 0x80F0
#define rSdSetEffectAttr 0x8130

#define SD_S_KOFF (0x16 << 8)
#define SD_P_MVOLL ((0x09 << 8) + (0x01 << 7))
#define SD_P_MVOLR ((0x0A << 8) + (0x01 << 7))
#define SD_P_EVOLL ((0x0B << 8) + (0x01 << 7))
#define SD_P_EVOLR ((0x0C << 8) + (0x01 << 7))
#define SD_A_EEA (0x1D << 8)

#define SD_C_EFFECT_ENABLE (1 << 1)
#define SD_C_SPDIF_MODE (5 << 1)

#define SD_SPDIF_COPY_PROHIBIT 0x80
#define SD_REV_MODE_CLEAR_WA 0x100

#define SD_TRANS_MODE_WRITE 0
#define SD_TRANS_STATUS_CHECK 0
#define SD_TRANS_STATUS_WAIT 1

struct sceSdEffectAttr {
    int core;
    int mode;
    short depth_L;
    short depth_R;
    int delay;
    int feedback;
};

#ifdef __cplusplus
extern "C" {
#endif

int sceSdRemoteInit(void);

int sceSdRemote(int arg, int command, ...);

#ifdef __cplusplus
}
#endif
