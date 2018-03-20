#include "GameScreen.h"
#include "Screen.h"
#include "GameObject.h"
#include <iostream>
#include <Windows.h>
#include "SFML\Audio.hpp"


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
	else if (parentCircle->transform.x + parentCircleShape.getLocalBounds().width >= win.getSize().x
		&& parentCircleRight == true)
		parentCircleRight = false;

	if (childCircle->transform.y <= 0)
		childCircleUp = true;
	else if (childCircle->transform.y >= 200)
		childCircleUp = false;

	if (parentCircleRight)
		parentCircle->transform.Translate(Vector3(1, 0, 0));
	else
		parentCircle->transform.Translate(Vector3(-1, 0, 0));

	if (childCircleUp)
		childCircle->transform.Translate(Vector3(0, 0.5f, 0));
	else
		childCircle->transform.Translate(Vector3(0, -0.5f, 0));

	parentCircleShape.setPosition(parentCircle->transform.xWorld, parentCircle->transform.yWorld);
	childCircleShape.setPosition(childCircle->transform.xWorld, childCircle->transform.yWorld);

}

void GameScreen::Draw(sf::RenderWindow &win) {
	win.draw(parentCircleShape);
	win.draw(childCircleShape);
}

void GameScreen::LoadAssets() {
	LoadedAssets = true;
}

void GameScreen::LoadObjects() {
	scene = new GameObject();
	parentCircle = new GameObject();
	childCircle = new GameObject();

	scene->AddChild(parentCircle);
	parentCircle->AddChild(childCircle);

	parentCircleShape.setRadius(100.0f);
	parentCircleShape.setFillColor(sf::Color::Green);
	parentCircleRight = true;

	childCircleShape.setRadius(20.0f);
	childCircleShape.setFillColor(sf::Color::Blue);
	childCircleUp = true;
	LoadedObjects = true;
}