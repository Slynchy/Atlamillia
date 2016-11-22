#pragma once

#include <glm/glm.hpp>
#include <SDL2\SDL.h>
#include <string>

namespace Atlamillia
{
	namespace Graphics
	{
		class Renderer;
		class Context;
		class Texture;

		class Texture
		{
		private:
			SDL_Texture* m_texture;
			std::string m_filename;
			glm::ivec2 m_dimensions;
			bool m_renderTarget = false;
		public:
			inline std::string GetFilename() { return m_filename; };
			inline SDL_Texture* GetTexture() { return this->m_texture; };
			inline glm::ivec2 GetDimensions() { return this->m_dimensions; };
			inline void SetTexture(SDL_Texture* _tex) { return void(m_texture = _tex); };

			Texture(Atlamillia::Graphics::Renderer* _rend, std::string _filename);
			Texture(Atlamillia::Graphics::Renderer* _rend, int _w, int _h, bool _isRenderTarget = true);

			~Texture()
			{
				SDL_DestroyTexture(m_texture);
				m_filename = "";
			}
		};

		class Context
		{
		private:
			SDL_Window* CONTEXT;
		public:
			inline SDL_Window* Get() { return CONTEXT; };

			Context(const char *title, int x, int y, int w, int h, Uint32 flags)
			{
				CONTEXT = SDL_CreateWindow(title, x, y, w, h, flags);
			}

			~Context()
			{
				SDL_DestroyWindow(CONTEXT);
			}
		};

		class Renderer
		{
		private:
			SDL_Renderer* RENDERER;
			Context* m_ctx;
			glm::ivec2 m_resolution;
			Uint32 dt_lastTime;
		public:

			static Uint32 DT;

			SDL_Renderer* GetRenderer() { return RENDERER; };

			inline void UpdateLastTime()
			{
				dt_lastTime = SDL_GetTicks();
			}

			inline void CalcDeltaTime()
			{
				DT = (SDL_GetTicks() - dt_lastTime);
			}

			inline void RenderClear()
			{
				SDL_RenderClear(RENDERER);
			}

			inline void RenderActiveColour(Uint8 r, Uint8 g, Uint8 b, Uint8 a = 255)
			{
				SDL_SetRenderDrawColor(RENDERER, r, g, b, a);
			}

			inline void RenderCopy(Texture * texture, const SDL_Rect* srcrect, const SDL_Rect* dstrect)
			{
				SDL_RenderCopy(RENDERER, texture->GetTexture(), srcrect, dstrect);
			}

			inline void RenderDrawLine(float _x1, float _y1, float _x2, float _y2)
			{
				SDL_RenderDrawLine(RENDERER, (int)_x1, (int)_y1, (int)_x2, (int)_y2);
			}

			inline void RenderDrawLine(int _x1, int _y1, int _x2, int _y2)
			{
				SDL_RenderDrawLine(RENDERER, _x1, _y1, _x2, _y2);
			}

			inline void RenderFlip()
			{
				SDL_RenderPresent(RENDERER);
			}

			inline void Delay(Uint32 _time)
			{
				SDL_Delay(_time);
			}

			inline glm::ivec2 GetResolution()
			{
				return m_resolution;
			}

			inline void UpdateResolution()
			{
				SDL_GetWindowSize(m_ctx->Get(), &m_resolution.x, &m_resolution.y);
			}

			inline void UpdateResolution(glm::ivec2 _res)
			{
				m_resolution = _res;
			}

			inline void SetRenderTarget(Atlamillia::Graphics::Texture* _target)
			{
				if(_target != nullptr || _target != NULL)
					SDL_SetRenderTarget(this->RENDERER, _target->GetTexture());
				else
					SDL_SetRenderTarget(this->RENDERER, NULL);
			}

			Renderer(Context* ctx)
			{
				m_ctx = ctx;
				RENDERER = SDL_CreateRenderer(m_ctx->Get(), -1, SDL_RENDERER_ACCELERATED);
				SDL_GetWindowSize(m_ctx->Get(), &m_resolution.x, &m_resolution.y);
			}
			~Renderer()
			{
				m_ctx = nullptr;
				SDL_DestroyRenderer(RENDERER);
			}
		};
	};
};