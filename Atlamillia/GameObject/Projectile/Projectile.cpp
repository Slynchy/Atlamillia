#include "Projectile.h"
#include "../../Engine/ResourceManager.h"
#include "../../Atlamillia.h"
#include "../FiniteAnimation.h"
#include "../NPC/RegularZed/RegularZed.h"
#include "../NPC/SkeletonWarrior/SkeletonWarrior.h"

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

	frame += (Atlamillia::Graphics::Renderer::DT * 0.012f);
	if (frame > 7.0f)
		frame = 0;

	srcRect.x = int(0 + (64 * std::floor(frame)));
	srcRect.y = int(0 + (64 * m_direction));
	srcRect.w = 64;
	srcRect.h = 64;

	dstRect.x = int((temp2.x ) + this->offset.x);
	dstRect.y = int((temp2.y - (32 * 1.5f)) + this->offset.y);
	dstRect.w = int(64 * 1.5f);
	dstRect.h = int(64 * 1.5f);

	rend->RenderCopy(m_activeTexture, &srcRect, &dstRect);
}

void Projectile::Update()
{
	this->pos = Atlamillia::Engine::interpolate(this->pos, target, 0.004f);
	offset = Atlamillia::Engine::interpolate(offset, glm::vec2(0,0), 0.004f);

	if (glm::distance(this->pos, glm::vec2(target)) < 1.0f)
	{
		FiniteAnimation* temp = new FiniteAnimation(
			this->pos,
			rsrc->GetTexture("./gfx/explosion.png"),
			glm::ivec2(96, 96), 
			19);

		size_t zombieHash = std::hash<std::string>{}("RegularZombie");
		size_t skeleHash = std::hash<std::string>{}("SkeletonWarrior");
		for each (GameObject* var in GameObject::SceneGraph)
		{
			if (glm::distance(var->pos, this->pos) < 3.0f)
			{
				if (var->TagHash == zombieHash)
				{
					static_cast<Atlamillia::RegularZed*>(var)->Kill();
				}
				else if (var->TagHash == skeleHash)
				{
					static_cast<Atlamillia::SkeletonWarrior*>(var)->Kill();
				}
			}
		}

		return delete this;
	}
}

Projectile::Projectile(glm::ivec2 _target, ResourceManager* _rsrc, glm::vec2 _offset)
{
	ChangeTag("Projectile");
	target = _target;
	rsrc = _rsrc;
	m_activeTexture = _rsrc->GetTexture("./gfx/fireball/fireball_0.png");
	this->LookAt(_target);
	offset = _offset;
}