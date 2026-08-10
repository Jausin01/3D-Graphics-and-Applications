#pragma once
#include "Command.h"

class CmdBeginDraw : public Command
{
public:
	const char* GetName() override
	{
		return "BeginDraw";
	}
	const char* GetDescription() override
	{
		return "BegindDraw(Topology, <applyTransform>)\n\n- Starts storing Vertices\n- topology (point, line, triangle)\n- (optional) apply transform to apply 3D pipeline transformation to vertices";
	}
	
	bool Execute(const std::vector<std::string>& params) override;

};