#include "vector.h"
#include "angle.h"
#include "matrix.h"

import math;
#include <algorithm>
#include <cmath>

#include <cmath>
#include <corecrt_math_defines.h>

Vector_t::Vector_t(float _x, float _y, float _z) noexcept {
	x = _x;
	y = _y;
	z = _z;
}

Vector_t::Vector_t(Vector2_t other)
{
	x = other.x;
	y = other.y;
	z = 0.f;
}

float Vector_t::Length() const noexcept {
	return sqrt(x * x + y * y + z * z);
}

float Vector_t::Length2D() const noexcept {
	return sqrt(x * x + y * y);
}

float Vector_t::LengthSqr() const noexcept {
	return x * x + y * y + z * z;
}

float Vector_t::LengthSqr2D() const noexcept {
	return x * x + y * y;
}

bool Vector_t::IsZero() const noexcept {
	return x == 0.f && y == 0.f && z == 0.f;
}

float Vector_t::Dot(const Vector_t other) const noexcept {
	return (x * other.x + y * other.y + z * other.z);
}

Vector_t Vector_t::Cross(const Vector_t other) const noexcept {
	Vector_t cross_product{};
	cross_product.x = y * other.z - z * other.y;
	cross_product.y = z * other.x - x * other.z;
	cross_product.z = x * other.y - y * other.x;
	return cross_product;
}

float Vector_t::DistanceTo(const Vector_t other) const noexcept {
	return (*this - other).Length();
}

float Vector_t::Distance2DTo(const Vector_t other) const noexcept {
	return (*this - other).Length2D();
}

Vector_t Vector_t::operator+(const float other) const noexcept {
	return Vector_t(x + other, y + other, z + other);
}

Vector_t Vector_t::operator-(const float other) const noexcept {
	return Vector_t(x - other, y - other, z - other);
}

Vector_t Vector_t::operator*(const float other) const noexcept {
	return Vector_t(x * other, y * other, z * other);
}

Vector_t Vector_t::operator/(const float other) const noexcept {
	return Vector_t(x / other, y / other, z / other);
}

Vector_t Vector_t::operator+(const Vector_t other) const noexcept {
	return Vector_t(x + other.x, y + other.y, z + other.z);
}

Vector_t Vector_t::operator-(const Vector_t other) const noexcept {
	return Vector_t(x - other.x, y - other.y, z - other.z);
}

Vector_t Vector_t::operator+=(const float other) noexcept {
	x += other;
	y += other;
	z += other;
	return *this;
}

Vector_t Vector_t::operator-=(const float other) noexcept {
	x -= other;
	y -= other;
	z -= other;
	return *this;
}

Vector_t Vector_t::operator*=(const float other) noexcept {
	x *= other;
	y *= other;
	z *= other;
	return *this;
}

Vector_t Vector_t::operator/=(const float other) noexcept {
	x /= other;
	y /= other;
	z /= other;
	return *this;
}

Vector_t Vector_t::operator+=(const Vector_t other) noexcept {
	x += other.x;
	y += other.y;
	z += other.z;
	return *this;
}

Vector_t Vector_t::operator-=(const Vector_t other) noexcept {
	x -= other.x;
	y -= other.y;
	z -= other.z;
	return *this;
}

bool Vector_t::operator==(const Vector_t& other) const noexcept {
	return x == other.x && y == other.y && z == other.z;
}

bool Vector_t::operator!=(const Vector_t& other) const noexcept {
	return x != other.x || y != other.y || z != other.z;
}

float& Vector_t::operator[](int i) noexcept {
	return ((float*)this)[i];
}

const float Vector_t::operator[](int i) const noexcept {
	return ((const float*)this)[i];
}

Vector_t Vector_t::Mins(const Vector_t& other) const noexcept {
	return Vector_t(std::min(x, other.x), std::min(y, other.y), std::min(z, other.z));
}

Vector_t Vector_t::Maxs(const Vector_t& other) const noexcept {
	return Vector_t(std::max(x, other.x), std::max(y, other.y), std::max(z, other.z));
}

Vector_t Vector_t::Rotate(const Angle_t& angle) const noexcept {
	Vector_t out{};
	Matrix3x4_t rotate = angle.ToMatrix();
	out.x = Dot(rotate[0]);
	out.y = Dot(rotate[1]);
	out.z = Dot(rotate[2]);
	return out;
}

Vector_t Vector_t::Rotate(const Vector_t& center, const Angle_t& angle) const noexcept {
	Vector_t out{};
	Matrix3x4_t rotate = angle.ToMatrix();
	const Vector_t localPos = *this - center;
	out.x = localPos.Dot(rotate[0]);
	out.y = localPos.Dot(rotate[1]);
	out.z = localPos.Dot(rotate[2]);
	out += center;
	return out;
}

