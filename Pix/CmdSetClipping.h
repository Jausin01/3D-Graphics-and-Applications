#pragma once
#include "Command.h"

class CmdSetClipping : public Command
{
public:

	const char* GetName() override
	{
		return "SetClipping";
	}

	const char* GetDescription() override
	{
		return "SetClipping(enable)\n\n - Enables/Disables clipping outside of viewport";
	}

	bool Execute(const std::vector<std::string>& params) override;

};