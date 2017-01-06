#include "GameObject.h"
#include "../Engine/Graphics/Debug.h"

using namespace Atlamillia;

std::vector<GameObject*> GameObject::SceneGraph;

std::vector<GameObject*> Atlamillia::GameObject::GetCloseObjects(glm::vec2 _pos, int _range, std::string _tag)
{
	size_t sceneGraphPos = 0;
	for (size_t i = 0; i < GameObject::SceneGraph.size(); i++)
	{
		// Is object further down (Z) than player?
		//if (glm::length(GameObject::SceneGraph.at(i)->pos) > glm::length(_pos))
		if(_pos == GameObject::SceneGraph.at(i)->pos)
		{
			sceneGraphPos = i;
			break;
		}
	}

	std::vector<GameObject*> closeObjects;
	int half = (_range / 2);
	for (size_t i = 0; i < _range; i++)
	{
		if (GameObject::SceneGraph.size() <= (sceneGraphPos + (half - i))) continue;
		if (_tag != "" && _tag == GameObject::SceneGraph.at(sceneGraphPos + (half - i))->Tag)
			closeObjects.push_back(GameObject::SceneGraph.at(sceneGraphPos + (half - i)));
		else
		{
			_range++;
			half = (_range / 2);
		}
	}
	return closeObjects;
}

void GameObject::ChangeTag(std::string _newtag)
{
	Tag = _newtag;
	TagHash = std::hash<std::string>{}(Tag);
}

void GameObject::SetTexture(Atlamillia::Graphics::Texture* _tex)
{
	m_activeTexture = _tex;
}

void GameObject::SetIsoPos(glm::ivec2 _pos)
{
	pos = Iso::twoDToIso(_pos);
}

void GameObject::LookAt(glm::ivec2 _target)
{
	m_direction = GetDirectionFromDelta(glm::vec2(_target) - this->pos);
}

void GameObject::Draw(glm::ivec2 _offset, Atlamillia::Graphics::Renderer* _rend)
{
	if (m_activeTexture == nullptr) return;
	glm::ivec2 temp = Iso::twoDToIso(glm::ivec2(pos));
	temp += _offset;
	temp.y = temp.y - m_activeTexture->GetDimensions().y + 32;
	if (
		temp.x + this->m_activeTexture->GetDimensions().x < 0 ||
		temp.y + this->m_activeTexture->GetDimensions().y < 0 ||
		temp.x > _rend->GetResolution().x ||
		temp.y > _rend->GetResolution().y
		)
	{
		return;
	};
	dstRect = { temp.x,temp.y,m_activeTexture->GetDimensions().x,m_activeTexture->GetDimensions().y };
	_rend->RenderCopy(this->m_activeTexture, NULL, &dstRect);
}

void GameObject::Translate(float _x, float _y)
{
	pos += glm::vec2(_x, _y);
	m_direction = GetDirectionFromDelta(glm::vec2(_x, _y));
}

void GameObject::Translate(glm::vec2 _trs)
{
	pos += _trs;
	m_direction = GetDirectionFromDelta(_trs);
}

void GameObject::Translate(float _x, float _y, std::vector<GameObject*>* _objects)
{
	_x = std::max(-0.05f, std::min(_x, 0.05f));
	_y = std::max(-0.05f, std::min(_y, 0.05f));

	bool collision = false;
	glm::vec2 tempPos = pos + glm::vec2(_x, _y);
	glm::ivec2 tempPosI = glm::ivec2(tempPos);
	for (size_t i = 0; i < _objects->size(); i++)
	{
		if (
			tempPosI.x == _objects->at(i)->pos.x ||
			tempPosI.x == _objects->at(i)->pos.x - 1
			)
		{
			if (
				tempPosI.y == _objects->at(i)->pos.y ||
				tempPosI.y == _objects->at(i)->pos.y - 1
				)
			{
				if (_objects->at(i)->TagHash != this->TagHash)
				{
					collision = true;
					break;
				}
			}
		}
	}


	if (collision != true)
		pos += glm::vec2(_x, _y);
	m_direction = GetDirectionFromDelta(glm::vec2(_x, _y));
}

GameObject::DIRECTIONS GameObject::GetDirectionFromDelta(glm::vec2 _deltapos)
{
	if (_deltapos.x > 0 && _deltapos.y > 0)
	{
		return GameObject::DIRECTIONS::SOUTH;
	}
	else if (_deltapos.x < 0 && _deltapos.y > 0)
	{
		return GameObject::DIRECTIONS::WEST;
	}
	else if (_deltapos.x < 0 && _deltapos.y < 0)
	{
		return GameObject::DIRECTIONS::NORTH;
	}
	else if (_deltapos.x > 0 && _deltapos.y < 0)
	{
		return GameObject::DIRECTIONS::EAST;
	}
	else if (_deltapos.x == 0 && _deltapos.y > 0)
	{
		return GameObject::DIRECTIONS::SOUTH_WEST;
	}
	else if (_deltapos.x == 0 && _deltapos.y < 0)
	{
		return GameObject::DIRECTIONS::NORTH_EAST;
	}
	else if (_deltapos.x > 0 && _deltapos.y == 0)
	{
		return GameObject::DIRECTIONS::SOUTH_EAST;
	}
	else if (_deltapos.x < 0 && _deltapos.y == 0)
	{
		return GameObject::DIRECTIONS::NORTH_WEST;
	}
	return GameObject::DIRECTIONS::SOUTH;
}

GameObject::GameObject()
{
	srcRect = { 0,0,0,0 };
	dstRect = { 0,0,0,0 };
	SceneGraph.push_back(this);
	TagHash = std::hash<std::string>{}(Tag);
}
GameObject::~GameObject()
{
	srcRect = { 0,0,0,0 };
	dstRect = { 0,0,0,0 };
	Tag = "";
	parent_level = nullptr;
	m_activeTexture = nullptr;
	pos = glm::vec2(0, 0);

	for (size_t i = 0; i < SceneGraph.size(); i++)
	{
		if (SceneGraph.at(i) == this)
		{
			SceneGraph.erase(SceneGraph.begin() + i);
			break;
		};
	}
}