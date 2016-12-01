#include "StateManager.h"
#include "AI.h"
#include "../../GameObject/GameObject.h"
#include "../../GameObject/NPC/NPC.h"
#include "../../../ModularPathFinding/AStar/AStar.h"
#include "../../../ModularPathFinding/BreadthFirst/BreadthFirst.h"
#include "../../../ModularPathFinding/DepthFirst/DepthFirst.h"
#include "../../../ModularPathFinding/BestFirst/BestFirst.h"
#include "../../../ModularPathFinding/AStarEpsilon/AStarEpsilon.h"
#include "../../../ModularPathFinding/Dijkstra/Dijkstra.h"
#include "../../../ModularPathFinding/Node.h"

using namespace Atlamillia;

void Atlamillia::StateManager::QueueState(AIState* _state)
{
	_state->SetManager(this);
	m_state_queue.push(this->m_active_state);
	this->m_active_state = _state;
}

std::stack<Atlamillia::AIState*>* StateManager::GetQueue()
{
	return &m_state_queue;
}

void StateManager::AddState(AIState* _state, bool _force)
{
	if (_state != nullptr)
	{
		/*if (_force)
		{
			for (size_t i = 0; i < m_state_queue.size(); i++)
			{
				if (m_state_queue.front() == m_active_state)
				{
					m_state_queue.pop();
				}
				else
				{
					delete m_state_queue.front();
					m_state_queue.pop();
				}
			}
		};*/
		m_state_queue.push(_state);

		m_active_state = _state;
		_state->SetManager(this);

	};
}

void Atlamillia::StateManager::PopState()
{
	delete m_state_queue.top();
	m_state_queue.pop();
	if(m_state_queue.size() == 0 || m_state_queue.top() == nullptr)
		m_active_state = nullptr;
	else
		m_active_state = m_state_queue.top();
}

void StateManager::Update()
{
	UpdatePathPos();
	if (m_active_state != nullptr) m_active_state->Update();
}

void StateManager::SwitchPathAlgorithm(ALGORITHMS _algo)
{
	if (path_algo != nullptr) delete path_algo;
	path_algo = nullptr;
	switch (_algo)
	{
		case ALGORITHMS::ASTAR:
			path_algo = new PathAlgorithms::AStar();
			break;
		case ALGORITHMS::BREADTH_FIRST:
			path_algo = new PathAlgorithms::BreadthFirst();
			break;
		case ALGORITHMS::DEPTH_FIRST:
			path_algo = new PathAlgorithms::DepthFirst();
			break;
		default:
		case ALGORITHMS::BEST_FIRST:
			path_algo = new PathAlgorithms::BestFirst();
			break;
		case ALGORITHMS::ASTAR_EPSILON:
			path_algo = new PathAlgorithms::AStarEpsilon();
			break;
		case ALGORITHMS::DJ_KASTRAS:
			path_algo = new PathAlgorithms::Dijkstra();
			break;
	};
	activePathFinder = _algo;
};

void StateManager::DoPath(glm::ivec2 _start, glm::ivec2 _goal, std::vector<std::vector<NODE*>> _map, bool _allowDiagonal)
{
	if (this == nullptr) return;

	if (_goal.y > 0 || _goal.y < _map.size())
	{
		if (_goal.x > 0 || _goal.x < _map.at(_goal.y).size())
		{
			if (_map.at(_goal.y).at(_goal.x)->isObstacle == true)
			{
				path_algo->path = std::vector<NODE>();
				return;
			}
		}
		else
		{
			path_algo->path = std::vector<NODE>();
			return;
		}
	}
	else
	{
		path_algo->path = std::vector<NODE>();
		return;
	}

	if (path_algo != nullptr)
		path_algo->path = path_algo->GeneratePath(_start, _goal, _map, _allowDiagonal);
}

std::vector<NODE>* StateManager::GetPath()
{
	if (path_algo != nullptr)
	{
		return &path_algo->path;
	}
	else
	{
		return nullptr;
	}
}

StateManager::StateManager(NPC* _parent)
{
	parent = _parent;
};

StateManager::~StateManager()
{
	if (path_algo != nullptr)
		delete path_algo;
	m_active_state = nullptr;
	while (m_state_queue.size() > 0)
	{
		delete m_state_queue.top();
		m_state_queue.pop();
	}
};

void StateManager::UpdatePathPos()
{
	if (path_algo == nullptr) return;
	if (path_algo->path.size() == 0)
	{
		curr_path_pos = 0;
		return;
	}

	float closest = FLT_MAX;
	NODE* current = nullptr;
	size_t current_pos = 0;
	size_t position = 0;
	for each (NODE var in path_algo->path)
	{
		if (glm::distance(parent->pos, glm::vec2(var.pos)) < closest)
		{
			closest = glm::distance(parent->pos, glm::vec2(var.pos));
			current = &var;
			current_pos = position;
		}
		position++;
	}

	curr_path_pos = current_pos;
}