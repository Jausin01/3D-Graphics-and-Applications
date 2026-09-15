#include "RayTracer.h"
#include "Camera.h"
#include <math.h>

extern float gResolutionX;
extern float gResolutionY;

namespace
{
	void Fresnel(const Vector3& i, const Vector3& n, float ri, float& kr, float& kt)
	{
		float cosi = X::Math::Clamp(MathHelper::Dot(i, n), -1.0f, 1.0f);
		float etai = 1.0f;
		float etat = ri;
		if (cosi > 0.0f)
		{
			std::swap(etai, etat);
		}
		float sint = etai / etat * sqrt(std::max(0.0f, 1.0f - cosi * cosi));

		kr = 1.0f;
		if (sint < 1.0f)
		{
			float cost = sqrt(std::max(0.0f, 1.0f - sint * sint));
			cosi = fabs(cosi);
			float Rs = ((etat * cosi) - (etai * cost)) / ((etat * cosi) + (etai * cost));
			float Rp = ((etai * cosi) - (etai * cost)) / ((etai * cosi) + (etat * cost));
			kr = (Rs * Rs + Rp * Rp) / 2.0f;
		}
		kt = 1.0f - kr;
	}
}

RayTracer* RayTracer::Get()
{
	static RayTracer sInstance;
	return &sInstance;
}

void RayTracer::OnNewFrame()
{
	mObject.clear();
	mLights.clear();
}

bool RayTracer::BeginDraw()
{
	return true;
}


void RayTracer::AddObject(const Sphere& sphere, const X::Color& color, float r)
{
	mObject.push_back({ sphere,color,r });
}

void RayTracer::AddLight(const Vector3& pos, const X::Color& color)
{
	mLights.push_back({ pos, color });
}

bool RayTracer::EndDraw()
{
	Camera* camera = Camera::Get();
	int columns = static_cast<int>(gResolutionX);
	int rows = static_cast<int>(gResolutionY);

	Matrix4 matView = camera->GetViewMatrix();
	Vector3 camPos = camera->GetPosition();
	float aspect = gResolutionX / gResolutionY;

	Vector3 screenCenter = camPos + camera->GetDirection();
	Vector3 xAxis = { matView._11, matView._21, matView._31 };
	Vector3 yAxis = { matView._12, matView._22, matView._32 };

	Vector3 p0 = screenCenter - (xAxis * aspect) + yAxis;
	Vector3 p1 = screenCenter + (xAxis * aspect) + yAxis;
	Vector3 p2 = screenCenter - (xAxis * aspect) - yAxis;

	for (int y = 0; y < rows; ++y)
	{
		for (int x = 0; x < columns; ++x)
		{
			float u = (float)x / columns;
			float v = (float)y / rows;
		
			Vector3 pointOnScreen = p0 + (p1 - p0) * u + (p2 - p0) * v;
			Ray primaryRay;
			primaryRay.origin = camPos;
			primaryRay.direction = MathHelper::Normalize(pointOnScreen - camPos);
			X::DrawPixel(x, y, Trace(primaryRay, 3));
		}
	}
	return true;

}

X::Color RayTracer::Trace(const Ray& ray, int depth)
{
	if (depth <= 0)
	{
		return X::Colors::Black;
	}

	Object* objHit = nullptr;
	float closestDist = FLT_MAX;
	X::Color closestColor;

	Vector3 closestPoint;
	Vector3 closestNorm;

	for (Object& obj : mObject)
	{
		float distanceToSphere = 0.0f;
		if (MathHelper::Intersect(ray, obj.sphere, distanceToSphere))
		{
			if (distanceToSphere >= 0.0f && distanceToSphere < closestDist)
			{
				objHit = &obj;
				closestDist = distanceToSphere;
				closestPoint = ray.origin + (ray.direction * distanceToSphere);
				closestNorm = MathHelper::Normalize(closestPoint - obj.sphere.origin);
				closestColor = obj.color;
			}
		}
	}
	if (objHit == nullptr)
	{
		return X::Colors::Black;
	}

	X::Color color;
	if (objHit->IsOpaque())
	{
		for (Light& light : mLights)
		{
			float distanceToLight = MathHelper::Magnitude(light.position - closestPoint);
			Vector3 dirToLight = (light.position - closestPoint) / distanceToLight;

			bool ocluded = false;
			for (Object& obj : mObject)
			{
				Ray shadowRay;
				shadowRay.origin = closestPoint + (closestNorm * 0.001f);
				shadowRay.direction = dirToLight;
				float distanceToObj = 0.0f;
				if (MathHelper::Intersect(shadowRay, obj.sphere, distanceToObj))
				{
					if (distanceToObj > 0.0f && distanceToObj + 0.1f < distanceToLight)
					{
						ocluded = true;
						break;
					}
				}
			}

			float intensity = mAmbient;
			if (!ocluded)
			{
				float diffuse = MathHelper::Dot(dirToLight, closestNorm);
				if (diffuse > 0.0f)
				{
					float atten = 1.0 / (light.attenC + (light.attenL * distanceToLight) + (light.attenQ * distanceToLight * distanceToLight));
					intensity = X::Math::Clamp(intensity + (diffuse * atten), 0.0f, 1.0f);
				}
			}
			color += light.color * closestColor * intensity;
		}
	}
	else
	{
		bool inside = false;
		if (MathHelper::Dot(ray.direction, closestNorm) > 0.0f)
		{
			inside = true;
			closestNorm = -closestNorm;
		}

		Ray reflectRay;
		reflectRay.origin = closestPoint + (closestNorm * 0.001f);
		reflectRay.direction = ray.direction - (closestNorm * 2 * MathHelper::Dot(ray.direction, closestNorm));
		reflectRay.direction = MathHelper::Normalize(reflectRay.direction);
		X::Color reflectColor = Trace(reflectRay, depth - 1);

		float eta = inside ? objHit->refractionIndex : 1.0f / objHit->refractionIndex;
		float cosi = -MathHelper::Dot(ray.direction, closestNorm);
		float k = 1.0f - eta * eta * (1.0f - (cosi * cosi));

		Ray refractRay;
		refractRay.origin = closestPoint - (closestNorm * 0.001f);
		refractRay.direction = ray.direction * eta + closestNorm * (eta * cosi - sqrt(k));
		refractRay.direction = MathHelper::Normalize(refractRay.direction);
		X::Color refractColor = Trace(refractRay, depth - 1);

		float kr, kt;
		Fresnel(ray.direction, closestNorm, objHit->refractionIndex, kr, kt);
		color = closestColor * (reflectColor * kr + refractColor * kt);
	}

	color.r = X::Math::Clamp(color.r, 0.0f, 1.0f);
	color.g = X::Math::Clamp(color.g, 0.0f, 1.0f);
	color.b = X::Math::Clamp(color.b, 0.0f, 1.0f);
	color.a = 1.0f;
	return color;
}
