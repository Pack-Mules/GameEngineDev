#include "SFML/Graphics.hpp"
#include "SFML/OpenGL.hpp"
#include "Matrices.h"
#include "Transform.h"
#include "Component.h"
#include <list>

class GameObject {
public:
	GameObject();

	~GameObject();

	//void SetParent(GameObject& p) { parent = p; }
	void AddChild(GameObject* s);
	void RemoveChild(GameObject* s);


	virtual void Update(float msec);

	public int id;
	Transform transform;

protected:
	GameObject* parent;
	std::vector<GameObject*> children;
	std::list<Component> Components;
};