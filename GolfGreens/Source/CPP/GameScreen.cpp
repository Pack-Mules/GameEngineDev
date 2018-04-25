
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
	for (int i = 0; i < walls.size(); i++)
	{
		if (walls[i])
			walls[i]->Update(dt);
	}
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
	for (int i = 0; i < walls.size(); i++)
	{
		if (walls[i])
			win.draw(walls[i]->rs);
	}

	if (isShooting)
	{
		win.draw(shotLine, 2, sf::Lines);
	}
	win.draw(turnDisplay);
}

void GameScreen::LoadAssets() {
	LoadedAssets = true;
}

void GameScreen::LoadObjects() {
	physics = new PhysicsEngine();

	scene = new GameObject();
	FirstCircle = new GameObject();
	SecondCircle = new GameObject();
	ImmovableCircle = new GameObject();

	scene->name = "Scene";
	FirstCircle->name = "First";
	SecondCircle->name = "Second";
	ImmovableCircle->name = "Hole";

	physics->AddRigidBody(&FirstCircle->rigidbody);
	physics->AddRigidBody(&SecondCircle->rigidbody);
	//physics->AddRigidBody(&ImmovableCircle->rigidbody);

	scene->AddChild(FirstCircle);
	scene->AddChild(SecondCircle);
	scene->AddChild(ImmovableCircle);

	FirstCircle->cs.setRadius(10.0f);
	FirstCircle->cs.setFillColor(sf::Color::White);
	FirstCircle->transform.SetPosition(Vector2(125, 75));
	FirstCircle->rigidbody.currentVelocity = Vector2(0, 0);
	FirstCircle->rigidbody.shape = Rigidbody::Shape::Circle;

	SecondCircle->cs.setRadius(10.0f);
	SecondCircle->cs.setFillColor(sf::Color::Blue);
	SecondCircle->transform.SetPosition(Vector2(165, 75));
	SecondCircle->rigidbody.currentVelocity = Vector2(0, 0);
	SecondCircle->rigidbody.shape = Rigidbody::Shape::Circle;

	ImmovableCircle->cs.setRadius(20.0f);
	ImmovableCircle->cs.setFillColor(sf::Color::Black);
	ImmovableCircle->transform.SetPosition(Vector2(500, 400));
	ImmovableCircle->rigidbody.currentVelocity = Vector2(0, 0);
	ImmovableCircle->rigidbody.shape = Rigidbody::Shape::Circle;
	//ImmovableCircle->rigidbody.moveable = false;

	GenerateMap();

	FirstCircle->rigidbody.frictionVal = 0.999f;
	SecondCircle->rigidbody.frictionVal = 0.999f;
	ImmovableCircle->rigidbody.frictionVal = 0;

	FirstCircle->Update(0.01f);
	SecondCircle->Update(0.01f);
	ImmovableCircle->Update(0.01f);

	
	turnDisplay.setString("Turn: Player One - Stroke: 1");
	turnDisplay.setFillColor(sf::Color::White);
	turnDisplay.setPosition(10, 10);
	turnDisplay.setCharacterSize(20); 
	std::string path = "../../Assets/Fonts/";
	font.loadFromFile(path + "arial.ttf");
	turnDisplay.setFont(font);

	LoadedObjects = true;

	//if (parentCircle->rigidbody.gameObject == parentCircle)
	//	std::cout << "true\n";



}

