#pragma once

#include "MathHelper.h"
#include <cmath>

bool CheckEqual(float a, float b)
{
	return abs(a - b) < 0.001f;
}

float MagnitudeSqr(const Vector2& v)
{
	return v.x * v.x + v.y * v.y;
}

float MagnitudeSqr(const Vector3& v)
{
	return v.x * v.x + v.y * v.y + v.z * v.z;
}

float Magnitude(const Vector2& v)
{
	return sqrt(MagnitudeSqr(v));
}

float Magnitude(const Vector3& v)
{
	return sqrt(MagnitudeSqr(v));
}

Vector2 Normalize(const Vector2& v)
{
	return v / Magnitude(v);
}

Vector3 Normalize(const Vector3& v)
{
	return v / Magnitude(v);
}

float Dot(const Vector2& a, const Vector2& b)
{
	return a.x * b.x + a.y * b.y;
}

float Dot(const Vector3& a, const Vector3& b)
{
	return a.x * b.x + a.y * b.y + a.z * b.z;
}

Vector3 Cross(const Vector3& a, const Vector3& b)
{
	return
	{
		a.y * b.z - a.z * b.y,
		a.z * b.x - a.x * b.z,
		a.x * b.y - a.y * b.x
	};
}