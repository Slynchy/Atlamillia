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

void SkeletonWarrior_States::Patrol::Update()
{
	if (this->parent_manager->parent->parent_level == nullptr || *this->parent_manager->parent->parent_level == nullptr)
	{
		dprintf("[SkeletonWarrior_States] Skeleton doesn't have valid level pointer for pathing!\n");
		return;
	}

	// If reached end of path, pop state
	if ((this->parent_manager->GetPathPos() + 1) >= this->parent_manager->GetPath()->size())
	{
		this->parent_manager->PopState();
		return;
	};

	// Else, continue along path
	this->parent_manager->UpdatePathPos();
	this->parent_manager->parent->MoveTowards(this->parent_manager->GetPath()->at(this->parent_manager->GetPathPos() + 1).pos);
}