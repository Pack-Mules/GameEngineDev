#include "SFML/Graphics.hpp"
#include "SFML/OpenGL.hpp"
#include "Matrices.h"

class GameObject {
public:
	GameObject() { parent = NULL; }
	~GameObject(void);
	void SetTransform(const Matrix4 &matrix) { transform = matrix; }
	Matrix4 GetTransform() { return transform; }
	Matrix4 GetWorldTransform() { return worldTransform; }
	//void SetParent(GameObject& p) { parent = p; }
	void AddChild(GameObject* s);
	virtual void Update(float msec);

protected:
	GameObject* parent;
	Matrix4 worldTransform;
	Matrix4 transform;
	std::vector<GameObject*> children;
};