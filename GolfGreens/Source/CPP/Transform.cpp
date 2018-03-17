#include "Component.h"
#include "Transform.h"


void Transform::SetPosition(Vector2 vector) {
	Position[12] = vector.x;
	Position[13] = vector.y;
	UpdateXYZ();
}

void Transform::SetPosition(Vector3 vector) {
	Position[12] = vector.x;
	Position[13] = vector.y;
	Position[13] = vector.z;
	UpdateXYZ();
}