#pragma once
#include "Command.h"


class CmdSetAddressMode : public Command
{
public:
	const char* GetName() override
	{
		return "SetAddressMode";
	}

	const char* GetDescription() override
	{
		return
			"SetAddressMode(Mode)\n\n- Sets the address mode for uv coordinates\n- <border> Sets a color if outisde of 0-1\n<clamp> maintains edge color if outisde of 0-1\n<wrap> repeats uv color if outisde of 0-1<mirror> flip and repeats uv color if outisde of 0-1\n";
	}

	bool Execute(const std::vector<std::string>& params) override;


};