#include "AFKEngine.h"
#include "GameObject.h"
#include <iostream>
#include <Windows.h>
#include "SFML\System\Clock.hpp"
#include "SFML\Audio.hpp"

sf::CircleShape circleShape(100.0f);

GameObject *scene;
GameObject *parentCircle;
GameObject *childCircle;

Matrix4* mat;
bool parentCircleRight;
bool childCircleUp;

AFKEngine::AFKEngine() {
	//no minimum requirements atm
	minDriveSpace = 0;//9999999;
	minMemory = 0;
	minCPUSpeed = 0;
}

bool AFKEngine::Initialize(int argc, char *argv[]) {
	SwitchStateTo(ShowingSplash);

	std::cout << "Current specs" << std::endl;

	std::cout << "Hard Drive Space: " << GetHardDriveSpace() << " MB" << std::endl;
	if (GetHardDriveSpace() < minDriveSpace) {
		return false;
	}

	std::cout << "Memory Space: " << GetMemory() << " MB" << std::endl;
	if (GetMemory() < minMemory) {
		return false;
	}

	std::cout << "CPU Speed: " << GetCPUSpeed() << " MHz" << std::endl;
	if (GetCPUSpeed() < minCPUSpeed) {
		return false;
	}


	//Placeholder atm
	//std::cout << "Input Devices: " << std::endl << std::endl;
	//std::cout << "Output Devices: " << std::endl << std::endl;
	if (sf::Joystick::isConnected(0))
		std::cout << "Joystick detected" << std::endl;
	else
		std::cout << "No Joystick detected" << std::endl;

	std::cout << "\n\n\n\n";
	return true;


}



//Only run once
void AFKEngine::Start() {
	if (gameState == Uninitialized)
		return;

	SwitchStateTo(Playing);

	mat = new Matrix4();
	//Graphics system
	mainWindow.create(sf::VideoMode(1024, 768, 32), "A Game");
	clock.restart();

	LoadAssets();
	LoadObjects();

	//Audio started
	AFKEngine::playMusic("Madeon - Pop Culture.flac");


	while (!IsExiting()) {
		Update();
	}

	mainWindow.close();

}

//Loads all the shapes, sprites and audio assets
void AFKEngine::LoadObjects() {

	scene = new GameObject();
	parentCircle = new GameObject();
	childCircle = new GameObject();

	scene->AddChild(parentCircle);
	parentCircle->AddChild(childCircle);


	parentCircle->transform.Translate(Vector3(100, 0, 0));
	std::cout << "Translating parent 100 units on x. \n";


	childCircle->transform.Translate(Vector3(100, 50, 0));
	std::cout << "Translating child 100 units on x. \n \n";

	std::cout << "Parent transform: \n"
		<< parentCircle->transform.GetPosition()
		<< "\n Child transform: \n"
		<< childCircle->transform.GetPosition();



	parentCircleShape.setRadius(100.0f);
	parentCircleShape.setFillColor(sf::Color::Green);
	parentCircleRight = true;

	childCircleShape.setRadius(20.0f);
	childCircleShape.setFillColor(sf::Color::Blue);
	childCircleUp = true;

}

void AFKEngine::LoadAssets() {
	std::string path = "../../Assets/Images/";

	if (!SplashScreenTexture.loadFromFile(path + "PackMulesIcon.jpg")) {
	}
	SplashScreenSprite.setTexture(SplashScreenTexture);
	SplashScreenSprite.setOrigin(
		SplashScreenSprite.getLocalBounds().width / 2,
		SplashScreenSprite.getLocalBounds().height / 2);
	SplashScreenSprite.setPosition(
		mainWindow.getSize().x / 2,
		mainWindow.getSize().y / 2);
}


void AFKEngine::Update() {



	stateTimer = clock.getElapsedTime().asSeconds();

	if (mainWindow.isOpen())
	{
		sf::Event event;
		if (mainWindow.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				gameState = AFKEngine::Exiting;
		}

		mainWindow.clear();

		//STATE Functions
		switch (gameState) {
		case AFKEngine::ShowingSplash:
			UpdateSplashScreen();
			DrawSplashScreen();

			break;
		case AFKEngine::Playing:
			UpdateGameScreen();
			DrawGameScreen();

			break;
		default:
			break;
		}


		mainWindow.display();


	}
}

bool AFKEngine::IsExiting() {
	if (gameState == Exiting)
		return true;
	else
		return false;

}




void AFKEngine::SwitchStateTo(GameState newState) {
	gameState = newState;
	clock.restart();
	stateTimer = 0;
}


void AFKEngine::UpdateSplashScreen() {

}
void AFKEngine::DrawSplashScreen() {

	mainWindow.draw(SplashScreenSprite);
}


void AFKEngine::UpdateGameScreen() {
	float dt = 0.01f;// &clock.getElapsedTime().asMilliseconds;
	parentCircle->Update(dt);
	childCircle->Update(dt);
	//moving circle
	if (parentCircle->transform.x <= 0 && parentCircleRight == false)
		parentCircleRight = true;
	else if (parentCircle->transform.x + parentCircleShape.getLocalBounds().width >= mainWindow.getSize().x
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

void AFKEngine::DrawGameScreen() {
	mainWindow.draw(parentCircleShape);
	mainWindow.draw(childCircleShape);
}


void AFKEngine::playSound(std::string fileName) {
	if (!mainAudioBuffer.loadFromFile(fileName)) {
		std::cout << "Failure" << std::endl;
		return;
	}

	sf::Sound sound;
	sound.setBuffer(mainAudioBuffer);
	sound.play();
}

void AFKEngine::playMusic(std::string fileName) {
	bgm.stop();
	if (!bgm.openFromFile("../../Assets/Audio/BGM/" + fileName))
		return;
	bgm.setLoop(true);
	bgm.setVolume(60.0f);
	bgm.play();

}

//Checking Engine Values
float AFKEngine::GetHardDriveSpace() {
	LPCSTR pszDrive = NULL;
	BOOL test, fResult;
	_int64 IpFreeBytesAvailable, IpTotalNumberOfBytes, IpTotalNumberOfFreeBytes;
	test = GetDiskFreeSpaceEx(pszDrive,
		(PULARGE_INTEGER)&IpFreeBytesAvailable,
		(PULARGE_INTEGER)&IpTotalNumberOfBytes,
		(PULARGE_INTEGER)&IpTotalNumberOfFreeBytes);
	IpTotalNumberOfFreeBytes /= (1024 * 1024);
	return IpTotalNumberOfFreeBytes;
}

float AFKEngine::GetMemory() {
	MEMORYSTATUSEX status;
	status.dwLength = sizeof(status);
	GlobalMemoryStatusEx(&status);
	return status.ullTotalPhys / (1024 * 1024);
}

float AFKEngine::GetCPUSpeed() {
	char Buffer[_MAX_PATH];
	DWORD BufSize = _MAX_PATH;
	DWORD dwMHz = _MAX_PATH;
	HKEY hkey;

	long lError = RegOpenKeyEx(HKEY_LOCAL_MACHINE,
		"Hardware\\Description\\System\\CentralProcessor\\0",
		0,
		KEY_READ,
		&hkey);
	if (lError != ERROR_SUCCESS) {
		//key not found
		return -1.0f;
	}
	RegQueryValueEx(hkey, "~MHz", NULL, NULL, (LPBYTE)&dwMHz, &BufSize);
	return dwMHz;
}