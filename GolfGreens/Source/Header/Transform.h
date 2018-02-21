
#include "Matrices.h"
#include "Component.h"

class Transform: public Component {



public: 

	Transform(){}

	void SetWorldPosition(const Matrix4 &matrix) { WorldPosition = matrix; }
	Matrix4 GetWorldPosition() { return WorldPosition; }

	void SetPosition(const Matrix4 &matrix) { Position = matrix; UpdateXYZ(); }
	Matrix4 GetPosition() { return Position; }


	


private:
	void UpdateXYZ() { x = Position[12]; y = Position[13]; z = Position[13]; }


public:
	float x;
	float y;
	float z;


private:

	Matrix4 WorldPosition;
	Matrix4 Position;



};