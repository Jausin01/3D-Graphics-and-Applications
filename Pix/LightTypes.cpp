#include "LightTypes.h"
#include "MaterialManager.h"
#include "Camera.h"


X::Color DirectionalLight::ComputeLightColor(const Vector3& pos, const Vector3& normal)
{
	Camera* cam = Camera::Get();
	MaterialManager* matM = MaterialManager::Get();

	// Calculate ambient Color
	X::Color ambient = mAmbient * matM->GetMaterialAmbient();

	// calculate diffuse color
	Vector3 L = -mDirection;
	float dot = X::Math::Max(MathHelper::Dot(L, normal),0.0f);
	X::Color diffuse = mDiffuse * matM->GetMaterialDiffuse() * dot;

	// calculate specular color
	Vector3 v = MathHelper::Normalize(cam->GetPosition() - pos);
	Vector3 r = MathHelper::Normalize(L + v);
	float fallOff = X::Math::Max((float)pow(MathHelper::Dot(r, normal), matM->GetMaterialShininess()), 0.0f);
	X::Color specular = mSpecular * matM->GetMaterialSpecular() * fallOff;

	// final color
	return ambient + diffuse + specular;
}

void DirectionalLight::SetDirection(const Vector3& dir)
{
	mDirection = MathHelper::Normalize(dir);
}

X::Color PointLight::ComputeLightColor(const Vector3& pos, const Vector3& normal)
{
	Camera* cam = Camera::Get();
	MaterialManager* matM = MaterialManager::Get();

	// get distance from light
	Vector3 L = mPos - pos;
	float distance = MathHelper::Magnitude(L);
	L /= distance;

	// calculate iL, light Intensity
	float attenuation = 1.0f / (mKConst + (mKLinear * distance) + (mKQuadratic * distance * distance));
	float iL = X::Math::Clamp(attenuation, 0.0f, 1.0f);

	// Calculate ambient Color
	X::Color ambient = mAmbient * matM->GetMaterialAmbient();

	// calculate diffuse color
	float dot = X::Math::Max(MathHelper::Dot(L, normal), 0.0f);
	X::Color diffuse = mDiffuse * matM->GetMaterialDiffuse() * dot * iL;

	// calculate specular color
	Vector3 v = MathHelper::Normalize(cam->GetPosition() - pos);
	Vector3 r = MathHelper::Normalize(L + v);
	float fallOff = X::Math::Max((float)pow(MathHelper::Dot(r, normal), matM->GetMaterialShininess()), 0.0f);
	X::Color specular = mSpecular * matM->GetMaterialSpecular() * fallOff * iL;

	// final color
	return ambient + diffuse + specular;
}

void PointLight::SetPosition(const Vector3& Pos)
{
	mPos = Pos;
}

void PointLight::SetAttenuation(float kConst, float kLinear, float kQuadratic)
{
	mKConst = kConst;
	mKLinear = kLinear;
	mKQuadratic = kQuadratic;

}

X::Color SpotLight::ComputeLightColor(const Vector3& pos, const Vector3& normal)
{
	Camera* cam = Camera::Get();
	MaterialManager* matM = MaterialManager::Get();

	// get distance from light
	Vector3 L = mPos - pos;
	float distance = MathHelper::Magnitude(L);
	L /= distance;

	// Calculate ambient Color
	X::Color ambient = mAmbient * matM->GetMaterialAmbient();

	// check to see if pos is in the cone
	Vector3 lightDir = -L; // light Direction to the point
	float dotDir = MathHelper::Dot(lightDir, mDirection);
	if (dotDir < mCosCangle)
	{
		return ambient;
	}

	// calculate iL, light Intensity
	float spot = pow(dotDir, mDecay);
	float attenuation = spot / (mKConst + (mKLinear * distance) + (mKQuadratic * distance * distance));
	float iL = X::Math::Clamp(attenuation, 0.0f, 1.0f);
	
	// calculate diffuse color
	float dot = X::Math::Max(MathHelper::Dot(L, normal), 0.0f);
	X::Color diffuse = mDiffuse * matM->GetMaterialDiffuse() * dot * iL;

	// calculate specular color
	Vector3 v = MathHelper::Normalize(cam->GetPosition() - pos);
	Vector3 r = MathHelper::Normalize(L + v);
	float fallOff = X::Math::Max((float)pow(MathHelper::Dot(r, normal), matM->GetMaterialShininess()), 0.0f);
	X::Color specular = mSpecular * matM->GetMaterialSpecular() * fallOff * iL;

	// final color
	return ambient + diffuse + specular;
}

void SpotLight::SetPosition(const Vector3& Pos)
{
	mPos = Pos;
}

void SpotLight::SetAttenuation(float kConst, float kLinear, float kQuadratic)
{
	mKConst = kConst;
	mKLinear = kLinear;
	mKQuadratic = kQuadratic;

}

void SpotLight::SetDirection(const Vector3& dir)
{
	mDirection = MathHelper::Normalize(dir);
}

void SpotLight::SetAngle(float angle)
{
	mCosCangle = cos(angle);
}

void SpotLight::SetDecay(float decay)
{
	mDecay = decay;
}
