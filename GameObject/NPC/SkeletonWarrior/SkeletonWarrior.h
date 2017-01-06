#pragma once

#include "../NPC.h"

namespace Atlamillia
{

	class SkeletonWarrior : public NPC
	{
	private:
	protected:
	public:

		void Update();

		void Draw(glm::vec2 offset, Atlamillia::Graphics::Renderer* rend);

		void Kill() {};

		SkeletonWarrior(glm::ivec2 _startpos, Level** _parentlevel);

		~SkeletonWarrior()
		{
			if (brain != nullptr)
			{
				delete brain;
				brain = nullptr;
			};
		}
	};

}