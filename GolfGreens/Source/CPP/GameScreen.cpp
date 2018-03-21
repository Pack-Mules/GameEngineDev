
#include "GameScreen.h"
#include "Screen.h"
#include "GameObject.h"
#include "PhysicsEngine.h"

#include <iostream>
#include <Windows.h>
#include "SFML\Audio.hpp"

PhysicsEngine* physics;

GameScreen::GameScreen() {
	LoadAssets();
	LoadObjects();
}

void GameScreen::Update(sf::RenderWindow &win) {
	float dt = 0.01f;// &clock.getElapsedTime().asMilliseconds;
	parentCircle->Update(dt);
	childCircle->Update(dt);
	//moving circle
	if (parentCircle->transform.x <= 0 && parentCircleRight == false)
		parentCircleRight = true;
	else if (parentCircle->transform.x + parentCircle->cs.getLocalBounds().width >= win.getSize().x
		&& parentCircleRight == true)
		parentCircleRight = false;

	if (childCircle->transform.y <= 0)
		childCircleUp = true;
	else if (childCircle->transform.y >= 200)
		childCircleUp = false;

	if (parentCircleRight)
	{
	
		parentCircle->transform.Translate(Vector3(0.1f, 0, 0));
		parentCircle->transform.ChangeScale(Vector3(1.0f * 1.0001f, 1.0f * 1.0001f, 1.0f * 1.0001f));
	}
	else
	{
		parentCircle->RemoveChild(childCircle);
		parentCircle->transform.Translate(Vector3(-0.1f, 0, 0));
		parentCircle->transform.ChangeScale(Vector3(1.0f / 1.0001f, 1.0f / 1.0001f, 1.0f / 1.0001f));
	}

	if (childCircleUp)
		childCircle->transform.Translate(Vector3(0, 0.05f, 0));
	else
		childCircle->transform.Translate(Vector3(0, -0.05f, 0));

	parentCircle->cs.setPosition(parentCircle->transform.xWorld, parentCircle->transform.yWorld);
	childCircle->cs.setPosition(childCircle->transform.xWorld, childCircle->transform.yWorld);

	//parentCircle->cs.setScale(parentCircle->transform.xWorldScale, parentCircle->transform.yWorldScale);
	//childCircle->cs.setScale(childCircle->transform.xWorldScale, childCircle->transform.yWorldScale);

	//parentCircle->rigidbody.SetAABB();
	childCircle->rigidbody.SetAABB();

	std::cout << "B child:  " << childCircle->rigidbody.bounds[0] << ", " 
		<< childCircle->rigidbody.bounds[1] << std::endl;

	physics->UpdatePhysics(dt);
}

void GameScreen::Draw(sf::RenderWindow &win) {
	win.draw(parentCircle->cs);
	win.draw(childCircle->cs);
}

void GameScreen::LoadAssets() {
	LoadedAssets = true;
}

void GameScreen::LoadObjects() {
	physics = new PhysicsEngine();

	scene = new GameObject();
	parentCircle = new GameObject();
	childCircle = new GameObject();

	physics->AddRigidBody(&parentCircle->rigidbody);
	physics->AddRigidBody(&childCircle->rigidbody);

	scene->AddChild(parentCircle);
	parentCircle->AddChild(childCircle);

	parentCircle->cs.setRadius(100.0f);
	parentCircle->cs.setFillColor(sf::Color::Green);
	parentCircleRight = true;

	childCircle->cs.setRadius(20.0f);
	childCircle->cs.setFillColor(sf::Color::Blue);
	childCircleUp = true;
	LoadedObjects = true;

	if (parentCircle->rigidbody.gameObject == parentCircle)
		std::cout << "true\n";
	
}