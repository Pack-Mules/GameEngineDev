#include "AFKEngine.h"
#include "GameObject.h"
#include "GameScreen.h"
#include "SplashScreen.h"
#include <iostream>
#include <Windows.h>
#include "SFML\System\Clock.hpp"
#include "SFML\Audio.hpp"

sf::CircleShape circleShape(100.0f);

SplashScreen* splashScreen;
GameScreen* gameScreen;

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
	splashScreen = new SplashScreen();
	gameScreen = new GameScreen();
}

void AFKEngine::LoadAssets() {

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
			splashScreen->Update(mainWindow);
			splashScreen->Draw(mainWindow);

			break;
		case AFKEngine::Playing:
			gameScreen->Update(mainWindow);
			gameScreen->Draw(mainWindow);

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