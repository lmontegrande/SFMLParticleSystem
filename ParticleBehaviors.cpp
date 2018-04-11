#include "ParticleBehaviors.h"

float lerpF(float, float, float);

NoChange::NoChange()
{
}

void NoChange::updateBehavior(Particle* particle, float deltaTime)
{
	// This does nothing
}

SizeChange::SizeChange()
{	
}

void SizeChange::updateBehavior(Particle* particle, float deltaTime)
{
	float newSize = 0;
	float delta = getDelta(particle->getLifeTimer(), particle->getLifeSpan());
	newSize = lerpF(startingSize, endingSize, delta);
	particle->setSize(newSize);
}

VelocityChange::VelocityChange()
{	
}

void VelocityChange::updateBehavior(Particle* particle, float deltaTime)
{
	sf::Vector2f newVelocity = sf::Vector2f(0, 0);
	float delta = getDelta(particle->getLifeTimer(), particle->getLifeSpan());
	newVelocity = sf::Vector2f(lerpF(startingVelocity.x, endingVelocity.x, delta), lerpF(startingVelocity.y, endingVelocity.y, delta));
	particle->setVelocity(newVelocity);
}

RotateChange::RotateChange()
{
}

void RotateChange::updateBehavior(Particle* particle, float deltaTime)
{
	float newRotationSpeed = 0;
	float delta = getDelta(particle->getLifeTimer(), particle->getLifeSpan());
	newRotationSpeed = lerpF(startingRotation, endingRotation, delta);
	particle->setRotationalSpeed(newRotationSpeed);
}

// t must be [0,1]
float lerpF(float from, float to, float t) {
	float value = (1 - t)*from + t * to;
	return value;
}

float ParticleBehavior::getDelta(float current, float max)
{
	float delta = 0;
	switch (easingOption) {
	case None:
		delta = 0;
		break;
	case Linear:
		delta = current / max;
		break;
	case Exponential:
		delta = (current / max) * (current / max);
		break;
	case Sin:
		delta = sin(current / max * 3.14);
		break;
	case Cube:
		delta = pow(current / max, 3);
		break;
	}
	return delta;
}
