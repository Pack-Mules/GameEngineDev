#include "Rigidbody.h"
#include "Vectors.h"
#include <list>
#include <map>
#include <math.h>
#include <algorithm>

class PhysicsEngine {

public:
	float groundedTol = 0.05f;

	struct CollisionPair {
		Rigidbody* rigidBodyA;
		Rigidbody* rigidBodyB;
	};

	struct CollisionInfo {
		Vector2 collisionNormal;
		float penetration;
	};

private:
	//map values: Int (ID's of both pairs added together)
	std::map<int, std::pair<CollisionPair, CollisionInfo>> collisions = std::map<int, std::pair<CollisionPair, CollisionInfo>>();
	std::list<Rigidbody*> rigidBodies = std::list<Rigidbody*>();



public:
	bool IsGrounded(Rigidbody *rigidBody) {
		for(Rigidbody *rb : rigidBodies) {
			if (&rb != &rigidBody) {
				if (rigidBody->aabb.bLeft.x < rb->aabb.tRight.x
					&& rigidBody->aabb.tRight.x > rb->aabb.bLeft.x
					&& abs(rigidBody->aabb.bLeft.y - rb->aabb.tRight.y) <= groundedTol) {
					if (abs(rigidBody->currentVelocity.y) < groundedTol)
						return true;
				}
			}
		}
		return false;
	}
	void AddRigidBody(Rigidbody* rigidBody) {
		rigidBodies.push_back(rigidBody);
		std::cout << "Added rigidbody: " << &rigidBody << std::endl;
	}

	void IntegrateBodies(float dT) {
		for(Rigidbody *rb : rigidBodies) {
			rb->Integrate(dT);
		}
	}

private:
	void CheckCollisions() {
		for(Rigidbody* bodyA : rigidBodies) {
			//original code was Rigidbody bodyB: 
			//rigidBodies.GetRange(rigidBodies.IndexOf(bodyA), rigidBodies.Count - rigidBodies.IndexOf(bodyA))
			//starting from a, compares everything. no code in c++ though
			for(Rigidbody* bodyB : rigidBodies) {
				if (bodyA->id != bodyB->id) {
					int pairID = bodyA->id * 10 + bodyB->id * 10;
					CollisionPair pair = CollisionPair();
					CollisionInfo colInfo = CollisionInfo();
					pair.rigidBodyA = bodyA; pair.rigidBodyB = bodyB;

					Vector2 distance = Vector2(bodyB->transform->x - bodyA->transform->x,
						bodyB->transform->y - bodyA->transform->y);

					Vector2 halfSizeA = (bodyA->aabb.tRight - bodyA->aabb.bLeft) / 2;
					Vector2 halfSizeB = (bodyB->aabb.tRight - bodyB->aabb.bLeft) / 2;

					Vector2 gap = Vector2(abs(distance.x), abs(distance.y)) - (halfSizeA + halfSizeB);
					//std::cout << "gap is " << gap.x << ", " << gap.y << std::endl;

					// Seperating Axis Theorem test
					if (gap.x < 0 && gap.y < 0) {
						
						//original code
						//if (collisions.find(pair) != collisions.end()) {
							//std::map<CollisionPair, CollisionInfo>::iterator it = collisions.find(pair);
							//collisions.erase(it);
						//}
						std::map<int, std::pair<CollisionPair, CollisionInfo>>::iterator it;
						for (it = collisions.begin(); it != collisions.end(); it++){
							if (it->first == pairID) {
								collisions.erase(it);
								break;
							}
						}

						//more horizontal dist
						if (gap.x > gap.y) {
							std::cout << "COLLISION" << std::endl;
							//body1 is to the right of body2
							if (distance.x > 0) {
								colInfo.collisionNormal = Vector2(1, 0);
								// ... Update collision normal
							}
							//body1 is to the left of body2
							else {
								colInfo.collisionNormal = Vector2(-1, 0);
								// ... Update collision normal
							}
							colInfo.penetration = gap.x;
						}
						//more vertical distance
						else {
							//body1 is above body2
							if (distance.y > 0) {
								colInfo.collisionNormal = Vector2(0, 1);
								// ... Update collision normal
							}
							//body1 is below body2
							else {
								colInfo.collisionNormal = Vector2(0, -1);
								// ... Update collision normal
							}
							colInfo.penetration = gap.y;
						}

						collisions.insert(std::make_pair(pairID, std::make_pair(pair, colInfo)));
					}
					/*old code c# unity
					
					else if (collisions.find(pair) != collisions.end()) {
						std::map<CollisionPair, CollisionInfo>::iterator it = collisions.find(pair);
						collisions.erase(it);
					}*/
					else {
						std::map<int, std::pair<CollisionPair, CollisionInfo>>::iterator it;
						for (it = collisions.begin(); it != collisions.end(); it++) {
							if (it->first == pairID) {
								collisions.erase(it);
								break;
							}
						}
					}

				}
			}
		}
	}

	void ResolveCollisions() {
		for (auto& it : collisions) {
			CollisionPair pair = it.second.first;
			CollisionInfo info = it.second.second;
			float minBounce = std::min(pair.rigidBodyA->bounciness, pair.rigidBodyB->bounciness);
			float velAlongNormal = (pair.rigidBodyB->currentVelocity - pair.rigidBodyA->currentVelocity).dot(it.second.second.collisionNormal);

			if (velAlongNormal > 0) continue;

			float j = -(1 + minBounce) * velAlongNormal;
			float invMassA, invMassB;
			if (pair.rigidBodyA->mass == 0)
				invMassA = 0;
			else
				invMassA = 1 / pair.rigidBodyA->mass;

			if (pair.rigidBodyB->mass == 0)
				invMassB = 0;
			else
				invMassB = 1 / pair.rigidBodyB->mass;

			j /= invMassA + invMassB;


			Vector2 impulse = j * it.second.second.collisionNormal;

			// ... update velocities

			pair.rigidBodyA->currentVelocity -= impulse;
			if (pair.rigidBodyB->moveable)
				pair.rigidBodyB->currentVelocity += impulse;
			if (abs(it.second.second.penetration) > 0.01f) {
				PositionalCorrection(pair, info);
			}
		}
	}

	/*
	* ______________ Why do we need this function?
	* Corrects the object from sticking into each other
	* Tries to move the object out of the objects it is stuck in
	* ______________ Try taking it out and see what happens
	*/
	void PositionalCorrection(CollisionPair c, CollisionInfo i) {
		const float percent = 0.2f;

		float invMassA, invMassB;
		if (c.rigidBodyA->mass == 0)
			invMassA = 0;
		else
			invMassA = 1 / c.rigidBodyA->mass;

		if (c.rigidBodyB->mass == 0)
			invMassB = 0;
		else
			invMassB = 1 / c.rigidBodyB->mass;

		Vector2 correction = ((i.penetration / (invMassA + invMassB)) * percent) * -i.collisionNormal;

		Vector2 temp = Vector2(c.rigidBodyA->transform->x, c.rigidBodyA->transform->y);
		temp -= invMassA * correction;
		c.rigidBodyA->transform->SetPosition(temp);

		temp = Vector2(c.rigidBodyB->transform->x, c.rigidBodyB->transform->y);
		temp += invMassB * correction;
		c.rigidBodyB->transform->SetPosition(temp);
	}

	public:
	void UpdatePhysics(float dT) {
		CheckCollisions();
		ResolveCollisions();
		IntegrateBodies(dT);
	}

};



//dot product