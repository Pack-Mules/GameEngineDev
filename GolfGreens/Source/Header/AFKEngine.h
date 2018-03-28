

#ifndef AFKENGINE_H
#define AFKENGINE_H

#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"


class AFKEngine
{
public:
	AFKEngine();
	void Start();
	bool Initialize(int argc, char *argv[]);


	const static int ScreenWidth = 1024;
	const static int ScreenHeight = 768;

private:
	void LoadAssets();
	void LoadObjects();


	bool IsExiting();
	void Update();

	float GetHardDriveSpace();
	float GetMemory();
	void GetInputDevices();
	void GetOutputDevices();
	float GetCPUSpeed();
	
	void playSound(std::string fileName);
	void playMusic(std::string fileName);

	

	enum GameState {
		Uninitialized,
		ShowingSplash,
		Paused,
		ShowingMenu,
		Playing,
		Exiting
	};

	void SwitchStateTo(GameState newState);
	GameState gameState = Uninitialized;
	sf::RenderWindow mainWindow;
	
	
	sf::SoundBuffer mainAudioBuffer;
	sf::Music bgm;

	float stateTimer = 0.0f;
	float SplashScreenTimer = 3.0f;
	sf::Clock clock;
	float minDriveSpace;
	float minMemory;
	float minCPUSpeed;


private:

};

#endif