#include "ParticleManager.h"

ParticleManager::ParticleManager()
{
}

ParticleManager::~ParticleManager()
{
	for (ParticleSystem* particleSystem : particleSystems) {
		delete particleSystem;
	}
}

void ParticleManager::update(float deltaTime)
{
	for (ParticleSystem* particleSystem : particleSystems) {
		particleSystem->update(deltaTime);
	}
}

void ParticleManager::render(sf::RenderWindow* window)
{
	for (ParticleSystem* particleSystem : particleSystems) {
		particleSystem->render(window);
	}
}

void ParticleManager::addParticleSystem(ParticleSystem *particleSystem)
{
	particleSystems.push_back(particleSystem);
}

std::vector<ParticleSystem*> ParticleManager::getParticleSystems()
{
	return particleSystems;
}
