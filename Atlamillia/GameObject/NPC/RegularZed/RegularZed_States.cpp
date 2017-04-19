#include "RegularZed_States.h"
#include "../../../Atlamillia.h"
#include "../../../Level/Level.h"
#include "../../../Engine/Graphics/Graphics.h"
#include "../../../../ModularPathFinding/BestFirst/BestFirst.h"
#include "../../../Engine/AI/LineOfSight.h"
#include "../SkeletonWarrior/SkeletonWarrior.h"

/// This function checks for duplicate positions in the path, in case it breaks
/// \param _path Pointer to vector of NODE objects
/// \return True if duplicate exists, false if not
bool CheckPathDuplicates(std::vector<NODE>* _path)
{
	for (size_t i = 0; i < _path->size(); i++)
	{
		for (size_t h = 0; h < _path->size(); h++)
		{
			if (i == h) continue;
			if (_path->at(i).pos.x == _path->at(h).pos.x)
			{
				if (_path->at(i).pos.y == _path->at(h).pos.y)
				{
					return true;
				}
			}
		}
	}
	return false;
}

void Atlamillia::RegularZed_States::Dead::Update()
{
	// He's dead, Jim.
	return;
}

void Atlamillia::RegularZed_States::Idle::Update()
{
	timer += Atlamillia::Graphics::Renderer::DT;

	LineOfSight LOS;
	bool CanSeePlayer = LOS.HasLineOfSight(this->parent_manager->parent->pos, playerptr->pos, (*this->parent_manager->parent->parent_level)->GetZone(0, 0)->m_nodemap, 8);
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
					(static_cast<RegularZed*>(this->parent_manager->parent)->GetWanderDistance() * 2)
				) - static_cast<RegularZed*>(this->parent_manager->parent)->GetWanderDistance()
			);
		int posY = 
			(
				(
					rand() %
					(static_cast<RegularZed*>(this->parent_manager->parent)->GetWanderDistance() * 2)
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

		if (this->parent_manager->GetPath()->size() != 0 && CheckPathDuplicates(this->parent_manager->GetPath()) == false)
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

	for each (GameObject* var in skeletons)
	{
		if (static_cast<NPC*>(var)->isAlive() == false)
		{
			continue;
		};
		if (glm::distance(var->pos, this->parent_manager->parent->pos) < 8)
		{
			LineOfSight LOS;
			bool CanSeeTarget = LOS.HasLineOfSight(this->parent_manager->parent->pos, var->pos, (*this->parent_manager->parent->parent_level)->GetZone(0, 0)->m_nodemap, 8);
			if(CanSeeTarget == true)
				return this->parent_manager->AddState(new Pursue(this->parent_manager, var));
		}
	}

	LineOfSight LOS;
	bool CanSeePlayer = LOS.HasLineOfSight(this->parent_manager->parent->pos, playerptr->pos, (*this->parent_manager->parent->parent_level)->GetZone(0, 0)->m_nodemap, 8);

	if (CanSeePlayer)
	{
		this->parent_manager->AddState(new Pursue(this->parent_manager, playerptr));
		return;
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

	if (target->Tag != "Player")
	{
		if (static_cast<NPC*>(target)->isAlive() == false)
		{
			return this->parent_manager->PopState();
		};
	}

	LineOfSight LOS;
	bool CanSeePlayer = LOS.HasLineOfSight(this->parent_manager->parent->pos, target->pos, (*this->parent_manager->parent->parent_level)->GetZone(0, 0)->m_nodemap, 8);

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
			(*this->parent_manager->parent->parent_level)->GetZone(0, 0)->m_nodemap,
			true
		);
	}

	this->parent_manager->UpdatePathPos();

	if (this->parent_manager->GetPathPos() == this->parent_manager->GetPath()->size() - 1)
	{
		this->parent_manager->parent->MoveTowards(target->pos);
		if (target->Tag == "SkeletonWarrior")
		{
			static_cast<SkeletonWarrior*>(target)->TakeDamage(10);
		}
	}
	else if(this->parent_manager->GetPath()->size() != 0)
	{
		this->parent_manager->parent->MoveTowards(this->parent_manager->GetPath()->at(this->parent_manager->GetPathPos() + 1).pos);
	}
}