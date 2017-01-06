#pragma once

#include "../GameObject.h"
#include "../../Engine/AI/StateManager.h"

namespace Atlamillia
{

	class NPC : public GameObject
	{
		private:
			float frame;
		protected:
			Atlamillia::StateManager* brain;
			bool m_isAttacking = false;
		public:
			float m_speed;
			float GetSpeed() { return m_speed; };

			void IsAttacking(bool _attk)
			{
				m_isAttacking = _attk;
			}
			bool IsAttacking()
			{
				return m_isAttacking;
			}

			float GetFrame() { return frame; };
			void SetFrame(float _frm) { frame = _frm; };

			virtual Atlamillia::StateManager* GetStateManager()
			{
				return brain;
			}

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