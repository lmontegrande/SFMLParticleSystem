#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Main.hpp>
#include "ParticleManager.h"
#include "ParticleSystem.h"
#include "Particle.h"

void init();
void run();
void handleInput();
void update();
void render();

sf::RenderWindow *window;
ParticleManager *particleManager;
boolean isDone;
float timePassed;

int main()
{
	char path[MAX_PATH];
	GetCurrentDirectoryA(MAX_PATH, path);
	MessageBoxA(NULL, path, "Current Directory", MB_OK);
	run();
	return 0;
}

void init() {
	window = new sf::RenderWindow(sf::VideoMode(800, 600), "Particle System Implementation");
	particleManager = new ParticleManager();
}

void run() {
	init();
	while (!isDone && window->isOpen()) {
		sf::Event event;
		while (window->pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window->close();
		}
		handleInput();
		update();
		render();
	}
	delete particleManager;
}

void handleInput() {
	// Create Particle Systems Here
	static bool num1PressedUp = false;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1)) {
		if (!num1PressedUp) {
			num1PressedUp = true;
			ParticleSystem *particleSystem = new ParticleSystem(); // Default Particle System
			particleManager->addParticleSystem(particleSystem);
		}
	}
	else 
	{
		if (num1PressedUp) {
			num1PressedUp = false;
		}
	}

	static bool num2PressedUp = false;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2)) {
		if (!num2PressedUp) {
			num2PressedUp = true;
			ParticleSystemArgs* particleSystemArgs = new ParticleSystemArgs();
			particleSystemArgs->size = 100;
			particleSystemArgs->sizeVariance = 50;
			particleSystemArgs->position = sf::Vector2f(100, 100);
			particleSystemArgs->texture = new sf::Texture();
			particleSystemArgs->texture->loadFromFile("resources/Erin.png");
			particleSystemArgs->emissionAngleVariance = 15;
			particleSystemArgs->duration = 10;
			particleSystemArgs->rotationalSpeed = -5;
			particleSystemArgs->rotationalSpeedVariance = 10;
			particleSystemArgs->particleLifeSpan = 3;
			particleSystemArgs->particleLifeSpanVariance = 1;
			particleSystemArgs->emissionRate = 0.1;
			//particleSystemArgs->acceleration = sf::Vector2f(0, 100);

			VelocityChange* velocityChange = new VelocityChange();
			velocityChange->easingOption = Cube;
			velocityChange->startingVelocity = sf::Vector2f(100,0);
			velocityChange->endingVelocity = sf::Vector2f(500, 0);
			particleSystemArgs->particleBehavior = velocityChange;

			ParticleSystem *particleSystem2 = new ParticleSystem(particleSystemArgs);
			particleManager->addParticleSystem(particleSystem2);
		}
	}
	else 
	{
		if (num2PressedUp) {
			num2PressedUp = false;
		}
	}

	static bool num3PressedUp = false;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3)) {
		if (!num3PressedUp) {
			num3PressedUp = true;
			ParticleSystemArgs* particleSystemArgs = new ParticleSystemArgs();
			particleSystemArgs->size = 50;
			particleSystemArgs->position = sf::Vector2f(700, 500);
			particleSystemArgs->texture = new sf::Texture();
			particleSystemArgs->texture->loadFromFile("resources/Colin.png");
			particleSystemArgs->emissionAngle = 180;
			particleSystemArgs->emissionAngleVariance = 45;
			particleSystemArgs->duration = 10;
			particleSystemArgs->particleLifeSpan = 2;
			particleSystemArgs->particleLifeSpanVariance = 1;
			particleSystemArgs->emissionRate = 0.1;
			particleSystemArgs->acceleration = sf::Vector2f(0, -100);

			RotateChange* rotateChange = new RotateChange();
			rotateChange->easingOption = Sin;
			rotateChange->startingRotation = -720;
			rotateChange->endingRotation = 360;
			particleSystemArgs->particleBehavior = rotateChange;

			ParticleSystem *particleSystem2 = new ParticleSystem(particleSystemArgs);
			particleManager->addParticleSystem(particleSystem2);
		}
	}
	else 
	{
		if (num3PressedUp) {
			num3PressedUp = false;
		}
	}

	static bool num4PressedUp = false;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num4)) {
		if (!num4PressedUp) {
			num4PressedUp = true;
			ParticleSystemArgs* particleSystemArgs = new ParticleSystemArgs();
			particleSystemArgs->position = sf::Vector2f(0, 600);
			particleSystemArgs->texture = new sf::Texture();
			particleSystemArgs->texture->loadFromFile("resources/Jim.png");
			particleSystemArgs->emissionAngle = 270;
			particleSystemArgs->emissionAngleVariance = 45;
			particleSystemArgs->startingSpeed = 100;
			particleSystemArgs->duration = 10;
			particleSystemArgs->particleLifeSpan = 3;
			particleSystemArgs->particleLifeSpanVariance = 1;
			particleSystemArgs->emissionRate = 0.1;
			particleSystemArgs->acceleration = sf::Vector2f(0, -100);

			SizeChange* sizeChange = new SizeChange();
			sizeChange->easingOption = Exponential;
			sizeChange->startingSize = 0;
			sizeChange->endingSize = 500;
			particleSystemArgs->particleBehavior = sizeChange;

			ParticleSystem *particleSystem2 = new ParticleSystem(particleSystemArgs);
			particleManager->addParticleSystem(particleSystem2);
		}
	}
	else
	{
		if (num4PressedUp) {
			num4PressedUp = false;
		}
	}

	static bool isLeftPressed = false;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
		if (!isLeftPressed) {
			isLeftPressed = true;
			std::vector<ParticleSystem*> particleSystems = particleManager->getParticleSystems();
			std::vector<ParticleSystem*>::iterator iterator;
			for (iterator = particleSystems.begin(); iterator != particleSystems.end(); iterator++) {
				(*iterator)->decreaseParticles();
			}
		}
	}
	else 
	{
		if (isLeftPressed) {
			isLeftPressed = false;
		}
	}

	static bool isRightPressed = false;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
		if (!isRightPressed) {
			isRightPressed = true;
			std::vector<ParticleSystem*> particleSystems = particleManager->getParticleSystems();
			std::vector<ParticleSystem*>::iterator iterator;
			for (iterator = particleSystems.begin(); iterator != particleSystems.end(); iterator++) {
				(*iterator)->increaseParticles();
			}
		}
	}
	else
	{
		if (isRightPressed) {
			isRightPressed = false;
		}
	}
}

void update() {
	static sf::Clock clock; // Don't know how to make this global
	float deltaTime = clock.restart().asSeconds();
	particleManager->update(deltaTime);

	// Debug Time Elapsed
	timePassed += deltaTime;
	window->setTitle(std::to_string(timePassed));
}

void render() {
	window->clear();
	particleManager->render(window);
	window->display();

	// Debug Crap
	/*sf::CircleShape shape(100.f);
	shape.setFillColor(sf::Color::Green);

	window->clear();
	window->draw(shape);
	window->display();*/
	// End Debug Crap
}