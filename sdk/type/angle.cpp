#include "angle.h"
#include "vector.h"
#include "matrix.h"

import math;
#include <algorithm>
#include <cmath>

Angle_t::Angle_t(float _x, float _y, float _z) noexcept {
	x = _x;
	y = _y;
	z = _z;
}

Angle_t Angle_t::operator+(const float other) const noexcept {
	return Angle_t(x + other, y + other, z + other);
}

Angle_t Angle_t::operator-(const float other) const noexcept {
	return Angle_t(x - other, y - other, z - other);
}

Angle_t Angle_t::operator*(const float other) const noexcept {
	return Angle_t(x * other, y * other, z * other);
}

Angle_t Angle_t::operator/(const float other) const noexcept {
	return Angle_t(x / other, y / other, z / other);
}

Angle_t Angle_t::operator+(const Angle_t other) const noexcept {
	return Angle_t(x + other.x, y + other.y, z + other.z);
}

Angle_t Angle_t::operator-(const Angle_t other) const noexcept {
	return Angle_t(x - other.x, y - other.y, z - other.z);
}

Angle_t Angle_t::operator+=(const float other) noexcept {
	x += other;
	y += other;
	z += other;
	return *this;
}

Angle_t Angle_t::operator-=(const float other) noexcept {
	x -= other;
	y -= other;
	z -= other;
	return *this;
}

Angle_t Angle_t::operator*=(const float other) noexcept {
	x *= other;
	y *= other;
	z *= other;
	return *this;
}

Angle_t Angle_t::operator/=(const float other) noexcept {
	x /= other;
	y /= other;
	z /= other;
	return *this;
}

Angle_t Angle_t::operator+=(const Angle_t other) noexcept {
	x += other.x;
	y += other.y;
	z += other.z;
	return *this;
}

Angle_t Angle_t::operator-=(const Angle_t other) noexcept {
	x -= other.x;
	y -= other.y;
	z -= other.z;
	return *this;
}

bool Angle_t::operator==(const Angle_t& other) const noexcept
{
	return x == other.x && y == other.y;
}

bool Angle_t::IsZero() const noexcept {
	return x == 0.f && y == 0.f && z == 0.f;
}

Angle_t Angle_t::Normalize() noexcept {
	x = std::isfinite(x) ? std::remainder(x, 360.f) : 0.f;
	y = std::isfinite(y) ? std::remainder(y, 360.f) : 0.f;
	z = 0.f;
	return *this;
}

Angle_t Angle_t::Clamp() noexcept {
	x = std::clamp(x, -89.f, 89.f);
	y = std::clamp(y, -180.f, 180.f);
	z = 0.f;
	return *this;
}

float Angle_t::Length() const noexcept
{
	return sqrt(x * x + y * y + z * z);
}

Vector_t Angle_t::ToVector(Vector_t* right, Vector_t* up) const noexcept {
	const float
		sp = sin(Math::DegToRad(x)),
		cp = cos(Math::DegToRad(x)),
		sy = sin(Math::DegToRad(y)),
		cy = cos(Math::DegToRad(y)),
		sr = sin(Math::DegToRad(z)),
		cr = cos(Math::DegToRad(z));

	Vector_t temp{};
	temp.x = cp * cy;
	temp.y = cp * sy;
	temp.z = -sp;

	if (right) {
		right->x = -sr * sp * cy + cr * sy;
		right->y = -sr * sp * sy - cr * cy;
		right->z = -sr * cp;
	}

	if (up) {
		up->x = cr * sp * cy + -sr * -sy;
		up->y = cr * sp * sy + -sr * cy;
		up->z = cr * cp;
	}

	return temp;
}

