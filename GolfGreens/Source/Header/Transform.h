#ifndef TRANSFORM_H
#define TRANSFORM_H
#include "Matrices.h"
#include "Component.h"

class Transform: public Component {



public: 

	Transform() { }

	void SetWorldPosition(const Matrix4 &matrix) { WorldPosition = matrix; UpdateXYZ(); }//UpdatePosition
	Matrix4 GetWorldPosition() { return WorldPosition; }

	void SetPosition(const Matrix4 &matrix) { Position = matrix; UpdateXYZ(); }
	void SetPosition(Vector2 vector);
	void SetPosition(Vector3 vector);

	Matrix4 GetPosition() { return Position; }

	void SetWorldScale(const Matrix4 &matrix) { WorldScale = matrix; UpdateScale(); }//Update Scale
	Matrix4 GetWorldScale() { return WorldScale; }

	void SetScale(const Matrix4 &matrix) { Scale = matrix; UpdateScale(); }
	void SetScale(Vector2 vector);
	void SetScale(Vector3 vector);

	Matrix4 GetScale() { return Scale; }

	void Translate(Vector3 vec) {
		Position.translate(vec); UpdateXYZ();
	}

	void ChangeScale(Vector3 vec) {
		Scale.scale(vec.x, vec.y, vec.z); UpdateScale();
	}
	


private:
	void UpdateXYZ() { x = Position[12]; y = Position[13]; z = Position[14]; 
				xWorld = WorldPosition[12]; yWorld = WorldPosition[13]; zWorld = WorldPosition[14];
						}

	void UpdateScale() {
		xScale = Scale[0]; yScale = Scale[5]; zScale = Scale[10];
		xWorldScale = WorldScale[10]; yWorldScale = WorldScale[5]; zWorldScale = WorldScale[10];
	}

public:
	float x;
	float y;
	float z;


	float xWorld;
	float yWorld;
	float zWorld;

	float xScale;
	float yScale;
	float zScale;
	
	float xWorldScale;
	float yWorldScale;
	float zWorldScale;

private:

	Matrix4 WorldPosition;
	Matrix4 Position;
	Matrix4 WorldScale;
	Matrix4 Scale;



};

#endif