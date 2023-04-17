#include <algorithm>
#include <cmath>
#include <corecrt_math_defines.h>
#include <vector>

#include "type/matrix.h"
#include "type/angle.h"
#include "type/vector.h"

import math;

Angle_t Math::CalcAngle(const Vector_t& src, const Vector_t& dst) {
	return (dst - src).ToAngle();
}

float Math::Fov(const Angle_t& src, const Angle_t& dst) {
	return (src - dst).Length();
}

void Math::RotatePoint(const Vector2_t& in, const float degrees, Vector2_t& out) noexcept {
	if (&in == &out) {
		const Vector2_t point = in;
		RotatePoint(point, degrees, out);
		return;
	}

	const float f_sin = std::sinf(DegToRad(degrees));
	const float f_cos = std::cosf(DegToRad(degrees));

	out.x = in.x * f_cos - in.y * f_sin;
	out.y = in.x * f_sin - in.y * f_cos;
}

void Math::RotatePointAroundCenter(const Vector2_t& center, const float degrees, Vector2_t& out) noexcept {
	const float f_sin = std::sinf(DegToRad(degrees));
	const float f_cos = std::cosf(DegToRad(degrees));

	out -= center;

	const Vector2_t point = Vector2_t(out.x * f_cos - out.y * f_sin, out.x * f_sin + out.y * f_cos);

	out = point + center;
}