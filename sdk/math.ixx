module;

#include <algorithm>
#include <cmath>
#include <corecrt_math_defines.h>
#include <vector>

#include "type/matrix.h"
#include "type/angle.h"
#include "type/vector.h"

export module math;

export namespace Math {
	constexpr inline float RadToDeg(const float x) noexcept {
		return x * (180.f / float(M_PI));
	}

	constexpr inline float DegToRad(const float x) noexcept {
		return x * (float(M_PI) / 180.f);
	}

	Angle_t CalcAngle(const Vector_t& src, const Vector_t& dst);
	float Fov(const Angle_t& src, const Angle_t& dst);

	void RotatePoint(const Vector2_t& in, const float degrees, Vector2_t& out) noexcept;
	void RotatePointAroundCenter(const Vector2_t& center, const float degrees, Vector2_t& out) noexcept;
}