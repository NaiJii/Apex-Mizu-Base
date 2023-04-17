#pragma once

#include <cstdint>
#include <cmath>

#include "../../memory/virtual.h"

#include "vector.h"
#include "utl.h"

enum EBoneId {
	BONE_SPINE = 3,
	BONE_CHEST = 5,
	BONE_NECK = 7,
	BONE_HEAD = 8,
	BONE_LEFT_SHOULDER = 11,
	BONE_LEFT_ELBOWROLL = 13,
	BONE_LEFT_HAND = 15,
	BONE_RIGHT_ARM = 16,
	BONE_RIGHT_SHOULDER = 35,
	BONE_RIGHT_ELBOWROLL = 37,
	BONE_RIGHT_HAND = 39,
	BONE_LEFT_ARM = 41,
	BONE_LEFT_KNEE = 58,
	BONE_RIGHT_KNEE = 63,
	BONE_LEFT_FOOT = 65,
	BONE_RIGHT_FOOT = 60,
};

enum EHitboxId {
	HITBOX_HEAD,
	HITBOX_NECK,
	HITBOX_UPPER_CHEST,
	HITBOX_LOWER_CHEST,
	HITBOX_STOMACH,
	HITBOX_CROTCH,
	HITBOX_LEFT_UPPER_ARM,
	HITBOX_LEFT_FOREARM,
	HITBOX_LEFT_HAND,
	HITBOX_RIGHT_UPPER_ARM,
	HITBOX_RIGHT_FOREARM,
	HITBOX_RIGHT_HAND,
	HITBOX_LEFT_THIGH,
	HITBOX_LEFT_CALF,
	HITBOX_LEFT_FOOT,
	HITBOX_LEFT_TOES,
	HITBOX_RIGHT_THIGH,
	HITBOX_RIGHT_CALF,
	HITBOX_RIGHT_FOOT,
	HITBOX_RIGHT_TOES,
	HITBOX_LEFT_UPPER_LEG,
	HITBOX_RIGHT_UPPER_LEG,
	HITBOX_LEFT_SHOULDER,
	HITBOX_RIGHT_SHOULDER
};

enum EHitgroup
{
	HITGROUP_GENERIC = 0,
	HITGROUP_HEAD = 1,
	HITGROUP_CHEST = 2,
	HITGROUP_STOMACH = 3,
	HITGROUP_LEFTARM = 4,
	HITGROUP_RIGHTARM = 5,
	HITGROUP_LEFTLEG = 6,
	HITGROUP_RIGHTLEG = 7,
	HITGROUP_GEAR = 10
};

struct StudioBone_t {
	uint32_t one;
	uint16_t unk1;
	uint16_t unk2;
	uint16_t parent;
	uint16_t unk3;
};

struct StudioBBox_t {
	uint16_t m_bone; // 0x0
	uint16_t group; // 0x2
	Vector_t mins; // 0x4
	Vector_t maxs; //	0x10
	uint16_t hitboxNameId; // 0x1C
	char pad_0024[2]; // 0x1E

	float Radius() const {
		Vector_t size = maxs - mins;
		float volume = size.LengthSqr();
		return std::cbrt(volume / (4.f / 3.f * 3.1415f));
	}
}; // 0x20

struct StudioHitboxSet_t {
	uint16_t m_nameIndex; // 0x0
	uint16_t m_hitboxCount; // 0x2
	uint16_t m_hitboxIndex; // 0x4

	inline char* const Name() const {
		return ((char*)this) + m_nameIndex;
	}

	StudioBBox_t* Hitbox(int index) const {
		return (StudioBBox_t*)(((uintptr_t)this) + m_hitboxIndex) + index;
	}
};

struct StudioHdr_t {
	uint16_t m_id; // 0x0
	uint16_t m_version; // 0x2
	PAD(0x2C); // 0x4
	uint16_t m_hitboxSetCount; // 0x30
	PAD(0x2); // 0x32
	uint16_t m_hitboxSetIndex; // 0x34
	PAD(0x3E); // 0x36
	uint16_t m_boneCount; // 0x74
	uint16_t m_boneIndex; // 0x76
	uint16_t m_unkIndex; // 0x78
	uint16_t m_seqCount; // 0x7A
	uint16_t m_seqIndex; // 0x7C
	PAD(0x5);
	uint16_t m_unk2Count;
	uint16_t m_unk2Index;

	StudioHitboxSet_t* HitboxSet(int index) const {
		return (StudioHitboxSet_t*)((uintptr_t)this + m_hitboxSetIndex) + index;
	}

	StudioBone_t* Bone(int index) const {
		if (index < 0 || index >= m_boneCount)
			return nullptr;

		return (StudioBone_t*)(((uintptr_t)this) + m_boneIndex) + index;
	}
};

struct Sequence_t;

struct CSoftBody {
};

struct VirtualModel_t {
	PAD(0x2); // 0x0 (0x2)
	uint16_t m_seqCount; // 0x2 (0x2)
	PAD(0xC); // 0x4 (0xC)
	void* m_someList; // 0x10 (0x8)
};

struct CStudioHdr {
	void* vtable; // 0x0 (0x8)
	const StudioHdr_t* m_hdr; // 0x8 (0x8)
	CUtlVector<void*> m_hdrCache; // 0x10 (0x1C)
	int m_frameUnlockCounter;
	int* m_frameUnlockCounterPtr;
}; // 0x20
