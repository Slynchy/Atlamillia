#pragma once

#include "./Zone/Zone.h"
#include <vector>

namespace Atlamillia
{
	// Level == the whole map
	// Zone == section of map
	// Tile == tile of map
	class Level
	{
		private:
			std::vector<std::vector<Atlamillia::Zone*>> m_zones;
			std::vector<Atlamillia::GameObject*> m_scenegraph;
			Atlamillia::Graphics::Renderer* m_renderer;

			Level(size_t _w, size_t _h, size_t _zW, size_t _zH, Atlamillia::Graphics::Renderer* _rend = nullptr)
			{
				m_renderer = _rend;
				m_zones.resize(_h);
				for (size_t y = 0; y < m_zones.size(); y++)
				{
					m_zones.at(y).resize(_w);
					for (size_t x = 0; x < m_zones.at(y).size(); x++)
					{
						m_zones.at(y).at(x) = new Zone();
						m_zones.at(y).at(x)->Resize(_zW, _zH);
					}
				}
			}
		protected:
		public:

			void Draw()
			{

			}

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

			static Level* CreateLevel(size_t _w, size_t _h, size_t _zW, size_t _zH, Atlamillia::Graphics::Renderer* _rend = nullptr)
			{
				return new Level(_w, _h, _zW, _zH, _rend);
			}

			~Level()
			{

			}
	};
}