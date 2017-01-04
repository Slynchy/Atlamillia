#pragma once

#include "../NPC.h"

namespace Atlamillia
{

	class RegularZed : public NPC
	{
		private:
			const unsigned int m_wanderDistance = 4; // how far the zombie will path to
			float frame = 0.0f;
		protected:
		public:

			void Update();

			void Draw(glm::vec2 offset, Atlamillia::Graphics::Renderer* rend);

			void Kill();

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