#pragma once
#include "Command.h"

class CmdSetLightAmbient : public Command
{
public:
	const char* GetName() override
	{
		return "SetLightAmbient";
	}

	const char* GetDescription() override
	{
		return
		{
			"SetLightAmbient(r,g,b)\n\n- Sets the ambient color of light"
		};
	}

	bool Execute(const std::vector<std::string>& params) override;

private:
};

class CmdSetLightDiffuse : public Command
{
public:
	const char* GetName() override
	{
		return "SetLightDiffuse";
	}

	const char* GetDescription() override
	{
		return
		{
			"SetLightDiffuse(r,g,b)\n\n- Sets the Diffuse color of light"
		};
	}

	bool Execute(const std::vector<std::string>& params) override;

private:
};

class CmdSetLightSpecular : public Command
{
public:
	const char* GetName() override
	{
		return "SetLightSpecular";
	}

	const char* GetDescription() override
	{
		return
		{
			"SetLightSpecular(r,g,b)\n\n- Sets the Specular color of light"
		};
	}

	bool Execute(const std::vector<std::string>& params) override;

private:
};

class CmdAddDirectionalLight : public Command
{
public:
	const char* GetName() override
	{
		return "AddDirectionalLight";
	}

	const char* GetDescription() override
	{
		return
		{
			"AddDirectionalLight(x,y,z)\n\n- adds a directional light to the scene"
		};
	}

	bool Execute(const std::vector<std::string>& params) override;

};

class CmdAddPointLight : public Command
{
public:
	const char* GetName() override
	{
		return "AddPointLight";
	}

	const char* GetDescription() override
	{
		return
		{
			"AddPointLight(x,y,z, <constant>, <linear>, <quadratic>)\n\n- adds a point light to the scene at a specified position\n - can modify the attenuation constants"
		};
	}

	bool Execute(const std::vector<std::string>& params) override;

};

class CmdAddSpotLights : public Command
{
public:
	const char* GetName() override
	{
		return "AddSpotLight";
	}

	const char* GetDescription() override
	{
		return
		{
			"AddSpotLight(pX, pY, pZ, dX, dY, dZ, <constant>, <linear>, <quadratic>, <angle>, <decay>)\n- adds a spot light to the scene at a specified position and angle"
		};
	}

	bool Execute(const std::vector<std::string>& params) override;

};