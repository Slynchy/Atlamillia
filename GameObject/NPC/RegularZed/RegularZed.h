#pragma once

#include "../NPC.h"

namespace Atlamillia
{

	class RegularZed : public NPC
	{
		private:
			const float m_speed = 0.03f;
			const unsigned int m_wanderDistance = 10; // how far the zombie will path to
		protected:
		public:

			float GetSpeed() { return m_speed; };

			void Update();

			void Draw(Atlamillia::Graphics::Renderer* rend, glm::vec2 offset);

			unsigned int GetWanderDistance() { return m_wanderDistance; };

			RegularZed(glm::ivec2 _startpos, Level** _parentlevel)
			{
				pos = _startpos;
				parent_level = _parentlevel;
				Tag = "RegularZombie";
			}

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