#include "Projectile.h"
#include "../../Engine/ResourceManager.h"
#include "../../Atlamillia.h"

using namespace Atlamillia;

void Projectile::Draw(glm::vec2 offset, Atlamillia::Graphics::Renderer* rend)
{
	glm::vec2 temp = this->pos;
	temp.x = std::round(temp.x);
	temp.y = std::round(temp.y);
	temp = Atlamillia::Iso::twoDToIso(temp);
	temp += offset;

	glm::vec2 temp2 = this->pos;
	temp2 = Atlamillia::Iso::twoDToIso(temp2);
	temp2 += offset;

	frame += (Atlamillia::Graphics::Renderer::DT * 0.004f);
	if (frame > 7.0f)
		frame = 0;

	srcRect.x = int(0 + (64 * std::floor(frame)));
	srcRect.y = int(0 + (64 * m_direction));
	srcRect.w = 64;
	srcRect.h = 64;

	dstRect.x = int(temp2.x - ((64 * 1.5f) * 0.5f));
	dstRect.y = int(temp2.y - (64 * 1.5f));
	dstRect.w = int(64 * 1.5f);
	dstRect.h = int(64 * 1.5f);

	rend->RenderCopy(m_activeTexture, &srcRect, &dstRect);
}

void Projectile::Update()
{
	this->pos = Atlamillia::Engine::interpolate(this->pos, target, 0.001f);

	if (glm::distance(this->pos, glm::vec2(target)) < 0.25f)
	{
		return delete this;
	}
}

Projectile::Projectile(glm::ivec2 _target, ResourceManager* rsrc)
{
	ChangeTag("Projectile");
	target = _target;
	m_activeTexture = rsrc->GetTexture("./gfx/fireball/fireball_0.png");
	m_direction = GetDirectionFromDelta( glm::vec2(_target) - this->pos );
}