#include "Vector3.h"

extern const Vector3 kZeroVector;

inline float dot(const Vector3& a, const Vector3& b)
{
	return a.x * b.x + a.y * b.y + a.z * b.z;
}

inline Vector3 cross(const Vector3& a, const Vector3& b)
{
	Vector3 ret = {
		(a.y * b.z - a.z * b.y),
		-(a.x * b.z - a.z * b.x),
		(a.x * b.y - a.y * b.x)
	};
	return ret;
}

inline float distance(const Vector3& a, const Vector3& b)
{
	float na = a.x - b.x;
	float nb = a.x - b.x;
	float nc = a.x - b.x;
	float ret = sqrtf(na * na + nb * nb + nc * nc);
	return ret;
}

Vector3& Vector3::operator=(Vector3& other)
{
	if (*this == other)
	{
		return *this;
	}

	x = other.x;
	y = other.y;
	z = other.z;
	return *this;
}

// define swizzling.

void Vector3::setToNormalized()
{
	float len = length();
	x /= len;
	y /= len;
	z /= len;
}

Vector3 Vector3::normalize() const
{
	float oneOverLen = 1.0f / length();
	Vector3 ret(
		x * oneOverLen,
		y * oneOverLen,
		z * oneOverLen
	);
	return ret;
}

float Vector3::length() const {
	return sqrtf(x*x + y*y + z*z);
}

bool Vector3::operator==(const Vector3& other) const
{
	return x == other.x && y == other.y && z == other.z;
}

bool Vector3::operator!=(const Vector3& other) const
{
	return x != other.x && y != other.y && z != other.z;
}

Vector3 Vector3::operator*(const float scaler) const
{
	Vector3 ret = {
		x * scaler,
		y * scaler,
		x * scaler
	};
	return ret;
}

Vector3 Vector3::operator/(const float scaler) const
{
	float oneOverScaler = 1.0f / scaler;
	Vector3 ret = {
		x * oneOverScaler,
		y * oneOverScaler,
		z * oneOverScaler
	};
	return ret;
}

Vector3 Vector3::operator+(const Vector3 & other)
{
	Vector3 ret = {
		x + other.x,
		y + other.y,
		z + other.z
	};
	return ret;
}

Vector3 Vector3::operator-(const Vector3 & other)
{
	Vector3 ret = {
		x - other.x,
		y - other.y,
		z - other.z
	};
	return ret;
}

Vector3 Vector3::operator-()
{
	Vector3 ret = {
		-x,
		-y,
		-z
	};
	return ret;
}

Vector3& Vector3::operator+=(const Vector3& other)
{
	x += other.x;
	y += other.y;
	z += other.z;
	return *this;
}

Vector3& Vector3::operator-=(const Vector3& other)
{
	x -= other.x;
	y -= other.y;
	z -= other.z;
	return *this;
}

Vector3& Vector3::operator*=(const Vector3& other)
{
	x *= other.x;
	y *= other.y;
	z *= other.z;
	return *this;
}

Vector3& Vector3::operator/=(const Vector3& other)
{
	x /= other.x;
	y /= other.y;
	z /= other.z;
	return *this;
}

void Vector3::clear()
{
	x = y = z = 0.0f;
}

Vector3 Vector3::projectOnto(Vector3 other) const
{
	float n = powf(other.length(), 2);
	float vdotn = dot(*this, other);
	float product = vdotn / n;
	Vector3 ret = {
		product * x,
		product * y,
		product * z
	};
	return ret;
}