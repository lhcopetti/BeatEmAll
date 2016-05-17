#pragma once
#include "GameObjects\Actions\Action.h"

namespace GameComponent
{
	namespace GameActions
	{
		class ShootAction : public Action
		{
		public:
			ShootAction(GameComponent::GameObject& target, b2Vec2 originTarget, b2Vec2 shotTarget);

			virtual ~ShootAction();
			virtual void execute();

		private:
			const b2Vec2 _originTarget;
			const b2Vec2 _shotTarget;
		};
	}
}