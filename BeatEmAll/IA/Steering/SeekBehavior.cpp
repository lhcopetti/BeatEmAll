
#include "IA\Steering\SeekBehavior.h"
#include "Box2D\Box2D.h"

using namespace IA::Steering;

b2Vec2 SeekBehavior::compute(const IA::Steering::Steerable& steerable)
{
	b2Vec2 desiredVel = _target - steerable.getCurrentPosition();
	float length = desiredVel.Length();

	desiredVel.Normalize();
	desiredVel *= steerable.getMaximumVelocity();

	if (length < _slowingRadius)
		desiredVel *=  (length / _slowingRadius);

	b2Vec2 steering = b2Vec2_zero;
	steering = desiredVel - steerable.getCurrentVelocity();

	steering = SteeringBehavior::truncate(steering, .05f);
	steering = truncate(steerable.getCurrentVelocity() + steering, steerable.getMaximumVelocity());

	return steering;
}