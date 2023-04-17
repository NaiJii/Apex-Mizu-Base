#pragma once

#include <cstdint>

struct IClientNetworkable;
struct RecvTable_t;
typedef IClientNetworkable* (*CreateClientClassFn_t)( int entNum, int serialNum );
typedef IClientNetworkable* (*CreateEventFn_t)();

struct ClientClass_t {
	CreateClientClassFn_t m_createFn; // 0x0 (0x8)
	CreateEventFn_t m_createEventFn; // 0x8 (0x8)
	char* m_networkName; // 0x10 (0x8)
	RecvTable_t* m_recvTable; // 0x18 (0x8)
	ClientClass_t* m_next; // 0x20 (0x8)
	int32_t m_classID; // 0x28 (0x4)
	uint32_t m_classSize; // 0x2C (0x4)
	char* m_name; // 0x30 (0x8)
}; // 0x38
