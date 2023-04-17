#include "sdk.h"
#include "type/netvars.h"

import memory;
import util;
import render;

#define SET_(member, pattern, base) \
if (!pattern.Valid()) { \
	Util::Log<LOG_ERROR>("{} could not be found!\n", std::string(#member).c_str()); \
	return false; \
} \
member = pattern.Cast<decltype(member)>(); \
Util::Log("{} > {:#X}", std::string(#member).c_str(), (uintptr_t)member - (uintptr_t)base);

// i'm lazy ok
#define SET(member, pattern) SET_(member, pattern, Memory::m_base.m_address)

bool SDK::Setup() {
	SET(m_clientState, Memory::Addresses::m_clientState);
	SET(m_cl_entity_list, Memory::Addresses::m_cl_entity_list);
	SET(m_chlClient, Memory::Addresses::m_chlClient);
	SET(m_engineClient, Memory::Addresses::m_engineClient);
	SET(m_input, Memory::Addresses::m_input);
	SET(m_gameMovement, Memory::Addresses::m_gameMovement);
	SET(m_globalVars, Memory::Addresses::m_globalVars);
	SET(m_viewRender, Memory::Addresses::m_viewRender);
	SET(m_localPlayerPtr, Memory::Addresses::m_localPlayerPtr);
	SET(m_levelName, Memory::Addresses::m_levelName);

	Util::Log(_("sdk::setup done!\n"));
	return true;
}

bool SDK::Init()
{
	if (m_init)
		return false;

	ParseNetVars();

	Util::Log(_("sdk::init done!\n"));

#if 1
	uint32_t m_iTeamNum = m_propTree[HASH_CT("DT_BaseEntity")][HASH_CT("m_iTeamNum")].m_offset;
	uint32_t m_Collision = m_propTree[HASH_CT("DT_BaseEntity")][HASH_CT("m_Collision")].m_offset;
	uint32_t m_highlightParams = m_propTree[HASH_CT("DT_HighlightSettings")][HASH_CT("m_highlightParams")].m_offset;
	Util::Log<LOG_DEBUG>(_("\t{} : {:#x}"), "m_iTeamNum", m_iTeamNum);
	Util::Log<LOG_DEBUG>(_("\t{} : {:#x}"), "m_Collision", m_Collision);
	Util::Log<LOG_DEBUG>(_("\t{} : {:#x}"), "m_highlightParams", m_highlightParams);
#endif

	m_init = true;
	return true;
}

void SDK::PopulateNodes(RecvTable_t* table, uint32_t baseOffset) {
	const uint32_t tableHash = HASH(table->name);
	if (m_propTree.count(tableHash) == 0)
		m_propTree[tableHash] = {};

#ifdef LOG_NETVARS
	Util::Log<LOG_DEBUG>(_("\t{} with {} props"), table->name, table->propsCount);
#endif

	for (uint32_t i = 0; i < table->propsCount; i++) {
		RecvProp_t* prop = table->props[i];
		if (!prop || !prop->name)
			continue;

		// filter array elements, you can probably add more checks here
		if (prop->name[0] == '[')
			continue;

		const uint32_t propHash = HASH(prop->name);
		bool isDatamap = prop->dataTable && prop->dataTable->name;
		if (isDatamap) {
#ifdef LOG_NETVARS
			Util::Log<LOG_DEBUG>(_("\t\tdatamap: {}"), prop->dataTable->name);
#endif
			PopulateNodes(prop->dataTable, baseOffset + prop->offset);
#ifdef LOG_NETVARS
			Util::Log<LOG_DEBUG>(_("\t{} inherits {}"), table->name, prop->dataTable->name);
#endif

			// give the inherited table shortcuts to the inherited properties
			for (const auto& [hash, node] : m_propTree[HASH(prop->dataTable->name)]) {
				if (node.m_relOffset == 0)
					continue;

				auto& props = m_propTree[tableHash];
				if (props.count(hash) != 0 && props[hash].m_relOffset != 0 && props[hash].m_relOffset != node.m_relOffset) {
#ifdef LOG_NETVARS
					Util::Log<LOG_WARNING>(_("\t\t{} already exists with different offset, skipping"), prop->name);
#endif
					continue;
				}

#ifdef LOG_NETVARS
				Util::Log<LOG_DEBUG>(_("\t{} : {:#x}"), prop->name, node.m_relOffset);
#endif

				props[hash] = node;
				props[hash].m_offset += baseOffset;
			}
		}

		if (m_propTree[tableHash].count(propHash)) {
			if (m_propTree[tableHash][propHash].m_relOffset != prop->offset) {
#ifdef LOG_NETVARS
				Util::Log<LOG_WARNING>(_("\t\t{} already exists with different offset, skipping"), prop->name);
#endif
			}

			continue;
		}

		if (prop->offset) {
			m_propTree[tableHash][propHash] = {
				.m_prop = prop,
				.m_relOffset = prop->offset,
				.m_offset = baseOffset + prop->offset,
				.m_tableHash = isDatamap ? HASH(prop->dataTable->name) : HASH_CT("")
			};

#ifdef LOG_NETVARS
			Util::Log<LOG_DEBUG>(_("\t{} {} : {:#x}"), table->name, prop->name, prop->offset);
#endif
		}
	}
}

void SDK::ParseNetVars()
{
	Util::Log(_("parsing netvars..."));
	// get the client class list
	ClientClass_t* classes = m_chlClient->GetAllClasses();
	if (!classes) {
		Util::Log<LOG_ERROR>(_("failed to get client class list"));
		return;
	}

	// iterate through the client classes
	for (ClientClass_t* clientClass = classes; clientClass; clientClass = clientClass->m_next) {
		RecvTable_t* table = clientClass->m_recvTable;
		if (!table || !table->name)
			continue;

		PopulateNodes(table);
	}

	Util::Log(_("netvars parsed!\n"));
}

bool SDK::Update() {
	if (m_updated)
		return false;

	long viewMatrixOffset = Memory::m_bin.FindPattern(_("48 0F BE C2 48 8B 84 C1 ? ? ? ? C3")).Offset(0x4).RelativeOffset(0x4);
	auto ptr = Memory::Address_t(m_viewRender).Get().Offset(viewMatrixOffset).Cast<VMatrix**>();
	if (!ptr) {
		Util::Log<LOG_ERROR>(_("wrong view matrix offset"));
		return false;
	}

	m_viewMatrixPtr = *ptr;

	m_updated = true;
	Util::Log(_("sdk::update done!\n"));
	return true;
}