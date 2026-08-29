#include "CmdSetShadeMode.h"
#include "Rasterizer.h"

bool CmdSetShadeMode::Execute(const std::vector<std::string>& params)
{
	if (params.size() < 1)
	{
		return false;
	}

	ShadeMode shademode = ShadeMode::Flat;
	if (params[0] == "flat") { shademode = ShadeMode::Flat; }
	else if (params[0] == "gouraud") { shademode = ShadeMode::Gouraud; }
	else if (params[0] == "phong") { shademode = ShadeMode::Phong; }
	else
	{
		return false;
	}

	Rasterizer::Get()->SetShadeMode(shademode);
	return true;
}
