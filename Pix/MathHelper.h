#pragma once

#include "Vector2.h"
#include "Vector3.h"
#include "Matrix4.h"
#include "Ray.h"
#include "Sphere.h"

namespace MathHelper
{
	constexpr float DegToRad = 3.1415926f / 180.0f;
	
	bool CheckEqual(float a, float b);
	void FlattenVectorScreenCoord(Vector3& v);

	float MagnitudeSqr(const Vector2& v);
	float MagnitudeSqr(const Vector3& v);

	float Magnitude(const Vector2& v);
	float Magnitude(const Vector3& v);

	Vector2 Normalize(const Vector2& v);
	Vector3 Normalize(const Vector3& v);

	float Dot(const Vector2& a, const Vector2& b);
	float Dot(const Vector3& a, const Vector3& b);

	Vector3 Cross(const Vector3& a, const Vector3& b);

	// Matrix Functions
	Vector3 TransformCoord(const Vector3& v, const Matrix4& m); // Translates vector position and rotation
	Vector3 TransformNormal(const Vector3& v, const Matrix4& m); // translates vector only by rotation

	
	Matrix4 Transpose(const Matrix4& m); // Swap the handiness of the matrix (left hand to right hand)
	Matrix4 Inverse(const Matrix4& m); // get the inverse matrix
	
	Matrix4 Adjoint(const Matrix4& m);
	float Determinant(const Matrix4& m);

	bool Intersect(const Ray& ray, const Sphere& sphere, float& distance);

}