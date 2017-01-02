#pragma once

#include "../NPC.h"

namespace Atlamillia
{
	class Graphics::Texture;
	class Wyvern : public NPC
	{
		private:
			const unsigned int m_wanderDistance = 5; // how far the zombie will path to
			float frame = 0.0f;
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