#ifndef SPLASHSCREEN_H
#define SPLASHSCREEN_H
#include "Screen.h"
#include "SFML/Graphics.hpp"

class SplashScreen : public Screen {

public:
	SplashScreen();

	void Update(sf::RenderWindow &win) override;
	void Draw(sf::RenderWindow &win) override;

	void LoadAssets() override;
	void LoadObjects() override;

public:

	sf::Texture SplashScreenTexture;
	sf::Sprite SplashScreenSprite;

};


#endif
