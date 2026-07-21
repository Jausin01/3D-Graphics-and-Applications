#include "Rasterizer.h"

// funtion for drawing a line where the slope is <= 1
// left is the smaller x position, right is highest x position
// this allows us to always index in a positive direction(simple math)
void DrawLineHorizontal(const Vertex& left, const Vertex& right)
{
	float dx = right.pos.x - left.pos.x;
	int startX = static_cast<int>(left.pos.x);
	int endX = static_cast<int>(right.pos.x);
	for (int x = startX; x <= endX; ++x)
	{
		float t = static_cast<float>(x - startX) / dx;
		Vertex v = LerpVertex(left, right, t);
		Rasterizer::Get()->DrawPoint(v);
	}

}

// a function for drawing a line the slope is > 1 (Vertical)
void DrawLineVertical(const Vertex& low, const Vertex& high)
{
	float dY = high.pos.y - low.pos.y;
	int startY = static_cast<int>(low.pos.y);
	int endY = static_cast<int>(high.pos.y);
	for (int y = startY; y <= endY; ++y)
	{
		float t = static_cast<float>(y - startY) / dY;
		Vertex v = LerpVertex(low, high, t);
		Rasterizer::Get()->DrawPoint(v);
	}
}


Rasterizer* Rasterizer::Get()
{
	static Rasterizer sInstance;
	return &sInstance;
}

void Rasterizer::SetColor(X::Color color)
{
	mColor = color;
}

void Rasterizer::SetFillMode(FillMode fillmode)
{
	mFillMode = fillmode;
}

void Rasterizer::DrawPoint(int x, int y)
{
	X::DrawPixel(x, y, mColor);
}

void Rasterizer::DrawPoint(const Vertex& v)
{
	X::DrawPixel(v.pos.x, v.pos.y, v.color);
}

void Rasterizer::DrawLine(const Vertex& a, const Vertex& b)
{
	float dx = b.pos.x - a.pos.x;
	float dy = b.pos.y - a.pos.y;

	if (MathHelper::CheckEqual(dx, 0.0f) || abs(dy / dx) > 1.0f)
	{
		if (a.pos.y < b.pos.y)
		{
			DrawLineVertical(a, b);
		}
		else
		{
			
			DrawLineVertical(b, a);
		}
	}
	else // draw horizontal
	{
		if (a.pos.x < b.pos.x)
		{
			DrawLineHorizontal(a, b);
		}
		else
		{
			DrawLineHorizontal(b, a);
		}
	}
}

void Rasterizer::DrawTriangle(const Vertex& a, const Vertex& b, const Vertex& c)
{
	switch (mFillMode)
	{
	case FillMode::WireFrame:
	{
		DrawLine(a, b);
		DrawLine(b, c);
		DrawLine(c, a);
	}
	break;
	case FillMode::Solid:
	{
		std::vector<Vertex> sortedVertices = { a,b,c };
		std::sort(sortedVertices.begin(), sortedVertices.end(),
		[](const Vertex& lhs, const Vertex& rhs)
		{
			return lhs.pos.y < rhs.pos.y;
		});
		DrawFilledTriangle(sortedVertices[0], sortedVertices[1], sortedVertices[2]);
	}
	break;
	default:
		break;
	}
}

void Rasterizer::DrawFilledTriangle(const Vertex& a, const Vertex& b, const Vertex& c)
{
	// values passed in are already sorted where a is the lowest value (top of the screen)
	// and c is the highest value (bottom of the screen remember positive y goes down)

	float dy = c.pos.y - a.pos.y;
	if (MathHelper::CheckEqual(a.pos.y, b.pos.y))
	{
		int startY = static_cast<int>(a.pos.y);
		int endY = static_cast<int>(c.pos.y);
		for (int y = startY; y <= endY; ++y)
		{
			float t = static_cast<float>(y - startY) / dy;
			Vertex aSide = LerpVertex(a, c,t);
			Vertex bSide = LerpVertex(b, c, t);;
			DrawLine(aSide, bSide);
		}
	}
	else if (MathHelper::CheckEqual(b.pos.y, c.pos.y))
	{
		int startY = static_cast<int>(a.pos.y);
		int endY = static_cast<int>(c.pos.y);
		for (int y = startY; y <= endY; ++y)
		{
			float t = static_cast<float>(y - startY) / dy;
			Vertex bSide = LerpVertex(a, b, t);
			Vertex cSide = LerpVertex(a, c, t);;
			DrawLine(bSide, cSide);
		}
	}
	else // no edges, need a split vertex
	{
		float t = (b.pos.y - a.pos.y) / dy; 
		Vertex splitVertex = LerpVertex(a, c, t);
		DrawFilledTriangle(a, b, splitVertex);
		DrawFilledTriangle(b, splitVertex, c);
	}
}
