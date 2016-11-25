#include "Level.h"
#include "../Atlamillia.h"
#include "../Engine/Graphics/Graphics.h"
#include <algorithm>

Atlamillia::Level::Level(size_t _w, size_t _h, size_t _zW, size_t _zH, Atlamillia::Engine* _eng)
{
	m_engine = _eng;
	m_renderer = m_engine->GetRenderer();
	m_zones.resize(_h);
	for (size_t y = 0; y < m_zones.size(); y++)
	{
		m_zones.at(y).resize(_w);
		for (size_t x = 0; x < m_zones.at(y).size(); x++)
		{
			m_zones.at(y).at(x) = new Zone();
			m_zones.at(y).at(x)->Resize(_zW, _zH);
		}
	}
}

/// \author http://stackoverflow.com/questions/1380463/sorting-a-vector-of-custom-objects
struct less_than_key
{
	inline bool operator() (const Atlamillia::GameObject* struct1, const Atlamillia::GameObject* struct2)
	{
		return (glm::length(struct1->pos) < glm::length(struct2->pos));
	}
};

void Atlamillia::Level::Draw(glm::ivec2 _offset)
{
	glm::ivec2 offset = _offset - glm::ivec2(m_texture->GetDimensions().x * 0.5f, 0);
	SDL_Rect temp = { offset.x,offset.y, m_texture->GetDimensions().x ,m_texture->GetDimensions().y };
	this->m_renderer->RenderCopy(m_texture, NULL, &temp);

	bool playerdrawn = false;
	float playerZMagnitude = glm::length(m_player->pos); // magnitude of XY == Z
	for (size_t i = 0; i < m_props.size(); i++)
	{
		// If the Z of the object is greater than the player's Z, then draw the player before the object
		if (glm::length(m_props.at(i)->pos) > (playerZMagnitude) && playerdrawn == false)
		{
			m_player->Draw(m_renderer, _offset);
			playerdrawn = true;
		}
		m_props.at(i)->Draw(offset + glm::ivec2(m_texture->GetDimensions().x*0.5, 0), m_renderer);
	}
	// If the player hasn't been drawn, draw them now; they are infront of all objects
	if(playerdrawn == false)
		m_player->Draw(m_renderer, _offset);
}

void Atlamillia::Level::Draw()
{
	try
	{
		for (size_t y = 0; y < (size_t)GetSize().y; y++)
		{
			for (size_t x = 0; x < (size_t)GetSize().x; x++)
			{
				for (size_t zY = 0; zY < (size_t)GetZone(x, y)->GetSize().y; zY++)
				{
					for (size_t zX = 0; zX < (size_t)GetZone(x, y)->GetSize().x; zX++)
					{
						glm::ivec2 temp = Atlamillia::Iso::twoDToIso(glm::vec2(zX, zY) + (glm::vec2(x, y) * (float)GetZone(x, y)->GetSize().y));
						temp += glm::ivec2(m_texture->GetDimensions().x * 0.5f, 0);

						this->GetZone(x, y)->GetTile(zX, zY)->Draw(m_renderer, temp, true);
					};
				}
			};
		}
	}
	catch (const std::exception& e)
	{
		printf("[Level] Failed to draw to texture! %s", e.what());
	}
}

void Atlamillia::Level::UpdateTexture()
{
	m_engine->GetResourceManager()->DeleteTexture(m_texture);
	m_texture = new Atlamillia::Graphics::Texture(
		m_renderer,
		64 * (GetSize().x * m_zones.front().front()->GetSize().x),
		32 * (GetSize().y * m_zones.front().front()->GetSize().y),
		true);

	m_renderer->SetRenderTarget(m_texture);
	m_renderer->RenderActiveColour(0, 0, 0, 0);
	m_renderer->RenderClear();
	this->Draw();
	m_renderer->SetRenderTarget(NULL);
};

void Atlamillia::Level::SetTileValues(glm::ivec2 _zone, std::vector<std::vector<int>>& _in)
{
	for (size_t zY = 0; zY < _in.size(); zY++)
	{
		for (size_t zX = 0; zX < _in.at(zY).size(); zX++)
		{
			this->m_zones.at(_zone.y).at(_zone.x)->GetTile(zX, zY)->SetValue(_in.at(zY).at(zX));
		};
	}

	return;
}

