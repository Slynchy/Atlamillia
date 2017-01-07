#include "SkeletonWarrior_States.h"
#include "../../../Engine/AI/LineOfSight.h"

using namespace Atlamillia;

void SkeletonWarrior_States::Idle::Update()
{
	this->parent_manager->GetPathAlgo()->path.clear();
	int posX =
		(
		(
			rand() %
			25 * 2
			) - 25
			);
	int posY =
		(
		(
			rand() %
			25 * 2
			) - 25
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
	this->parent_manager->AddState(new Patrol(parent_manager));
}

SkeletonWarrior_States::Idle::Idle(StateManager* _parent)
{
	parent_manager = _parent;
}

void SkeletonWarrior_States::Hunt::Update()
{
	if (target == nullptr) return this->parent_manager->PopState();
	if (static_cast<RegularZed*>(target)->isAlive() == false) return this->parent_manager->PopState();

	this->parent_manager->DoPath(
		glm::ivec2(this->parent_manager->parent->pos.x, this->parent_manager->parent->pos.y),
		target->pos,
		(*this->parent_manager->parent->parent_level)->GetZone(0, 0)->m_nodemap,
		true
	);

	this->parent_manager->UpdatePathPos();

	if (glm::distance(target->pos, this->parent_manager->parent->pos) < 2.0f)
		return this->parent_manager->AddState(new Attack(this->parent_manager, target));

	if (this->parent_manager->GetPathPos() == this->parent_manager->GetPath()->size() - 1)
	{
		this->parent_manager->parent->MoveTowards(target->pos);
	} 
	else if (this->parent_manager->GetPath()->size() != 0)
	{
		this->parent_manager->parent->MoveTowards(this->parent_manager->GetPath()->at(this->parent_manager->GetPathPos() + 1).pos);
	}
}

void SkeletonWarrior_States::Patrol::Update()
{
	if (this->parent_manager->parent->parent_level == nullptr || *this->parent_manager->parent->parent_level == nullptr)
	{
		dprintf("[SkeletonWarrior_States] Skeleton doesn't have valid level pointer for pathing!\n");
		return;
	}

	// Get close objects
	std::vector<GameObject*> closeObjects = GameObject::GetCloseObjects(this->parent_manager->parent->pos, 55, "RegularZombie");
	for (size_t i = 0; i < closeObjects.size(); i++)
	{
		if (static_cast<RegularZed*>(closeObjects.at(i))->isAlive() == false)
		{
			closeObjects.erase(closeObjects.begin() + i);
			i--;
		}
	}
	if (closeObjects.size() != 0)
	{
		GameObject* closest = closeObjects.front();
		if (closeObjects.size() != 1)
		{
			for (size_t i = 1; i < closeObjects.size(); i++)
			{
				if (glm::distance(closeObjects.at(i)->pos, this->parent_manager->parent->pos) < glm::distance(closest->pos, this->parent_manager->parent->pos))
				{
					closest = closeObjects.at(i);
				}
			}
		}
		//hunt down closest
		return this->parent_manager->AddState(new SkeletonWarrior_States::Hunt(this->parent_manager, closest));
	};

	// If reached end of path, pop state
	if ((this->parent_manager->GetPathPos() + 1) >= this->parent_manager->GetPath()->size())
	{
		return this->parent_manager->PopState();
	};

	// Else, continue along path
	this->parent_manager->UpdatePathPos();
	this->parent_manager->parent->MoveTowards(this->parent_manager->GetPath()->at(this->parent_manager->GetPathPos() + 1).pos);
}

void SkeletonWarrior_States::Attack::Update()
{
	if (this->parent_manager->parent->IsAttacking() == false)
	{
		static_cast<RegularZed*>(target)->Kill();
		return this->parent_manager->PopState();
	}
}

void SkeletonWarrior_States::Dead::Update()
{
	printf("");
}