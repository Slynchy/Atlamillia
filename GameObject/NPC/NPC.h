#pragma once

#include "../GameObject.h"
#include "../../Engine/AI/StateManager.h"

namespace Atlamillia
{

	class NPC : public GameObject
	{
		private:
		protected:
			Atlamillia::StateManager* brain;
		public:
			float m_speed;
			float GetSpeed() { return m_speed; };

			virtual Atlamillia::StateManager* GetStateManager()
			{
				return brain;
			}

			void MoveTowards(glm::vec2 _dst);

			NPC()
			{
				brain = new StateManager(this);
			}

			~NPC()
			{
				if(brain != nullptr)
					delete brain;
			}
	};

}