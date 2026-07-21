#pragma once
#include "Command.h"

class CmdSetFillMode : public Command
{
public:
	const char* GetName() override
	{
		return "SetFillMode";
	}
	const char* GetDescription() override
	{
		return "SetFillMode(fillmode)\n\n - Sets triangle fill mode (Wireframe or Solid)";
	}

	bool Execute(const std::vector<std::string>& params) override;
};