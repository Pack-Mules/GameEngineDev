
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
	GetInput(win);
	float dt = 0.01f;// &clock.getElapsedTime().asMilliseconds;
	if (FirstCircle)
		FirstCircle->Update(dt);
	if (SecondCircle)
		SecondCircle->Update(dt);
	if (ThirdCircle)
		ThirdCircle->Update(dt);

	ImmovableCircle->Update(dt);
	//moving circle
	//std::cout << FirstCircle->name << ": " << FirstCircle->rigidbody.aabb.bLeft << ", " << FirstCircle->rigidbody.aabb.tRight << std::endl;
	//std::cout << SecondCircle->name << ": " << FirstCircle->rigidbody.aabb.bLeft << ", " << SecondCircle->rigidbody.aabb.tRight << std::endl;

	physics->UpdatePhysics(dt);
	CheckHole();

}

void GameScreen::Draw(sf::RenderWindow &win) {
	win.draw(ImmovableCircle->cs);
	if (FirstCircle)
		win.draw(FirstCircle->cs);
	if (SecondCircle)
		win.draw(SecondCircle->cs);
	if (ThirdCircle)
		win.draw(ThirdCircle->cs);
	if (isShooting)
	{
		win.draw(shotLine, 2, sf::Lines);
	}
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
	ImmovableCircle = new GameObject();

	scene->name = "Scene";
	FirstCircle->name = "First";
	SecondCircle->name = "Second";
	ThirdCircle->name = "Third";
	ImmovableCircle->name = "Block";

	physics->AddRigidBody(&FirstCircle->rigidbody);
	physics->AddRigidBody(&SecondCircle->rigidbody);
	physics->AddRigidBody(&ThirdCircle->rigidbody);
	//physics->AddRigidBody(&ImmovableCircle->rigidbody);

	scene->AddChild(FirstCircle);
	scene->AddChild(SecondCircle);
	scene->AddChild(ThirdCircle);
	scene->AddChild(ImmovableCircle);

	FirstCircle->cs.setRadius(20.0f);
	FirstCircle->cs.setFillColor(sf::Color::White);
	FirstCircle->transform.SetPosition(Vector2(30, 30));
	FirstCircle->rigidbody.currentVelocity = Vector2(0, 0);
	FirstCircle->rigidbody.shape = Rigidbody::Shape::Circle;

	SecondCircle->cs.setRadius(20.0f);
	SecondCircle->cs.setFillColor(sf::Color::Blue);
	SecondCircle->transform.SetPosition(Vector2(500, 60));
	SecondCircle->rigidbody.currentVelocity = Vector2(0, 0);
	SecondCircle->rigidbody.shape = Rigidbody::Shape::Circle;


	ThirdCircle->cs.setRadius(20.0f);
	ThirdCircle->cs.setFillColor(sf::Color::Green);
	ThirdCircle->transform.SetPosition(Vector2(500, 300));
	ThirdCircle->rigidbody.currentVelocity = Vector2(0, 0);
	ThirdCircle->rigidbody.shape = Rigidbody::Shape::Circle;

	ImmovableCircle->cs.setRadius(40.0f);
	ImmovableCircle->cs.setFillColor(sf::Color::Black);
	ImmovableCircle->transform.SetPosition(Vector2(rand() % 944, rand() % 688));
	ImmovableCircle->rigidbody.currentVelocity = Vector2(0, 0);
	ImmovableCircle->rigidbody.shape = Rigidbody::Shape::Circle;
	//ImmovableCircle->rigidbody.moveable = false;

	FirstCircle->rigidbody.frictionVal = 0.9996f;
	SecondCircle->rigidbody.frictionVal = 0.9996f;
	ThirdCircle->rigidbody.frictionVal = 0.9996f;
	ImmovableCircle->rigidbody.frictionVal = 0;

	FirstCircle->Update(0.01f);
	SecondCircle->Update(0.01f);
	ThirdCircle->Update(0.01f);
	ImmovableCircle->Update(0.01f);
	LoadedObjects = true;

	//if (parentCircle->rigidbody.gameObject == parentCircle)
	//	std::cout << "true\n";



}

