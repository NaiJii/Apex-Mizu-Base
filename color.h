#pragma once

#include <algorithm>

struct Color_t {
	Color_t() = default;
	Color_t(const int r, const int g, const int b, const int a = 255);
	Color_t(const float r, const float g, const float b, const float a);
	int& operator[](size_t i) noexcept;
	int operator[](size_t i) const noexcept;

	bool operator==(const Color_t& other) const {
		return other.r == r && other.g == g && other.b == b && other.a == a;
	}

	bool operator!=(const Color_t& other) const {
		return other.r != r || other.g != g || other.b != b || other.a != a;
	}

	void operator*=(const float m) {
		r = static_cast<uint8_t>(r * m);
		g = static_cast<uint8_t>(g * m);
		b = static_cast<uint8_t>(b * m);
		a = static_cast<uint8_t>(a * m);
	}

	uint8_t r, g, b, a;
};
