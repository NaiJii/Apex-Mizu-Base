#include "include.h"
#include "../sdk/sdk.h"

// alphabetical order
import hook;
import memory;
import util;

BOOL APIENTRY DllMain(HMODULE _module, DWORD reason, LPVOID reserved) {
	if (reason == DLL_PROCESS_ATTACH) {
		AllocConsole();
		freopen_s((FILE**)stdout, _("CONOUT$"), _("w"), stdout);

		if (!Memory::Setup(_module))
			Util::Log(_("failed to setup memory"));

		if (!SDK::Setup())
			Util::Log(_("failed to setup interfaces"));

		if (!Hooks::Setup())
			Util::Log(_("failed to setup hooks"));
	}

	return TRUE;
}