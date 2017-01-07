#include "NPC.h"

void Atlamillia::NPC::MoveTowards(glm::vec2 _dst)
{
	glm::vec2 velocity(0, 0);
	if (pos.x < _dst.x)
	{
		velocity.x += this->m_speed;
	}
	else
	{
		velocity.x -= m_speed;
	}
	if (pos.y < _dst.y)
	{
		velocity.y += m_speed;
	}
	else
	{
		velocity.y -= m_speed;
	}

	this->velocity = velocity;

	Translate(velocity.x, velocity.y);

	glm::vec2 rounder = _dst - pos;
	rounder *= 10;
	rounder.x = std::round(rounder.x);
	rounder.y = std::round(rounder.y);
	rounder *= 0.10f;
	m_direction = GetDirectionFromDelta(rounder);
}

void Atlamillia::NPC::Kill()
{
	// Pop all states
	while (this->brain->GetActiveState() != nullptr)
		this->brain->PopState();

	// Set alive status to not alive
	m_isAlive = false;
}