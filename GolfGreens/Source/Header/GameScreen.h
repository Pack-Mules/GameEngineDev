#ifndef GAMESCREEN_H
#define GAMESCREEN_H

#include "Screen.h"
#include "GameObject.h"
#include "SFML/Graphics.hpp"
#include <array>


class GameScreen : public Screen {
public:
	GameScreen();

	void Update(sf::RenderWindow &win) override;
	void Draw(sf::RenderWindow &win) override;

	void LoadAssets() override;
	void LoadObjects() override;

	void GetInput(sf::RenderWindow &win) override;

	void CheckHole();

	void GenerateMap();
	void GameScreen::CreateWall(GameObject *wall, float sx, float sy, int x, int y, sf::Color color = sf::Color::Black);



public:
	GameObject * scene;
	GameObject *FirstCircle;
	GameObject *SecondCircle;
	GameObject *ImmovableCircle;

	GameObject *Block1;
	GameObject *Block2;
	GameObject *Block3;
	GameObject *Block4;
	GameObject *Block5;

	GameObject *HWall1;
	GameObject *HWall2;
	GameObject *HWall3;
	GameObject *HWall4;
	GameObject *HWall5;
	GameObject *HWall6;
	GameObject *HWall7;
	GameObject *HWall8;
	GameObject *HWall9;
	GameObject *HWall10;
	GameObject *HWall11;
	GameObject *HWall12;

	GameObject *VWall1;
	GameObject *VWall2;
	GameObject *VWall3;
	GameObject *VWall4;
	GameObject *VWall5;
	GameObject *VWall6;
	GameObject *VWall7;
	GameObject *VWall8;
	GameObject *VWall9;



	std::array<GameObject*, 100> walls;

	sf::Text turnDisplay;
	sf::Font font;
	sf::Vertex shotLine[2];
	bool isShooting;
	bool isReset;
	sf::Vector2i shotVel;
	int numWalls;
	int shotTurn;
	int player1count, player2count;


	//objects
	//sf::CircleShape parentCircleShape;
	//sf::CircleShape childCircleShape;
private:

	
};
#endif