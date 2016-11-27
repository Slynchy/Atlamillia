#pragma once

#include "./Zone/Zone.h"
#include <vector>
#include "./Atlamillia/Engine/CSVLoader/CSVLoader.h"
#include "../GameObject/Player/Player.h"
#include "../../ModularPathFinding/node.h"

namespace Atlamillia
{
	class Engine;

	// Level == the whole map
	// Zone == section of map
	// Tile == tile of map
	class Level
	{
		private:
			std::vector<std::vector<Atlamillia::Zone*>> m_zones;
			std::vector<Atlamillia::GameObject*> m_scenegraph;
			Atlamillia::Graphics::Renderer* m_renderer;
			Atlamillia::Graphics::Texture* m_texture;
			Atlamillia::Engine* m_engine;
			std::vector<Atlamillia::Graphics::Texture*> m_levelTextures;
			void SetTileValues(glm::ivec2 _zone, std::vector<std::vector<int>>& _in);

			std::vector<Atlamillia::GameObject*> m_props;

			Level(size_t _w, size_t _h, size_t _zW, size_t _zH, Atlamillia::Engine* _eng);
			void Draw();
		protected:
		public:

			Atlamillia::Player* m_player;

			void Draw(glm::ivec2 offset);

			std::vector<Atlamillia::GameObject*>* GetLevelProps()
			{
				return &m_props;
			}

			void UpdateTexture();

			void DebugDraw(glm::ivec2 offset)
			{
				for (size_t y = 0; y < (size_t)GetSize().y; y++)
				{
					for (size_t x = 0; x < (size_t)GetSize().x; x++)
					{
						for (size_t zY = 0; zY < (size_t)GetZone(x, y)->GetSize().y; zY++)
						{
							for (size_t zX = 0; zX < (size_t)GetZone(x, y)->GetSize().x; zX++)
							{
								//_level->GetZone(x, y)->GetTile(zX, zY);
								glm::ivec2 temp = Atlamillia::Iso::twoDToIso(glm::vec2(zX, zY) + (glm::vec2(x, y) * (float)GetZone(x, y)->GetSize().y));
								temp += offset;
								(m_renderer)->RenderDrawLine(temp.x, temp.y + 16, temp.x + 32, temp.y);
								(m_renderer)->RenderDrawLine(temp.x + 32, temp.y, temp.x + 64, temp.y + 16);
								(m_renderer)->RenderDrawLine(temp.x + 64, temp.y + 16, temp.x + 32, temp.y + 32);
								(m_renderer)->RenderDrawLine(temp.x + 32, temp.y + 32, temp.x, temp.y + 16);
							};
						}
					};
				}
				return;
			}

			glm::ivec2 GetSize()
			{
				return glm::ivec2(m_zones.size(), m_zones.front().size());
			}

			Atlamillia::Zone* GetZone(size_t x, size_t y)
			{
				return m_zones.at(y).at(x);
			}

			static Level* CreateLevel(const char* _inputfile, Atlamillia::Engine* _eng);
			static Level* CreateLevel(size_t _w, size_t _h, size_t _zW, size_t _zH, Atlamillia::Engine* _eng);

			~Level()
			{

			}
	};
}