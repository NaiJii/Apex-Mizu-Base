#pragma once
#include "vector.h"

enum EHighlightContextID {
	HIGHLIGHT_CONTEXT_NONE = -1,
	HIGHLIGHT_CONTEXT_NEUTRAL = 0,
	HIGHLIGHT_CONTEXT_FRIENDLY = 1,
	HIGHLIGHT_CONTEXT_ENEMY = 2,
	HIGHLIGHT_CONTEXT_OWNED = 3,
	HIGHLIGHT_CONTEXT_PRIVATE_MATCH_OBSERVER = 4,
	HIGHLIGHT_CHARACTER_SPECIAL_HIGHLIGHT = 5,
	HIGHLIGHT_CONTEXT_DEATH_RECAP = 6,
	HIGHLIGHT_CONTEXT_SONAR = 7,
	HIGHLIGHT_CHARACTER_SPECIAL_HIGHLIGHT_2 = 8,
	HIGHLIGHT_CONTEXT_FRIENDLY_REVEALED = 9,
	HIGHLIGHT_CONTEXT_MOVEMENT_REVEALED = 10,
	HIGHLIGHT_MAX_CONTEXTS = 11
};

enum EHighlightVis {
	HIGHLIGHT_VIS_NONE = 0,
	HIGHLIGHT_VIS_FORCE_ON = 1,
	HIGHLIGHT_VIS_ALWAYS = 2,
	HIGHLIGHT_VIS_OCCLUDED = 3,
	HIGHLIGHT_VIS_FULL_VIEW = 4,
	HIGHLIGHT_VIS_LOS = 5,
	HIGHLIGHT_VIS_LOS_ENTSONLYCONTENTSBLOCK = 6
};

enum EHighlightOutterFn {
	HIGHLIGHT_OUTLINE_NONE = 0,
	HIGHLIGHT_OUTLINE_MENU_MODEL_REVEAL = 75,
	HIGHLIGHT_OUTLINE_CUSTOM_COLOR = 101,
	HIGHLIGHT_OUTLINE_EDGE_ = 102,
	HIGHLIGHT_OUTLINE_SONAR = 103,
	HIGHLIGHT_OUTLINE_INTERACT_BUTTON = 105,
	HIGHLIGHT_OUTLINE_CUSTOM_COLOR_WEAPON_PICKUP = 110,
	HIGHLIGHT_OUTLINE_VM_CUSTOM_COLOR = 114,
	HIGHLIGHT_OUTLINE_SMTH = 117,
	HIGHLIGHT_OUTLINE_CUSTOM_COLOR_PULSE = 120,
	HIGHLIGHT_OUTLINE_CUSTOM_COLOR_OBEY_Z = 121,
	HIGHLIGHT_OUTLINE_OBJECTIVE = 125,
	HIGHLIGHT_OUTLINE_CUSTOM_COLOR_OCCLUDED_NOSCANLINES = 129,
	HIGHLIGHT_OUTLINE_LOOT_DEFAULT = 135,
	HIGHLIGHT_OUTLINE_LOOT_FOCUSED = 136,
	HIGHLIGHT_OUTLINE_LOOT_SCANNED = 138,
	HIGHLIGHT_OUTLINE_CRYPTO_DRONE = 140,
	HIGHLIGHT_OUTLINE_CUSTOM_COLOR_OCCLUDED = 145,
	HIGHLIGHT_OUTLINE_CUSTOM_COLOR_NOZ_NOSCANLINES = 169,
};

enum EHighlightFlag {
	HIGHLIGHT_FLAG_NONE = (0 << 0),
	HIGHLIGHT_FLAG_ADS_FADE = (1 << 1),
	HIGHLIGHT_FLAG_REQUIRE_NOT_FULL_HEALTH = (1 << 2),
	HIGHLIGHT_FLAG_REQUIRE_CAN_PICK_UP_CLIP = (1 << 3),
	HIGHLIGHT_FLAG_REQUIRE_CAN_PICK_UP_OFFHAND = (1 << 4),
	HIGHLIGHT_FLAG_REQUIRE_WEAKPOINT_VISIBLE = (1 << 5),
	HIGHLIGHT_FLAG_REQUIRE_PILOT = (1 << 6),
	HIGHLIGHT_FLAG_REQUIRE_TITAN = (1 << 7),
	HIGHLIGHT_FLAG_REQUIRE_SAME_TEAM = (1 << 8),
	HIGHLIGHT_FLAG_REQUIRE_DIFFERENT_TEAM = (1 << 9),
	HIGHLIGHT_FLAG_REQUIRE_FRIENDLY_TEAM = (1 << 10),
	HIGHLIGHT_FLAG_REQUIRE_ENEMY_TEAM = (1 << 11),
	HIGHLIGHT_FLAG_REQUIRE_LOCAL_PLAYER_IS_OWNER = (1 << 12),
	HIGHLIGHT_FLAG_REQUIRE_LOW_MOVEMENT = (1 << 13),
	HIGHLIGHT_FLAG_REQUIRE_HIGH_MOVEMENT = (1 << 14),
	HIGHLIGHT_FLAG_CHECK_OFTEN = (1 << 15),
};

