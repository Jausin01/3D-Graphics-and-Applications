#pragma once
#include "Command.h"

class CmdSetCorrectUV : public Command
{
public:
	const char* GetName() override
	{
		return "SetCorrectUV";
	}

	const char* GetDescription() override
	{
		return
			"SetCorrectUV(correctUV)\n\n- Enables/disables uv correction when using texture";
	}

	bool Execute(const std::vector<std::string>& params) override;

private:

};