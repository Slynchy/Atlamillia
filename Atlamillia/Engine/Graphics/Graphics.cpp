#include "Graphics.h"
#include <string>
#include <SDL2\SDL.h>
#include <SDL2\SDL_image.h>

Uint32 Atlamillia::Graphics::Renderer::DT;

Atlamillia::Graphics::Texture::Texture(Atlamillia::Graphics::Renderer* _rend , std::string _filename)
{
	m_texture = IMG_LoadTexture(_rend->GetRenderer(), _filename.c_str());
	if (m_texture)
	{
		m_filename = _filename;
		SDL_QueryTexture(m_texture, NULL, NULL, &m_dimensions.x, &m_dimensions.y);
	}
	else
	{
		return;
	}
	return;
}

Atlamillia::Graphics::Texture::Texture(Atlamillia::Graphics::Renderer* _rend, int _w, int _h, bool _isRenderTarget)
{
	if(_isRenderTarget)
		m_texture = SDL_CreateTexture(_rend->GetRenderer(), NULL, SDL_TEXTUREACCESS_TARGET, _w, _h);
	else
		m_texture = SDL_CreateTexture(_rend->GetRenderer(), NULL, NULL, _w, _h);

	m_renderTarget = _isRenderTarget;
	SDL_SetTextureBlendMode(m_texture, SDL_BLENDMODE_BLEND);
	m_dimensions = glm::ivec2(_w, _h);
}