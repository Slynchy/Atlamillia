#include "Player.h"
#include "../../Engine/Isometry/Isometry.h"
#include "../../Engine/InputManager.h"
#include "../../Level/Level.h"

void Atlamillia::Player::Update(InputManager* _iman)
{
	movement = glm::vec2(0, 0);
	if(HandleInput(_iman))
		Translate(movement.x, movement.y, (*this->parent_level)->GetLevelProps());
}

bool Atlamillia::Player::HandleInput(InputManager* _iman)
{
	bool input = false;
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
	frame += 0.022f * Atlamillia::Graphics::Renderer::DT;
	if (frame >= 15.0f)
		frame = 0.0f;
	srcRect.w = 105;
	srcRect.h = 127;
	srcRect.x = int(srcRect.w * std::floor(frame));
	dstRect.w = int(srcRect.w * 0.66f);
	dstRect.h = int(srcRect.h * 0.66f);

	glm::vec2 temp = Iso::twoDToIso(pos);
	temp += _offset;
	dstRect.x = int((temp.x) - 8);
	dstRect.y = int((temp.y) - (dstRect.h - 24));

	_rend->RenderCopy(texture, &srcRect, &dstRect);
}