#include "CmdSetTexture.h"

bool CmdSetTexture::Execute(const std::vector<std::string>& params)
{
    if (params.size() < 1)
    {
        return false;
    }

    TextureManager::Get()->SetTexutre(params[0]);
    return true;
}