Vector_t Vector_t::Rotate(const Vector4_t& q) const {
	// Extract the vector part of the quaternion
	const Vector_t u(q.x, q.y, q.z);

	// Extract the scalar part of the quaternion
	const float s = q.w;

	// Do the math
	return u * 2.0f * Dot(u) + *this * (s * s - u.Dot(u)) + u.Cross(*this) * 2.0f * s;
}

float Vector_t::normalize_in_place() noexcept {
	// thank you qo0
	const float length = this->Length(), radius = 1.0f / (length + std::numeric_limits<float>::epsilon());

	this->x *= radius;
	this->y *= radius;
	this->z *= radius;

	return length;
}

Vector_t Vector_t::Normalize() const noexcept {
	Vector_t tmp = *this;
	if (const float l = Length(); l)
		tmp /= l;
	else
		tmp.x = tmp.y = tmp.z = 0.f;
	return tmp;
}

Vector_t Vector_t::Normalized() noexcept {
	if (const float l = Length(); l)
		*this /= l;
	else
		x = y = z = 0.f;
	return *this;
}

Angle_t Vector_t::ToAngle() const noexcept {
	Angle_t result{};
	if (x == 0.f && y == 0.f) {
		result.x = z > 0.f ? 270.f : 90.f;
		result.y = 0.f;
	}
	else {
		result.x = std::atan2f(-z, Length2D()) * 180.f / static_cast<float>(M_PI);

		if (result.x < 0.f)
			result.x += 360.f;

		result.y = std::atan2f(y, x) * 180.f / static_cast<float>(M_PI);

		if (result.y < 0.f)
			result.y += 360.f;
	}
	result.z = 0.f;
	return result;
}

Vector_t Vector_t::Transform(const Matrix3x4_t& other) const noexcept {
	return Vector_t(Dot(other[0]) + other[0].w, Dot(other[1]) + other[1].w, Dot(other[2]) + other[2].w);
}

Vector_t Vector_t::Transform(const Matrix4x4& other) const noexcept {
	return Vector_t(Dot(other.data[0]) + other.data[0].w, Dot(other.data[1]) + other.data[1].w, Dot(other.data[2]) + other.data[2].w);
}

Vector2_t::Vector2_t(float _x, float _y) noexcept {
	x = _x;
	y = _y;
}

float Vector2_t::Length() const noexcept {
	return sqrt(x * x + y * y);
}

Vector2_t Vector2_t::operator+(const float other) const noexcept {
	return Vector2_t(x + other, y + other);
}

Vector2_t Vector2_t::operator-(const float other) const noexcept {
	return Vector2_t(x - other, y - other);
}

Vector2_t Vector2_t::operator*(const float other) const noexcept {
	return Vector2_t(x * other, y * other);
}

Vector2_t Vector2_t::operator/(const float other) const noexcept {
	return Vector2_t(x / other, y / other);
}

Vector2_t Vector2_t::operator+(const Vector2_t other) const noexcept {
	return Vector2_t(x + other.x, y + other.y);
}

Vector2_t Vector2_t::operator-(const Vector2_t other) const noexcept {
	return Vector2_t(x - other.x, y - other.y);
}

Vector2_t Vector2_t::operator+=(const float other) noexcept {
	x += other;
	y += other;
	return *this;
}

Vector2_t Vector2_t::operator-=(const float other) noexcept {
	x -= other;
	y -= other;
	return *this;
}

Vector2_t Vector2_t::operator*=(const float other) noexcept {
	x *= other;
	y *= other;
	return *this;
}

Vector2_t Vector2_t::operator/=(const float other) noexcept {
	x /= other;
	y /= other;
	return *this;
}

Vector2_t Vector2_t::operator+=(const Vector2_t other) noexcept {
	x += other.x;
	y += other.y;
	return *this;
}

Vector2_t Vector2_t::operator-=(const Vector2_t other) noexcept {
	x -= other.x;
	y -= other.y;
	return *this;
}

bool Vector2_t::operator==(const Vector2_t& other) const noexcept {
	return x == other.x && y == other.y;
}

float& Vector2_t::operator[](int i) noexcept {
	return ((float*)this)[i];
}

const float Vector2_t::operator[](int i) const noexcept {
	return reinterpret_cast<const float*>(this)[i];
}

float Vector2_t::Length2D() const noexcept {
	return sqrtf(x * x + y * y);
}

float Vector2_t::Normalize_() noexcept {
	float mag = Length2D();

	if (mag != 0.f) {
		x /= mag;
		y /= mag;
	}

	return mag;
}

