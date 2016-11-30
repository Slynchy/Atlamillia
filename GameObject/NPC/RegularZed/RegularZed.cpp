#include "./RegularZed.h"
#include "../../../Engine/AI/AI.h"
#include "../../../Engine/AI/StateManager.h"
#include "../../../Engine/Graphics/Graphics.h"
#include <vector>
#include "../../../../ModularPathFinding/node.h"

using namespace Atlamillia;

void RegularZed::Update()
{
	if (this->brain != nullptr) this->brain->Update();
	return;
}

void RegularZed::Draw(Atlamillia::Graphics::Renderer* rend, glm::vec2 offset)
{
	glm::vec2 temp = this->pos;
	//temp.x = std::round(temp.x);
	//temp.y = std::round(temp.y);
	temp = Atlamillia::Iso::twoDToIso(temp);
	temp += offset;
	//temp -= glm::vec2(8, 8);
	rend->RenderDrawLine(temp.x, temp.y + 16, temp.x + 32, temp.y);
	rend->RenderDrawLine(temp.x + 32, temp.y, temp.x + 64, temp.y + 16);
	rend->RenderDrawLine(temp.x + 64, temp.y + 16, temp.x + 32, temp.y + 32);
	rend->RenderDrawLine(temp.x + 32, temp.y + 32, temp.x, temp.y + 16);
}