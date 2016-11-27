#pragma once

namespace Atlamillia
{
	class StateManager;

	class AIState
	{
	protected:
		/// Pointer to the statemanager responsible for this state
		StateManager* parent_manager;
	private:
	public:
		AIState* parent_state;

		/// Start function is called before the state is updated and only called once
		virtual void Start()
		{

		}
		/// Stop function is called before the state is deleted and only called once
		virtual void Stop()
		{

		}
		/// Update function is called every frame
		virtual void Update()
		{

		}

		/// Getter for the statemanager
		StateManager* GetManager()
		{
			return parent_manager;
		}

		/// Setter for the statemanager
		void SetManager(StateManager* _param)
		{
			parent_manager = _param;
		}

		AIState()
		{

		}
		AIState(StateManager* _parent)
		{

		}
		~AIState()
		{

		}
	};

};