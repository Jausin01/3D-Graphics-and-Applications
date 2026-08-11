#include "PrimitivesManager.h"
#include "Rasterizer.h"
#include "Clipper.h"
#include "MatrixStack.h"
#include "Camera.h"

extern float gResolutionX;
extern float gResolutionY;

namespace
{
	Matrix4 GetScreenTransform()
	{
		const float hw = gResolutionX * 0.5f;
		const float hh = gResolutionY * 0.5f;
		return
		{
			  hw, 0.0f, 0.0f, 0.0f,
			0.0f,  -hh, 0.0f, 0.0f,
			0.0f, 0.0f, 1.0f, 0.0f,
			  hw,   hh, 0.0f, 1.0f
		};

	}

	Vector3 CreateFaceNormal(const std::vector<Vertex>& triangle)
	{
		// take b-a cross c-a
		const Vector3& a = triangle[0].pos;
		const Vector3& b = triangle[1].pos;
		const Vector3& c = triangle[2].pos;
		Vector3 norm = MathHelper::Normalize(MathHelper::Cross((b-a),(c-a)));
		return norm;
	}

	bool CullTriangle(CullMode mode, const std::vector<Vertex>& triangle)
	{
		if (mode == CullMode::None)
		{
			return false;
		}
		Vector3 faceNormal = CreateFaceNormal(triangle);
		if (mode == CullMode::Back)
		{
			return faceNormal.z > 0.0f;
		}
		if (mode == CullMode::Front)
		{
			return faceNormal.z < 0.0f;
		}

		return false;
	}

}

PrimitivesManager::PrimitivesManager()
{

}

void PrimitivesManager::OnNewFrame()
{
	mCullMode = CullMode::None;

}

void PrimitivesManager::SetCullMode(CullMode mode)
{
	mCullMode = mode;
}


bool PrimitivesManager::BeginDraw(Topology topology, bool applyTransform)
{
	mVertexBuffer.clear();
	mTopology = topology;
	mDrawBegin = true;
	mApplyTransform = applyTransform;
	return true;
}

void PrimitivesManager::AddVertex(const Vertex& v)
{
	if (mDrawBegin)
	{
		mVertexBuffer.push_back(v);
	}
}

void PrimitivesManager::EndDraw()
{
	if (!mDrawBegin)
	{
		return;
	}

	// apply transformation pipeline
	//matLocal -> MatWorld -> MatView -> matProj -> MatScreen
	Matrix4 matWorld = MatrixStack::Get()->GetTransform();
	// view matrix from the camera
	Matrix4 matView = Camera::Get()->GetViewMatrix();
	// projection matrix from the camera
	Matrix4 matProj = Camera::Get()->GetProjectionMatrix();
	// screen space matrix from the screen
	Matrix4 matScreen = GetScreenTransform();
	// full transformation pipeline
	//Matrix4 matFinal = matWorld * matView * matProj * matScreen;
	// transformation pipeline only to NDC Space
	Matrix4 matNDCSpace = matWorld * matView * matProj;

	switch (mTopology)
	{
	case Topology::Point:
	{
		for (uint32_t i = 0; i < mVertexBuffer.size(); i++)
		{
			if (!Clipper::Get()->ClipPoint(mVertexBuffer[i]))
			{
				Rasterizer::Get()->DrawPoint(mVertexBuffer[i]);
			}			
		}

	}
	break;
	case Topology::Line:
	{
		for (uint32_t i = 1; i < mVertexBuffer.size(); i+= 2)
		{
			if (!Clipper::Get()->ClipLine(mVertexBuffer[i - 1], mVertexBuffer[i]))
			{
				Rasterizer::Get()->DrawLine(mVertexBuffer[i - 1], mVertexBuffer[i]);
			}
		}
	}
	break;
	case Topology::Triangle:
	{
		for (uint32_t i = 2; i < mVertexBuffer.size(); i += 3)
		{
			std::vector<Vertex> triangle =
			{
				mVertexBuffer[i - 2],
				mVertexBuffer[i - 1],
				mVertexBuffer[i],

			};
			if (mApplyTransform)
			{
				// transform to NDC Space, then check Facing to see if you can draw, then draw.
				// use 3 points of triangle to make a normal direction 
				// // check the nromal if it should be culled, proceed or cancel
				for (size_t t = 0; t < triangle.size(); ++t)
				{
					// transform all position to NDC
					triangle[t].pos = MathHelper::TransformCoord(triangle[t].pos, matNDCSpace);

				}

				// triangle in NDC space, if cull mode says to cull, contininue, otherwise render.
				if (CullTriangle(mCullMode, triangle))
				{
					continue;
				}
					

				// transofmratiion pipeline (matfinal, transforms from local to screen space)
				for (size_t t = 0; t < triangle.size(); ++t)
				{
					// uf akready in ndc space, transform again just with the remaining matrices (matScreen)
					triangle[t].pos = MathHelper::TransformCoord(triangle[t].pos, matScreen);
					// after converting to screen space, make sure x and y are whole numers
					MathHelper::FlattenVectorScreenCoord(triangle[t].pos);
				}
			}
			if (!Clipper::Get()->ClipTriangle(triangle))
			{
				for (size_t t = 2; t < triangle.size(); ++t)
				{
					Rasterizer::Get()->DrawTriangle(triangle[0], triangle[t - 1], triangle[t]);
				}
			}
		}
	}
	break;
	default:
		break;
	}
}

PrimitivesManager* PrimitivesManager::Get()
{
	static PrimitivesManager sInstance;
	return &sInstance;
}


