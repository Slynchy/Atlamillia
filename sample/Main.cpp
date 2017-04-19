#include "./include/glm/glm.hpp"
#include "./include/SDL2/SDL.h"
#include "./include/SDL2/SDL_image.h"

#include "include/Atlamillia/Atlamillia.h"
#include "include/Atlamillia/GameObject/FiniteAnimation.h"
#include "include/Atlamillia/GameObject/Player/Player.h"
#include "include/Atlamillia/GameObject/NPC/RegularZed/RegularZed.h"
#include "include/Atlamillia/GameObject/NPC/RegularZed/RegularZed_States.h"
#include "include/Atlamillia/GameObject/NPC/Wyvern/Wyvern.h"
#include "include/Atlamillia/GameObject/NPC/Wyvern/Wyvern_States.h"
#include "include/Atlamillia/GameObject/Projectile/Projectile.h"
#include "include/Atlamillia/GameObject/NPC/SkeletonWarrior/SkeletonWarrior.h"
#include "include/Atlamillia/GameObject/NPC/SkeletonWarrior/SkeletonWarrior_States.h"

#include <vector>
#include <chrono>
#include <Windows.h>

#define RENDERER ATLA->GetRenderer()
#define CONTEXT ATLA->GetContext()
#define RMANAGER ATLA->GetResourceManager()
#define ACTIVE_LEVEL ATLA->GetActiveLevel()
#define VIEWPORT ATLA->GetViewport()
#define Texture Graphics::Texture

enum ExitCodes
{
	GAME_RUNNING, // this should never be an exit code, as 0 == the program is running
	NORMAL_EXIT,
	GAME_WIN,
	FAILED_TO_LOAD_LEVEL
};

using namespace Atlamillia;

