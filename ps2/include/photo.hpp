#pragma once

#include "common.h"

class CPadControl;
class CInventUserData;
class mgCMemory;
struct USER_PICTURE_INFO;

enum TakePhotoState {
    TAKE_PHOTO_OFF       = 0,
    TAKE_PHOTO_AIM       = 2,
    TAKE_PHOTO_SHUTTER   = 3,
    TAKE_PHOTO_STORE     = 5,
    TAKE_PHOTO_AFTERSHOT = 4,
    TAKE_PHOTO_OPEN_MENU = 6,
};

enum PhotoMessage {
    PHOTO_MES_CONFIRM  = 0,
    PHOTO_MES_TAKE     = 1,
    PHOTO_MES_LEVEL_UP = 2,
    PHOTO_MES_ZOOM     = 3,
    PHOTO_MES_NUM      = 4,
};

char *GetMesTxt(int message);

float PhotoAddProjection();

void InitTakePhoto();

void LoadTakePhoto(int camera_texb, mgCMemory *memory, u_long128 *buffer);

void StartTakePhoto();

void EndTakePhoto();

int NowTakePhoto();

int IsEnablePhotoMenu();

void HidePhoto();

int GhostPhotoTiming();

void LoopTakePhoto(CPadControl *pad, CInventUserData *user_data);

int DrawTakePhoto(USER_PICTURE_INFO *picture, float *distance);

void SetTookPhotoData(USER_PICTURE_INFO *picture);

void DrawTakePhotoSystem(int texb, CInventUserData *user_data);
