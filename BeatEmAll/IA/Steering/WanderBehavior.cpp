
#include "IA\Steering\WanderBehavior.h"
#include "Box2D\Box2D.h"
#include "DebugBoxDraw\WorldConstants.h"

using namespace IA::Steering;

float WanderBehavior::_wanderAngleChange = 3.f;

WanderBehavior::WanderBehavior(float circleRadius) : _circleRadius(circleRadius)
{
	_displacement.Set(0, +1);
	_wanderAngle = 0.f;
}

b2Vec2 WanderBehavior::compute(const IA::Steering::Steerable& steerable)
{
	b2Vec2 circleCenter = steerable.getCurrentVelocity();
	circleCenter.Normalize();
	circleCenter *= _circleRadius;

	b2Vec2 wanderForce;
	wanderForce.Set(sin(_wanderAngle * DEGTORAD), cos(_wanderAngle * DEGTORAD));
	wanderForce.Normalize();
	wanderForce *= _circleRadius;

	_wanderAngle += rand() % 2 == 0 ? +_wanderAngleChange : -_wanderAngleChange;

	b2Vec2 resultingForce = b2Vec2(circleCenter.x + wanderForce.x, circleCenter.y + wanderForce.y);
	return  truncate(steerable.getCurrentVelocity() + resultingForce, steerable.getMaximumVelocity());

	//return resultingForce;



	/*b2Vec2 desiredVel = _target - steerable.getCurrentPosition();
	desiredVel.Normalize();
	desiredVel *= steerable.getMaximumVelocity();

	b2Vec2 steering = b2Vec2_zero;
	steering = desiredVel - steerable.getCurrentVelocity();

	steering = SteeringBehavior::truncate(steering, steerable.getMaximumVelocity());
	steering = truncate(steerable.getCurrentVelocity() + steering, steerable.getMaximumVelocity());

	return steering;*/
}