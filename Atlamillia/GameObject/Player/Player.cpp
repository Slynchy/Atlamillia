#include "Player.h"
#include "../../Engine/Isometry/Isometry.h"
#include "../../Engine/InputManager.h"
#include "../../Level/Level.h"
#include "../../Atlamillia.h"
#include "../NPC/RegularZed/RegularZed.h"

void Atlamillia::Player::Update(InputManager* _iman)
{
	movement = glm::vec2(0, 0);
	if(HandleInput(_iman))
		Translate(movement.x, movement.y, (*this->parent_level)->GetLevelProps());

	if (isAttacking)
	{
		std::vector<GameObject*> closeObjects = GameObject::GetCloseObjects(this->pos, 25, "RegularZombie");

		for each (GameObject* var in closeObjects)
		{
			bool hit = false;
			if (glm::ivec2(var->pos) == glm::ivec2(this->pos))
				hit = true;
			else
			{
				switch (m_direction)
				{
				case DIRECTIONS::SOUTH:
					if (
						glm::ivec2(var->pos) == glm::ivec2(this->pos.x + 1, this->pos.y + 1) ||
						glm::ivec2(var->pos) == glm::ivec2(this->pos.x - 1, this->pos.y + 1) ||
						glm::ivec2(var->pos) == glm::ivec2(this->pos.x, this->pos.y + 1)
						)
					{
						hit = true;
					}
					break;
				case DIRECTIONS::NORTH:
					if (
						glm::ivec2(var->pos) == glm::ivec2(this->pos.x + 1, this->pos.y - 1) ||
						glm::ivec2(var->pos) == glm::ivec2(this->pos.x - 1, this->pos.y - 1) ||
						glm::ivec2(var->pos) == glm::ivec2(this->pos.x, this->pos.y - 1)
						)
					{
						hit = true;
					}
					break;
				case DIRECTIONS::EAST:
					if (
						glm::ivec2(var->pos) == glm::ivec2(this->pos.x + 1, this->pos.y - 1) ||
						glm::ivec2(var->pos) == glm::ivec2(this->pos.x + 1, this->pos.y) ||
						glm::ivec2(var->pos) == glm::ivec2(this->pos.x + 1, this->pos.y + 1)
						)
					{
						hit = true;
					}
					break;
				case DIRECTIONS::WEST:
					if (
						glm::ivec2(var->pos) == glm::ivec2(this->pos.x - 1, this->pos.y - 1) ||
						glm::ivec2(var->pos) == glm::ivec2(this->pos.x - 1, this->pos.y) ||
						glm::ivec2(var->pos) == glm::ivec2(this->pos.x - 1, this->pos.y + 1)
						)
					{
						hit = true;
					}
					break;
				}
			}

			if (hit == true)
			{
				if (var->Tag == "RegularZombie")
				{
					static_cast<RegularZed*>(var)->Kill();
				}
			}
		}
	}
}

bool Atlamillia::Player::HandleInput(InputManager* _iman)
{
	bool input = false;
	if (_iman->KeyDown(Atlamillia::InputManager::BUTTONS::SPACE) && isAttacking == false)
	{
		isAttacking = true;
		frame = 0;
		return false;
	}
	if (isAttacking == true) return false;
	if (_iman->KeyDown(Atlamillia::InputManager::BUTTONS::UP))
	{
		movement.y += -0.05f * Atlamillia::Graphics::Renderer::DT;
		movement.x += -0.05f * Atlamillia::Graphics::Renderer::DT;
		input = true;
	}
	if (_iman->KeyDown(Atlamillia::InputManager::BUTTONS::LEFT))
	{
		movement.x += -0.05f * Atlamillia::Graphics::Renderer::DT;
		movement.y += 0.05f * Atlamillia::Graphics::Renderer::DT;
		input = true;
	}
	if (_iman->KeyDown(Atlamillia::InputManager::BUTTONS::DOWN))
	{
		movement.y += 0.05f * Atlamillia::Graphics::Renderer::DT;
		movement.x += 0.05f * Atlamillia::Graphics::Renderer::DT;
		input = true;
	}
	if (_iman->KeyDown(Atlamillia::InputManager::BUTTONS::RIGHT))
	{
		movement.x += 0.05f * Atlamillia::Graphics::Renderer::DT;
		movement.y += -0.05f * Atlamillia::Graphics::Renderer::DT;
		input = true;
	}
	return input;
}

void Atlamillia::Player::Draw(Atlamillia::Graphics::Renderer* _rend, glm::vec2 _viewportPos, glm::vec2 _viewportSize)
{
	frame += 0.022f * Atlamillia::Graphics::Renderer::DT;
	if (frame >= 15.0f)
		frame = 0.0f;
	srcRect.w = 105;
	srcRect.h = 127;
	srcRect.x = int(srcRect.w * std::floor(frame));
	dstRect.w = int(srcRect.w * 0.66f);
	dstRect.h = int(srcRect.h * 0.66f);

	glm::vec2 temp = pos;
	temp += _viewportPos;
	temp += (_viewportSize * 0.5f);
	dstRect.x = int((temp.x) - 8);
	dstRect.y = int((temp.y) - (dstRect.h - 24));

	_rend->RenderCopy(texture, &srcRect, &dstRect);
}

void Atlamillia::Player::Draw(glm::vec2 _offset, Atlamillia::Graphics::Renderer* _rend)
{
	bool walking = false;

	if (isAttacking)
	{
		m_activeTexture = (*parent_level)->GetEngine()->GetResourceManager()->GetTexture("./gfx/skeleton_0_attack.png");
	}
	else
	{
		if (movement.x != 0 || movement.y != 0)
		{
			m_activeTexture = (*parent_level)->GetEngine()->GetResourceManager()->GetTexture("./gfx/skeleton_0_walk.png");
			walking = true;
		}
		else
		{
			m_activeTexture = (*parent_level)->GetEngine()->GetResourceManager()->GetTexture("./gfx/skeleton_0.png");
		}
	}

	glm::vec2 temp = this->pos;
	temp.x = std::round(temp.x);
	temp.y = std::round(temp.y);
	temp = Atlamillia::Iso::twoDToIso(temp);
	temp += _offset;

	glm::vec2 temp2 = this->pos;
	temp2 = Atlamillia::Iso::twoDToIso(temp2);
	temp2 += _offset;

	if (walking)
	{
		frame += (Atlamillia::Graphics::Renderer::DT * 0.001f) * 4.0f;
		if (frame > 8.0f)
			frame = 0;
	}
	else
	{
		if (isAttacking == true)
		{
			frame += (Atlamillia::Graphics::Renderer::DT * 0.008f);
			if (frame > 4.0f)
			{
				frame = 0; 
				isAttacking = false;
			}
		}
		else
		{
			frame += (Atlamillia::Graphics::Renderer::DT * 0.001f) * 4.0f;
			if (frame > 4.0f)
			{
				frame = 0;
			}
		}
	}

	srcRect.x = int(0 + (128 * std::floor(frame)));
	srcRect.y = int(0 + (128 * m_direction));
	srcRect.w = 128;
	srcRect.h = 128;

	dstRect.x = int(temp2.x - ((128 * 1.5f) * 0.5f));
	dstRect.y = int(temp2.y - (128));
	dstRect.w = int(128 * 1.5f);
	dstRect.h = int(128 * 1.5f);

	_rend->RenderCopy(m_activeTexture, &srcRect, &dstRect);
}