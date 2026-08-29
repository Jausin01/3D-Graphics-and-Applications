#pragma once
#include "Light.h"

class DirectionalLight : public Light
{
public:
	X::Color ComputeLightColor(const Vector3& pos, const Vector3& normal) override;

	void SetDirection(const Vector3& dir);

private:
	Vector3 mDirection = { 0.0f,0.0f,1.0f };
};

class PointLight : public Light
{
public:
	X::Color ComputeLightColor(const Vector3& pos, const Vector3& normal) override;

	void SetPosition(const Vector3& Pos);
	void SetAttenuation(float kConst, float kLinear, float kQuadratic);
private:
	Vector3 mPos = { 0.0f,0.0f,0.0f };
	float mKConst = 1.0f;
	float mKLinear = 0.0f;
	float mKQuadratic = 0.0f;
};

class SpotLight : public Light
{
public:
	X::Color ComputeLightColor(const Vector3& pos, const Vector3& normal) override;

	void SetPosition(const Vector3& Pos);
	void SetDirection(const Vector3& Pos);
	void SetAttenuation(float kConst, float kLinear, float kQuadratic);
	void SetAngle(float angle);
	void SetDecay(float decay);
private:
	Vector3 mPos = { 0.0f,0.0f,0.0f };
	Vector3 mDirection = { 0.0f,0.0f,1.0f };
	float mKConst = 1.0f;
	float mKLinear = 0.0f;
	float mKQuadratic = 0.0f;
	float mCosCangle = cos(X::Math::kPiByTwo);
	float mDecay = 0.0f;
};