#include "RegularZed_States.h"
#include "../../../Level/Level.h"
#include "../../../Engine/Graphics/Graphics.h"

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
			false
		);

		if (this->parent_manager->GetPathAlgo()->path.size() != 0)
		{
			this->parent_manager->AddState(new Patrol(this->parent_manager));
		}
		timer = 0;
	};
};

void Atlamillia::RegularZed_States::Patrol::MoveTowards(glm::vec2 _dst)
{
	float speed = static_cast<RegularZed*>(this->parent_manager->parent)->GetSpeed();
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

void Atlamillia::RegularZed_States::Patrol::Update()
{
	if (this->parent_manager->parent->parent_level == nullptr || *this->parent_manager->parent->parent_level == nullptr)
	{
		dprintf("[RegularZed_States] Zombie doesn't have valid level pointer for pathing!\n");
	}

	if ((this->parent_manager->GetPathPos() + 1) >= this->parent_manager->GetPath()->size())
	{
		this->parent_manager->PopState();
		return;
	};

	this->parent_manager->UpdatePathPos();
	MoveTowards(this->parent_manager->GetPath()->at(this->parent_manager->GetPathPos() + 1).pos);
}