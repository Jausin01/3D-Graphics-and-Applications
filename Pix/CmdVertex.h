#pragma once
#include "Command.h"

class CmdVertex : public Command
{
public:
	const char* GetName() override
	{
		return "Vertex";
	}
	const char* GetDescription() override
	{
		// 2D Postion, 3D Position, 2D Position with Color, 3D position with Color
		return "Vertex(x, y)\nVertex(x,y,z)\nVertex(x,y,r,g,b)\nVertex(x,y,z,r,g,b)\n\n- adds vertex to the primitives manager before render";
	}

	bool Execute(const std::vector<std::string>& params) override;
};