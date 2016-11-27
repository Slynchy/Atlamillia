#pragma once

#include <vector>
#include <queue>
#include "../../../ModularPathFinding/pathalgo.h"

namespace Atlamillia
{
	class AIState; 
	class NPC;

	/// Class that handles States for each AI agent
	class StateManager
	{
		protected:
			/// The current state in use by the agent
			AIState* m_active_state;

			/// The queue of states to execute
			std::queue<AIState*> m_state_queue;

			/// The algorithm in use for pathfinding
			PathAlgorithm* path_algo;
		private:
		public:
			/// Enumerator of all eligible algorithms
			enum ALGORITHMS
			{
				ASTAR,
				BREADTH_FIRST,
				DEPTH_FIRST,
				BEST_FIRST,
				ASTAR_EPSILON,
				DJ_KASTRAS
			};

			/// Pointer to the actual object this statemanager is bound to
			NPC* parent;

			/// The activePathFinder in use
			ALGORITHMS activePathFinder;

			/// The pathfinder to default to when switching algorithms
			ALGORITHMS defaultPathfinder;

			/// Getter to the queue
			std::queue<AIState*>* GetQueue();

			/// Adds a state to the queue
			/// \param _state AIState to queue to
			void QueueState(AIState* _state);

			/// Updates the statemanager
			void Update();

			/// Changes the active pathfinder algorithm (ignoring defaultPathfinder!)
			/// \param _algo Enumerator of algorithm to switch to
			void SwitchPathAlgorithm(ALGORITHMS _algo);

			/// Gets the active state
			AIState* GetActiveState()
			{
				return m_active_state;
			}

			/// Switches state to the specified one
			/// \param _state AIState to switch to
			void SwitchState(AIState* _state, bool _force = false);

			/// Getter for the path algo
			inline PathAlgorithm* GetPathAlgo() { return path_algo; }

			/// Does the path of the active algorithm
			/// \param _start Start position
			/// \param _goal End position
			/// \param _map Node map
			/// \param _allowDiagonal Can it move diagonally?
			void DoPath(glm::ivec2 _start, glm::ivec2 _goal, std::vector<std::vector<NODE*>> _map, bool _allowDiagonal = false);

			/// Getter for the actual path
			std::vector<NODE>* GetPath();

			/// Getter for the current position in the active path
			size_t GetPathPos();

			StateManager(NPC* _parent);

			~StateManager();
	};
};