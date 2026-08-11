#pragma once
#include "PrimitivesManager.h"
#include "Command.h"

class CmdSetCullMode : public Command
{
public:
	const char* GetName() override
	{
		return "SetCullMode";
	}
	const char* GetDescription() override
	{
		return "CmdSetCullMode(mode)\n\n- Sets cull mode for rendering\n- <none>: No cull mode used\n- <back>: cull faces away from the camera\n- <front>: cull faces pointed at the  camera\n";
	}

	bool Execute(const std::vector<std::string>& params) override;



private:
};