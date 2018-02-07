#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"

class AFKEngine
{
public:
	AFKEngine();
	void Start();
	bool Initialize(int argc, char *argv[]);
private:
	bool IsExiting();
	void GameLoop();

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

	GameState gameState;
	sf::RenderWindow mainWindow;
	
	
	//sf::SoundBuffer mainAudioBuffer;
	//sf::Music bgm;


	float minDriveSpace;
	float minMemory;
	float minCPUSpeed;

private:
	//objects

};

