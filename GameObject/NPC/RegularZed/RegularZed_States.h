#pragma once

#include <glm\glm.hpp>
#include "RegularZed.h"
#include "../../../Engine/AI/AI.h"
#include "../../../../ModularPathFinding/node.h"

#ifdef _DEBUG
	#define dprintf printf
#else
	#define dprintf __noop
#endif

namespace Atlamillia
{
	namespace RegularZed_States
	{
		class Idle : public AIState
		{
			public:
				void Update();

				Idle(StateManager* _parent)
				{
					parent_manager = _parent;
				}
		};

		class Patrol : public AIState
		{
			private:
				void MoveTowards(glm::vec2 _dst);

			public:
				void Update();

				Patrol(StateManager* _parent)
				{
					parent_manager = _parent;
				}
		};
	}
}