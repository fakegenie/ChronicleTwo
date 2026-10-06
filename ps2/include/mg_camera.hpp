#pragma once

#include "common.h"

#include <libvu0.h>

enum mgCameraKind {
    MG_CAMERA_KIND_CAMERA = 0,
    MG_CAMERA_KIND_FOLLOW = 1,
};

class mgCCamera {
public:
    sceVu0FVECTOR pos;
    sceVu0FVECTOR ref;
    sceVu0FVECTOR next_pos;
    sceVu0FVECTOR next_ref;
    float roll;
    int unk_44;
    float pos_speed;
    float ref_speed;
    float angle_h;
    float angle_v;
    float snap_range;
    int suspended;

    static int StopCamera;

    virtual void Step(int steps);

    virtual void Suspend() { suspended = 1; }

    virtual void Resume() { suspended = 0; }

    virtual void Stay();

    virtual void GetCameraMatrix(float (*matrix)[4]);

    virtual int Iam() { return MG_CAMERA_KIND_CAMERA; }

    void SetPos(float x, float y, float z);

    void SetPos(float *pos);

    void SetNextPos(float x, float y, float z);

    void SetNextPos(float *pos);

    void SetRef(float x, float y, float z);

    void SetRef(float *ref);

    void SetNextRef(float x, float y, float z);

    void SetNextRef(float *ref);

    void GetDir(float *dir);

    void SetSpeed(float pos_speed, float ref_speed);

    void SetRoll(float roll);

    void GetPos(float *pos);

    void GetRef(float *ref);

    void GetNextPos(float *pos);

    void GetNextRef(float *ref);

    float GetAngleH();

    float GetAngleV();

    mgCCamera(float speed);
};
STATIC_ASSERT(sizeof(mgCCamera) == 0x70);

class mgCCameraFollow : public mgCCamera {
public:
    sceVu0FVECTOR follow;
    sceVu0FVECTOR follow_offset;
    float distance;
    float height;
    float next_angle;
    float angle;
    int follow_on;
    sceVu0FVECTOR follow_next;

    virtual void Step(int steps);

    virtual void Stay();

    virtual int Iam() { return MG_CAMERA_KIND_FOLLOW; }

    virtual void SetFollow(float x, float y, float z);

    void GetFollowNextPos(float *pos);

    void GetFollowNext(float *pos);

    void FollowOn();

    void FollowOff();

    void SetAngle(float angle);

    void SetAngleSoon(float angle);

    float GetAngle();

    void AddAngle(float delta);

    void SetDistance(float distance);

    float GetDistance();

    void AddDistance(float delta);

    void SetHeight(float height);

    float GetHeight();

    void AddHeight(float delta);

    void SetFollowOffset(float x, float y, float z);

    void GetFollow(float *pos);

    void GetFollowOffset(float *offset);

    mgCCameraFollow(float distance, float height, float angle, float speed);
};
STATIC_ASSERT(sizeof(mgCCameraFollow) == 0xC0);