Atlamillia::Level* Atlamillia::Level::CreateLevel(const char* _inputfile, Atlamillia::Engine* _eng)
{
	// Load the floormap to int table
	std::string filename = "./levels/" + std::string(_inputfile) + "_floor.csv";
	std::vector<std::vector<int>> floormap_int = Atlamillia::CSVLoader::LoadCSVFile_int(filename.c_str());
	filename = "./levels/" + std::string(_inputfile) + "_floorindex.txt";
	std::vector<std::vector<std::string>> floormap_index = Atlamillia::CSVLoader::LoadCSVFile_str(filename.c_str());

	// Load the floormap to int table
	filename = "./levels/" + std::string(_inputfile) + "_props.csv";
	std::vector<std::vector<int>> propmap_int = Atlamillia::CSVLoader::LoadCSVFile_int(filename.c_str());
	filename = "./levels/" + std::string(_inputfile) + "_propsindex.txt";
	std::vector<std::vector<std::string>> propmap_index = Atlamillia::CSVLoader::LoadCSVFile_str(filename.c_str());

	// Load the wallmap to int table
	filename = "./levels/" + std::string(_inputfile) + "_wall.csv";
	std::vector<std::vector<std::vector<int>>> wallmap_int = Atlamillia::CSVLoader::Load3DCSVFile_int(filename.c_str());
	filename = "./levels/" + std::string(_inputfile) + "_wallindex.txt";
	std::vector<std::vector<std::string>> wallmap_index = Atlamillia::CSVLoader::LoadCSVFile_str(filename.c_str());

	// Create the level based on the passed size
	Level* output = new Level(1, 1, floormap_int.at(0).size(), floormap_int.size(), _eng);
	output->SetTileValues(glm::ivec2(0, 0), floormap_int);

	try
	{
		for (size_t y = 0; y < (size_t)output->GetSize().y; y++)
		{
			for (size_t x = 0; x < (size_t)output->GetSize().x; x++)
			{
				for (size_t zY = 0; zY < floormap_int.size(); zY++)
				{
					for (size_t zX = 0; zX < floormap_int.at(zY).size(); zX++)
					{
						if (floormap_int.at(zY).at(zX) != 0)
						{
							// Set the texture to the specified index file, minus 1
							// Because it is assumed 0 == nothing, so the file starts at 1
							output->GetZone(x, y)->GetTile(zX, zY)->SetTexture(
								output->m_engine->GetResourceManager()->GetTexture(
									floormap_index.at(0).at(floormap_int.at(zY).at(zX) - 1),
									output->m_engine->GetRenderer()
								)
							);

							if (propmap_int.at(zY).at(zX) != 0)
							{
								GameObject* temp = new GameObject();
								temp->SetTexture(output->m_engine->GetResourceManager()->GetTexture(propmap_index.front().at(propmap_int.at(zY).at(zX)-1), output->m_engine->GetRenderer()));
								temp->pos = (glm::vec2(zX, zY));
								output->m_props.push_back(temp);
							};

							if (wallmap_int.at(zY).at(zX).size() > 1)
							{
								for (size_t wall = 0; wall < wallmap_int.at(zY).at(zX).size(); wall++)
								{
									if (wallmap_int.at(zY).at(zX).at(wall) == 0) continue;
									GameObject* temp = new GameObject();
									temp->SetTexture(output->m_engine->GetResourceManager()->GetTexture(wallmap_index.front().at(wallmap_int.at(zY).at(zX).at(wall) - 1), output->m_engine->GetRenderer()));
									temp->pos = (glm::vec2(zX, zY));
									output->m_props.push_back(temp);
								}
							}
							else if(wallmap_int.at(zY).at(zX).size() == 1)
							{
								if (wallmap_int.at(zY).at(zX).front() == 0) continue;
								GameObject* temp = new GameObject();
								temp->SetTexture(output->m_engine->GetResourceManager()->GetTexture(wallmap_index.front().at(wallmap_int.at(zY).at(zX).front() - 1), output->m_engine->GetRenderer()));
								temp->pos = (glm::vec2(zX, zY));
								output->m_props.push_back(temp);
							}
						};
					};
				};
			};
		};
	}
	catch (const std::exception& e)
	{
		printf("[Level] Failed to create level! %s", e.what());
	}

	output->UpdateTexture();

	std::sort(output->m_props.begin(), output->m_props.end(), less_than_key());

	return output;
	//out
}

Atlamillia::Level* Atlamillia::Level::CreateLevel(size_t _w, size_t _h, size_t _zW, size_t _zH, Atlamillia::Engine* _eng)
{
	return new Level(_w, _h, _zW, _zH, _eng);
}