#pragma once
#include "Command.h"

class CmdPushTranslation : public Command
{
public:
	const char* GetName() override
	{
		return "PushTranslation";
	}

	const char* GetDescription() override
	{
		return "PushTranslation(x,y,z)\n\n - Pushes a translation matrix to the matrix stack";
	}

	bool Execute(const std::vector<std::string>& params) override;


private:

};

class CmdPushRotationX : public Command
{
public:
	const char* GetName() override
	{
		return "PushRotationX";
	}

	const char* GetDescription() override
	{
		return "PushRotationX(degrees)\n\n- Pushes a rotation around the X axis matrix to the matrix stack";
	}

	bool Execute(const std::vector<std::string>& params) override;
};

class CmdPushRotationY : public Command
{
public:
	const char* GetName() override
	{
		return "PushRotationY";
	}

	const char* GetDescription() override
	{
		return "PushRotationY(degrees)\n\n- Pushes a rotation around the Y axis matrix to the matrix stack";
	}

	bool Execute(const std::vector<std::string>& params) override;
};

class CmdPushRotationZ : public Command
{
public:
	const char* GetName() override
	{
		return "PushRotationZ";
	}

	const char* GetDescription() override
	{
		return "PushRotationZ(degrees)\n\n- Pushes a rotation around the Z axis matrix to the matrix stack";
	}

	bool Execute(const std::vector<std::string>& params) override;
};

class CmdPushScaling : public Command
{
public:
	const char* GetName() override
	{
		return "PushScaling";
	}

	const char* GetDescription() override
	{
		return "PushScaling(x,y,z)\n\n - Pushes a scale matrix to the matrix stack";
	}

	bool Execute(const std::vector<std::string>& params) override;


private:

};

class CmdPopMatrix : public Command
{
public:
	const char* GetName() override
	{
		return "PopMatrix";
	}

	const char* GetDescription() override
	{
		return "PopMatrix()\n\n- Pops the last matrix on the matrix stack";
	}

	bool Execute(const std::vector<std::string>& params) override;


private:

};