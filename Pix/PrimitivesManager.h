#pragma once
#include "Vertex.h"

// purpose of the primitives manager is to store all of the verticies
// render all of the shapes based on topology
// clip/cull all the non visible faces

enum class Topology
{
	Point,
	Line,
	Triangle
};

class PrimitivesManager
{
public:
	static PrimitivesManager* Get();

	// Start Accepting Vertices
	bool BeginDraw(Topology topology);
	// add verticies to the manager
	void AddVertex(const Vertex& v);
	//Send all stored Vertices to render as specified
	void EndDraw();

private:
	PrimitivesManager();

	std::vector<Vertex> mVertexBuffer;
	Topology mTopology = Topology::Point;
	bool mDrawBegin = false;


};