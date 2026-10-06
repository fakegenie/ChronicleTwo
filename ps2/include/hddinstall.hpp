#pragma once

#include "common.h"

int HddConectCheck(int *state);

int CheckAppInstall();

int CheckInstallSpace();

int MountHDDFileSystem();

int UmountHDDFileSystem();

int CreateInstallThread(u_long128 *work, int work_size);

void DeleteInstallThread();

int StepInstallThread();

int InstallPause();

void InstallCancel();

float GetInstallProgress();

int UninstallApp();