#undef main
int main()
{
	// Seed the random
	srand((unsigned int)time(NULL));

	// Instantiate the engine
	Engine* ATLA = new Engine("IsometryTest", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 960, SDL_WINDOW_RESIZABLE);

	// Create a new level and set it as the active
	if(!ATLA->SetActiveLevel(Level::CreateLevel("level1", ATLA))) return FAILED_TO_LOAD_LEVEL;

	// Set up the player
	Player* player = new Player(ATLA->GetActiveLevelPtr());
	player->texture = RMANAGER->GetTexture("./gfx/skeleton_0.png", RENDERER);
	player->pos = glm::ivec2(55, 55);
	ATLA->GetActiveLevel()->m_player = player;

	// Game logic variables
		int zombie_counter = 0;
	// Game logic variables

	// Set up the enemies
	std::vector<RegularZed*> zambies;
	std::vector<SkeletonWarrior*> warriors;
	for (int i = 0; i < 100; i++)
	{
		glm::ivec2 spawnpos;
		spawnpos.x = (rand() % (ATLA->GetActiveLevel()->GetZone(0,0)->GetSize().x-1))+1;
		spawnpos.y = (rand() % (ATLA->GetActiveLevel()->GetZone(0, 0)->GetSize().y-1)) + 1;
		RegularZed* zomb = new RegularZed(spawnpos, ATLA->GetActiveLevelPtr());
		zomb->GetStateManager()->SwitchPathAlgorithm(StateManager::ALGORITHMS::BEST_FIRST);
		zomb->GetStateManager()->AddState(new RegularZed_States::Idle(zomb->GetStateManager()), true);
		zambies.push_back(zomb);
	}
	Wyvern* wyvern = new Wyvern(glm::ivec2(32, 32), ATLA->GetActiveLevelPtr());
	wyvern->GetStateManager()->SwitchPathAlgorithm(StateManager::ALGORITHMS::ASTAR);
	wyvern->GetStateManager()->AddState(new Wyvern_States::Idle(wyvern->GetStateManager()), true);

	for (int i = 0; i < 50; i++)
	{
		glm::ivec2 spawnpos;
		spawnpos.x = (rand() % (ATLA->GetActiveLevel()->GetZone(0, 0)->GetSize().x - 1)) + 1;
		spawnpos.y = (rand() % (ATLA->GetActiveLevel()->GetZone(0, 0)->GetSize().y - 1)) + 1;
		SkeletonWarrior* warrior = new SkeletonWarrior(spawnpos, ATLA->GetActiveLevelPtr());
		warrior->GetStateManager()->SwitchPathAlgorithm(StateManager::ALGORITHMS::BEST_FIRST);
		warrior->GetStateManager()->AddState(new SkeletonWarrior_States::Idle(warrior->GetStateManager()), true);
		warriors.push_back(warrior);
	}

	ExitCodes EXITCODE = GAME_RUNNING; // 1 == normal exit
	while (EXITCODE == GAME_RUNNING)
	{
		ATLA->GetRenderer()->UpdateLastTime();
		while (ATLA->PollEvents())
		{
			switch (ATLA->GetEvent()->type)
			{
				case SDL_QUIT:
					EXITCODE = NORMAL_EXIT;
					break;
				case SDL_KEYUP:
					ATLA->GetInputManager()->QueueUpdate(true);
					if (ATLA->GetEvent()->key.keysym.scancode == SDL_SCANCODE_F2)
						ATLA->GetDebug()->SpeedUp(false);
					break;
				case SDL_KEYDOWN:
					ATLA->GetInputManager()->QueueUpdate(true);
					if (ATLA->GetEvent()->key.keysym.scancode == SDL_SCANCODE_ESCAPE)
						EXITCODE = NORMAL_EXIT;
					if (ATLA->GetEvent()->key.keysym.scancode == SDL_SCANCODE_F2)
						ATLA->GetDebug()->SpeedUp(true);
					if (ATLA->GetEvent()->key.keysym.scancode == SDL_SCANCODE_F1)
						ATLA->GetDebug()->SetEnabled(true);
					break;
				case SDL_WINDOWEVENT:
					if (ATLA->GetEvent()->window.event == SDL_WINDOWEVENT_RESIZED)
					{
						int x, y;
						SDL_GetWindowSize(CONTEXT->Get(), &x, &y);
						VIEWPORT->size = glm::vec2(x, y);
						RENDERER->UpdateResolution(glm::ivec2(x, y));
						ATLA->GetActiveLevel()->UpdateTexture();
					}
			};
		}

		zombie_counter = 0;
		for each (RegularZed* var in zambies)
		{
			if (var->isAlive() == false)
				zombie_counter++;
		}
		if (zombie_counter == (zambies.size() - 1))
		{
			EXITCODE = GAME_WIN;
		}

		ATLA->GetInputManager()->Update();
		ATLA->GetDebug()->Update();

		player->Update(ATLA->GetInputManager());

		VIEWPORT->pos = -Iso::twoDToIso(player->pos);

		RENDERER->RenderActiveColour(0, 0, 0, 255);
		RENDERER->RenderClear();

		RENDERER->RenderActiveColour(255, 0, 0, 255);

		for (size_t i = 0; i < zambies.size(); i++)
		{
			zambies.at(i)->Update();
		}
		wyvern->Update();
		for (size_t i = 0; i < warriors.size(); i++)
		{
			warriors.at(i)->Update();
		}

		for (size_t i = 0; i < GameObject::SceneGraph.size(); i++)
		{
			if (GameObject::SceneGraph.at(i)->Tag == "Projectile")
			{
				static_cast<Atlamillia::Projectile*>(GameObject::SceneGraph.at(i))->Update();
			}
			else if (GameObject::SceneGraph.at(i)->Tag == "FiniteAnim")
			{
				static_cast<Atlamillia::FiniteAnimation*>(GameObject::SceneGraph.at(i))->Update();
			}
		}

		ACTIVE_LEVEL->Draw(VIEWPORT->pos + (VIEWPORT->size * 0.5f));
		//ACTIVE_LEVEL->DebugDraw(VIEWPORT->pos + (VIEWPORT->size * 0.5f));

		RENDERER->RenderFlip();

		ATLA->GetRenderer()->CalcDeltaTime();
		long int delay = Uint32(std::round(1000 / 30)) - Graphics::Renderer::DT;
		if (delay > 0 && ATLA->GetDebug()->SpeedUp() == false)
		{
			SDL_Delay(delay);
			Graphics::Renderer::DT += delay;
		}
	}

	if(EXITCODE == GAME_WIN) 
		MessageBox(NULL, "You wiped out all the zombies!", "Congrats!", NULL);

	delete ATLA;
	delete player;
	for (size_t i = 0; i < zambies.size(); i++)
	{
		delete zambies.at(i);
	}
	zambies.clear();
	for (size_t i = 0; i < warriors.size(); i++)
	{
		delete warriors.at(i);
	}
	warriors.clear();
	delete wyvern;
	return EXITCODE;
}