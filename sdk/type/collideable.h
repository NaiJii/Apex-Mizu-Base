#pragma once

#include <cstdint>
#include "vector.h"

struct CollisionProperty_t {
	void* m_vtable; // 0x0
	uint8_t pad0[0x8]; // 0x8
	Vector_t m_mins; // 0x10
	Vector_t m_maxs; // 0x1c
	int m_solidFlags; // 0x28
	char m_solidType; // 0x2c
	char m_triggerBloat; // 0x2d
	char m_collisionDetailLevel; // 0x2e
	uint8_t pad1[0x11]; // 0x2f
}; // 0x40