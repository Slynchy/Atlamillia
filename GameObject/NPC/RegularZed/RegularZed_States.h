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
			private:
				Uint32 timer = 0;
				Uint32 timetowait = 0;
			public:
				void Update();

				Idle(StateManager* _parent)
				{
					parent_manager = _parent;
					timetowait = (rand() % 2000) + 1000; // 1 to 3 seconds
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