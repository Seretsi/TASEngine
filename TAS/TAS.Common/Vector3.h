#pragma once
#include <array>

class Vector3
{
public:
	std::array<float, 3> data;

	Vector3()
	{
		data = { 0.0f , 0.0f, 0.0f };
	}

	Vector3(float x, float y, float z) {
		data = { x , y, z };
	}

	Vector3(const Vector3& other)
	{
		data = other.data;
	}

	Vector3& operator=(Vector3& other);

	int operator<=>(const Vector3& other) const;

	float x() const;
	float y() const;
	float z() const;
	// define different ordering for swizzling.
	// float xxy() { std::array<float, 3> ret = { data[0], data[0], data[1] }; return ret; }

	void setToNormalized();

	Vector3 normalize() const;

	float length() const;

	bool operator==(const Vector3& other) const;

	bool operator!=(const Vector3& other) const;

	Vector3 operator*(const float scaler) const;

	Vector3 operator/(const float scaler) const;

	Vector3 operator+(const Vector3& other);

	Vector3 operator-(const Vector3& other);

	Vector3 operator-();

	Vector3& operator+=(const Vector3& other);

	Vector3& operator-=(const Vector3& other);

	Vector3& operator*=(const Vector3& other);

	Vector3& operator/=(const Vector3& other);

	void clear();

	Vector3 projectOnto(Vector3 other) const;
};

