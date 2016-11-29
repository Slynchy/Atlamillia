#pragma once

#include "../../../GameObject/GameObject.h"
#include <glm/glm.hpp>
#include <vector>
#include "../../../Engine/Graphics/Graphics.h"

#ifdef _DEBUG
	#define dprintf printf
#else
	#define dprintf __noop
#endif


namespace Atlamillia
{
	class Tile
	{
		private:
			/// Objects that occupy this tile
			std::vector<GameObject*> m_objects;
			Atlamillia::Graphics::Texture* m_floortexture;
			int m_value = 0;
		protected:
		public:
			glm::ivec2 pos;

			inline void AddObject(GameObject* _obj)
			{
				m_objects.push_back(_obj);
			}

			inline GameObject* GetObject(size_t _pos)
			{
				try
				{
					return m_objects.at(_pos);
				}
				catch (std::exception& e)
				{
					dprintf("[Tile] Failed to get object at index %d! %s\n", _pos, e.what());
					return nullptr;
				}
			}

			inline int GetValue()
			{
				return m_value;
			}
			inline void SetValue(int _i)
			{
				m_value = _i;
			}

			inline void SetTexture(Atlamillia::Graphics::Texture* _tex)
			{
				m_floortexture = _tex;
			}

			inline void Draw(Atlamillia::Graphics::Renderer* _rend, glm::ivec2 _pos, bool _force = false)
			{
				if (m_value == 0 || m_floortexture == nullptr) return;
				if (_force == false && (_pos.x > _rend->GetResolution().x || _pos.x < -m_floortexture->GetDimensions().x || _pos.y > _rend->GetResolution().y || _pos.y < -m_floortexture->GetDimensions().y))
					return;
				SDL_Rect temp = { _pos.x, _pos.y, m_floortexture->GetDimensions().x, m_floortexture->GetDimensions().y };
				_rend->RenderCopy(m_floortexture, NULL, &temp);
			}

			~Tile()
			{
				m_objects.clear();
			}
	};
}