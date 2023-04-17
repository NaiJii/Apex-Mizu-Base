#pragma once

#include <cstdint>
#include "../memory/virtual.h"

struct CGlobalVars {
	double realTime;
	int frameCount;
	float absFrameTime;
	float serverTime;
	float currentTime2;
	float currentTime3;
	float currentTime4;
	float frameTime;
	float currentTime5;
	float currentTime6;
	float zero;
	float frameTime2;
	int maxClients;
	int unk38;
	int unk3C;
	int tickCount;
	float intervalPerTick;
	float interpolationAmount;

	int TimeToTicks(float time) const {
		return int(time / intervalPerTick);
	}

	float TicksToTime(int ticks) const {
		return (float)(ticks)*intervalPerTick;
	}
};
