#pragma once

namespace GameComponent
{
	namespace StateMachine 
	{
		class State
		{
		public:
			virtual State* update(float elapsedTime) = 0;
		};
	}
}