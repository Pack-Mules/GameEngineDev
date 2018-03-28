
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
	FirstCircle->Update(dt);
	SecondCircle->Update(dt);
	//moving circle
	std::cout << FirstCircle->name << ": " << FirstCircle->rigidbody.aabb.bLeft << ", " << FirstCircle->rigidbody.aabb.tRight << std::endl;

	std::cout << SecondCircle->name << ": " << FirstCircle->rigidbody.aabb.bLeft << ", " << SecondCircle->rigidbody.aabb.tRight << std::endl;

	physics->UpdatePhysics(dt);
}

void GameScreen::Draw(sf::RenderWindow &win) {
	win.draw(FirstCircle->cs);
	win.draw(SecondCircle->cs);
}

void GameScreen::LoadAssets() {
	LoadedAssets = true;
}

void GameScreen::LoadObjects() {
	physics = new PhysicsEngine();

	scene = new GameObject();
	FirstCircle = new GameObject();
	SecondCircle = new GameObject();

	scene->name = "Scene";
	FirstCircle->name = "First";
	SecondCircle->name = "Second";

	physics->AddRigidBody(&FirstCircle->rigidbody);
	physics->AddRigidBody(&SecondCircle->rigidbody);

	scene->AddChild(FirstCircle);
	scene->AddChild(SecondCircle);

	FirstCircle->cs.setRadius(50.0f);
	FirstCircle->cs.setFillColor(sf::Color::Green);
	FirstCircle->rigidbody.currentVelocity = Vector2(20, 0);
	FirstCircle->rigidbody.shape = Rigidbody::Shape::Circle;

	SecondCircle->cs.setRadius(50.0f);
	SecondCircle->cs.setFillColor(sf::Color::Blue);
	SecondCircle->transform.SetPosition(Vector2(500, 0));
	SecondCircle->rigidbody.shape = Rigidbody::Shape::Circle;
	//SecondCircle->rigidbody.currentVelocity = Vector2(-20, 0);


	LoadedObjects = true;

	//if (parentCircle->rigidbody.gameObject == parentCircle)
	//	std::cout << "true\n";
	
}