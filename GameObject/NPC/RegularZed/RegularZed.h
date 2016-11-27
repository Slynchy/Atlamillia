#pragma once

#include "../NPC.h"
#include "../../../Engine/Graphics/Graphics.h"

namespace Atlamillia
{

	class RegularZed : public NPC
	{
		private:
		protected:
		public:

			void Draw(Atlamillia::Graphics::Renderer* rend, glm::vec2 offset)
			{
				glm::ivec2 temp = Atlamillia::Iso::twoDToIso(this->pos);
				temp += offset;
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