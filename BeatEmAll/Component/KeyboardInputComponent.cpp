#include "Component\KeyboardInputComponent.h"

#include "GameObjects\Actions\Action.h"
#include "GameObjects\Actions\MoveAction.h"
#include "GameObjects\Actions\ShootAction.h"
#include "GameObjects\Actions\AimAction.h"

#include "GameObjects\Player.h"

#include "DebugBoxDraw\WorldConstants.h"

using namespace Components;
namespace GA = GameComponent::GameActions;


KeyboardInputComponent::KeyboardInputComponent(Keys::KeyboardManager& keyboardManager, MouseComponent::MouseManager& mouseManager)
	:_keyboardManager(keyboardManager), _mouseManager(mouseManager)
{

}
KeyboardInputComponent::~KeyboardInputComponent()
{

}

void KeyboardInputComponent::update(GameComponent::Player& player)
{
	_mouseManager.update();
	handleMouse(player, _mouseManager);

	_keyboardManager.update();
	handleKeyboard(player, _keyboardManager.keys());


}

void KeyboardInputComponent::handleKeyboard(GameComponent::Player& player, const std::map<Keys::KeyboardManager::KeyAction, bool>& keys)
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

	GA::MoveAction* moveAction = new GA::MoveAction(player, moveDir);
	player.addAction(moveAction);
}

void KeyboardInputComponent::handleMouse(GameComponent::Player& player, MouseComponent::MouseManager& mouse)
{
	/* We can safely assume there will no vector.x as big as MAX_INT. Cast is OK! */
	const sf::Vector2f mousePosF = sf::Vector2f(static_cast<float>(mouse.mousePos().x), static_cast<float>(mouse.mousePos().y));

	GA::Action* aimAction = new GA::AimAction(player, player.body()->GetPosition(), WorldConstants::sfmlToPhysics(mousePosF));
	player.addAction(aimAction);

	if (mouse.left())
	{
		b2Vec2 target = WorldConstants::sfmlToPhysics(mousePosF);
		GA::ShootAction* shootAction = new GA::ShootAction(player, player.body()->GetPosition(), target);
		player.addAction(shootAction);
	}
}