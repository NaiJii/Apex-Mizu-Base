#pragma once

#include "type/CUserCmd.h"

struct CInput {
	// 4C 8B C9 83 FA FF 74 0D
	VCALL(CUserCmd*, GetUserCmd, 9, (int sequenceNb, int commandNb), (this, sequenceNb, commandNb));
};
