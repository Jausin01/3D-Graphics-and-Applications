#pragma once

struct Vector3
{
	float x;
	float y;
	float z;

	Vector3() : x(0.0f), y(0.0f), z(0.f){}
	Vector3(float a) : x(a), y(a), z(a) {}
	Vector3(float a, float b, float c) : x(a), y(b), z(c) {}
	Vector3(const Vector3& v) : x(v.x), y(v.y), z(v.z) {}


	// common operators
	Vector3 operator-() const { return { -x, -y, -z }; }
	Vector3 operator+(const Vector3& rhs) const { return{ x + rhs.x, y + rhs.y, z + rhs.z }; }
	Vector3 operator-(const Vector3& rhs) const { return { x - rhs.x, y - rhs.y, z - rhs.z }; }
	Vector3 operator*(float a) const { return { x * a, y * a, z * a }; }
	Vector3 operator/(float a) const { return { x / a, y / a, z / a }; }
		  
	//comm3n inline operators
	Vector3& operator+=(const Vector3 rhs) { x += rhs.x; y += rhs.y; z += rhs.z; return *this; }
	Vector3& operator-=(const Vector3 rhs) { x -= rhs.x; y -= rhs.y; z -= rhs.z ; return *this; }
	Vector3& operator*=(float a) { x *= a; y *= a; z *= a; return *this; }
	Vector3& operator/=(float a) { x /= a; y /= a; z /= a; return *this; }
};