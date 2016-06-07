#pragma once

#include "Keyboard\KeyboardListener.h"
#include "Mouse\MouseListener.h"

#include "GameObjects\Player.h"

#include "GameObjects\StateMachine\PlayerStates\PlayerState.h"

namespace GameComponent
{
	namespace StateMachine
	{
		namespace PlayerStates
		{
			class ParentPlayerState : 
				public GameComponent::StateMachine::State
			{
			public:
				ParentPlayerState(GameComponent::Player& player, GameComponent::StateMachine::PlayerStates::PlayerState* initialState) : 
					_player(player),
					_childState(initialState) {}

				virtual void handleKeyboard(const std::map<Keys::KeyboardManager::KeyAction, bool>& keys);
				virtual void handleMouse(const sf::Vector2i& vector, bool leftClicked, bool rightClicked);

				virtual void onEnter();
				virtual State* update(float elapsedTime);

			private:
				void aim(b2Vec2 target);
				void move(const std::map<Keys::KeyboardManager::KeyAction, bool>& keys);
				void shoot(b2Vec2 target);

				GameComponent::Player& _player;
				GameComponent::StateMachine::PlayerStates::PlayerState* _childState;
			};
		}
	}
}