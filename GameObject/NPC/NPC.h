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

			virtual Atlamillia::StateManager* GetStateManager()
			{
				return brain;
			}

			NPC()
			{
				brain = new StateManager(this);
			}
	};

}