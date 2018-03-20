#include "GameObject.h"

GameObject::GameObject() {
	parent = NULL;
	Components.push_back(&transform);

}

GameObject::~GameObject() {
	for (unsigned int i = 0; i< children.size(); i++){
		delete children[i];
	}
}


void GameObject::AddChild(GameObject* s) {
	//if child has a parent, then we remove their link
	if (s->parent != NULL) {
		s->parent->RemoveChild(s);
	}

	//add the child to the gameobject children array
	children.push_back(s);
	s->parent = this;
}

void GameObject::RemoveChild(GameObject* s) {
	for (int i = 0; i < children.size(); i++) {
		if (children[i] == s) {
			std::cout << "ye";
			children.erase(children.begin() + i);
		}
	}
}

void GameObject::Update(float msec) {
	//Updating world position
	if (parent) { //This node has a parent...
		//setting world position
		transform.SetWorldPosition(parent->transform.GetWorldPosition() * transform.GetPosition());
	}
	else { //Root node, world transform is local transform!
		transform.SetWorldPosition(transform.GetPosition());
	}



	for (std::vector<GameObject*>::iterator i = children.begin(); i != children.end(); ++i)
	{
		(*i)->Update(msec);
	}
}