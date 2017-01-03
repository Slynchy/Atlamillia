#pragma once

#include <string>
#include "Graphics\Graphics.h"
#include <vector>
#include "../Engine/Graphics/Debug.h"

namespace Atlamillia
{
	class ResourceManager
	{
		private:
			std::vector<Graphics::Texture*> loaded_textures;
			Graphics::Renderer* rend;

		public:
			Graphics::Texture* GetTexture(std::string _name, Atlamillia::Graphics::Renderer* _rend = NULL);

			void DeleteTexture(Graphics::Texture* _tex);

			void AddTexture(Graphics::Texture* _tex)
			{
				loaded_textures.push_back(_tex);
			};

			ResourceManager(Graphics::Renderer* _rend)
			{
				rend = _rend;
			}
			
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