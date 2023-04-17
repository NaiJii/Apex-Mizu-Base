#pragma once

struct Vector4_t;
struct Angle_t;
struct Matrix3x4_t;
struct Matrix4x4;
struct Vector2_t;

struct Vector_t {
	Vector_t() = default;
	Vector_t(float _x, float _y, float _z) noexcept;
	Vector_t(Vector2_t other);

	float Length() const noexcept;
	float Length2D() const noexcept;
	float LengthSqr() const noexcept;
	float LengthSqr2D() const noexcept;

	bool IsZero() const noexcept;
	float Dot(const Vector_t other) const noexcept;
	Vector_t Cross(const Vector_t other) const noexcept;
	float DistanceTo(const Vector_t other) const noexcept;
	float Distance2DTo(const Vector_t other) const noexcept;

	Vector_t operator+(const float other) const noexcept;
	Vector_t operator-(const float other) const noexcept;
	Vector_t operator*(const float other) const noexcept;
	Vector_t operator/(const float other) const noexcept;
	Vector_t operator+(const Vector_t other) const noexcept;
	Vector_t operator-(const Vector_t other) const noexcept;
	Vector_t operator+=(const float other) noexcept;
	Vector_t operator-=(const float other) noexcept;
	Vector_t operator*=(const float other) noexcept;
	Vector_t operator/=(const float other) noexcept;
	Vector_t operator+=(const Vector_t other) noexcept;
	Vector_t operator-=(const Vector_t other) noexcept;
	bool operator==(const Vector_t& other) const noexcept;
	bool operator!=(const Vector_t& other) const noexcept;
	float& operator[](int i) noexcept;
	const float operator[](int i) const noexcept;

	Vector_t Mins(const Vector_t& other) const noexcept;
	Vector_t Maxs(const Vector_t& other) const noexcept;
	Vector_t Rotate(const Angle_t& angle) const noexcept;
	Vector_t Rotate(const Vector_t& center, const Angle_t& angle) const noexcept;
	Vector_t Rotate(const Vector4_t& q) const;
	/* doesn't motify 'this' */
	Vector_t Normalize() const noexcept;
	float normalize_in_place() noexcept;
	/* motify 'this' */
	Vector_t Normalized() noexcept;
	Angle_t ToAngle() const noexcept;
	Vector_t Transform(const Matrix3x4_t& other) const noexcept;
	Vector_t Transform(const Matrix4x4& other) const noexcept;

	float x = 0.f, y = 0.f, z = 0.f;
};

struct Vector2_t {
	Vector2_t() = default;
	Vector2_t(float _x, float _y) noexcept;

	Vector2_t operator+(const float other) const noexcept;
	Vector2_t operator-(const float other) const noexcept;
	Vector2_t operator*(const float other) const noexcept;
	Vector2_t operator/(const float other) const noexcept;
	Vector2_t operator+(const Vector2_t other) const noexcept;
	Vector2_t operator-(const Vector2_t other) const noexcept;
	Vector2_t operator+=(const float other) noexcept;
	Vector2_t operator-=(const float other) noexcept;
	Vector2_t operator*=(const float other) noexcept;
	Vector2_t operator/=(const float other) noexcept;
	Vector2_t operator+=(const Vector2_t other) noexcept;
	Vector2_t operator-=(const Vector2_t other) noexcept;
	bool operator==(const Vector2_t& other) const noexcept;
	float& operator[](int i) noexcept;
	const float operator[](int i) const noexcept;

	float Length() const noexcept;
	float Length2D() const noexcept;
	float Normalize_() noexcept;
	Vector2_t Normalize() noexcept;
	float Dot(const Vector2_t other) const noexcept;

	float x, y;
};

struct Vector4_t : Vector_t {
	Vector4_t() = default;

	Vector4_t(Vector_t vec, float _w) {
		x = vec.x;
		y = vec.y;
		z = vec.z;
		w = _w;
	}

	Vector4_t(float _x, float _y, float _z, float _w) {
		x = _x;
		y = _y;
		z = _z;
		w = _w;
	}

	Vector4_t(const Vector_t& value) {
		x = value.x;
		y = value.y;
		z = value.z;
		w = 0.f;
	}

	Vector4_t& operator=(const Vector_t& value) {
		x = value.x;
		y = value.y;
		z = value.z;
		w = 0.f;

		return *this;
	}

	Vector4_t& operator=(const Vector4_t& value) {
		x = value.x;
		y = value.y;
		z = value.z;
		w = value.w;

		return *this;
	}

	float Dot(const Vector_t other) const noexcept;
	float Dot(const Vector4_t other) const noexcept;
	// Euler
	Angle_t ToAngle() const;

	float w = 0.f;
};

struct __declspec(align(16)) Vector4a : Vector_t {
	Vector4a() = default;

	Vector4a(float _x, float _y, float _z, float _w) {
		x = _x;
		y = _y;
		z = _z;
		w = _w;
	}

	Vector4a(const Vector_t& value) {
		x = value.x;
		y = value.y;
		z = value.z;
		w = 0.f;
	}

	Vector4a& operator=(const Vector_t& value) {
		x = value.x;
		y = value.y;
		z = value.z;
		w = 0.f;

		return *this;
	}

	Vector4a& operator=(const Vector4a& value) {
		x = value.x;
		y = value.y;
		z = value.z;
		w = value.w;

		return *this;
	}

	float w = 0.f;
};

struct Point_t {
	Point_t() = default;
	Point_t(int _x, int _y) noexcept;

	Point_t operator+(const int other) const noexcept;
	Point_t operator-(const int other) const noexcept;
	Point_t operator*(const int other) const noexcept;
	Point_t operator*(const float other) const noexcept;
	Point_t operator/(const int other) const noexcept;
	Point_t operator/(const float other) const noexcept;
	Point_t operator+(const Point_t other) const noexcept;
	Point_t operator-(const Point_t other) const noexcept;
	Point_t operator+=(const int other) noexcept;
	Point_t operator-=(const int other) noexcept;
	Point_t operator*=(const int other) noexcept;
	Point_t operator*=(const float other) noexcept;
	Point_t operator/=(const int other) noexcept;
	Point_t operator/=(const float other) noexcept;
	Point_t operator+=(const Point_t other) noexcept;
	Point_t operator-=(const Point_t other) noexcept;
	bool operator==(const Point_t& other) const noexcept;
	int& operator[](int i) noexcept;
	const int operator[](int i) const noexcept;
	float DistanceTo(const Point_t& other) const;
	float DistanceToSquared(const Point_t& other) const;
	Angle_t ToAngle() const;

	int x, y;
};
