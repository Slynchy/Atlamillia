#pragma once

#include "SkeletonWarrior.h"
#include "../RegularZed/RegularZed.h"
#include <glm\glm.hpp>
#include "../../../Engine/AI/AI.h"
#include "../../../../ModularPathFinding/node.h"
#include "../../../Level/Level.h"
#include "../../../Engine/Graphics/Debug.h"
#include "../../../Atlamillia.h"
#include "../../../Engine/ResourceManager.h"


namespace Atlamillia
{
	namespace SkeletonWarrior_States
	{
		class Idle : public AIState
		{
			private:
			protected:
			public:

				Idle(StateManager* _parent);

				void Update();
		};

		class Patrol : public AIState
		{
			private:
			public:
				void Update();

				Patrol(StateManager* _parent)
				{
					parent_manager = _parent;
				}
		};

		class Hunt : public AIState
		{
		private:
			GameObject* target;
		public:
			void Update();

			Hunt(StateManager* _parent, GameObject* _target)
			{
				parent_manager = _parent;
				target = _target;
			}
		};

		class Attack : public AIState
		{
			private:
				GameObject* target;
			public:
				void Update();

				Attack(StateManager* _parent, GameObject* _target)
				{
					parent_manager = _parent;
					target = _target;
					parent_manager->parent->SetFrame(0);
					this->parent_manager->parent->IsAttacking(true);
				}
		};

	}

}