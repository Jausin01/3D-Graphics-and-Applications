#pragma once
#include "Command.h"

class CmdSetViewport : public Command
{
public:

	const char* GetName() override
	{
		return "SetViewport";
	}

	const char* GetDescription() override
	{
		return "SetViewport(x,y,width,height, <show>\n\n- Creates a viewport rect with x, t, width, and height";
	}

	bool Execute(const std::vector<std::string>& params) override;

};