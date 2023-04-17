#pragma once

#include <cstdint>

struct RecvProp_t;

static constexpr const char* SEND_PROP_TYPES[11] = {
	"int", "float", "Vector", "Vector2D", "const char*",
	"Array", "Angle", "bitMask", "Cycle", "Time",
	"DataTable",
};

static constexpr const char* FIELD_TYPES[32] = {
	"void", "float", "const char*", "Vector", "Quaternion",
	"int", "bool", "short", "char", "Color",
	"Embedded", "Custom", "ClassPtr", "EHandle", "edict",
	"PositionVector", "Time", "Tick", "ModelName", "SoundName",
	"20", "21", "22", "23", "24",
	"25","26", "27", "28", "29",
	"30", "Outer",
};

struct RecvTable_t {
	void* instance; // 0x0 (0x8)
	RecvProp_t** props; // 0x8 (0x8)
	uint32_t propsCount; // 0x10 (0x4)
	uint32_t _pad0[256]; // 0x14 (0x400)
	uint32_t _pad1[43]; // 0x414 (0xAC)
	void* decoder; // 0x4C0 (0x8)
	const char* name; // 0x4C8 (0x8)
	bool initialized; // 0x4D0 (0x1)
	bool inMainList; // 0x4D1 (0x1)
	uint8_t _pad2[6]; // 0x4D2 (0x6)
}; // sizeof: 0x4D8

struct RecvProp_t {
	int32_t type; // 0x0 (0x4)
	uint32_t offset; // 0x4 (0x4)
	uint32_t _pad0[6]; // 0x8 (0x18)
	RecvTable_t* dataTable; // 0x20 (0x8)
	const char* name; // 0x28 (0x8)
	bool isInsideArray; // 0x30 (0x1)
	uint8_t _pad1[7]; // 0x31 (0x7)
	RecvProp_t* arrayProp; // 0x38 (0x8)
	void* proxyFn; // 0x40 (0x8)
	char _pad2[12]; // 0x48 (0x12)
	int32_t flags; // 0x5A (0x4)
	uint32_t _pad3; // 0x5E (0x4)
	int32_t numElements; // 0x62 (0x4)
	uint32_t _pad4; // 0x66 (0x4)
}; // sizeof: 0x6A

struct Datamap_t;
