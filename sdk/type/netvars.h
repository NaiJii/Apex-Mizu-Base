#pragma once

#include "../../include.h"

#include "recv.h"

// #define LOG_NETVARS

namespace SDK {
	struct PropNode_t {
		RecvProp_t* m_prop = nullptr;
		// offset relative to parent
		uint32_t m_relOffset = 0;
		// offset relative to the upmost parent
		uint32_t m_offset = 0;
		uint32_t m_tableHash = HASH_CT("");
	};
	inline std::unordered_map<uint32_t, std::map<uint32_t, PropNode_t>> m_propTree;

	void PopulateNodes(RecvTable_t* table, uint32_t baseOffset = 0);
	void ParseNetVars();
}

#define NETVAR_OFFSET(type, name, dataTable, propName, add) \
type& name() { \
	static uint32_t offset = SDK::m_propTree[HASH_CT(dataTable)][HASH_CT(propName)].m_offset + add; \
	return *(type*)((uintptr_t)this + offset); \
}

#define NETVAR(type, name, dataTable, propName) \
type& name() { \
	static uint32_t offset = SDK::m_propTree[HASH_CT(dataTable)][HASH_CT(propName)].m_offset; \
	return *(type*)((uintptr_t)this + offset); \
}

#define NETVAR_PTR(type, name, dataTable, propName) \
type* name() { \
	static uint32_t offset = SDK::m_propTree[HASH_CT(dataTable)][HASH_CT(propName)].m_offset; \
	return (type*)((uintptr_t)this + offset); \
}
