#include "LineOfSight.h"
#include "../../../ModularPathFinding/node.h"
#include <stack>

bool Atlamillia::LineOfSight::HasLineOfSight(glm::ivec2 _start, glm::ivec2 _goal, std::vector<std::vector<NODE*>> _map, size_t range)
{
	std::vector<NODE*> open;
	std::vector<glm::ivec2> closed;
	std::vector<NODE*> index;

	open.push_back(new NODE(_start, false));
	index.push_back(open.front());

	while (open.size() != 0)
	{
		size_t position;
		NODE* current = GetLowestFCost(open, position);
		open.erase(open.begin() + position);
		closed.push_back(current->pos);

		if (current->pos == _goal)
		{
			for (size_t i = 0; i < index.size(); i++)
			{
				delete index.at(i);
			}
			index.clear();
			return true;
		}

		if (current->g >= range)
		{
			for (size_t i = 0; i < index.size(); i++)
			{
				delete index.at(i);
			}
			index.clear();
			return false;
		}

		std::vector<NODE*> neighbours = GetNeighbors(current, &_map, true);
		for each (NODE* var in neighbours)
		{
			index.push_back(var);
		}

		for each (NODE* neighbour in neighbours)
		{
			neighbour->g = current->g + 1.0f;
			neighbour->h = glm::distance(glm::vec2(_goal), glm::vec2(neighbour->pos));
			neighbour->f = neighbour->g + neighbour->h;

			bool existsInOpen;
			if (PositionExistsInVector(open, neighbour) == nullptr)
			{
				existsInOpen = false;
			}
			else
			{
				existsInOpen = true;
			}
			bool existsInClosed = PositionExistsInVector(closed, neighbour->pos);

			if (existsInClosed) continue;

			if (_map.size() != 0)
			{
				if (
					size_t(neighbour->pos.y) >= _map.size() ||
					size_t(neighbour->pos.x) >= _map.at(neighbour->pos.y).size() ||
					neighbour->pos.y < 0 ||
					neighbour->pos.x < 0
					) // is above or less the size
				{
					for (size_t i = 0; i < index.size(); i++)
					{
						delete index.at(i);
					}
					index.clear();
					return false;
				}
				else if (_map.at(neighbour->pos.y).at(neighbour->pos.x)->isObstacle == true)
				{
					for (size_t i = 0; i < index.size(); i++)
					{
						delete index.at(i);
					}
					index.clear();
					return false;
				}
			}

			if (existsInClosed == false && existsInOpen == false)
			{
				open.push_back(neighbour);
				continue;
			}
		};

	}

	return false;
};