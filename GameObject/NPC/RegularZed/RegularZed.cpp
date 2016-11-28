#include "./RegularZed.h"
#include "../../../Engine/AI/AI.h"
#include "../../../Engine/AI/StateManager.h"
#include "../../../Engine/Graphics/Graphics.h"
#include <vector>
#include "../../../../ModularPathFinding/node.h"

using namespace Atlamillia;

void RegularZed::Update()
{
	if (this->brain->GetActiveState() != nullptr) this->brain->GetActiveState()->Update();
	return;

	// If we're at the end of the path, return
	if ((brain->GetPathPos() + 1) >= brain->GetPath()->size()) return;
	glm::vec2 temp(0, 0);
	if (pos.x < (float)brain->GetPath()->at(brain->GetPathPos() + 1).pos.x)
	{
		temp.x += m_speed;
	}
	else
	{
		temp.x -= m_speed;
	}
	if (pos.y < (float)brain->GetPath()->at(brain->GetPathPos() + 1).pos.y)
	{
		temp.y += m_speed;
	}
	else
	{
		temp.y -= m_speed;
	}
	this->Translate(temp.x, temp.y);
}

void RegularZed::Draw(Atlamillia::Graphics::Renderer* rend, glm::vec2 offset)
{
	glm::ivec2 temp = Atlamillia::Iso::twoDToIso(this->pos);
	temp += offset;
	temp -= glm::vec2(8, 8);
	rend->RenderDrawLine(temp.x, temp.y + 16, temp.x + 32, temp.y);
	rend->RenderDrawLine(temp.x + 32, temp.y, temp.x + 64, temp.y + 16);
	rend->RenderDrawLine(temp.x + 64, temp.y + 16, temp.x + 32, temp.y + 32);
	rend->RenderDrawLine(temp.x + 32, temp.y + 32, temp.x, temp.y + 16);
}