Vector2_t Vector2_t::Normalize() noexcept {
	float mag = Length2D();
	if (mag != 0.f) {
		x /= mag;
		y /= mag;
	}
	return *this;
}

float Vector2_t::Dot(const Vector2_t other) const noexcept
{
	return x * other.x + y * other.y;
}

Angle_t Vector4_t::ToAngle() const {
	Angle_t out{};

	const float sinr = static_cast<float>(+2.0 * (w * x + y * z));
	const float cosr = static_cast<float>(+1.0 - 2.0 * (x * x + y * y));
	out.x = atan2(sinr, cosr);

	const double sinp = +2.0 * (w * y - z * x);
	if (abs(sinp) >= 1.)
		out.z = static_cast<float>(copysign(M_PI / 2, sinp));
	else
		out.z = static_cast<float>(asin(sinp));

	const double siny = +2.0 * (w * z + x * y);
	const double cosy = +1.0 - 2.0 * (y * y + z * z);

	out.y = static_cast<float>(atan2(siny, cosy));

	out.x = Math::RadToDeg(out.x);
	out.y = Math::RadToDeg(out.y);
	out.z = Math::RadToDeg(out.z);

	return out;
}

Point_t::Point_t(int _x, int _y) noexcept {
	x = _x;
	y = _y;
}

Point_t Point_t::operator+(const int other) const noexcept {
	return Point_t(x + other, y + other);
}

Point_t Point_t::operator-(const int other) const noexcept {
	return Point_t(x - other, y - other);
}

Point_t Point_t::operator*(const int other) const noexcept {
	return Point_t(x * other, y * other);
}

Point_t Point_t::operator*(const float other) const noexcept
{
	return Point_t((int)(x * other), (int)(y * other));
}

Point_t Point_t::operator/(const int other) const noexcept {
	if (other == 0)
		return Point_t();

	return Point_t(x / other, y / other);
}

Point_t Point_t::operator/(const float other) const noexcept
{
	if (other == 0.f)
		return Point_t();

	return Point_t((int)(x / other), (int)(y / other));
}

Point_t Point_t::operator+(const Point_t other) const noexcept {
	return Point_t(x + other.x, y + other.y);
}

Point_t Point_t::operator-(const Point_t other) const noexcept {
	return Point_t(x - other.x, y - other.y);
}

Point_t Point_t::operator+=(const int other) noexcept {
	x += other;
	y += other;
	return *this;
}

Point_t Point_t::operator-=(const int other) noexcept {
	x -= other;
	y -= other;
	return *this;
}

Point_t Point_t::operator*=(const int other) noexcept {
	x *= other;
	y *= other;
	return *this;
}

Point_t Point_t::operator*=(const float other) noexcept
{
	x = (int)(x * other);
	y = (int)(y * other);
	return *this;
}

Point_t Point_t::operator/=(const int other) noexcept {
	if (other == 0)
		return Point_t();

	x /= other;
	y /= other;
	return *this;
}

Point_t Point_t::operator/=(const float other) noexcept
{
	if (other == 0.f)
		return Point_t();

	x = (int)(x / other);
	y = (int)(y / other);
	return *this;
}

Point_t Point_t::operator+=(const Point_t other) noexcept {
	x += other.x;
	y += other.y;
	return *this;
}

Point_t Point_t::operator-=(const Point_t other) noexcept {
	x -= other.x;
	y -= other.y;
	return *this;
}

bool Point_t::operator==(const Point_t& other) const noexcept {
	return x == other.x && y == other.y;
}

int& Point_t::operator[](int i) noexcept {
	return ((int*)this)[i];
}

const int Point_t::operator[](int i) const noexcept {
	return reinterpret_cast<const int*>(this)[i];
}

float Point_t::DistanceTo(const Point_t& other) const {
	return sqrtf(powf((float)(x - other.x), 2.f) + powf((float)(y - other.y), 2.f));
}

float Point_t::DistanceToSquared(const Point_t& other) const {
	return powf((float)(x - other.x), 2.f) + powf((float)(y - other.y), 2.f);
}

Angle_t Point_t::ToAngle() const
{
	static float m_pitch = 0.022f;
	static float m_yaw = 0.022f;
	return Angle_t(y * m_pitch, -x * m_yaw, 0.f);
}

float Vector4_t::Dot(const Vector_t other) const noexcept {
	return (x * other.x + y * other.y + z * other.z);
}

float Vector4_t::Dot(const Vector4_t other) const noexcept {
	return (x * other.x + y * other.y + z * other.z + w * other.w);
}