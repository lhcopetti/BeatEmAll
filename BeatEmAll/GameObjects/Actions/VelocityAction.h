#pragma once
#include "GameObjects\Actions\Action.h"

namespace GameComponent
{
	namespace GameActions
	{
		class VelocityAction : public Action
		{
		public:
			VelocityAction(GameComponent::GameObject& target, b2Vec2 newVelocity);

			virtual ~VelocityAction();
			virtual void execute();

		private:
			b2Vec2 _newVelocity;
		};
	}
}