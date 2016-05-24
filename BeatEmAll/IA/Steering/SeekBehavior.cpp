
#include "IA\Steering\SeekBehavior.h"
#include "Box2D\Box2D.h"

using namespace IA::Steering;

b2Vec2 SeekBehavior::compute(const IA::Steering::Steerable& steerable) const
{
	b2Vec2 desiredVel = _target - steerable.getCurrentPosition();
	desiredVel.Normalize();
	desiredVel *= steerable.getMaximumVelocity();

	b2Vec2 steering = b2Vec2_zero;
	steering = desiredVel - steerable.getCurrentVelocity();

	steering = SteeringBehavior::truncate(steering, steerable.getMaximumVelocity());
	steering = truncate(steerable.getCurrentVelocity() + steering, steerable.getMaximumVelocity());

	return steering;
}