/// \file 		Viewport.h
/// \author 	Sam Lynch
/// \brief 		Header file for viewport object

#pragma once

#include <glm/glm.hpp>

namespace Atlamillia
{
	struct Viewport
	{
		glm::vec2 pos;
		glm::vec2 size;
		Viewport(float _x, float _y, float _w, float _h)
		{
			pos = glm::vec2(_x, _y);
			size = glm::vec2(_w, _h);
		}
	};
};