#pragma once

#include "../NPC.h"

namespace Atlamillia
{

	class RegularZed : public NPC
	{
		private:
			const float m_speed = 0.03f;
		protected:
		public:

			void Update();

			void Draw(Atlamillia::Graphics::Renderer* rend, glm::vec2 offset);

			RegularZed(glm::ivec2 _startpos)
			{
				pos = _startpos;
			}
	};

}