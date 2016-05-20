#include "RandomInputComponent.h"

#include "GameObjects\Player.h"
#include "SFML\Config.hpp"

using namespace Components;
namespace GA = GameComponent::GameActions;

RandomInputComponent::RandomInputComponent()
{

}

RandomInputComponent::~RandomInputComponent() 
{

}

void RandomInputComponent::update(GameComponent::Player& player)
{
	GA::MoveAction::MoveDirection moveDir;

	/* 75% of chance to keep on track */
	if (rand() % 100 <= 95)
		moveDir = _lastMove;
	else
	{
		GA::XAxis::Dir xDir[3] = { GA::XAxis::NONE , GA::XAxis::LEFT, GA::XAxis::RIGHT};
		GA::YAxis::Dir yDir[3] = { GA::YAxis::NONE , GA::YAxis::UP, GA::YAxis::DOWN };

		moveDir.xDir = xDir[rand() % 3];
		moveDir.yDir = yDir[rand() % 3];

		_lastMove = moveDir;
	}

	GA::MoveAction* moveAction = new GA::MoveAction(player, moveDir);
	player.addAction(moveAction);
}