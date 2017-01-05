#pragma once

#ifdef _DEBUG
	#define dprintf printf
#else
	#define dprintf __noop
#endif

#include "Graphics.h"

namespace Atlamillia
{
	class Engine;
	
	class Debug
	{
		private:
			Atlamillia::Engine* m_engine;
			Atlamillia::Graphics::Context* ctx;
			Atlamillia::Graphics::Renderer* rend;
			bool isEnabled = false;
			bool m_speedUp = false;
		protected:
		public:

			Debug(Atlamillia::Engine* _engine)
			{
				m_engine = _engine;
				ctx = new Atlamillia::Graphics::Context("AI Window", 0,0,600,600, SDL_WINDOW_RESIZABLE | SDL_WINDOW_HIDDEN);
				rend = new Atlamillia::Graphics::Renderer(ctx);
				rend->SetLogicalResolution(600, 600);
			}
			~Debug()
			{
				m_engine = nullptr;
				if (ctx != nullptr) delete ctx;
				if (rend != nullptr) delete rend;
			}

			bool SpeedUp(bool _speedup)
			{
				m_speedUp = _speedup;
				return m_speedUp;
			}

			bool SpeedUp()
			{
				return m_speedUp;
			}

			/// Toggle the debug mode/window
			void Toggle()
			{
				ctx->ToggleWindow();
				isEnabled = true;
			}
			/// Is it enabled?
			bool enabled()
			{
				return isEnabled;
			}

			void Draw();

			/// Update the grid with newest info if enabled
			void Update()
			{
				if (isEnabled == true)
				{
					Draw();
				}
			}
	};

}