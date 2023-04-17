#pragma once

#include "angle.h"
#include "vector.h"

enum EButtons {
	IN_ATTACK = (1 << 0),
	IN_JUMP = (1 << 1),
	IN_DUCK = (1 << 2),
	IN_FORWARD = (1 << 3),
	IN_BACK = (1 << 4),
	IN_USE = (1 << 5),
	IN_PAUSEMENU = (1 << 6),
	IN_LEFT = (1 << 7),
	IN_RIGHT = (1 << 8),
	IN_MOVELEFT = (1 << 9),
	IN_MOVERIGHT = (1 << 10),
	IN_WALK = (1 << 11),
	IN_RELOAD = (1 << 12),
	IN_USE_LONG = (1 << 13),
	IN_WEAPON_DISCARD = (1 << 14),
	IN_SPEED = (1 << 15),
	IN_ZOOM = (1 << 16),
	IN_ZOOM_TOGGLE = (1 << 17),
	IN_MELEE = (1 << 18),
	IN_WEAPON_CYCLE = (1 << 19),
	IN_OFFHAND0 = (1 << 20),
	IN_OFFHAND1 = (1 << 21), // ability Q
	IN_OFFHAND2 = (1 << 22),
	IN_OFFHAND3 = (1 << 23),
	IN_OFFHAND4 = (1 << 24), // ultimate Z
	IN_OFFHAND_QUICK = (1 << 25),
	IN_DUCKTOGGLE = (1 << 26),
	IN_USE_AND_RELOAD = (1 << 27),
	IN_DODGE = (1 << 28),
	IN_VARIABLE_SCOPE_TOGGLE = (1 << 29),
	IN_PING = (1 << 30),
	IN_USE_ALT = (1 << 31),
};

#pragma pack(push, 1)
struct CUserCmd {
	int cmdNumber; // 0x0 (0x4)
	int tickCount; // 0x4 (0x4)
	float cmdTime; // 0x8 (0x4)
	Angle_t viewAngles; // 0xC (0xC)
	Angle_t aimDirection; // 0x18 (0xC)
	Vector_t moves; // 0x24 (0xC)
	float absval1[2]; // 0x30 (0x8)
	unsigned int buttons; // 0x38 (0x4)
	char impulse; // 0x3C (0x1)
	char _pad[0x1EB]; // 0x3D (0x1EB)
}; // 0x228
#pragma pack(pop)