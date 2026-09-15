#pragma once

#include "Command.h"

class CmdPostProcessingBeginDraw : public Command
{
public:
	const char* GetName() override
	{
		return "PostProcessingBeginDraw";
	}
	const char* GetDescription() override
	{
		return "PostProcessingBeginDraw()\n\n- initiates rendering to target instead of to the main screen";
	}

	bool Execute(const std::vector<std::string>& params) override;
};

class CmdPostProcessingEndDraw : public Command
{
public:
	const char* GetName() override
	{
		return "PostProcessingEndDraw";
	}
	const char* GetDescription() override
	{
		return "PostProcessingEndDraw()\n\n- draws the render target to the main screen\n- applies set effects to the image";
	}

	bool Execute(const std::vector<std::string>& params) override;
};

class CmdPostProcessingSetEffectType : public Command
{
public:
	const char* GetName() override
	{
		return "PostProcessingSetEffectType";
	}
	const char* GetDescription() override
	{
		return "PostProcessingSetEffectType(effectType)\n\n- Set the effect to apply to the image\n- none, monochrome, invert, mirror, blur\n - colormaskr, colormaskg, colormaskb\n-sepia, wave";
	}

	bool Execute(const std::vector<std::string>& params) override;
};