#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "SFML/Graphics.hpp"
#include "SFML/OpenGL.hpp"
#include "Matrices.h"
#include "Transform.h"
#include "Rigidbody.h"
#include "Component.h"
#include <list>


class GameObject: public sf::Drawable {
public:
	GameObject();

	~GameObject();

	//void SetParent(GameObject& p) { parent = p; }
	void AddChild(GameObject* s);
	void RemoveChild(GameObject* s);


	virtual void Update(float msec);


	void AddComponent(Component* newS) { Components.push_back(newS); }

	Transform transform;
	std::list<Component*> Components;

	sf::Sprite sprite;
	void draw(sf::RenderTarget& target, sf::RenderStates state) const
	{
		target.draw(sprite);
	}

protected:

	GameObject* parent;
	std::vector<GameObject*> children;
	//Rigidbody rigidBody;
};

#endif