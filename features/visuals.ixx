module;

#include "../include.h"
#include "../sdk/sdk.h"

export module visuals;

import memory;
import mizu;
import util;

export namespace Visuals {
	namespace Config {
		bool box = true;
	}

	void Run();

	void Players();
}