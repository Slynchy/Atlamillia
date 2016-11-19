#include "Graphics.h"
#include <string>
#include <SDL2\SDL.h>
#include <SDL2\SDL_image.h>

Atlamillia::Graphics::Texture::Texture(Atlamillia::Graphics::Renderer* _rend , std::string _filename)
{
	m_texture = IMG_LoadTexture(_rend->GetRenderer(), _filename.c_str());
	if (m_texture)
	{
		m_filename = _filename;
	}
	else
	{
		return;
	}
	return;
}
