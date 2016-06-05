#pragma once

#include "Updatable\Updatable.h"

#include "GameObjects\StateMachine\State.h"

namespace GameComponent
{
	namespace StateMachine
	{
		class StateManager : public Updatable
		{
			GameComponent::StateMachine::State* _currentState;

		public:
			virtual void update(float elapsedTime);
		};
	}
}