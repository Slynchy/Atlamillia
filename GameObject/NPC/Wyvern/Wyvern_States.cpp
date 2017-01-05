#include "Wyvern_States.h"
#include "../../../Atlamillia.h"
#include "../../../Level/Level.h"
#include "../../../Engine/Graphics/Graphics.h"
#include "../../../../ModularPathFinding/BestFirst/BestFirst.h"
#include "../../../Engine/AI/LineOfSight.h"
#include "../../Projectile/Projectile.h"

void Atlamillia::Wyvern_States::Idle::Update()
{
	timer += Atlamillia::Graphics::Renderer::DT;
	this->parent_manager->parent->velocity = glm::vec2(0,0);

	LineOfSight LOS;
	bool CanSeePlayer = LOS.HasLineOfSight(this->parent_manager->parent->pos, playerptr->pos, std::vector<std::vector<NODE*>>(), 9);
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
	bool CanSeePlayer = LOS.HasLineOfSight(this->parent_manager->parent->pos, playerptr->pos, std::vector<std::vector<NODE*>>(), 9);

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
		dprintf("[Wyvern_States] Wyvern doesn't have valid level pointer for pathing!\n");
		return;
	}
	if (target == nullptr)
	{
		dprintf("[Wyvern_States] Wyvern has no target to pursue!\n");
		return;
	}

	LineOfSight LOS;
	bool CanSeePlayer = LOS.HasLineOfSight(this->parent_manager->parent->pos, target->pos, std::vector<std::vector<NODE*>>(), 9);

	// Since it can see the player, the pathfinder is quick; plus the Wyvern has no obstacles
	if (!CanSeePlayer)
	{
		return this->parent_manager->PopState();
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

	if ( glm::distance(this->parent_manager->parent->pos, target->pos) < 10.0f )
	{
		this->parent_manager->AddState(new Attack(this->parent_manager, target));
	}

	if (this->parent_manager->GetPathPos() == this->parent_manager->GetPath()->size() - 1)
	{
		this->parent_manager->parent->MoveTowards(target->pos);
	}
	else if(this->parent_manager->GetPath()->size() != 0)
	{
		this->parent_manager->parent->MoveTowards(this->parent_manager->GetPath()->at(this->parent_manager->GetPathPos() + 1).pos);
	}
}

void Atlamillia::Wyvern_States::Attack::Update()
{

	//this->parent_manager->parent->LookAt(this->target->pos);
	//this->parent_manager->parent->SetTexture((*this->parent_manager->parent->parent_level)->GetEngine()->GetResourceManager()->GetTexture("./gfx/wyvern.png"));

	this->parent_manager->parent->velocity = glm::vec2(0, 0);
	if (timer > 1000) // 1 second? Maybe?
	{
		Projectile* projectile = new Projectile(this->target->pos,(*this->parent_manager->parent->parent_level)->GetEngine()->GetResourceManager(), glm::vec2(0,-192));
		projectile->pos = this->parent_manager->parent->pos;
		return this->parent_manager->PopState();
	}
	else
		timer += Atlamillia::Graphics::Renderer::DT;
}