#ifndef GAMESCREEN_H
#define GAMESCREEN_H

#include "Screen.h"
#include "GameObject.h"
#include "SFML/Graphics.hpp"


class GameScreen : public Screen {
public:
	GameScreen();

	void Update(sf::RenderWindow &win) override;
	void Draw(sf::RenderWindow &win) override;

	void LoadAssets() override;
	void LoadObjects() override;

	

public:
	GameObject *scene;
	GameObject *FirstCircle;
	GameObject *SecondCircle;
	GameObject *ThirdCircle;


	//objects
	//sf::CircleShape parentCircleShape;
	//sf::CircleShape childCircleShape;
private:
};
#endif