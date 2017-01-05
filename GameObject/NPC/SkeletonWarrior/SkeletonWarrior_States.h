#pragma once

#include "SkeletonWarrior.h"
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

	}

}