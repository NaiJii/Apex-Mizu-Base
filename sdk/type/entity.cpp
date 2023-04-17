#include "entity.h"
#include "../sdk.h"
#include "../../memory/virtual.h"

import mizu;
import memory;
import util;

CStudioHdr* CEntity::GetModelPtr() {
	static uint32_t offset = Memory::Addresses::m_modelPtr.Offset(0x3).Get<uint32_t>();
	return *(CStudioHdr**)((uintptr_t)this + offset);
}