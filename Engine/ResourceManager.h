#pragma once

#include <string>
#include "Graphics\Graphics.h"
#include <vector>

namespace Atlamillia
{
	class ResourceManager
	{
		private:
			std::vector<Graphics::Texture*> loaded_textures;

		public:
			Graphics::Texture* GetTexture(std::string _name, Atlamillia::Graphics::Renderer* _rend = NULL);

			~ResourceManager()
			{
				for (size_t i = 0; i < loaded_textures.size(); i++)
				{
					delete loaded_textures.at(i);
				}
				loaded_textures.clear();
			}
	};
};