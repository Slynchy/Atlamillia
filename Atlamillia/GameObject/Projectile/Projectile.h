#pragma once

#include "../GameObject.h"

namespace Atlamillia
{
	class ResourceManager;
	class Projectile : public GameObject
	{
		private:
			glm::ivec2 target;
			glm::vec2 offset;
			ResourceManager* rsrc;
			float frame = 0.0f;
		protected:

		public:

			void Draw(glm::vec2 offset, Atlamillia::Graphics::Renderer* rend);
			void Update();

			Projectile(glm::ivec2 _target, ResourceManager* rsrc, glm::vec2 _offset = glm::vec2());

	};

}