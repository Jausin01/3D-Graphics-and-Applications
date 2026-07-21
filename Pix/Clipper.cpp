#include "Clipper.h"
#include "Viewport.h"

const short BIT_INSIDE       = 0; // 0000
const short BIT_LEFT = 1    << 0; // 0001
const short BIT_RIGHT = 1   << 1; // 0010
const short BIT_BOTTOM = 1  << 2; // 0100
const short BIT_TOP = 1		<< 3; // 1000

// generate a bit code that signifies where the point is
// if code is not 0, it is outside of the screen in one of the 8 regions
// compare code with other point's code to confirm if the line crosses screen.
short GetOutputCode(float x, float y)
{
	Viewport* vp = Viewport::Get();
	short code = BIT_INSIDE;
	if (x < vp->GetMinX())
	{
		code |= BIT_LEFT;
	}
	else if (x > vp->GetMaxX())
	{
		code |= BIT_RIGHT;
	}

	if (y < vp->GetMinY())
	{
		code |= BIT_TOP;
	}
	else if (y > vp->GetMaxY())
	{
		code |= BIT_BOTTOM;
	}
	return code;
}

Clipper* Clipper::Get()
{
	static Clipper sIntance;
	return &sIntance;
}

Clipper::Clipper()
{

}

void Clipper::OnNewFrame()
{
	mIsClipping = false;
}

bool Clipper::ClipPoint(const Vertex& v)
{
	if (!mIsClipping)
	{
		return false;
	}

	Viewport* vp = Viewport::Get();
	float minX = vp->GetMinX();
	float minY = vp->GetMinY();
	float maxX = vp->GetMaxX();
	float maxY = vp->GetMaxY();

	return v.pos.x < minX || v.pos.x > maxX || v.pos.y < minY || v.pos.y > maxY;
}

bool Clipper::ClipLine(Vertex& a, Vertex& b)
{
	if (!mIsClipping)
	{
		return false;
	}

	Viewport* vp = Viewport::Get();
	float minX = vp->GetMinX();
	float minY = vp->GetMinY();
	float maxX = vp->GetMaxX();
	float maxY = vp->GetMaxY();

	short codeA = GetOutputCode(a.pos.x, a.pos.y);
	short codeB = GetOutputCode(b.pos.x, b.pos.y);
	while (true)
	{
		if (!(codeA | codeB))
		{
			// both are 0000, so both are in the viewport
			break;
		}
		else if (codeA & codeB)
		{
			// both are along the same edge, so they will never cross the viewport
			break;
		}

		float t = 0.0f;
		// pick a code that isnt 0000
		// if the value is > then that is not 0000
		short outCode = codeB > codeA ? codeB : codeA;
		if (outCode & BIT_TOP) { t = { (minY - a.pos.y) / (b.pos.y - a.pos.y) }; }
		else if (outCode & BIT_BOTTOM) { t = { (maxY - a.pos.y) / (b.pos.y - a.pos.y) }; }
		else if (outCode & BIT_LEFT) { t = { (minX - a.pos.x) / (b.pos.x - a.pos.x) }; }
		else if (outCode & BIT_RIGHT) { t = { (maxX - a.pos.x) / (b.pos.x - a.pos.x) }; }

		if (outCode == codeA)
		{
			a = LerpVertex(a, b, t);
			codeA = GetOutputCode(a.pos.x, a.pos.y);
		}
		else
		{
			b = LerpVertex(a, b, t);
			codeB = GetOutputCode(b.pos.x, b.pos.y);
		}


	}

	return (codeA | codeB);

}

enum ClipEdge
{
	CE_LEFT,
	CE_TOP,
	CE_RIGHT,
	CE_BOTTOM,
	CE_COUNT // we can use this to iterate the enum
};

bool IsInFront(ClipEdge edge, const Vector3& pos)
{
	Viewport* vp = Viewport::Get();
	switch (edge)
	{
	case CE_LEFT: return pos.x > vp->GetMinX();
	case CE_TOP: return pos.y > vp->GetMinY();
	case CE_RIGHT: return pos.x < vp->GetMaxX();
	case CE_BOTTOM: return pos.y < vp->GetMaxY();
	default:
		break;
	}

	return false;
}

Vertex ComputeIntersection(ClipEdge edge, const Vertex& a, const Vertex& b)
{
	Viewport* vp = Viewport::Get();
	float t = 0.0f;
	switch (edge)
	{
	case CE_LEFT: t = (vp->GetMinX() - a.pos.x) / (b.pos.x - a.pos.x); break;
	case CE_TOP: t = (vp->GetMinY() - a.pos.y) / (b.pos.y - a.pos.y); break;
	case CE_RIGHT: t = (vp->GetMaxX() - a.pos.x) / (b.pos.x - a.pos.x); break;
	case CE_BOTTOM:t = (vp->GetMaxY() - a.pos.y) / (b.pos.y - a.pos.y); break;
	default:
		break;
	}

	return LerpVertex(a, b, t);

}


bool Clipper::ClipTriangle(std::vector<Vertex>& v)
{
	if (!mIsClipping)
	{
		return false;
	}

	// Store New Vertices while we step through the edges
	std::vector<Vertex> newVertices;
	for (int i = 0; i < CE_COUNT; ++i)
	{
		newVertices.clear();
		ClipEdge edge = (ClipEdge)i;
		for (size_t n = 0; n < v.size(); ++n)
		{
			size_t nPO = (n + 1) % v.size();
			const Vertex& vN = v[n];

			const Vertex& vNPO = v[nPO];

			bool nIsInFront = IsInFront(edge, vN.pos);
			bool nPOIsInFront = IsInFront(edge, vNPO.pos);

			if (nIsInFront && nPOIsInFront)
			{
				// both are in front
				newVertices.push_back(vNPO);
			}
			else if (!nIsInFront && !nPOIsInFront)
			{
				// dont save anything
			}
			else if (nIsInFront && !nPOIsInFront)
			{
				// n is in front, npo behind
				newVertices.push_back(ComputeIntersection(edge, vN, vNPO));
			}
			else if (!nIsInFront && nPOIsInFront)
			{
				// npo is in front, npo behind.
				newVertices.push_back(ComputeIntersection(edge, vN, vNPO));
				newVertices.push_back(vNPO);
			}

		}
		v = newVertices;
	}

	return newVertices.empty();
}

bool Clipper::IsClipping() const
{
	return mIsClipping;
}

void Clipper::SetClipping(bool enable)
{
	mIsClipping = enable;
}
