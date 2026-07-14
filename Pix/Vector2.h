#pragma once

struct Vector2
{
	float x;
	float y;

	Vector2() : x(0.0f), y(0.0f) {}
	Vector2(float a) : x(a), y(0.0f) {}
	Vector2(float a, float b) : x(a), y(b) {}
	Vector2(const Vector2& v) : x(v.x), y(v.y) {}


	// common operators
	Vector2 operator-() const { return { -x, -y }; }
	Vector2 operator+(const Vector2& rhs) const { return{ x + rhs.x, y + rhs.y }; }
	Vector2 operator-(const Vector2& rhs) const { return { x - rhs.x, y - rhs.y }; }
	Vector2 operator*( float a) const { return { x * a, y * a }; }
	Vector2 operator/(float a) const { return { x / a, y / a }; }

	//common inline operators
	Vector2& operator+=(const Vector2 rhs) { x += rhs.x; y += rhs.y; return *this; }
	Vector2& operator-=(const Vector2 rhs) { x -= rhs.x; y -= rhs.y; return *this; }
	Vector2& operator*=(float a) { x *= a; y *= a; return *this; }
	Vector2& operator/=(float a) { x /= a; y /= a; return *this; }
};