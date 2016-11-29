#pragma once

#include <glm\glm.hpp>
#include "../Engine/Isometry/Isometry.h"
#include "../Engine/Graphics/Graphics.h"
#include <iostream>
#include <vector>
#include <algorithm>

namespace Atlamillia
{

	class Level;

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
			SDL_Rect srcRect;
			SDL_Rect dstRect;
		public:

			Level** parent_level;
			std::string Tag = "GameObject";
			glm::vec2 pos;

			void SetTexture(Atlamillia::Graphics::Texture* _tex)
			{
				m_activeTexture = _tex;
			}

			void SetIsoPos(glm::ivec2 _pos)
			{
				pos = Iso::twoDToIso(_pos);
			}

			void Draw(glm::ivec2 _offset, Atlamillia::Graphics::Renderer* _rend)
			{
				glm::ivec2 temp = Iso::twoDToIso(glm::ivec2(pos));
				temp += _offset;
				temp.y = temp.y - m_activeTexture->GetDimensions().y + 32;
				if (
					temp.x + this->m_activeTexture->GetDimensions().x < 0 ||
					temp.y + this->m_activeTexture->GetDimensions().y < 0 ||
					temp.x > _rend->GetResolution().x ||
					temp.y > _rend->GetResolution().y
					)
				{
					return;
				};
				dstRect = { temp.x,temp.y,m_activeTexture->GetDimensions().x,m_activeTexture->GetDimensions().y };
				_rend->RenderCopy(this->m_activeTexture, NULL, &dstRect);
			}

			void Translate(float _x, float _y)
			{
				pos += glm::vec2(_x, _y);
				m_direction = GetDirectionFromDelta(glm::vec2(_x, _y));
			}

			void Translate(glm::vec2 _trs)
			{
				pos += _trs;
				m_direction = GetDirectionFromDelta(_trs);
			}

			void Translate(float _x, float _y, std::vector<GameObject*>* _objects)
			{
				_x = std::max(-0.05f, std::min(_x, 0.05f));
				_y = std::max(-0.05f, std::min(_y, 0.05f));

				bool collision = false;
				glm::vec2 tempPos = pos + glm::vec2(_x, _y);
				glm::ivec2 tempPosI = glm::ivec2(tempPos);
				for (size_t i = 0; i < _objects->size(); i++)
				{
					if (
						tempPosI.x == _objects->at(i)->pos.x ||
						tempPosI.x == _objects->at(i)->pos.x - 1
						)
					{
						if (
							tempPosI.y == _objects->at(i)->pos.y ||
							tempPosI.y == _objects->at(i)->pos.y - 1
							)
						{
							collision = true;
							break;
						}
					}
				}


				if(collision != true)
					pos += glm::vec2(_x, _y);
				m_direction = GetDirectionFromDelta(glm::vec2(_x, _y));
			}

			GameObject::DIRECTIONS GameObject::GetDirectionFromDelta(glm::vec2 _deltapos)
			{

				if (_deltapos.x > 0 && _deltapos.y > 0) 
				{
					return GameObject::DIRECTIONS::SOUTH;
				}
				else if (_deltapos.x < 0 && _deltapos.y > 0) 
				{
					return GameObject::DIRECTIONS::WEST;
				}
				else if (_deltapos.x < 0 && _deltapos.y < 0) 
				{
					return GameObject::DIRECTIONS::NORTH;
				}
				else if (_deltapos.x > 0 && _deltapos.y < 0) 
				{
					return GameObject::DIRECTIONS::EAST;
				}
				else if (_deltapos.x == 0 && _deltapos.y > 0)
				{
					return GameObject::DIRECTIONS::SOUTH_WEST;
				}
				else if (_deltapos.x == 0 && _deltapos.y < 0)
				{
					return GameObject::DIRECTIONS::NORTH_EAST;
				}
				else if (_deltapos.x > 0 && _deltapos.y == 0)
				{
					return GameObject::DIRECTIONS::SOUTH_EAST;
				}
				else if (_deltapos.x < 0 && _deltapos.y == 0)
				{
					return GameObject::DIRECTIONS::NORTH_WEST;
				}
				return GameObject::DIRECTIONS::SOUTH;
			}

			GameObject()
			{
				srcRect = { 0,0,0,0 };
				dstRect = { 0,0,0,0 };
			}
			~GameObject()
			{
				srcRect = { 0,0,0,0 };
				dstRect = { 0,0,0,0 };
			}
	};

};