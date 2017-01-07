#pragma once

#include "../NPC.h"

namespace Atlamillia
{

	class SkeletonWarrior : public NPC
	{
	private:
		short int m_health = 100;
	protected:
	public:

		void Update();

		void Draw(glm::vec2 offset, Atlamillia::Graphics::Renderer* rend);

		void TakeDamage(short int _dmg) { m_health -= _dmg; };
		short int GetHealth() { return m_health; };

		void Kill();

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