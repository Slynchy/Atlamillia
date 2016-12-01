#include "RegularZed_States.h"
#include "../../../Atlamillia.h"
#include "../../../Level/Level.h"
#include "../../../Engine/Graphics/Graphics.h"
#include "../../../../ModularPathFinding/BestFirst/BestFirst.h"

void Atlamillia::RegularZed_States::Idle::Update()
{
	timer += Atlamillia::Graphics::Renderer::DT;

	if (timer >= timetowait)
	{
		this->parent_manager->GetPathAlgo()->path.clear();

		int posX =
			(
				(
					rand() %
					static_cast<RegularZed*>(this->parent_manager->parent)->GetWanderDistance() * 2
				) - static_cast<RegularZed*>(this->parent_manager->parent)->GetWanderDistance()
			);
		int posY = 
			(
				(
					rand() %
					static_cast<RegularZed*>(this->parent_manager->parent)->GetWanderDistance() * 2
				) - static_cast<RegularZed*>(this->parent_manager->parent)->GetWanderDistance()
			);

		this->parent_manager->DoPath(
			glm::ivec2(this->parent_manager->parent->pos.x, this->parent_manager->parent->pos.y),
			glm::ivec2(
				this->parent_manager->parent->pos.x + posX,
				this->parent_manager->parent->pos.y + posY
			),
			(*this->parent_manager->parent->parent_level)->GetZone(0, 0)->m_nodemap,
			true
		);

		if (this->parent_manager->GetPathAlgo()->path.size() != 0)
		{
			this->parent_manager->AddState(new Patrol(this->parent_manager, playerptr));
		}
		timer = 0;
	};
};

void Atlamillia::RegularZed_States::Patrol::Update()
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

	if (glm::distance(this->parent_manager->parent->pos, playerptr->pos) < 5.0f)
	{
		PathAlgorithms::BestFirst* bstfst = new PathAlgorithms::BestFirst();
		bstfst->GeneratePath(this->parent_manager->parent->pos, playerptr->pos, (*this->parent_manager->parent->parent_level)->GetZone(0, 0)->m_nodemap, true);
		if (bstfst->path.size() < 6)
		{
			delete bstfst;
			this->parent_manager->AddState(new Pursue(this->parent_manager, playerptr));
			return;
		}
		delete bstfst;
	}

	this->parent_manager->UpdatePathPos();
	this->parent_manager->parent->MoveTowards(this->parent_manager->GetPath()->at(this->parent_manager->GetPathPos() + 1).pos);
}

void Atlamillia::RegularZed_States::Pursue::Update()
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

	if (glm::distance(this->parent_manager->parent->pos, target->pos) > 5.0f)
	{
		this->parent_manager->PopState();
		return;
	}

	//this->parent_manager->UpdatePathPos();
	this->parent_manager->parent->MoveTowards(target->pos);
}