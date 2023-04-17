#include "include.h"
#include "sdk/sdk.h"

import mizu;
import memory;
import util;

void Mizu::Reset() {
	m_localPlayer = nullptr;
	m_cmd = nullptr;
}

bool Mizu::OnTick(CUserCmd* cmd) {
	if (SDK::m_clientState->signonState != ESignonState::SIGNON_FULL)
		return false;

	if (!m_localPlayer)
		m_localPlayer = *SDK::m_localPlayerPtr;

	if (!m_localPlayer)
		return false;

	if (strcmp(SDK::m_levelName, _("mp_lobby")) == 0)
		return false;

	m_cmd = cmd;

	SDK::Update();
	return true;
}

bool Mizu::OnFrame() {
	if (!SDK::m_updated)
		return false;

	if (SDK::m_clientState->signonState != ESignonState::SIGNON_FULL)
		return false;

	if (!m_localPlayer)
		return false;

	return true;
}