#pragma once

#include "common.h"

struct SubGameInfo;

int sgInitBuggy(SubGameInfo *info);

int sgExitBuggy(SubGameInfo *info);

int sgLoopBuggy(SubGameInfo *info);

int sgDrawBuggy(SubGameInfo *info);

int sgEffectDrawBuggy(SubGameInfo *info);

int sgDrawShadowBuggy(SubGameInfo *info);

int sgSystemDrawBuggy(SubGameInfo *info);
