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
			std::string Tag = "GameObject";
			enum DIRECTIONS
			{
				WEST,
				NORTH_WEST, 
				NORTH,
				NORTH_EAST, 
				EAST,
				SOUTH_EAST, 
				SOUTH,
				SOUTH_WEST 
			};

			static std::vector<GameObject*> SceneGraph;
		private:
		protected:
			Atlamillia::Graphics::Texture* m_activeTexture;
			SDL_Rect srcRect;
			SDL_Rect dstRect;
		public:

			DIRECTIONS m_direction;
			Level** parent_level;
			glm::vec2 pos;
			glm::vec2 velocity;
			std::size_t TagHash;
			int drawOrder = 0;

			void ChangeTag(std::string _newtag);

			void SetTexture(Atlamillia::Graphics::Texture* _tex);

			void SetIsoPos(glm::ivec2 _pos);

			void Translate(float _x, float _y);

			void Translate(glm::vec2 _trs);

			void Translate(float _x, float _y, std::vector<GameObject*>* _objects);

			void LookAt(glm::ivec2 _target);

			virtual void Update() {};
			virtual void Draw(glm::ivec2 _offset, Atlamillia::Graphics::Renderer* _rend);

			GameObject::DIRECTIONS GameObject::GetDirectionFromDelta(glm::vec2 _deltapos);

			GameObject();
			~GameObject();
	};

};