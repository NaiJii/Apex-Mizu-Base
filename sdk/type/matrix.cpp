#include "matrix.h"
#include "angle.h"

import math;
#include <algorithm>
#include <cmath>

Matrix3x4_t::Matrix3x4_t(float m00, float m01, float m02, float m03, float m10, float m11, float m12, float m13, float m20, float m21, float m22, float m23) noexcept {
	m_value[0][0] = m00;
	m_value[0][1] = m01;
	m_value[0][2] = m02;
	m_value[0][3] = m03;

	m_value[1][0] = m10;
	m_value[1][1] = m11;
	m_value[1][2] = m12;
	m_value[1][3] = m13;

	m_value[2][0] = m20;
	m_value[2][1] = m21;
	m_value[2][2] = m22;
	m_value[2][3] = m23;
}

Matrix3x4_t::Matrix3x4_t(const Vector_t& x_axis, const Vector_t& y_axis, const Vector_t& z_axis, const Vector_t& localPos) noexcept {
	m_value[0][0] = x_axis.x;
	m_value[0][1] = y_axis.x;
	m_value[0][2] = z_axis.x;
	m_value[0][3] = localPos.x;

	m_value[1][0] = x_axis.y;
	m_value[1][1] = y_axis.y;
	m_value[1][2] = z_axis.y;
	m_value[1][3] = localPos.y;

	m_value[2][0] = x_axis.z;
	m_value[2][1] = y_axis.z;
	m_value[2][2] = z_axis.z;
	m_value[2][3] = localPos.z;
}

Vector_t Matrix3x4_t::GetColumn(int column) const noexcept { return Vector_t(m_value[0][column], m_value[1][column], m_value[2][column]); }

void Matrix3x4_t::set_column(const Vector_t& value, int column) noexcept {
	m_value[0][column] = value.x;
	m_value[1][column] = value.y;
	m_value[2][column] = value.z;
}

void Matrix3x4_t::add_to_column(const Vector_t& value, int column) noexcept {
	m_value[0][column] += value.x;
	m_value[1][column] += value.y;
	m_value[2][column] += value.z;
}

Matrix3x4_t Matrix3x4_t::operator+(const Matrix3x4_t& value) const noexcept {
	return Matrix3x4_t(
		m_value[0][0] + value[0][0],
		m_value[0][1] + value[0][1],
		m_value[0][2] + value[0][2],
		m_value[0][3] + value[0][3],
		m_value[1][0] + value[1][0],
		m_value[1][1] + value[1][1],
		m_value[1][2] + value[1][2],
		m_value[1][3] + value[1][3],
		m_value[2][0] + value[2][0],
		m_value[2][1] + value[2][1],
		m_value[2][2] + value[2][2],
		m_value[2][3] + value[2][3]
	);
}

Matrix3x4_t Matrix3x4_t::operator*(const Matrix3x4_t& value) const noexcept {
	return Matrix3x4_t(
		m_value[0][0] * value[0][0] + m_value[0][1] * value[1][0] + m_value[0][2] * value[2][0],
		m_value[0][0] * value[0][1] + m_value[0][1] * value[1][1] + m_value[0][2] * value[2][1],
		m_value[0][0] * value[0][2] + m_value[0][1] * value[1][2] + m_value[0][2] * value[2][2],
		m_value[0][0] * value[0][3] + m_value[0][1] * value[1][3] + m_value[0][2] * value[2][3] + m_value[0][3],
		m_value[1][0] * value[0][0] + m_value[1][1] * value[1][0] + m_value[1][2] * value[2][0],
		m_value[1][0] * value[0][1] + m_value[1][1] * value[1][1] + m_value[1][2] * value[2][1],
		m_value[1][0] * value[0][2] + m_value[1][1] * value[1][2] + m_value[1][2] * value[2][2],
		m_value[1][0] * value[0][3] + m_value[1][1] * value[1][3] + m_value[1][2] * value[2][3] + m_value[1][3],
		m_value[2][0] * value[0][0] + m_value[2][1] * value[1][0] + m_value[2][2] * value[2][0],
		m_value[2][0] * value[0][1] + m_value[2][1] * value[1][1] + m_value[2][2] * value[2][1],
		m_value[2][0] * value[0][2] + m_value[2][1] * value[1][2] + m_value[2][2] * value[2][2],
		m_value[2][0] * value[0][3] + m_value[2][1] * value[1][3] + m_value[2][2] * value[2][3] + m_value[2][3]
	);
}

