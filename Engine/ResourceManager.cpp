#include "ResourceManager.h"

Atlamillia::Graphics::Texture* Atlamillia::ResourceManager::GetTexture(std::string _name, Atlamillia::Graphics::Renderer* _rend)
{
	for (size_t i = 0; i < loaded_textures.size(); i++)
	{
		if (loaded_textures.at(i)->GetFilename() == _name)
		{
			return loaded_textures.at(i);
		}
	}

	// texture not found, load it
	Atlamillia::Graphics::Texture* temp;

	// if no renderer passed
	// We don't pass renderer for assets that *should* already be loaded
	// If this error happens, it just needs access to the renderer somehow
	if (_rend == NULL)
	{
		printf("Could not load file (no renderer): %s\n", _name.c_str());
		return NULL;
	}
	else
	{
		temp = new Atlamillia::Graphics::Texture(_rend, _name.c_str());
	}

	// If temp == null, it's because it couldn't be loaded for whatever reason
	if (temp->GetFilename() != "")
	{
		loaded_textures.push_back(temp);
		return temp;
	}
	else
	{
		printf("Could not load file: %s\n", _name.c_str());
		return NULL;
	}
};