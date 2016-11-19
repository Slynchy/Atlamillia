#pragma once

#include "./GameObject/GameObject.h"
#include "./Engine/Isometry/Isometry.h"
#include "./Engine/Viewport.h"
#include "./Engine/Graphics/Graphics.h"
#include "./Engine/ResourceManager.h"
#include "./Engine/InputManager.h"
#include "./Level/Level.h"

namespace Atlamillia
{
	class Engine
	{
		private:
			Atlamillia::Graphics::Context* m_ctx;
			Atlamillia::Graphics::Renderer* m_renderer;
			Atlamillia::ResourceManager* m_rmanager;
			Atlamillia::InputManager* m_inputmanager;
			SDL_Event* m_events;
			Atlamillia::Viewport* m_viewport;
			Atlamillia::Level* m_activeLevel;

		protected:
		public:

			inline Atlamillia::ResourceManager* GetResourceManager() { return m_rmanager; };
			inline Atlamillia::Graphics::Renderer* GetRenderer() { return m_renderer; };
			inline Atlamillia::Graphics::Context* GetContext() { return m_ctx; };
			inline Atlamillia::InputManager* GetInputManager() { return m_inputmanager; };
			inline int PollEvents() { return SDL_PollEvent(m_events); };
			inline SDL_Event* GetEvent() { return m_events; };
			inline Atlamillia::Viewport* GetViewport() { return m_viewport; };
			inline Atlamillia::Level* GetActiveLevel() { return m_activeLevel; };
			inline void SetActiveLevel(Atlamillia::Level* _lev) { m_activeLevel = _lev; };

			Engine(const char *title, int x, int y, int w, int h, Uint32 flags)
			{
				SDL_Init(SDL_INIT_EVERYTHING);
				m_ctx = new Atlamillia::Graphics::Context(title, x, y, w, h, flags);
				m_renderer = new Atlamillia::Graphics::Renderer(m_ctx);
				m_rmanager = new Atlamillia::ResourceManager();
				m_events = new SDL_Event();
				m_inputmanager = new InputManager();
				m_viewport = new Atlamillia::Viewport(0, 0, (float)w, (float)h);
			}

			~Engine()
			{
				delete m_rmanager;
				delete m_ctx;
				delete m_renderer;
				delete m_events;
				delete m_inputmanager;
				delete m_viewport;
				SDL_Quit();
			}
	};
};