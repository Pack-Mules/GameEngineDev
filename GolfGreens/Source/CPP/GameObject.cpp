#include "GameObject.h"

GameObject::GameObject() {
	parent = NULL;
	Components.push_back(transform);
}

GameObject::~GameObject() {
	for (unsigned int i = 0; i< children.size(); i++){
		delete children[i];
	}
}
void GameObject::AddChild(GameObject* s) {
	children.push_back(s);
		s->parent = this;
}
void GameObject::Update(float msec) {
	//Updating world position
	if (parent) { //This node has a parent...
		//setting world position
		transform.SetWorldPosition(parent->transform.GetWorldPosition() * transform.GetPosition());
	}
	else { //Root node, world transform is local transform!
		//transform.SetPosition(transform.GetPosition());
	}



	for (std::vector<GameObject*>::iterator i = children.begin(); i != children.end(); ++i)
	{
		(*i)->Update(msec);
	}
}