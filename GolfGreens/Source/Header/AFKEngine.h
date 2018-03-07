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

	void UpdateSplashScreen();
	void DrawSplashScreen();

	void UpdateGameScreen();
	void DrawGameScreen();
	

	enum GameState {
		Uninitialized,
		ShowingSplash,
		Paused,
		ShowingMenu,
		Playing,
		Exiting
	};

	void SwitchStateTo(GameState newState);
	GameState gameState;
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
	//objects

	sf::CircleShape parentCircleShape;
	sf::CircleShape childCircleShape;
	sf::Texture SplashScreenTexture;
	sf::Sprite SplashScreenSprite;


};

