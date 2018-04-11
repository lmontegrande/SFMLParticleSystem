#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Main.hpp>
#include <vector>
#include "ParticleSystem.h"

class ParticleManager {
private:
	std::vector<ParticleSystem*> particleSystems;
public:
	ParticleManager();
	~ParticleManager();

	void update(float deltaTime);
	void render(sf::RenderWindow* window);
	void addParticleSystem(ParticleSystem* particleSystem);
	std::vector<ParticleSystem*> getParticleSystems();
};