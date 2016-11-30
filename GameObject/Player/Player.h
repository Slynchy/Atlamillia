#pragma once

#include <glm\glm.hpp>
#include <SDL2\SDL.h>
#include "../GameObject.h"
#include "../../Engine/Graphics/Graphics.h"

namespace Atlamillia
{
	class InputManager;
	class Player : public GameObject
	{
		private:
			float frame = 0.0f;
			glm::vec2 movement = glm::vec2(0, 0);
		protected:
		public:
			Graphics::Texture* texture;

			void Draw(Atlamillia::Graphics::Renderer* _rend, glm::vec2 _offset);
			void Draw(Atlamillia::Graphics::Renderer* _rend, glm::vec2 _viewportPos, glm::vec2 _viewportSize);

			bool HandleInput(InputManager* _iman);

			void Update(InputManager* _iman);

			Player(Level** _lev)
			{
				Tag = "Player";
				parent_level = _lev;
			}

			~Player()
			{
				frame = 0.0f;
				texture = nullptr;
			}
	};
}