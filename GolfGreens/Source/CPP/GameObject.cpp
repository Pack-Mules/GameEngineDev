#include "GameObject.h"

GameObject::GameObject() {
	parent = NULL;
	id = rand() % 99999;

	rigidbody.id = this->id;
	rigidbody.gameObject = this;
	rigidbody.transform = &transform;
	Components.push_back(&transform);

	rigidbody.cs = &cs;
	rigidbody.rs = &rs;
}

GameObject::~GameObject() {
	for (unsigned int i = 0; i< children.size(); i++) {
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
	//Vector3 tempPos = Vector3(s->transform.xWorld, s->transform.yWorld, s->transform.zWorld);
	//Vector3 tempScale = Vector3(s->transform.xWorldScale, s->transform.yWorldScale, s->transform.zWorldScale);
	s->transform.SetPosition(Vector3(s->transform.xWorld - this->transform.xWorld, s->transform.yWorld - this->transform.yWorld, s->transform.zWorld - this->transform.zWorld));
	s->transform.SetScale(Vector3(s->transform.xWorldScale - this->transform.xWorldScale, s->transform.yWorldScale - this->transform.yWorldScale, s->transform.zWorldScale - this->transform.zWorldScale));
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


	//updating position with rigidbody

	//our sprite
	cs.setPosition(transform.xWorld, transform.yWorld);
	rs.setPosition(transform.xWorld, transform.yWorld);

	//Updating world position values
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