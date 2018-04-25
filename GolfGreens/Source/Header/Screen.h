#ifndef SCREEN_H
#define SCREEN_H

#include <SFML/Graphics.hpp>
#include "SFML/Audio.hpp"
#include <iostream>
#include <Windows.h>

class Screen {

public:
	Screen() {
	}

	virtual void Update(sf::RenderWindow &win) {

	}

	virtual void Draw(sf::RenderWindow &win) {
	}

	virtual void LoadAssets() {
		LoadedAssets = true;
	}

	virtual void LoadObjects() {
		LoadedObjects = true;
	}

	virtual void GetInput(sf::RenderWindow &win) {

	}

	bool isReady() {
		if (LoadedObjects && LoadedAssets)
			return true;
		return false;
	}

	void playSound(std::string fileName) {
		if (!mainAudioBuffer.loadFromFile("../../Assets/Audio/SFX/" + fileName)) {
			std::cout << "Failure" << std::endl;
			return;
		}

		sfx.setBuffer(mainAudioBuffer);
		sfx.play();
	}
public:
	bool LoadedObjects = false;
	bool LoadedAssets = false;


	sf::SoundBuffer mainAudioBuffer;
	sf::Sound sfx;
private:

};

#endif