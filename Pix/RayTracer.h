#pragma once
#include "MathHelper.h"
#include <XEngine.h>

class RayTracer
{
public:
	static RayTracer* Get();
	void OnNewFrame();
	bool BeginDraw();
	void AddObject(const Sphere& sphere, const X::Color& color, float r);
	void AddLight(const Vector3& pos, const X::Color& color);
	bool EndDraw();


private:
	X::Color Trace(const Ray& ray, int depth);

	struct Object
	{
		Sphere sphere;
		X::Color color;
		float refractionIndex = 0.0f;
		bool IsOpaque() const
		{
			return MathHelper::CheckEqual(refractionIndex, 0.0f);
		}
	};

	struct Light
	{
		Vector3 position;
		X::Color color;
		float attenC = 1.0f;
		float attenL = 0.0f;
		float attenQ = 0.0f;
	};
	std::vector<Object> mObject;
	std::vector<Light> mLights;
	float mAmbient = 0.0f;
};