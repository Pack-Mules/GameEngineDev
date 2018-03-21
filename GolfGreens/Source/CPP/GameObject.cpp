#include "GameObject.h"

GameObject::GameObject() {
	parent = NULL;
	rigidbody.gameObject = this;
	rigidbody.transform = &transform;
	rigidbody.cs = &cs;
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
			std::cout << "Child removed from parent.";
			children[i]->transform.SetPosition(Vector3(children[i]->transform.xWorld, children[i]->transform.yWorld, children[i]->transform.zWorld));
			children[i]->transform.SetScale(Vector3(children[i]->transform.xWorldScale, children[i]->transform.yWorldScale, children[i]->transform.zWorldScale));

			children[i]->parent = NULL;
			children.erase(children.begin() + i);
		}
	}
}

void GameObject::Update(float msec) {
	//Updating world position
	if (parent) { //This node has a parent...
		//setting world position
		transform.SetWorldPosition(parent->transform.GetWorldPosition() * transform.GetPosition());
		transform.SetWorldScale(parent->transform.GetWorldScale() * transform.GetScale());
	}
	else { //Root node, world transform is local transform!
		transform.SetWorldPosition(transform.GetPosition());
		transform.SetWorldScale(transform.GetScale());
	}



	for (std::vector<GameObject*>::iterator i = children.begin(); i != children.end(); ++i)
	{
		(*i)->Update(msec);
	}
}