#pragma once

#include <glm\glm.hpp>
#include <SDL2\SDL.h>
#include "../GameObject.h"
#include "../../Engine/Graphics/Graphics.h"

namespace Atlamillia
{
	class Player : public GameObject
	{
		private:
			float frame = 0.0f;
		protected:
		public:
			Graphics::Texture* texture;

			void Draw(Atlamillia::Graphics::Renderer* _rend, glm::vec2 _offset);
			void Draw(Atlamillia::Graphics::Renderer* _rend, glm::vec2 _viewportPos, glm::vec2 _viewportSize);

			Player()
			{
				Tag = "Player";
			}

			~Player()
			{
				frame = 0.0f;
				texture = nullptr;
			}
	};
}