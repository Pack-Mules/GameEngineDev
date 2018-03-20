//#include "Rigidbody.h"
//#include "Vectors.h"
//#include <list>
//#include <map>
//#include <math.h>
//#include <algorithm>
//
//class PhysicsEngine {
//
//public:
//	float groundedTol = 0.05f;
//
//	struct CollisionPair {
//		Rigidbody* rigidBodyA;
//		Rigidbody* rigidBodyB;
//	};
//
//	struct CollisionInfo {
//		Vector2 collisionNormal;
//		float penetration;
//	};
//
//private:
//	std::map<CollisionPair, CollisionInfo> collisions = std::map<CollisionPair, CollisionInfo>();
//	std::list<Rigidbody*> rigidBodies = std::list<Rigidbody*>();
//
//
//
//public:
//	bool IsGrounded(Rigidbody *rigidBody) {
//		for(Rigidbody *rb : rigidBodies) {
//			if (&rb != &rigidBody) {
//				if (rigidBody->aabb.bLeft.x < rb->aabb.tRight.x
//					&& rigidBody->aabb.tRight.x > rb->aabb.bLeft.x
//					&& abs(rigidBody->aabb.bLeft.y - rb->aabb.tRight.y) <= groundedTol) {
//					if (abs(rigidBody->currentVelocity.y) < groundedTol)
//						return true;
//				}
//			}
//		}
//		return false;
//	}
//	void AddRigidBody(Rigidbody* rigidBody) {
//		rigidBodies.push_back(rigidBody);
//	}
//
//	void IntegrateBodies(float dT) {
//		for(Rigidbody *rb : rigidBodies) {
//			rb->Integrate(dT);
//		}
//	}
//
//private:
//	void CheckCollisions() {
//		for(Rigidbody* bodyA : rigidBodies.size-1) {
//			for(Rigidbody* bodyB : rigidBodies.GetRange(rigidBodies.IndexOf(bodyA), rigidBodies.Count - rigidBodies.IndexOf(bodyA))) {
//				if (&bodyA != &bodyB) {
//					CollisionPair pair = CollisionPair();
//					CollisionInfo colInfo = CollisionInfo();
//					pair.rigidBodyA = bodyA; pair.rigidBodyB = bodyB;
//
//					Vector2 distance = Vector2(bodyB->transform.x - bodyA->transform.x, 
//						bodyB->transform.y - bodyA->transform.y);
//
//					Vector2 halfSizeA = (bodyA->aabb.tRight - bodyA->aabb.bLeft) / 2;
//					Vector2 halfSizeB = (bodyB->aabb.tRight - bodyB->aabb.bLeft) / 2;
//
//					Vector2 gap = Vector2(abs(distance.x), abs(distance.y)) - (halfSizeA + halfSizeB);
//
//					// Seperating Axis Theorem test
//					if (gap.x < 0 && gap.y < 0) {
//						if (collisions.ContainsKey(pair)) {
//							collisions.Remove(pair);
//						}
//						//more horizontal dist
//						if (gap.x > gap.y) {
//							//body1 is to the right of body2
//							if (distance.x > 0) {
//								colInfo.collisionNormal = Vector2(1, 0);
//								// ... Update collision normal
//							}
//							//body1 is to the left of body2
//							else {
//								colInfo.collisionNormal = Vector2(-1, 0);
//								// ... Update collision normal
//							}
//							colInfo.penetration = gap.x;
//						}
//						//more vertical distance
//						else {
//							//body1 is above body2
//							if (distance.y > 0) {
//								colInfo.collisionNormal = Vector2(0, 1);
//								// ... Update collision normal
//							}
//							//body1 is below body2
//							else {
//								colInfo.collisionNormal = Vector2(0, -1);
//								// ... Update collision normal
//							}
//							colInfo.penetration = gap.y;
//						}
//						collisions.Add(pair, colInfo);
//					}
//					else if (collisions.ContainsKey(pair)) {
//						collisions.Remove(pair);
//					}
//
//				}
//			}
//		}
//	}
//
//	void ResolveCollisions() {
//		for(CollisionPair pair : collisions.key_comp) {
//			float minBounce = std::min(pair.rigidBodyA.bounciness, pair.rigidBodyB.bounciness);
//			float velAlongNormal = (pair.rigidBodyB.currentVelocity - pair.rigidBodyA.currentVelocity, collisions[pair].collisionNormal).dot;
//			if (velAlongNormal > 0) continue;
//
//			float j = -(1 + minBounce) * velAlongNormal;
//			float invMassA, invMassB;
//			if (pair.rigidBodyA.mass == 0)
//				invMassA = 0;
//			else
//				invMassA = 1 / pair.rigidBodyA.mass;
//
//			if (pair.rigidBodyB.mass == 0)
//				invMassB = 0;
//			else
//				invMassB = 1 / pair.rigidBodyB.mass;
//
//			j /= invMassA + invMassB;
//
//			Vector2 impulse = j * collisions[pair].collisionNormal;
//
//			// ... update velocities
//
//			pair.rigidBodyA.currentVelocity -= impulse;
//			if (pair.rigidBodyB.moveable)
//				pair.rigidBodyB.currentVelocity += impulse;
//			if (abs(collisions[pair].penetration) > 0.01f) {
//				PositionalCorrection(pair);
//			}
//		}
//	}
//
//	/*
//	* ______________ Why do we need this function?
//	* Corrects the object from sticking into each other
//	* Tries to move the object out of the objects it is stuck in
//	* ______________ Try taking it out and see what happens
//	*/
//	void PositionalCorrection(CollisionPair c) {
//		const float percent = 0.2f;
//
//		float invMassA, invMassB;
//		if (c.rigidBodyA.mass == 0)
//			invMassA = 0;
//		else
//			invMassA = 1 / c.rigidBodyA.mass;
//
//		if (c.rigidBodyB.mass == 0)
//			invMassB = 0;
//		else
//			invMassB = 1 / c.rigidBodyB.mass;
//
//		Vector2 correction = ((collisions[c].penetration / (invMassA + invMassB)) * percent) * -collisions[c].collisionNormal;
//
//		Vector2 temp = Vector2(c.rigidBodyA.transform.x, c.rigidBodyA.transform.y);
//		temp -= invMassA * correction;
//		c.rigidBodyA.transform.SetPosition(temp);
//
//		temp = Vector2(c.rigidBodyB.transform.x, c.rigidBodyB.transform.y);
//		temp += invMassB * correction;
//		c.rigidBodyB.transform.SetPosition(temp);
//	}
//
//	void UpdatePhysics(float dT) {
//		CheckCollisions();
//		ResolveCollisions();
//		IntegrateBodies(dT);
//	}
//
//};