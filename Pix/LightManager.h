#pragma once
#include <XEngine.h>
#include "Light.h"

class LightManager
{
public:
	static LightManager* Get();

	void OnNewFrame();

	void SetLightSpecular(const X::Color& color);
	void SetLightAmbient(const X::Color& color);
	void SetLightDiffuse(const X::Color& color);

	// directional Light
	void AddDirectionalLight(const Vector3& direction);

	// point light
	void AddPointLight(const Vector3& pos, float kConst, float kLiner, float kQuadratic);
	// spot light
	void AddSpotLight(const Vector3& pos, const Vector3& direction, float kConst, float kLiner, float kQuadratic, float angle, float decay);

	X::Color ComputeLightColor(const Vector3& pos, const Vector3& normal);

private:
	std::vector<std::unique_ptr<Light>> mLights;
	X::Color mAmbient = X::Colors::White;
	X::Color mDiffuse = X::Colors::White;
	X::Color mSpecular = X::Colors::White;


};