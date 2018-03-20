#ifndef SCREEN_H
#define SCREEN_H

#include <SFML/Graphics.hpp>

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

	bool isReady() {
		if (LoadedObjects && LoadedAssets)
			return true;
		return false;
	}

public:
	bool LoadedObjects = false;
	bool LoadedAssets = false;
private:

};

#endif