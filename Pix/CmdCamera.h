#pragma once
#include "Command.h"

class CmdSetCameraPosition : public Command
{
public:
	const char* GetName() override
	{
		return "SetCameraPosition";
	}

	const char* GetDescription() override
	{
		return
		{
			"SetCameraPosition(x,y,z)\n\n- Sets Camera Position in The Scene"
		};
	}

	bool Execute(const std::vector<std::string>& params) override;

private:

};

class CmdSetCameraDirection : public Command
{
public:
	const char* GetName() override
	{
		return "SetCameraDirection";
	}

	const char* GetDescription() override
	{
		return
		{
			"SetCameraDirection(x,y,z)\n\n-Sets the Direction of the Camera, will normalize when set"
		};
	}

	bool Execute(const std::vector<std::string>& params) override;

private:
};

class CmdSetCameraNear : public Command
{
public:
	const char* GetName() override
	{
		return "SetCameraNear";
	}

	const char* GetDescription() override
	{
		return
		{
			"SetCameraNear(nearplane)\n\n-Sets the near plane value for the camera"
		};
	}

	bool Execute(const std::vector<std::string>& params) override;

private:
};

class CmdSetCameraFar : public Command
{
public:
	const char* GetName() override
	{
		return "SetCameraFar";
	}

	const char* GetDescription() override
	{
		return
		{
			"SetCameraDirection(farplane)\n\n-Sets the far plane distance for the camera"
		};
	}

	bool Execute(const std::vector<std::string>& params) override;

private:
};

class CmdSetCameraFov : public Command
{
public:
	const char* GetName() override
	{
		return "SetCameraFov";
	}

	const char* GetDescription() override
	{
		return
		{
			"SetCamerafov(degrees)\n\n-Sets the camera field of view in degrees"
		};
	}

	bool Execute(const std::vector<std::string>& params) override;

private:
};