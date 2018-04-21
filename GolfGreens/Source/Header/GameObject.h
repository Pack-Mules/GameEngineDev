#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "SFML/Graphics.hpp"
#include "SFML/OpenGL.hpp"
#include "Matrices.h"
#include "Transform.h"
#include "Rigidbody.h"
#include "Component.h"
#include <string>
#include <list>


class GameObject : public sf::Drawable {
public:
	GameObject();

	~GameObject();

	//void SetParent(GameObject& p) { parent = p; }
	void AddChild(GameObject* s);
	void RemoveChild(GameObject* s);


	virtual void Update(float msec);

	GameObject* parent;



	void AddComponent(Component* newS) { Components.push_back(newS); }

	Transform transform;
	Rigidbody rigidbody;

	sf::CircleShape cs;
	sf::RectangleShape rs;

	std::list<Component*> Components;

	sf::Sprite sprite;
	void draw(sf::RenderTarget& target, sf::RenderStates state) const
	{
		target.draw(sprite);
	}


	std::string name;
	int id;

protected:


	std::vector<GameObject*> children;
	//Rigidbody rigidBody;
};

#endif