Matrix3x4_t Matrix3x4_t::operator*(float value) const noexcept {
	return Matrix3x4_t(
		m_value[0][0] * value,
		m_value[0][1] * value,
		m_value[0][2] * value,
		m_value[0][3] * value,
		m_value[1][0] * value,
		m_value[1][1] * value,
		m_value[1][2] * value,
		m_value[1][3] * value,
		m_value[2][0] * value,
		m_value[2][1] * value,
		m_value[2][2] * value,
		m_value[2][3] * value
	);
}

Vector_t Matrix3x4_t::operator*(const Vector_t& value) const noexcept {
	return Vector_t(
		m_value[0][0] * value.x + m_value[0][1] * value.y + m_value[0][2] * value.z + m_value[0][3],
		m_value[1][0] * value.x + m_value[1][1] * value.y + m_value[1][2] * value.z + m_value[1][3],
		m_value[2][0] * value.x + m_value[2][1] * value.y + m_value[2][2] * value.z + m_value[2][3]
	);
}

Matrix3x4_t& Matrix3x4_t::build_rotation_about_axis(const Vector_t& axis, float degrees) noexcept {
	float f_sin = sinf(Math::DegToRad(degrees));
	float f_cos = cosf(Math::DegToRad(degrees));

	float x_squared = axis[0] * axis[0];
	float y_squared = axis[1] * axis[1];
	float z_squared = axis[2] * axis[2];

	// Column 0:
	m_value[0][0] = x_squared + (1 - x_squared) * f_cos;
	m_value[1][0] = axis[0] * axis[1] * (1 - f_cos) + axis[2] * f_sin;
	m_value[2][0] = axis[2] * axis[0] * (1 - f_cos) - axis[1] * f_sin;

	// Column 1:
	m_value[0][1] = axis[0] * axis[1] * (1 - f_cos) - axis[2] * f_sin;
	m_value[1][1] = y_squared + (1 - y_squared) * f_cos;
	m_value[2][1] = axis[1] * axis[2] * (1 - f_cos) + axis[0] * f_sin;

	// Column 2:
	m_value[0][2] = axis[2] * axis[0] * (1 - f_cos) + axis[1] * f_sin;
	m_value[1][2] = axis[1] * axis[2] * (1 - f_cos) - axis[0] * f_sin;
	m_value[2][2] = z_squared + (1 - z_squared) * f_cos;

	// Column 3:
	m_value[0][3] = 0;
	m_value[1][3] = 0;
	m_value[2][3] = 0;
	return *this;
}

Matrix3x4_t Matrix3x4_t::invert() noexcept {
	Matrix3x4_t out{};
	out[0][0] = m_value[0][0];
	out[0][1] = m_value[1][0];
	out[0][2] = m_value[2][0];

	out[1][0] = m_value[0][1];
	out[1][1] = m_value[1][1];
	out[1][2] = m_value[2][1];

	out[2][0] = m_value[0][2];
	out[2][1] = m_value[1][2];
	out[2][2] = m_value[2][2];

	// now fix up the translation to be in the other space
	Vector_t tmp{};
	tmp[0] = m_value[0][3];
	tmp[1] = m_value[1][3];
	tmp[2] = m_value[2][3];

	out[0][3] = -tmp.Dot(out[0]);
	out[1][3] = -tmp.Dot(out[1]);
	out[2][3] = -tmp.Dot(out[2]);
	return out;
}

Angle_t Matrix3x4_t::ToAngle() const noexcept {
	Angle_t angle = Angle_t();
	const float length = sqrt(m_value[0].x * m_value[0].x + m_value[1].x * m_value[1].x);

	if (length > 0.001f) {
		angle.x = Math::RadToDeg(atan2(-m_value[2][0], length));
		angle.y = Math::RadToDeg(atan2(m_value[1][0], m_value[0][0]));
		angle.z = Math::RadToDeg(atan2(m_value[2][1], m_value[2][2]));
	}
	else {
		angle.x = Math::RadToDeg(atan2(-m_value[2][0], length));
		angle.y = Math::RadToDeg(atan2(-m_value[0][1], m_value[1][1]));
		angle.z = 0.f;
	}

	return angle;
}