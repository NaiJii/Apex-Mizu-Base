module;

#include "include.h"
#include "sdk/sdk.h"

export module mizu;

import util;

/* Global data that is not part of the sdk and still is useful to have */
export namespace Mizu {
	// data that needs tick / frame updates
	CEntity* m_localPlayer = nullptr;
	CUserCmd* m_cmd = nullptr;

	void Reset();

	// called every tick
	bool OnTick(CUserCmd* cmd);

	// called every frame
	bool OnFrame();
}