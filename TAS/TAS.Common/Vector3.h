#pragma once
#include <array>

class Vector3
{
public:
	float x, y, z; // crack this open into x, y, z

	Vector3()
	{
		x = y = z = 0.0f;
	}

	Vector3(float x, float y, float z) : x(x), y(y), z(z) {	}

	Vector3(const Vector3& other)
	{
		x = other.x;
		y = other.y;
		z = other.z;
	}

	Vector3& operator=(Vector3& other);

	// define swizzling.

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