Matrix3x4_t Angle_t::ToMatrix() noexcept {
	Matrix3x4_t out{};

	const float
		sp = sin(Math::DegToRad(x)),
		cp = cos(Math::DegToRad(x)),
		sy = sin(Math::DegToRad(y)),
		cy = cos(Math::DegToRad(y)),
		sr = sin(Math::DegToRad(z)),
		cr = cos(Math::DegToRad(z)),
		crcy = cr * cy,
		crsy = cr * sy,
		srcy = sr * cy,
		srsy = sr * sy;

	out[0][0] = cp * cy;
	out[1][0] = cp * sy;
	out[2][0] = -sp;

	out[0][1] = sp * srcy - crsy;
	out[1][1] = sp * srsy + crcy;
	out[2][1] = sr * cp;

	out[0][2] = (sp * crcy + srsy);
	out[1][2] = (sp * crsy - srcy);
	out[2][2] = cr * cp;

	out[0][3] = out[1][3] = out[2][3] = 0.f;

	return out;
}

Matrix3x4_t Angle_t::ToMatrix() const noexcept {
	Matrix3x4_t out{};

	const float
		sp = sin(Math::DegToRad(x)),
		cp = cos(Math::DegToRad(x)),
		sy = sin(Math::DegToRad(y)),
		cy = cos(Math::DegToRad(y)),
		sr = sin(Math::DegToRad(z)),
		cr = cos(Math::DegToRad(z)),
		crcy = cr * cy,
		crsy = cr * sy,
		srcy = sr * cy,
		srsy = sr * sy;

	out[0][0] = cp * cy;
	out[1][0] = cp * sy;
	out[2][0] = -sp;

	out[0][1] = sp * srcy - crsy;
	out[1][1] = sp * srsy + crcy;
	out[2][1] = sr * cp;

	out[0][2] = (sp * crcy + srsy);
	out[1][2] = (sp * crsy - srcy);
	out[2][2] = cr * cp;

	out[0][3] = out[1][3] = out[2][3] = 0.f;

	return out;
}

Matrix3x4_t Angle_t::ToMatrix(const Vector_t& position) noexcept {
	Matrix3x4_t out = ToMatrix();
	out.set_column(position, 3);
	return out;
}

Matrix3x4_t Angle_t::ToMatrix(const Vector_t& position) const noexcept {
	Matrix3x4_t out = ToMatrix();
	out.set_column(position, 3);
	return out;
}

Matrix3x4a_t Angle_t::ToAlignedMatrix() noexcept {
	Matrix3x4a_t out{};

	const float
		sp = sin(Math::DegToRad(x)),
		cp = cos(Math::DegToRad(x)),
		sy = sin(Math::DegToRad(y)),
		cy = cos(Math::DegToRad(y)),
		sr = sin(Math::DegToRad(z)),
		cr = cos(Math::DegToRad(z)),
		crcy = cr * cy,
		crsy = cr * sy,
		srcy = sr * cy,
		srsy = sr * sy;

	out[0][0] = cp * cy;
	out[1][0] = cp * sy;
	out[2][0] = -sp;

	out[0][1] = sp * srcy - crsy;
	out[1][1] = sp * srsy + crcy;
	out[2][1] = sr * cp;

	out[0][2] = (sp * crcy + srsy);
	out[1][2] = (sp * crsy - srcy);
	out[2][2] = cr * cp;

	out[0][3] = out[1][3] = out[2][3] = 0.f;

	return out;
}

Matrix3x4a_t Angle_t::ToAlignedMatrix(const Vector_t& position) noexcept {
	Matrix3x4a_t out = ToAlignedMatrix();
	out.set_column(position, 3);
	return out;
}

Vector4_t Angle_t::ToQuaternion() const {
	Vector4_t out{};

	const double cr = cos(Math::DegToRad(x) * 0.5);
	const double sr = sin(Math::DegToRad(x) * 0.5);
	const double cy = cos(Math::DegToRad(y) * 0.5);
	const double sy = sin(Math::DegToRad(y) * 0.5);
	const double cp = cos(Math::DegToRad(z) * 0.5);
	const double sp = sin(Math::DegToRad(z) * 0.5);

	out.x = static_cast<float>(cy * sr * cp - sy * cr * sp);
	out.y = static_cast<float>(cy * cr * sp + sy * sr * cp);
	out.z = static_cast<float>(sy * cr * cp - cy * sr * sp);
	out.w = static_cast<float>(cy * cr * cp + sy * sr * sp);

	return out;
}