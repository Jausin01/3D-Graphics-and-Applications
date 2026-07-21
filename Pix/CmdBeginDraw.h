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
		return "BegindDraw(Topology)\n\n- Starts storing Vertices\n- topology (point, line, triangle)";
	}
	
	bool Execute(const std::vector<std::string>& params) override;

};