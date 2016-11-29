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
					this->parent_manager->parent->Translate(temp);
				}

			public:
				void Update()
				{
					if (this->parent_manager->parent->parent_level == nullptr || *this->parent_manager->parent->parent_level == nullptr)
					{
						dprintf("[RegularZed_States] Zombie doesn't have valid level pointer for pathing!\n");
					}

					// If we're at the end of the path, generate a new one at a random place
					if ((this->parent_manager->GetPathPos() + 1) >= this->parent_manager->GetPath()->size())
					{
						this->parent_manager->GetPathAlgo()->path.clear();
						while (this->parent_manager->GetPathAlgo()->path.size() == 0)
						{
							this->parent_manager->DoPath(
								glm::ivec2(this->parent_manager->parent->pos.x, this->parent_manager->parent->pos.y),
								glm::ivec2(
									rand()%(*this->parent_manager->parent->parent_level)->GetZone(0, 0)->GetSize().x,
									rand()%(*this->parent_manager->parent->parent_level)->GetZone(0, 0)->GetSize().y
								),
								(*this->parent_manager->parent->parent_level)->GetZone(0,0)->m_nodemap,
								false
							);
						}
					};
					this->parent_manager->UpdatePathPos();
					MoveTowards(this->parent_manager->GetPath()->at(this->parent_manager->GetPathPos() + 1).pos);
				}

				Patrol(StateManager* _parent)
				{
					parent_manager = _parent;
				}
		};
	}
}