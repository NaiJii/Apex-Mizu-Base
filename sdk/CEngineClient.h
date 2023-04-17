#pragma once

#include "../memory/virtual.h"

struct PlayerInfo_t {
	char name[128];
};

struct CEngineClient {
	VCALL(bool, GetPlayerInfo, 24, (const int idx, PlayerInfo_t* info), (this, idx, info));
	VCALL(bool, IsInGame, 46, (), (this));
};
