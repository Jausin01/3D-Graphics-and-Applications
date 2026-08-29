#pragma once
#include "Command.h"

class CmdSetShadeMode : public Command
{
public:

	const char* GetName() override
	{
		return "SetShadeMode";
	}

	const char* GetDescription() override
	{
		return
			"SetShadeMode(<shadeMode)\n\n- Sets the lighting shade mode\n - flat : Per face lighting\n - gouraud: Per vertex lighting\n - phong: per pixel lighting\n";
	}

	bool Execute(const std::vector<std::string>& params) override;
};