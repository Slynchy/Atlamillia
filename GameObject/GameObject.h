#pragma once

#include <glm\glm.hpp>
#include "../Engine/Isometry/Isometry.h"
#include "../Engine/Graphics/Graphics.h"
#include <iostream>

namespace Atlamillia
{

	class GameObject
	{
		public:
			enum DIRECTIONS
			{
				NORTH,
				NORTH_EAST, // s
				EAST,
				SOUTH_EAST, // d
				SOUTH,
				SOUTH_WEST, // w
				WEST,
				NORTH_WEST // a
			};
		private:
		protected:
			DIRECTIONS m_direction;
			Atlamillia::Graphics::Texture* m_activeTexture;
		public:

			glm::vec2 pos;


			void Translate(float _x, float _y)
			{
				glm::vec2 delta = Atlamillia::Iso::twoDToIso(glm::vec2(_x, _y));
				pos += delta;
				m_direction = GetDirectionFromDelta(delta);
				//std::cout << "Direction: " << (int)m_direction << "\n";
			}

			GameObject::DIRECTIONS GameObject::GetDirectionFromDelta(glm::vec2 _deltapos)
			{
				float angle = (atan2f(_deltapos.y, _deltapos.x));
				//std::cout << "Angle: " << angle << "\n";
				if (_deltapos.x >= 0.001f && _deltapos.y >= 0.001f) 
				{
					return GameObject::DIRECTIONS::SOUTH;
				}
				else if (_deltapos.x >= 0.001f && _deltapos.y <= -0.001f) 
				{
					return GameObject::DIRECTIONS::EAST;
				}
				else if (_deltapos.x <= 0.001f && _deltapos.y >= 0.001f) 
				{
					return GameObject::DIRECTIONS::WEST;
				}
				else if (_deltapos.x <= 0.001f && _deltapos.y <= -0.001f) 
				{
					return GameObject::DIRECTIONS::NORTH;
				}
				return GameObject::DIRECTIONS::SOUTH;
			}

			GameObject()
			{

			}
			~GameObject()
			{

			}
	};

};