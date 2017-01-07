#pragma once

#include "../NPC.h"

namespace Atlamillia
{
	class Graphics::Texture;

	/// Wyvern NPC class
	class Wyvern : public NPC
	{
		private:
			/// How far away the wyvern can path to
			const unsigned int m_wanderDistance = 5;

			/// Current animation frame
			float frame = 0.0f;

			/// Texture of wyvern in flight
			Graphics::Texture* flyingTexture;
		protected:
		public:

			void Update();

			void Draw(glm::vec2 offset, Atlamillia::Graphics::Renderer* rend);

			unsigned int GetWanderDistance() { return m_wanderDistance; };

			Wyvern(glm::ivec2 _startpos, Level** _parentlevel);

			~Wyvern()
			{
				if (brain != nullptr)
				{
					delete brain;
					brain = nullptr;
				};
			}
	};

}