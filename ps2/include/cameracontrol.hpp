#pragma once

#include "common.h"

#include <libvu0.h>

#include "mg_camera.hpp"

class CPadControl;
struct CCPoly;

enum CameraControlKind {
    CAMERA_KIND_CONTROL = 1000,
};

enum CameraRotCancel {
    CAMERA_ROT_CANCEL_BUTTON    = 0x1,
    CAMERA_ROT_CANCEL_ANALOG    = 0x2,
    CAMERA_ROT_CANCEL_ROT_BACK  = 0x40,
    CAMERA_ROT_CANCEL_AUTO_MOVE = 0x80,
};

class CameraCtrlParam {
public:
    float min_dist;
    float max_dist;
    float near_height;
    float far_height;
    float height;
    float max_height;
    float min_height;
    float rest_max_height;
    float rest_min_height;
    float ground_space;
    int no_check;

    CameraCtrlParam() { no_check = 0; }

    void SetFixHeight(float height);

    void SetFixDist(float dist);
};
STATIC_ASSERT(sizeof(CameraCtrlParam) == 0x2C);

class CCameraControl : public mgCCameraFollow {
public:
    struct Control {
        float rot;
        float height;
        int rot_back;
    };

    int control_on;
    int rot_cancel;
    int rot_back;
    float rot_back_angle;
    int rot_reverse;
    sceVu0FVECTOR dir_offset;
    int active_param;
    CameraCtrlParam param[4];
    CameraCtrlParam default_param;
    sceVu0FVECTOR check_ref;
    int check_ref_on;

    CCameraControl();

    CameraCtrlParam *GetActiveParam();

    void SetRotCameraCancel(int cancel);

    void BitSetRotCameraCancel(int cancel);

    void BitResetRotCameraCancel(int cancel);

    void InitStatus();

    void ControlOn();

    void ControlOff();

    virtual void Stay();

    virtual void Step(int steps);

    void MoveCamera(CPadControl *pad, float *rot, CCPoly *polys, int poly_count);

    void MoveCamera(Control *control, float *rot, CCPoly *polys, int poly_count);

    void Rotate(float angle);

    void SetRotate(float angle);

    void SetHeight(float height);

    void RotBack(float angle);

    void CancelRotBack();

    void SetCheckRef(float *ref);

    void SetCheckRef(float x, float y, float z);

    void CheckCollision(CCPoly *polys, int poly_count);

    int AutoMove(CCPoly *polys, int poly_count);

    void CheckGround(CCPoly *polys, int poly_count);

    virtual void GetCameraMatrix(float (*matrix)[4]);

    void CopyParam(CCameraControl &dest);

    virtual int Iam();
};
STATIC_ASSERT(sizeof(CCameraControl) == 0x1F0);
