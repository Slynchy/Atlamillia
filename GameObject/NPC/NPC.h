#pragma once

#include "../GameObject.h"
#include "../../Engine/AI/StateManager.h"

namespace Atlamillia
{
	/// Class for NPC; not pure virtual because it can be instantiated on its own
	class NPC : public GameObject
	{
		private:

			/// The current animation frame
			float frame;

		protected:

			/// The brain of the NPC; handles states and pathing
			Atlamillia::StateManager* brain;

			/// Is this NPC attacking?
			bool m_isAttacking = false;

			/// Is this NPC alive?
			bool m_isAlive = true;

		public:

			/// How fast can the NPC move?
			float m_speed;

			/// Gets the NPCs speed
			/// \deprecated m_speed is now public
			float GetSpeed() { return m_speed; };

			/// Sets the NPCs attack state
			void IsAttacking(bool _attk)
			{
				m_isAttacking = _attk;
			}
			/// Gets the NPCs attack state
			bool IsAttacking()
			{
				return m_isAttacking;
			}

			/// Gets the NPCs alive status
			bool isAlive()
			{
				return m_isAlive;
			}

			/// Kills the NPC
			virtual void Kill();

			/// Getter for animation frame
			float GetFrame() { return frame; };
			/// Setter for animation frame
			void SetFrame(float _frm) { frame = _frm; };

			/// Gets the brain of the NPC
			virtual Atlamillia::StateManager* GetStateManager()
			{
				return brain;
			}

			/// Moves the NPC towards a destination at their speed
			void MoveTowards(glm::vec2 _dst);

			NPC()
			{
				brain = new StateManager(this);
			}

			~NPC()
			{
				if(brain != nullptr)
					delete brain;
			}
	};

}