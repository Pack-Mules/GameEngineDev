
#include "Matrices.h"
#include "Component.h"

class Transform: public Component {



public: 

	Transform(){}

	void SetWorldPosition(const Matrix4 &matrix) { WorldPosition = matrix; UpdateXYZ(); }//UpdatePosition}
	Matrix4 GetWorldPosition() { return WorldPosition; }

	void SetPosition(const Matrix4 &matrix) { Position = matrix; UpdateXYZ(); }
	void SetPosition(Vector2 vector);
	void SetPosition(Vector3 vector);

	Matrix4 GetPosition() { return Position; }

	void Translate(Vector3 vec) {
		Position.translate(vec); UpdateXYZ();
	}
	


private:
	void UpdateXYZ() { x = Position[12]; y = Position[13]; z = Position[14]; 
				xWorld = WorldPosition[12]; yWorld = WorldPosition[13]; zWorld = WorldPosition[14];
						}

public:
	float x;
	float y;
	float z;


	float xWorld;
	float yWorld;
	float zWorld;
private:

	Matrix4 WorldPosition;
	Matrix4 Position;



};