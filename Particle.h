#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Main.hpp>
#include "ParticleBehaviors.h"

class ParticleBehavior; // Forward Declaration

class Particle {
private:
	sf::RectangleShape _rectangleShape;
	sf::Vector2f _velocity;
	sf::Vector2f _acceleration;
	sf::Color _color;
	ParticleBehavior* _behavior;
	float _rotationalSpeed;
	float _lifeSpan;
	float _startingSize;

	float _lifeTimer;

	Particle(); // Hide Default Constructor (I don't know if you even have to do this)

public:
	bool isDone;

	Particle(sf::Vector2f position, sf::Vector2f velocity, sf::Vector2f acceleration, sf::Texture* texture, sf::Color color, float rotationalSpeed, float size, float lifeSpan, ParticleBehavior* particleBehavior);
	~Particle();
	void update(float deltaTime);
	void render(sf::RenderWindow *window);
	ParticleBehavior* getBehavior();
	void setBehavior(ParticleBehavior* particleBehavior);

	// Created the getters and setters to help with Strategy Pattern
	sf::Vector2f getVelocity();
	void setVelocity(sf::Vector2f velocity);
	float getStartingSize();
	void setSize(float size);
	float getRotationalSpeed();
	void setRotationalSpeed(float rotationalSpeed);
	float getLifeSpan();
	float getLifeTimer();
};