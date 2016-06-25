
#include "Collision\ContactListener.h"
#include "Collision\Collidable.h"
#include "GameObjects\GameObject.h"

using namespace Collision;

void ContactListener::BeginContact(b2Contact* contact)
{
	if (!contact->IsTouching())
		return;

	b2Body* bodyA = contact->GetFixtureA()->GetBody();
	b2Body* bodyB = contact->GetFixtureB()->GetBody();

	GameComponent::GameObject* collidableA = ((GameComponent::GameObject*) bodyA->GetUserData());
	GameComponent::GameObject* collidableB = ((GameComponent::GameObject*) bodyB->GetUserData());

	if (collidableA)
		collidableA->beginContact(collidableB, contact);

	if (collidableB)
		collidableB->beginContact(collidableA, contact);
}

void ContactListener::EndContact(b2Contact* contact)
{
	b2Body* bodyA = contact->GetFixtureA()->GetBody();
	b2Body* bodyB = contact->GetFixtureB()->GetBody();

	GameComponent::GameObject* collidableA = ((GameComponent::GameObject*) bodyA->GetUserData());
	GameComponent::GameObject* collidableB = ((GameComponent::GameObject*) bodyB->GetUserData());

	if (collidableA)
		collidableA->endContact(collidableB, contact);

	if (collidableB)
		collidableB->endContact(collidableA, contact);
}