enum EHighlightInnerFn {
	HIGHLIGHT_FILL_NONE = 0,
	HIGHLIGHT_FILL_BLOODHOUND = 12,
	HIGHLIGHT_FILL_BLOODHOUND_CLONE = 13,
	HIGHLIGHT_FILL_MENU_MODEL_REVEAL = 75,
	HIGHLIGHT_FILL_MENU_MODEL_REVEAL_TSAA = 76,
	HIGHLIGHT_FILL_CUSTOM_COLOR = 101,
	HIGHLIGHT_FILL_INTERACT_BUTTON = 103,
	HIGHLIGHT_FILL_LOBBY_IN_MATCH = 109,
	HIGHLIGHT_FILL_NEWT = 112,
	HIGHLIGHT_FILL_VM_CUSTOM_COLOR = 114,
	HIGHLIGHT_FILL_OBJECTIVE = 126,
	HIGHLIGHT_FILL_CAUSTIC_THREAT = 133,
	HIGHLIGHT_FILL_CRYPTO = 133,
	HIGHLIGHT_FILL_CAUSTIC_CANISTER = 134,
	HIGHLIGHT_FILL_LOOT_DEFAULT = 135,
	HIGHLIGHT_FILL_LOOT_FOCUSED = 136,
	HIGHLIGHT_FILL_LOOT_SCANNED = 137,
	HIGHLIGHT_FILL_CRYPTO_DRONE = 139,
	HIGHLIGHT_FILL_OBSERVER = 141,
	HIGHLIGHT_FILL_EMPTY_OCCLUDED = 146,
};

struct HighlightParams_t {
	Vector_t color;
	Vector_t pos;
}; // sizeof 0x18

struct HighlightBits_t {
	HighlightBits_t() = default;
	HighlightBits_t(uint8_t insideFunction, uint8_t outsideFunction, uint8_t outlineRadius, uint8_t state, uint8_t shouldDraw, uint8_t postProcess) {
		this->insideFunction = insideFunction;
		this->outsideFunction = outsideFunction;
		this->outlineRadius = outlineRadius;
		this->state = state;
		this->shouldDraw = shouldDraw;
		this->postProcess = postProcess;
	}
	
	uint8_t insideFunction;
	uint8_t outsideFunction;
	uint8_t outlineRadius;
	uint8_t state : 6;
	uint8_t shouldDraw : 1;
	uint8_t postProcess : 1;

	uint32_t AsInt() {
		return *(uint32_t*)this;
	}
}; // sizeof 0x4

struct HighlightFadeSlot_t {
	HighlightFadeSlot_t() = default;
	float inside;
	float outside;
}; // sizeof 0x8

struct HighlightSettings_t {
	HighlightSettings_t() = default;
	HighlightParams_t params[HIGHLIGHT_MAX_CONTEXTS]; // 0x1B8 (0x108)
	HighlightBits_t serverFunctionBits[HIGHLIGHT_MAX_CONTEXTS]; // 0x2C0 (0x2C)
	HighlightBits_t clientFunctionBits[HIGHLIGHT_MAX_CONTEXTS]; // 0x2EC (0x2C)
	HighlightBits_t serverTeamBits[HIGHLIGHT_MAX_CONTEXTS]; // 0x318 (0x2C)
	HighlightBits_t clientTeamBits[HIGHLIGHT_MAX_CONTEXTS]; // 0x344 (0x2C)
	HighlightFadeSlot_t serverFadeBases; // 0x370 (0x8)
	HighlightFadeSlot_t serverFadeStartTimes; // 0x378 (0x8)
	HighlightFadeSlot_t serverFadeEndTimes; // 0x380 (0x8)
	HighlightFadeSlot_t clientFadeBases; // 0x388 (0x8)
	HighlightFadeSlot_t clientFadeStartTimes; // 0x390 (0x8)
	HighlightFadeSlot_t clientFadeEndTimes; // 0x398 (0x8)
	float lifetime; // 0x3A0 (0x4)
	float lastUpdateTime; // 0x3A4 (0x4)
	float fadeInTime; // 0x3A8 (0x4)
	float fadeOutTime; // 0x3AC (0x4)
	float nearFadeDist; // 0x3B0 (0x4)
	float farFadeDist; // 0x3B4 (0x4)
	HighlightFadeSlot_t oldFadeEnd; // 0x3B8 (0x8)
	int32_t serverContextId; // 0x3C0 (0x4)
	int32_t clientContextId; // 0x3C4 (0x4)
	int32_t currentContextId; // 0x3C8 (0x4)
	uint32_t flag; // 0x3CC (0x4)
	int32_t visibilityType; // 0x3D0 (0x4)
}; // sizeof 0x21C