
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
	ThirdCircle->Update(dt);
	//moving circle
	//std::cout << FirstCircle->name << ": " << FirstCircle->rigidbody.aabb.bLeft << ", " << FirstCircle->rigidbody.aabb.tRight << std::endl;
	//std::cout << SecondCircle->name << ": " << FirstCircle->rigidbody.aabb.bLeft << ", " << SecondCircle->rigidbody.aabb.tRight << std::endl;

	physics->UpdatePhysics(dt);
}

void GameScreen::Draw(sf::RenderWindow &win) {
	win.draw(FirstCircle->cs);
	win.draw(SecondCircle->cs);
	win.draw(ThirdCircle->cs);
}

void GameScreen::LoadAssets() {
	LoadedAssets = true;
}

void GameScreen::LoadObjects() {
	physics = new PhysicsEngine();

	scene = new GameObject();
	FirstCircle = new GameObject();
	SecondCircle = new GameObject();
	ThirdCircle = new GameObject();

	scene->name = "Scene";
	FirstCircle->name = "First";
	SecondCircle->name = "Second";
	ThirdCircle->name = "Third";

	physics->AddRigidBody(&FirstCircle->rigidbody);
	physics->AddRigidBody(&SecondCircle->rigidbody);
	physics->AddRigidBody(&ThirdCircle->rigidbody);

	scene->AddChild(FirstCircle);
	scene->AddChild(SecondCircle);
	scene->AddChild(ThirdCircle);

	FirstCircle->cs.setRadius(20.0f);
	FirstCircle->cs.setFillColor(sf::Color::White);
	FirstCircle->transform.SetPosition(Vector2(30, 30));
	FirstCircle->rigidbody.currentVelocity = Vector2(40, 0);
	FirstCircle->rigidbody.shape = Rigidbody::Shape::Circle;

	SecondCircle->cs.setRadius(20.0f);
	SecondCircle->cs.setFillColor(sf::Color::Blue);
	SecondCircle->transform.SetPosition(Vector2(500, 60));
	SecondCircle->rigidbody.currentVelocity = Vector2(0, 0);
	SecondCircle->rigidbody.shape = Rigidbody::Shape::Circle;


	ThirdCircle->cs.setRadius(20.0f);
	ThirdCircle->cs.setFillColor(sf::Color::Green);
	ThirdCircle->transform.SetPosition(Vector2(500, 100));
	ThirdCircle->rigidbody.currentVelocity = Vector2(0, 0);
	ThirdCircle->rigidbody.shape = Rigidbody::Shape::Circle;



	LoadedObjects = true;

	//if (parentCircle->rigidbody.gameObject == parentCircle)
	//	std::cout << "true\n";
	
}