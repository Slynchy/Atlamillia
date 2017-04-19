#pragma once

#include <glm/glm.hpp>

namespace Atlamillia
{
	class Iso
	{
		public:

			static inline glm::ivec2 twoDToIso(glm::ivec2 pt, int _w = 32, int _h = 32) {
				glm::ivec2 tempPt = glm::ivec2(0, 0);
				pt.x *= _w;
				pt.y *= _h;
				tempPt.x = pt.x - pt.y;
				tempPt.y = (pt.x + pt.y) / 2;
				return(tempPt);
			}

			static inline glm::vec2 twoDToIso(glm::vec2 pt, int _w = 32, int _h = 32) {
				glm::vec2 tempPt = glm::ivec2(0, 0);
				pt.x *= _w;
				pt.y *= _h;
				tempPt.x = pt.x - pt.y;
				tempPt.y = (pt.x + pt.y) / 2;
				return(tempPt);
			}

			static inline glm::vec2 isoTo2D(glm::vec2 pt, int _w = 32, int _h = 32) {
				glm::vec2 tempPt = glm::ivec2(0, 0);
				pt.x /= _w;
				pt.y /= _h;
				tempPt.x = (2 * pt.y + pt.x) / 2;
				tempPt.y = (2 * pt.y - pt.x) / 2;
				return(tempPt);
			}
	};
};