#include "ParticleSystem.h"
#include <iostream>
#include <string>

ParticleSystemArgs::ParticleSystemArgs() {
	position = sf::Vector2f(0, 0);
	texture = new sf::Texture();
	color = sf::Color::White;
	duration = 5;
	emissionRate = .01;
	startingSpeed = 100;
	acceleration = sf::Vector2f(0, 0);
	accelerationVariance = sf::Vector2f(0, 0);
	size = 25;
	sizeVariance = 0;
	emissionAngle = 0;
	emissionAngleVariance = 0;
	rotationalSpeed = 0;
	rotationalSpeedVariance = 0;
	particleLifeSpan = 1;
	particleLifeSpanVariance = 0;
	particleBehavior = new NoChange();
}

ParticleSystemArgs::~ParticleSystemArgs() {

}

// Default Particle System Will Have Random Elements
ParticleSystem::ParticleSystem()
{
	_position = sf::Vector2f(400, 300);
	_acceleration.x = 0;
	_acceleration.y = 400;
	_accelerationVariance.x = 0;
	_accelerationVariance.y = 0;
	_startingSpeed = 200;
	_emissionAngle = 270;
	_emissionAngleVariance = 45;
	_rotationalSpeed = -90;
	_rotationalSpeedVariance = 180;
	_emissionRate = .0001;
	_particleLifeSpan = 3;
	_particleLifeSpanVariance = 0;
	_duration = 10;
	_size = 100;
	_sizeVariance = 0;
	_color = sf::Color::White;

	/*SizeChange* sizeChange = new SizeChange();
	sizeChange->startingSize = 100;
	sizeChange->endingSize = 100;
	sizeChange->easingOption = None;
	_particleBehavior = sizeChange;*/
	_particleBehavior = new NoChange();

	_texture = new sf::Texture();
	_texture->loadFromFile("resources/MJ.png");

	_emissionTimer = 0;
	_durationTimer = 0;
	_isReadyToBeDestroyedTimer = 0;
	
	isDone = false;
}

ParticleSystem::ParticleSystem(ParticleSystemArgs* args)
{
	_position = args->position;
	_texture = args->texture;
	_color = args->color;
	_duration = args->duration;
	_emissionRate = args->emissionRate;
	_startingSpeed = args->startingSpeed;
	_acceleration = args->acceleration;
	_accelerationVariance = args->accelerationVariance;
	_size = args->size;
	_sizeVariance = args->sizeVariance;
	_emissionAngle = args->emissionAngle;
	_emissionAngleVariance = args->emissionAngleVariance;
	_rotationalSpeed = args->rotationalSpeed;
	_rotationalSpeedVariance = args->rotationalSpeedVariance;
	_particleLifeSpan = args->particleLifeSpan;
	_particleLifeSpanVariance = args->particleLifeSpanVariance;
	_particleBehavior = args->particleBehavior;

	_emissionTimer = 0;
	_durationTimer = 0;
	_isReadyToBeDestroyedTimer = 0;

	isDone = false;

	delete args;
}

ParticleSystem::~ParticleSystem()
{
	for (Particle* particle : _particles) {
		delete particle;
	}
	delete _texture;
	delete _particleBehavior;
}

void ParticleSystem::update(float deltaTime)
{
	// Stop emitting and wait to be killed by manager
	if (_durationTimer > _duration) {
		if (!isDone) {
			isDone = true;
		}
		_isReadyToBeDestroyedTimer += deltaTime;
		if (_isReadyToBeDestroyedTimer > _particleLifeSpan) {
			isReadyToBeDestroyed = true;
		}
	}
	else 
	{
		// Emit at intervals
		_emissionTimer += deltaTime;
		_durationTimer += deltaTime;
		if (_emissionTimer > _emissionRate) {
			_emissionTimer -= _emissionRate;
			emit();
		}
	}

	// Iterate through particles and update.  If their ready to be destroyed, destroy them.
	std::vector<Particle*>::iterator particleItr;
	for (particleItr = _particles.begin(); particleItr != _particles.end();) {
		if ((*particleItr)->isDone) {
			particleItr = _particles.erase(particleItr);
		}
		else 
		{
			(*particleItr)->update(deltaTime);
			++particleItr;
		}
	}
}

void ParticleSystem::render(sf::RenderWindow *window)
{
	for (Particle* particle : _particles) {
		particle->render(window);
	}
}

void ParticleSystem::decreaseParticles()
{
	_emissionRate *= 2;
}

void ParticleSystem::increaseParticles()
{
	_emissionRate /= 2;
}

void ParticleSystem::emit()
{
	sf::Vector2f particlePosition(_position);
	sf::Vector2f particleVelocity = sf::Vector2f(cosf(getEmissionAngle()), sinf(getEmissionAngle())) * _startingSpeed;
	sf::Vector2f particleAcceleration(_acceleration);
	sf::Texture* particleTexture = _texture;
	sf::Color particleColor = _color;
	float particleRotationalSpeed = getRotationSpeed();
	float particleSize = getSize();
	float particleLifeSpan = getParticleLifeSpan();
	ParticleBehavior* particleBehavior = _particleBehavior;

	_particles.push_back(new Particle(particlePosition, particleVelocity, particleAcceleration, particleTexture, particleColor, particleRotationalSpeed, particleSize, particleLifeSpan, particleBehavior));
}

sf::Vector2f ParticleSystem::getAcceleration() {
	float startingX = _acceleration.x + (rand() % (int)_accelerationVariance.x);
	float startingY = _acceleration.y + (rand() % (int)_accelerationVariance.y);
	return sf::Vector2f(startingX, startingY);
}

float ParticleSystem::getParticleLifeSpan() {
	float startingLifeSpan = _particleLifeSpan;
	if ((int)_particleLifeSpanVariance != 0)
		startingLifeSpan += (rand() % (int)_particleLifeSpanVariance);
	return startingLifeSpan;
}

float ParticleSystem::getSize() {
	float startingSize = _size;
	if ((int)_sizeVariance != 0)
		startingSize += (rand() % (int)_sizeVariance);
	return startingSize;
}

float ParticleSystem::getRotationSpeed() {
	float startingRotationSpeed = _rotationalSpeed;
	if ((int)_rotationalSpeed != 0)
		startingRotationSpeed += (rand() % (int)_rotationalSpeedVariance);
	return startingRotationSpeed;
}

float ParticleSystem::getEmissionAngle() {
	float startingAngle = _emissionAngle - _emissionAngleVariance;
	if ((int)_emissionAngleVariance != 0)
		startingAngle += (rand() % (int)_emissionAngleVariance * 2);
	return (degToRads(startingAngle));
}

float ParticleSystem::degToRads(float deg) {
	return (deg * 3.14159) / 180;
}