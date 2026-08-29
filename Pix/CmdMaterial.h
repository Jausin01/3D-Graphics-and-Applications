#pragma once
#include "Command.h"

class CmdMaterialEmissive : public Command
{
public:
	const char* GetName() override
	{
		return "SetMaterialEmissive";
	}
	const char* GetDescription() override
	{
		return "SetMaterialEmissive(r,g,b)\n\n- Sets the rgb value for the material emissve Color";
	}

	bool Execute(const std::vector<std::string>& params) override;
};

class CmdMaterialAmbient : public Command
{
public:
	const char* GetName() override
	{
		return "SetMaterialAmbient";
	}
	const char* GetDescription() override
	{
		return "SetMaterialAmbient(r,g,b)\n\n- Sets the rgb value for the material Ambient Color";
	}

	bool Execute(const std::vector<std::string>& params) override;
};

class CmdMaterialDiffuse : public Command
{
public:
	const char* GetName() override
	{
		return "SetMaterialDiffuse";
	}
	const char* GetDescription() override
	{
		return "SetMaterialDiffuse(r,g,b)\n\n- Sets the rgb value for the material Diffuse Color";
	}

	bool Execute(const std::vector<std::string>& params) override;
};

class CmdMaterialSpecular : public Command
{
public:
	const char* GetName() override
	{
		return "SetMaterialSpecular";
	}
	const char* GetDescription() override
	{
		return "SetMaterialSpecular(r,g,b)\n\n- Sets the rgb value for the material Specular Color";
	}

	bool Execute(const std::vector<std::string>& params) override;
};

class CmdMaterialShininess : public Command
{
public:
	const char* GetName() override
	{
		return "SetMaterialShininess";
	}
	const char* GetDescription() override
	{
		return "SetMaterialShininess(float)\n\n- Sets the rgb value for the material shininess";
	}

	bool Execute(const std::vector<std::string>& params) override;
};