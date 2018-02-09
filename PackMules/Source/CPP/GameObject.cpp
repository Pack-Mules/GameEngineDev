#include "GameObject.h"

GameObject::~GameObject(void) {
	for (unsigned int i = 0; i< children.size(); i++){
		delete children[i];
	}
}
void GameObject::AddChild(GameObject* s) {
	children.push_back(s);
		s->parent = this;
}
void GameObject::Update(float msec) {
	if (parent) { //This node has a parent...
		worldTransform = parent->worldTransform * transform;
	}
	else { //Root node, world transform is local transform!
		worldTransform = transform;
	}
	for (std::vector<GameObject*>::iterator i = children.begin(); i != children.end(); ++i)
	{
		(*i)->Update(msec);
	}
}