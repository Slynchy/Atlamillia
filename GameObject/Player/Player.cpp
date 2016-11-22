#include "Player.h"
#include "../../Engine/Isometry/Isometry.h"

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

void Atlamillia::Player::Draw(Atlamillia::Graphics::Renderer* _rend, glm::vec2 _offset)
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
	temp += _offset;
	dstRect.x = int((temp.x) - 8);
	dstRect.y = int((temp.y) - (dstRect.h - 24));

	_rend->RenderCopy(texture, &srcRect, &dstRect);
}