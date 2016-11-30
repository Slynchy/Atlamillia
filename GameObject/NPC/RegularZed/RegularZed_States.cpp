#include "RegularZed_States.h"
#include "../../../Atlamillia.h"
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
			true
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
	//this->parent_manager->parent->m_direction = this->parent_manager->parent->GetDirectionFromDelta(temp);
	//this->parent_manager->parent->pos.x = Atlamillia::Engine::interpolate(this->parent_manager->parent->pos.x, _dst.x, speed * 0.33f);
	//this->parent_manager->parent->pos.y = Atlamillia::Engine::interpolate(this->parent_manager->parent->pos.y, _dst.y, speed * 0.33f);

	//temp.x -= this->parent_manager->parent->pos.x;
	//temp.y -= this->parent_manager->parent->pos.y;
	//this->parent_manager->parent->pos += glm::vec2(temp.x, temp.y);

	this->parent_manager->parent->Translate(temp.x, temp.y);

	glm::vec2 anus = _dst - this->parent_manager->parent->pos;
	anus *= 10;
	anus.x = std::round(anus.x);
	anus.y = std::round(anus.y);
	anus /= 10;

	this->parent_manager->parent->m_direction = this->parent_manager->parent->GetDirectionFromDelta(anus);
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