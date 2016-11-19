#pragma once

#include "../../../GameObject/GameObject.h"
#include <glm/glm.hpp>

namespace Atlamillia
{
	class Tile
	{
		private:
			/// Objects that occupy this tile
			std::vector<GameObject*> m_objects;
		protected:
		public:
			glm::ivec2 pos;
	};
}