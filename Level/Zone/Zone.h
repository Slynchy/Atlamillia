#pragma once

#include "./Tile/Tile.h"

namespace Atlamillia
{
	class Zone
	{
		private:
			std::vector<std::vector<Atlamillia::Tile*>> m_tiles;
		protected:
		public:

			glm::ivec2 GetSize()
			{
				return glm::ivec2(m_tiles.size(), m_tiles.front().size());
			}

			Tile* GetTile(size_t x, size_t y)
			{
				return m_tiles.at(y).at(x);
			}

			void Resize(size_t _w, size_t _h)
			{
				m_tiles.resize(_h);
				for (size_t i = 0; i < m_tiles.size(); i++)
				{
					m_tiles.at(i).resize(_w);
				}
			}
	};
}