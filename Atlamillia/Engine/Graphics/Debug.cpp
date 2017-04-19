#include "Debug.h"
#include "../../Level/Level.h"
#include "../../Atlamillia.h"
#include "../../GameObject/GameObject.h"

void Atlamillia::Debug::Draw()
{
	const int squareSize = 8;

	rend->RenderActiveColour(0, 0, 0, 255);
	rend->RenderClear();
	rend->RenderActiveColour(111, 111, 111, 255);
	// Iterate through zones
	for (size_t y = 0; y < m_engine->GetActiveLevel()->GetSize().y; y++)
	{
		for (size_t x = 0; x < m_engine->GetActiveLevel()->GetSize().x; x++)
		{
			// Shortcut to nodemap
			std::vector<std::vector<NODE*>>* level = &m_engine->GetActiveLevel()->GetZone(x, y)->m_nodemap;

			// Iterate through nodemap
			for (size_t nY = 0; nY < level->size(); nY++)
			{
				for (size_t nX = 0; nX < level->at(nY).size(); nX++)
				{
					SDL_Rect temp = {
						0 + (squareSize * int(nX)),
						0 + (squareSize * int(nY)),
						squareSize,
						squareSize
					};

					SDL_RenderDrawRect(rend->GetRenderer(), &temp);
				}
			}
		}
	}

	size_t player = std::hash<std::string>{}("Player");
	size_t zomb = std::hash<std::string>{}("RegularZombie");
	size_t skele = std::hash<std::string>{}("SkeletonWarrior");
	size_t wyv = std::hash<std::string>{}("Wyvern");
	for each (GameObject* var in GameObject::SceneGraph)
	{
		SDL_Rect temp = {
			0 + (squareSize * int(std::roundf(var->pos.x))),
			0 + (squareSize * int(std::roundf(var->pos.y))),
			squareSize,
			squareSize
		};
		if (var->TagHash == player)
		{
			rend->RenderActiveColour(0, 255, 0, 255);
		}
		else if (var->TagHash == zomb)
		{
			rend->RenderActiveColour(255, 0, 0, 255);
		}
		else if (var->TagHash == skele)
		{
			rend->RenderActiveColour(102, 255, 255, 255);
		}
		else if (var->TagHash == wyv)
		{
			rend->RenderActiveColour(255, 0, 127, 255);
		}
		else
		{
			rend->RenderActiveColour(0, 0, 255, 255);
		}
		SDL_RenderFillRect(rend->GetRenderer(), &temp);
	}

	rend->RenderFlip();
}