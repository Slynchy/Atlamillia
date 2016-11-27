#pragma once

#include "../NPC.h"
#include "../../../Engine/Graphics/Graphics.h"

namespace Atlamillia
{

	class RegularZed : public NPC
	{
		private:
			const float m_speed = 0.03f;
		protected:
		public:

			void Update()
			{
				// If we're at the end of the path, return
				if ((brain->GetPathPos() + 1) >= brain->GetPath()->size()) return;

				glm::vec2 temp(0,0);
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

			void Draw(Atlamillia::Graphics::Renderer* rend, glm::vec2 offset)
			{
				glm::ivec2 temp = Atlamillia::Iso::twoDToIso(this->pos);
				temp += offset;
				temp -= glm::vec2(8, 8);
				rend->RenderDrawLine(temp.x, temp.y + 16, temp.x + 32, temp.y);
				rend->RenderDrawLine(temp.x + 32, temp.y, temp.x + 64, temp.y + 16);
				rend->RenderDrawLine(temp.x + 64, temp.y + 16, temp.x + 32, temp.y + 32);
				rend->RenderDrawLine(temp.x + 32, temp.y + 32, temp.x, temp.y + 16);
			}

			RegularZed(glm::ivec2 _startpos)
			{
				pos = _startpos;
			}
	};

}