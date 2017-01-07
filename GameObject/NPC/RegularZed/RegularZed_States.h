#pragma once

#include <glm\glm.hpp>
#include "RegularZed.h"
#include "../../../Engine/AI/AI.h"
#include "../../../../ModularPathFinding/node.h"
#include "../../../Level/Level.h"
#include "../../../Engine/Graphics/Debug.h"
#include "../../../Atlamillia.h"
#include "../../../Engine/ResourceManager.h"

namespace Atlamillia
{
	namespace RegularZed_States
	{
		
		/// Idle state; waits a bit then pathfinds randomly via Patrol state
		class Idle : public AIState
		{
			private:
				/// Current timer until moving
				Uint32 timer = 0;

				/// Time limit until moving
				Uint32 timetowait = 0;

				/// Pointer to the player
				/// Not necessary anymore, really..
				GameObject* playerptr;
			public:
				void Update();

				Idle(StateManager* _parent)
				{
					parent_manager = _parent;
					timetowait = (rand() % 2000) + 1000; // 1 to 3 seconds
					playerptr = nullptr;

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

		/// Dead state; does absolutely nothing
		class Dead : public AIState
		{
		private:
		public:
			void Update();

			Dead(StateManager* _parent)
			{
				_parent->parent->SetTexture( (*_parent->parent->parent_level)->GetEngine()->GetResourceManager()->GetTexture("./gfx/zombie_dead.png") );
			}
		};

		/// Patrol state; follows its path, checking for enemies along the way
		class Patrol : public AIState
		{
			private:
				GameObject* playerptr;

				/// Array of pointers to all skeletons in level
				std::vector<GameObject*> skeletons;
			public:
				void Update();

				Patrol(StateManager* _parent, GameObject* _player)
				{
					parent_manager = _parent;
					playerptr = _player;
					size_t skeletonHash = std::hash<std::string>{}("SkeletonWarrior");
					for each (GameObject* var in GameObject::SceneGraph)
					{
						if (var->TagHash == skeletonHash)
						{
							skeletons.push_back(var);
						}
						else continue;
					}
				}
		};

		/// Pursue state; pathfinds towards target and deals damage if within range
		class Pursue : public AIState
		{
			private:
				/// Pointer to target to pursue
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
	}
}