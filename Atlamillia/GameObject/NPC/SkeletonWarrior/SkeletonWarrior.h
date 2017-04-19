#pragma once

#include "../NPC.h"

namespace Atlamillia
{

	/// Skeleton warrior NPC class
	class SkeletonWarrior : public NPC
	{
	private:
		/// NPCs health
		short int m_health = 100;
	protected:
	public:

		void Update();

		void Draw(glm::vec2 offset, Atlamillia::Graphics::Renderer* rend);

		/// Deals damage to the NPC
		void TakeDamage(short int _dmg) { m_health -= _dmg; };

		/// Gets NPCs health
		short int GetHealth() { return m_health; };

		/// Kills NPC
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