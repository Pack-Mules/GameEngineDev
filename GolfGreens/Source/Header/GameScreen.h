#ifndef GAMESCREEN_H
#define GAMESCREEN_H

#include "AFKEngine.h"
#include "Screen.h"
#include "GameObject.h"
#include <iostream>
#include <Windows.h>
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"


class GameScreen : public Screen {
public:
	GameScreen();

	void Update(sf::RenderWindow &win) override;
	void Draw(sf::RenderWindow &win) override;

	void LoadAssets() override;
	void LoadObjects() override;

	

public:
	GameObject *scene;
	GameObject *parentCircle;
	GameObject *childCircle;

	bool parentCircleRight;
	bool childCircleUp;

	//objects
	sf::CircleShape parentCircleShape;
	sf::CircleShape childCircleShape;
private:
};
#endif