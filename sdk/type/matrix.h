#pragma once

#include "vector.h"
#include "angle.h"

#include <array>

struct Matrix3x4_t {
	Matrix3x4_t() = default;
	Matrix3x4_t( float m00, float m01, float m02, float m03, float m10, float m11, float m12, float m13, float m20, float m21, float m22, float m23 ) noexcept;
	Matrix3x4_t( const Vector_t& x_axis, const Vector_t& y_axis, const Vector_t& z_axis, const Vector_t& localPos ) noexcept;

	Vector_t GetColumn( int column ) const noexcept;
	void set_column( const Vector_t& value, int column ) noexcept;
	void add_to_column( const Vector_t& value, int column ) noexcept;

	Matrix3x4_t operator+( const Matrix3x4_t& value ) const noexcept;
	Matrix3x4_t operator*( const Matrix3x4_t& value ) const noexcept;
	Matrix3x4_t operator*( float value ) const noexcept;
	Vector_t operator*( const Vector_t& value ) const noexcept;

	Matrix3x4_t& build_rotation_about_axis( const Vector_t& axis, float degrees ) noexcept;
	Matrix3x4_t invert() noexcept;
	Angle_t ToAngle() const noexcept;

	Vector4_t& operator[]( int i ) noexcept { return m_value.at( i ); }
	const Vector4_t& operator[]( int i ) const noexcept { return m_value.at( i ); }

	std::array<Vector4_t, 3u> m_value = {};
};

struct __declspec(align(16)) Matrix3x4a_t : Matrix3x4_t {};

struct Matrix4x4 {
	Matrix4x4() = default;
	std::array<Vector4_t, 4u> data = {};
};

struct VMatrix : Matrix4x4 {
	VMatrix() = default;

	Vector4_t operator[]( const int index ) noexcept {
		return data[index];
	}

	const Vector4_t operator[]( const int index ) const noexcept {
		return data[index];
	}

	[[nodiscard]] Vector4_t at( const int index ) const noexcept {
		return Vector4_t( data[0][index], data[1][index], data[2][index], data[3][index] );
	}

	VMatrix& operator+=( const VMatrix& other ) noexcept {
		for (int i = 0; i < 4; i++)
			for (int n = 0; n < 4; n++)
				this->data[i][n] += other[i][n];
		return *this;
	}

	VMatrix& operator-=( const VMatrix& other ) noexcept {
		for (int i = 0; i < 4; i++)
			for (int n = 0; n < 4; n++)
				this->data[i][n] -= other[i][n];
		return *this;
	}

	void Identity() {
		for (int i = 0; i < 4; i++)
			for (int n = 0; n < 4; n++)
				data[i][n] = i == n ? 1.0f : 0.0f;
	}

	void Transpose() {
		for (int i = 0; i < 4; i++)
			for (int j = 0; j < 4; j++) data[i][j] = data[j][i];
	}
};
