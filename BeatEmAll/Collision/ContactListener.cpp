
#include "Collision\ContactListener.h"
#include "Collision\Collidable.h"

using namespace Collision;

void ContactListener::BeginContact(b2Contact* contact)
{
	if (!contact->IsTouching())
		return;

	b2Body* bodyA = contact->GetFixtureA()->GetBody();
	b2Body* bodyB = contact->GetFixtureB()->GetBody();

	Collision::Collidable* collidableA = ((Collision::Collidable*) bodyA->GetUserData());
	Collision::Collidable* collidableB = ((Collision::Collidable*) bodyB->GetUserData());

	if (collidableA)
		collidableA->beginContact(collidableB, contact);

	if (collidableB)
		collidableB->beginContact(collidableA, contact);
}

void ContactListener::EndContact(b2Contact* contact)
{

}