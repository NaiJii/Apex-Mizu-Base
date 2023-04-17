#pragma once

#include <cstdint>
#include "../memory/virtual.h"

enum ESignonState : int32_t {
	SIGNON_NONE,
	SIGNON_CHALLENGE,
	SIGNON_CONNECTED,
	SIGNON_STATENEW,
	SIGNON_PRESPAWN,
	SIGNON_GETTINGDATA,
	SIGNON_SPAWN,
	SIGNON_FIRSTSNAP,
	SIGNON_FULL,
	SIGNON_CHANGELEVEL
};

struct CClientState {
	PAD(0x60); // 0x00 (0x60)
	void* netChannel; // 0x60
	PAD(0x44); // 0x68 (0x44)
	int32_t signonState; // 0xAC (0x04)
	PAD(0xB0); // 0xB0 (0xB0)
};
