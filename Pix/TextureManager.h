#pragma once
#include "Texture.h"

class TextureManager
{
public:

	static TextureManager* Get();

	void Clear();
	void SetTexutre(const std::string& fileName);
	void SetUseFilter(bool useFilter);

	void SetAddresssMode(AddressMode addressMode);

	// "Hack" is to use clor with -z to flag color as uv coordinates
	X::Color SampleColor(const X::Color& uv) const;

private:

	std::vector<std::unique_ptr<Texture>> mTextures;
	const Texture* mCurrentTexture = nullptr;
	bool mUseFilter = false;
	AddressMode mAddressMode = AddressMode::Clamp;
};