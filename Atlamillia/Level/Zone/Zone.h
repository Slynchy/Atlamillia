#pragma once

#include "./Tile/Tile.h"
#include "../../../ModularPathFinding/node.h"

namespace Atlamillia
{
	class Zone
	{
		private:
			std::vector<std::vector<Atlamillia::Tile*>> m_tiles;
		protected:
		public:
			std::vector<std::vector<NODE*>> m_nodemap;

			glm::ivec2 GetSize()
			{
				return glm::ivec2(m_tiles.size(), m_tiles.front().size());
			}

			Tile* GetTile(size_t x, size_t y)
			{
				return m_tiles.at(y).at(x);
			}
			void SetTile(size_t x, size_t y, Tile* _til)
			{
				m_tiles.at(y).at(x) = _til;
			}

			void Resize(size_t _w, size_t _h)
			{
				m_tiles.resize(_h);
				for (size_t i = 0; i < m_tiles.size(); i++)
				{
					m_tiles.at(i).resize(_w);
					for (size_t x = 0; x < m_tiles.at(i).size(); x++)
					{
						m_tiles.at(i).at(x) = new Tile();
					}
				}
			}

			~Zone()
			{
				for (size_t y = 0; y < m_tiles.size(); y++)
				{
					for (size_t x = 0; x < m_tiles.at(y).size(); x++)
					{
						delete m_tiles.at(y).at(x);
						delete m_nodemap.at(y).at(x);
					}
				}
			}
	};
}