#pragma once
#include "GameObjects\Actions\Action.h"
#include "GameObjects\Player.h"

namespace GameComponent
{
	namespace GameActions
	{
		class ShootAction : public Action
		{
		public:
			ShootAction(b2Vec2 originTarget, b2Vec2 shotTarget);

			virtual ~ShootAction();
			virtual void execute(GameComponent::GameObject& target);

		private:
			const b2Vec2 _originTarget;
			const b2Vec2 _shotTarget;
		};
	}
}