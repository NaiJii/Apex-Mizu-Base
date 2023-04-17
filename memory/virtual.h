#pragma once

#include <cstddef>
#include <cstdint>
#include <utility>

import memory;

namespace Memory {
	template <typename T = void*>
	constexpr T GetVirtual(void* base, int index) {
		return (*(T**)(base))[index];
	}

	template<typename R = void, size_t index, typename... Args_t>
	constexpr R CallVirtual(void* base, Args_t... args) {
		using Fn_t = R(__thiscall*)(void*, Args_t...);
		return GetVirtual<Fn_t>(base, index)(base, args...);
	}
}

#define STR_MERGE_IMPL(a, b) a##b
#define STR_MERGE(a, b) STR_MERGE_IMPL(a, b)
#define PAD(size) unsigned char STR_MERGE(_pad, __COUNTER__)[size]
#define MEMBER(type, name, offset) struct {PAD(offset); type name;}

#define VCALL(returnType, name, idx, args, argsRaw) \
returnType name args \
{ \
    return Memory::CallVirtual<returnType, idx>argsRaw; \
}
