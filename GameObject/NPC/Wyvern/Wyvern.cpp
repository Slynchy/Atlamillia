#include "./Wyvern.h"
#include "../../../Engine/AI/AI.h"
#include "../../../Engine/AI/StateManager.h"
#include "../../../Engine/Graphics/Graphics.h"
#include <vector>
#include "../../../../ModularPathFinding/node.h"
#include "../../../Level/Level.h"
#include "../../../Atlamillia.h"

using namespace Atlamillia;

void Wyvern::Update()
{
	if (this->brain != nullptr) this->brain->Update();
	return;
}

void Wyvern::Draw(glm::vec2 offset, Atlamillia::Graphics::Renderer* rend)
{
	if (velocity.x != 0 && velocity.y != 0)
	{
		m_activeTexture = (*parent_level)->GetEngine()->GetResourceManager()->GetTexture("./gfx/wyvern_flying.png");
	}
	else
	{
		m_activeTexture = (*parent_level)->GetEngine()->GetResourceManager()->GetTexture("./gfx/wyvern.png");
	}

	glm::vec2 temp = this->pos;
	temp.x = std::round(temp.x);
	temp.y = std::round(temp.y);
	temp = Atlamillia::Iso::twoDToIso(temp);
	temp += offset;

	glm::vec2 temp2 = this->pos;
	temp2 = Atlamillia::Iso::twoDToIso(temp2);
	temp2 += offset;

	frame += (Atlamillia::Graphics::Renderer::DT * 0.001f) * 4.0f;
	if (frame > 8.0f)
		frame = 0;

	srcRect.x = int(0 + (256 * std::floor(frame)));
	srcRect.y = int(0 + (256 * m_direction));
	srcRect.w = 256;
	srcRect.h = 256;

	dstRect.x = int(temp2.x - ((256 * 1.5f) * 0.5f));
	dstRect.y = int(temp2.y - (256 * 1.5f));
	dstRect.w = int(256 * 1.5f);
	dstRect.h = int(256 * 1.5f);

	rend->RenderCopy(m_activeTexture, &srcRect, &dstRect);

	for (size_t i = 1; i < this->brain->GetPath()->size(); i++)
	{
		temp = Atlamillia::Iso::twoDToIso(this->brain->GetPath()->at(i).pos);
		temp += offset;
		temp2 = Atlamillia::Iso::twoDToIso(this->brain->GetPath()->at(i-1).pos);
		temp2 += offset;
		(rend)->RenderDrawLine(temp.x + 16, temp.y + 8, temp2.x + 16, temp2.y + 8);
	}
}

Wyvern::Wyvern(glm::ivec2 _startpos, Level** _parentlevel)
{
	pos = _startpos;
	parent_level = _parentlevel;
	ChangeTag("Wyvern");
	m_speed = 0.01f;
	m_activeTexture = (*parent_level)->GetEngine()->GetResourceManager()->GetTexture("./gfx/wyvern.png", (*parent_level)->GetEngine()->GetRenderer());
	flyingTexture = (*parent_level)->GetEngine()->GetResourceManager()->GetTexture("./gfx/wyvern_flying.png", (*parent_level)->GetEngine()->GetRenderer());
	drawOrder = 100;
}