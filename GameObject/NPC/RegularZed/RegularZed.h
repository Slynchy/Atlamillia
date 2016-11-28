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

			float GetSpeed() { return m_speed; };

			void Update();

			void Draw(Atlamillia::Graphics::Renderer* rend, glm::vec2 offset);

			RegularZed(glm::ivec2 _startpos)
			{
				pos = _startpos;
			}
	};

}