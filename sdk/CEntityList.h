#pragma once

#include <cstdint>

inline constexpr size_t NUM_ENT_ENTRIES = 0x10000;
inline constexpr size_t INVALID_HANDLE = 0xffffffff;

// https://github.com/ValveSoftware/source-sdk-2013/blob/master/mp/src/game/shared/entitylist_base.h

struct CEntity;

struct EHandle {
	// The low NUM_SERIAL_BITS hold the index. If this value is less than MAX_EDICTS, then the entity is networkable.
	// The high NUM_SERIAL_NUM_BITS bits are the serial number.
	uint32_t value = INVALID_HANDLE;

	bool IsValid() const { return value != INVALID_HANDLE; }
	size_t Index() const { return value & uint32_t(NUM_ENT_ENTRIES - 1); }

	bool operator==(const EHandle other) const {
		return value == other.value;
	}
};

struct CEntInfo {
	CEntity* m_entity;
	int64_t m_serialNumber;
	CEntInfo* m_prev;
	CEntInfo* m_next;
};

struct CEntityList {
	struct CEntInfoList {
		CEntInfo* m_head;
		CEntInfo* m_tail;
	};

	int GetEntInfoIndex(CEntInfo* entInfo);
	CEntInfo& GetEntInfoFromHandle(EHandle h) {
		return m_entInfos[h.Index()];
	}

	CEntInfo m_entInfos[NUM_ENT_ENTRIES];
	CEntInfoList m_activeList;
	CEntInfoList m_freeNonNetworkableList;
};

inline int CEntityList::GetEntInfoIndex(CEntInfo* entInfo)
{
	if (!entInfo)
		return -1;

	int index = (int)(entInfo - m_entInfos);
	if (index < 0 || index >= NUM_ENT_ENTRIES)
		return -1;

	return index;
}

struct CClientEntityList {
};