#pragma once

#include "GameObject.h"
#include "../Engine/Graphics/Graphics.h"

namespace Atlamillia
{

	class FiniteAnimation : public GameObject
	{
	protected:
	private:
		SDL_Rect frame;
		size_t max_frames;
		float counter;
		float speed;
	public:

		FiniteAnimation(glm::ivec2 _pos, Graphics::Texture* _spritesheet, glm::ivec2 _frame_size, size_t _max_frames, float _speed = 3.0f)
		{
			frame.x = 0;
			frame.y = 0;
			frame.w = _frame_size.x;
			frame.h = _frame_size.y;
			max_frames = _max_frames;
			counter = 0.0f;
			this->pos = _pos;
			this->Tag = "FiniteAnim";
			this->m_activeTexture = _spritesheet;
			speed = _speed;
		}

		void Draw(glm::ivec2 _offset, Atlamillia::Graphics::Renderer* _rend)
		{
			if (m_activeTexture == nullptr) return;
			glm::ivec2 temp = Iso::twoDToIso(glm::ivec2(pos));
			temp += _offset;
			temp.y = temp.y - m_activeTexture->GetDimensions().y + 32;
			if (
				temp.x + this->m_activeTexture->GetDimensions().x < 0 ||
				temp.y + this->m_activeTexture->GetDimensions().y < 0 ||
				temp.x > _rend->GetResolution().x ||
				temp.y > _rend->GetResolution().y
				)
			{
				return;
			};

			srcRect = {
				96 * (int)std::floor(this->counter),
				0,
				96,
				96
			};

			dstRect = { temp.x - 32,temp.y - 32,156,156 };
			_rend->RenderCopy(this->m_activeTexture, &srcRect, &dstRect);
		}

		void Update()
		{
			if (counter < max_frames)
			{
				counter += (Atlamillia::Graphics::Renderer::DT * 0.01f) * speed;
			}
			else
			{
				delete this;
				return;
			}
		};
	};

}