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

enum class CullMode
{
	None, // No Culling Used
	Back, // cull anything facing away from the camera
	Front, // Cull Anything Facing the Camera

};

class PrimitivesManager
{
public:
	static PrimitivesManager* Get();

	void OnNewFrame();
	void SetCullMode(CullMode mode);

	// Start Accepting Vertices
	bool BeginDraw(Topology topology, bool applyTransform);
	// add verticies to the manager
	void AddVertex(const Vertex& v);
	//Send all stored Vertices to render as specified
	void EndDraw();

private:
	PrimitivesManager();

	std::vector<Vertex> mVertexBuffer;
	Topology mTopology = Topology::Point;
	bool mDrawBegin = false;
	CullMode mCullMode = CullMode::None;
	bool mApplyTransform = false;


};