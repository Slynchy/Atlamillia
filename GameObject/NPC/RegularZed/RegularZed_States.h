#pragma once

#include "../../../Engine/AI/AI.h"

namespace Atlamillia
{
	namespace RegularZed_States
	{
		class Idle : public AIState
		{
			public:
				void Update()
				{

				};

				Idle(StateManager* _parent)
				{
					parent_manager = _parent;
				}
		};

		class Patrol : public AIState
		{
			private:
				void MoveTowards(glm::vec2 _dst)
				{
					float speed = dynamic_cast<RegularZed*>(this->parent_manager->parent)->GetSpeed();
					glm::vec2 temp(0, 0);
					if (this->parent_manager->parent->pos.x < _dst.x)
					{
						temp.x += speed;
					}
					else
					{
						temp.x -= speed;
					}
					if (this->parent_manager->parent->pos.y < _dst.y)
					{
						temp.y += speed;
					}
					else
					{
						temp.y -= speed;
					}
					this->parent_manager->parent->Translate(temp.x, temp.y);
				}

			public:
				void Update()
				{
					// If we're at the end of the path, return
					if ((this->parent_manager->GetPathPos() + 1) >= this->parent_manager->GetPath()->size()) return;
					MoveTowards(this->parent_manager->GetPath()->at(this->parent_manager->GetPathPos() + 1).pos);
				}

				Patrol(StateManager* _parent)
				{
					parent_manager = _parent;
				}
		};
	}
}