/// \file		Atlamillia.h
/// \author		Sam Lynch
/// \brief		Header file for Atlamillia engine
/// \version	0.5.1
/// \date		January 2017
/// \details	The header file for declaring the engine and its functions/variables.

#pragma once

#include "./GameObject/GameObject.h"
#include "./Engine/Isometry/Isometry.h"
#include "./Engine/Viewport.h"
#include "./Engine/Graphics/Graphics.h"
#include "./Engine/ResourceManager.h"
#include "./Engine/InputManager.h"
#include "./Level/Level.h"
#include "./Engine/Graphics/Debug.h"

namespace Atlamillia
{

	/// Master class of the Atlamillia engine
	class Engine
	{
		private:
			/// The window/context for primary rendering
			Atlamillia::Graphics::Context* m_ctx;

			/// The primary renderer
			Atlamillia::Graphics::Renderer* m_renderer;

			/// The main resource manager; for loading/getting textures
			Atlamillia::ResourceManager* m_rmanager;

			/// The input manager, for mouse/keyboard input
			Atlamillia::InputManager* m_inputmanager;

			/// SDL events buffer
			SDL_Event* m_events;

			/// The viewport into the 2D world
			Atlamillia::Viewport* m_viewport;

			/// The current level
			Atlamillia::Level* m_activeLevel;

			/// The debug window and other debug-related information
			Atlamillia::Debug* m_debug;

		protected:
		public:

			inline Atlamillia::ResourceManager* GetResourceManager() { return m_rmanager; };
			inline Atlamillia::Graphics::Renderer* GetRenderer() { return m_renderer; };
			inline Atlamillia::Graphics::Context* GetContext() { return m_ctx; };
			inline Atlamillia::InputManager* GetInputManager() { return m_inputmanager; };
			inline SDL_Event* GetEvent() { return m_events; };
			inline Atlamillia::Viewport* GetViewport() { return m_viewport; };
			inline Atlamillia::Level* GetActiveLevel() { return m_activeLevel; };
			inline Atlamillia::Debug* GetDebug() { return m_debug; };
			inline Atlamillia::Level** GetActiveLevelPtr() { return &m_activeLevel; };

			inline int PollEvents() { return SDL_PollEvent(m_events); };
			inline bool SetActiveLevel(Atlamillia::Level* _lev) 
			{ 
				if (_lev == nullptr) return false; 
				m_activeLevel = _lev; 
				return true;
			};

			/// Lerp function for glm Vec2
			static glm::vec2 interpolate(const glm::vec2 &start, const glm::vec2 &end, float alpha)
			{
				alpha *= Atlamillia::Graphics::Renderer::DT;
				return (start + alpha*(end - start));
			}

			/// Lerp function for FP values
			static float interpolate(const float &start, const float &end, float alpha)
			{
				alpha *= Atlamillia::Graphics::Renderer::DT;
				return (start + alpha*(end - start));
			}

			Engine(const char *title, int x, int y, int w, int h, Uint32 flags)
			{
				SDL_Init(SDL_INIT_EVERYTHING);
				m_ctx = new Atlamillia::Graphics::Context(title, x, y, w, h, flags);
				m_renderer = new Atlamillia::Graphics::Renderer(m_ctx);
				m_rmanager = new Atlamillia::ResourceManager(m_renderer);
				m_events = new SDL_Event();
				m_inputmanager = new InputManager();
				m_viewport = new Atlamillia::Viewport(0, 0, (float)w, (float)h);
				m_debug = new Debug(this);
			}

			~Engine()
			{
				if (m_activeLevel != nullptr)
					delete m_activeLevel;
				delete m_events;
				delete m_inputmanager;
				delete m_viewport;
				delete m_rmanager;
				delete m_ctx;
				delete m_renderer;
				delete m_debug;
				SDL_Quit();
			}
	};
};