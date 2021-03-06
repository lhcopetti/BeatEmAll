#pragma once

#include "GameObjects\Actions\Action.h"
#include "Box2D\Box2D.h"

namespace GameComponent
{
	namespace GameActions
	{
		class VelocityAction : public Action
		{
		public:
			VelocityAction(b2Vec2 newVelocity);

			virtual ~VelocityAction();
			virtual void execute(GameComponent::GameObject& target);

		private:
			b2Vec2 _newVelocity;
		};
	}
}