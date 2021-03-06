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
	Position[14] = vector.z;
	UpdateXYZ();
}

void Transform::SetScale(Vector2 vector) {
	Scale[0] = vector.x;
	Scale[5] = vector.y;
	UpdateScale();

}

void Transform::SetScale(Vector3 vector) {
	Scale[0] = vector.x;
	Scale[5] = vector.y;
	Scale[10] = vector.z;
	UpdateScale();
}

void Transform::Translate(Vector3 vec) {
	Position.translate(vec); UpdateXYZ();
}

void Transform::Translate(Vector2 vec) {
	Vector3 newVec = Vector3(vec.x, vec.y, 0);
	Translate(newVec);
}