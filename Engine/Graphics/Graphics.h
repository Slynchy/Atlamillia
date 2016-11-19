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
		public:
			inline std::string GetFilename() { return m_filename; };
			inline SDL_Texture* GetTexture() { return this->m_texture; };
			inline void SetTexture(SDL_Texture* _tex) { return void(m_texture = _tex); };

			Texture(Atlamillia::Graphics::Renderer* _rend, std::string _filename);
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
		public:

			SDL_Renderer* GetRenderer() { return RENDERER; };

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

			Renderer(Context* ctx)
			{
				RENDERER = SDL_CreateRenderer(ctx->Get(), -1, SDL_RENDERER_ACCELERATED);
			}
			~Renderer()
			{
				SDL_DestroyRenderer(RENDERER);
			}
		};
	};
};