void GameScreen::GenerateMap()
{
	// ***Blocks***
	Block1 = new GameObject();
	Block1->name = "B1";
	CreateWall(Block1, 50.0f, 50.0f, 275, 575, sf::Color(20, 20, 20, 255));

	Block2 = new GameObject();
	Block2->name = "B2";
	CreateWall(Block2, 50.0f, 50.0f, 275, 437, sf::Color(20, 20, 20, 255));

	Block3 = new GameObject();
	Block3->name = "B3";
	CreateWall(Block3, 50.0f, 50.0f, 275, 300, sf::Color(20, 20, 20, 255));

	Block4 = new GameObject();
	Block4->name = "B4";
	CreateWall(Block4, 20.0f, 20.0f, 835, 400, sf::Color(20, 20, 20, 255));

	Block5 = new GameObject();
	Block5->name = "B4";
	CreateWall(Block5, 20.0f, 20.0f, 835, 500, sf::Color(20, 20, 20, 255));
	

	// ***Horizontal Walls***
	HWall1 = new GameObject();
	HWall1->name = "VW1";
	CreateWall(HWall1, 100.0f, 10.0f, 100, 50);

	HWall2 = new GameObject();
	HWall2->name = "VW2";
	CreateWall(HWall2, 300.0f, 10.0f, 100, 700);

	HWall3 = new GameObject();
	HWall3->name = "HW3";
	CreateWall(HWall3, 100.0f, 10.0f, 250, 237);

	HWall4 = new GameObject();
	HWall4->name = "HW4";
	CreateWall(HWall4, 700.0f, 10.0f, 200, 175);
	
	HWall5 = new GameObject();
	HWall5->name = "HW5";
	CreateWall(HWall5, 100.0f, 10.0f, 450, 237);

	HWall6 = new GameObject();
	HWall6->name = "HW6";
	CreateWall(HWall6, 400.0f, 10.0f, 390, 300);

	HWall7 = new GameObject();
	HWall7->name = "HW7";
	CreateWall(HWall7, 100.0f, 10.0f, 650, 237);

	HWall8 = new GameObject();
	HWall8->name = "HW8";
	CreateWall(HWall8, 500.0f, 10.0f, 390, 665);

	HWall9 = new GameObject();
	HWall9->name = "HW9";
	CreateWall(HWall9, 100.0f, 10.0f, 390, 565);

	HWall10 = new GameObject();
	HWall10->name = "HW10";
	CreateWall(HWall10, 260.0f, 10.0f, 540, 565);
	
	HWall11 = new GameObject();
	HWall11->name = "HW11";
	CreateWall(HWall11, 200.0f, 10.0f, 495, 445);

	HWall12 = new GameObject();
	HWall12->name = "HW11";
	CreateWall(HWall12, 200.0f, 10.0f, 495, 385);


	// ***Vertical Walls***
	VWall1 = new GameObject();
	VWall1->name = "HW1";
	CreateWall(VWall1, 10.0f, 650.0f, 100, 50);

	VWall2 = new GameObject();
	VWall2->name = "HW2";
	CreateWall(VWall2, 10.0f, 550.0f, 200, 50);

	VWall3 = new GameObject();
	VWall3->name = "VW3";
	CreateWall(VWall3, 10.0f, 400.0f, 390, 300);

	VWall4 = new GameObject();
	VWall4->name = "VW4";
	CreateWall(VWall4, 10.0f, 62.0f, 540, 175);

	VWall5 = new GameObject();
	VWall5->name = "VW5";
	CreateWall(VWall5, 10.0f, 62.0f, 740, 238);

	VWall6 = new GameObject();
	VWall6->name = "VW6";
	CreateWall(VWall6, 10.0f, 500.0f, 890, 175);

	VWall7 = new GameObject();
	VWall7->name = "VW7";
	CreateWall(VWall7, 10.0f, 275.0f, 790, 300);

	VWall8 = new GameObject();
	VWall8->name = "VW8";
	CreateWall(VWall8, 10.0f, 70.0f, 485, 385);

	VWall9 = new GameObject();
	VWall9->name = "VW9";
	CreateWall(VWall9, 10.0f, 125.0f, 590, 445);


}
void GameScreen::CreateWall(GameObject *wall, float sx, float sy, int x, int y, sf::Color color)
{
	color = sf::Color(205, 133, 63, 255);

	physics->AddRigidBody(&wall->rigidbody);
	scene->AddChild(wall);
	wall->rs.setSize(sf::Vector2f(sx, sy));
	wall->rs.setFillColor(color);
	wall->transform.SetPosition(Vector2(x, y));
	wall->rigidbody.currentVelocity = Vector2(0, 0);
	wall->rigidbody.shape = Rigidbody::Shape::Rectangle;
	wall->rigidbody.moveable = false;
	wall->rigidbody.frictionVal = 0;
	wall->Update(0.01f);
	walls[numWalls] = wall;
	numWalls++;
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


	if (FirstCircle && shotTurn != 2)
	{
		sf::Vector2i mousePosI;
		sf::Vector2f mousePosF;

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			/* //For testingn collision (click and hold to move object there)
			sf::Vector2i test1 = sf::Mouse::getPosition(win);
			FirstCircle->transform.SetPosition(Vector2((float)test1.x, (float)test1.y));
			*/

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
			shotVel = sf::Vector2i(shotLine[0].position - shotLine[1].position) / 5;
			std::cout << "Shot Velocity = " << shotVel.x << ", " << shotVel.y << std::endl;
			player1count++;
			
			FirstCircle->rigidbody.currentVelocity = Vector2(shotVel.x, shotVel.y);
			playSound("GolfBallHit.flac");
			if (SecondCircle)
			{
				shotTurn = 2;
				std::string str = "Turn: Player Two - Stroke: " + std::to_string(player2count + 1);
				std::cout << str << std::endl;
				turnDisplay.setString(str);
				turnDisplay.setFillColor(sf::Color::Blue);
			}
			else
			{
				shotTurn = 1;
				std::string str = "Turn: Player One - Stroke: " + std::to_string(player1count + 1);
				turnDisplay.setString(str);
				turnDisplay.setFillColor(sf::Color::White);
			}
			isShooting = false;
		}
		
	}
	else if (SecondCircle && shotTurn == 2)
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
			player2count++;
			SecondCircle->rigidbody.currentVelocity = Vector2(shotVel.x, shotVel.y);
			playSound("GolfBallHit.flac");
			
			if (FirstCircle)
			{
				shotTurn = 1; 
				std::string str = "Turn: Player One - Stroke: " + std::to_string(player1count + 1);
				turnDisplay.setString(str);
				turnDisplay.setFillColor(sf::Color::White);
			}
			else
			{
				shotTurn = 2;
				std::string str = "Turn: Player Two - Stroke: " + std::to_string(player2count + 1);
				turnDisplay.setString(str);
				turnDisplay.setFillColor(sf::Color::Blue);
			}
			isShooting = false;
		}
	}

	else if (!FirstCircle && !SecondCircle)
	{
		std::string str;
		if (player1count < player2count)
		{
			str = "Player One wins!\nPlayer One score: " + std::to_string(player1count) + '\n';
			str += "Player Two score: " + std::to_string(player2count + 1) + '\n';
			str += "Press 'ESC' to restart.";
		}
		else if (player1count == player2count)
		{
			str = "Tie game!\nPlayer One score: " + std::to_string(player1count) + '\n';
			str += "Player Two score: " + std::to_string(player2count) + '\n';
			str += "Press 'ESC' to restart.";
		}
		else
		{
			str = "Player Two wins!\nPlayer Two score: " + std::to_string(player2count) + '\n';
			str += "Player One score: " + std::to_string(player1count) + '\n';
			str += "Press 'ESC' to restart.";
		}

		turnDisplay.setString(str);
	}
	//  ***Child inheritence tests***
	/*if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
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
	}*/
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
			shotTurn = 2;
			std::string str = "Turn: Player Two - Stroke: " + std::to_string(player2count + 1);
			turnDisplay.setString(str);
			turnDisplay.setFillColor(sf::Color::Blue);
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
			shotTurn = 1;
			std::string str = "Turn: Player One - Stroke: " + std::to_string(player1count + 1);
			turnDisplay.setString(str);
			turnDisplay.setFillColor(sf::Color::White);
		}
	}



}
