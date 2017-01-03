#pragma once

#include <glm\glm.hpp>
#include "Wyvern.h"
#include "../../../Engine/AI/AI.h"
#include "../../../../ModularPathFinding/node.h"
#include "../../../Level/Level.h"
#include "../../../Engine/Graphics/Debug.h"

namespace Atlamillia
{
	namespace Wyvern_States
	{
		class Idle : public AIState
		{
			private:
				Uint32 timer = 0;
				Uint32 timetowait = 0;
				GameObject* playerptr;
			public:
				void Update();

				Idle(StateManager* _parent)
				{
					parent_manager = _parent;
					timetowait = (rand() % 2000) + 1000; // 1 to 3 seconds
					
					std::size_t playerHash = std::hash<std::string>{}("Player");
					for (size_t i = 0; i < GameObject::SceneGraph.size(); i++)
					{
						if (GameObject::SceneGraph.at(i)->TagHash == playerHash)
						{
							playerptr = GameObject::SceneGraph.at(i);
							break;
						}
					}
				}
		};

		class Patrol : public AIState
		{
			private:
				GameObject* playerptr;
			public:
				void Update();

				Patrol(StateManager* _parent, GameObject* _player)
				{
					parent_manager = _parent;
					playerptr = _player;
				}
		};

		class Pursue : public AIState
		{
			private:
				GameObject* target = nullptr;
			protected:
			public:

				void Update();

				Pursue(StateManager* _parent, GameObject* _target)
				{
					parent_manager = _parent;
					target = _target;
					this->parent_manager->DoPath(
						glm::ivec2(this->parent_manager->parent->pos.x, this->parent_manager->parent->pos.y),
						target->pos,
						(*this->parent_manager->parent->parent_level)->GetZone(0, 0)->m_nodemap,
						true
					);
				}
		};

		class Attack : public AIState
		{
		private:
			GameObject* target;

			int timer;
		protected:
		public:

			void Update();

			Attack(StateManager* _parent, GameObject* _target)
			{
				parent_manager = _parent;
				target = _target;
				timer = 0;
			}
		};
	}
}