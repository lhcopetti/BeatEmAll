#include "GameObjects\StateMachine\PlayerStates\ParentPlayerState.h"

#include "GameObjects\Actions\MoveAction.h"
#include "GameObjects\Actions\VelocityAction.h"
#include "GameObjects\Actions\AimAction.h"
#include "GameObjects\Actions\ShootAction.h"

#include "DebugBoxDraw\WorldConstants.h"

using namespace GameComponent::StateMachine;
namespace GA = GameComponent::GameActions;

void PlayerStates::ParentPlayerState::handleKeyboard(const std::map<Keys::KeyboardManager::KeyAction, bool>& keys)
{
	move(keys);
}

void PlayerStates::ParentPlayerState::handleMouse(const sf::Vector2i& vector, bool leftClicked, bool rightClicked)
{
	/* We can safely assume there will no vector.x as big as MAX_INT. Cast is OK! */
	const sf::Vector2f mousePosF = sf::Vector2f(static_cast<float>(vector.x), static_cast<float>(vector.y));

	aim(WorldConstants::sfmlToPhysics(mousePosF));

	if (leftClicked)
		shoot(WorldConstants::sfmlToPhysics(mousePosF));
}

State* PlayerStates::ParentPlayerState::update(float elapsedTime)
{
	return _childState->update(elapsedTime);
}

void PlayerStates::ParentPlayerState::aim(b2Vec2 target)
{
	GA::Action* aimAction = new GA::AimAction(_player.getCurrentPosition(), target);
	_player.addAction(aimAction);
}

void PlayerStates::ParentPlayerState::move(const std::map<Keys::KeyboardManager::KeyAction, bool>& keys)
{
	using namespace Keys;
	GA::MoveAction::MoveDirection moveDir;

	if (keys.at(KeyboardManager::KeyAction::MOVE_UP))
		moveDir.yDir = GA::YAxis::UP;
	if (keys.at(KeyboardManager::KeyAction::MOVE_DOWN))
		moveDir.yDir = GA::YAxis::DOWN;
	if (keys.at(KeyboardManager::KeyAction::MOVE_LEFT))
		moveDir.xDir = GA::XAxis::LEFT;
	if (keys.at(KeyboardManager::KeyAction::MOVE_RIGHT))
		moveDir.xDir = GA::XAxis::RIGHT;

	float pVelocity = _player.getMaximumVelocity();
	b2Vec2 nextVel(moveDir.xDir * pVelocity, moveDir.yDir * pVelocity);

	GA::VelocityAction* velAction = new GA::VelocityAction(nextVel);
	_player.addAction(velAction);
}

void PlayerStates::ParentPlayerState::shoot(b2Vec2 target)
{
	GA::ShootAction* shootAction = new GA::ShootAction(_player.getCurrentPosition(), target);
	_player.addAction(shootAction);
}