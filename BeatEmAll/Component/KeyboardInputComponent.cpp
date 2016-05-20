#include "Component\KeyboardInputComponent.h"

#include "GameObjects\Actions\Action.h"
#include "GameObjects\Actions\MoveAction.h"

#include "GameObjects\Player.h"

using namespace Components;

namespace GA = GameComponent::GameActions;

KeyboardInputComponent::KeyboardInputComponent()
{

}
KeyboardInputComponent::~KeyboardInputComponent()
{

}

void KeyboardInputComponent::update(GameComponent::Player& player)
{
	_keyboardManager.update();
	handleKeyboard(player, _keyboardManager.keys());

}

void KeyboardInputComponent::handleKeyboard(GameComponent::Player& player, std::map<Keys::KeyboardManager::KeyAction, bool> keys)
{
	using namespace Keys;
	GA::MoveAction::MoveDirection moveDir;

	if (keys[KeyboardManager::KeyAction::MOVE_UP])
		moveDir.yDir = GA::YAxis::UP;
	if (keys[KeyboardManager::KeyAction::MOVE_DOWN])
		moveDir.yDir = GA::YAxis::DOWN;
	if (keys[KeyboardManager::KeyAction::MOVE_LEFT])
		moveDir.xDir = GA::XAxis::LEFT;
	if (keys[KeyboardManager::KeyAction::MOVE_RIGHT])
		moveDir.xDir = GA::XAxis::RIGHT;

	GA::MoveAction* moveAction = new GA::MoveAction(player, moveDir);
	player.addAction(moveAction);
}