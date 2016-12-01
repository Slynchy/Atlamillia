#pragma once

#include <vector>
#include <memory>
#include <algorithm>
#include "../../../ModularPathFinding/pathalgo.h"

#include <glm\glm.hpp>

struct NODE;

namespace Atlamillia
{

	class LineOfSight : public PathAlgorithm
	{
		protected:
		private:
		public:
			bool HasLineOfSight(glm::ivec2 _start, glm::ivec2 _goal, std::vector<std::vector<NODE*>> _map, bool _allowDiagonal = false);
	};

};