#pragma once

struct Vector_t;
struct Vector4_t;
struct Matrix3x4_t;
struct Matrix3x4a_t;
struct Point_t;

struct Angle_t {
	Angle_t() = default;
	Angle_t(float x, float y, float z) noexcept;

	Angle_t operator+(const float other) const noexcept;
	Angle_t operator-(const float other) const noexcept;
	Angle_t operator*(const float other) const noexcept;
	Angle_t operator/(const float other) const noexcept;
	Angle_t operator+(const Angle_t other) const noexcept;
	Angle_t operator-(const Angle_t other) const noexcept;
	Angle_t operator+=(const float other) noexcept;
	Angle_t operator-=(const float other) noexcept;
	Angle_t operator*=(const float other) noexcept;
	Angle_t operator/=(const float other) noexcept;
	Angle_t operator+=(const Angle_t other) noexcept;
	Angle_t operator-=(const Angle_t other) noexcept;

	bool operator==(const Angle_t& other) const noexcept;

	bool IsZero() const noexcept;

	Angle_t Normalize() noexcept;
	Angle_t Clamp() noexcept;
	// SHOULD ONLY BE USED ON DELTAs.
	float Length() const noexcept;
	Vector_t ToVector(Vector_t* right = nullptr, Vector_t* up = nullptr) const noexcept;
	Matrix3x4_t ToMatrix() noexcept;
	Matrix3x4_t ToMatrix() const noexcept;
	Matrix3x4_t ToMatrix(const Vector_t& position) noexcept;
	Matrix3x4_t ToMatrix(const Vector_t& position) const noexcept;
	Matrix3x4a_t ToAlignedMatrix() noexcept;
	Matrix3x4a_t ToAlignedMatrix(const Vector_t& position) noexcept;
	// not supposed to be a vec4 but a quat, whatever idc
	Vector4_t ToQuaternion() const;

	float x, y, z;
};
