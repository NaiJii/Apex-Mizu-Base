#pragma once

#include <cstdint>

enum EFlags {
	FL_ONGROUND = (1 << 0),
	FL_DUCKING = (1 << 1),
	FL_DUCKING_ANIM = (1 << 2),
	FL_WATER_JUMP = (1 << 3),
	FL_ON_TRAIN = (1 << 4),
	FL_IN_RAIN = (1 << 5),
	FL_FROZEN = (1 << 6),
	FL_AT_CONTROLS = (1 << 7),
	FL_CLIENT = (1 << 8),
	FL_FAKE_CLIENT = (1 << 9),
	FL_IN_WATER = (1 << 10),
	FL_FLY = (1 << 11),
	FL_SWIM = (1 << 12),
	FL_CONVEYOR = (1 << 13),
	FL_NPC = (1 << 14),
	FL_GODMODE = (1 << 15),
	FL_NO_TARGET = (1 << 16),
	FL_AIM_TARGET = (1 << 17),
	FL_PARTIAL_GROUND = (1 << 18),
	FL_STATIC_PROP = (1 << 19),
	FL_GRAPHED = (1 << 20),
	FL_GRENADE = (1 << 21),
	FL_STEP_MOVEMENT = (1 << 22),
	FL_DONT_TOUCH = (1 << 23),
	FL_BASE_VELOCITY = (1 << 24),
	FL_WORLD_BRUSH = (1 << 25),
	FL_OBJECT = (1 << 26),
	FL_KILL_ME = (1 << 27),
	FL_ON_FIRE = (1 << 28),
	FL_DISSOLVING = (1 << 29),
	FL_RAGDOLL = (1 << 30),
	FL_UNBLOCKABLE = (1 << 31)
};

enum ELifeState {
	LIFESTATE_ALIVE,
	LIFESTATE_FALLING,
	LIFESTATE_DEAD
};

enum ERenderFx {
	RENDER_FX_NONE = 0,
	RENDER_FX_PULSE_SLOW,
	RENDER_FX_PULSE_FAST,
	RENDER_FX_PULSE_SLOW_WIDE,
	RENDER_FX_PULSE_FAST_WIDE,
	RENDER_FX_FADE_SLOW,
	RENDER_FX_FADE_FAST,
	RENDER_FX_SOLID_SLOW,
	RENDER_FX_SOLID_FAST,
	RENDER_FX_STROBE_SLOW,
	RENDER_FX_STROBE_FAST,
	RENDER_FX_STROBE_FASTER,
	RENDER_FX_FLICKER_SLOW,
	RENDER_FX_FLICKER_FAST,
	RENDER_FX_NODISSIPATION,
	RENDER_FX_FADEOUT,
	RENDER_FX_FADEIN,
	RENDER_FX_PULSE_FAST_WIDER,
	RENDER_FX_GLOWSHELL,
	RENDER_FX_MAX
};

enum EWeaponTypeFlags : uint32_t
{
	WEAPON_TYPE_FLAG_HANDS = 1 << 0, // this will be set when not holding any weapon and doing melee attack
	WEAPON_TYPE_FLAG_PRIMARY = 1 << 1, // weapons
	WEAPON_TYPE_FLAG_MELEE = 1 << 2, // 4 this will be set when doing melee attack
	WEAPON_TYPE_FLAG_TACTICAL = 1 << 3,
	WEAPON_TYPE_FLAG_ULTIMATE = 1 << 4,
	WEAPON_TYPE_FLAG_CONSUMABLE = 1 << 5, // ultimate accelerator / health kit / shield
	WEAPON_TYPE_FLAG_INCAP_SHIELD = 1 << 6, // not sure what is this
	WEAPON_TYPE_FLAG_GRENADE = 1 << 7,
};

enum EAmmoType : uint32_t {
	AMMOTYPE_LIGHT = 0,
	AMMOTYPE_HEAVY,
	AMMOTYPE_ENERGY,
	AMMOTYPE_SHOTGUN,
	AMMOTYPE_SNIPER,
};

