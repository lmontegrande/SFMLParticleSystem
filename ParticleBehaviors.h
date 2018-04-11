#pragma once
#include "Particle.h"

class Particle; // Forward Declaration

enum EasingOption {
	// Todo: Implement EasingOptions
	None, Linear, Exponential, Sin, Cube
};

class ParticleBehavior {
public:
	EasingOption easingOption;
	virtual void updateBehavior(Particle* particle, float deltaTime) = 0;
	float getDelta(float current, float max);
};

class NoChange : public ParticleBehavior {
public:
	NoChange();
	virtual void updateBehavior(Particle* particle, float deltaTime);
};

class SizeChange : public ParticleBehavior {
public:
	float startingSize;
	float endingSize;
	SizeChange();
	virtual void updateBehavior(Particle* particle, float deltaTime);
};

class VelocityChange : public ParticleBehavior {
public:
	sf::Vector2f startingVelocity;
	sf::Vector2f endingVelocity;
	VelocityChange();
	virtual void updateBehavior(Particle* particle, float deltaTime);
};

class RotateChange : public ParticleBehavior {
public:
	float startingRotation;
	float endingRotation;
	RotateChange();
	virtual void updateBehavior(Particle* particle, float deltaTime);
};