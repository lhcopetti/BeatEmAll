#pragma once
#include "GameObjects\Actions\Action.h"
#include "GameObjects\Player.h"

namespace GameComponent
{
	namespace GameActions
	{
		class AimAction : public Action
		{
		public:
			AimAction(GameComponent::Player& target, b2Vec2 origin, b2Vec2 aimTarget);

			virtual ~AimAction();
			virtual void execute();

		private:
			const b2Vec2 _origin;
			const b2Vec2 _aimTarget;
		};
	}
}