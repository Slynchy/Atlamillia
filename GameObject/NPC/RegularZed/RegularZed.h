#pragma once

#include "../NPC.h"

namespace Atlamillia
{

	class RegularZed : public NPC
	{
		private:
			float m_speed;
			const unsigned int m_wanderDistance = 10; // how far the zombie will path to
			float frame = 0.0f;
		protected:
		public:

			float GetSpeed() { return m_speed; };

			void Update();

			void Draw(glm::vec2 offset, Atlamillia::Graphics::Renderer* rend);

			unsigned int GetWanderDistance() { return m_wanderDistance; };

			RegularZed(glm::ivec2 _startpos, Level** _parentlevel);

			~RegularZed()
			{
				if (brain != nullptr)
				{
					delete brain;
					brain = nullptr;
				};
			}
	};

}