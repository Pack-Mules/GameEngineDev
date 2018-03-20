#include "SplashScreen.h"

SplashScreen::SplashScreen() {
	LoadAssets();
	LoadObjects();
}


void SplashScreen::Update(sf::RenderWindow &win) {
	SplashScreenSprite.setPosition(
		win.getSize().x / 2,
		win.getSize().y / 2);
}
void SplashScreen::Draw(sf::RenderWindow &win) {
	win.draw(SplashScreenSprite);
}

void SplashScreen::LoadAssets() {
	std::string path = "../../Assets/Images/";

	if (!SplashScreenTexture.loadFromFile(path + "PackMulesIcon.jpg")) {
	}
	SplashScreenSprite.setTexture(SplashScreenTexture);
	SplashScreenSprite.setOrigin(
		SplashScreenSprite.getLocalBounds().width / 2,
		SplashScreenSprite.getLocalBounds().height / 2);
}
void SplashScreen::LoadObjects() {

}