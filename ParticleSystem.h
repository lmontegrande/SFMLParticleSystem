#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Main.hpp>
#include <vector>
#include "Particle.h"

struct ParticleSystemArgs {
public:
	sf::Vector2f position;
	sf::Texture* texture;
	sf::Color color;
	float duration;
	float emissionRate;
	float startingSpeed;
	sf::Vector2f acceleration;
	sf::Vector2f accelerationVariance;
	float size;
	float sizeVariance;
	float emissionAngle;
	float emissionAngleVariance;
	float rotationalSpeed;
	float rotationalSpeedVariance;
	float particleLifeSpan;
	float particleLifeSpanVariance;
	ParticleBehavior *particleBehavior;

	ParticleSystemArgs();
	~ParticleSystemArgs();
};

class ParticleSystem {
private:
	std::vector<Particle*> _particles;
	sf::Vector2f _acceleration;
	sf::Vector2f _accelerationVariance;
	sf::Vector2f _position;
	sf::Texture* _texture;
	sf::Color _color;
	ParticleBehavior* _particleBehavior;
	float _duration;
	float _emissionRate;
	float _startingSpeed;
	float _size;
	float _sizeVariance;
	float _emissionAngle;
	float _emissionAngleVariance;
	float _rotationalSpeed;
	float _rotationalSpeedVariance;
	float _particleLifeSpan;
	float _particleLifeSpanVariance;
	float _emissionTimer;
	float _durationTimer;
	float _isReadyToBeDestroyedTimer;

	void emit();
	sf::Vector2f getAcceleration();
	float getParticleLifeSpan();
	float getSize();
	float getRotationSpeed();
	float getEmissionAngle();
	float degToRads(float deg);
public:
	ParticleSystem();
	ParticleSystem(ParticleSystemArgs* args);
	~ParticleSystem();
	void update(float deltaTime);
	void render(sf::RenderWindow* window);

	void decreaseParticles();
	void increaseParticles();
	bool isDone;
	bool isReadyToBeDestroyed;
};