#pragma once

#include "../NPC.h"

namespace Atlamillia
{
	/// Zombie NPC class
	class RegularZed : public NPC
	{
		private:
			/// How far the zombie can path to
			const unsigned int m_wanderDistance = 12; 

			/// Animation frame
			float frame = 0.0f;
		protected:
		public:

			/// Updates the zombie via its active state
			void Update();

			/// Draws the zombie
			void Draw(glm::vec2 offset, Atlamillia::Graphics::Renderer* rend);

			/// Kills the zombie
			void Kill();

			/// Gets the wander distance
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