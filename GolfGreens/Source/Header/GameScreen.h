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

	void GetInput(sf::RenderWindow &win) override;

	

public:
	GameObject *scene;
	GameObject *FirstCircle;
	GameObject *SecondCircle;
	GameObject *ThirdCircle;

	sf::Vertex shotLine[2];
	bool isShooting;
	sf::Vector2i shotVel;


	//objects
	//sf::CircleShape parentCircleShape;
	//sf::CircleShape childCircleShape;
private:
};
#endif