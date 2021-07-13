#include "Vector3.h"

extern const Vector3 kZeroVector;

Vector3& Vector3::operator=(Vector3& other)
{
	if (*this == other)
	{
		return *this;
	}

	data = other.data;
	return *this;
}

float Vector3::x() const { return data[0]; }
float Vector3::y() const { return data[1]; }
float Vector3::z() const { return data[2]; }
// define different ordering for swizzling.
// float xxy() { std::array<float, 3> ret = { data[0], data[0], data[1] }; return ret; }

void Vector3::setToNormalized()
{
	float len = length();
	data[0] /= len;
	data[1] /= len;
	data[2] /= len;
}

Vector3 Vector3::normalize() const
{
	float oneOverLen = 1.0f / length();
	Vector3 ret(
		data[0] * oneOverLen,
		data[1] * oneOverLen,
		data[2] * oneOverLen
	);
	return ret;
}

float Vector3::length() const {
	return sqrtf(powf(data[0], 2) + powf(data[1], 2) + powf(data[2], 2));
}

bool Vector3::operator==(const Vector3& other) const
{
	return data == other.data;
}

bool Vector3::operator!=(const Vector3& other) const
{
	return data != other.data;
}

int Vector3::operator<=>(const Vector3& other) const
{
	if (data > other.data) return 1;
	else if (data == other.data) return 0;
	else return -1;
}

Vector3 Vector3::operator*(const float scaler) const
{
	Vector3 ret = {
		data[0] * scaler,
		data[1] * scaler,
		data[2] * scaler
	};
	return ret;
}

Vector3 Vector3::operator/(const float scaler) const
{
	float oneOverScaler = 1.0f / scaler;
	Vector3 ret = {
		data[0] * oneOverScaler,
		data[1] * oneOverScaler,
		data[2] * oneOverScaler
	};
	return ret;
}

Vector3 Vector3::operator+(const Vector3 & other)
{
	Vector3 ret = {
		data[0] + other.data[0],
		data[1] + other.data[1],
		data[2] + other.data[2]
	};
	return ret;
}

Vector3 Vector3::operator-(const Vector3 & other)
{
	Vector3 ret = {
		data[0] - other.data[0],
		data[1] - other.data[1],
		data[2] - other.data[2]
	};
	return ret;
}

Vector3 Vector3::operator-()
{
	Vector3 ret = {
		-data[0],
		-data[1],
		-data[2]
	};
	return ret;
}

Vector3& Vector3::operator+=(const Vector3& other)
{
	data[0] += other.data[0];
	data[1] += other.data[1];
	data[2] += other.data[2];
	return *this;
}

Vector3& Vector3::operator-=(const Vector3& other)
{
	data[0] -= other.data[0];
	data[1] -= other.data[1];
	data[2] -= other.data[2];
	return *this;
}

Vector3& Vector3::operator*=(const Vector3& other)
{
	data[0] *= other.data[0];
	data[1] *= other.data[1];
	data[2] *= other.data[2];
	return *this;
}

Vector3& Vector3::operator/=(const Vector3& other)
{
	data[0] /= other.data[0];
	data[1] /= other.data[1];
	data[2] /= other.data[2];
	return *this;
}

void Vector3::clear()
{
	data[0] = data[1] = data[2] = 0.0f;
}

Vector3 Vector3::projectOnto(Vector3 other) const
{
	float n = powf(other.length(), 2);
	float vdotn = dot(*this, other);
	float product = vdotn / n;
	Vector3 ret = {
		product * data[0],
		product * data[1],
		product * data[2]
	};
	return ret;
}


inline float dot(const Vector3& a, const Vector3& b)
{
	return a.data[0] * b.data[0] + a.data[1] * b.data[1] + a.data[2] * b.data[2];
}

inline Vector3 cross(const Vector3& a, const Vector3& b)
{
	Vector3 ret = {
		(a.data[1] * b.data[2] - a.data[2] * b.data[1]),
		-(a.data[0] * b.data[2] - a.data[2] * b.data[0]),
		(a.data[0] * b.data[1] - a.data[1] * b.data[0])
	};
	return ret;
}

inline float distance(const Vector3& a, const Vector3& b)
{
	float na = a.data[0] - b.data[0];
	float nb = a.data[0] - b.data[0];
	float nc = a.data[0] - b.data[0];
	float ret = sqrtf(na*na + nb*nb + nc*nc);
	return ret;
}