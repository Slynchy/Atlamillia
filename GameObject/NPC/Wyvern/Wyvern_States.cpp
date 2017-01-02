#include "Wyvern_States.h"
#include "../../../Atlamillia.h"
#include "../../../Level/Level.h"
#include "../../../Engine/Graphics/Graphics.h"
#include "../../../../ModularPathFinding/BestFirst/BestFirst.h"
#include "../../../Engine/AI/LineOfSight.h"

void Atlamillia::Wyvern_States::Idle::Update()
{
	timer += Atlamillia::Graphics::Renderer::DT;
	this->parent_manager->parent->velocity = glm::vec2(0,0);

	LineOfSight LOS;
	bool CanSeePlayer = LOS.HasLineOfSight(this->parent_manager->parent->pos, playerptr->pos, std::vector<std::vector<NODE*>>(), 12);
	if (CanSeePlayer)
	{
		this->parent_manager->AddState(new Pursue(this->parent_manager, playerptr));
		return;
	}

	if (timer >= timetowait)
	{
		this->parent_manager->GetPathAlgo()->path.clear();

		int posX =
			(
				(
					rand() %
					static_cast<Wyvern*>(this->parent_manager->parent)->GetWanderDistance() * 2
				) - static_cast<Wyvern*>(this->parent_manager->parent)->GetWanderDistance()
			);
		int posY = 
			(
				(
					rand() %
					static_cast<Wyvern*>(this->parent_manager->parent)->GetWanderDistance() * 2
				) - static_cast<Wyvern*>(this->parent_manager->parent)->GetWanderDistance()
			);

		this->parent_manager->DoPath(
			glm::ivec2(this->parent_manager->parent->pos.x, this->parent_manager->parent->pos.y),
			glm::ivec2(
				this->parent_manager->parent->pos.x + posX,
				this->parent_manager->parent->pos.y + posY
			),
			std::vector<std::vector<NODE*>>(),
			true
		);

		if (this->parent_manager->GetPathAlgo()->path.size() != 0)
		{
			this->parent_manager->AddState(new Patrol(this->parent_manager, playerptr));
		}
		timer = 0;
	};
};

void Atlamillia::Wyvern_States::Patrol::Update()
{
	if (this->parent_manager->parent->parent_level == nullptr || *this->parent_manager->parent->parent_level == nullptr)
	{
		dprintf("[RegularZed_States] Zombie doesn't have valid level pointer for pathing!\n");
		return;
	}

	if ((this->parent_manager->GetPathPos() + 1) >= this->parent_manager->GetPath()->size())
	{
		this->parent_manager->PopState();
		return;
	};

	LineOfSight LOS;
	bool CanSeePlayer = LOS.HasLineOfSight(this->parent_manager->parent->pos, playerptr->pos, std::vector<std::vector<NODE*>>(), 12);

	if (CanSeePlayer)
	{
		this->parent_manager->AddState(new Pursue(this->parent_manager, playerptr));
		return;
	}

	this->parent_manager->UpdatePathPos();
	this->parent_manager->parent->MoveTowards(this->parent_manager->GetPath()->at(this->parent_manager->GetPathPos() + 1).pos);
}

void Atlamillia::Wyvern_States::Pursue::Update()
{
	if (this->parent_manager->parent->parent_level == nullptr || *this->parent_manager->parent->parent_level == nullptr)
	{
		dprintf("[RegularZed_States] Zombie doesn't have valid level pointer for pathing!\n");
		return;
	}
	if (target == nullptr)
	{
		dprintf("[RegularZed_States] Zombie has no target to pursue!\n");
		return;
	}

	LineOfSight LOS;
	bool CanSeePlayer = LOS.HasLineOfSight(this->parent_manager->parent->pos, target->pos, std::vector<std::vector<NODE*>>(), 12);

	if (!CanSeePlayer)
	{
		this->parent_manager->PopState();
		return;
	}
	else
	{
		this->parent_manager->DoPath(
			glm::ivec2(this->parent_manager->parent->pos.x, this->parent_manager->parent->pos.y),
			target->pos,
			std::vector<std::vector<NODE*>>(),
			true
		);
	}

	this->parent_manager->UpdatePathPos();

	if (this->parent_manager->GetPathPos() == this->parent_manager->GetPath()->size() - 1)
	{
		this->parent_manager->parent->MoveTowards(target->pos);
	}
	else if(this->parent_manager->GetPath()->size() != 0)
	{
		this->parent_manager->parent->MoveTowards(this->parent_manager->GetPath()->at(this->parent_manager->GetPathPos() + 1).pos);
	}
}