void GameScreen::GetInput(sf::RenderWindow &win)
{

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
	{
		if (!isReset)
		{
			LoadObjects();
			isReset = true;
			std::cout << "Balls reset." << std::endl;
		}
	}


	if (FirstCircle)
	{
		sf::Vector2i mousePosI;
		sf::Vector2f mousePosF;

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			isReset = false;
			if (isShooting)
			{
				mousePosI = sf::Mouse::getPosition(win);
				mousePosF = sf::Vector2f(mousePosI);
				shotLine[1] = mousePosF;
			}
			else
			{
				isShooting = true;
				mousePosI = sf::Mouse::getPosition(win);
				mousePosF = sf::Vector2f(mousePosI);
				shotLine[0] = mousePosF;
				//std::cout << mousePosF.x << ", " << mousePosF.y << std::endl;
			}
		}
		else if (isShooting)
		{
			shotVel = sf::Vector2i(shotLine[0].position - shotLine[1].position) / 3;
			std::cout << "Shot Velocity = " << shotVel.x << ", " << shotVel.y << std::endl;
			FirstCircle->rigidbody.currentVelocity = Vector2(shotVel.x, shotVel.y);
			isShooting = false;
		}

		if (SecondCircle)
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
			{
				if (SecondCircle->parent == scene)
				{
					scene->RemoveChild(SecondCircle);
					FirstCircle->AddChild(SecondCircle);
				}
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::E))
			{
				if (SecondCircle->parent == FirstCircle)
				{
					FirstCircle->RemoveChild(SecondCircle);
					scene->AddChild(SecondCircle);
				}
			}
		}


	}

}

void GameScreen::CheckHole()
{
	Vector2 holeCenter = Vector2((ImmovableCircle->transform.xWorld + ImmovableCircle->cs.getGlobalBounds().width / 2), (ImmovableCircle->transform.yWorld + ImmovableCircle->cs.getGlobalBounds().height / 2));
	float holeRadius = (ImmovableCircle->rigidbody.aabb.tRight.x - ImmovableCircle->rigidbody.aabb.bLeft.x) / 2;
	float ballRadius = 20.0f;
	float threshold = holeRadius - ballRadius;

	if (FirstCircle)
	{
		Vector2 distance = Vector2((ImmovableCircle->transform.xWorld + ImmovableCircle->cs.getGlobalBounds().width / 2) - (FirstCircle->transform.xWorld + FirstCircle->cs.getGlobalBounds().width / 2),
			(ImmovableCircle->transform.yWorld + ImmovableCircle->cs.getGlobalBounds().height / 2) - (FirstCircle->transform.yWorld + FirstCircle->cs.getGlobalBounds().height / 2));

		if ((distance.x*distance.x) + (distance.y*distance.y) <= (threshold*threshold))
		{
			std::cout << "1st Ball in hole" << std::endl;
			physics->RemoveRigidBody(&FirstCircle->rigidbody);
			FirstCircle = nullptr;
			new GameScreen();
		}
	}
	if (SecondCircle)
	{
		Vector2 distance = Vector2((ImmovableCircle->transform.xWorld + ImmovableCircle->cs.getGlobalBounds().width / 2) - (SecondCircle->transform.xWorld + SecondCircle->cs.getGlobalBounds().width / 2),
			(ImmovableCircle->transform.yWorld + ImmovableCircle->cs.getGlobalBounds().height / 2) - (SecondCircle->transform.yWorld + SecondCircle->cs.getGlobalBounds().height / 2));

		if ((distance.x*distance.x) + (distance.y*distance.y) <= (threshold*threshold))
		{
			std::cout << "2nd Ball in hole" << std::endl;
			physics->RemoveRigidBody(&SecondCircle->rigidbody);
			SecondCircle = nullptr;
		}
	}
	if (ThirdCircle)
	{
		Vector2 distance = Vector2((ImmovableCircle->transform.xWorld + ImmovableCircle->cs.getGlobalBounds().width / 2) - (ThirdCircle->transform.xWorld + ThirdCircle->cs.getGlobalBounds().width / 2),
			(ImmovableCircle->transform.yWorld + ImmovableCircle->cs.getGlobalBounds().height / 2) - (ThirdCircle->transform.yWorld + ThirdCircle->cs.getGlobalBounds().height / 2));

		if ((distance.x*distance.x) + (distance.y*distance.y) <= (threshold*threshold))
		{
			std::cout << "3rd Ball in hole" << std::endl;
			physics->RemoveRigidBody(&ThirdCircle->rigidbody);
			ThirdCircle = nullptr;
		}
	}



}
