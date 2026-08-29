#pragma once
#include "Command.h"
#include "TextureManager.h"


class CmdSetTexture : public Command
{
public:

	const char* GetName() override
	{
		return "SetTexture";
	}

	const char* GetDescription() override
	{
		return
			"SetTexture(fileName)\n\n- Sets the texture to use when uv is coordinable";
	}

	bool Execute(const std::vector<std::string>& params) override;



private:

};