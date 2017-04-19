/// \file 		ResourceManager.h
/// \author 	Sam Lynch
/// \brief 		Header file for resource manager

#pragma once

#include <string>
#include "Graphics\Graphics.h"
#include <vector>
#include "../Engine/Graphics/Debug.h"

namespace Atlamillia
{
	/// Class for resource management
	class ResourceManager
	{
		private:
			std::vector<Graphics::Texture*> loaded_textures;
			Graphics::Renderer* rend;

		public:
			/// Gets the specified texture and loads it if it isn't already loaded.
			/// Does not require the renderer to be passed in as a parameter.
			Graphics::Texture* GetTexture(std::string _name, Atlamillia::Graphics::Renderer* _rend = NULL);

			/// Deletes the specified texture from the loaded textures
			void DeleteTexture(Graphics::Texture* _tex);

			/// Adds the specified texture to the loaded texture array
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