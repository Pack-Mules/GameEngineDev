#ifndef RIGIDBODY_H
#define RIGIDBODY_H

#include "Component.h"
#include "GameObject.h"
#include "Vectors.h"
#include "Transform.h"
#include "AFKEngine.h"

class Rigidbody : public Component {
public:
	//TODO; In order to check we aren't comparing the same Rigidbody (rb != rigidBody), I think we should use
	// id, where rb.id != rigidBody.id, and id is a randomly generated value
	// IsGrounded() Function implementation
	float id;

	class GameObject* gameObject;

	enum Shape { Rectangle, Circle };
	Shape shape = Rectangle;


	//the other transform component of the gameObject
	Transform* transform;
	sf::CircleShape *cs;

	float frictionVal = 1.0f;
	float mass = 1.0f;                             // Mass of the RigidBody
	float bounciness = 1;                        // The bounciness factor (value between 0 and 1, 0 being no bounce, and 1 being super bouncy!)
	bool obeysGravity = true;                    // Whether or not this body obeys gravity
	Vector2 gravity = Vector2(0, -0.0f);     // The gravity vector applied to this body

	Vector2 currentVelocity;                     // The current velocity the body is moving at
	Vector2 maxVelocity = Vector2(10.0f, 10.0f); // The maximum allowed velocity for this object

	bool grounded;
	bool moveable = true;

	//Vector2 bounds[2];



	struct AABB
	{
		Vector2 bLeft;
		Vector2 tRight;
	};

	AABB aabb;

private:
	Vector2 totalForces;




public:
	void AddForce(Vector2 force)
	{
		totalForces += force;
	}

	void Stop()
	{
		currentVelocity = Vector2(0.0f, 0.0f);
		totalForces = Vector2(0.0f, 0.0f);
	}


	void SetAABB()
	{
		//bounds[0] = Vector2(transform->xWorld, transform->yWorld + cs->getGlobalBounds().height);


		//bounds[1] = Vector2(transform->xWorld + cs->getGlobalBounds().width, transform->yWorld);

		aabb.bLeft = Vector2(transform->xWorld, transform->yWorld + cs->getGlobalBounds().height);
		aabb.tRight = Vector2(transform->xWorld + cs->getGlobalBounds().width, transform->yWorld);

		/*Bounds bound = new Bounds(new Vector2(0, 0), new Vector2(1, 1));

		Renderer renderer = GetComponent<Renderer>();

		if (renderer)
		{
		bound = renderer.bounds;
		}

		aabb.bLeft = new Vector2(bound.center.x - bound.extents.x, bound.center.y - bound.extents.y);
		aabb.tRight = new Vector2(bound.center.x + bound.extents.x, bound.center.y + bound.extents.y);
		*/
	}

	void Start() {
		SetAABB();
		/*engine = GameObject.FindWithTag("PhysicsEngine").GetComponent<PhysicsEngine>();

		engine.AddRigidBody(this);
		*/
	}

	void Integrate(float dT) {
		/// 
		/// If this object is affected by gravity and not grounded, add gravity force
		/// otherwise if our current y velocity is less than 0.05f, set to 0
		if (obeysGravity && !IsGrounded()) {
			AddForce(gravity);
		}
		else {
			if (abs(currentVelocity.y) < 0.05f) currentVelocity.y = 0;
		}
		///
		///
		///

		Vector2 acceleration = totalForces / mass;
		if (mass == 0)
			acceleration = Vector2(0.0f, 0.0);

		currentVelocity += acceleration * dT;

		float frictionEffect = frictionVal;// 0.998f; //1 for zero friction
		currentVelocity *= frictionEffect;

		//slowing down
		if (currentVelocity.length() < 0.01f)
			currentVelocity = Vector2(0, 0);




		//Vector2 temp = Vector2(transform->x, transform->y);
		//temp += currentVelocity * dT;
		transform->Translate(currentVelocity*dT);
		//moving

		SetAABB();
		//updating new bounding box

		//if hit edges...
		if (aabb.bLeft.x < 0)
			currentVelocity.x = abs(currentVelocity.x);
		if (aabb.bLeft.y < 0)
			currentVelocity.y = abs(currentVelocity.y);

		if (aabb.tRight.x > AFKEngine::ScreenWidth)
			currentVelocity.x = -abs(currentVelocity.x);
		if (aabb.tRight.y > AFKEngine::ScreenHeight)
			currentVelocity.y = -abs(currentVelocity.y);



		totalForces = Vector2(0.0f, 0.0f);
	}

	bool IsGrounded() {

		return false;
	}

};

#endif