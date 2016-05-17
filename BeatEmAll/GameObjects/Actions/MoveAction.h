#pragma once
#include "GameObjects\Actions\Action.h"

namespace GameComponent
{
	namespace GameActions
	{
		/*
		 *	Not using strongly typed enums (eg: enum class XAxisDirection)
		 * because it doesn't support silent int conversions.
		 */

		namespace XAxis 
		{
			enum Dir
			{
				LEFT = -1,
				RIGHT = 1,
				NONE = 0
			};
		}

		namespace YAxis
		{
			enum Dir
			{
				UP = -1,
				DOWN = +1,
				NONE = 0
			};
		}
		class MoveAction : public Action
		{
		public:
			struct MoveDirection
			{
				XAxis::Dir xDir = XAxis::Dir::NONE;
				YAxis::Dir yDir = YAxis::Dir::NONE;
			};

			MoveAction(GameComponent::GameObject& target, MoveDirection moveDirection);

			virtual ~MoveAction();
			virtual void execute();

		private:
			const MoveDirection _moveDir;
		};
	}
}