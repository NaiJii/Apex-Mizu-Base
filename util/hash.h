#pragma once

#include <cstddef>
#include <string>

namespace Util {
	namespace Hash {
		template <typename T, T V> struct ConstantHolder {
			enum class ValHolder : T { val = V };
		};

		constexpr inline uint32_t basis = 0x11111111;
		constexpr inline uint32_t prime = 0x12345678;

		constexpr inline uint32_t GetConst(const char* txt, const uint32_t value = basis) noexcept {
			return txt[0] == '\0' ? value : GetConst(&txt[1], (value ^ static_cast<uint32_t>(txt[0])) * prime);
		}

		static uint32_t Get(std::string_view string) noexcept {
			uint32_t result = basis;
			for (size_t i = 0; i < string.length(); ++i) {
				result ^= string[i];
				result *= prime;
			}
			return result;
		}
	}
}

#define VAL_CT(value) (decltype(value))Util::Hash::ConstantHolder<decltype(value), value>::ValHolder::val
#define HASH_CT(x) VAL_CT(Util::Hash::GetConst(x))
#define HASH(x) Util::Hash::Get(x)
