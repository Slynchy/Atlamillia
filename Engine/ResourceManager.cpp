#include "ResourceManager.h"

void Atlamillia::ResourceManager::DeleteTexture(Graphics::Texture* _tex)
{
	if (_tex == nullptr) return;
	for (size_t i = 0; i < loaded_textures.size(); i++)
	{
		if (loaded_textures.at(i) == _tex)
		{
			delete loaded_textures.at(i);
			loaded_textures.erase(loaded_textures.begin() + i);
			break;
		}
	}
	return;
}

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
		dprintf("[RManager] Could not load file (no renderer): %s\n", _name.c_str());
		return NULL;
	}
	else
	{
		temp = new Atlamillia::Graphics::Texture(_rend, _name.c_str());
	}

	// If temp == null, it's because it couldn't be loaded for whatever reason
	if (temp->GetFilename() != "")
	{
		dprintf("[RManager] Loading texture: %s\n", _name.c_str());
		loaded_textures.push_back(temp);
		return temp;
	}
	else
	{
		dprintf("[RManager] Could not load file: %s\n", _name.c_str());
		return NULL;
	}
};