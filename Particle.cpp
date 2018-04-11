#include "Particle.h"

Particle::Particle(sf::Vector2f position, sf::Vector2f velocity, sf::Vector2f acceleration, sf::Texture* texture, sf::Color color, float rotationalSpeed, float size, float lifeSpan, ParticleBehavior* particleBehavior)
{
	_rectangleShape.setPosition(position);
	_rectangleShape.setTexture(texture, false);
	_rectangleShape.setFillColor(color);
	_rectangleShape.setSize(sf::Vector2f(size, size));
	_rectangleShape.setOrigin(_rectangleShape.getLocalBounds().width/2, _rectangleShape.getLocalBounds().height/2);
	_lifeSpan = lifeSpan;
	
	_startingSize = size;
	_velocity = velocity;
	_acceleration = acceleration;
	_rotationalSpeed = rotationalSpeed;

	_behavior = particleBehavior;
	_lifeTimer = 0;
	isDone = false;
}

Particle::~Particle()
{
	delete _behavior;
}

void Particle::update(float deltaTime)
{
	_lifeTimer += deltaTime;
	if (_lifeTimer > _lifeSpan) {
		isDone = true;
	}
	else 
	{
		_behavior->updateBehavior(this, deltaTime);
		_rectangleShape.move(_velocity * deltaTime);
		_rectangleShape.rotate(_rotationalSpeed * deltaTime);
		_velocity += (_acceleration * deltaTime);
	}
}

void Particle::render(sf::RenderWindow * window)
{
	window->draw(_rectangleShape);
}

ParticleBehavior* Particle::getBehavior()
{
	return _behavior;
}

void Particle::setBehavior(ParticleBehavior * particleBehavior)
{
	if (_behavior != nullptr)
		delete _behavior;
	_behavior = particleBehavior;
}

sf::Vector2f Particle::getVelocity()
{
	return _velocity;
}

void Particle::setVelocity(sf::Vector2f velocity)
{
	_velocity = velocity;
}

float Particle::getStartingSize()
{
	return _startingSize;
}

void Particle::setSize(float size)
{
	_rectangleShape.setSize(sf::Vector2f(size, size));
}

float Particle::getRotationalSpeed()
{
	return _rotationalSpeed;
}

void Particle::setRotationalSpeed(float rotationalSpeed)
{
	_rotationalSpeed = rotationalSpeed;
}

float Particle::getLifeSpan()
{
	return _lifeSpan;
}

float Particle::getLifeTimer()
{
	return _lifeTimer;
}
